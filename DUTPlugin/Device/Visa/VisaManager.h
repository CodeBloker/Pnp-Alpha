/*
VISAManager.h
*/
#pragma once

#include "Visa/VisaCaller.h"
#include <string>
#include <map>

#define VISA_BUFFER				32768

// Structure of each measuring instrument
struct VisaSession
{
	ViSession vi;				// Fragments of each instrument
	char szPrefix[32];			// The instrument command language prefix (node[0]Etc)
	bool bCopy;					// Not an actual session, but a replicated session
};

class VisaManager
{
public:
	VisaManager();	
	~VisaManager();

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
	ViSession m_defaultRM;
	std::map<std::string, VisaSession> m_mapSession;
};