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

	// ��ȡ��ʵ��
	static DvpCamera_Manage*& GetInstance();

	// ����/��ȡ����ģʽ 
	bool SetTriggerMode(std::string camera_name, bool bTrigger);

	bool GetTriggerMode(std::string camera_name, bool &bTrigger);

	// ����/��ȡ����Դ
	bool SetTriggerSource(std::string camera_name, dvpTriggerSource TriggerSource);

	bool GetTriggerSource(std::string camera_name, dvpTriggerSource &TriggerSource);

	// �����Զ��ع�
	bool SetAutoExposure(std::string camera_name, dvpAeOperation dvpAuto);

	// ��ȡ�ع�ʱ��
	bool GetExposure(std::string camera_name, double *pExposure);

	// ���ù̶��ع�
	bool SetExposure(std::string camera_name, double Exposure);

	//���÷�תģʽ;
	bool SetFlipMode(std::string camera_name, bool bHorizontal, bool bVertical);

	//�����������
	bool SetCameraUserID(std::string camera_name, char* UserID);

	//��������Դ���
	bool OpenCameraProperty(std::string camera_name);

	// ö���豸
	std::vector<std::string> EnumDevice();	

	// ���豸
	int OpenDevice(std::string camera_name, std::string &strError);
	// ���豸 0820����ʵʱ�ɼ��ж�
	int OpenDevice(std::string camera_name, std::string &strError, bool isLoop);

	// �豸��״̬
	bool Camera_IsOpen(std::string camera_name);

	// �ر��豸
	int CloseDivice(std::string camera_name);

	// ��ʼ�ɼ�
	int StartGrabbing(std::string camera_name);

	// �����ɼ�
	int StopGrabbing(std::string camera_name);

	//����Ƿ����ɼ�
	bool Camera_IsLive(std::string camera_name);

	// ��ȡͼƬ is_SoftwareTrigger = true ��������� is_SoftwareTrigger = false Ӳ����
	int TakePhoto(std::string camera_name, std::string strSaveImagePath, std::string &strError, bool is_SoftwareTrigger = true);
	
	//���ô�ͼ·��
	void SetSaveImagePath(std::string camera_name, std::string strSaveImagePath);

private:
	// �������������к�����
	std::map<std::string, DVPCamera_Control*> m_CameraList;
	inline static DvpCamera_Manage* m_SingleInstance = nullptr;
	inline static std::mutex m_Mutex;
};

