#pragma once

#include "DVPCamera.h"
#include <string>
#include <vector>
#include <mutex>

class DVPCamera_Control
{
public:
	DVPCamera_Control();
	~DVPCamera_Control();

	static void DVP_FindAllCamera(std::vector<std::string> &std_strCameraID);					//根据索引获取相机ID;
	static std::string DVP_CameraNames(unsigned int nCamID);					//根据索引获取相机ID;
	static std::string DVP_FriendlyName(std::string strCameraID);			//根据ID获取相机FriendlyName;

	bool DVP_IsValidHandle(dvpHandle handle);						//相机句柄检查;
	bool DVP_OpenCamera(std::string strCameraID, std::string &strError);	//根据相机ID代开相机;
	bool DVP_OpenCamera(unsigned int nCamID, std::string &strError);				//根据索引打开相机;
	bool DVP_IsCameraOpen();

	bool DVP_StartCamera();
	bool DVP_StopCamera();
	bool DVP_IsLive();

	bool DVP_CloseCamera();											//根据索引关闭相机;

	bool DVP_TakePhoto(std::string strSaveImagePath, std::string &strError, bool is_SoftwareTrigger);

	bool DVP_CameraProperty();										//相机属性窗口;
	bool DVP_SetCameraUserID(char* UserID);							//设置相机名称;
	bool DVP_SetTriggerState(bool bState);							//设置软触发使能;
	bool DVP_GetTriggerState(bool &bState);							//获取软触发使能;
	bool DVP_SetTriggerSource(dvpTriggerSource TriggerSource);		//设置触发源;
	bool DVP_GetTriggerSource(dvpTriggerSource &TriggerSource);		//获取触发源;
	bool DVP_SetAeOperation(dvpAeOperation dvpAuto);				//设置自动曝光使能;
	bool DVP_GetExposure(double *pExposure);						//获取曝光时间
	bool DVP_SetExposure(double Exposure);							//设置曝光
	bool DVP_SetFlipMode(bool bHorizontal, bool bVertical);			//设置翻转模式;

	void SetSaveImagePath(std::string strSaveImagePath);

private:
	dvpHandle					m_handle;
	std::string					m_strCamID;
	std::mutex					m_DVP_Lock;
	inline static std::string	m_SaveImagePath = "D:/AlphaDoeImage/image/result.bmp";
	static int OnDrawPicture(dvpHandle handle, dvpStreamEvent event, void *pContext, dvpFrame *pFrame, void *pBuffer);
};