#pragma once

#include <future>
#include "ueye.h"

class IDSCamera
{
public:
	IDSCamera();
	~IDSCamera();

	static IDSCamera*& GetInstance();

	INT InitCamera(HIDS *hCam, HWND hWnd);   //初始化相机   hWnd指向显示图像窗口的指针，若用DIB模式可以令hWnd=NULL  
	bool OpenCamera();
	void ExitCamera();
	int  InitDisplayMode();
	void GetMaxImageSize(INT *pnSizeX, INT *pnSizeY);//查询相机支持的图像格式
	bool SaveImage(const char* fileName);

	// 设置相机参数
	bool SetGamma(int nGamma);				// 设置Gamma
	int ReadGamma();						// 获取Gamma
	bool SetGain(int nGain);				// 设置增益
	int ReadGain();							// 获取增益
	bool SetExposure(double nExposure);		// 设置曝光
	double ReadExposure();					// 获取曝光
	bool SetFrameRate(double nFrameRate);	// 设置帧率
	double ReadFrameRate();					// 获取帧率
	bool SetSharpness(double nSharpness);	// 设置清晰度
	int ReadSharpness();					// 获取清晰度

	int SetTrigger(int m_nTimeout, int mode);
	int LoadParameterFromFile(const char* file);

	int getWidth();
	int getHeight();

	int	 StartGrabbingImage(bool is_calibration = false);
	int	 StopGrabbingImage();
	void GetCaptureImage(bool is_calibration = false);

	// uEye varibles
	HIDS	m_hCam;				// 相机句柄
	HWND	m_hWndDisplay;		// window显示句柄
	INT		m_nColorMode;		// Y8/RGB16/RGB24/REG32
	INT		m_nBitsPerPixel;	// 图像位深
	INT		m_nSizeX;			// 图像宽度
	INT		m_nSizeY;			// 图像高度
	INT		m_nPosX;			// 图像左偏移
	INT		m_nPosY;			// 图像右偏移

	char *m_pLastBuffer;

	bool    m_bStartGrabbing;
private:
	wchar_t* charToWchat(const char* str);

private:
	// 使用位图模式进行实时显示需要的内存  
	INT	 m_lMemoryId;	        // camera memory - buffer ID
	char*	m_pcImageMemory;	// camera memory - pointer to buffer
	SENSORINFO m_sInfo;			// sensor information struct
	INT     m_nRenderMode;		// render  mode
	INT     m_nFlipHor;			// 水平翻转标志
	INT     m_nFlipVert;		// 垂直翻转标志

	inline static IDSCamera* m_SingleInstance = nullptr;
	inline static std::mutex m_Mutex;
};

