#include "JClientSocket.h"
#include <Ws2tcpip.h>
#include <iostream>

//接受数据线程
ULONG WINAPI ClientSocket_RecvThread(void *pParam)
{
	JClientSocket *pSoc = (JClientSocket*)pParam;

	char szBuf[SOCKET_BUFFER_SIZE];
	int len, err;
	SOCKET sSoc;

	std::cout << "JClientSocket Recv thread :: Thread Start" << std::endl;

	ResetEvent(pSoc->GetEndEventHandle());

	while (pSoc->GetRecvThreadRun())
	{
		sSoc = pSoc->GetSocket();
		if (sSoc == NULL)
			break;

		len = recv(sSoc, szBuf, SOCKET_BUFFER_SIZE, 0);

		if (len == 0)
		{
			std::cout << "JClientSocket Recv thread :: Recv Empty" << std::endl;
			break;
		}
		else if (len != SOCKET_ERROR)
		{
			std::cout << "JClientSocket Recv thread :: Recv OK, size =" << len << std::endl;
			pSoc->AddReceivedData(szBuf, len);
		}
		else
		{
			err = WSAGetLastError();
			if (err == WSAENOTCONN || err == WSAECONNRESET)	// 10057, 10054
			{
				std::cout << "JClientSocket Recv thread :: Socket Disconnect" << std::endl;
				break;
			}
		}
		Sleep(50);
	}

	SetEvent(pSoc->GetEndEventHandle());

	std::cout << "JClientSocket Recv thread :: Thread End" << std::endl;

	return 1;
}

JClientSocket::JClientSocket()
{
	ZeroMemory(&m_serverIP, sizeof(m_serverIP));
	m_hEventEnd = CreateEvent(NULL, TRUE, FALSE, NULL);
}

JClientSocket::~JClientSocket()
{
	m_bConnected = false;
	m_hSocket = NULL;

	if (m_hEventEnd != NULL)
		CloseHandle(m_hEventEnd);
}

bool JClientSocket::Connect(std::string server, USHORT sPort)
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

void JClientSocket::Close()
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
	}
	m_bConnected = false;

	WSACleanup();
}

int JClientSocket::SendToHost(const char *buf, int len, int retryCnt)
{
	std::lock_guard lock(m_socketMutex);

	for (int i = 0; i < retryCnt; i++)
	{
		int nLen = send(m_hSocket, buf, len, 0);
		if (nLen != SOCKET_ERROR)
		{
			return nLen;
		}
	}
	return SOCKET_ERROR;
}

void JClientSocket::AddReceivedData(const char *buf, int len)
{
	if (len <= 0)
		return;

	SocRecvData data;
	::ZeroMemory(&data, sizeof(SocRecvData));
	memcpy_s(data.buf, sizeof(data.buf), buf, len);
	data.size = len;

	std::lock_guard lock(m_dataMutex);

	m_queRecvData.push(data);
}

int JClientSocket::GetReceiveData(char *buf, int len)
{
	std::lock_guard lock(m_dataMutex);

	if (m_queRecvData.empty())
	{
		return 0;
	}

	SocRecvData data = m_queRecvData.front();
	m_queRecvData.pop();

	if (data.buf == "")
	{
		return 0;
	}

	if (data.size > len)
	{
		return 0;
	}

	memcpy_s(buf, len, data.buf, data.size);

	return data.size;
}

bool JClientSocket::IsExistReceiveData()
{
	std::lock_guard lock(m_dataMutex);

	return !m_queRecvData.empty();
}

void JClientSocket::ClearReceiveData()
{
	std::lock_guard lock(m_dataMutex);

	std::queue<SocRecvData>().swap(m_queRecvData);
}
