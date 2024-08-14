#include "VisaManager.h"
#include <Windows.h>
#include "ParasDefine.h"

#define COMMAND_MAX_SIZE	1024
#define VISA_BUF_SIZE		32768

VisaManager::VisaManager()
{
}

VisaManager::~VisaManager()
{
}

int VisaManager::OpenDevice()
{
	m_defaultRM = NULL;
	if (viOpenDefaultRM(&m_defaultRM) != VI_SUCCESS)
		return 0;
	else
		return 1;
}

bool VisaManager::AddSession(std::string szName, std::string szConStr, std::string szPrefix, int nTimeout)
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

bool VisaManager::CopySession(std::string szDestName, std::string szPrefix, std::string szSrcName)
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

int VisaManager::CloseDevice()
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


ViSession VisaManager::GetSession(std::string szName)
{
	return m_mapSession[szName].vi;
}

bool VisaManager::ExecuteCommand(bool bAddPrefix, std::string szName, std::string szCommand)
{
	return ExecuteCommand(bAddPrefix, szName, szCommand.c_str());
}

bool VisaManager::ExecuteCommand(bool bAddPrefix, std::string szName, const char* szCommand, ...)
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

bool VisaManager::ReadResult(std::string szName, char* szResult, int cbLen)
{
	VisaSession session = m_mapSession[szName];
	
	ViStatus ret = viScanf(session.vi, (char *)"%t", szResult);

	if (ret != VI_SUCCESS)
		return false;
	else
		return true;	
}

bool VisaManager::WriteScriptToSMU(std::string szSessionNm)
{
	//char szFile[260];
	//VisaSession session = m_mapSession[szSessionNm];
	//sprintf_s(szFile, _countof(szFile), SMUFile_INI);

	//viClear(session.vi);

	//// WriteFromFile
	//FILE *fp;
	//char szLine[COMMAND_MAX_SIZE];
	//bool bFirstLine = true;

	////g_pOP->LogInfo(-1, __FUNCTION__, "SMU Script Loading Start");

	//fopen_s(&fp, szFile, "r");
	//while (!feof(fp))
	//{
	//	memset(szLine, 0, sizeof(char) * _countof(szLine));
	//	fgets(szLine, _countof(szLine), fp);

	//	if (bFirstLine == true)
	//	{
	//		//JupTrim(szLine);
	//		//g_pOP->LogInfo(-1, __FUNCTION__, "%s", szLine);
	//		bFirstLine = false;
	//	}

	//	viPrintf(session.vi, (char *)"%s\n", szLine);
	//	//QThread::msleep(10);
	//	Sleep(10);
	//}
	//fclose(fp);

	//g_pOP->LogInfo(-1, __FUNCTION__, "Script Loading Completed");

	return true;
}

bool VisaManager::WriteScriptToDMM(std::string szSessionNm)
{
	//char szFile[260];
	//VisaSession session = m_mapSession[szSessionNm];

	//if (szSessionNm == "DMM6")
	//	sprintf_s(szFile, _countof(szFile), DMMFile_INI);
	//else if (szSessionNm == "DMM7")
	//	sprintf_s(szFile, _countof(szFile), RMTDMM_LUA);/*"D:\\Screen\\Config\\RMT_DMM.lua"*/

	//viClear(session.vi);

	//// WriteFromFile
	//FILE *fp;
	//char szLine[COMMAND_MAX_SIZE];
	//bool bFirstLine = true;

	////g_pOP->LogInfo(-1, __FUNCTION__, "DMM Script Loading Start");

	//fopen_s(&fp, szFile, "r");
	//while (!feof(fp))
	//{
	//	memset(szLine, 0, sizeof(szLine));
	//	fgets(szLine, _countof(szLine), fp);

	//	if (bFirstLine == true)
	//	{
	//		//JupTrim(szLine);
	//		//g_pOP->LogInfo(-1, __FUNCTION__, "%s", szLine);
	//		bFirstLine = false;
	//	}

	//	viPrintf(session.vi, (char *)"%s\n", szLine);
	//	//QThread::msleep(10);
	//	Sleep(10);
	//}

	//fclose(fp);
	
	//g_pOP->LogInfo(-1, __FUNCTION__, "DMM Script Loading Completed");

	return true;
}