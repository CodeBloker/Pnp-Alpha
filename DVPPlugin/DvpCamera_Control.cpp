#include "DvpCamera_Control.h"
#include "JupCore.h"
#include "../_INCLUDE/ProjectEvent.h"

DVPCamera_Control::DVPCamera_Control()
{
	m_strCamID = "NULL";
	m_handle = NULL;
}

DVPCamera_Control::~DVPCamera_Control()
{
    if (m_handle != NULL)
    {
		dvpClose(m_handle);
		m_handle = NULL;
    }
}

void DVPCamera_Control::DVP_FindAllCamera(std::vector<std::string> &std_strCameraID)
{
	std_strCameraID.clear();
	UINT i = 0;
	while (1)
	{
		std::string strCameraID = DVP_CameraNames(i);
		if (strCameraID != "")
		{
			std_strCameraID.push_back(strCameraID);
			i++;
		}
		else
			break;
	}
}

std::string DVPCamera_Control::DVP_CameraNames(unsigned int nCamID)
{
	UINT num_camera = 0;
	dvpCameraInfo info = { 0 };
	if (dvpRefresh(&num_camera) == DVP_STATUS_OK)
	{
		if (num_camera <= nCamID)
			return "";
	}
	if (dvpEnum((dvpUint32)nCamID, &info) == DVP_STATUS_OK)
	{
		/*std::string strCamID, strSerialNumber;
		strCamID = info.FriendlyName;
		int nPos = strCamID.find("@");
		strSerialNumber = strCamID.substr(nPos + 1);
		return strSerialNumber;*/
		std::string strCamID;
		strCamID = info.UserID;
		return strCamID; 
	}

	return "";
}

std::string DVPCamera_Control::DVP_FriendlyName(std::string strCameraID)
{
	unsigned int num_camera = 0;
	dvpCameraInfo info = { 0 };
	if (dvpRefresh(&num_camera) == DVP_STATUS_OK)
	{
		for (UINT i = 0; i < num_camera; i++)
		{
			if (dvpEnum((dvpUint32)i, &info) == DVP_STATUS_OK)
			{
				std::string strCamID, strUserID;
				strCamID = info.FriendlyName;
				strUserID = info.UserID;
				int pos = strCamID.find(strCameraID);
				if (pos > 0)
					return strCamID;
				if(strUserID == strCameraID)
					return strCamID;
			}
		}
	}

	return "";
}

bool DVPCamera_Control::DVP_IsValidHandle(dvpHandle handle)
{
	bool bValidHandle;
	dvpStatus status = dvpIsValid(handle, &bValidHandle);
	if (status != DVP_STATUS_OK)
		return false;
	return bValidHandle;
}

bool DVPCamera_Control::DVP_OpenCamera(std::string strCameraID, std::string &strError)
{
	dvpStatus status = DVP_STATUS_OK;
	dvpUint32 NumCamera;
	std::string strFriendlyName;

	if (!DVP_IsValidHandle(m_handle))
	{
		if (strCameraID != "")
		{
			//查找ID对应的friendlyName;
			strFriendlyName = DVP_FriendlyName(strCameraID);
			if (strFriendlyName == "")
			{
				strError = "Fail to find Camera " + strCameraID;
				return false;
			}

			//连接相机;
			status = dvpOpenByName(strFriendlyName.c_str(), OPEN_NORMAL, &m_handle);
			if (status != DVP_STATUS_OK)
			{
				strError = "Fail to open Camera [Error :" + std::to_string(status) + "][" + strCameraID + "]";
				return false;
			}
			m_strCamID = strCameraID;

			////注册回调函数;
			//status = dvpRegisterStreamCallback(m_handle, OnDrawPicture, STREAM_EVENT_FRAME_THREAD, this);
			//if (status != DVP_STATUS_OK)
			//{
			//	strError = "Fail to Register Stream Callback [Error :" + std::to_string(status) + "][" + strCameraID + "]";
			//	return false;
			//}

			strError = "Success to open Camera :" +  strCameraID;
			return true;
		}
		else
		{
			strError = "Fail to open Camera [Error :" + std::to_string(status) + "][" + strCameraID + "]";
			return false;
		}
	}

	strError = "Camera can not open again [Error :" + std::to_string(status) + "][" + strCameraID + "]";
	return false;
}

bool DVPCamera_Control::DVP_OpenCamera(std::string strCameraID, std::string & strError, bool isLoop)
{
	dvpStatus status = DVP_STATUS_OK;
	dvpUint32 NumCamera;
	std::string strFriendlyName;

	if (!DVP_IsValidHandle(m_handle))
	{
		if (strCameraID != "")
		{
			//查找ID对应的friendlyName;
			strFriendlyName = DVP_FriendlyName(strCameraID);
			if (strFriendlyName == "")
			{
				strError = "Fail to find Camera " + strCameraID;
				return false;
			}

			//连接相机;
			status = dvpOpenByName(strFriendlyName.c_str(), OPEN_NORMAL, &m_handle);
			if (status != DVP_STATUS_OK)
			{
				strError = "Fail to open Camera [Error :" + std::to_string(status) + "][" + strCameraID + "]";
				return false;
			}
			m_strCamID = strCameraID;

			if (isLoop)
			{
				//注册回调函数;
				dvpUnregisterStreamCallback(m_handle, OnDrawPicture, STREAM_EVENT_FRAME_THREAD, this);
				Sleep(100);
				status = dvpRegisterStreamCallback(m_handle, OnDrawPicture, STREAM_EVENT_FRAME_THREAD, this);
				if (status != DVP_STATUS_OK)
				{
					strError = "Fail to Register Stream Callback [Error :" + std::to_string(status) + "][" + strCameraID + "]";
					return false;
				}
			}

			strError = "Success to open Camera :" + strCameraID;
			return true;
		}
		else
		{
			strError = "Fail to open Camera [Error :" + std::to_string(status) + "][" + strCameraID + "]";
			return false;
		}
	}

	strError = "Camera can not open again [Error :" + std::to_string(status) + "][" + strCameraID + "]";
	return false;
}

bool DVPCamera_Control::DVP_OpenCamera(unsigned int nCamID, std::string &strError)
{
	dvpStatus status = DVP_STATUS_OK;
	dvpUint32 NumCamera;

	if (!DVP_IsValidHandle(m_handle))
	{
		//相机数量查询;
		unsigned int num_camera = 0;
		status = dvpRefresh(&num_camera);
		if (status != DVP_STATUS_OK)
		{
			strError = "Fail to find Camera [Error :" + std::to_string(status) + "][" + std::to_string(nCamID) + "]";
			return false;
		}

		if (num_camera <= nCamID)
		{
			strError = "Fail to find Camera [Error :" + std::to_string(status) + "][" + std::to_string(nCamID) + "]";
			return false;
		}

		//连接相机;
		status = dvpOpen((dvpUint32)nCamID, OPEN_NORMAL, &m_handle);
		if (status != DVP_STATUS_OK)
		{
			strError = "Fail to open Camera [Error :" + std::to_string(status) + "][" + std::to_string(nCamID) + "]";
			return false;
		}
		m_strCamID = DVP_CameraNames(nCamID);

		//注册回调函数;
		//status = dvpRegisterStreamCallback(m_handle, OnDrawPicture, STREAM_EVENT_FRAME_THREAD, this);
		//if (status != DVP_STATUS_OK)
		//{
		//	strError = "Fail to Register Stream Callback [Error :" + std::to_string(status) + "][" + std::to_string(nCamID) + "]";
		//	return false;
		//}

		strError = "Camera can not open again [Error :" + std::to_string(status) + "][" + std::to_string(nCamID) + " - " + m_strCamID + "]"; 
		return true;
	}

	strError = "Camera can not open again [Error :" + std::to_string(status) + "][" + std::to_string(nCamID) + "]";
	return false;
}

bool DVPCamera_Control::DVP_IsCameraOpen()
{
	if (DVP_IsValidHandle(m_handle))
		return true;

	return false;
}

bool DVPCamera_Control::DVP_StartCamera()
{
	dvpStreamState state;
	dvpStatus status;

	if (DVP_IsValidHandle(m_handle))
	{
		//查询视频流状态;
		status = dvpGetStreamState(m_handle, &state);
		if (state == STATE_STARTED)
		{
			return true;
		}
		else
		{
			status = dvpStart(m_handle);
			if (status == DVP_STATUS_OK)
				return true;
		}
	}

	return false;
}

bool DVPCamera_Control::DVP_StopCamera()
{
	dvpStreamState state;
	dvpStatus status;

	if (DVP_IsValidHandle(m_handle))
	{
		//查询视频流状态;
		status = dvpGetStreamState(m_handle, &state);
		if (state == STATE_STARTED)
		{
			status = dvpStop(m_handle);
			if (status == DVP_STATUS_OK)
				return true;
		}
		else
		{
			return true;
		}
	}

	return false;
}

bool DVPCamera_Control::DVP_IsLive()
{
	dvpStreamState state;
	dvpStatus status;

	if (DVP_IsValidHandle(m_handle))
	{
		//查询视频流状态;
		status = dvpGetStreamState(m_handle, &state);
		if (state == STATE_STARTED)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool DVPCamera_Control::DVP_CloseCamera()
{
	dvpStatus status;
	dvpStreamState state;
	//关闭视频流;
	status = dvpGetStreamState(m_handle, &state);
	if (state == STATE_STARTED)
	{
		status = dvpStop(m_handle);
	}
	dvpUnregisterStreamCallback(m_handle, OnDrawPicture, STREAM_EVENT_FRAME_THREAD, this);
	status = dvpClose(m_handle);
	m_handle = NULL;
	if (status == DVP_STATUS_OK)
		return true;
	else
		return false;

	return true;
}

bool DVPCamera_Control::DVP_TakePhoto(std::string strSaveImagePath, std::string &strError, bool is_SoftwareTrigger)
{
	dvpStatus status;
	dvpFrame frame;
	void *pBuffer;
	//**************************************************
	//提前获取图片;
	status = dvpGetFrame(m_handle, &frame, &pBuffer, 10);
	m_DVP_Lock.lock();

	if (is_SoftwareTrigger)
	{		
		//**************************************************软触发;
		//查询软触发使能状态;
		bool bSendTrigger = false;
		bool bSoftTrigger = false;
		status = dvpGetTriggerState(m_handle, &bSoftTrigger);
		if (DVP_STATUS_OK == status && bSoftTrigger)
		{
			//查询软触发触发使能状态;
			bool bSoftTriggerLoop = false;
			status = dvpGetSoftTriggerLoopState(m_handle, &bSoftTriggerLoop);
			if (DVP_STATUS_OK == status && !bSoftTriggerLoop)
			{
				//发送软触发信号;
				status = dvpTriggerFire(m_handle);
				if (status != DVP_STATUS_OK)
				{
					strError = "Fail to send the Trigger Error : " + std::to_string(status);
					jCore->Logger("DvpPlugin.dll").LogError(__FUNCTION__, strError);
					m_DVP_Lock.unlock();
					return false;
				}
				else
				{
					bSendTrigger = true;
				}
			}

			if (status != DVP_STATUS_OK || !bSendTrigger)
			{
				strError = "Fail to wait for sending the Trigger Error : " + std::to_string(status);
				jCore->Logger("DvpPlugin.dll").LogError(__FUNCTION__, strError);
				m_DVP_Lock.unlock();
				return false;
			}
		}
		else if (DVP_STATUS_OK != status)
		{
			strError = "Fail to get Trigger State Error : " + std::to_string(status);
			jCore->Logger("DvpPlugin.dll").LogError(__FUNCTION__, strError);
			m_DVP_Lock.unlock();
			return false;
		}
	}
	
	//**************************************************
	//获取图片;
	status = dvpGetFrame(m_handle, &frame, &pBuffer, 10000);
	if (status != DVP_STATUS_OK)
	{
		strError = "Fail to get the data of photo Error : " + std::to_string(status);
		jCore->Logger("DvpPlugin.dll").LogError(__FUNCTION__, strError);
		m_DVP_Lock.unlock();
		return false;
	}
	jCore->PostEvent(ProjectEvent::g_DvpWidget, new ProjectEvent::JDvpEvent(pBuffer, frame.iWidth, frame.iHeight));
	//保存图片;
	status = dvpSavePicture(&frame, pBuffer, strSaveImagePath.c_str(), 100);
	if (status != DVP_STATUS_OK)
	{
		strError = "save photo Error : " + std::to_string(status) + "save path:" + strSaveImagePath;
		jCore->Logger("DvpPlugin.dll").LogError(__FUNCTION__, strError);
		m_DVP_Lock.unlock();
		return false;
	}
	//jCore->SendEvent(ProjectEvent::g_DvpWidget, &ProjectEvent::JDvpPnpCalibrationEvent(strSaveImagePath));//用来校准的时候用的
	m_DVP_Lock.unlock();
	return true;
}

bool DVPCamera_Control::DVP_CameraProperty()
{
	dvpStatus status;
	HWND hParent = NULL;
	if (DVP_IsValidHandle(m_handle))
	{
		status = dvpShowPropertyModalDialog(m_handle, hParent);
		if (status != DVP_STATUS_OK)
		{
			return false;
		}
		return true;
	}
	return false;
}

bool DVPCamera_Control::DVP_SetCameraUserID(char* UserID)
{
	UINT Length = strlen(UserID);
	dvpStatus status = dvpSetUserId(m_handle, UserID, &Length);
	if (status != DVP_STATUS_OK)
	{
		return false;
	}
	return true;
}

bool DVPCamera_Control::DVP_SetTriggerState(bool bState)
{
	dvpStatus status;
	dvpStreamState state;
	if (DVP_IsValidHandle(m_handle))
	{
		//暂停视频流;
		status = dvpGetStreamState(m_handle, &state);
		if (state == STATE_STARTED)
		{
			status = dvpStop(m_handle);
		}

		//修改触发模式;
		status = dvpSetTriggerState(m_handle, bState);
		if (status != DVP_STATUS_OK)
		{
			return false;
		}
		if (state == STATE_STARTED)
		{
			//启动视频流;
			status = dvpStart(m_handle);
		}
		return true;
	}

	return false;
}

bool DVPCamera_Control::DVP_GetTriggerState(bool &bState)
{
	dvpStatus status;
	dvpStreamState state;
	if (DVP_IsValidHandle(m_handle))
	{		
		status = dvpGetTriggerState(m_handle, &bState);
		if (status != DVP_STATUS_OK)
		{
			return false;
		}		
		return true;
	}

	return false;
}

bool DVPCamera_Control::DVP_SetTriggerSource(dvpTriggerSource TriggerSource)
{
	dvpStatus status;
	if (DVP_IsValidHandle(m_handle))
	{
		status = dvpSetTriggerSource(m_handle, TriggerSource);
		if (status != DVP_STATUS_OK)
		{
			return false;
		}
		return true;
	}

	return false;
}

bool DVPCamera_Control::DVP_GetTriggerSource(dvpTriggerSource &TriggerSource)
{
	dvpStatus status;
	dvpStreamState state;
	if (DVP_IsValidHandle(m_handle))
	{
		status = dvpGetTriggerSource(m_handle, &TriggerSource);
		if (status != DVP_STATUS_OK)
		{
			return false;
		}
		return true;
	}

	return false;
}

bool DVPCamera_Control::DVP_SetAeOperation(dvpAeOperation dvpAuto)
{
	dvpStatus status;
	dvpStreamState state;
	if (DVP_IsValidHandle(m_handle))
	{
		status = dvpSetAeOperation(m_handle, dvpAuto);
		if (status == DVP_STATUS_OK)
		{
			return true;
		}
	}

	return false;
}

bool DVPCamera_Control::DVP_GetExposure(double *pExposure)
{
	dvpStatus status;
	if (DVP_IsValidHandle(m_handle))
	{
		status = dvpGetExposure(m_handle, pExposure);
		if (status != DVP_STATUS_OK)
		{
			return false;
		}
		return true;
	}

	return false;
}

bool DVPCamera_Control::DVP_SetExposure(double Exposure)
{
	dvpStatus status;
	if (DVP_IsValidHandle(m_handle))
	{
		status = dvpSetExposure(m_handle, Exposure);
		if (status != DVP_STATUS_OK)
		{
			return false;
		}
		return true;
	}

	return false;
}

bool DVPCamera_Control::DVP_SetFlipMode(bool bHorizontal, bool bVertical)
{
	dvpStatus status;
	dvpStreamState state;
	if (DVP_IsValidHandle(m_handle))
	{
		status = dvpSetFlipHorizontalState(m_handle, bHorizontal);
		if (status != DVP_STATUS_OK)
		{
			return false;
		}
		status = dvpSetFlipVerticalState(m_handle, bVertical);
		if (status != DVP_STATUS_OK)
		{
			return false;
		}
		return true;
	}
	return false;
}

void DVPCamera_Control::SetSaveImagePath(std::string strSaveImagePath)
{
	m_SaveImagePath = strSaveImagePath;
}
//***********************************************************************************************************************************************
int DVPCamera_Control::OnDrawPicture(dvpHandle handle, dvpStreamEvent event, void *pContext, dvpFrame *pFrame, void *pBuffer)
{
	//std::string strSaveImagePath = m_SaveImagePath + "AliveGet" + Jup::GetLocalTime(1) + ".bmp";
	//// 保存新图片
	//dvpStatus status = dvpSavePicture(pFrame, pBuffer, strSaveImagePath.c_str(), 100);
	//if (status != DVP_STATUS_OK)
	//{
	//	std:: string strError = "save photo Error : " + std::to_string(status) + "save path:" + strSaveImagePath;
	//}
	//jCore->SendEvent(ProjectEvent::g_DvpWidget, &ProjectEvent::JDvpPnpCalibrationEvent(pBuffer, pFrame->iWidth, pFrame->iHeight,strSaveImagePath));
	jCore->SendEvent(ProjectEvent::g_DvpWidget, new ProjectEvent::JDvpEvent(pBuffer, pFrame->iWidth, pFrame->iHeight));
	return 0;
}
