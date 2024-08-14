#pragma once
#include "MilManager.h"
#include "Common/JSerialPort.h"
#include "opencv2/opencv.hpp"

class CameraDILManager
{
public:
	CameraDILManager();
	~CameraDILManager();

	bool Open();
	void Close();

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

private:
	MIL_ID m_milSys;
	MIL_ID m_milDig;
	MIL_ID m_milGrabBuf;

	cv::Mat m_matGrab;

	bool m_bOpened;
	int m_nRunMode;		//(0:continue, 1:external trigger, 2:software trigger)

	int m_nImgWidth;
	int m_nImgHeight;
	int m_nRetryGrabCount;

	JSerialPort m_comm;

	MilManager* m_milManager;
};

