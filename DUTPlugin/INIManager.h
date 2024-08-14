#pragma once
#include <string>
#include <vector>
#include <map>
#include "Common/JIniSettings.h"

using SectionCmdMap = std::map<std::string, std::vector<std::string>>;
using CommandPair = std::pair<std::string, std::string>;
using INIData = std::map<std::string, std::string>;

enum eDecodeResult
{
	eResult_OK,
	eResult_Fail,
	eResult_NullSection,
	eResult_NullInIFile,
};

class ScreenINI
{
public:
	ScreenINI();
	~ScreenINI();

	bool LoadIni(std::string path);
	bool IsLoadIni();
	std::string GetVersion();

	eDecodeResult DecodeSection(std::string sectionName, std::vector<CommandPair> & cmdList);

private:
	bool m_bLoadIni = false;
	std::string m_sVersion;
	std::string m_sIniPath;

	SectionCmdMap m_sectionCmdMap;
};

class DutParameterINI
{
public:
	DutParameterINI();
	~DutParameterINI() {}

	void loadParameter();

public:
	// 解析标准INI文件对象（每个对象关联一个INI文件）
	JIniSettings *m_CMBUIni;
	JIniSettings *m_TesterResourceInfor;
	JIniSettings *m_ErrorParser;
	//JIniSettings *m_StationIni;

	ScreenINI *m_screenIni;
	ScreenINI *m_screenTxIni;
	//ScreenINI *m_screenFFBLIni;
	ScreenINI *m_screenRxIni;

	// 解析非标准INI文件对象（每个对象关联一个INI文件）
	INIData m_FFBL_Config;
	INIData m_BanffPinPowerSetting;
	INIData m_FFBLImageCount;
	INIData m_FFBLImageNameList;
	INIData m_DPTWSetting;
	INIData m_StrobeBoardSetting;
	INIData m_BanffDynamicOffset;
	INIData m_BanffStandbyOffset_500uA;
	INIData m_BanffStandbyOffset_5mA;
	INIData m_BanffOSTESTOffset;
	INIData m_SFR20Setting;
	INIData m_SFR60Setting;
	INIData m_SFR25Setting;
	INIData m_RMTSetting;
	INIData m_StationTECSetting;
	INIData m_ErrorCodeSetting;
	INIData m_TECTempSetting;
	INIData m_StationVisionSetting;
	INIData m_StationTxLimit;
	INIData m_StationRxLimit;
	INIData m_StationTestInfo;
	INIData m_StationInfo;
	INIData m_DILSetting;
	INIData m_LIVSetting;

	std::string m_SMU_SFR60 = "SMU1";
	std::string m_SMU_SFR20 = "SMU1";
	std::string m_SMU_SFR25 = "SMU1";
	std::string m_SMU_DIL = "SMU1";
	std::string m_SMU_LIV = "SMU1";
	std::string m_DMM_LIV = "DMM1";
	std::string m_DMM_RMT = "DMM7";
};
