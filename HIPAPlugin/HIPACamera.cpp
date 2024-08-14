#include "HIPACamera.h"
#include <stringapiset.h>
#include <process.h>
#include <WinBase.h>
#include "JupCore.h"
#include "../_INCLUDE/ProjectEvent.h"

using namespace ProjectEvent;

HIPACamera::HIPACamera()
{
	memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
}

HIPACamera::~HIPACamera()
{
	std::map<std::string, CMvCamera*>::iterator iter_camera = m_CameraList.begin();
	while (iter_camera != m_CameraList.end())
	{
		delete iter_camera->second;
		iter_camera++;
	}
	m_CameraList.clear();

	std::map<std::string, CameraStatus*>::iterator iter_status = m_CameraStatus.begin();
	while (iter_status != m_CameraStatus.end())
	{
		delete iter_status->second;
		iter_status++;
	}
	m_CameraStatus.clear();

	if (m_SingleInstance)
	{
		delete m_SingleInstance;
		m_SingleInstance = nullptr;
	}
}

HIPACamera *& HIPACamera::GetInstance()
{
	if (m_SingleInstance == nullptr) {
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (m_SingleInstance == nullptr) {
			m_SingleInstance = new (std::nothrow) HIPACamera{};
		}
	}
	return m_SingleInstance;
}

int HIPACamera::SetTriggerMode(std::string camera_name, int is_trigger)
{
	if (is_trigger)
	{
		m_CameraStatus[camera_name]->m_nTriggerMode = MV_TRIGGER_MODE_ON;
	}
	else
	{
		m_CameraStatus[camera_name]->m_nTriggerMode = MV_TRIGGER_MODE_OFF;
	}
	int nRet = m_CameraList[camera_name]->SetEnumValue("TriggerMode", m_CameraStatus[camera_name]->m_nTriggerMode);
	if (MV_OK != nRet)
	{
		return nRet;
	}
	return 0;
}

int HIPACamera::GetTriggerMode(std::string camera_name)
{
	MVCC_ENUMVALUE stEnumValue = { 0 };

	int nRet = m_CameraList[camera_name]->GetEnumValue("TriggerMode", &stEnumValue);
	if (MV_OK != nRet)
	{
		return nRet;
	}
	int triggerMode = stEnumValue.nCurValue;
	m_CameraStatus[camera_name]->m_nTriggerMode = triggerMode;
	return triggerMode;
}

int HIPACamera::GetExposureTime(std::string camera_name, float& ex)
{
	MVCC_FLOATVALUE stFloatValue = { 0 };

	int nRet = m_CameraList[camera_name]->GetFloatValue("ExposureTime", &stFloatValue);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	ex = stFloatValue.fCurValue;

	return MV_OK;
}

int HIPACamera::SetExposureTime(std::string camera_name, float ex)
{
	// ch:调节这两个曝光模式，才能让曝光时间生效
	// en:Adjust these two exposure mode to allow exposure time effective
	int nRet = m_CameraList[camera_name]->SetEnumValue("ExposureMode", MV_EXPOSURE_MODE_TIMED);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	m_CameraList[camera_name]->SetEnumValue("ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);

	return m_CameraList[camera_name]->SetFloatValue("ExposureTime", (float)ex);
}

int HIPACamera::GetGain(std::string camera_name, float& gain)
{
	MVCC_FLOATVALUE stFloatValue = { 0 };

	int nRet = m_CameraList[camera_name]->GetFloatValue("Gain", &stFloatValue);
	if (MV_OK != nRet)
	{
		return nRet;
	}
	gain = stFloatValue.fCurValue;

	return MV_OK;
}

int HIPACamera::SetGain(std::string camera_name, float gain)
{
	// ch:设置增益前先把自动增益关闭，失败无需返回
	//en:Set Gain after Auto Gain is turned off, this failure does not need to return
	m_CameraList[camera_name]->SetEnumValue("GainAuto", 0);

	return m_CameraList[camera_name]->SetFloatValue("Gain", gain);
}

int HIPACamera::GetGama(std::string camera_name, float & gamma)
{
	return 0;
}

int HIPACamera::SetGama(std::string camera_name, float gamma)
{
	return 0;
}

int HIPACamera::GetFrameRate(std::string camera_name, float& frame_rate)
{
	MVCC_FLOATVALUE stFloatValue = { 0 };

	int nRet = m_CameraList[camera_name]->GetFloatValue("ResultingFrameRate", &stFloatValue);
	if (MV_OK != nRet)
	{
		return nRet;
	}
	frame_rate = stFloatValue.fCurValue;

	return MV_OK;
}

int HIPACamera::SetFrameRate(std::string camera_name, float frame_rate)
{
	int nRet = m_CameraList[camera_name]->SetBoolValue("AcquisitionFrameRateEnable", true);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	return m_CameraList[camera_name]->SetFloatValue("AcquisitionFrameRate", (float)frame_rate);
}

int HIPACamera::GetTriggerSource(std::string camera_name)
{
	MVCC_ENUMVALUE stEnumValue = { 0 };

	int nRet = m_CameraList[camera_name]->GetEnumValue("TriggerSource", &stEnumValue);
	if (MV_OK != nRet)
	{
		return nRet;
	}

	if ((unsigned int)MV_TRIGGER_SOURCE_SOFTWARE == stEnumValue.nCurValue)
	{
		m_CameraStatus[camera_name]->m_isSoftwareTrigger = true;
	}
	else
	{
		m_CameraStatus[camera_name]->m_isSoftwareTrigger = false;
	}

	return stEnumValue.nCurValue;
}

int HIPACamera::SetTriggerSource(std::string camera_name, bool is_software)
{
	int nRet = MV_OK;
	if (is_software)
	{
		m_CameraStatus[camera_name]->m_isSoftwareTrigger = true;
		m_CameraStatus[camera_name]->m_nTriggerSource = MV_TRIGGER_SOURCE_SOFTWARE;
		nRet = m_CameraList[camera_name]->SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_SOFTWARE);
		if (MV_OK != nRet)
		{
			return nRet;
		}
	}
	else
	{
		m_CameraStatus[camera_name]->m_isSoftwareTrigger = false;
		m_CameraStatus[camera_name]->m_nTriggerSource = MV_TRIGGER_SOURCE_LINE0;
		nRet = m_CameraList[camera_name]->SetEnumValue("TriggerSource", MV_TRIGGER_SOURCE_LINE0);
		if (MV_OK != nRet)
		{
			return nRet;
		}
	}

	return nRet;
}

bool HIPACamera::RemoveCustomPixelFormats(MvGvspPixelType enPixelFormat)
{
	int nResult = enPixelFormat & MV_GVSP_PIX_CUSTOM;
	if (MV_GVSP_PIX_CUSTOM == nResult)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<std::string> HIPACamera::EnumDevice()
{
	std::string strMsg;
	std::vector<std::string> deviceList;
	deviceList.clear();

	//m_ctrlDeviceCombo.ResetContent();
	memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

	// ch:枚举子网内所有设备 | en:Enumerate all devices within subnet
	int nRet = CMvCamera::EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);
	if (MV_OK != nRet)
	{
		return std::vector<std::string>();
	}

	// ch:将值加入到信息列表框中并显示出来 | en:Add value to the information list box and display
	for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++)
	{
		MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];
		if (NULL == pDeviceInfo)
		{
			continue;
		}

		wchar_t* pUserName = NULL;
		if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
		{
			int nIp1 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
			int nIp2 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
			int nIp3 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
			int nIp4 = (m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

			if (strcmp("", (LPCSTR)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName)) != 0)
			{
				short dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName), -1, NULL, 0);
				pUserName = new wchar_t[dwLenUserName];
				MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName), -1, pUserName, dwLenUserName);
			}
			else
			{
				char strUserName[256] = { 0 };
				sprintf_s(strUserName, 256, "%s %s (%s)", pDeviceInfo->SpecialInfo.stGigEInfo.chManufacturerName,
					pDeviceInfo->SpecialInfo.stGigEInfo.chModelName,
					pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
				DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(strUserName), -1, NULL, 0);
				pUserName = new wchar_t[dwLenUserName];
				MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(strUserName), -1, pUserName, dwLenUserName);
			}
			//char buf[50];
			//sprintf(buf, "[%d]GigE:    %s  (%d.%d.%d.%d)", i, pUserName, nIp1, nIp2, nIp3, nIp4);
			//strMsg = buf;

			char *buff = new char[20]{ 0 };
			memcpy(buff, pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName, 16);
			strMsg = buff;
			std::string camName = buff;
			CMvCamera* camera = new CMvCamera;
			m_CameraList.insert(std::pair<std::string, CMvCamera*>(camName, camera));
			CameraStatus* cStatus = new CameraStatus();
			cStatus->m_nIndex = i;
			m_CameraStatus.insert(std::pair<std::string, CameraStatus*>(camName, cStatus));
			//strMsg.Format(_T("[%d]GigE:    %s  (%d.%d.%d.%d)"), i, pUserName, nIp1, nIp2, nIp3, nIp4);
		}
		else if (pDeviceInfo->nTLayerType == MV_USB_DEVICE)
		{
			if (strcmp("", (char*)pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName) != 0)
			{
				DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName), -1, NULL, 0);
				pUserName = new wchar_t[dwLenUserName];
				MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName), -1, pUserName, dwLenUserName);
			}
			else
			{
				char strUserName[256] = { 0 };
				sprintf_s(strUserName, 256, "%s %s (%s)", pDeviceInfo->SpecialInfo.stUsb3VInfo.chManufacturerName,
					pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName,
					pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
				DWORD dwLenUserName = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(strUserName), -1, NULL, 0);
				pUserName = new wchar_t[dwLenUserName];
				MultiByteToWideChar(CP_ACP, 0, (LPCSTR)(strUserName), -1, pUserName, dwLenUserName);
			}	
			//strMsg.Format(_T("[%d]UsbV3:  %s"), i, pUserName);
			//char buf[50];
			//sprintf(buf, "[%d]UsbV3:  %s", i, pUserName);
			//strMsg = buf;

			char *buff = new char[20]{ 0 };
			memcpy(buff, pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName, 16);
			strMsg = buff;
			std::string camName = buff;
			CMvCamera* camera = new CMvCamera();
			m_CameraList.insert(std::pair<std::string, CMvCamera*>(camName, camera));
			CameraStatus* cStatus = new CameraStatus();
			cStatus->m_nIndex = i;
			m_CameraStatus.insert(std::pair<std::string, CameraStatus*>(camName, cStatus));
		}
		else
		{
			//ShowErrorMsg(TEXT("Unknown device enumerated"), 0);
		}
		//m_ctrlDeviceCombo.AddString(strMsg);
		deviceList.push_back(strMsg);

		if (pUserName)
		{
			delete[] pUserName;
			pUserName = NULL;
		}
	}

	if (0 == m_stDevList.nDeviceNum)
	{
		//ShowErrorMsg(TEXT("No device"), 0);
		return std::vector<std::string>();
	}
	//m_ctrlDeviceCombo.SetCurSel(0);

	//EnableControls(TRUE);
	return deviceList;
}

int HIPACamera::OpenDevice(std::string camera_name)
{
	if (TRUE == m_CameraList[camera_name]->IsDeviceConnected())
	{
		return -1;
	}

	int nIndex = m_CameraStatus[camera_name]->m_nIndex;
	if ((nIndex < 0) | (nIndex >= MV_MAX_DEVICE_NUM))
	{
		//ShowErrorMsg(TEXT("Please select device"), 0);
		return -2;
	}

	// ch:由设备信息创建设备实例 | en:Device instance created by device information
	if (NULL == m_stDevList.pDeviceInfo[nIndex])
	{
		//ShowErrorMsg(TEXT("Device does not exist"), 0);
		return -3;
	}

	//m_pcMyCamera = new CMvCamera;
	if (NULL == m_CameraList[camera_name])
	{
		return -4;
	}

	int nRet = m_CameraList[camera_name]->Open(m_stDevList.pDeviceInfo[nIndex]);
	if (MV_OK != nRet)
	{
		//delete m_pcMyCamera;
		//m_pcMyCamera = NULL;
		//ShowErrorMsg(TEXT("Open Fail"), nRet);
		return nRet;
	}

	// ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
	if (m_stDevList.pDeviceInfo[nIndex]->nTLayerType == MV_GIGE_DEVICE)
	{
		unsigned int nPacketSize = 0;
		nRet = m_CameraList[camera_name]->GetOptimalPacketSize(&nPacketSize);
		if (nRet == MV_OK)
		{
			unsigned int stParam = 5000;
			m_CameraList[camera_name]->SetIntValue("GevHeartbeatTimeout", stParam); // 设置心跳包时间（异常退出时原本需等待60s）
			nRet = m_CameraList[camera_name]->SetIntValue("GevSCPSPacketSize", nPacketSize);
			if (nRet != MV_OK)
			{
				//ShowErrorMsg(TEXT("Warning: Set Packet Size fail!"), nRet);
				return nRet;
			}
		}
		else
		{
			//ShowErrorMsg(TEXT("Warning: Get Packet Size fail!"), nRet);
			return nRet;
		}
	}
	// 开启连续采集模式
	//SetTriggerMode(camera_name, false);
	//SetContinusMode(camera_name, true);
	//SetTriggerSource(camera_name);
	//// 开启采集
	//nRet = StartGrabbing(camera_name);
	//if (nRet != MV_OK)
	//{
	//	return nRet;
	//}

	return MV_OK;
}

int HIPACamera::CloseDivice(std::string camera_name)
{
	int nRet = MV_OK;
	// 关闭采集(没开启不用执行此步骤)
	if (m_CameraStatus[camera_name]->m_bStartGrabbing)
	{
		nRet = StopGrabbing(camera_name);
		if (nRet != MV_OK)
		{
			return nRet;
		}
	}

	m_CameraStatus[camera_name]->m_bStartGrabbing = FALSE;

	if (m_CameraStatus[camera_name]->m_hGrabThread)
	{
		WaitForSingleObject(m_CameraStatus[camera_name], INFINITE);
		CloseHandle(m_CameraStatus[camera_name]);
		m_CameraStatus[camera_name] = NULL;
	}

	if (m_CameraList[camera_name])
	{
		nRet = m_CameraList[camera_name]->Close();
		if (MV_OK != nRet)
		{
			return nRet;
		}

		//delete(m_pcMyCamera[GetCameraIndex(serial_num)]);
		//m_pcMyCamera[GetCameraIndex(serial_num)] = NULL;
	}

	if (m_CameraStatus[camera_name]->m_pSaveImageBuf)
	{
		free(m_CameraStatus[camera_name]->m_pSaveImageBuf);
		m_CameraStatus[camera_name]->m_pSaveImageBuf = NULL;
	}
	m_CameraStatus[camera_name]->m_nSaveImageBufSize = 0;

	return MV_OK;
}

bool HIPACamera::IsDiviceOpen(std::string camera_name)
{
	return m_CameraList[camera_name]->IsDeviceConnected();
}

int HIPACamera::StartGrabbing(std::string camera_name, bool is_start_thread, bool is_calibration)
{
	if (FALSE == m_CameraList[camera_name]->IsDeviceConnected() || TRUE == m_CameraStatus[camera_name]->m_bStartGrabbing)
	{
		return 0;
	}

	if (m_CameraList[camera_name])
	{
		memset(&(m_CameraStatus[camera_name]->m_stImageInfo), 0, sizeof(MV_FRAME_OUT_INFO_EX));

		int nRet = m_CameraList[camera_name]->StartGrabbing();
		if (MV_OK != nRet)
		{
			return -2;
		}
		m_CameraStatus[camera_name]->m_bStartGrabbing = TRUE;

		// ch:开始采集之后才创建workthread线程
		if (is_start_thread)
		{
			//m_future = std::async(std::launch::async, &HIPACamera::ImageGrabThreadAsync, this, camera_name);
			
			std::thread t(&HIPACamera::ImageGrabThreadAsync, this, camera_name, is_calibration);
			t.detach();
		}
	}
	return 0;
}

int HIPACamera::StopGrabbing(std::string camera_name)
{
	bool ret1 = m_CameraList[camera_name]->IsDeviceConnected();
	bool ret2 = m_CameraStatus[camera_name]->m_bStartGrabbing;
	if (FALSE == m_CameraList[camera_name]->IsDeviceConnected() || FALSE == m_CameraStatus[camera_name]->m_bStartGrabbing)
	{
		return -1;
	}

	m_CameraStatus[camera_name]->m_bStartGrabbing = FALSE;

	if (m_CameraList[camera_name])
	{
		int nRet = m_CameraList[camera_name]->StopGrabbing();
		if (MV_OK != nRet)
		{
			return nRet;
		}
	}

	//if (m_CameraStatus[camera_name]->m_hGrabThread)
	//{
	//	WaitForSingleObject(m_CameraStatus[camera_name]->m_hGrabThread, INFINITE);
	//	CloseHandle(m_CameraStatus[camera_name]->m_hGrabThread);
	//	m_CameraStatus[camera_name]->m_hGrabThread = NULL;
	//}

	return 0;
}

int HIPACamera::SoftwareOnce(std::string camera_name)
{
	if (TRUE != m_CameraStatus[camera_name]->m_bStartGrabbing)
	{
		return -1;
	}
	return m_CameraList[camera_name]->CommandExecute("TriggerSoftware");
}

int HIPACamera::GetOneFrameImage(std::string serial_num)
{
	return 0;
}

bool HIPACamera::SetSaveImageType(std::string camera_name, std::string file_name, MV_SAVE_IAMGE_TYPE type)
{
	MV_SAVE_IMG_TO_FILE_PARAM stSaveFileParam;
	memset(&stSaveFileParam, 0, sizeof(MV_SAVE_IMG_TO_FILE_PARAM));

	EnterCriticalSection(&m_CameraStatus[camera_name]->m_hSaveImageMux);
	if (m_CameraStatus[camera_name]->m_pSaveImageBuf == NULL || m_CameraStatus[camera_name]->m_stImageInfo.enPixelType == 0)
	{
		LeaveCriticalSection(&m_CameraStatus[camera_name]->m_hSaveImageMux);
		return MV_E_NODATA;
	}

	if (RemoveCustomPixelFormats(m_CameraStatus[camera_name]->m_stImageInfo.enPixelType))
	{
		LeaveCriticalSection(&m_CameraStatus[camera_name]->m_hSaveImageMux);
		return MV_E_SUPPORT;
	}

	stSaveFileParam.enImageType = type;							// ch:需要保存的图像类型 | en:Image format to save
	stSaveFileParam.enPixelType = m_CameraStatus[camera_name]->m_stImageInfo.enPixelType;	// ch:相机对应的像素格式 | en:Camera pixel type
	stSaveFileParam.nWidth = m_CameraStatus[camera_name]->m_stImageInfo.nWidth;				// ch:相机对应的宽 | en:Width
	stSaveFileParam.nHeight = m_CameraStatus[camera_name]->m_stImageInfo.nHeight;			// ch:相机对应的高 | en:Height
	stSaveFileParam.nDataLen = m_CameraStatus[camera_name]->m_stImageInfo.nFrameLen;
	stSaveFileParam.pData = m_CameraStatus[camera_name]->m_pSaveImageBuf;
	stSaveFileParam.iMethodValue = 0;

	// ch:jpg图像质量范围为(50-99], png图像质量范围为[0-9] | en:jpg image nQuality range is (50-99], png image nQuality range is [0-9]
	if (MV_Image_Bmp == stSaveFileParam.enImageType)
	{
		sprintf_s(stSaveFileParam.pImagePath, "%s.bmp", file_name.c_str());
	}
	else if (MV_Image_Jpeg == stSaveFileParam.enImageType)
	{
		stSaveFileParam.nQuality = 60;
		sprintf_s(stSaveFileParam.pImagePath, "%s.jpg", file_name.c_str());
	}
	else if (MV_Image_Tif == stSaveFileParam.enImageType)
	{
		sprintf_s(stSaveFileParam.pImagePath, "%s.tif", file_name.c_str());
	}
	else if (MV_Image_Png == stSaveFileParam.enImageType)
	{
		stSaveFileParam.nQuality = 8;
		sprintf_s(stSaveFileParam.pImagePath, "%s.png", file_name.c_str());
	}

	LeaveCriticalSection(&m_CameraStatus[camera_name]->m_hSaveImageMux);
	int nRet = m_CameraList[camera_name]->SaveImageToFile(&stSaveFileParam);

	return nRet;
}

int HIPACamera::ImageGrabThreadAsync(std::string camera_name, bool is_calibration)
{
	if (m_CameraList[camera_name])
	{
		MV_FRAME_OUT stImageInfo = { 0 };
		MV_DISPLAY_FRAME_INFO stDisplayInfo = { 0 };
		do
		{
			int nRet = m_CameraList[camera_name]->GetImageBuffer(&stImageInfo, 10000);
			if (nRet == MV_OK)
			{
				//用于保存图片
				EnterCriticalSection(&m_CameraStatus[camera_name]->m_hSaveImageMux);
				if (NULL == m_CameraStatus[camera_name]->m_pSaveImageBuf || stImageInfo.stFrameInfo.nFrameLen > m_CameraStatus[camera_name]->m_nSaveImageBufSize)
				{
					if (m_CameraStatus[camera_name]->m_pSaveImageBuf)
					{
						free(m_CameraStatus[camera_name]->m_pSaveImageBuf);
						m_CameraStatus[camera_name]->m_pSaveImageBuf = NULL;
					}

					m_CameraStatus[camera_name]->m_pSaveImageBuf = (unsigned char *)malloc(sizeof(unsigned char) * stImageInfo.stFrameInfo.nFrameLen);
					if (m_CameraStatus[camera_name]->m_pSaveImageBuf == NULL)
					{
						LeaveCriticalSection(&m_CameraStatus[camera_name]->m_hSaveImageMux);
						return -1;
					}
					m_CameraStatus[camera_name]->m_nSaveImageBufSize = stImageInfo.stFrameInfo.nFrameLen;
				}
				memcpy(m_CameraStatus[camera_name]->m_pSaveImageBuf, stImageInfo.pBufAddr, stImageInfo.stFrameInfo.nFrameLen);
				memcpy(&m_CameraStatus[camera_name]->m_stImageInfo, &(stImageInfo.stFrameInfo), sizeof(MV_FRAME_OUT_INFO_EX));
				LeaveCriticalSection(&m_CameraStatus[camera_name]->m_hSaveImageMux);

				//自定义格式不支持显示
				if (RemoveCustomPixelFormats(stImageInfo.stFrameInfo.enPixelType))
				{
					m_CameraList[camera_name]->FreeImageBuffer(&stImageInfo);
					continue;
				}
				//stDisplayInfo.hWnd = m_hwndDisplay;
				stDisplayInfo.pData = stImageInfo.pBufAddr;
				stDisplayInfo.nDataLen = stImageInfo.stFrameInfo.nFrameLen;
				stDisplayInfo.nWidth = stImageInfo.stFrameInfo.nWidth;
				stDisplayInfo.nHeight = stImageInfo.stFrameInfo.nHeight;
				stDisplayInfo.enPixelType = stImageInfo.stFrameInfo.enPixelType;
				//m_pcMyCamera->DisplayOneFrame(&stDisplayInfo);

				// 标定时显示到标定界面
				if (is_calibration)
				{
					jCore->SendEvent(g_CalibrationWidget, &JCalibrationEvent("DisplayOnceFrame", camera_name, stDisplayInfo.pData, stDisplayInfo.nWidth, stDisplayInfo.nHeight));
					Sleep(500);
				}
				else
					jCore->SendEvent(g_HikWidget, &JHikEvent("DisplayOnceFrame", (void*)&stDisplayInfo));		

				m_CameraList[camera_name]->FreeImageBuffer(&stImageInfo);
			}
			else
			{
				if (MV_TRIGGER_MODE_ON != m_CameraStatus[camera_name]->m_nTriggerMode)
				{
					Sleep(1);
				}
			}
		} while (m_CameraStatus[camera_name]->m_bStartGrabbing && (MV_TRIGGER_SOURCE_SOFTWARE ==  m_CameraStatus[camera_name]->m_nTriggerSource || MV_TRIGGER_MODE_ON != m_CameraStatus[camera_name]->m_nTriggerMode)); // 连续模式循环采图，触发模式只采图一次
	}
	return MV_OK;
}

CMvCamera * HIPACamera::GetCamera(std::string camera_name)
{
	return m_CameraList.empty() ? m_CameraList[camera_name] : nullptr;
}

CameraStatus * HIPACamera::GetCameraStatus(std::string camera_name)
{
	return m_CameraStatus.empty() ? m_CameraStatus[camera_name] : nullptr;
}