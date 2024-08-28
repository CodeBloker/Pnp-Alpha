#include "DvpCamera_Manage.h"
#include <stringapiset.h>
#include <process.h>
#include <WinBase.h>
#include "JupCore.h"
#include "../_INCLUDE/ProjectEvent.h"

using namespace ProjectEvent;

DvpCamera_Manage::DvpCamera_Manage()
{
	
}

DvpCamera_Manage::~DvpCamera_Manage()
{
	std::map<std::string, DVPCamera_Control*>::iterator iter_camera = m_CameraList.begin();
	while (iter_camera != m_CameraList.end())
	{
		delete iter_camera->second;
		iter_camera++;
	}
	m_CameraList.clear();

	if (m_SingleInstance)
	{
		delete m_SingleInstance;
		m_SingleInstance = nullptr;
	}
}

DvpCamera_Manage *& DvpCamera_Manage::GetInstance()
{
	if (m_SingleInstance == nullptr) {
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (m_SingleInstance == nullptr) {
			m_SingleInstance = new (std::nothrow) DvpCamera_Manage{};
		}
	}
	return m_SingleInstance;
}

bool DvpCamera_Manage::SetTriggerMode(std::string camera_name, bool bTrigger)
{
	if (NULL == m_CameraList[camera_name])
	{
		return false;
	}
	return m_CameraList[camera_name]->DVP_SetTriggerState(bTrigger);
}

bool DvpCamera_Manage::GetTriggerMode(std::string camera_name, bool &bTrigger)
{
	if (NULL == m_CameraList[camera_name])
	{
		return false;
	}
	return m_CameraList[camera_name]->DVP_GetTriggerState(bTrigger);
}

bool DvpCamera_Manage::SetTriggerSource(std::string camera_name, dvpTriggerSource TriggerSource)
{
	if (NULL == m_CameraList[camera_name])
	{
		return false;
	}
	return m_CameraList[camera_name]->DVP_SetTriggerSource(TriggerSource);
}

bool DvpCamera_Manage::GetTriggerSource(std::string camera_name, dvpTriggerSource &TriggerSource)
{
	if (NULL == m_CameraList[camera_name])
	{
		return false;
	}
	return m_CameraList[camera_name]->DVP_GetTriggerSource(TriggerSource);
}

bool DvpCamera_Manage::SetAutoExposure(std::string camera_name, dvpAeOperation dvpAuto)
{
	if (NULL == m_CameraList[camera_name])
	{
		return false;
	}
	return m_CameraList[camera_name]->DVP_SetAeOperation(dvpAuto);
}

bool DvpCamera_Manage::GetExposure(std::string camera_name, double *pExposure)
{
	if (NULL == m_CameraList[camera_name])
	{
		return false;
	}
	return m_CameraList[camera_name]->DVP_GetExposure(pExposure);
}

bool DvpCamera_Manage::SetExposure(std::string camera_name, double Exposure)
{
	if (NULL == m_CameraList[camera_name])
	{
		return false;
	}
	return m_CameraList[camera_name]->DVP_SetExposure(Exposure);
}

bool DvpCamera_Manage::SetFlipMode(std::string camera_name, bool bHorizontal, bool bVertical)
{
	if (NULL == m_CameraList[camera_name])
	{
		return false;
	}
	return m_CameraList[camera_name]->DVP_SetFlipMode(bHorizontal, bVertical);
}

bool DvpCamera_Manage::SetCameraUserID(std::string camera_name, char* UserID)
{
	if (NULL == m_CameraList[camera_name])
	{
		return false;
	}
	return m_CameraList[camera_name]->DVP_SetCameraUserID(UserID);
}

bool DvpCamera_Manage::OpenCameraProperty(std::string camera_name)
{
	if (NULL == m_CameraList[camera_name])
	{
		return false;
	}
	if (m_CameraList[camera_name]->DVP_IsCameraOpen())
	{
		m_CameraList[camera_name]->DVP_CameraProperty();
		return true;
	}
	return false;
}

std::vector<std::string> DvpCamera_Manage::EnumDevice()
{
	std::string strMsg;
	std::vector<std::string> deviceList;
	deviceList.clear();

	// ch:枚举子网内所有设备 | en:Enumerate all devices within subnet
	DVPCamera_Control::DVP_FindAllCamera(deviceList);
	if (deviceList.empty())
	{
		return std::vector<std::string>();
	}
	for (const auto value : deviceList)
	{
		std::string camName = value;
		DVPCamera_Control* camera = new DVPCamera_Control;
		m_CameraList.insert(std::pair<std::string, DVPCamera_Control*>(camName, camera));
	}

	return deviceList;
}

int DvpCamera_Manage::OpenDevice(std::string camera_name, std::string &strError)
{
	//m_pcMyCamera = new CMvCamera;
	if (NULL == m_CameraList[camera_name])
	{
		return -1;
	}

	if (m_CameraList[camera_name]->DVP_IsCameraOpen())
	{
		CloseDivice(camera_name);
	}
	if (!m_CameraList[camera_name]->DVP_OpenCamera(camera_name, strError))
	{
		return -2;
	}

	return 0;
}

int DvpCamera_Manage::OpenDevice(std::string camera_name, std::string & strError, bool isLoop)
{
	if (NULL == m_CameraList[camera_name])
	{
		return -1;
	}

	if (m_CameraList[camera_name]->DVP_IsCameraOpen())
	{
		CloseDivice(camera_name);
	}
	if (!m_CameraList[camera_name]->DVP_OpenCamera(camera_name, strError, isLoop))
	{
		return -2;
	}

	return 0;
}

bool DvpCamera_Manage::Camera_IsOpen(std::string camera_name)
{
	if (NULL == m_CameraList[camera_name])
	{
		return false;
	}
	return m_CameraList[camera_name]->DVP_IsCameraOpen();
}

int DvpCamera_Manage::CloseDivice(std::string camera_name)
{
	// 关闭采集
	int nRet = StopGrabbing(camera_name);
	if (nRet != 0)
	{
		return -1;
	}
	if (NULL == m_CameraList[camera_name])
	{
		return -2;
	}

	if (m_CameraList[camera_name])
	{
		if(!m_CameraList[camera_name]->DVP_CloseCamera())
		{
			return -3;
		}
	}

	return 0;
}

int DvpCamera_Manage::StartGrabbing(std::string camera_name)
{
	if (NULL == m_CameraList[camera_name])
	{
		return -1;
	}
	if (!Camera_IsOpen(camera_name))
	{
		return -2;
	}
	if (!m_CameraList[camera_name]->DVP_IsLive())
	{
		if(!m_CameraList[camera_name]->DVP_StartCamera())
		{
			return -3;
		}
	}

	return 0;
}

int DvpCamera_Manage::StopGrabbing(std::string camera_name)
{
	if (NULL == m_CameraList[camera_name])
	{
		return -1;
	}
	if (!Camera_IsOpen(camera_name))
	{
		return -2;
	}
	if (m_CameraList[camera_name]->DVP_IsLive())
	{
		if (!m_CameraList[camera_name]->DVP_StopCamera())
		{
			return -3;
		}
	}

	return 0;
}

bool DvpCamera_Manage::Camera_IsLive(std::string camera_name)
{
	if (NULL == m_CameraList[camera_name])
	{
		return false;
	}
	return m_CameraList[camera_name]->DVP_IsLive();
}

int DvpCamera_Manage::TakePhoto(std::string camera_name, std::string strSaveImagePath, std::string &strError, bool is_SoftwareTrigger)
{
	if (NULL == m_CameraList[camera_name])
	{
		strError = "Camera ID: " + camera_name + " ,camera does not exist";
		return -1;
	}
	std::string localCamerName = camera_name;
	std::string localSaveImagePath = strSaveImagePath;
	bool localIsSoftwareTrigger = is_SoftwareTrigger;

	//if (localCamerName == std::string("DVP Bottom Vision") && !localIsSoftwareTrigger)
	//{
	//	for (size_t i = 0; i < 2; i++)
	//	{
	//		size_t lastSlashPos = localSaveImagePath.find_last_of('/');
	//		if (lastSlashPos == std::string::npos)
	//		{
	//			strError = "Not found '\'";
	//			jCore->Logger("DvpPlugin.dll").LogError(__FUNCTION__, strError);
	//			return -3;
	//		}
	//		std::string directory = localSaveImagePath.substr(0, lastSlashPos + 1);
	//		std::string filename = localSaveImagePath.substr(lastSlashPos + 1);
	//		std::string newFilename;
	//		if (i != 0)
	//		{
	//			newFilename = std::to_string(i + 1) + filename;
	//		}
	//		else
	//		{
	//			newFilename = filename;
	//		}
	//		std::string newPath = directory + newFilename;
	//		std::thread([this, localCamerName, newPath, strError, localIsSoftwareTrigger]()
	//		{
	//			std::string subStrError = strError;
	//			m_CameraList[localCamerName]->DVP_TakePhoto(newPath, subStrError, localIsSoftwareTrigger);
	//		}).detach();
	//	}
	//}
	//else
	//{
	//	if (!m_CameraList[camera_name]->DVP_TakePhoto(strSaveImagePath, strError, is_SoftwareTrigger))
	//	{
	//		jCore->Logger("DvpPlugin.dll").LogError(__FUNCTION__, strError);
	//		return -2;
	//	}
	//}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//std::thread([this, localCamerName, localSaveImagePath, strError, localIsSoftwareTrigger]()
	//{
	//	std::string subStrError = strError;
	//	if (!m_CameraList[localCamerName]->DVP_TakePhoto(localSaveImagePath, subStrError, localIsSoftwareTrigger))
	//	{
	//		
	//	}
	//}).detach();

	if (!m_CameraList[camera_name]->DVP_TakePhoto(strSaveImagePath, strError, is_SoftwareTrigger))
	{
		return -2;
	}
	return 0;
}

void DvpCamera_Manage::SetSaveImagePath(std::string camera_name, std::string strSaveImagePath)
{
	if (m_CameraList[camera_name] != NULL)
	{
		m_CameraList[camera_name]->SetSaveImagePath(strSaveImagePath);
	}
}