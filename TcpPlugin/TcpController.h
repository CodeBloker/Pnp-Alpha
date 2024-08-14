#pragma once
#include <mutex>
class JClientSocket;

class TcpController
{
public:
	TcpController();
	~TcpController();

	// ��ȡ��ʵ��
	static TcpController*& GetInstance();

	//********************�ⲿ�豸����**********************//
	//ACL
	//��ȡACL����ֵ
	bool ConnectTcpGetACLValue(double& Tx, double& Ty);

	//Confocal Sensor
	bool ConnectConfocalSensor(std::string ip, unsigned short port);
	void DisConnectConfocalSensor();
	bool GetConfocalValue(std::string command, double& val);
	bool ConnectAndGetConfocalValue(std::string ip, unsigned short port, std::string command, double& val);

private:
	JClientSocket* m_socket_ACL;
	JClientSocket* m_socket_confocal;

	inline static TcpController* m_SingleInstance = nullptr;
	inline static std::mutex m_Mutex;
};

