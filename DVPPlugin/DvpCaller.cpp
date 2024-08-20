#include "DvpCaller.h"
#include "JError.h"
#include <Windows.h>
#include "JupCore.h"
#include <filesystem>
#include <random>
#include "../_INCLUDE/ProjectEvent.h"
using namespace ProjectEvent;
#define Plugin_Method_Add(T, f) appendMethod(#f, transformMethod<T>(&T::f));
static JError s_error;

std::future<int> m_top_future;
std::future<int> m_bottom_future;

double getRandomDouble(double min, double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

DvpCaller::DvpCaller()
{
	m_pCamera = DvpCamera_Manage::GetInstance();
}

DvpCaller::~DvpCaller()
{}

/*
	在该函数做特定的初始化操作，一般由平台调用该函数

	示例：默认调用父类接口的实现JupCaller::Initialize();
	根据当前插件的实际需要选择添加内容
*/
int DvpCaller::Initialize()
{
	return JupCaller::Initialize();
}

/*
	统一在此注册所有测试项方法的函数

	示例：Plugin_Method_Add(HIKCaller, Demo_msleep100);
	其中参数1：HIKCaller为当前类的类名，参数2：Demo_msleep100为需要注册的函数名
*/
int DvpCaller::RegisterMethod()
{
	Plugin_Method_Add(DvpCaller, Demo_msleep100);
	Plugin_Method_Add(DvpCaller, LoadPnpDoeResetDatas);
	Plugin_Method_Add(DvpCaller, SetTopCameraHwParameter);
	Plugin_Method_Add(DvpCaller, SetDownCameraHwParameter);
	Plugin_Method_Add(DvpCaller, StartCaptureTopImageThread);
	Plugin_Method_Add(DvpCaller, StartCaptureBottomImageThread);

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
int DvpCaller::Demo_msleep100(JupData & data)
{
	Sleep(10);

	//qDebug() << this->objectName() << this->metaObject()->className() << __FUNCTION__;
	return 0;
}

int DvpCaller::LoadPnpDoeResetDatas(JupData & data)
{
	// 先关闭采集
	m_pCamera->StopGrabbing(cameraTop_serial);
	m_pCamera->StopGrabbing(cameraBottom_serial);

	Sleep(300);

	return 0;
}

int DvpCaller::SetTopCameraHwParameter(JupData & data)
{
	std::string strErrorMsg;
	int nRet = m_pCamera->OpenDevice(cameraTop_serial, strErrorMsg);
	if (nRet != 0)
	{
		return -1;
	}
	// 修改触发源
	if (!m_pCamera->SetTriggerSource(cameraTop_serial, TRIGGER_SOURCE_SOFTWARE))
	{
		return -2;
	}
	// 修改触发模式
	if (!m_pCamera->SetTriggerMode(cameraTop_serial, true))
	{
		return -3;
	}
	// 设置曝光等参数
	if (!m_pCamera->SetAutoExposure(cameraTop_serial, AE_OP_OFF))
	{
		return -4;
	}

	// 开启上相机采集
	nRet = m_pCamera->StartGrabbing(cameraTop_serial);
	if (nRet != 0)
	{
		return -5;
	}

	return 0;
}

int DvpCaller::SetDownCameraHwParameter(JupData & data)
{
	std::string strErrorMsg;
	int nRet = m_pCamera->OpenDevice(cameraBottom_serial, strErrorMsg);
	if (nRet != 0)
	{
		return -1;
	}
	// 修改触发源
	if (!m_pCamera->SetTriggerSource(cameraBottom_serial, TRIGGER_SOURCE_LINE1))
	{
		return -2;
	}
	// 修改触发模式
	if (!m_pCamera->SetTriggerMode(cameraBottom_serial, true))
	{
		return -3;
	}
	// 设置曝光等参数
	if (!m_pCamera->SetAutoExposure(cameraBottom_serial, AE_OP_OFF))
	{
		return -4;
	}

	// 获取曝光时间
	double pExposure = 0;
	if (!m_pCamera->GetExposure(cameraBottom_serial, &pExposure))
	{
		return -7;
	}

	// 设置固定曝光参数
	int exposureTime = jCore->GlobalSettings().ReadInt("PnpDoe", "BottomCameraExTime");
	if (!m_pCamera->SetExposure(cameraBottom_serial, exposureTime))
	{
		return -6;
	}

	// 开启下相机采集
	nRet = m_pCamera->StartGrabbing(cameraBottom_serial);
	if (nRet != 0)
	{
		return -5;
	}

	return 0;
}

int DvpCaller::StartCaptureTopImageThread(JupData & data)
{
	// 保存图片
	std::string strStartTime_1, strStartTime_3, strErrorMsg;
	strStartTime_1 = data.GetValue("MotionData", "StartTime_1");
	strStartTime_3 = data.GetValue("MotionData", "StartTime_3");
	std::string imagePath = IMAGE_PATH_DEFAULT;
	std::string file_name = imagePath + strStartTime_1 + "/";
	if (!std::filesystem::exists(file_name))
	{
		std::filesystem::create_directory(file_name);
	}
	file_name += "temp/";
	if (!std::filesystem::exists(file_name))
	{
		std::filesystem::create_directory(file_name);
	}
	bool takeOrLay = data.GetInt("MotionData", "TakeUpOrLayDown");
	if (takeOrLay)
	{
		std::string takeUpDutPath = data.GetValue("MotionData", "TakeDutImagePath");
		file_name += cameraTop_serial + "_" + strStartTime_3 + "_" + takeUpDutPath + "_dvp.bmp";
	}
	else
	{
		std::string takeUpDutPath = data.GetValue("MotionData", "TakeDutImagePath");
		file_name += cameraTop_serial + "_" + strStartTime_3 + "_" + takeUpDutPath + "_dvp.bmp";
	}
	
	
	// 软触发一次拍照
	int nRet = m_pCamera->TakePhoto(cameraTop_serial, file_name, strErrorMsg);
	if (nRet != 0)
	{
		// 软触发失败
		return -1;
	}

	// 计算结果
	jCore->SendEvent(ProjectEvent::g_DvpWidget, &ProjectEvent::JDvpPnpCalibrationEvent(getRandomDouble(10,50), getRandomDouble(10, 50), getRandomDouble(10, 50), getRandomDouble(10, 50), file_name));
	data.SetValue("ImageData", "TopImageFile", file_name);

	return 0;
}

int DvpCaller::StartCaptureBottomImageThread(JupData & data)
{
	int exposureTime = jCore->GlobalSettings().ReadInt("PnpDoe", "DelayTime_TakePicture");
	Sleep(exposureTime);

	// 保存图片
	std::string strStartTime_1, strStartTime_3, strErrorMsg;
	strStartTime_1 = data.GetValue("MotionData", "StartTime_1");
	strStartTime_3 = data.GetValue("MotionData", "StartTime_3");
	std::string imagePath = IMAGE_PATH_DEFAULT;
	std::string file_name = imagePath + strStartTime_1 + "/";
	if (!std::filesystem::exists(file_name))
	{
		std::filesystem::create_directory(file_name);
	}
	file_name += "temp/";
	if (!std::filesystem::exists(file_name))
	{
		std::filesystem::create_directory(file_name);
	}
	file_name += cameraBottom_serial + "_" + strStartTime_3 + ".bmp";

	int nRet = m_pCamera->TakePhoto(cameraBottom_serial, file_name, strErrorMsg, false);
	if (nRet != 0)
	{
		// 软触发失败
		return -1;
	}

	// 计算结果
	data.SetValue("ImageData", "BottomImageFile", file_name);

	return 0;
}
