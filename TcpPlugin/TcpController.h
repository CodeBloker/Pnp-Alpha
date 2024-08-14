#pragma once
#include <mutex>
class JClientSocket;

class TcpController
{
public:
	TcpController();
	~TcpController();

	// 获取单实例
	static TcpController*& GetInstance();

	//********************外部设备功能**********************//
	//ACL
	//获取ACL俯仰值
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

