#include "DUTCaller.h"

#include "JError.h"
#include <Windows.h>
#include "ParasDefine.h"

#define Plugin_Method_Add(T, f) appendMethod(#f, transformMethod<T>(&T::f));
static JError s_error;

DUTCaller::DUTCaller()
{
	m_dut = DutController::GetInstance();
}

DUTCaller::~DUTCaller()
{}

/*
	在该函数做特定的初始化操作，一般由平台调用该函数

	示例：默认调用父类接口的实现JupCaller::Initialize();
	根据当前插件的实际需要选择添加内容
*/
int DUTCaller::Initialize()
{
	return JupCaller::Initialize();
}

/*
	统一在此注册所有测试项方法的函数

	示例：Plugin_Method_Add(DUTCaller, Demo_msleep100);
	其中参数1：DUTCaller为当前类的类名，参数2：Demo_msleep100为需要注册的函数名
*/
int DUTCaller::RegisterMethod()
{
	Plugin_Method_Add(DUTCaller, Demo_msleep100);
	Plugin_Method_Add(DUTCaller, InitCanyon);
	Plugin_Method_Add(DUTCaller, DutPowerOn);
	Plugin_Method_Add(DUTCaller, DutPowerOff);
	Plugin_Method_Add(DUTCaller, DutSetDotPara);
	Plugin_Method_Add(DUTCaller, DutSetFloodPara);

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
int DUTCaller::Demo_msleep100(JupData & data)
{
	Sleep(100);
	return 0;
}

int DUTCaller::InitCanyon(JupData & data)
{
	return m_dut->fnCanyouInit(m_socketIndex) ? 0 : -1;
}

int DUTCaller::DutPowerOn(JupData & data)
{
	return m_dut->fnCanyouPowerOnTriggerMode(m_socketIndex, TXRegFile_INI, RXRegFile_INI) ? 0 : -1;
}

int DUTCaller::DutPowerOff(JupData & data)
{
	return m_dut->fnCanyouPowerOff(m_socketIndex, "ManuelPowerOff") ? 0 : -1;
}

int DUTCaller::DutSetDotPara(JupData & data)
{
	const char* strAddr = "0x60";
	const char* strData = "0x00";

	unsigned char uAddr = static_cast<unsigned short>(std::strtoul(strAddr, NULL, 16));
	unsigned char uData = static_cast<unsigned short>(std::strtoul(strData, NULL, 16));
	bool ret = m_dut->fnWriteI2CData(m_socketIndex, BANFF_TX_SLAVE_ADDRESS, uAddr, 1, &uData);
	if (ret)
	{
		unsigned char pData;
		ret = m_dut->fnReadI2CData(m_socketIndex, BANFF_TX_SLAVE_ADDRESS, uAddr, 1, &pData);
		if (ret)
		{
			char hex_str[32];
			sprintf(hex_str, "0x%02X", pData);
			if (std::string(hex_str) == strData)
			{
				return 0;
			}
		}
	}
	return -1;
}

int DUTCaller::DutSetFloodPara(JupData & data)
{
	const char* strAddr = "0x60";
	const char* strData = "0x01";

	unsigned char uAddr = static_cast<unsigned short>(std::strtoul(strAddr, NULL, 16));
	unsigned char uData = static_cast<unsigned short>(std::strtoul(strData, NULL, 16));
	bool ret = m_dut->fnWriteI2CData(m_socketIndex, BANFF_TX_SLAVE_ADDRESS, uAddr, 1, &uData);
	if (ret)
	{
		unsigned char pData;
		ret = m_dut->fnReadI2CData(m_socketIndex, BANFF_TX_SLAVE_ADDRESS, uAddr, 1, &pData);
		if (ret)
		{
			char hex_str[32];
			sprintf(hex_str, "0x%02X", pData);
			if (std::string(hex_str) == strData)
			{
				return 0;
			}
		}
	}
	return -1;
}

