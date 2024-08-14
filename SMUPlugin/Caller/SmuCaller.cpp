#include "SmuCaller.h"
#include "JupCore.h"

#include "JError.h"
#include <Windows.h>

#define Plugin_Method_Add(T, f) appendMethod(#f, transformMethod<T>(&T::f));
static JError s_error;

SmuCaller::SmuCaller()
{
	m_pSmu = SmuControl::GetInstance();
}

SmuCaller::~SmuCaller()
{
}

/*
	在该函数做特定的初始化操作，一般由平台调用该函数

	示例：默认调用父类接口的实现JupCaller::Initialize();
	根据当前插件的实际需要选择添加内容
*/
int SmuCaller::Initialize()
{
	return JupCaller::Initialize();
}

/*
	统一在此注册所有测试项方法的函数

	示例：Plugin_Method_Add(SmuCaller, Demo_msleep100);
	其中参数1：SmuCaller为当前类的类名，参数2：Demo_msleep100为需要注册的函数名
*/
int SmuCaller::RegisterMethod()
{
	Plugin_Method_Add(SmuCaller, Demo_msleep100);
	Plugin_Method_Add(SmuCaller, SmuConnect);
	Plugin_Method_Add(SmuCaller, SmuDisConnect);
	Plugin_Method_Add(SmuCaller, ExecuteCommandDOT);
	Plugin_Method_Add(SmuCaller, ExecuteCommandFlood);
	Plugin_Method_Add(SmuCaller, ExecuteCommandDark);

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
int SmuCaller::Demo_msleep100(JupData & data)
{
	Sleep(100);

	//qDebug() << this->objectName() << this->metaObject()->className() << __FUNCTION__;
	return 0;
}

int SmuCaller::SmuConnect(JupData & resultTable)
{
	if (m_pSmu->smuIsConnected())
	{
		return 0;
	}
	bool ret = m_pSmu->fnSMUDevImpl();
	return ret ? 0 : -1;
}

int SmuCaller::SmuDisConnect(JupData & resultTable)
{
	bool ret = m_pSmu->fnSMUDevDestory();
	return ret ? 0 : -1;
}

int SmuCaller::ExecuteCommandDOT(JupData & resultTable)
{
	std::string smu_num = jCore->GlobalSettings().ReadString("SMU", "SmuNum");
	std::string dot_command = jCore->GlobalSettings().ReadString("SMU", "Dot_Script");
	bool ret = m_pSmu->ExecuteCommand(false, smu_num, dot_command.c_str());
	return ret ? 0 : -1;
}

int SmuCaller::ExecuteCommandFlood(JupData & resultTable)
{
	std::string smu_num = jCore->GlobalSettings().ReadString("SMU", "SmuNum");
	std::string flood_command = jCore->GlobalSettings().ReadString("SMU", "Flood_Script");
	bool ret = m_pSmu->ExecuteCommand(false, smu_num, flood_command.c_str());
	return ret ? 0 : -1;
}

int SmuCaller::ExecuteCommandDark(JupData & resultTable)
{
	std::string smu_num = jCore->GlobalSettings().ReadString("SMU", "SmuNum");
	std::string dark_command = jCore->GlobalSettings().ReadString("SMU", "Dark_Script");
	bool ret = m_pSmu->ExecuteCommand(false, smu_num, dark_command.c_str());
	return ret ? 0 : -1;
}
