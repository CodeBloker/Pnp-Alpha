#include "INIManager.h"
#include "Common/JIniSettings.h"
#include "ParasDefine.h"
#include <iostream>

ScreenINI::ScreenINI()
{
}

ScreenINI::~ScreenINI()
{
}

bool ScreenINI::LoadIni(std::string path)
{
	if (!m_sectionCmdMap.empty())
	{
		m_sectionCmdMap.clear();
	}

	//JIniSettings setting(path);
	//setting.SetUnicode(true);

	std::vector<std::string> list;
	std::ifstream file;
	file.open(path, std::ios::in);
	if (file.is_open()) 
	{
		std::string strLine;
		while (!file.eof()) 
		{
			getline(file, strLine);
			list.push_back(strLine);
		}

		//QFile qfile(path);
		//if (qfile.is_open())
		//{
		m_sIniPath = path;

		//ByteArray arr = qfile.readAll();
		//arr.replace('\r', "");
		//ByteArrayList list = arr.split('\n');

		bool bSectionStart = false;
		std::string sectionName;

		for (auto var : list)
		{
			if (var.empty() || var._Starts_with("//"))
				continue;

			int nStartDesc = var.find("//");
			if (nStartDesc >= 0)
			{
				var = var.substr(0, nStartDesc);
			}

			if (bSectionStart == false)
			{
				//if (var.find_first_of('[') && var.find_last_of(']'))
				if ((var.rfind('[', 0) == 0) && (var.rfind(']') == (var.length() - 1)))
				{
					bSectionStart = true;
					sectionName = var;
				}
			}
			else if (var._Starts_with("[END]"))
			{
				bSectionStart = false;
			}
			else
			{
				//var.replace(var.begin(), var.end(), '\t', ' ');
				Jup::Replace(var, "\t", " ");
				var.erase(var.find_last_not_of("\r\t\n ") + 1);
				if (var._Starts_with("Version"))
				{
					StringList list = Jup::Split(var, ' ');
					if (list.size() > 1 && m_sVersion.empty())
					{
						m_sVersion = list.at(1);
					}
				}
				m_sectionCmdMap[sectionName].push_back(var);
			}
		}
		m_bLoadIni = true;
		file.close();
	}
	else
	{
		m_bLoadIni = false;
	}
	return m_bLoadIni;
}

bool ScreenINI::IsLoadIni()
{
	return m_bLoadIni;
}

std::string ScreenINI::GetVersion()
{
	return m_sVersion;
}

eDecodeResult ScreenINI::DecodeSection(std::string sectionName, std::vector<CommandPair>& cmdList)
{
	eDecodeResult eResult = eResult_OK;
	if (m_bLoadIni == false)
	{
		eResult = eResult_NullInIFile;
		return eResult;
	}

	if (!m_sectionCmdMap.count(sectionName))
	{
		eResult = eResult_NullSection;
		return eResult;
	}

	std::vector<CommandPair> lCmd;

	std::vector<std::string> list = m_sectionCmdMap[sectionName];
	int dataCount = list.size();
	for (int i = 0; i < dataCount; i++)
	{
		std::string str = m_sectionCmdMap[sectionName].at(i);
		int size = str.size();

		int cmdEnd = -1;
		int dataStart = -1;
		for (int j = 0; j < size; j++)
		{
			if (cmdEnd == -1)
			{
				if (str[j] == '\t' || str[j] == ' ')
				{
					cmdEnd = (int)j;
				}
			}
			else if (dataStart == -1)
			{
				if (str[j] != '\t' && str[j] != ' ')
				{
					dataStart = (int)j;
					break;
				}
			}
		}

		if (cmdEnd != -1 && dataStart != -1)
		{
			int cmdLength = cmdEnd;
			int dataLength = size - dataStart;

			std::string strCmd = str.substr(0, cmdLength);
			std::string strData = str.substr(dataStart, dataLength);

			strCmd = trim(strCmd);
			strData = trim(strData);

			CommandPair cmd;
			if (strCmd.size() >= 4 && strCmd._Starts_with("0x"))
			{
				cmd.first = "I2C_W";
				cmd.second = strCmd + " " + strData;
			}
			else
			{
				cmd.first = strCmd;
				cmd.second = strData;
			}

			lCmd.push_back(cmd);
		}
	}

	cmdList = lCmd;
	eResult = lCmd.size() > 0 ? eResult_OK : eResult_Fail;

	return eResult;
}

DutParameterINI::DutParameterINI()
{
	loadParameter();
}

void DutParameterINI::loadParameter()
{
	m_screenIni = new ScreenINI();
	m_screenIni->LoadIni(SCREEN_INI);

	m_screenTxIni = new ScreenINI();
	m_screenTxIni->LoadIni(TXRegFile_INI);

	//m_screenRxIni = new ScreenINI();
	//m_screenRxIni->LoadIni(RXRegFile_INI);

	//m_screenFFBLIni = new ScreenINI();
	//m_screenFFBLIni->LoadIni(FFBLRegFile_INI);

	//m_StationIni = new JIniSettings(STATION_INFO_INI);
	//m_StationIni->ReadSection("TESTINFO", m_StationTestInfo);
	//m_StationIni->ReadSection("STATION", m_StationInfo);

	//INSPECTORINFOR_INI
	m_TesterResourceInfor = new JIniSettings(INSPECTORINFOR_INI);
	m_TesterResourceInfor->ReadSection("STATION_VISION", m_StationVisionSetting);
	m_TesterResourceInfor->ReadSection("DIL_TEST", m_DILSetting);
	m_TesterResourceInfor->ReadSection("LIV_TEST", m_LIVSetting);
	m_TesterResourceInfor->ReadSection("FFBL_SETTING", m_FFBL_Config);
	m_TesterResourceInfor->ReadSection("FFBL_ITEMLIST", m_FFBLImageCount);
	m_TesterResourceInfor->ReadSection("FFBL_NameLIST", m_FFBLImageNameList);
	m_TesterResourceInfor->ReadSection("DPTW_TEST", m_DPTWSetting);
	m_TesterResourceInfor->ReadSection("STROBETEST_SETTING", m_StrobeBoardSetting);
	m_TesterResourceInfor->ReadSection("HVS_HW", m_BanffPinPowerSetting);
	m_TesterResourceInfor->ReadSection("CURRENT_TEST", m_BanffDynamicOffset);
	m_TesterResourceInfor->ReadSection("CURRENT_TEST_STANDBY_500uA", m_BanffStandbyOffset_500uA);
	m_TesterResourceInfor->ReadSection("CURRENT_TEST_STANDBY_5mA", m_BanffStandbyOffset_5mA);
	m_TesterResourceInfor->ReadSection("OS_TEST", m_BanffOSTESTOffset);
	m_TesterResourceInfor->ReadSection("SFR20_SETTING", m_SFR20Setting);
	m_TesterResourceInfor->ReadSection("SFR60_SETTING", m_SFR60Setting);
	m_TesterResourceInfor->ReadSection("SFR25_SETTING", m_SFR25Setting);
	m_TesterResourceInfor->ReadSection("RMT_TEST", m_RMTSetting);
	m_TesterResourceInfor->ReadSection("STATION_TEC", m_StationTECSetting);
	m_TesterResourceInfor->ReadSection("TECTEMP_SET", m_TECTempSetting);
	m_TesterResourceInfor->ReadSection("Station_TX_Limit", m_StationTxLimit);
	m_TesterResourceInfor->ReadSection("Station_RX_Limit", m_StationRxLimit);


	//ERRORCODE
	//m_ErrorParser = new INIFileParser(ERRORCODE_INI, false);
	m_ErrorParser = new JIniSettings(ERRORCODE_INI);
	m_ErrorParser->ReadSection("Error_code", m_ErrorCodeSetting);

	//FFBL 工站需要的DLL算法参数
	m_CMBUIni = new JIniSettings(CMBU_INI);

	//m_SMU_SFR60 =m_SFR60Setting.GetString("SMU_SFR60_Num", "SMU1"); //"SMU1";
	m_SMU_SFR60 = m_SFR60Setting["SMU_SFR60_Num"]; //"SMU1";
	//m_SMU_SFR20 = m_SFR20Setting.GetString("SMU_SFR20_Num", "SMU5"); //"SMU5";
	m_SMU_SFR20 = m_SFR20Setting["SMU_SFR20_Num"]; //"SMU5";
	m_SMU_SFR25 = m_SFR25Setting["SMU_SFR25_Num"]; //"SMU9";
	m_SMU_DIL = m_LIVSetting["SMU_LIV2_Num"]; //"SMU7";
	m_SMU_LIV = m_LIVSetting["SMU_LIV_Num"]; //"SMU3";

	m_DMM_LIV = m_LIVSetting["DMM_LIV_Num"]; //"DMM6";
	m_DMM_RMT = m_RMTSetting["DMM_RMT_Num"]; //"DMM7";
}
