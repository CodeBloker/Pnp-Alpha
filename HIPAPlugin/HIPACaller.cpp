#include "HIPACaller.h"
#include "JError.h"
#include <Windows.h>
#include "JupCore.h"

#define Plugin_Method_Add(T, f) appendMethod(#f, transformMethod<T>(&T::f));
static JError s_error;

std::future<int> m_top_future;
std::future<int> m_bottom_future;

HIPACaller::HIPACaller()
{
	m_pCamera = HIPACamera::GetInstance();
}

HIPACaller::~HIPACaller()
{}

/*
	在该函数做特定的初始化操作，一般由平台调用该函数

	示例：默认调用父类接口的实现JupCaller::Initialize();
	根据当前插件的实际需要选择添加内容
*/
int HIPACaller::Initialize()
{
	return JupCaller::Initialize();
}

/*
	统一在此注册所有测试项方法的函数

	示例：Plugin_Method_Add(HIPACaller, Demo_msleep100);
	其中参数1：HIPACaller为当前类的类名，参数2：Demo_msleep100为需要注册的函数名
*/
int HIPACaller::RegisterMethod()
{
	Plugin_Method_Add(HIPACaller, Demo_msleep100);
	Plugin_Method_Add(HIPACaller, SetTxCameraParameter);
	Plugin_Method_Add(HIPACaller, SetTyCameraParameter);
	Plugin_Method_Add(HIPACaller, GetCameraImage1);
	Plugin_Method_Add(HIPACaller, GetCameraImage2);
	Plugin_Method_Add(HIPACaller, LoadPnpDoeResetDatas);
	Plugin_Method_Add(HIPACaller, SetTopCameraHwParameter);
	Plugin_Method_Add(HIPACaller, SetDownCameraHwParameter);
	Plugin_Method_Add(HIPACaller, StartCaptureTopImageThread);
	Plugin_Method_Add(HIPACaller, StartCaptureBottomImageThread);
	Plugin_Method_Add(HIPACaller, SaveTopImageAndCalculate);
	Plugin_Method_Add(HIPACaller, SaveBottomImageAndCalculate);

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
int HIPACaller::Demo_msleep100(JupData & data)
{
	Sleep(10);

	//qDebug() << this->objectName() << this->metaObject()->className() << __FUNCTION__;
	return 0;
}

int HIPACaller::SetTxCameraParameter(JupData & data)
{
	if (m_pCamera->IsDiviceOpen(cameraTx_serial))
	{
		return 0;
	}
	// 打开设备
	int nRet = m_pCamera->OpenDevice(cameraTx_serial);
	if (nRet != MV_OK)
	{
		return -1;
	}
	// 修改触发源(上相机软件触发拍照)
	nRet = m_pCamera->SetTriggerSource(cameraTx_serial, false);
	if (nRet != MV_OK)
	{
		return -2;
	}
	// 修改触发模式
	nRet = m_pCamera->SetTriggerMode(cameraTx_serial, false);
	if (nRet != MV_OK)
	{
		return -3;
	}
	// 设置曝光等参数
	int exposureTime = jCore->GlobalSettings().ReadInt("CameraParas", "TxCameraExTime");
	nRet = m_pCamera->SetExposureTime(cameraTx_serial, exposureTime);
	if (nRet != MV_OK)
	{
		return -4;
	}
	// 开启上相机采集
	nRet = m_pCamera->StartGrabbing(cameraTx_serial, true);
	if (nRet != MV_OK)
	{
		return -5;
	}
	return 0;
}

int HIPACaller::SetTyCameraParameter(JupData & data)
{
	if (m_pCamera->IsDiviceOpen(cameraTy_serial))
	{
		return 0;
	}
	// 打开设备
	int nRet = m_pCamera->OpenDevice(cameraTy_serial);
	if (nRet != MV_OK)
	{
		return -1;
	}
	// 修改触发源(上相机软件触发拍照)
	nRet = m_pCamera->SetTriggerSource(cameraTy_serial, false);
	if (nRet != MV_OK)
	{
		return -2;
	}
	// 修改触发模式
	nRet = m_pCamera->SetTriggerMode(cameraTy_serial, false);
	if (nRet != MV_OK)
	{
		return -3;
	}
	// 设置曝光等参数
	int exposureTime = jCore->GlobalSettings().ReadInt("CameraParas", "TyCameraExTime");
	nRet = m_pCamera->SetExposureTime(cameraTy_serial, exposureTime);
	if (nRet != MV_OK)
	{
		return -4;
	}
	// 开启上相机采集
	nRet = m_pCamera->StartGrabbing(cameraTy_serial, true);
	if (nRet != MV_OK)
	{
		return -5;
	}
	return 0;
}

int HIPACaller::GetCameraImage1(JupData & data)
{
	std::string imagePath = data.GetValue("HikData", "ImagePath");
	std::string posName = data.GetValue("HikData", "PosName");

	std::string file_name;
	if (data.GetInt("HikData", "SaveImage"))
	{
		file_name = imagePath + "/" + posName + "_" + cameraTx_serial + "_" + Jup::GetLocalTime(3);
	}
	else
	{
		file_name = imagePath + "/" + posName + "_" + cameraTx_serial + "_Temp_" + Jup::GetLocalTime(3);
	}
	int ret = m_pCamera->SetSaveImageType(cameraTx_serial, file_name);
	if (ret != MV_OK)
	{
		// error
		//return -1;
	}
	data.SetValue("HikData", "ImageFile", file_name + ".bmp");
	data.SetValue("HikData", "CurrentCamera", "TX");
	return 0;
}

int HIPACaller::GetCameraImage2(JupData & data)
{
	std::string imagePath = data.GetValue("HikData", "ImagePath");
	std::string posName = data.GetValue("HikData", "PosName");

	std::string file_name;
	if (data.GetInt("HikData", "SaveImage"))
	{
		file_name = imagePath + "/" + posName + "_" + cameraTy_serial + "_" + Jup::GetLocalTime(3);
	}
	else
	{
		file_name = imagePath + "/" + posName + "_" + cameraTy_serial + "_Temp_" + Jup::GetLocalTime(3);
	}
	int ret = m_pCamera->SetSaveImageType(cameraTy_serial, file_name);
	if (ret != MV_OK)
	{
		// error
		//return -1;
	}
	data.SetValue("HikData", "ImageFile", file_name + ".bmp");
	data.SetValue("HikData", "CurrentCamera", "TY");
	return 0;
}

int HIPACaller::LoadPnpDoeResetDatas(JupData & data)
{
	// 先关闭采集
	m_pCamera->StopGrabbing(cameraTop_serial);
	m_pCamera->StopGrabbing(cameraBottom_serial);

	Sleep(300);

	return 0;
}

int HIPACaller::SetTopCameraHwParameter(JupData & data)
{
	// 修改触发源(上相机软件触发拍照)
	int nRet = m_pCamera->SetTriggerSource(cameraTop_serial, true);
	if (nRet != MV_OK)
	{
		return -1;
	}
	// 修改触发模式
	nRet = m_pCamera->SetTriggerMode(cameraTop_serial, true);
	if (nRet != MV_OK)
	{
		return -2;
	}
	// 设置曝光等参数
	int exposureTime = jCore->GlobalSettings().ReadInt("PnpDoe", "TopCameraExTime");
	nRet = m_pCamera->SetExposureTime(cameraTop_serial, exposureTime);
	if (nRet != MV_OK)
	{
		return -3;
	}
	int gamma = jCore->GlobalSettings().ReadInt("PnpDoe", "TopCameraGamma");
	nRet = m_pCamera->SetGama(cameraTop_serial, gamma);
	if (nRet != MV_OK)
	{
		return -4;
	}

	// 开启上相机采集
	//nRet = m_pCamera->StartGrabbing(cameraTop_serial, false);
	nRet = m_pCamera->StartGrabbing(cameraTop_serial, true);
	if (nRet != MV_OK)
	{
		return -5;
	}

	return 0;
}

int HIPACaller::SetDownCameraHwParameter(JupData & data)
{
	// 修改触发模式
	int nRet = m_pCamera->SetTriggerMode(cameraBottom_serial, true);
	if (nRet != MV_OK)
	{
		return -2;
	}
	// 修改触发源(下相机硬件触发拍照)
	nRet = m_pCamera->SetTriggerSource(cameraBottom_serial, false);
	if (nRet != MV_OK)
	{
		return -1;
	}
	// 设置曝光等参数
	int exposureTime = jCore->GlobalSettings().ReadInt("PnpDoe", "BottomCameraExTime");
	nRet = m_pCamera->SetExposureTime(cameraTop_serial, exposureTime);
	if (nRet != MV_OK)
	{
		return -3;
	}

	// 开启上相机采集
	nRet = m_pCamera->StartGrabbing(cameraBottom_serial, false);
	//nRet = m_pCamera->StartGrabbing(cameraBottom_serial, true);
	if (nRet != MV_OK)
	{
		return -4;
	}

	return 0;
}

int HIPACaller::StartCaptureTopImageThread(JupData & data)
{
	// 软触发一次拍照
	int nRet = m_pCamera->SoftwareOnce(cameraTop_serial);
	if (nRet != MV_OK)
	{
		// 软触发失败
		return -1;
	}
	return 0;
}

int HIPACaller::StartCaptureBottomImageThread(JupData & data)
{
	m_bottom_future = std::async(std::launch::async, &HIPACamera::ImageGrabThreadAsync, m_pCamera, cameraBottom_serial, false);
	return 0;
}

int HIPACaller::SaveTopImageAndCalculate(JupData & data)
{
	// 保存图片
	std::string imagePath = IMAGE_PATH_DEFAULT;
	std::string file_name = imagePath + cameraTop_serial + "_" + Jup::GetLocalTime(3);
	m_pCamera->SetSaveImageType(cameraTop_serial, file_name);
	// 计算结果
	return 0;
}

int HIPACaller::SaveBottomImageAndCalculate(JupData & data)
{
	int ret = m_bottom_future.get();
	if (ret != MV_OK)
	{
		//
	}
	// 保存图片
	std::string imagePath = IMAGE_PATH_DEFAULT;
	std::string file_name = imagePath + cameraBottom_serial + "_" + Jup::GetLocalTime(3);
	m_pCamera->SetSaveImageType(cameraBottom_serial, file_name);
	// 计算结果

	return 0;
}
