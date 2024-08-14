/*
VISAManager.h
*/
#pragma once

#include "VisaManager.h"
#include <vector>
#include "Common/JIniSettings.h"

// Structure of each measuring instrument
struct VisaSession
{
	ViSession vi;				// Fragments of each instrument
	char szPrefix[32];			// The instrument command language prefix (node[0]Etc)
	bool bCopy;					// Not an actual session, but a replicated session
};

struct SMU_READ_BUFFER_DATA
{
	double V_DOT = 0.0;
	double V_A = 0.0;
	double V_B = 0.0;
	double V_F = 0.0;
	double I_DOT = 0.0;
	double I_A = 0.0;
	double I_B = 0.0;
	double I_F = 0.0;
	double NTC_R = 0.0;
	double RMT_R = 0.0;

	void Clear()
	{
		*this = SMU_READ_BUFFER_DATA();
	}
};

class SmuControl
{
public:
	SmuControl();
	~SmuControl();

	static SmuControl*& GetInstance();

	//VISA
	bool smuIsConnected();
	bool OpenVISA(std::string session, std::string address, std::string prefix);
	bool fnSMUDevImpl();
	bool fnSMUDevDestory();
	bool fnSetUpSMU(std::string session);
	bool fnSetUpDMM(std::string session);
	void fnResetSMU(std::string session);
	bool SMU_ReadBuffer(std::string session, int nSocIndex, std::vector<SMU_READ_BUFFER_DATA> & buffer_data, std::string ReadBufferCommand = "");
	bool GetNtcOFF(std::string session, int nSocIndex, double* dTemper, double* dRValue);
	bool SMU_BufferClear(std::string session, int nSocIndex);
	bool SMU_Initialize(std::string session, int nSocIndex);
	bool fnGetNTCSMU(std::string session, int nSocIndex, double & Temperature);


//private:
	int OpenDevice();
	int CloseDevice();

	bool AddSession(std::string szName, std::string szConStr, std::string szPrefix, int nTimeout);
	bool CopySession(std::string szDestName, std::string szPrefix, std::string szSrcName);

	unsigned long GetDefaultRMNum() { return (unsigned long)m_defaultRM;}
	ViSession GetSession(std::string szName);

	bool ExecuteCommand(bool bAddPrefix, std::string szName, std::string szCommand);
	bool ExecuteCommand(bool bAddPrefix, std::string szName, const char* szCommand, ...);
	bool ReadResult(std::string szName, char* szResult, int cbLen);

	bool WriteScriptToSMU(std::string szSessionNm);
	bool WriteScriptToDMM(std::string szSessionNm);

private:
	void loadParameterFromFile();

private:
	ViSession m_defaultRM;
	std::map<std::string, VisaSession> m_mapSession;

	bool m_smuIsConnected = false;

	JIniSettings *m_VisaParasInfor;
	std::map<std::string, std::string> m_AlphaSetting;

	inline static SmuControl* m_SingleInstance = nullptr;
	inline static std::mutex m_Mutex;
};