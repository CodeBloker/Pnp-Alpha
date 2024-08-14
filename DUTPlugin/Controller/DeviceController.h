/************************************************************************
* Filename     :  DeviceController.h
* Content      :  This file contains the defines necessary to use the
                  instance of IO device management class.

* Comments     :  There may be some definitions that will be provided to
				  use of IO device management class.
*************************************************************************/

#pragma once

#include <QObject>
#include "JupImport.h"
#include "ParamController.h"
#include "Visa/VisaManager.h"
#include "Cas/Cas.h"
#include "Vision/CameraDIL.h"
#include "Canyon/DeviceModuleGuadalupeCanyon.h"
#include "FFBLControl/FFBLControl.h"
#include "FFBLControl/FFBLAlgorithm.h"
#include "FFBLControl/LGIT/FFBLAlgorithm_LGIT.h"
#include "FFBLControl/DPBU/FFBLAlgorithm_DPBU.h"

#include "MvsCamera/MvsCamera.h"
#include "publicDLL/publicDLL.h"

#include "wfDemo/wfManager.h"
#include "DTPW/DTPW.h"
#include "MeasureStrobe/MeasureStrobe.h"
#include "SerialTEC/CSerialPortTEC.h"
#include "LightPanelSouce/CPanelLight.h"
#include "Define/wfDemo_SFR.h"

#define CANYON_CAPTURE_SLEEP		(500) //500  700
#define CANYON_CAPTURE_SLEEP_SFR25		(550) //500  700

#define MTCP_HEAD_LENGTH sizeof(tMTCP_header)
#define MTCP_REQ_LENGTH sizeof(tMTCP_payload_GENL_REQ)

#include "MIL/Mil.h"
typedef struct _tagMILInstance
{
	MIL_ID milApplication;		// Application identifier.
	MIL_ID milSystem;			// System Identifier.
	MIL_ID milDisplay;			// Display identifier.
} MILInstance, *PMILInstance;

typedef enum DUTIMGNAME
{
	ST200MTFIMG = 0,
	ST200DOTIMG,
	ST200DOTAIMG,
	ST200DOTBIMG,
	ST200DOTABIMG,
	ST200FLOODIMG,

	ST600MTFIMG,
	ST600DOTIMG,
	ST600DOTAIMG,
	ST600DOTBIMG,
	ST600DOTABIMG,
	ST600FLOODIMG,

	ST250MTFIMG,
	ST250DARKIMG,
	ST250DOTIMG,
	ST250DOTAIMG,
	ST250DOTBIMG,
	ST250DOTABIMG,
	ST250FLOODIMG,

}DUTIMGNAME;

typedef enum DUTIMGQTY
{

#ifdef kTESTBA

	//BA
	ST200DOTQTY = 10,//10,
	ST200DOTAQTY = 1,
	ST200DOTBQTY = 1,
	ST200DOTABQTY = 10,//10,
	ST200FLOODQTY = 5,//5,
	ST200MTFQTY = 10,// 10,
	
	ST600DOTQTY = 10,//10,
	ST600DOTAQTY = 1,
	ST600DOTBQTY = 1,
	ST600DOTABQTY = 10,//10,
	ST600FLOODQTY = 5,//5,
	ST600MTFQTY = 10,//10,
	
	ST250DOTQTY = 10,//10,
	ST250DOTAQTY = 1,
	ST250DOTBQTY = 1,
	ST250DOTABQTY = 10,//10,
	ST250FLOODQTY = 5,//5,
	//ST250MTFQTY = 1,//10,
	ST250DARKQTY = 10,//10,

#else

	//SP
	ST200DOTQTY = 11,
	ST200DOTAQTY = 1,
	ST200DOTBQTY = 1,
	ST200DOTABQTY = 0,
	ST200FLOODQTY = 0,
	ST200MTFQTY = 11,// 10,

	ST600DOTQTY = 11,//10,
	ST600DOTAQTY = 1,
	ST600DOTBQTY = 1,
	ST600DOTABQTY = 0,//10,
	ST600FLOODQTY = 0,//5,
	ST600MTFQTY = 11,//10,

	ST250FLOODQTY = 5,
	ST250DOTQTY = 1,
	ST250DOTAQTY = 0,
	ST250DOTBQTY = 0,
	ST250DOTABQTY = 1,
	ST250DARKQTY = 0,

#endif // kTESTBA

}DUTIMGQTY;

//using TestResults = std::pair<std::string, std::string>;
using ResultsArray = std::vector<std::pair<std::string, std::string>>;

extern std::string fnGetIMGName(DUTIMGNAME prefix, int suffix);

extern std::string to_string2dec(int num);
extern std::string fnGetJSONFileName(DUTIMGNAME prefix, int suffix);

extern bool add_csv_file_context(std::string csv_pah, list<string> context_v);
extern list<string> vec_to_list(vector<string> m_vec);
extern bool PushListToPacketList(vector<string> &m_context, vector<string> list, int count);
extern vector<string> split2(const std::string & s, std::string delim);
extern string getTimestamp();
//extern QString getQStringTimeStamp();
extern int appendContentListToCSV(QString filePath, QStringList list, bool iWithLimit = false);
extern int PushSMUBufferToQStringList(QStringList &contextList, QString buffer, int count);
extern int PushSMUBufferToQStringList(QStringList &contextList, QString buffer, int count);
extern std::string MergeJsonFormatToString(JSONFORMAT buffer);
extern double CalcNTCResistanceToTemperature(double Rexp);
//extern int HexToInt(std::string & hexString);
extern float hextoaeShutterTime(std::string & hexString);
extern QString getTimeIntervalStringFromStartTime(QDateTime startTime, QDateTime currentTime);


class DeviceController
{
public:
	DeviceController();
	~DeviceController();

	int Start();
	void Stop();
	
	//VISA
	bool fnSMUDevImpl();
	bool fnSMUDevDestory();

	bool OpenVISA(QString session, QString address, QString prefix);
	bool fnSetUpSMU(QString session);
	bool fnSetUpDMM(QString session);
	void fnResetSMU(QString session);

	bool SMU_ReadBuffer(QString session, int nSocIndex, QList<SMU_READ_BUFFER_DATA> & buffer_data, QString ReadBufferCommand = "");
	bool GetNtcOFF(QString session, int nSocIndex, double* dTemper, double* dRValue);

	bool SMU_BufferClear(QString session, int nSocIndex);
	bool SMU_Initialize(QString session, int nSocIndex);

	bool fnGetNTCSMU(QString session, int nSocIndex, double & Temperature);

	bool SendSMUCommandStart(int nSocIndex, QString session, QString script, QString & startTime, int timeRead);
	bool SendSMUResultStart(int nSocIndex, QString session, QString script, QString result, QString startTime, int timeRead);


	QList<QString> m_NVMShutterCmdStart;
	QMutex m_mutexNVMShutterCmdStart;
	QMap<QString, QString> m_mapShutterCmdResult;
	QMutex m_mutexShutterCmdResult;

	QList<QString> m_SFR25ShutterCmdStart;
	QMutex m_mutexSFR25ShutterCmdStart;

	bool SendSocketPowerOff(int nSocIndex);

	bool SendToStopTest();

	bool SendToLotStart(QString sConfig, QString sLot, QString sTestMode, QString sRunMode);

	bool SendToLotEnd();
	
	bool SendToSaveTxNVM(int nSocIndex, std::string sDumpFilePrefix);

	bool SendDILInspect(int nSocIndex, MtcpPacket packet);
	bool SendDILInspectResult(int nSocIndex, MtcpPacket packet);

	//RX Temperature,
	DTPW m_DPTW;
	MeasureStrobe m_StrobeIns;
	CSerialComm *m_DPTWSerial;
	CSerialComm mCSPort_StationTEC;
	CSerialPortTEC m_StationTEC;
	bool fnCollectiDevImpl();
	bool fnCollectiDevDestory();

	//LIV
	double LIVNtcBaLiv(double dRVal);
	void LIVTestCallBaLiv(BALIVInput &livInput, BALIVOutput &pLivOutput);

	//DIL,LIV流程	VISA + Canyon

	bool ContactCheck(QString session, int nSocIndex, SMU_READ_BUFFER_DATA & measureData);

	//Canyon
	bool fnCanyouInit(int nSocIndex);
	bool fnCanyouPowerOff(int nSocIndex, std::string sDumpFilePrefix);
	bool fnCanyouPowerOnStreamingMode(int nSocIndex, std::string sTX_RegisterFile, std::string sRX_RegisterFile);
	bool fnCanyouPowerOnTriggerMode(int nSocIndex, std::string sTX_RegisterFile, std::string sRX_RegisterFile);
	bool fnSwitchTrrigerMode(int nSocIndex);
	bool DoMeasure_PowerOnTx(int nSocIndex, std::string section, bool bWithoutPowerControl = false);
	bool DoMeasure_ConfigDUTRx(int nSocIndex, QString sectionName, QString & result, bool bWithoutPowerControl = false);
	bool DoMeasure_ConfigDUTRx(int nSocIndex, QString sectionName);

	int DoMeasure_ConfigDUTForCapture(int nSocIndex, QString section, string & sCMDSMU);

	bool fnModuleCaptureImage(int nSocIndex, QString station, QString barcode, std::string FilePath, std::string fileName, std::string sDumpFilePrefix, bool iTriger = true);
	int fnSendOneTrigerSMU(QString session, int nSocIndex, QString command, std::string info, std::string sDumpFilePrefix);

	bool ReadTxASIC_Temper(int nSocIndex, double* pResult);
	bool ReadRTraceValue(int nSocIndex, uInt16* pRTrace, double* pRTraceOhm, std::string* pLog = NULL);
	bool fnGetRxTemperature(int nSocIndex, double & temperature);
	bool Read_Tx_ASIC_ID(int nSocIndex, string & tx);
	bool Read_Rx_ASIC_ID(int nSocIndex, string & rx);
	bool Read_Tx_ASIC_Trim(int nSocIndex, string & trim);
	bool fnReadRTraceValue(int nSocIndex, double * RTraceValue);
	bool fnReadPinFaultValue(int nSocIndex, string &pinFault1, string &pinFault2);
	bool fnAdjustIntergretionTime(int nSocIndex, WORD ValTime, std::string &ValTimeCheck, std::string &data147);

	bool fnReadTECTemper(int nSocIndex, float & TECTempValue);

	bool setTECTemper(int nSocIndex, float &TECTempValue);
	bool setTECOffset(int nSocIndex, float & TECTempValue);

	bool fnOpenLightPanel(QString Station);
	bool fnShutDownLightPanel(QString Station);

	//ACL
	bool fnGetACLValue(double &Tx, double &Ty);

	//Mvs
	bool fnStationMvsImpl();
	bool fnStationMvsDestory();
	bool fnCapture(int nSocIndex, QString path);
	bool fnGetPictureDegree(int nSocIndex, QString file, QString & outPath, float &degree, bool bDebug = false);


	bool MeasureStrobe(int nSocIndex, float &fVol, float &fRaise, float &fFall, float &fDuration);

	//FFBL
	bool fnAE_process(int nSocIndex, QString sPatten, QString barcode, std::string FilePath, std::string fileName,int &ImgMean, int &AEInt);
	bool fnFreadUint16(const char *fullFileName, uint16_t V, unsigned short * data);
	bool fnStationFFBLImpl();
	bool fnStationFFBLDestory();

	//SFR
	bool fnStationSFRImpl();
	bool fnStationSFRDestory();

	//DIL
	bool fnStationDILImpl();
	bool fnStationDILDestory();

	//LIV
	bool fnStationLIVImpl();
	bool fnStationLIVDestory();


	//Matlab
	bool fnInitMatlabDLL();
	//bool fnSCSP20FromFile(string srcPath, string folderName, WFDEMO_SFR::TestResult & results);
	bool fnSCSPFromFile(string imageFile, string jsonFile, string rxnNvmFile, WFDEMO_SFR::TestResult &results);
	bool fnScreenFromFile(string srcPath, WFDEMO_SFR::TestResult &results);

	bool fnCreateJSONByName(JSONFORMAT stJSON, string filename);

public:
	float m_afLastRecvTemperature[8];

	//WFDEMO_SFR::TestResult ST250DotFomList;

	//FFBL station
	FFBLControl m_FFBLightControl;
	FFBLAlgorithm *m_FFBLAlgorithm;
	QMap<QString, FFBLAlgorithm*>  m_FFBLAlgorithmMap;


	FFBLAlgorithm_DPBU *m_FFBLAlgorithm_DPBU[8];
	//FFBLAlgorithm_LGIT *m_FFBLAlgorithm_LGIT;


	VisaManager m_Visa;

	struct SMUExecuteInfo
	{
		QString session;
		QString script;
		QString result;
		QString startTime;
		int timeRead;
		int socketIndex;
	};


	struct DPTWTemperature
	{
		int socketIndex = 0;
		float fsensorTemp = -1;
		float fDUTTemp = -1;
	};

	QMutex m_SMULock;
	QList<SMUExecuteInfo> m_SMUExecuteInfos;
	//QMap<QString, SMUExecuteInfo> m_SMUExecuteInfos;
	QMap<QString, SMUExecuteInfo> m_SMUResultInfos;


	QMutex m_DPTWTempLock;
	DPTWTemperature	TagDPTWTempSender;


	CCAS4 m_Cas;

	MILInstance m_mil;
	CameraDIL *m_pCam;

	DeviceModuleGuadalupeCanyon m_BanffControl;

	CWfManager m_wfDll;
	CClientSocket m_StrobeMeasure_Data;  //15
	CClientSocket m_StrobeMeasure_CMD;  //502
	CClientSocket m_RMTMeasure;

	CClientSocket m_ACL;

	CPanelLight m_PanelLight25;
	CPanelLight m_PanelLight60;
	CPanelLight m_PanelLight20;

	
	MvsCamera m_mvsCam;
};

extern void fnCloseHvsSocket(bool isSaveTXnvm = true);