#pragma once
#include "Device/Canyon/DeviceModuleGuadalupeCanyon.h"

class DutController
{
public:
	DutController();
	~DutController();

	static DutController*& GetInstance();

	//Canyon
	bool fnCanyouInit(int nSocIndex);
	bool fnCanyouPowerOff(int nSocIndex, std::string sDumpFilePrefix);
	bool fnCanyouPowerOnStreamingMode(int nSocIndex, std::string sTX_RegisterFile, std::string sRX_RegisterFile);
	bool fnCanyouPowerOnTriggerMode(int nSocIndex, std::string sTX_RegisterFile, std::string sRX_RegisterFile);
	bool fnSwitchTrrigerMode(int nSocIndex);
	bool DoMeasure_PowerOnTx(int nSocIndex, std::string section, bool bWithoutPowerControl = false);
	bool DoMeasure_ConfigDUTRx(int nSocIndex, std::string sectionName, std::string & result, bool bWithoutPowerControl = false);
	bool DoMeasure_ConfigDUTRx(int nSocIndex, std::string sectionName);

	int DoMeasure_ConfigDUTForCapture(int nSocIndex, std::string section, std::string & sCMDSMU);

	bool fnModuleCaptureImage(int nSocIndex, std::string station, std::string barcode, std::string FilePath, std::string fileName, std::string sDumpFilePrefix, bool iTriger = true);
	int fnSendOneTrigerSMU(std::string session, int nSocIndex, std::string command, std::string info, std::string sDumpFilePrefix);

	bool ReadTxASIC_Temper(int nSocIndex, double* pResult);
	bool ReadRTraceValue(int nSocIndex,UINT16* pRTrace, double* pRTraceOhm, std::string* pLog = NULL);
	bool fnGetRxTemperature(int nSocIndex, double & temperature);
	bool Read_Tx_ASIC_ID(int nSocIndex, std::string & tx);
	bool Read_Rx_ASIC_ID(int nSocIndex, std::string & rx);
	bool Read_Tx_ASIC_Trim(int nSocIndex, std::string & trim);
	bool fnReadRTraceValue(int nSocIndex, double * RTraceValue);
	bool fnReadPinFaultValue(int nSocIndex, std::string &pinFault1, std::string &pinFault2);
	bool fnAdjustIntergretionTime(int nSocIndex, WORD ValTime, std::string &ValTimeCheck, std::string &data147);

	// ¶ÁÐ´I2C
	bool fnReadI2CData(int nSocIndex, unsigned short nSlave, unsigned short nAddr, unsigned short nDataLen, unsigned char* pBuf, bool bAddr16 = false);
	bool fnWriteI2CData(int nSocIndex, unsigned short nSlave, unsigned short nAddr, unsigned short nDataLen, const unsigned char* pBuf, bool bAddr16 = false);

	// Switch (DOT FLOOD)
	bool switchTriggerLight(int nSocIndex, std::string section_name);


private:
	bool getCheckArmed();
	void setCheckArmed(int armed);
	double CalcNTCResistanceToTemperature(char * bufferData);

private:
	DeviceModuleGuadalupeCanyon m_BanffControl;

	inline static DutController* m_SingleInstance = nullptr;
	inline static std::mutex m_Mutex;
};

