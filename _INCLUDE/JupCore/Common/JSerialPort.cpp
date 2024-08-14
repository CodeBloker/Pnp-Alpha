#include "JSerialPort.h"
#include <iostream>

ULONG WINAPI SerialPort_RecvThread(void *pParam)
{
	JSerialPort *pComm = (JSerialPort*)pParam;

	ULONG ulEvent = 0;
	ULONG ulRead = 0;
	bool bOk = true;
	char* buff = NULL;

	OVERLAPPED os;
	memset(&os, 0, sizeof(OVERLAPPED));

	std::cout << "JSerialPort Recv thread :: Thread Start" << std::endl;

	ResetEvent(pComm->GetEndEventHandle());

	if (!(os.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) || !SetCommMask(pComm->GetPortHandle(), EV_RXCHAR))
	{
		std::cout << "Set comm mask failed";
		return 0;
	}

	buff = new char[pComm->GetReadSize()];

	while (pComm->GetRecvThreadRun())
	{
		ulEvent = 0;
		WaitCommEvent(pComm->GetPortHandle(), &ulEvent, NULL);

		if ((ulEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			do
			{
				memset(buff, 0, pComm->GetReadSize());
				ulRead = pComm->Recv(buff, pComm->GetReadSize());

				std::cout << "JSerialPort Recv thread :: Recv OK, size =" << ulRead << std::endl;
				pComm->AddReceivedData(buff, ulRead);

				Sleep(10);
			} while (ulRead);

		}
		Sleep(50);
	}

	SetEvent(pComm->GetEndEventHandle());

	CloseHandle(os.hEvent);

	delete[] buff;

	std::cout << "JSerialPort Recv thread :: Thread End" << std::endl;

	return 1;
}

JSerialPort::JSerialPort()
{
	::ZeroMemory(&m_portName, sizeof(m_portName));
	::ZeroMemory(&m_osRead, sizeof(OVERLAPPED));
	::ZeroMemory(&m_osWrite, sizeof(OVERLAPPED));

	m_hEventEnd = CreateEvent(NULL, TRUE, FALSE, NULL);
}

JSerialPort::~JSerialPort()
{
	if (m_bConnected)
		CloseDevice();

	if (m_hEventEnd != NULL)
		CloseHandle(m_hEventEnd);

	if (m_bConnected && m_hPort != NULL)
		CloseHandle(m_hPort);
}

/*
	Open the device.
	Parameters
		szPortName			Port name
		ulBaudRate			Baud Rate
								CBR_110		110
								CBR_300		300
								...
								CBR_9600	9600
								CBR_14400	14400
								...
		ucByteSize			Transmission byte bits
		ucParity			Parity Bit
								JupENPARITY	2
								MARKPARITY	3
								NOPARITY	0
								ODDPARITY	1
								SPACEPARITY	4
		ucStopBit			Stop bits number
								ONESTOPBIT		0
								ONE5STOPBITS	1
								TWOSTOPBITS		2
		ulXonXoff			XON/XOFF written words
		ulReadSize		Receive buffer size of the device
		ulWriteSize		Send buffer size of the device


	Return
		1		: Success.
		0		: Port open failed
		-1		: Read/Write event fail to create object
		-2		: Port configuration failed
		-3		: Read monitoring thread generation (Registration) failed

	Remarks
		Refer to DCB structure of MSDN for details of each parameter.
*/
int JSerialPort::OpenDevice(std::string portName, ULONG ulBaudRate, UCHAR ucByteSize, UCHAR ucParity, UCHAR ucStopBit, ULONG ulHandshake, char cXOn, char cXOff, ULONG ulReadSize, ULONG ulWriteBufSize)
{
	DCB dcb;
	COMMTIMEOUTS timeouts;

	strcpy_s(m_portName, SERIAL_NAME_SIZE, portName.c_str());
	m_bConnected = false;
	m_ulReadSize = ulReadSize;
	m_ulWriteSize = ulWriteBufSize;

	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	if (!(m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
		return -1;

	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	if (!(m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
		return -1;

	m_hPort = CreateFileA(m_portName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL);

	if (m_hPort == NULL)
	{
		return 0;
	}

	SetCommMask(m_hPort, EV_RXCHAR);

	SetupComm(m_hPort, ulReadSize, ulWriteBufSize);
	PurgeComm(m_hPort, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	// ReadIntervalTimeout
	//0xFFFFFFFF	MAXulORD
	//0x00000064	0.1s
	//0x000001F4	0.5s
	//0x000003E8	1s
	timeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2 * CBR_9600 / ulBaudRate;
	timeouts.WriteTotalTimeoutConstant = 0;		// Disable

	SetCommTimeouts(m_hPort, &timeouts);

	dcb.DCBlength = sizeof(DCB);
	GetCommState(m_hPort, &dcb);

	dcb.BaudRate = ulBaudRate;
	dcb.ByteSize = ucByteSize;
	dcb.Parity = ucParity;
	dcb.StopBits = ucStopBit;

	switch (ulHandshake)
	{
	case 1:		// Harulare
		dcb.fOutxCtsFlow = TRUE;					// Enable CTS monitoring
		dcb.fOutxDsrFlow = TRUE;					// Enable DSR monitoring
		dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;	// Enable DTR handshaking
		dcb.fOutX = FALSE;							// Disable XON/XOFF for transmission
		dcb.fInX = FALSE;							// Disable XON/XOFF for receiving
		dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;	// Enable RTS handshaking
		break;

	case 2:		// XOn/XOff	
		dcb.fOutxCtsFlow = FALSE;					// Disable CTS (Clear To Send)
		dcb.fOutxDsrFlow = FALSE;					// Disable DSR (Data Set Ready)
		dcb.fDtrControl = DTR_CONTROL_DISABLE;		// Disable DTR (Data Terminal Ready)
		dcb.fOutX = TRUE;							// Enable XON/XOFF for transmission
		dcb.fInX = TRUE;							// Enable XON/XOFF for receiving
		dcb.fRtsControl = RTS_CONTROL_DISABLE;		// Disable RTS (Ready To Send)
		dcb.XonChar = cXOn;
		dcb.XoffChar = cXOff;
		dcb.XonLim = 100;
		dcb.XoffLim = 100;
		break;

	default:
		dcb.fOutxCtsFlow = FALSE;					// Disable CTS monitoring
		dcb.fOutxDsrFlow = FALSE;					// Disable DSR monitoring
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
		dcb.fOutX = FALSE;							// Disable XON/XOFF for transmission
		dcb.fInX = FALSE;							// Disable XON/XOFF for receiving
		dcb.fRtsControl = RTS_CONTROL_DISABLE;		// Disable RTS (Ready To Send)
		break;
	}

	if (!SetCommState(m_hPort, &dcb))
	{
		//MessageBoxA(NULL, "Set comm state failed", __FUNCTION__, MB_OK | MB_ICONSTOP);
		return -2;
	}

	m_hThread = ::CreateThread(NULL, NULL, SerialPort_RecvThread, this, NULL, &m_ulThreadID);
	if (m_hThread == NULL)
	{
		CloseDevice();
		//MessageBoxA(NULL, "Recv thread create failed", __FUNCTION__, MB_OK | MB_ICONSTOP);
		return -3;
	}

	m_bConnected = true;
	m_bRecvThreadRun = true;

	return 1;
}

int JSerialPort::CloseDevice()
{
	m_bRecvThreadRun = false;

	if (m_hPort != NULL)
	{
		SetCommMask(m_hPort, 0);
		PurgeComm(m_hPort, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);
		CloseHandle(m_hPort);
		m_hPort = NULL;
	}

	if (m_bConnected)
	{
		if (m_hThread != NULL)
		{
			WaitForSingleObject(m_hThread, INFINITE);
			m_hThread = NULL;
		}
	}

	m_bConnected = false;

	if (m_osRead.hEvent != NULL)
	{
		CloseHandle(m_osRead.hEvent);
		m_osRead.hEvent = NULL;
	}

	if (m_osWrite.hEvent != NULL)
	{
		CloseHandle(m_osWrite.hEvent);
		m_osWrite.hEvent = NULL;
	}
	return 1;
}

int JSerialPort::Send(const char *buf, ULONG len)
{
	ULONG ulWritten, ulError, ulErrorFlags;
	COMSTAT comstat;

	if (m_hPort == NULL)
		return -1;

	std::lock_guard lock(m_portMutex);

	if (!WriteFile(m_hPort, buf, len, &ulWritten, &m_osWrite))
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			while (!GetOverlappedResult(m_hPort, &m_osWrite, &ulWritten, TRUE))
			{
				ulError = GetLastError();
				if (ulError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError(m_hPort, &ulErrorFlags, &comstat);
					return -1;
				}
			}
		}
		else
		{
			ulWritten = 0;
			ClearCommError(m_hPort, &ulErrorFlags, &comstat);
		}
	}
	return ulWritten;
}

int JSerialPort::Recv(char *buf, ULONG len)
{
	ULONG ulRead, ulError, ulErrorFlags;
	COMSTAT comstat;

	ClearCommError(m_hPort, &ulErrorFlags, &comstat);
	ulRead = comstat.cbInQue;

	std::lock_guard lock(m_portMutex);

	if (ulRead > 0)
	{
		if (!ReadFile(m_hPort, buf, len, &ulRead, &m_osRead))
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				while (!GetOverlappedResult(m_hPort, &m_osRead, &ulRead, TRUE))
				{
					ulError = GetLastError();
					if (ulError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError(m_hPort, &ulErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				ulRead = 0;
				ClearCommError(m_hPort, &ulErrorFlags, &comstat);
			}
		}
	}
	return ulRead;
}

void JSerialPort::AddReceivedData(const char *buf, int len)
{
	std::lock_guard lock(m_dataMutex);

	for (int i = 0; i < len; i++)
	{
		m_queRecvData.push(buf[i]);
	}
}

int JSerialPort::GetReceiveData(char *buf, int len)
{
	std::lock_guard lock(m_dataMutex);

	memset(buf, 0, len);
	int size = m_queRecvData.size();
	if (m_queRecvData.size() == 0)
	{
		return 0;
	}

	std::cout << "GetReceiveData size:" << size << std::endl;
	int i = 0;
	for (i = 0; i < size && i < len; i++)
	{
		buf[i] = m_queRecvData.front();
		m_queRecvData.pop();
	}
	std::cout << "GetReceiveData len:" << len << "buff:" << buf;
	return i;
}

int JSerialPort::IsExistRecvData()
{
	std::lock_guard lock(m_dataMutex);

	return !m_queRecvData.empty();
}

void JSerialPort::ClearReceiveData()
{
	std::lock_guard lock(m_dataMutex);

	std::queue<char>().swap(m_queRecvData);
}
