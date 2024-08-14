#include "CameraDILManager.h"

#define FILE_25MP_EXT_DCF								"D:\\EVMS\\ENV\\Config\\25M_Trig.dcf"
#define FILE_25MP_DCF									"D:\\EVMS\\ENV\\Config\\25M_Cont.dcf"
#define COM_BUFF_SIZE			32

CameraDILManager::CameraDILManager()
{
	m_milManager = MilManager::GetInstance();
}

CameraDILManager::~CameraDILManager()
{
}

bool CameraDILManager::Open()
{
	if (m_bOpened)
		return false;

	bool bRtn = true;
	char tszDCF[MAX_PATH] = { 0, };
	char mszDCF[MAX_PATH] = { 0, };

	//QByteArray descriptor = "M_SYSTEM_RADIENTEVCL";
	MsysAllocA(m_milManager->getMilInstance().milApplication, "M_SYSTEM_RADIENTEVCL", M_DEV0, M_COMPLETE, &m_milSys);
	if (m_milSys == 0)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Init fail, bad descriptor : " + descriptor, 0);
		bRtn = false;
	}

	sprintf_s(tszDCF, _countof(tszDCF), "%s", FILE_25MP_EXT_DCF);
	MosSprintfA(mszDCF, MAX_PATH, "%s", tszDCF);
	if (MdigAllocA(m_milSys, M_DEV0, mszDCF, M_DEFAULT, &m_milDig) == M_NULL)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "MdigAllocA is null", 0);
		bRtn = false;
	}

	MdigControl(m_milDig, M_GRAB_TIMEOUT, 5000);

	MbufAlloc2d(m_milSys, GetWidth(), GetHeight(), 8, M_IMAGE + M_DISP + M_GRAB + M_PROC, &m_milGrabBuf);

	//´®¿Ú1-9: "COM1"~"COM9", ´®¿Ú10->"\\\\.\\COM10"
	if (m_comm.OpenDevice("COM8", CBR_57600, 8, 0, 0, 0) != 1)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Bad serial port : " + strSerial, 0);
		bRtn = false;
	}

	this->SetRunMode(1);

	m_bOpened = bRtn;

	return m_bOpened;
}

void CameraDILManager::Close()
{
	if (!m_bOpened)
		return;

	m_comm.CloseDevice();

	MbufFree(m_milGrabBuf);
	MdigFree(m_milDig);
	//MsysFree(m_milSys);
	m_bOpened = false;
}

uchar * CameraDILManager::GetGrabImage()
{
	cv::Mat mat;
	MdigGrab(m_milDig, m_milGrabBuf); //700ms+   427ms

	uchar *pBuf = NULL;
	std::vector<uchar> vBuf;

	pBuf = new uchar[this->GetWidth() * this->GetHeight()];
	MbufGet2d(m_milGrabBuf, 0, 0, GetWidth(), GetHeight(), pBuf);

	vBuf.resize(this->GetWidth() * this->GetHeight());
	memcpy(&vBuf[0], pBuf, this->GetWidth() * this->GetHeight());
	delete[] pBuf;

	mat = cv::Mat(cv::Size(this->GetWidth(), this->GetHeight()), GetType(), vBuf.data());
	mat.copyTo(m_matGrab);

	//g_pOP->LogInfo(-1, __FUNCTION__, "Grab Image OK, mat.size:%f", mat.size());
	//imwrite("D:\\lua\\test.bmp", m_matGrab);
	return m_matGrab.data;
}

void CameraDILManager::SetRetryGrabCount(int nCount)
{
	m_nRetryGrabCount = nCount;
	MdigControl(m_milDig, M_GRAB_TIMEOUT, m_nRetryGrabCount);
}

void CameraDILManager::SetRunMode(int nMode)
{
	if (m_nRunMode == nMode)
		return;

	int nRunMode = 0;

	if (nMode == 0)
		nRunMode = 0;		// Continue
	else if (nMode == 1)
		nRunMode = 3;		// External

	MdigFree(m_milDig);

	char sDCF[MAX_PATH] = { 0, };
	if (nRunMode == 0)		// Continue
	{
		sprintf_s(sDCF, _countof(sDCF), "%s", FILE_25MP_DCF);
	}
	else if (nRunMode == 3)	// External 
	{
		sprintf_s(sDCF, _countof(sDCF), "%s", FILE_25MP_EXT_DCF);
	}

	if (MdigAllocA(m_milSys, M_DEV0, sDCF, M_DEFAULT, &m_milDig) == M_NULL)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "MdigAllocA is null", 0);
	}

	char buf[COM_BUFF_SIZE] = { 0, };
	sprintf_s(buf, sizeof(buf), "%cMO%d%c", 0x40, nRunMode, 0x0D);
	m_comm.Send(buf, strlen(buf));

	m_nRunMode = nMode;
}

int CameraDILManager::GetExposure()
{
	m_comm.ClearReceiveData();

	char buf[COM_BUFF_SIZE] = { 0, };
	sprintf_s(buf, sizeof(buf), "%cIT?%c", 0x40, 0x0D);
	m_comm.Send(buf, strlen(buf));
	::Sleep(100);

	for (int i = 0; i < 10; i++)
	{
		if (m_comm.IsExistRecvData())
		{
			::ZeroMemory(buf, sizeof(buf));
			m_comm.GetReceiveData(buf, sizeof(buf));
			return atoi(&buf[3]);
		}
		::Sleep(100);
	}
	return 0;
}

void CameraDILManager::SetExposure(int nExpTime)
{
	char buf[COM_BUFF_SIZE] = { 0, };
	int expTime = nExpTime;

	if (expTime > 100000)
		expTime = 100000;

	sprintf_s(buf, sizeof(buf), "%cIT%d%c", 0x40, expTime, 0x0D);
	m_comm.Send(buf, strlen(buf));
}

int CameraDILManager::GetGain()
{
	m_comm.ClearReceiveData();

	char buf[COM_BUFF_SIZE] = { 0, };
	sprintf_s(buf, sizeof(buf), "%cGA?%c", 0x40, 0x0D);
	m_comm.Send(buf, strlen(buf));
	::Sleep(100);

	for (int i = 0; i < 10; i++)
	{
		if (m_comm.IsExistRecvData())
		{
			::ZeroMemory(buf, sizeof(buf));
			m_comm.GetReceiveData(buf, sizeof(buf));
			return atoi(&buf[3]);
		}
		::Sleep(100);
	}
	return 0;
}

void CameraDILManager::SetGain(int nGain)
{
	char buf[COM_BUFF_SIZE] = { 0, };
	sprintf_s(buf, sizeof(buf), "%cGA%d%c", 0x40, nGain, 0x0D);
	m_comm.Send(buf, strlen(buf));
}

int CameraDILManager::GetBlackLevel()
{
	m_comm.ClearReceiveData();

	char buf[COM_BUFF_SIZE] = { 0, };
	sprintf_s(buf, sizeof(buf), "%cBL?%c", 0x40, 0x0D);
	m_comm.Send(buf, strlen(buf));
	::Sleep(100);

	for (int i = 0; i < 10; i++)
	{
		if (m_comm.IsExistRecvData())
		{
			::ZeroMemory(buf, sizeof(buf));
			m_comm.GetReceiveData(buf, sizeof(buf));
			return atoi(&buf[3]);
		}
		::Sleep(100);
	}
	return 0;
}

void CameraDILManager::SetBlackLevel(int nLevel)
{
	char buf[COM_BUFF_SIZE] = { 0, };
	int level = nLevel;

	if (level > 255)
		level = 255;

	sprintf_s(buf, sizeof(buf), "%cBL%d%c", 0x40, level, 0x0D);
	m_comm.Send(buf, strlen(buf));
}

int CameraDILManager::GetFramePeriod()
{
	m_comm.ClearReceiveData();

	char buf[COM_BUFF_SIZE] = { 0, };
	sprintf_s(buf, sizeof(buf), "%cFP?%c", 0x40, 0x0D);
	m_comm.Send(buf, strlen(buf));
	::Sleep(100);

	for (int i = 0; i < 10; i++)
	{
		if (m_comm.IsExistRecvData())
		{
			::ZeroMemory(buf, sizeof(buf));
			m_comm.GetReceiveData(buf, sizeof(buf));
			return atoi(&buf[3]);
		}
		::Sleep(100);
	}
	return 0;
}

void CameraDILManager::SetFramePeriod(int nPeriod)
{
	char buf[COM_BUFF_SIZE] = { 0, };
	int period = nPeriod;

	if (period > 100000)
		period = 100000;

	sprintf_s(buf, sizeof(buf), "%cFP%d%c", 0x40, period, 0x0D);
	m_comm.Send(buf, strlen(buf));
}

double CameraDILManager::GetTemperature()
{
	MIL_INT val = 0;
	MdigInquireFeature(m_milDig, M_FEATURE_VALUE, MIL_TEXT("Temperature"), M_DEFAULT, &val);
	return (double)val;
}
