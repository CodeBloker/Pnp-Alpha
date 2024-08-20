#pragma once
#include "DvpCamera_Control.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <map>
#include <synchapi.h>
#include "Common/JIniSettings.h"
#include <future>

#define MAX_DEVICE_NUM          9
#define IMAGE_PATH_DEFAULT		"D:/AlphaDoeImage/"


class DvpCamera_Manage
{
public:
	DvpCamera_Manage();
	~DvpCamera_Manage();

	// 获取单实例
	static DvpCamera_Manage*& GetInstance();

	// 设置/获取触发模式 
	bool SetTriggerMode(std::string camera_name, bool bTrigger);

	bool GetTriggerMode(std::string camera_name, bool &bTrigger);

	// 设置/获取触发源
	bool SetTriggerSource(std::string camera_name, dvpTriggerSource TriggerSource);

	bool GetTriggerSource(std::string camera_name, dvpTriggerSource &TriggerSource);

	// 设置自动曝光
	bool SetAutoExposure(std::string camera_name, dvpAeOperation dvpAuto);

	// 获取曝光时间
	bool GetExposure(std::string camera_name, double *pExposure);

	// 设置固定曝光
	bool SetExposure(std::string camera_name, double Exposure);

	//设置翻转模式;
	bool SetFlipMode(std::string camera_name, bool bHorizontal, bool bVertical);

	//设置相机名称
	bool SetCameraUserID(std::string camera_name, char* UserID);

	//打开相机属性窗口
	bool OpenCameraProperty(std::string camera_name);

	// 枚举设备
	std::vector<std::string> EnumDevice();	

	// 打开设备
	int OpenDevice(std::string camera_name, std::string &strError);
	// 打开设备 0820增加实时采集判断
	int OpenDevice(std::string camera_name, std::string &strError, bool isLoop);

	// 设备打开状态
	bool Camera_IsOpen(std::string camera_name);

	// 关闭设备
	int CloseDivice(std::string camera_name);

	// 开始采集
	int StartGrabbing(std::string camera_name);

	// 结束采集
	int StopGrabbing(std::string camera_name);

	//相机是否开启采集
	bool Camera_IsLive(std::string camera_name);

	// 获取图片 is_SoftwareTrigger = true 软件触发， is_SoftwareTrigger = false 硬触发
	int TakePhoto(std::string camera_name, std::string strSaveImagePath, std::string &strError, bool is_SoftwareTrigger = true);
	
	//设置存图路径
	void SetSaveImagePath(std::string camera_name, std::string strSaveImagePath);

private:
	// 多个相机根据序列号区分
	std::map<std::string, DVPCamera_Control*> m_CameraList;
	inline static DvpCamera_Manage* m_SingleInstance = nullptr;
	inline static std::mutex m_Mutex;
};

