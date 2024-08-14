#pragma once
#ifndef _JCLIENTSOCKET_
#define _JCLIENTSOCKET_

//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif

#pragma comment(lib,"ws2_32.lib")

#include <WinSock2.h>
#include <string>
#include <queue>
#include <mutex>

#define SERVER_NAME_SIZE		128
#define SOCKET_BUFFER_SIZE		8192

struct SocRecvData
{
	char buf[SOCKET_BUFFER_SIZE];
	int size = 0;
};

#include "JupCore_export.h"

class JUPCORE_EXPORT JClientSocket
{
public:
	JClientSocket();
	virtual ~JClientSocket();

	bool Connect(std::string server, USHORT sPort);
	void Close();

	int SendToHost(const char *buf, int len, int retryCnt = 1);

	void AddReceivedData(const char *buf, int len);
	int GetReceiveData(char *buf, int len);

	bool IsExistReceiveData();
	void ClearReceiveData();

	bool IsConnected() { return m_bConnected; }
	bool GetRecvThreadRun() { return m_bRecvThreadRun; }
	HANDLE GetEndEventHandle() { return m_hEventEnd; }
	SOCKET GetSocket() { return m_hSocket; }

private:
	char m_serverIP[SERVER_NAME_SIZE];
	USHORT m_sPort = 0;

	bool m_bConnected = false;
	bool m_bRecvThreadRun = false;
	ULONG m_ulThreadID = 0;

	HANDLE m_hThread = NULL;
	HANDLE m_hEventEnd = NULL;
	SOCKET m_hSocket = NULL;

	std::mutex m_dataMutex;
	std::mutex m_socketMutex;
	std::queue<SocRecvData> m_queRecvData;
};

#endif //_JCLIENTSOCKET_