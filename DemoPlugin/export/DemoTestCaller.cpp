#include "DemoTestCaller.h"

#include "JError.h"

#define Plugin_Method_Add(T, f) appendMethod(#f, transformMethod<T>(&T::f));
static JError s_error;

#include "JupCore.h"
#include <Windows.h>

DemoTestCaller::DemoTestCaller()
{
}

DemoTestCaller::~DemoTestCaller()
{}

/*
	在该函数做特定的初始化操作，一般由平台调用该函数

	示例：默认调用父类接口的实现JupCaller::Initialize();
	根据当前插件的实际需要选择添加内容
*/
int DemoTestCaller::Initialize()
{
	return JupCaller::Initialize();
}

/*
	统一在此注册所有测试项方法的函数

	示例：Plugin_Method_Add(DemoTestCaller, Demo_msleep100);
	其中参数1：DemoTestCaller为当前类的类名，参数2：Demo_msleep100为需要注册的函数名
*/
int DemoTestCaller::RegisterMethod()
{
	Plugin_Method_Add(DemoTestCaller, Demo_msleep100);
	Plugin_Method_Add(DemoTestCaller, Demo_msleep500Error);
	Plugin_Method_Add(DemoTestCaller, Demo_msleep1000);
	Plugin_Method_Add(DemoTestCaller, Demo_select);
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
int DemoTestCaller::Demo_msleep100(JupData & data)
{
	Sleep(100);

	//qDebug() << this->objectName() << this->metaObject()->className() << __FUNCTION__;
	return 0;
}

int DemoTestCaller::Demo_msleep500Error(JupData & data)
{
	Sleep(500);

	//qDebug() << __FUNCTION__
	//	<< (int)ErrorCode::ERR_Init												//错误码
	//	<< s_error.GetNameByCode(ErrorCode::ERR_Init)							//错误名
	//	<< s_error.GetPromptByCode(ErrorCode::ERR_Init, JUP_ERROR_PROMPT_CN)	//中文错误提示
	//	<< s_error.GetPromptByCode(ErrorCode::ERR_Init, JUP_ERROR_PROMPT_EN);	//英文错误提示

	return JError::ERR_Init;
}

int DemoTestCaller::Demo_msleep1000(JupData & data)
{
	Sleep(1000);

	jCore->Logger("DemoPlugin.dll").LogInfo(__FUNCTION__, "sleep 1s...");

	return 0;
}

int DemoTestCaller::Demo_select(JupData & data)
{
	static int i = 0;
	if (i < 2)
	{
		i++;
		return -10086;
	}
	else
	{
		i = 0;
		return 0;
	}
}
