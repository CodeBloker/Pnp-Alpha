#pragma once
#include "MvCamera.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <map>
#include <synchapi.h>
#include "Common/JIniSettings.h"
#include <future>

#define MAX_DEVICE_NUM          9
#define IMAGE_PATH_DEFAULT		"E:/AlphaDoeImage/"

class CameraStatus
{
public:
	int   m_nIndex;
	bool  m_isContinueTrigger;
	bool  m_isSoftwareTrigger;
	bool  m_bStartGrabbing;
	int   m_nTriggerMode;
	int   m_nTriggerSource;
	CRITICAL_SECTION        m_hSaveImageMux;
	unsigned char*          m_pSaveImageBuf;
	unsigned int            m_nSaveImageBufSize;
	MV_FRAME_OUT_INFO_EX    m_stImageInfo;
	void*                   m_hGrabThread;

	CameraStatus()
	{
		m_nIndex = 0;
		m_isContinueTrigger = true;
		m_isSoftwareTrigger = false;
		m_bStartGrabbing = false;
		m_nTriggerMode = MV_TRIGGER_MODE_OFF;
		m_nTriggerSource = MV_TRIGGER_SOURCE_LINE0;
		m_hGrabThread = NULL;
		m_pSaveImageBuf = NULL;
		m_nSaveImageBufSize = 0;
		memset(&(m_stImageInfo), 0, sizeof(MV_FRAME_OUT_INFO_EX));
		InitializeCriticalSection(&m_hSaveImageMux);
	};
};


class HIPACamera
{
public:
	HIPACamera();
	~HIPACamera();

	// 获取单实例
	static HIPACamera*& GetInstance();

	// 设置/获取触发模式 
	int SetTriggerMode(std::string camera_name, int is_trigger);
	int GetTriggerMode(std::string camera_name);
	// 设置/获取曝光时间
	int GetExposureTime(std::string camera_name, float& ex);
	int SetExposureTime(std::string camera_name, float ex);
	// 设置/获取增益
	int GetGain(std::string camera_name, float& gain);
	int SetGain(std::string camera_name, float gain);
	// 设置/获取Gamma
	int GetGama(std::string camera_name, float& gamma);
	int SetGama(std::string camera_name, float gamma);
	// 设置/获取帧率
	int GetFrameRate(std::string camera_name, float& frame_rate);
	int SetFrameRate(std::string camera_name, float frame_rate);
	// 设置/获取触发源
	int GetTriggerSource(std::string camera_name);
	int SetTriggerSource(std::string camera_name, bool is_software);

	// 枚举设备
	std::vector<std::string> EnumDevice();	
	// 打开设备
	int OpenDevice(std::string camera_name);
	// 关闭设备
	int CloseDivice(std::string camera_name);
	// 设备连接状态
	bool IsDiviceOpen(std::string camera_name);

	// 开始采集
	int StartGrabbing(std::string camera_name, bool is_start_thread = true, bool is_calibration = false);
	// 结束采集
	int StopGrabbing(std::string camera_name);
	// 软触发一次
	int SoftwareOnce(std::string camera_name);

	// 获得一帧图像
	int GetOneFrameImage(std::string camera_name);
	// 图像保存 
	bool SetSaveImageType(std::string camera_name, std::string file_name, MV_SAVE_IAMGE_TYPE type = MV_SAVE_IAMGE_TYPE::MV_Image_Bmp);

	// 去除自定义的像素格式
	bool RemoveCustomPixelFormats(enum MvGvspPixelType enPixelFormat); 

	// 采集线程
	int ImageGrabThreadAsync(std::string camera_name, bool is_calibration = false);

	CMvCamera* GetCamera(std::string camera_name);
	CameraStatus* GetCameraStatus(std::string camera_name);
	
private:
	MV_CC_DEVICE_INFO_LIST  m_stDevList;

	// 多个相机根据序列号区分
	std::map<std::string, CMvCamera*> m_CameraList;
	std::map<std::string, CameraStatus*> m_CameraStatus;

	inline static HIPACamera* m_SingleInstance = nullptr;
	inline static std::mutex m_Mutex;
	std::future<int> m_future;
};

