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

	static void DVP_FindAllCamera(std::vector<std::string> &std_strCameraID);					//����������ȡ���ID;
	static std::string DVP_CameraNames(unsigned int nCamID);					//����������ȡ���ID;
	static std::string DVP_FriendlyName(std::string strCameraID);			//����ID��ȡ���FriendlyName;

	bool DVP_IsValidHandle(dvpHandle handle);						//���������;
	bool DVP_OpenCamera(std::string strCameraID, std::string &strError);	//�������ID�������;
	bool DVP_OpenCamera(unsigned int nCamID, std::string &strError);				//�������������;
	bool DVP_IsCameraOpen();

	bool DVP_StartCamera();
	bool DVP_StopCamera();
	bool DVP_IsLive();

	bool DVP_CloseCamera();											//���������ر����;

	bool DVP_TakePhoto(std::string strSaveImagePath, std::string &strError, bool is_SoftwareTrigger);

	bool DVP_CameraProperty();										//������Դ���;
	bool DVP_SetCameraUserID(char* UserID);							//�����������;
	bool DVP_SetTriggerState(bool bState);							//��������ʹ��;
	bool DVP_GetTriggerState(bool &bState);							//��ȡ����ʹ��;
	bool DVP_SetTriggerSource(dvpTriggerSource TriggerSource);		//���ô���Դ;
	bool DVP_GetTriggerSource(dvpTriggerSource &TriggerSource);		//��ȡ����Դ;
	bool DVP_SetAeOperation(dvpAeOperation dvpAuto);				//�����Զ��ع�ʹ��;
	bool DVP_GetExposure(double *pExposure);						//��ȡ�ع�ʱ��
	bool DVP_SetExposure(double Exposure);							//�����ع�
	bool DVP_SetFlipMode(bool bHorizontal, bool bVertical);			//���÷�תģʽ;

	void SetSaveImagePath(std::string strSaveImagePath);

private:
	dvpHandle					m_handle;
	std::string					m_strCamID;
	std::mutex					m_DVP_Lock;
	inline static std::string	m_SaveImagePath = "D:/AlphaDoeImage/image/result.bmp";
	static int OnDrawPicture(dvpHandle handle, dvpStreamEvent event, void *pContext, dvpFrame *pFrame, void *pBuffer);
};