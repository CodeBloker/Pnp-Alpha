#include "TcpController.h"
#include "Common/JClientSocket.h"
#include "JupCore.h"

TcpController::TcpController()
{
	m_socket_ACL = new JClientSocket();
	m_socket_confocal = new JClientSocket();
}

TcpController::~TcpController()
{
	if (m_socket_ACL)
	{
		delete m_socket_ACL;
		m_socket_ACL = nullptr;
	}

	if (m_socket_confocal)
	{
		delete m_socket_confocal;
		m_socket_confocal = nullptr;
	}
}

TcpController *& TcpController::GetInstance()
{
	if (m_SingleInstance == nullptr) {
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (m_SingleInstance == nullptr) {
			m_SingleInstance = new (std::nothrow) TcpController{};
		}
	}
	return m_SingleInstance;
}

bool TcpController::ConnectTcpGetACLValue(double & Tx, double & Ty)
{
	std::string ip = jCore->GlobalSettings().ReadString("TCP", "ACL_IP");
	unsigned short port = jCore->GlobalSettings().ReadInt("TCP", "ACL_Port");
	if (m_socket_ACL->Connect(ip, port))
	{
		Tx = Ty = 0;
		for (int i = 0; i < 3; i++)
		{
			Sleep(100);
			char buf[1024] = { 0 };
			m_socket_ACL->GetReceiveData(buf, sizeof(buf));

			std::string str = buf;
			auto lst = Jup::Split(str, ",");
			if (lst.size() < 5)
			{
				continue;
			}
			if (lst.at(1) == "N")
			{
				continue;
			}
			else
			{
				Ty = stof(lst.at(2));
				Tx = -stof(lst.at(3));
				break;
			}
		}
		m_socket_ACL->Close();
		if (Tx != 0 && Ty != 0)
			return true;
	}
	return false;
}

bool TcpController::ConnectConfocalSensor(std::string ip, unsigned short port)
{
	bool ret = m_socket_confocal->Connect(ip, port);
	return ret;
}

void TcpController::DisConnectConfocalSensor()
{
	m_socket_confocal->Close();
}

bool TcpController::GetConfocalValue(std::string command, double & val)
{
	if (!m_socket_confocal->IsConnected())
	{
		return false;
	}
	// send
	const char* str_buf = command.c_str();
	int ret = m_socket_confocal->SendToHost(str_buf, sizeof(str_buf), 3);
	Sleep(200);
	// recv
	for (int i = 0; i < 5; i++)
	{
		Sleep(100);
		char buf[1024] = { 0 };
		m_socket_confocal->GetReceiveData(buf, sizeof(buf));

		std::string str = buf;
		auto lst = Jup::Split(str, ",");
		if (lst.size() < 2)
		{
			continue;
		}
		if (lst.at(0) != "MS")
		{
			continue;
		}
		else
		{
			val = stof(lst.at(1));
			break;
		}
	}
}

bool TcpController::ConnectAndGetConfocalValue(std::string ip, unsigned short port, std::string command, double & val)
{
	if (m_socket_confocal->Connect(ip, port))
	{
		// send
		const char* str_buf = command.c_str();
		int ret = m_socket_confocal->SendToHost(str_buf, sizeof(str_buf), 3);
		//Sleep(200);
		for (int i = 0; i < 3; i++)
		{
			Sleep(50);
			char buf[1024] = { 0 };
			m_socket_confocal->GetReceiveData(buf, sizeof(buf));

			std::string str = buf;
			auto lst = Jup::Split(str, ",");
			if (lst.size() < 2)
			{
				continue;
			}
			if (lst.at(0) != "MS")
			{
				continue;
			}
			else
			{
				val = stof(lst.at(1));
				break;
			}
		}
		m_socket_confocal->Close();
		if (val != 0)
			return true;
	}
	return false;
}
