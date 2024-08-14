#include "ClientSocket.h"
#include <Ws2tcpip.h>
//#pragma comment (lib, "ws2_32.lib")
using namespace std;


unsigned long WINAPI ClientSocket_RecvThread(void *pParam)
{
	CClientSocket *pSoc = (CClientSocket*)pParam;

	char szBuf[SOCKET_BUFFER_SIZE];
	int len, err;
	SOCKET sSoc;

	//qDebug() << "CClientSocket Recv thread :: Thread Start";

	ResetEvent(pSoc->GetEndEventHandle());
	
	while (pSoc->GetRecvThreadRun())
	{		
		sSoc = pSoc->GetSocket();
		if (sSoc == NULL)
			break;

		len = recv(sSoc, szBuf, SOCKET_BUFFER_SIZE, 0);
		
		if (len == 0)
		{
			//qDebug() << "CClientSocket Recv thread :: Recv Empty";
			break;
		}
		else if (len != SOCKET_ERROR)
		{
			//qDebug() << "CClientSocket Recv thread :: Recv OK, size =" << len;
			pSoc->AddReceivedData(szBuf, len);
		}
		else
		{
			err = WSAGetLastError();
			if (err == WSAENOTCONN || err == WSAECONNRESET)	// 10057, 10054
			{
				//qDebug() << "CClientSocket Recv thread :: Socket Disconnect";
				break;
			}
		}
		Sleep(50);
	}

	SetEvent(pSoc->GetEndEventHandle());

	//qDebug() << "CClientSocket Recv thread :: Thread End";

	return 1;
}

CClientSocket::CClientSocket()
{
	ZeroMemory(&m_serverIP, sizeof(m_serverIP));
	m_hEventEnd = CreateEvent(NULL, TRUE, FALSE, NULL);
}

CClientSocket::~CClientSocket()
{
	m_bConnected = false;
	m_hSocket = NULL;

	if(m_hEventEnd != NULL)
		CloseHandle(m_hEventEnd);
}

bool CClientSocket::Connect(std::string server, unsigned short sPort)
{
	strcpy_s(m_serverIP, SERVER_NAME_SIZE, server.c_str());
	m_sPort = sPort;
	
	if (strcmp(m_serverIP, "") == 0 || m_sPort == 0)
	{
		MessageBoxA(NULL, "Server or Port is not initialized", __FUNCTION__, MB_OK | MB_ICONSTOP);
		return false;
	}

	WSADATA wsaData;
	SOCKADDR_IN servAddr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		MessageBoxA(NULL, "WSAStartup call failed", __FUNCTION__, MB_OK | MB_ICONSTOP);
		return false;
	}

	m_hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (m_hSocket == INVALID_SOCKET)
	{
		MessageBoxA(NULL, "socket create failed", __FUNCTION__, MB_OK | MB_ICONSTOP);
		return false;
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;

	InetPtonA(AF_INET, m_serverIP, &servAddr.sin_addr.s_addr);
	servAddr.sin_port = htons(m_sPort);

	if (connect(m_hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		if (m_hSocket != NULL)
			closesocket(m_hSocket);

		m_hSocket = NULL;
		m_hThread = NULL;

		//MessageBoxA(NULL, "socket connect failed", __FUNCTION__, MB_OK | MB_ICONSTOP);
		return false;
	}

	m_hThread = CreateThread(NULL, NULL, ClientSocket_RecvThread, this, NULL, &m_ulThreadID);
	if (m_hThread == NULL)
	{
		closesocket(m_hSocket);
		m_hSocket = NULL;
		MessageBoxA(NULL, "Recv thread create failed", __FUNCTION__, MB_OK | MB_ICONSTOP);
		return false;
	}

	m_bConnected = true;
	m_bRecvThreadRun = true;

	return true;
}

void CClientSocket::Close()
{
	m_bRecvThreadRun = false;
		
	if (m_hSocket != NULL)
	{
		closesocket(m_hSocket);
		m_hSocket = NULL;

		if (m_hThread != NULL)
		{
			WaitForSingleObject(m_hThread, INFINITE);
			m_hThread = NULL;
		}

		WSACleanup();
	}
	m_bConnected = false;
}

int CClientSocket::SendToHost(const char *buf, int len, int retryCnt)
{
	m_mutexSocket.lock();
	for(int i = 0; i < retryCnt; i++)
	{
		int nLen = send(m_hSocket, buf, len, 0);
		if (nLen != SOCKET_ERROR)
		{
			m_mutexSocket.unlock();
			return nLen;
		}
	}
	m_mutexSocket.unlock();
	return SOCKET_ERROR;
}

void CClientSocket::AddReceivedData(const char *buf, int len)
{
	if (len <= 0)
		return;

	SocRecvData data;
	::ZeroMemory(&data, sizeof(SocRecvData));
	memcpy_s(data.buf, sizeof(data.buf), buf, len);
	data.size = len;

	m_mutexData.lock();

	m_queRecvData.push_back(data);

	m_mutexData.unlock();
}

int CClientSocket::GetReceiveData(char *buf, int len)
{
	m_mutexData.lock();

	if (m_queRecvData.size() == 0)
	{
		return 0;
	}

	SocRecvData data = m_queRecvData.front();
	m_queRecvData.erase(m_queRecvData.begin());
	m_mutexData.unlock();
	if (data.buf == "" )
	{
		return 0;
	}

	if (data.size>len)
	{
		return 0;
	}

	memcpy_s(buf, len, data.buf, data.size);

	return data.size;
}

bool CClientSocket::IsExistReceiveData()
{
	m_mutexData.lock();
	bool bRet = m_queRecvData.size() > 0 ? true : false;
	m_mutexData.unlock();
	return bRet;
}

void CClientSocket::ClearReceiveData()
{
	m_mutexData.lock();
	m_queRecvData.clear();
	m_mutexData.unlock();
}
