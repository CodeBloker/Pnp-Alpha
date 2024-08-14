#include "TcpPluginCaller.h"

#include "JError.h"

#define Plugin_Method_Add(T, f) appendMethod(#f, transformMethod<T>(&T::f));
static JError s_error;

#include "JupCore.h"
#include <Windows.h>

TcpPluginCaller::TcpPluginCaller()
{
	m_tcp = TcpController::GetInstance();
}

TcpPluginCaller::~TcpPluginCaller()
{}

/*
	在该函数做特定的初始化操作，一般由平台调用该函数

	示例：默认调用父类接口的实现JupCaller::Initialize();
	根据当前插件的实际需要选择添加内容
*/
int TcpPluginCaller::Initialize()
{
	return JupCaller::Initialize();
}

/*
	统一在此注册所有测试项方法的函数

	示例：Plugin_Method_Add(TcpPluginCaller, Demo_msleep100);
	其中参数1：TcpPluginCaller为当前类的类名，参数2：Demo_msleep100为需要注册的函数名
*/
int TcpPluginCaller::RegisterMethod()
{
	Plugin_Method_Add(TcpPluginCaller, Demo_msleep100);
	Plugin_Method_Add(TcpPluginCaller, GetACLValues);
	Plugin_Method_Add(TcpPluginCaller, GetConfocalSensorValue1);
	Plugin_Method_Add(TcpPluginCaller, GetConfocalSensorValue2);

	return 0;
}

/*
	示例：
	如函数Demo_msleep100，内容自行添加；返回值为0表示没有错误，返回值非0表示有错误

	错误码的使用：
	1.在本cpp文件包含头文件：#include "ErrorCode.h"
	2.在函数中返回错误码：return ErrorCode::ERR_Init;

	如果想直接得到错误名以及错误提示（在函数Demo_msleep500Error中有范例）
	1.在本cpp文件定义静态变量：static ErrorCode s_error;
	2.在函数中使用下列方法
	获得错误名：			s_error.GetNameByCode(ErrorCode::ERR_Init);
	获得中文错误提示：	s_error.GetPromptByCode(ErrorCode::ERR_Init, JUP_ERROR_PROMPT_CN);
	获得英文错误提示：	s_error.GetPromptByCode(ErrorCode::ERR_Init, JUP_ERROR_PROMPT_EN);
*/
int TcpPluginCaller::Demo_msleep100(JupData & data)
{
	Sleep(100);
	return 0;
}

int TcpPluginCaller::GetACLValues(JupData & data)
{
	double Tx;
	double Ty;
	bool nRet = m_tcp->ConnectTcpGetACLValue(Tx, Ty);
	if (nRet)
	{
		// 记录俯仰值Tx,Ty

		return 0;
	}
	return -1;
}

int TcpPluginCaller::GetConfocalSensorValue1(JupData & data)
{
	std::string ip = jCore->GlobalSettings().ReadString("TcpPlugin", "ConfocalSensor1_IP");
	unsigned short port = jCore->GlobalSettings().ReadInt("TcpPlugin", "ConfocalSensor1_PORT"); 
	std::string command = "MS,0,1\r";
	double value;
	if (!m_tcp->ConnectAndGetConfocalValue(ip, port, command, value))
	{
		data.SetValue("ConfocalSensor", "Heigh1", "-99.99");
		return -1;
	}
	data.SetValue("ConfocalSensor", "Heigh1", std::to_string(value));
	return 0;
}

int TcpPluginCaller::GetConfocalSensorValue2(JupData & data)
{
	std::string ip = jCore->GlobalSettings().ReadString("TcpPlugin", "ConfocalSensor2_IP");
	unsigned short port = jCore->GlobalSettings().ReadInt("TcpPlugin", "ConfocalSensor2_PORT");
	std::string command = "MS,0,1\r";
	double value;
	if (!m_tcp->ConnectAndGetConfocalValue(ip, port, command, value))
	{
		data.SetValue("ConfocalSensor", "Heigh2", "-99.99");
		return -1;
	}
	data.SetValue("ConfocalSensor", "Heigh2", std::to_string(value));
	return 0;
}
