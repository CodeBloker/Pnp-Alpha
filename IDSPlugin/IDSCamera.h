#pragma once

#include <future>
#include "ueye.h"

class IDSCamera
{
public:
	IDSCamera();
	~IDSCamera();

	static IDSCamera*& GetInstance();

	INT InitCamera(HIDS *hCam, HWND hWnd);   //��ʼ�����   hWndָ����ʾͼ�񴰿ڵ�ָ�룬����DIBģʽ������hWnd=NULL  
	bool OpenCamera();
	void ExitCamera();
	int  InitDisplayMode();
	void GetMaxImageSize(INT *pnSizeX, INT *pnSizeY);//��ѯ���֧�ֵ�ͼ���ʽ
	bool SaveImage(const char* fileName);

	// �����������
	bool SetGamma(int nGamma);				// ����Gamma
	int ReadGamma();						// ��ȡGamma
	bool SetGain(int nGain);				// ��������
	int ReadGain();							// ��ȡ����
	bool SetExposure(double nExposure);		// �����ع�
	double ReadExposure();					// ��ȡ�ع�
	bool SetFrameRate(double nFrameRate);	// ����֡��
	double ReadFrameRate();					// ��ȡ֡��
	bool SetSharpness(double nSharpness);	// ����������
	int ReadSharpness();					// ��ȡ������

	int SetTrigger(int m_nTimeout, int mode);
	int LoadParameterFromFile(const char* file);

	int getWidth();
	int getHeight();

	int	 StartGrabbingImage(bool is_calibration = false);
	int	 StopGrabbingImage();
	void GetCaptureImage(bool is_calibration = false);

	// uEye varibles
	HIDS	m_hCam;				// ������
	HWND	m_hWndDisplay;		// window��ʾ���
	INT		m_nColorMode;		// Y8/RGB16/RGB24/REG32
	INT		m_nBitsPerPixel;	// ͼ��λ��
	INT		m_nSizeX;			// ͼ����
	INT		m_nSizeY;			// ͼ��߶�
	INT		m_nPosX;			// ͼ����ƫ��
	INT		m_nPosY;			// ͼ����ƫ��

	char *m_pLastBuffer;

	bool    m_bStartGrabbing;
private:
	wchar_t* charToWchat(const char* str);

private:
	// ʹ��λͼģʽ����ʵʱ��ʾ��Ҫ���ڴ�  
	INT	 m_lMemoryId;	        // camera memory - buffer ID
	char*	m_pcImageMemory;	// camera memory - pointer to buffer
	SENSORINFO m_sInfo;			// sensor information struct
	INT     m_nRenderMode;		// render  mode
	INT     m_nFlipHor;			// ˮƽ��ת��־
	INT     m_nFlipVert;		// ��ֱ��ת��־

	inline static IDSCamera* m_SingleInstance = nullptr;
	inline static std::mutex m_Mutex;
};

