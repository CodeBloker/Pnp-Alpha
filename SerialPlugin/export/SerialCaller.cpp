#include "SerialCaller.h"

#include "JError.h"

#define Plugin_Method_Add(T, f) appendMethod(#f, transformMethod<T>(&T::f));
static JError s_error;

#include "JupCore.h"
#include <Windows.h>

SerialCaller::SerialCaller()
{
	m_Serial = SerialControl::GetInstance();
}

SerialCaller::~SerialCaller()
{}

/*
	在该函数做特定的初始化操作，一般由平台调用该函数

	示例：默认调用父类接口的实现JupCaller::Initialize();
	根据当前插件的实际需要选择添加内容
*/
int SerialCaller::Initialize()
{
	return JupCaller::Initialize();
}

/*
	统一在此注册所有测试项方法的函数

	示例：Plugin_Method_Add(SerialCaller, Demo_msleep100);
	其中参数1：SerialCaller为当前类的类名，参数2：Demo_msleep100为需要注册的函数名
*/
int SerialCaller::RegisterMethod()
{
	Plugin_Method_Add(SerialCaller, Demo_msleep100);
	Plugin_Method_Add(SerialCaller, OpenAlphaLightSource);
	Plugin_Method_Add(SerialCaller, CloseAlphaLightSource);
	Plugin_Method_Add(SerialCaller, OpenAllAlphaLightSource);
	Plugin_Method_Add(SerialCaller, CloseAllAlphaLightSource);
	Plugin_Method_Add(SerialCaller, OpenSensorTemperature);
	Plugin_Method_Add(SerialCaller, CloseSensorTemperature);
	Plugin_Method_Add(SerialCaller, GetSensorTemperature);
	Plugin_Method_Add(SerialCaller, OpenSensorHeigh);
	Plugin_Method_Add(SerialCaller, CloseSensorHeigh);
	Plugin_Method_Add(SerialCaller, GetOmronSensor1HeighValue);
	Plugin_Method_Add(SerialCaller, GetOmronSensor2HeighValue);
	Plugin_Method_Add(SerialCaller, GetOmronSensor3HeighValue);
	Plugin_Method_Add(SerialCaller, GetKeyenceSensorHeighValue);

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
int SerialCaller::Demo_msleep100(JupData & data)
{
	Sleep(1);
	return 0;
}

int SerialCaller::OpenAlphaLightSource(JupData & data)
{
	return 0;
	if (m_Serial->IsLightSourceOpen())
	{
		return 0;
	}
	return  m_Serial->OpenLightSource() ? 0 : -1;
}

int SerialCaller::CloseAlphaLightSource(JupData & data)
{
	if (!m_Serial->IsLightSourceOpen())
	{
		return 0;
	}
	return m_Serial->CloseLightSource() ? 0 : -1;
}

int SerialCaller::OpenAllAlphaLightSource(JupData & data)
{
	return 0;
	return m_Serial->OpenAllLight() ? 0 : -1;
}

int SerialCaller::CloseAllAlphaLightSource(JupData & data)
{
	return m_Serial->CloseAllLight() ? 0 : -1;
}

int SerialCaller::OpenSensorTemperature(JupData & data)
{
	if (m_Serial->IsTempSensorOpen())
	{
		return 0;
	}
	return m_Serial->OpenTempSensor() ? 0 : -1;
}

int SerialCaller::CloseSensorTemperature(JupData & data)
{
	if (!m_Serial->IsTempSensorOpen())
	{
		return 0;
	}
	return m_Serial->CloseTempSensor() ? 0 : -1;
}

int SerialCaller::GetSensorTemperature(JupData & data)
{
	std::string temp1 = m_Serial->ReadTemp();
	data.SetValue("Serial", "CurrentTemp1", temp1.c_str());
	std::string temp2 = m_Serial->ReadTemp2();
	data.SetValue("Serial", "CurrentTemp2", temp2.c_str());
	return (temp1.empty() || temp2.empty()) ? -1 : 0;
}

int SerialCaller::OpenSensorHeigh(JupData & data)
{
	if (m_Serial->IsHeighSensorOpen())
	{
		return 0;
	}
	return m_Serial->OpenHeighSensor1() ? 0 : -1;
}

int SerialCaller::CloseSensorHeigh(JupData & data)
{
	if (!m_Serial->IsHeighSensorOpen())
	{
		return 0;
	}
	return m_Serial->CloseHeighSensor1() ? 0 : -1;
}

int SerialCaller::GetOmronSensor1HeighValue(JupData & data)
{
	Sleep(1000);
	std::string heigh = m_Serial->ReadHeigh1();
	data.SetValue("Serial", "OmronHeigh1", heigh.c_str());
	return heigh.empty() ? -1 : 0;
}

int SerialCaller::GetOmronSensor2HeighValue(JupData & data)
{
	std::string heigh = m_Serial->ReadHeigh2();
	data.SetValue("Serial", "OmronHeigh2", heigh.c_str());
	return heigh.empty() ? -1 : 0;
}

int SerialCaller::GetOmronSensor3HeighValue(JupData & data)
{
	std::string heigh = m_Serial->ReadHeigh3();
	data.SetValue("Serial", "OmronHeigh3", heigh.c_str());
	return heigh.empty() ? -1 : 0;
}

int SerialCaller::GetKeyenceSensorHeighValue(JupData & data)
{
	std::string heigh = m_Serial->ReadKeyenceHeigh();
	data.SetValue("Serial", "KeyenceHeigh", heigh.c_str());
	return heigh.empty() ? -1 : 0;
}
