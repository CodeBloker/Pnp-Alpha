#include "DutController.h"
#include "ParasDefine.h"
#include <Windows.h>

DutController::DutController()
{
}

DutController::~DutController()
{
}

DutController *& DutController::GetInstance()
{
	if (m_SingleInstance == nullptr) {
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (m_SingleInstance == nullptr) {
			m_SingleInstance = new (std::nothrow) DutController{};
		}
	}
	return m_SingleInstance;
}

bool DutController::fnCanyouInit(int nSocIndex)
{
	bool  ret = m_BanffControl.fnCanyonDLLInitialize(nSocIndex);
	return ret;
}

bool DutController::fnCanyouPowerOff(int nSocIndex, std::string sDumpFilePrefix)
{
	m_BanffControl.fnSaveAllTXDumpToCsv(nSocIndex % 4, "Before_PowerOFF", sDumpFilePrefix); //没有poweroff 80ms  已经poweroff 550ms ，通讯时间 1ms

	bool  ret = m_BanffControl.fnPowerOFF(nSocIndex);  //25ms
	return ret;
}

bool DutController::fnCanyouPowerOnStreamingMode(int nSocIndex, std::string sTX_RegisterFile, std::string sRX_RegisterFile)
{
	int status = m_BanffControl.fnPowerOnCanyouPinVoltSet(nSocIndex, sTX_RegisterFile.c_str(), sRX_RegisterFile.c_str());
	if (status <= 0) {
		return false; 
	}

	Sleep(50);//GPIO 上电需要延时 150  0712

	std::string powerOnSection = "[POWER_ON_ARMED]";
	if (!getCheckArmed())
	{
		powerOnSection = "[POWER_ON]";
	}
	bool ret = DoMeasure_PowerOnTx(nSocIndex, powerOnSection);
	if (!ret)
	{
		return false; 
	}

	std::string result2;
	bool ret2 = DoMeasure_ConfigDUTRx(nSocIndex, "[REGISTER_STREAM2]", result2);
	if (!ret2)
	{
		return false; 
	}

	bool status2 = m_BanffControl.fnPowerOnCanyouAfterRegister(nSocIndex);
	if (!status2)
	{
		return false; 
	}

	bool retLVDsStart = m_BanffControl.fnSetLVDS_Start(nSocIndex);
	if (!retLVDsStart)
	{
		return false; 
	}

	return (status && status2 && ret && ret2 && retLVDsStart);
}

bool DutController::fnCanyouPowerOnTriggerMode(int nSocIndex, std::string sTX_RegisterFile, std::string sRX_RegisterFile)
{
	int status = m_BanffControl.fnPowerOnCanyouPinVoltSet(nSocIndex, sTX_RegisterFile.c_str(), sRX_RegisterFile.c_str());
	if (status <= 0) {
		return false;
	}
	Sleep(50);//GPIO 上电需要延时 150  0712

	std::string powerOnSection = "[POWER_ON]";
	//if (!getCheckArmed())
	//{
	//	powerOnSection = "[POWER_ON]";
	//}
	bool ret = DoMeasure_PowerOnTx(nSocIndex, powerOnSection);
	if (!ret)
	{
		return false; //TODO
	}

	//std::string result2;
	//bool ret2 = DoMeasure_ConfigDUTRx(nSocIndex, "[REGISTER]", result2);
	//if (!ret2)
	//{
	//	return false; //TODO
	//}

	bool status2 = m_BanffControl.fnPowerOnCanyouAfterRegister(nSocIndex);
	if (!status2)
	{
		return false; //TODO
	}

	return (status && status2 && ret/* && ret2*/);
}

bool DutController::fnSwitchTrrigerMode(int nSocIndex)
{
	std::string result2;
	bool ret2 = DoMeasure_ConfigDUTRx(nSocIndex, "[REGISTER]", result2); //Hard ware trriger.
	if (!ret2)
	{
		return false; 
	}
	return true;
}

bool DutController::DoMeasure_PowerOnTx(int nSocIndex, std::string section, bool bWithoutPowerControl)
{
	int ret = 1;
	std::string strLog;
	std::string strT;
	std::string strSession, strScript;
	std::vector<CommandPair> cmdList;
	m_BanffControl.getParas()->m_screenTxIni->DecodeSection(section, cmdList);
	if (cmdList.empty())
	{
		char buf[128];
		sprintf(buf, "[SOCKET_%02d][DoMeasure_PowerOn] [%d] Invalid INI script.. Use the valid INI", nSocIndex + 1, section);
		//std::string strT = GetFormat("[SOCKET_%02d][DoMeasure_PowerOn] [%d] Invalid INI script.. Use the valid INI", nSocIndex + 1, section);
		std::string strT = buf;

		throw std::string("Invalid INI script.. Use the valid INI");
		return 0;
	}

	ret = m_BanffControl.RegisterScriptParse(nSocIndex, section, false, cmdList);
	if (!ret)
	{
		strT = "*****  ConfigDUTForCapture FAILEDURE *****\r\n";
	}
	else
	{
		strT = "ConfigDUTForCapture OK \r\n";
	}
	//3B BB 5D 44
	//34 45 48 3E
	return ret;
}

bool DutController::DoMeasure_ConfigDUTRx(int nSocIndex, std::string sectionName, std::string & result, bool bWithoutPowerControl)
{
	int ret = 1;
	std::string strLog;
	std::string strT;
	std::string strSession, strScript;
	std::vector<CommandPair> cmdList;
	m_BanffControl.getParas()->m_screenRxIni->DecodeSection(sectionName, cmdList);
	if (cmdList.empty())
	{
		char buf[128];
		sprintf(buf, "[SOCKET_%02d][DoMeasure_PowerOn] [%d] Invalid INI script.. Use the valid INI", nSocIndex + 1, sectionName);
		//std::string strT = GetFormat("[SOCKET_%02d][DoMeasure_PowerOn] [%d] Invalid INI script.. Use the valid INI", nSocIndex + 1, sectionName);
		std::string strT = buf;

		throw std::string("Invalid INI script.. Use the valid INI");
		return 0;
	}

	ret = m_BanffControl.RegisterScriptParse(nSocIndex, sectionName, false, cmdList);
	if (!ret)
	{
		strT = "*****  ConfigDUTForCapture FAILEDURE *****\r\n";
	}
	else
	{
		strT = "ConfigDUTForCapture OK \r\n";
	}

	return ret;
	return true;
}

bool DutController::DoMeasure_ConfigDUTRx(int nSocIndex, std::string sectionName)
{
	//int ret = 1;
	//std::string strLog;
	//std::string strT;
	//std::string strSession, strScript;
	//std::vector<CommandPair> cmdList;
	//m_BanffControl.getParas()->m_screenFFBLIni->DecodeSection(sectionName, cmdList);
	//if (cmdList.empty())
	//{
	//	char buf[128];
	//	sprintf(buf, "[SOCKET_%02d][DoMeasure_ConfigDUTRx] [%d] Invalid INI script.. Use the valid INI", nSocIndex + 1, sectionName);
	//	//std::string strT = GetFormat("[SOCKET_%02d][DoMeasure_ConfigDUTRx] [%d] Invalid INI script.. Use the valid INI", nSocIndex + 1, sectionName);
	//	std::string strT = buf;

	//	throw std::string("Invalid INI script.. Use the valid INI");
	//	return 0;
	//}
	//ret = m_BanffControl.RegisterScriptParse(nSocIndex, sectionName, false, cmdList);
	//if (!ret)
	//{
	//	strT = "*****  DoMeasure_ConfigDUTRx FAILEDURE *****\r\n";
	//}
	//else
	//{
	//	strT = "DoMeasure_ConfigDUTRx OK \r\n";
	//}
	//return ret;
	return true;
}

int DutController::DoMeasure_ConfigDUTForCapture(int nSocIndex, std::string section, std::string & sCMDSMU)
{
	int ret = 1;
	std::string value;
	bool ret0 = m_BanffControl.fnCheckHardBrick(nSocIndex, value);
	if (ret0)
	{
		return false;
	}

	std::string strLog;
	std::string strT;
	std::string sectionName = section;
	std::string strSession, strScript;
	std::vector<CommandPair> cmdList;
	m_BanffControl.getParas()->m_screenTxIni->DecodeSection(sectionName, cmdList);
	if (cmdList.empty())
	{
		throw std::string("Invalid INI script.. Use the valid INI");
	}

	for (CommandPair var : cmdList)
	{
		if (var.first == "SMU" && var.second.find("Drive")) {
			strScript = var.second;
		}
	}
	sCMDSMU = strScript;

	ret = m_BanffControl.RegisterScriptParse(nSocIndex, sectionName, false, cmdList);
	if (!ret)
	{
		strT = "*****  ConfigDUTForCapture FAILEDURE *****\r\n";
	}
	else
	{
		strT = "ConfigDUTForCapture OK \r\n";
		ret = 1;
	}
	return ret;// ret; //TODO 
}

bool DutController::fnModuleCaptureImage(int nSocIndex, std::string station, std::string barcode, std::string FilePath, std::string fileName, std::string sDumpFilePrefix, bool iTriger)
{
	bool ret = false;
	bool iShowImg = true;
	if (iTriger)
	{
		ret = m_BanffControl.fnGetOneFrame(nSocIndex, station, barcode, FilePath, fileName, iShowImg);
	}
	else
	{
		ret = m_BanffControl.fnGetOneFrameWithoutTrigger(nSocIndex, station, barcode, FilePath, fileName, iShowImg);
	}


	if (sDumpFilePrefix.length() <= 0)
	{
		return ret;
	}
	std::string section = fileName;
	section.replace(section.begin(), section.end(), ".raw", "");
	std::vector<std::string> fileNames = Jup::Split(section, "_");
	int listLength = fileNames.size();
	if (listLength >= 2)
	{
		//section = QString("%1-%2").arg(fileNames.at(listLength - 2)).arg(fileNames.at(listLength - 1));
		section = fileNames.at(listLength - 2) + "-" + fileNames.at(listLength - 1);
	}
	if (sDumpFilePrefix.length() > 0)
	{
		bool status = m_BanffControl.fnSaveSimpleTXDumpToCsv(nSocIndex, ("After Capture " + section), sDumpFilePrefix);
		if (status == false)
		{
			//return false;
		}
	}
	return ret;
}

int DutController::fnSendOneTrigerSMU(std::string session, int nSocIndex, std::string command, std::string info, std::string sDumpFilePrefix)
{
	bool ret = true;
	//std::string strSession, strScript;
	//strSession = session;
	//strScript = command;
	//if (!PC4())
	//{
	//	std::string startTime;
	//	device::SMUResponse reply;
	//	ret = g_pCOMM->m_grpcToPC4.ExecuteSMU(nSocIndex, strSession, strScript, reply);

	//	bool status = m_BanffControl.fnSaveSimpleTXDumpToCsv(nSocIndex, Format("SendOneTrigerSMU %s", info.c_str()), sDumpFilePrefix);
	//	if (status == false)
	//	{
	//		//return false;
	//	}
	//	return ret;
	//}

	//ret = g_pDEV->m_Visa.ExecuteCommand(FALSE, strSession, strScript);

	return  ret;
}

bool DutController::ReadTxASIC_Temper(int nSocIndex, double * pResult)
{
	*pResult = 0.0;
	bool bRet = true;

	bRet = m_BanffControl.ReadTxASIC_Temper(nSocIndex, pResult);

	return bRet;
}

bool DutController::ReadRTraceValue(int nSocIndex, UINT16 * pRTrace, double * pRTraceOhm, std::string * pLog)
{
	bool bRet = 0;
	unsigned short ADC_READOUT;
	double RPU = 332000;
	bool status = m_BanffControl.fnReadRTraceValue(nSocIndex, ADC_READOUT);
	double ADC_V = (double)(1.5 / 4095) * ADC_READOUT;
	double RTraceValue = ADC_V * RPU / (1.5 - ADC_V);

	ADC_READOUT = ADC_READOUT / 1000.0;
	RTraceValue = RTraceValue / 1000.0;

	*pRTrace = ADC_READOUT;
	*pRTraceOhm = RTraceValue;  //RPD * (1.5 - ADC_V) / ADC_V;

	return bRet;
}

bool DutController::fnGetRxTemperature(int nSocIndex, double & temperature)
{
	bool status = false;
	double temp;

	status = m_BanffControl.fnReadRxTemperature(nSocIndex, temp);
	temperature = temp;

	return status;
}

bool DutController::Read_Tx_ASIC_ID(int nSocIndex, std::string & tx)
{
	std::vector<unsigned char> readBuffer;
	bool ret = m_BanffControl.Read_Tx_ASIC_ID(nSocIndex, readBuffer);

	int size = readBuffer.size();
	std::string txValue = "0x";
	if (size > 0)
	{
		for (size_t i = 0; i < size; i++)
		{
			unsigned char buf = readBuffer.at(i);
			char strVal[64];
			sprintf(strVal, "%s%02X", txValue.c_str(), buf);
			//txValue = Format("%s%02X", txValue.c_str(), buf);
			txValue = strVal;
		}
	}
	tx = txValue;
	return ret;
}

bool DutController::Read_Rx_ASIC_ID(int nSocIndex, std::string & rx)
{
	std::string txValue = "";
	bool ret = m_BanffControl.fnReadRx_ASIC_ID(nSocIndex, txValue);
	rx = txValue;

	return ret;
}

bool DutController::Read_Tx_ASIC_Trim(int nSocIndex, std::string & trim)
{
	bool ret = m_BanffControl.fnReadTx_ASIC_Trim(nSocIndex, trim);
	return ret;
}

bool DutController::fnReadRTraceValue(int nSocIndex, double * RTraceValue)
{
	unsigned short ADC_READOUT;
	double RPU = 332000;

	bool status = m_BanffControl.fnReadRTraceValue(nSocIndex, ADC_READOUT);
	double ADC_V = (double)(1.5 / 4095) * ADC_READOUT;
	*RTraceValue = ADC_V * RPU / (1.5 - ADC_V);

	ADC_READOUT = ADC_READOUT / 1000.0;
	*RTraceValue = *RTraceValue / 1000.0;

	return status;
}

bool DutController::fnReadPinFaultValue(int nSocIndex, std::string & pinFault1, std::string & pinFault2)
{
	std::string value1 = "";
	std::string value2 = "";
	unsigned short uPinFault_1, uPinFault_2;
	bool ret = m_BanffControl.fnCheckRegValue(nSocIndex, uPinFault_1, uPinFault_2);
	//value1 = to_string(uPinFault_1);// Format("0x%X", uPinFault_1);
	//value2 = to_string(uPinFault_2);// Format("0x%X", uPinFault_2);	
	char buf[32];
	sprintf(buf, "0x%X", uPinFault_1);
	value1 = buf;// Format("0x%X", uPinFault_1);
	memset(&buf, 0, sizeof(buf));
	sprintf(buf, "0x%X", uPinFault_2);
	value2 = buf;// Format("0x%X", uPinFault_2);
	pinFault1 = value1;
	pinFault2 = value2;
	return ret;
}

bool DutController::fnAdjustIntergretionTime(int nSocIndex, WORD ValTime, std::string & ValTimeCheck, std::string & data147)
{
	return false;

	// 0x18  0x146 
	unsigned short reg_0x146 = 0x146;
	//ret_write = mCanyonBanff.WriteI2C_16_Bit(nSocIndex, BANFF_RX_SLAVE_ADDRESS, BANFF_RX_INTERGRETION_TIME_ADDR, ValTime);
	//ValTimeCheck = mCanyonBanff.I2cRead(nSocIndex, strSlave, strAddrRead_3, nAddrLen, nDataLen);
	bool ret_write = m_BanffControl.I2cWrite16BitByte(nSocIndex, true, reg_0x146, ValTime);
	std::string value = m_BanffControl.I2cReadByte(nSocIndex, true, reg_0x146, 2);
	ValTimeCheck = value;
	data147 = m_BanffControl.I2cReadByte(nSocIndex, true, 0x147, 2);

	Sleep(100); //500  200  0712
	return ret_write;
}

bool DutController::fnReadI2CData(int nSocIndex, unsigned short nSlave, unsigned short nAddr, unsigned short nDataLen, unsigned char * pBuf, bool bAddr16)
{
	return m_BanffControl.ReadByte(nSocIndex, bAddr16, nAddr, pBuf);
}

bool DutController::fnWriteI2CData(int nSocIndex, unsigned short nSlave, unsigned short nAddr, unsigned short nDataLen, const unsigned char * pBuf, bool bAddr16)
{
	return m_BanffControl.WriteByte(nSocIndex, bAddr16, nAddr, *pBuf);
}

bool DutController::switchTriggerLight(int nSocIndex, std::string section_name)
{
	std::string section = "";
	if (section_name == "DOT")
	{
		section = "[SWITCH_TO_DOT]";
	}
	else if (section_name == "FLOOD")
	{
		section = "[SWITCH_TO_FLOOD]";
	}
	std::vector<CommandPair> cmdList;
	m_BanffControl.getParas()->m_screenTxIni->DecodeSection(section, cmdList);
	if (cmdList.empty())
	{
		char buf[128];
		sprintf(buf, "[SOCKET_%02d][DoMeasure_PowerOn] [%d] Invalid INI script.. Use the valid INI", nSocIndex + 1, section);
		std::string strT = buf;

		throw std::string("Invalid INI script.. Use the valid INI");
		return false;
	}
	return m_BanffControl.RegisterScriptParse(nSocIndex, section, false, cmdList) ? true : false;
}

bool DutController::getCheckArmed()
{
	std::string value = m_BanffControl.getParas()->m_TesterResourceInfor->ReadString("POWERON_SET", "POWERON_ARMED", "0");
	bool armed = atoi(value.c_str());
	return armed;
}

void DutController::setCheckArmed(int armed)
{
	std::string section = "POWERON_SET";
	std::string key = "POWERON_ARMED";
	std::string value = std::to_string(armed);
	m_BanffControl.getParas()->m_TesterResourceInfor->WriteString(section, key, value);
}

double DutController::CalcNTCResistanceToTemperature(char * bufferData)
{
	char *next_token = NULL;
	char *strToken = NULL;
	if (bufferData == NULL)
	{
		return 0;
	}
	std::string buffer = bufferData;
	if (buffer.find(",") || buffer.find("e-"))
	{
		return 0;
	}
	strToken = strtok_s(bufferData, "e+", &next_token);
	double Rexp = atof(strToken);
	//mData->mLogEvent->fnWriteLogAndShowui((LOG_STATION)nSocIndex, INFO, __FUNCTION__, "SMU getNTC Rexp:" + mData->mCommon->ToString(Rexp) );

	//添加电阻值换算方法在这里

	double B = 3435;
	double R0 = 10000;
	double T0 = 298.15;
	double scale = 1000.0;
	int  next = atof(next_token);
	//mData->mLogEvent->fnWriteLogAndShowui((LOG_STATION)nSocIndex, INFO, __FUNCTION__, "SMU getNTC Rexp:" + mData->mCommon->ToString(Rexp) + "e+" + mData->mCommon->ToString(next));
	if (next != 3)
	{
		scale = 1;
		for (size_t i = 0; i < next; i++)
		{
			scale = scale * 10;
		}
	}
	/*double Rexp = 9.432400;*/  //还可以用 strtod() 方法直接把char[] 转换成 浮点数
	double Temperature = 1 / (1.0 / B * log(Rexp * scale / R0) + 1.0 / T0) - 273.15;
	return Temperature;
}
