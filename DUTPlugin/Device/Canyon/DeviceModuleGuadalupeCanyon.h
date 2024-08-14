#pragma once

#include "JupCore.h"
#include <functional>
//#include <Windows.h>
//#include <opencv2/core/internal.hpp>
#include "INIManager.h"
#include <Windows.h>

typedef std::pair<std::string, std::string> CommandPair;

//DataMaxSize
#define DATA_MAX_X		1104
#define DATA_MAX_Y		1314

#define BANFF_TX_SLAVE_ADDRESS		0x64
#define BANFF_RX_SLAVE_ADDRESS		0x18

#ifndef ALIGNED_SIZE
//origin define at <align.h>
#define ALIGNED_SIZE(size, alignment) (((size) + (alignment)) & ~(alignment))
#endif

extern std::vector<std::string> split(const std::string &s, char delim);
extern std::string vecToString(std::vector<std::string> m_vec, std::string elems);
extern std::vector<std::string> fnGetRx_regAddr();



typedef struct RTraceData {
	double dRtrace_Mean_ADC = 0.0;
	double dRtrace_Mean = 0.0;
	double dRtrace_Max = 0.0;
	double dRtrace_Min = 0.0;
	double dRtrace_Range = 0.0;
	double dRtrace_Stdev = 0.0;
	double dRtrace_TSMC = 0.0;
	double dRtrace_Delta = 0.0;
} RTraceData;

class DeviceModuleGuadalupeCanyon
{
public:
	DeviceModuleGuadalupeCanyon();
	~DeviceModuleGuadalupeCanyon();

	void fnGetDllVersionFile(DWORD & v1, DWORD & v2);
	bool fnCanyonDLLInitialize(int nBoardindex);

	void BoardControl(int nBoardindex);
	bool Oscillator_Set(int nBoardindex);

	void Reset_High(int nBoardindex);
	void Reset_Low(int nBoardindex);

	void ENB_High(int nBoardindex);
	void ENB_Low(int nBoardindex);

	void VCLK_ByPass(int nBoardindex);
	void VCLK_Inv(int nBoardindex);

	void VSYNC_ByPass(int nBoardindex);
	void VSYNC_Inv(int nBoardindex);

	void MCLK_Off(int nBoardindex);

	void SetVCLKMode(bool bVCLK);
	bool GetVCLKMode(void);

	void SetVSYNCMode(bool bVSYNC);
	bool GetVSYNCMode(void);

	int GetMipiMode(void);

	bool ReadI2CData(int nBoardindex, unsigned short nSlave, unsigned short nAddr, unsigned short nDataLen, unsigned char* pBuf, bool bAddr16 = false);
	bool WriteI2CData(int nBoardindex, unsigned short nSlave, unsigned short nAddr, unsigned short nDataLen, const unsigned char* pBuf, bool bAddr16 = false);

	std::string I2cReadByte(int nBoardindex, bool bAddr16, unsigned short addr, int nDataLen); //读取 datalen的 //bAddr16  0x64 false,0x18 true
	bool I2cWrite16BitByte(int nBoardindex, bool bAddr16, unsigned short addr, unsigned short Data);//写 datalen = 2 的 //bAddr16  0x64 false,0x18 true

	//bAddr16:	false = 0x64 , true = 0x18
	bool WriteByte(int nBoardindex, bool bAddr16, unsigned short addr, unsigned char value, bool bVerify = true);
	bool WriteBit(int nBoardindex, bool bAddr16, unsigned short addr, int msb, int lsb, unsigned char value, bool bVerify = true);

	bool ReadByteVerify(int nBoardindex, bool bAddr16, unsigned short addr, unsigned char value);
	bool ReadBitVerify(int nBoardindex, bool bAddr16, unsigned short addr, int msb, int lsb, unsigned char value);

	bool ReadByte(int nBoardindex, bool bAddr16, unsigned short addr, unsigned char * value);
	bool ReadBit(int nBoardindex, bool bAddr16, unsigned short addr, int msb, int lsb, unsigned char * value);

	bool ReadBuffer(int nBoardindex, bool bAddr16, unsigned short addr, std::vector<unsigned char> & value);

	char toAscii(unsigned char ch);
	bool CheckDeviceIsActive(int nBoardindex);

	bool SaveToRaw16BitImg(const char * strFilename, unsigned char * pBuffer, int nWidth, int nHeight);
	bool fnGetFFBLDummyFrame(int nBoardindex);

	bool fnGetFFBLOneFrame(int nBoardindex, bool isSave, std::string station, std::string barcode, std::string FilePath, std::string fileName, BYTE* RawBuffer, bool is16Bit=false);
	bool fnGetFFBLExposureImg(int nBoardindex, bool isSave, std::string station, std::string barcode, std::string FilePath, std::string fileName, unsigned short * gpRaw10bitBuffer, bool is16Bit = true);
	double fnGetImgMean(PUSHORT pRawBuffer, int nWidth, int nHeight, int nROIWidth);
	bool fnGetFFBLOneFrame(int nBoardindex, bool isSave, std::string station, std::string barcode, std::string FilePath, std::string fileName, unsigned short* RawBuffer, bool is16Bit = false);

	void fnFireSync(int nBoardindex);

	bool fnGetOneFrame(int nBoardindex, std::string station, std::string barcode, std::string FilePath, std::string fileName, bool iShowImg = true);
	bool fnGetOneFrameWithoutTrigger(int nBoardindex, std::string station, std::string barcode, std::string FilePath, std::string fileName, bool iShowImg = true);
	bool fnSetLVDS_Start(int nBoardindex);
	bool fnSetLVDS_Stop(int nBoardindex);

	bool Read_Tx_ASIC_ID(int nBoardindex, std::vector<unsigned char> & readBuffer);
	bool Read_Tx_ASIC_Trim(int nBoardindex, std::vector<unsigned char> & readBuffer);
	bool fnReadTx_ASIC_Trim(int nBoardindex, std::string & TrimSN);
	bool fnReadRx_ASIC_ID(int nBoardindex, std::string & RxID);

	bool RegisterScriptParse(int nBoardindex, std::string scriptName, bool bParseOnly, const std::vector<CommandPair> & script);

	int fnPowerOnCanyouPinVoltSet(int nBoardindex, const char * sTX_RegisterFile, const char * sRX_RegisterFile);

	int fnPowerOnCanyouPinVoltSetForOSTest(int nSocIndex);

	bool fnPowerOnCanyouAfterRegister(int nSocIndex);

	bool fnSetModuleCheckSum(int nSocIndex, bool set);

	bool fnPowerOFF(int nBoardindex);

	bool ReadTxASIC_Temper(int nBoardindex, double* pResult); //virture??

	bool fnCheckRegValue(int nBoardindex, unsigned short &tempV1, unsigned short & tempV2);

	bool fnReadingBarCodeSN(int nBoardindex, std::string & output_sn);

	bool fnReadTxNVM(int nBoardindex, unsigned char* TxNVMData, const unsigned short  TxNVMSize);

	bool fnReadRxNVM(int nBoardindex, unsigned char * RxVMData, const unsigned short RxNVMSize);

	int Read_NVM_DATA(int nBoardindex, unsigned char OTPData[], int nReadLength, int nStartAddr, int ECC, int iMode);

	void WriteBin_NVM(std::string filename, unsigned char DATA[], unsigned short DataSize);

	bool NVMArrayToString(bool flag, std::string startAddr, unsigned char DATA[], unsigned short DataSize, std::string & address_list, std::string & data_list);

	void WriteCSV_NVM(std::string filename, std::string NVMAddr, std::string NVMData);

	bool fnReadTxREGNVM(int nBoardindex, std::string filename);

	bool fnReadRxREGNVM(int nBoardindex, std::string filename);

	bool fnReadRTraceValue(int nBoardIndex, unsigned short & RTraceValue);

	bool fnReadRtraceTSMC(int nBoardindex, float & RtraceRaw);

	bool fnGetRtrace_ADC(int nBoardindex, RTraceData & rTraceData);

	bool fnReadUserModeNTCNew(int nBoardindex, uint8_t * AddressGroup, int AddressGroupSize, DWORD * AddressData);

	bool fnReadUserModeNTCNewBak(int nBoardindex, uint8_t * AddressGroup, int AddressGroupSize, DWORD * AddressData);

	bool fnReadUserModeNTCNewGetOne(int nBoardindex, uint8_t AddressGroup, DWORD & AddressData);

	bool fnReadTX_NVM(int nBoardindex, std::string FileName);

	bool fnReadRx_reg(int nBoardindex, std::vector<std::string>& dataVecotrOut);

	bool fnReadRxTemperature(int nBoardindex, double& temperature);

	bool fnCheckHardBrick(int nBoardindex, std::string& b4Value);

	bool fnSaveAllTXDumpToCsv(int nBoardindex, std::string sInfo,std::string sFilePrefix);

	int fnSaveSimpleTXDumpToCsv(int nBoardindex, std::string sInfo, std::string sFilePrefix);

	BOOL SaveToRawImg(const char * strFilename, unsigned char * pBuffer, int sizeX, int sizeY);

	BOOL SaveToRawImg(const char * strFilename, unsigned short * pBuffer, int sizeX, int sizeY);

	void Make10BitMode(unsigned char * pImage, WORD * pDest, unsigned int nWidth, unsigned int nHeight);

	int	gnHeaderCnt = 4;
	int	gbChecksum_OnlyHWmode = 0;
	int	gbSaveChecksumFailRAW = 0;
	int	gbListOutOnlyCrcFail = 0;
	int	m_iMipiMode = 1;
	bool m_bVCLK = 0;				//V clock bypass/inverse
	bool m_bVSYNC = 0;				//V sync  bypass/inverse
	bool m_bENB = 1;				//Enable  high/low
	bool m_bRESET = 1;				//reset	  high/low	
	bool bPGMOSC = false;

	static const int TxNVMSize = (4 * 51);     //0x16~0x49
	static const int TxRegSize = (0xFF + 1);         //0x00~0xDB
	//static const int RxNVMSize = (0x400);				//0x0310 ~0x03ff
	static const int RxNVMSize = (0x070F - 0x0310 + 1);				//0x0310 ~0x07ff

public:
	bool fnOSTest(int nSocIndex, std::vector<float> &reading);
	bool fnDynamicReading(int nSocIndex, std::vector<float> &reading);
	bool fnStandbyReading(int nSocIndex, std::vector<float> &reading);
	bool fnDynamicOffset(int nSocIndex);
	bool fnStandbyOffset(int nSocIndex);

public:
	DutParameterINI* getParas() { return m_INI; }

private:
	DutParameterINI* m_INI;
};