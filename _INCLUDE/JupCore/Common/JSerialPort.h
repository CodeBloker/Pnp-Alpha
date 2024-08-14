#pragma once
#ifndef _JSERIALPORT_
#define _JSERIALPORT_

#include <Windows.h>
#include <string>
#include <queue>
#include <mutex>

#define SERIAL_NAME_SIZE	128

#define ASCII_LF	0x0A
#define ASCII_CR	0x0D
#define ASCII_XON	0x11
#define ASCII_XOFF	0x13

#include "JupCore_export.h"

class JUPCORE_EXPORT JSerialPort
{
public:
	JSerialPort();
	virtual ~JSerialPort();
	
	int OpenDevice(std::string portName, ULONG ulBaudRate, UCHAR ucByteSize, UCHAR ucParity, UCHAR ucStopBit, ULONG ulHandshake, char cXOn = ASCII_XON, char cXOff = ASCII_XOFF, ULONG ulReadSize = 1024, ULONG ulWriteBufSize = 1024);
	int CloseDevice();

	int Send(const char *buf, ULONG len);
	int Recv(char *buf, ULONG len);

	void AddReceivedData(const char *buf, int len);
	int GetReceiveData(char *buf, int len);

	int IsExistRecvData();
	void ClearReceiveData();

	std::string GetPortName() { return m_portName; }
	ULONG GetReadSize() { return m_ulReadSize; }
	ULONG GetWriteSize() { return m_ulWriteSize; }

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
	ULONG m_ulThreadID = 0;
	ULONG m_ulReadSize = 1024;
	ULONG m_ulWriteSize = 1024;

	HANDLE m_hThread = NULL;
	HANDLE m_hEventEnd = NULL;
	HANDLE m_hPort = NULL;

	std::mutex m_dataMutex;
	std::mutex m_portMutex;
	std::queue<char> m_queRecvData;
};

#endif //_JSERIALPORT_