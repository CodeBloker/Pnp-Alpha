#pragma once
#include "MilManager.h"
#include "Common/JSerialPort.h"
#include "opencv2/opencv.hpp"
#include "SimpleSerialPort.h"

class CameraDILManager
{
public:
	CameraDILManager();
	~CameraDILManager();

	static CameraDILManager*& GetInstance();

	bool Open();
	void Close();

	void StartGrabing();
	uchar* GetGrabImage();
	void SetRetryGrabCount(int nCount);

	bool IsOpened() { return m_bOpened; }
	int GetType() { return CV_8UC1; }
	int GetWidth() { return m_nImgWidth; }
	int GetHeight() { return m_nImgHeight; }

	int GetRunMode() { return m_nRunMode; }
	void SetRunMode(int nMode);

	int GetExposure();
	void SetExposure(int nExpTime);

	int GetGain();
	void SetGain(int nGain);

	int GetBlackLevel();
	void SetBlackLevel(int nLevel);

	int GetFramePeriod();
	void SetFramePeriod(int nPeriod);

	double GetTemperature();

	void SetStartGrabing(bool status);

private:
	MIL_ID m_milSys;
	MIL_ID m_milDig;
	MIL_ID m_milGrabBuf;

	cv::Mat m_matGrab;

	bool m_bOpened = false;
	int m_nRunMode;		//(0:continue, 1:external trigger, 2:software trigger)

	int m_nImgWidth = 5120;
	int m_nImgHeight = 5120;
	int m_nTriggerModeTimeout = 10000;

	bool isStartGrabing = false;

	SimpleSerialPort m_comm;
	MilManager* m_milManager;

	inline static CameraDILManager* m_SingleInstance = nullptr;
	inline static std::mutex m_Mutex;
};

