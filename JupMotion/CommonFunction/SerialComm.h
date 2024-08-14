#pragma once
#include <string>
#include <mutex>
#include <Windows.h>

#define SERIAL_NAME_SIZE	128

#define ASCII_LF	0x0A
#define ASCII_CR	0x0D
#define ASCII_XON	0x11
#define ASCII_XOFF	0x13

class CSerialComm
{
public:
	CSerialComm();	
	virtual ~CSerialComm();
	
	int OpenDevice(std::string portName, unsigned long ulBaudRate, unsigned char ucByteSize, unsigned char ucParity, unsigned char ucStopBit, unsigned long ulHandshake, char cXOn = ASCII_XON, char cXOff = ASCII_XOFF, unsigned long ulReadSize = 1024, unsigned long ulWriteBufSize = 1024);
	int CloseDevice();

	int Send(const char *buf, unsigned long len);
	int Send(const unsigned char *buf, unsigned long len);
	int Recv(char *buf, unsigned long len);

	void AddReceivedData(const char *buf, int len);
	int GetReceiveData(char *buf, int len);
	
	int IsExistRecvData();
	void ClearReceiveData();

	std::string GetPortName() { return m_portName; }
	unsigned long GetReadSize() { return m_ulReadSize; }
	unsigned long GetWriteSize() { return m_ulWriteSize; }

	bool IsOpened() { return m_bConnected; }
	bool GetRecvThreadRun() { return m_bRecvThreadRun; }
	HANDLE GetEndEventHandle() { return m_hEventEnd; }
	HANDLE GetPortHandle() { return m_hPort; }

private:			
	char m_portName[SERIAL_NAME_SIZE];
	OVERLAPPED m_osRead;
	OVERLAPPED m_osWrite;

	bool m_bConnected = false;
	bool m_bRecvThreadRun = false;
	unsigned long m_ulThreadID = 0;
	unsigned long m_ulReadSize = 1024;
	unsigned long m_ulWriteSize = 1024;

	HANDLE m_hThread = NULL;
	HANDLE m_hEventEnd = NULL;
	HANDLE m_hPort = NULL;
	
	std::mutex m_mutexData;
	std::mutex m_mutexPort;
	std::vector<char> m_queRecvData;
};