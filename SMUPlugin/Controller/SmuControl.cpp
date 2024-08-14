#include "SmuControl.h"
#include <Windows.h>

SmuControl::SmuControl()
{
	loadParameterFromFile();
}

SmuControl::~SmuControl()
{
}

SmuControl *& SmuControl::GetInstance()
{
	if (m_SingleInstance == nullptr) {
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (m_SingleInstance == nullptr) {
			m_SingleInstance = new (std::nothrow) SmuControl{};
		}
	}
	return m_SingleInstance;
}

bool SmuControl::OpenVISA(std::string session, std::string address, std::string prefix)
{
	bool ret = true;

	if (OpenDevice() != 1)
	{
		ret = false;
	}
	else
	{
		//g_pOP->LogDebug(-1, __FUNCTION__, "SMU DefaultRM : %ld", m_Visa.GetDefaultRMNum());
	}

	char _session[32];
	sprintf_s(_session, _countof(_session), "%s", session.c_str());

	if (AddSession(_session, address, prefix, 2000/*OPEN_TIMEOUT*/) == false)
	{
		//g_pOP->LogInfo(-1, __FUNCTION__, "SMU initialization retry");

		Sleep(100);

		if (AddSession(_session, address, prefix, 2000/*OPEN_TIMEOUT*/) == false)
		{
			//g_pOP->LogError(-1, __FUNCTION__, "SMU initialization FAIL!!!");
			ret = false;
		}
	}

	if (ret)
	{
		unsigned long dwValue = 0;
		viSetAttribute(GetSession(session), VI_ATTR_TMO_VALUE, 500);
		viGetAttribute(GetSession(session), VI_ATTR_TMO_VALUE, &dwValue);
		//g_pOP->LogInfo(-1, __FUNCTION__, "%s Timeout : %dms", _session, dwValue);

		viGetAttribute(GetSession(session), VI_ATTR_RD_BUF_SIZE, &dwValue);
		//g_pOP->LogInfo(-1, __FUNCTION__, "%s Read Buffer Size : %d", _session, dwValue);

		viGetAttribute(GetSession(session), VI_ATTR_WR_BUF_SIZE, &dwValue);
		//g_pOP->LogInfo(-1, __FUNCTION__, "%s Write Buffer Size : %d", _session, dwValue);

		if (session.find("DMM") != std::string::npos)
			fnSetUpDMM(session);
		else
			fnSetUpSMU(session);
	}
	return ret;
}

bool SmuControl::fnSMUDevImpl()
{
	std::string session;
	std::string sAddress;
	//session = g_pINSP->m_SFR60Setting.GetString("SMU_SFR60_Num", "SMU1");
	session = m_AlphaSetting["SMU_SFR60_Num"];
	//sAddress = g_pINSP->m_SFR60Setting.GetString("SMU_SFR60_Addr", "TCPIP0::192.168.5.20::inst0::INSTR");
	sAddress = m_AlphaSetting["SMU_SFR60_Addr"];
	bool res = OpenVISA(session, sAddress, "node[1]");
	//int res = this->OpenVISA(QString("SMU1"), "TCPIP0::192.168.5.20::inst0::INSTR", "node[1]");
	if (!res)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Open SMU1 FAILED", 0);
		return false;
	}
	Sleep(200);
	m_smuIsConnected = true;
	return true;
}

bool SmuControl::fnSMUDevDestory()
{
	m_smuIsConnected = false;
	return CloseDevice();
}

bool SmuControl::fnSetUpSMU(std::string session)
{
	WriteScriptToSMU(session);

	Sleep(20);
	fnResetSMU(session);		//Reset_SMU()
	Sleep(200);

	ExecuteCommand(false, session, "Init_SMU()");
	Sleep(200);

	return true;
}

bool SmuControl::fnSetUpDMM(std::string session)
{
	char buf[1024];
	//g_pOP->LogInfo(-1, __FUNCTION__, "Setting %s.", session.toLatin1().data());

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Script
	bool ret = WriteScriptToDMM(session);
	Sleep(200);

	sprintf_s(buf, sizeof(buf), "Init_DMM(0.01)");
	ret &= ExecuteCommand(false, session, buf);
	Sleep(200);

	return ret;
}

void SmuControl::fnResetSMU(std::string session)
{
	ExecuteCommand(false, session, "Reset_SMU()");
	Sleep(100);
}

bool SmuControl::SMU_ReadBuffer(std::string session, int nSocIndex, std::vector<SMU_READ_BUFFER_DATA>& buffer_data, std::string ReadBufferCommand)
{
	bool bResult = false;

	std::string strSession = session;
	std::string strRawData;
	char readedBuffer[VISA_BUFFER] = { 0L, };

	std::string strReadBufferCmd;
	if (ReadBufferCommand != "")
	{
		strReadBufferCmd = ReadBufferCommand;
	}
	else
		strReadBufferCmd = "Buffer_Read()";

	memcpy(readedBuffer, strRawData.c_str(), strRawData.size());

	//g_pDEV->m_Visa.ReadResult(strSession, readedBuffer, _countof(readedBuffer));

	char *pTok, *pSes;
	std::string tsztmp;

	int nItemCnt = 0;

	SMU_READ_BUFFER_DATA result;
	if (strcmp(readedBuffer, "nil") != 0)
	{
		pTok = strtok_s(readedBuffer, ",", &pSes);
		tsztmp = pTok;

		result.V_DOT = atof(tsztmp.c_str());
		nItemCnt++;
		while (pTok != NULL)
		{
			//dTemp = (double)atof(pTok);
			//vTempList.push_back(dTemp);

			pTok = strtok_s(NULL, ",", &pSes);
			tsztmp = pTok;

			if (!tsztmp.empty())
			{
				switch (nItemCnt)
				{
				case 0:	result.V_DOT = atof(tsztmp.c_str()); break;
				case 1:	result.V_A = atof(tsztmp.c_str()); break;
				case 2:	result.V_B = atof(tsztmp.c_str()); break;
				case 3:	result.V_F = atof(tsztmp.c_str()); break;
				case 4:	result.I_DOT = atof(tsztmp.c_str()); break;
				case 5:	result.I_A = atof(tsztmp.c_str()); break;
				case 6:	result.I_B = atof(tsztmp.c_str()); break;
				case 7:	result.I_F = atof(tsztmp.c_str()); break;
				case 8:	result.NTC_R = atof(tsztmp.c_str());
					bResult = true;
					buffer_data.push_back(result);
					nItemCnt = -1;
					break;
				}
				nItemCnt++;
			}
		}

	}
	return bResult;
}

bool SmuControl::GetNtcOFF(std::string session, int nSocIndex, double * dTemper, double * dRValue)
{
	return true;
}

bool SmuControl::SMU_BufferClear(std::string session, int nSocIndex)
{
	std::string strSession = session;

	bool bRtn = TRUE;

	int retryCnt = 3; //5
	bool bReadOK = false;
	for (int i = 0; i < retryCnt; i++)
	{
		std::string strRes;
		if (ExecuteCommand(FALSE, strSession, "Buffer_Clear()") == FALSE) //"Buffer_Clear()\r\n"
		{
			continue;
		}

		bReadOK = true;
		break;
	}
	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "SMU Buffer Clear, Session:%s, SocketIndex:%d", session.toLatin1().data(), nSocIndex);
	return bReadOK ? true : false;
}

bool SmuControl::SMU_Initialize(std::string session, int nSocIndex)
{
	std::string strSession = session;
	bool bRtn = fnSetUpSMU(strSession);
	return bRtn;
}

bool SmuControl::fnGetNTCSMU(std::string session, int nSocIndex, double & Temperature)
{
	BOOL status = FALSE;
	//从SMU读取对应的电阻值，然后根据公式计算出温度
	double dRtrace = 0.0;
	double dTemp = 0.0;
	bool ret = GetNtcOFF(session, nSocIndex, &dTemp, &dRtrace);
	Temperature = dTemp;

	return ret;
}

int SmuControl::OpenDevice()
{
	m_defaultRM = NULL;
	if (viOpenDefaultRM(&m_defaultRM) != VI_SUCCESS)
		return 0;
	else
		return 1;
}

bool SmuControl::AddSession(std::string szName, std::string szConStr, std::string szPrefix, int nTimeout)
{
	char szBuf[128];
	char szPre[128];
	VisaSession session;
	
	strcpy_s(szBuf, _countof(szBuf), szConStr.c_str());
	strcpy_s(szPre, _countof(szPre), szPrefix.c_str());

	// "TCPIP0::192.168.5.100::inst0::INSTR"
	if (viOpen(m_defaultRM, szBuf, VI_NULL, nTimeout, &session.vi) != VI_SUCCESS)
		return false;
	else
	{
		session.bCopy = false;

		strcpy_s(session.szPrefix, _countof(session.szPrefix), szPre);
		m_mapSession[szName] = session;

		viSetBuf(session.vi, VI_READ_BUF, VISA_BUF_SIZE);
		viSetBuf(session.vi, VI_WRITE_BUF, VISA_BUF_SIZE);
	}
	return true;
}

bool SmuControl::CopySession(std::string szDestName, std::string szPrefix, std::string szSrcName)
{
	VisaSession session;
	char szBuf[128];

	if (m_mapSession.find(szSrcName) == m_mapSession.end())
		return false;

	strcpy_s(szBuf, _countof(szBuf), szPrefix.c_str());

	session.bCopy = true;
	strcpy_s(session.szPrefix, _countof(session.szPrefix), szBuf);
	session.vi = m_mapSession[szSrcName].vi;
	
	m_mapSession[szDestName] = session;
	return true;
}

int SmuControl::CloseDevice()
{
	VisaSession session;

	for (auto&[key, value]: m_mapSession)
	{
		session = value;
		if (!session.bCopy)
			viClose(session.vi);
	}

	m_mapSession.clear();
	viClose(m_defaultRM);
	return 1;
}


ViSession SmuControl::GetSession(std::string szName)
{
	return m_mapSession[szName].vi;
}

bool SmuControl::ExecuteCommand(bool bAddPrefix, std::string szName, std::string szCommand)
{
	return ExecuteCommand(bAddPrefix, szName, szCommand.c_str());
}

bool SmuControl::ExecuteCommand(bool bAddPrefix, std::string szName, const char* szCommand, ...)
{	
	va_list list;
	char pszBuf[VISA_BUFFER];

	size_t nPrefixLen = 0;

	VisaSession session = m_mapSession[szName];

	if (bAddPrefix)
	{
		sprintf_s(pszBuf, _countof(pszBuf), "%s.", session.szPrefix);
		nPrefixLen = strlen(pszBuf);
	}
	else
		nPrefixLen = 0;

	va_start(list, szCommand);
    vsprintf_s(&pszBuf[nPrefixLen], _countof(pszBuf) - nPrefixLen, szCommand, list);	
    va_end(list);
	
	ViStatus ret = viPrintf(session.vi, (char *)"%s\n", pszBuf);

	//g_pOP->LogInfo(-1, __FUNCTION__, "[%s][%s] %s", szName.toLatin1().data(), ret == VI_SUCCESS ? "OK" : "NG", pszBuf);

	if (ret != VI_SUCCESS)
		return false;
	else
		return true;
}

bool SmuControl::ReadResult(std::string szName, char* szResult, int cbLen)
{
	VisaSession session = m_mapSession[szName];
	
	ViStatus ret = viScanf(session.vi, (char *)"%t", szResult);

	if (ret != VI_SUCCESS)
		return false;
	else
		return true;	
}

bool SmuControl::WriteScriptToSMU(std::string szSessionNm)
{
	char szFile[260];
	VisaSession session = m_mapSession[szSessionNm];
	sprintf_s(szFile, _countof(szFile), SMUFile_INI);

	viClear(session.vi);

	// WriteFromFile
	FILE *fp;
	char szLine[COMMAND_MAX_SIZE];
	bool bFirstLine = true;

	//g_pOP->LogInfo(-1, __FUNCTION__, "SMU Script Loading Start");

	fopen_s(&fp, szFile, "r");
	while (!feof(fp))
	{
		memset(szLine, 0, sizeof(char) * _countof(szLine));
		fgets(szLine, _countof(szLine), fp);

		if (bFirstLine == true)
		{
			//JupTrim(szLine);
			//g_pOP->LogInfo(-1, __FUNCTION__, "%s", szLine);
			bFirstLine = false;
		}

		viPrintf(session.vi, (char *)"%s\n", szLine);
		//QThread::msleep(10);
		Sleep(10);
	}
	fclose(fp);

	//g_pOP->LogInfo(-1, __FUNCTION__, "Script Loading Completed");

	return true;
}

bool SmuControl::WriteScriptToDMM(std::string szSessionNm)
{
	char szFile[260];
	VisaSession session = m_mapSession[szSessionNm];

	if (szSessionNm == "DMM6")
		sprintf_s(szFile, _countof(szFile), DMMFile_INI);
	else if (szSessionNm == "DMM7")
		sprintf_s(szFile, _countof(szFile), RMTDMM_LUA);/*"D:\\Screen\\Config\\RMT_DMM.lua"*/

	viClear(session.vi);

	// WriteFromFile
	FILE *fp;
	char szLine[COMMAND_MAX_SIZE];
	bool bFirstLine = true;

	fopen_s(&fp, szFile, "r");
	while (!feof(fp))
	{
		memset(szLine, 0, sizeof(szLine));
		fgets(szLine, _countof(szLine), fp);

		if (bFirstLine == true)
		{
			//JupTrim(szLine);
			bFirstLine = false;
		}

		viPrintf(session.vi, (char *)"%s\n", szLine);
		//QThread::msleep(10);
		Sleep(10);
	}

	fclose(fp);
	
	return true;
}

void SmuControl::loadParameterFromFile()
{
	m_VisaParasInfor = new JIniSettings("D:\\EVMS\\ENV\\Config\\InspectInfor.ini");
	m_VisaParasInfor->ReadSection("SFR60_SETTING", m_AlphaSetting);
}

bool SmuControl::smuIsConnected()
{
	return m_smuIsConnected;
}
