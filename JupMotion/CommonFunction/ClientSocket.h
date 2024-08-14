#pragma once
#include <string>
#include <WinSock2.h>
#include <mutex>

//#define ushort unsigned short
//#define ulong unsigned long

#define SERVER_NAME_SIZE		128
#define SOCKET_BUFFER_SIZE		8192

struct SocRecvData
{	
	char buf[SOCKET_BUFFER_SIZE];
	int size = 0;
};

class CClientSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

	bool Connect(std::string server, unsigned short sPort);
	void Close();

	int SendToHost(const char *buf, int len, int retryCnt = 1);

	void AddReceivedData(const char *buf, int len);
	int GetReceiveData(char *buf, int len);

	bool IsExistReceiveData();
	void ClearReceiveData();

	bool IsConnected() { return m_bConnected; }
	bool GetRecvThreadRun() { return m_bRecvThreadRun; }
	void SetConnected(bool state) {m_bConnected = state;}
	HANDLE GetEndEventHandle() { return m_hEventEnd; }
	SOCKET GetSocket() { return m_hSocket; }

private:
	char m_serverIP[SERVER_NAME_SIZE];
	unsigned short m_sPort = 0;

	bool m_bConnected = false;
	bool m_bRecvThreadRun = false;
	unsigned long m_ulThreadID = 0;

	HANDLE m_hThread = NULL;
	HANDLE m_hEventEnd = NULL;
	SOCKET m_hSocket = NULL;

	std::mutex  m_mutexData;
	std::mutex  m_mutexSocket;
	std::vector<SocRecvData> m_queRecvData;
};