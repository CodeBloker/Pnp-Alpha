#include "DeviceController.h"
#include "CommonDefine.h"
#include <iostream>
#include <sstream>
#include <io.h>
#include <string>
#include <vector>
#include <mutex>
#include <atomic>
#include <experimental/filesystem>
#include <fstream>
#include "JSON\rapidjson\document.h"
#include "JSON\rapidjson\prettywriter.h"
#include "JSON\rapidjson\stringbuffer.h"
#include "Define/Define_DUT.h"

using namespace WFDEMO_SFR;

#define ZXY_Change 1

DeviceController::DeviceController()
{
	
}

DeviceController::~DeviceController()
{
	
}

int DeviceController::Start()
{
	//string cam = m_mvsCam.findAll();
	//cam = cam.substr(0, cam.size() - 2);
	//bool ret = m_mvsCam.init(cam);
	//m_mvsCam.close();

	PC1() && fnStationMvsImpl();
	(PC2() || PC3()) && fnStationSFRImpl();
	PC4() && fnCollectiDevImpl();
	(PC2() || PC3()) && fnStationFFBLImpl();
	PC4() && fnSMUDevImpl();
	PC4() && fnStationDILImpl();
	PC4() && fnStationLIVImpl();
	
	return 1;
}

void DeviceController::Stop()
{
	//int res = m_Visa.CloseDevice();
	PC1() && fnStationMvsDestory();
	(PC2() || PC3()) && fnStationSFRDestory();
	PC4() && fnCollectiDevDestory();
	(PC2() || PC3()) && fnStationFFBLDestory();
	PC4() && fnSMUDevDestory();
	PC4() && fnStationDILDestory();
	PC4() && fnStationLIVDestory();

	g_pOP->LogInfo(-1, __FUNCTION__, "*******************************************PROGRAM STOP********************************************");
	g_pOP->LogInfo(0, __FUNCTION__,  "*******************************************PROGRAM STOP********************************************");
	g_pOP->LogInfo(1, __FUNCTION__,  "*******************************************PROGRAM STOP********************************************");
	g_pOP->LogInfo(2, __FUNCTION__,  "*******************************************PROGRAM STOP********************************************");
	g_pOP->LogInfo(3, __FUNCTION__,  "*******************************************PROGRAM STOP********************************************");

}

bool DeviceController::fnSMUDevImpl()
{
	QString session;
	QString sAddress;
	session = g_pINSP->m_SFR60Setting.GetString("SMU_SFR60_Num", "SMU1");
	sAddress = g_pINSP->m_SFR60Setting.GetString("SMU_SFR60_Addr", "TCPIP0::192.168.5.20::inst0::INSTR");
	bool res = this->OpenVISA(session, sAddress, "node[1]");
	//int res = this->OpenVISA(QString("SMU1"), "TCPIP0::192.168.5.20::inst0::INSTR", "node[1]");
	if (!res)
	{
		g_pOP->LogError(-1, __FUNCTION__, "Open SMU1 FAILED");
		MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Open SMU1 FAILED", 0);
	}
	Sleep(200);

	session = g_pINSP->m_LIVSetting.GetString("SMU_LIV_Num", "SMU3");
	sAddress = g_pINSP->m_LIVSetting.GetString("SMU_LIV_Addr", "TCPIP0::192.168.5.21::inst0::INSTR");
	res = this->OpenVISA(session, sAddress, "node[1]");
	//res = this->OpenVISA(QString("SMU3"), "TCPIP0::192.168.5.21::inst0::INSTR", "node[1]");
	if (!res)
	{
		g_pOP->LogError(-1, __FUNCTION__, "Open SMU3 FAILED");
		MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Open SMU3 FAILED", 0);
	}
	Sleep(200);

	session = g_pINSP->m_SFR20Setting.GetString("SMU_SFR20_Num", "SMU5");
	sAddress = g_pINSP->m_SFR20Setting.GetString("SMU_SFR20_Addr", "TCPIP0::192.168.5.22::inst0::INSTR");
	res = this->OpenVISA(session, sAddress, "node[1]");
	//res = this->OpenVISA(QString("SMU5"), "TCPIP0::192.168.5.22::inst0::INSTR", "node[1]");
	if (!res)
	{
		g_pOP->LogError(-1, __FUNCTION__, "Open SMU5 FAILED");
		MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Open SMU5 FAILED", 0);
	}
	Sleep(200);
	
	session = g_pINSP->m_LIVSetting.GetString("SMU_LIV2_Num", "SMU7");
	sAddress = g_pINSP->m_LIVSetting.GetString("SMU_LIV2_Addr", "TCPIP0::192.168.5.23::inst0::INSTR");
	res = this->OpenVISA(session, sAddress, "node[1]");
	//res = this->OpenVISA(QString("SMU7"), "TCPIP0::192.168.5.23::inst0::INSTR", "node[1]");
	if (!res)
	{
		g_pOP->LogError(-1, __FUNCTION__, "Open SMU7 FAILED");
		MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Open SMU7 FAILED", 0);
	}
	Sleep(200);
	
	session = g_pINSP->m_SFR25Setting.GetString("SMU_SFR25_Num", "SMU9");
	sAddress = g_pINSP->m_SFR25Setting.GetString("SMU_SFR25_Addr", "TCPIP0::192.168.5.24::inst0::INSTR");
	res = this->OpenVISA(session, sAddress, "node[1]");
	//res = this->OpenVISA(QString("SMU9"), "TCPIP0::192.168.5.24::inst0::INSTR", "node[1]");
	if (!res)
	{
		g_pOP->LogError(-1, __FUNCTION__, "Open SMU9 FAILED");
		MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Open SMU9 FAILED", 0);
	}
	Sleep(200);

	session = g_pINSP->m_LIVSetting.GetString("DMM_LIV_Num", "DMM6");
	sAddress = g_pINSP->m_LIVSetting.GetString("DMM_LIV_Addr", "TCPIP0::192.168.5.25::inst0::INSTR");
	res = this->OpenVISA(session, sAddress, "node[1]");
	//res = this->OpenVISA(QString("DMM6"), "TCPIP0::192.168.5.25::inst0::INSTR", "node[1]");
	if (!res)
	{
		g_pOP->LogError(-1, __FUNCTION__, "Open DMM6 FAILED");
		MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Open DMM6 FAILED", 0);
	}
	Sleep(200);

	session = g_pINSP->m_RMTSetting.GetString("DMM_RMT_Num", "DMM7");
	sAddress = g_pINSP->m_RMTSetting.GetString("DMM_RMT_Addr", "TCPIP0::192.168.5.26::inst0::INSTR");
	//res = this->OpenVISA(QString("DMM7"), "TCPIP0::192.168.5.26::inst0::INSTR", "node[1]");
	res = this->OpenVISA(session, sAddress, "node[1]");
	if (!res)
	{
		g_pOP->LogError(-1, __FUNCTION__, "Open DMM7 FAILED");
		MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Open DMM7 FAILED", 0);
	}
	Sleep(200);

	return 1;
}

bool DeviceController::fnSMUDevDestory()
{
	this->m_Visa.CloseDevice();
	return true;
}

bool DeviceController::fnFreadUint16(const char *fullFileName, uint16_t V, unsigned short * data)
{
	FILE *fp60 = NULL;
	uint16_t H = 0;
	fp60 = fopen(fullFileName, "rb+"); // NB

	fseek(fp60, 0L, SEEK_END);
	long flen = ftell(fp60);

	H = flen / sizeof(USHORT) / 1104;

	fseek(fp60, 0L, SEEK_SET);

	unsigned char *ByteBuf = new unsigned char[H*V * 2];
	if (fread(ByteBuf, sizeof(BYTE), H * V * 2, fp60) < 0)
	{
		return FALSE;
	}

	for (int i = 0; i < H * V; i++)
	{
		data[i] = ((ByteBuf[i * 2] << 2) + (ByteBuf[i * 2 + 1] >> 6));
	}
	fp60 = NULL;
	delete[] ByteBuf;
	//fclose(fp60);

	return true;
}

bool DeviceController::fnStationFFBLImpl()
{
	QVariantMap::const_iterator index;
	QVariantMap varMap = g_pINSP->m_FFBLImageCount.GetValues();

	for (index = varMap.constBegin(); index != varMap.constEnd(); ++index) {
		qDebug() << index.key() << ":" << index.value();

		m_FFBLAlgorithmMap[index.key()] = new FFBLAlgorithm(index.key());
	}


	for (int i = 0; i < 8; i++)
	{
		m_FFBLAlgorithm_DPBU[i] = new FFBLAlgorithm_DPBU();
	}

	//m_FFBLAlgorithm_LGIT = new FFBLAlgorithm_LGIT();



	return true;
}

bool DeviceController::fnStationFFBLDestory()
{
	for (int i = 0; i < 8; i++)
	{
		delete m_FFBLAlgorithm_DPBU[i];
	}

	
	//delete m_FFBLAlgorithm_LGIT;


	return true;
}

bool DeviceController::fnStationSFRImpl()
{
	fnCloseHvsSocket(false);

	return true;
}

bool DeviceController::fnStationSFRDestory()
{
	fnCloseHvsSocket();

	return true;
}

//..config
#define CAMERA60_FRAME_PERIOD	100000
#define CAMERA60_EXPOSURE_TIME	5000
#define CAMERA60_GAIN			100
#define CAMERA60_BLACK_LEVEL	0

bool DeviceController::fnStationDILImpl()
{

	//FFBL Light initail
	bool retFFBL = false;
	retFFBL = g_pDEV->m_FFBLightControl.fnOpenPort(g_pINSP->m_FFBL_Config.GetString("Serial_Port", "COM1"));
	if (retFFBL == false)
	{
		//msg box here

	}

	g_pDEV->m_FFBLightControl.fnSetLight(1, 0);
	g_pDEV->m_FFBLightControl.fnSetLight(2, 0);
	g_pDEV->m_FFBLightControl.fnSetLight(3, 0);
	g_pDEV->m_FFBLightControl.fnSetLight(4, 0);
	g_pDEV->m_FFBLightControl.fnSetLight(5, 0);
	g_pDEV->m_FFBLightControl.fnSetLight(6, 0);	

	MappAllocA("M_DEFAULT", M_DEFAULT, &(m_mil.milApplication));
	MappControl(m_mil.milApplication, M_ERROR, M_PRINT_DISABLE);
	MsysAllocA(m_mil.milApplication, "M_SYSTEM_HOST", M_DEV1, M_COMPLETE, &(m_mil.milSystem));

	m_pCam = new CameraDIL();

	int nFramePeriod = CAMERA60_FRAME_PERIOD;
	int nExpTime = CAMERA60_EXPOSURE_TIME;
	int nGain = CAMERA60_GAIN;
	int nBlackLevel = CAMERA60_BLACK_LEVEL;

	if (!m_pCam->Open())
	{
		MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Open DIL FAILED", 0);
	}
	else
	{
		m_pCam->SetRunMode(0);					Sleep(300);
		m_pCam->SetFramePeriod(nFramePeriod);	Sleep(200);
		m_pCam->SetExposure(nExpTime);			Sleep(100);
		m_pCam->SetGain(nGain);					Sleep(100);
		m_pCam->SetBlackLevel(nBlackLevel);		Sleep(100);

		g_pOP->LogInfo(-1, __FUNCTION__, "Camera Frame Peroid : %dus", m_pCam->GetFramePeriod());
		g_pOP->LogInfo(-1, __FUNCTION__, "Camera Integration Time : %dus", m_pCam->GetExposure());
		g_pOP->LogInfo(-1, __FUNCTION__, "Camera Gain : %.2f", (float)m_pCam->GetGain() * 0.01);
		g_pOP->LogInfo(-1, __FUNCTION__, "Camera Black Level : %d", m_pCam->GetBlackLevel());

		m_pCam->SetRunMode(1);
	}

	testMilInitCopy(m_mil.milApplication, m_mil.milSystem, m_mil.milDisplay);

	//testMilInit();

	return true;
}

bool DeviceController::fnStationDILDestory()
{
	MsysFree(m_mil.milSystem);
	MappFree(m_mil.milApplication);

	//testMilDestruct();

	return true;
}

bool DeviceController::fnStationLIVImpl()
{
	if (!m_Cas.OpenDevice())
	{
		MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Open CAS FAILED", 0);
	}
	return true;
}

bool DeviceController::fnStationLIVDestory()
{
	m_Cas.CloseDevice();
	return true;
}

std::string to_string2dec(int num) {
	char numchar[2];
	sprintf(numchar, "%01d", num);   ///从两位数又改为1位数。210729
	std::string str = numchar;
	return str;
}


bool DeviceController::fnInitMatlabDLL()
{
	uint16_t status = wfDLLStat::WF_OK;
	std::cout << "Welcome to wfDemo " << std::endl << std::endl;

	// DLL version check
	ResultsArray dllVersion;
	status = GetWFDLLVersion(dllVersion);
	if (status != wfDLLStat::WF_OK) {
		return wfDLLStat::WF_CPP_ERROR;
	}

	// List out the metrics
	for (const Result& el : dllVersion)
	{
		std::cout << el.first.c_str() << " : " << el.second.c_str() << std::endl;
	}
	// Running library check 
	ResultsArray libVersion;
	status = GetWFLibrary(libVersion);
	if (status != wfDLLStat::WF_OK) {
		return wfDLLStat::WF_ML_ERROR;
	}

	// List out the metrics 
	for (const Result& el : libVersion)
	{
		std::cout << el.first.c_str() << " : " << el.second.c_str() << std::endl;
	}

	return status == wfDLLStat::WF_OK ? TRUE : FALSE;
}

//bool DeviceController::fnSCSP20FromFile(string srcPath, string folderName, WFDEMO_SFR::TestResult &results)
bool DeviceController::fnSCSPFromFile(string imageFile, string jsonFile, string rxnNvmFile, WFDEMO_SFR::TestResult &results)
{
	uint16_t status = wfDLLStat::WF_OK;

	// Run each station test
	WFDEMO_SFR::TestResult intermediate_fom;

	std::string image_file_path = imageFile;
	std::string image_json_path = jsonFile;
	std::string image_nvm_path = rxnNvmFile;

	//只计算(第一张图片)最后一张
	std::string output_spotlog_path = (QString::fromStdString(imageFile)).replace(".raw", "_Spotlog.csv").toLocal8Bit();
	std::string output_heatmap_path = (QString::fromStdString(imageFile)).replace(".raw", "_Heatmap.csv").toLocal8Bit();

	// 250_Dot test
	status = SCSP25FromFile(image_file_path, image_json_path, image_nvm_path, intermediate_fom);
	for (const Result& el : intermediate_fom.FOM) {
		std::cout << el.first.c_str() << " : " << el.second.c_str() << std::endl;
	}
	//if (status != wfDLLStat::WF_OK)
	//{
	//	return wfDLLStat::WF_SP_ERROR;
	//}

	status = WFWriteSpotLog(intermediate_fom, output_spotlog_path);
	if (status != wfDLLStat::WF_OK) {
		return wfDLLStat::WF_SPOTLOG_ERROR;
	}

	if (intermediate_fom.FOM.size() < 2)
	{
		return wfDLLStat::WF_HMLOG_ERROR;
	}

	status = WFWriteHMLog(intermediate_fom, output_heatmap_path);
	if (status != wfDLLStat::WF_OK) {
		return wfDLLStat::WF_SPOTLOG_ERROR;
	}

	results = intermediate_fom;
	//ST250DotFomList = intermediate_fom;

	return TRUE;
}


bool DeviceController::fnScreenFromFile(string srcPath, WFDEMO_SFR::TestResult &results)
{
	uint16_t status = wfDLLStat::WF_OK;

	// ScreenFromFile section
	// Inputs
	std::string screen_dut_directory = srcPath;
	// Output Data structs
	WFDEMO_SFR::TestResult SC_Output;

	// Run the screen test
	status = ScreenFromFile(screen_dut_directory, SC_Output);
	if (status != wfDLLStat::WF_OK) {
		return wfDLLStat::WF_SP_ERROR;
	}

	// List out the metrics 
	for (const Result& el : SC_Output.FOM)
	{
		std::cout << el.first.c_str() << " : " << el.second.c_str() << std::endl;
	}
	results = SC_Output;

	return TRUE;
}

bool DeviceController::OpenVISA(QString session, QString address, QString prefix)
{
	bool ret = true;

	if (m_Visa.OpenDevice() != 1)
	{
		g_pOP->LogError(-1, __FUNCTION__, "SMU open device FAIL");
		ret = false;
	}
	else 
	{
		g_pOP->LogDebug(-1, __FUNCTION__, "SMU DefaultRM : %ld", m_Visa.GetDefaultRMNum());
	}

	char _session[32];
	sprintf_s(_session, _countof(_session), "%s", session.toLatin1().data());

	if (m_Visa.AddSession(_session, address, prefix, 2000/*OPEN_TIMEOUT*/) == false)
	{
		g_pOP->LogInfo(-1, __FUNCTION__, "SMU initialization retry");

		Sleep(100);

		if (m_Visa.AddSession(_session, address, prefix, 2000/*OPEN_TIMEOUT*/) == false)
		{
			g_pOP->LogError(-1, __FUNCTION__, "SMU initialization FAIL!!!");
			ret = false;
		}
	}

	if (ret)
	{
		ulong dwValue = 0;
		viSetAttribute(m_Visa.GetSession(session), VI_ATTR_TMO_VALUE, 500);
		viGetAttribute(m_Visa.GetSession(session), VI_ATTR_TMO_VALUE, &dwValue);
		g_pOP->LogInfo(-1, __FUNCTION__, "%s Timeout : %dms", _session, dwValue);

		viGetAttribute(m_Visa.GetSession(session), VI_ATTR_RD_BUF_SIZE, &dwValue);
		g_pOP->LogInfo(-1, __FUNCTION__, "%s Read Buffer Size : %d", _session, dwValue);

		viGetAttribute(m_Visa.GetSession(session), VI_ATTR_WR_BUF_SIZE, &dwValue);
		g_pOP->LogInfo(-1, __FUNCTION__, "%s Write Buffer Size : %d", _session, dwValue);

		if (session.contains("DMM"))
			fnSetUpDMM(session);
		else
			fnSetUpSMU(session);
	}
	return ret;
}

bool DeviceController::fnSetUpSMU(QString session)
{
	g_pOP->LogInfo(-1, __FUNCTION__, "%s Setting.", session.toLatin1().data());

	//m_Visa.WriteScriptToSMU(session);

	fnResetSMU(session);		//Reset_SMU()
	Sleep(200);

	m_Visa.ExecuteCommand(false, session, "Init_SMU()");
	Sleep(200);

	return true;
}

bool DeviceController::fnSetUpDMM(QString session)
{
	char buf[1024];
	g_pOP->LogInfo(-1, __FUNCTION__, "Setting %s.", session.toLatin1().data());

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Script
	bool ret = m_Visa.WriteScriptToDMM(session);
	Sleep(200);

	sprintf_s(buf, sizeof(buf), "Init_DMM(0.01)");
	ret &= g_pDEV->m_Visa.ExecuteCommand(false, session, buf);
	Sleep(200);

	return ret;
}

void DeviceController::fnResetSMU(QString session)
{
	g_pOP->LogInfo(-1, __FUNCTION__, "%s Reset.", session.toLatin1().data());

	g_pDEV->m_Visa.ExecuteCommand(false, session, "Reset_SMU()");
	Sleep(100);
}

bool DeviceController::SMU_ReadBuffer(QString session, int nSocIndex, QList<SMU_READ_BUFFER_DATA>& buffer_data, QString ReadBufferCommand)
{
	bool bResult = false;

	QString strSession = session;
	QString strRawData;
	char readedBuffer[VISA_BUFFER] = { 0L, };

	QString strReadBufferCmd;
	if (ReadBufferCommand != "")
	{
		strReadBufferCmd = ReadBufferCommand;
	}
	else
		strReadBufferCmd = "Buffer_Read()";

	if (!PC4())
	{
		device::SMUResponse reply;
		bool ret = g_pCOMM->m_grpcToPC4.ExecuteSMU(nSocIndex, session, strReadBufferCmd, reply);
		if (ret)
		{
			strRawData = reply.result().c_str();
			g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Buffer_Read OK,bufferSize:%d", strRawData.size());
		}
		else
		{
			g_pOP->LogError(nSocIndex, __FUNCTION__, "Send SMU CMD FAILED,nSocIndex:%d session:%s CMD:%s)", nSocIndex, session.toLatin1().data(), strReadBufferCmd);
			MessageBoxManage::Instance()->PostMessageBox("SMU ERROR", QString("SMU ERROR! Send SMU CMD FAILED, Socket:%1, %2").arg(nSocIndex + 1).arg(session), 0);
			return false;
		}
	}
	else
	{
		g_pDEV->m_Visa.ExecuteCommand(FALSE, strSession, strReadBufferCmd.toLatin1().data());

		if (g_pDEV->m_Visa.ReadResult(strSession, readedBuffer, sizeof(readedBuffer)))
		{

		}

		if (strcmp(readedBuffer, "") != 0 && strcmp(readedBuffer, "\n") != 0)
		{
			strRawData.append(readedBuffer);
			g_pOP->LogInfo(nSocIndex,__FUNCTION__, readedBuffer);
		}
	}

	if (strRawData.size() <= 0) {
		g_pOP->LogError(nSocIndex, __FUNCTION__, "Read SMU Buffer Empty");
		MessageBoxManage::Instance()->PostMessageBox("SMU ERROR", QString("SMU ERROR! Read SMU Buffer Empty, Socket:%1, %2").arg(nSocIndex + 1).arg(session), 0);

		return false;
	}

	if (session == g_pINSP->m_DMM_RMT)
	{
		SMU_READ_BUFFER_DATA result;
		result.RMT_R = strRawData.toDouble();
		buffer_data.push_back(result);
		//return true; //TODO 0707
	}

	memcpy(readedBuffer, strRawData.toLatin1().data(), strRawData.size());

	//g_pDEV->m_Visa.ReadResult(strSession, readedBuffer, _countof(readedBuffer));

	char *pTok, *pSes;
	QString tsztmp;

	int nItemCnt = 0;

	SMU_READ_BUFFER_DATA result;
	if (strcmp(readedBuffer, "nil") != 0)
	{
		pTok = strtok_s(readedBuffer, ",", &pSes);
		tsztmp = pTok;

		result.V_DOT = tsztmp.toDouble();
		nItemCnt++;
		while (pTok != NULL)
		{
			//dTemp = (double)atof(pTok);
			//vTempList.push_back(dTemp);

			pTok = strtok_s(NULL, ",", &pSes);
			tsztmp = pTok;

			if (!tsztmp.isEmpty())
			{
				switch (nItemCnt)
				{
				case 0:	result.V_DOT = tsztmp.toDouble(); break;
				case 1:	result.V_A = tsztmp.toDouble(); break;
				case 2:	result.V_B = tsztmp.toDouble(); break;
				case 3:	result.V_F = tsztmp.toDouble(); break;
				case 4:	result.I_DOT = tsztmp.toDouble(); break;
				case 5:	result.I_A = tsztmp.toDouble(); break;
				case 6:	result.I_B = tsztmp.toDouble(); break;
				case 7:	result.I_F = tsztmp.toDouble(); break;
				case 8:	result.NTC_R = tsztmp.toDouble();
					bResult = true;
					buffer_data.push_back(result);
					nItemCnt = -1;
					break;
				}
				nItemCnt++;
			}
		}

	}
	//ASSERT(buffer_data.size() <= 1);
	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Read SMU Buffer, Session:%s, SocketIndex:%d", session.toLatin1().data(), nSocIndex);
	return bResult;
}

double CalcNTCResistanceToTemperature(char * bufferData) 
{
	char *next_token = NULL;
	char *strToken = NULL;
	if (bufferData == NULL)
	{
		return 0;
	}
	QString buffer = QString("%1").arg(bufferData);
	if (buffer.contains(",") || buffer.contains("e-"))
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


double CalcNTCResistanceToTemperature(double Rexp)
{
	//char *next_token = NULL;
	//char *strToken = NULL;
	//if (bufferData == NULL)
	//{
	//	return 0;
	//}
	//strToken = strtok_s(bufferData, "e+", &next_token);
	//double Rexp = atof(strToken);
	//mData->mLogEvent->fnWriteLogAndShowui((LOG_STATION)nSocIndex, INFO, __FUNCTION__, "SMU getNTC Rexp:" + mData->mCommon->ToString(Rexp) );

	//添加电阻值换算方法在这里

	double B = 3435;
	double R0 = 10000;
	double T0 = 298.15;
	double scale = 1; // 1000.0;
	//int  next = atof(next_token);
	////mData->mLogEvent->fnWriteLogAndShowui((LOG_STATION)nSocIndex, INFO, __FUNCTION__, "SMU getNTC Rexp:" + mData->mCommon->ToString(Rexp) + "e+" + mData->mCommon->ToString(next));
	//if (next != 3)
	//{
	//	scale = 1;
	//	for (size_t i = 0; i < next; i++)
	//	{
	//		scale = scale * 10;
	//	}
	//}
	/*double Rexp = 9.432400;*/  //还可以用 strtod() 方法直接把char[] 转换成 浮点数
	double Temperature = 1 / (1.0 / B * log(Rexp * scale / R0) + 1.0 / T0) - 273.15;
	return Temperature;
}


bool DeviceController::GetNtcOFF(QString session, int nSocIndex, double * dTemper, double * dRValue)
{
	bool bReadOK = false;

	if (!PC4())
	{
		//QString startTime;
		//g_pDEV->m_SMULock.lock();
		//g_pDEV->m_SMUResultInfos.remove(session);
		//g_pDEV->m_SMULock.unlock();

		//bool ret = SendSMUCommandStart(nSocIndex, session, "Get_NTC()", startTime, 200);
		//
		////Sleep(1000 + 200);

		////SMUExecuteInfo SMUInfo;
		////g_pDEV->m_SMULock.lock();
		////if (g_pDEV->m_SMUResultInfos.contains(session))
		////{
		////	SMUInfo = m_SMUResultInfos.take(session);
		////}
		////g_pDEV->m_SMULock.unlock();
		//SMUExecuteInfo SMUInfo;
		//if (ret)
		//{			
		//	clock_t start = clock();
		//	while (start + 5000 > clock())
		//	{
		//		g_pDEV->m_SMULock.lock();
		//		if (g_pDEV->m_SMUResultInfos.contains(session))
		//		{
		//			SMUInfo = m_SMUResultInfos.take(session);
		//			g_pDEV->m_SMULock.unlock();
		//			break;
		//		}
		//		g_pDEV->m_SMULock.unlock();
		//		Sleep(10);
		//	}

		//	//在这里查询
		//	if (startTime != SMUInfo.startTime)
		//	{
		//		g_pOP->LogError(nSocIndex, __FUNCTION__, "Buffer_Read FAILED,startTime:%s SMUInfo.startTime:%s)", startTime.toLatin1().data(), SMUInfo.startTime.toLatin1().data());
		//		return false;
		//	}
		//	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Buffer_Read OK, value:%s", SMUInfo.result.toLatin1().data());
		//}
		//else
		//{
		//	g_pOP->LogError(nSocIndex, __FUNCTION__, "Send SMU CMD FAILED,nSocIndex:%d session:%s CMD:%s startTime:%s)", nSocIndex, session.toLatin1().data(), "Get_NTC()", startTime.toLatin1().data());
		//	return false;
		//}

		device::SMUResponse reply;
		bool ret = g_pCOMM->m_grpcToPC4.ExecuteSMU(nSocIndex, session, "Get_NTC()", reply);
		if (ret)
		{
			g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Buffer_Read OK, value:%s", reply.result().c_str());
		}
		else
		{
			g_pOP->LogError(nSocIndex, __FUNCTION__, "Send SMU CMD FAILED,nSocIndex:%d session:%s CMD:%s)", nSocIndex, session.toLatin1().data(), "Get_NTC()");
			MessageBoxManage::Instance()->PostMessageBox("SMU ERROR", QString("SMU ERROR! Send SMU CMD FAILED, Socket:%1, %2").arg(nSocIndex + 1).arg(session), 0);
			return false;
		}

	
		//在这里查询
		QString buffer = reply.result().c_str();
		if (buffer.size() > 0)
		{
			*dRValue = (double)buffer.toDouble();
			double dNTCTemperature = CalcNTCResistanceToTemperature(buffer.toLocal8Bit().data());
			*dTemper = dNTCTemperature;
			bReadOK = true;
		}
		else
		{
			*dRValue = 0.0;
			*dTemper = 0.0;
			bReadOK = false;
		}
		g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Get NTC off,SocketIndex:%d ,NTCTemper:%f", nSocIndex, *dTemper);
		return bReadOK;
	}

	double dNTCTemperature = 25.0;
	bool bRtn = TRUE;
	*dTemper = 0;
	*dRValue = 0;

	int retryCnt = 5;
	for (int i = 0; i < retryCnt; i++)
	{
		QString strRes;
		//--//
		//if (g_pDEV->SendCommandCurTemper(nSocIndex) == FALSE)
		//{
		//	continue;
		//}

		if (g_pDEV->m_Visa.ExecuteCommand(FALSE, session, "Get_NTC()") == FALSE)
		{
			continue;
		}

		//Sleep(200);

		char readedBuffer[VISA_BUFFER] = { 0L, };
		int retry = 0;
		while (1)
		{
			if (!g_pDEV->m_Visa.ReadResult(session, readedBuffer, sizeof(readedBuffer)))
			{
				retry++;
			}
			else
				break;
		}


		if (strcmp(readedBuffer, "") != 0 && strcmp(readedBuffer, "\n") != 0)
		{
			strRes.append(readedBuffer);
			g_pOP->LogInfo(nSocIndex,__FUNCTION__, readedBuffer);
		}
		//--//dNTCTemperature = g_pST->CalcNTCResistanceToTemperature(10000, (double)atof(strRes.c_str()), 3435, 298.15, FALSE);

		*dRValue = strRes.toDouble();
		*dTemper = CalcNTCResistanceToTemperature(strRes.toLocal8Bit().data());;		
		bReadOK = true;
		break;
	}
	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Get NTC off, Session:%s ,SocketIndex:%d ,NTCTemper:%f", session.toLatin1().data(), nSocIndex, *dTemper);
	return bReadOK ? true : false;
}

bool DeviceController::SMU_BufferClear(QString session, int nSocIndex)
{
	QString strSession = session;

	bool bRtn = TRUE;


	if (!PC4())
	{
		//QString startTime;
		///*g_pDEV->m_SMULock.lock();
		//g_pDEV->m_SMUResultInfos.remove(session);
		//g_pDEV->m_SMULock.unlock();*/

		//bool ret = SendSMUCommandStart(nSocIndex, session, "Buffer_Clear()", startTime, 200);
		device::SMUResponse reply;
		bool ret = g_pCOMM->m_grpcToPC4.ExecuteSMU(nSocIndex, session, "Buffer_Clear()", reply);


		return ret;
	}


	int retryCnt = 3; //5
	bool bReadOK = false;
	for (int i = 0; i < retryCnt; i++)
	{
		QString strRes;
		if (g_pDEV->m_Visa.ExecuteCommand(FALSE, strSession, "Buffer_Clear()") == FALSE) //"Buffer_Clear()\r\n"
		{
			continue;
		}

		bReadOK = true;
		break;
	}
	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "SMU Buffer Clear, Session:%s, SocketIndex:%d", session.toLatin1().data(), nSocIndex);
	return bReadOK ? true : false;
}

bool DeviceController::SMU_Initialize(QString session, int nSocIndex)
{
	QString strSession = session;
	bool bRtn = fnSetUpSMU(strSession);

	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "SMU initialize, Session:%s, SocketIndex:%d", session.toLatin1().data(), nSocIndex);
	return bRtn;
}


bool DeviceController::fnCollectiDevImpl()
{
	m_DPTWSerial = new CSerialComm();


	return true;
}

bool DeviceController::fnCollectiDevDestory()
{
	//if (m_DPTWSerial->IsOpened)
	//{

	//}
	delete m_DPTWSerial;

	g_pOP->LogInfo(-1, __FUNCTION__, "Collect Dev Destroy");
	return true;
}

double DeviceController::LIVNtcBaLiv(double dRVal)
{
	return NTC_Temp(dRVal);
}

void DeviceController::LIVTestCallBaLiv(BALIVInput & livInput, BALIVOutput & pLivOutput)
{
	double Ptot_Factor = 0.815300;
	double WL_Offset = 0.024400;

	BA_LIV(livInput.Sp_WL_nm,
		livInput.Sp_Power_W,
		livInput.Sp_ArrSize,
		livInput.PDCalWL_nm,
		livInput.PDCalResp_AW,
		livInput.PDCal_ArrSize,
		livInput.VCSEL_Array,
		livInput.V_Dot_input_V,
		livInput.V_A_input_V,
		livInput.V_B_input_V,
		livInput.V_Flood_input_V,
		livInput.I_Dot_input_A,
		livInput.I_A_input_A,
		livInput.I_B_input_A,
		livInput.I_Flood_input_A,
		livInput.NTC_ON_R_input_Ohm,
		livInput.Ipd_mA,
		livInput.tPeriod_ms,
		livInput.tPulse_ms,
		livInput.N_Total,
		livInput.N_Meas,
		livInput.N_Skin,
		livInput.tSkin_ms,
		Ptot_Factor,
		WL_Offset,
		livInput.MAxCCDCount,
		&(pLivOutput.data));
}

bool DeviceController::ContactCheck(QString session, int nSocIndex, SMU_READ_BUFFER_DATA & measureData)
{
	QString strScript;
	QString strSession = session;

	bool bRtn = false;

	double v_limit = 3.0;
	QList<CommandPair> cmdList;
	g_pINSP->m_screenIni->DecodeSection("CONTACT_CHECK", cmdList);
	for each (CommandPair var in cmdList)
	{
		if (var.first == "SMU")
		{
			strScript = var.second;
			break;
		}
		if (var.first == "PARAM" && var.second.contains("V_Limit"))
		{
			v_limit = var.second.remove("V_Limit").remove(" ").toDouble();
			break;
		}
	}

	bRtn = g_pDEV->m_Visa.ExecuteCommand(FALSE, strSession, strScript);
	if (!bRtn)
	{
		return false;
	}
	Sleep(100);

	double dOpenRangeLimit = v_limit - 0.001;
	double dShortRangeLimit = 0.001;

	QList<SMU_READ_BUFFER_DATA>	MeasureDataList;
	for each (CommandPair var in cmdList)
	{
		if (var.first == "SMU")
		{
			strScript = var.second;
		}
	}
	bRtn = SMU_ReadBuffer(strSession, nSocIndex, MeasureDataList, strScript);
	if (!bRtn)
	{
		return false;
	}

	measureData = MeasureDataList.front();
	if (measureData.V_DOT < dShortRangeLimit || measureData.V_DOT > dOpenRangeLimit)
	{
		bRtn = false;
	}
	g_pOP->LogSeq(__FUNCTION__, nSocIndex, "[SOCKET_%d][%s] V_DOT = %0.12f V", nSocIndex + 1, bRtn ? "OK" : "NG", measureData.V_DOT);

	if (measureData.V_A < dShortRangeLimit || measureData.V_A > dOpenRangeLimit)
	{
		bRtn = false;
	}
	g_pOP->LogSeq(__FUNCTION__, nSocIndex, "[SOCKET_%d][%s] V_A = %0.12f V", nSocIndex + 1, bRtn ? "OK" : "NG", measureData.V_DOT);

	if (measureData.V_B < dShortRangeLimit || measureData.V_B > dOpenRangeLimit)
	{
		bRtn = false;
	}
	g_pOP->LogSeq(__FUNCTION__, nSocIndex, "[SOCKET_%d][%s] V_B = %0.12f V", nSocIndex + 1, bRtn ? "OK" : "NG", measureData.V_DOT);

	if (measureData.V_F < dShortRangeLimit || measureData.V_F > dOpenRangeLimit)
	{
		bRtn = false;
	}
	g_pOP->LogSeq(__FUNCTION__, nSocIndex, "[SOCKET_%d][%s] V_F = %0.12f V", nSocIndex + 1, bRtn ? "OK" : "NG", measureData.V_DOT);

	return bRtn;
}

bool DeviceController::fnCanyouInit(int nSocIndex) {
	bool  ret = g_pDEV->m_BanffControl.fnCanyonDLLInitialize(nSocIndex);

	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Conyou init,Sockdet Index:%d", nSocIndex);
	return ret;
}

bool DeviceController::fnCanyouPowerOff(int nSocIndex, std::string sDumpFilePrefix) {
	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Canyou power off Start,Sockdet Index:%d", nSocIndex);

	m_BanffControl.fnSaveAllTXDumpToCsv(nSocIndex % 4, "Before_PowerOFF", sDumpFilePrefix); //没有poweroff 80ms  已经poweroff 550ms ，通讯时间 1ms
	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Canyou power off SaveAllTXDumpToCsv Done,Sockdet Index:%d", nSocIndex);

	bool  ret = m_BanffControl.fnPowerOFF(nSocIndex);  //25ms

	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Canyou power off,Sockdet Index:%d", nSocIndex);
	return ret;
}

bool DeviceController::fnCanyouPowerOnStreamingMode(int nSocIndex, std::string sTX_RegisterFile, std::string sRX_RegisterFile) {
	//
	int status = m_BanffControl.fnPowerOnCanyouPinVoltSet(nSocIndex, sTX_RegisterFile.c_str(), sRX_RegisterFile.c_str());
	if (status <= 0) {
		g_pOP->LogError(nSocIndex,__FUNCTION__, ("Power On PinVoltSet FAILED Socket:" + to_string(nSocIndex)).c_str());
		return false; //TODO
	}

	Sleep(50);//GPIO 上电需要延时 150  0712

	//status = m_BanffControl.fnSaveAllTXDumpToCsv(nSocIndex, "BeforePowerOn");
	//if (status == false)
	//{
	//	g_pOP->LogError(nSocIndex,__FUNCTION__, "SaveAllTXDump failed! BeforePowerOn");
		//return false;
	//}

	string powerOnSection = "[POWER_ON_ARMED]";
	if (!g_pINSP->getCheckArmed())
	{
		powerOnSection = "[POWER_ON]";
	}
	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "POWER_ON Section:[%s]", powerOnSection.c_str());
	bool ret = DoMeasure_PowerOnTx(nSocIndex, powerOnSection);
	if (!ret)
	{
		g_pOP->LogError(nSocIndex,__FUNCTION__, ("POWER_ON RegisterScriptParse Tx FAILED Socket:" + to_string(nSocIndex)).c_str());
		return false; //TODO
	}

	QString result2;
	bool ret2 = DoMeasure_ConfigDUTRx(nSocIndex, "[REGISTER_STREAM2]", result2);
	if (!ret2)
	{
		g_pOP->LogError(nSocIndex,__FUNCTION__, ("POWER_ON [REGISTER_STREAM3] Rx FAILED Socket:" + to_string(nSocIndex)).c_str());
		return false; //TODO
	}

	bool status2 = m_BanffControl.fnPowerOnCanyouAfterRegister(nSocIndex);
	if (!status2)
	{
		g_pOP->LogError(nSocIndex, __FUNCTION__, ("PowerOnCanyouAfterRegister FAILED Socket:" + to_string(nSocIndex)).c_str());
		return false; //TODO
	}

	//status = m_BanffControl.fnSaveAllTXDumpToCsv(nSocIndex, "AfterPowerOn");
	//if (status == false)
	//{
	//	g_pOP->LogError(nSocIndex,__FUNCTION__, "SaveAllTXDump FAILED! After PowerOn");
	//	return false;
	//}


	bool retLVDsStart = g_pDEV->m_BanffControl.fnSetLVDS_Start(nSocIndex);
	if (!retLVDsStart)
	{
		g_pOP->LogError(nSocIndex, __FUNCTION__, ("PowerOnCanyouAfterRegister FAILED fnSetLVDS_Start Socket:" + to_string(nSocIndex)).c_str());
		return false; //TODO
	}

	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Canyou power On [OK] ,Sockdet Index:%d", nSocIndex);
	return (status && status2 && ret && ret2 && retLVDsStart);
}

bool DeviceController::fnCanyouPowerOnTriggerMode(int nSocIndex, std::string sTX_RegisterFile, std::string sRX_RegisterFile) {
	//
	int status = m_BanffControl.fnPowerOnCanyouPinVoltSet(nSocIndex, sTX_RegisterFile.c_str(), sRX_RegisterFile.c_str());
	if (status <= 0) {
		g_pOP->LogError(nSocIndex, __FUNCTION__, ("Power On PinVoltSet FAILEDSocket:" + to_string(nSocIndex)).c_str());
		return false; //TODO
	}
	Sleep(50);//GPIO 上电需要延时 150  0712

	//status = m_BanffControl.fnSaveAllTXDumpToCsv(nSocIndex, "BeforePowerOn");
	//if (status == false)
	//{
	//	g_pOP->LogError(nSocIndex,__FUNCTION__, "SaveAllTXDump failed! BeforePowerOn");
		//return false;
	//}

	string powerOnSection = "[POWER_ON_ARMED]";
	if (!g_pINSP->getCheckArmed())
	{
		powerOnSection = "[POWER_ON]";
	}
	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "POWER_ON Section:[%s]", powerOnSection.c_str());
	bool ret = DoMeasure_PowerOnTx(nSocIndex, powerOnSection);
	if (!ret)
	{
		g_pOP->LogError(nSocIndex, __FUNCTION__, ("POWER_ON RegisterScriptParse Tx FAILEDSocket:" + to_string(nSocIndex)).c_str());
		return false; //TODO
	}

	QString result2;
	bool ret2 = DoMeasure_ConfigDUTRx(nSocIndex, "[REGISTER]", result2);
	if (!ret2)
	{
		g_pOP->LogError(nSocIndex, __FUNCTION__, ("POWER_ON [REGISTER_STREAM3] Rx FAILEDSocket:" + to_string(nSocIndex)).c_str());
		return false; //TODO
	}

	bool status2 = m_BanffControl.fnPowerOnCanyouAfterRegister(nSocIndex);
	if (!status2)
	{
		g_pOP->LogError(nSocIndex, __FUNCTION__, ("PowerOnCanyouAfterRegister FAILEDSocket:" + to_string(nSocIndex)).c_str());
		return false; //TODO
	}

	//status = m_BanffControl.fnSaveAllTXDumpToCsv(nSocIndex, "AfterPowerOn");
	//if (status == false)
	//{
	//	g_pOP->LogError(nSocIndex,__FUNCTION__, "SaveAllTXDump FAILED! After PowerOn");
	//	return false;
	//}

	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Canyou power On [OK] ,Sockdet Index:%d", nSocIndex);
	return (status && status2 && ret && ret2);
}


bool DeviceController::fnSwitchTrrigerMode(int nSocIndex)
{
	QString result2;
	bool ret2 = DoMeasure_ConfigDUTRx(nSocIndex, "[REGISTER]", result2); //Hard ware trriger.
	if (!ret2)
	{
		g_pOP->LogError(nSocIndex, __FUNCTION__, ("POWER_ON [REGISTER] Rx FAILEDSocket:" + to_string(nSocIndex)).c_str());
		return false; //TODO
	}

	return true;
}



bool DeviceController::DoMeasure_PowerOnTx(int nSocIndex, std::string sectionName, bool bWithoutPowerControl)
{
	int ret = 1;
	QString strLog;
	QString strT;
	QString strSession, strScript;
	QList<CommandPair> cmdList;
	g_pINSP->m_screenTxIni->DecodeSection(QString::fromStdString(sectionName), cmdList);
	if (cmdList.empty())
	{
		QString strT;
		strT = GetFormat("[SOCKET_%02d][DoMeasure_PowerOn] [%d] Invalid INI script.. Use the valid INI", nSocIndex + 1, sectionName);
		g_pOP->LogError(nSocIndex,__FUNCTION__, strT.toStdString().c_str());

		throw QString("Invalid INI script.. Use the valid INI");
		return 0;
	}

	ret = m_BanffControl.RegisterScriptParse(nSocIndex, QString::fromStdString(sectionName), false, cmdList);
	if (!ret)
	{
		strT = "*****  ConfigDUTForCapture FAILEDURE *****\r\n";
	}
	else
	{
		strT = "ConfigDUTForCapture OK \r\n";
	}

	return ret;
}

bool DeviceController::DoMeasure_ConfigDUTRx(int nSocIndex, QString sectionName)
{
	int ret = 1;
	QString strLog;
	QString strT;
	QString strSession, strScript;
	QList<CommandPair> cmdList;
	g_pINSP->m_screenFFBLIni->DecodeSection(sectionName, cmdList);
	if (cmdList.empty())
	{
		QString strT;
		strT = GetFormat("[SOCKET_%02d][DoMeasure_ConfigDUTRx] [%d] Invalid INI script.. Use the valid INI", nSocIndex + 1, sectionName);
		g_pOP->LogError(nSocIndex,__FUNCTION__, strT.toStdString().c_str());
		throw QString("Invalid INI script.. Use the valid INI");
		return 0;
	}
	ret = m_BanffControl.RegisterScriptParse(nSocIndex, sectionName, false, cmdList);
	if (!ret)
	{
		strT = "*****  DoMeasure_ConfigDUTRx FAILEDURE *****\r\n";
	}
	else
	{
		strT = "DoMeasure_ConfigDUTRx OK \r\n";
	}
	return ret;
}
bool DeviceController::DoMeasure_ConfigDUTRx(int nSocIndex, QString sectionName, QString & result, bool bWithoutPowerControl)
{
	int ret = 1;
	QString strLog;
	QString strT;
	QString strSession, strScript;
	QList<CommandPair> cmdList;
	g_pINSP->m_screenRxIni->DecodeSection(sectionName, cmdList);
	if (cmdList.empty())
	{
		QString strT;
		strT = GetFormat("[SOCKET_%02d][DoMeasure_PowerOn] [%d] Invalid INI script.. Use the valid INI", nSocIndex + 1, sectionName);
		g_pOP->LogError(nSocIndex,__FUNCTION__, strT.toStdString().c_str());

		throw QString("Invalid INI script.. Use the valid INI");
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

	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Canyou power on Rx,Sockdet Index:%d", nSocIndex);
	return ret;
}

int DeviceController::DoMeasure_ConfigDUTForCapture(int nSocIndex, QString section, string &sCMDSMU)
{
	int ret = 1;
	string value;
	bool ret0 = m_BanffControl.fnCheckHardBrick(nSocIndex, value);
	g_pOP->LogDebug(nSocIndex,__FUNCTION__, "Read 0xB4 value before ConfigDUTForCapture.Index:%d Section:%s 0xB4:%s", (nSocIndex), section.toLatin1().data(), value.c_str());
	if (ret0)
	{
		return false;
	}

	QString strLog;
	QString strT;
	QString sectionName = QString("[%1]").arg(section); 
	QString strSession, strScript;
	QList<CommandPair> cmdList;
	g_pINSP->m_screenTxIni->DecodeSection(sectionName, cmdList);
	if (cmdList.empty())
	{
		QString strT;
		strT = GetFormat("[SOCKET_%02d][DoMeasure_ConfigDUTForCapture] [%d] Invalid INI script.. Use the valid INI", nSocIndex + 1, sectionName.toLatin1().data());
		g_pOP->LogError(nSocIndex,__FUNCTION__, strT.toStdString().c_str());

		throw QString("Invalid INI script.. Use the valid INI");
		//return 0; //TODO 
	}

	for each (CommandPair var in cmdList)
	{
		if (var.first == "SMU" && var.second.contains("Drive")) {
			strScript = var.second;
		}
	}
	sCMDSMU = strScript.toStdString();

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

	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Config DUT for Captrue.Board Index:%d section:%s", nSocIndex, sectionName.toLatin1().data());
	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Config DUT for Captrue.Board Index:%d command:%s", nSocIndex, sCMDSMU.c_str());

	return ret;// ret; //TODO 
}

bool DeviceController::fnModuleCaptureImage(int nSocIndex, QString station, QString barcode, std::string FilePath, std::string fileName, std::string sDumpFilePrefix, bool iTriger) {
	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "CaptureImage, %d %s %s %s\\%s", nSocIndex, station.toLatin1().data(), barcode.toLatin1().data(), FilePath.c_str(), fileName.c_str());
	bool ret = false;
	/*bool iShowImg = false;
	if (fileName.find("0.raw") != std::string::npos)
	{
		iShowImg = true;
	}*/
	bool iShowImg = true;
	if (iTriger)
	{
		ret = m_BanffControl.fnGetOneFrame(nSocIndex, station, barcode, FilePath, fileName, iShowImg);
	}
	else
	{
		ret = m_BanffControl.fnGetOneFrameWithoutTrigger(nSocIndex, station, barcode, FilePath, fileName, iShowImg);
	}
	
	
	if (sDumpFilePrefix.length()<=0)
	{
		return ret;
	}
	QString section = QString(fileName.c_str());
	section.replace(".raw", "");
	QStringList fileNames = section.split("_");
	int listLength = fileNames.size();
	if (listLength >= 2)
	{
		section = QString("%1-%2").arg(fileNames.at(listLength - 2)).arg(fileNames.at(listLength - 1));
	}
	if (sDumpFilePrefix.length() > 0)
	{
		bool status = m_BanffControl.fnSaveSimpleTXDumpToCsv(nSocIndex, Format("After Capture %s", section.toLatin1().data()), sDumpFilePrefix);
		if (status == false)
		{
			g_pOP->LogError(nSocIndex, __FUNCTION__, "SaveSimpleTXDump FAILED! After Capture Image");
			//return false;
		}
	}
	return ret;
}

int DeviceController::fnSendOneTrigerSMU(QString session, int nSocIndex, QString command, string info, std::string sDumpFilePrefix)
{
	bool ret = true;
	QString strSession, strScript;
	strSession = session;
	strScript = command;
	if (!PC4())
	{
		g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Send One Triger SMU,boardIndex:%d session:%s Info:%s CMD:%s", nSocIndex, session.toLatin1().data(), info.c_str(), command.toLatin1().data());

		QString startTime;
		
		//bool ret = SendSMUCommandStart(nSocIndex, session, command, startTime, 200);

		device::SMUResponse reply;
		ret = g_pCOMM->m_grpcToPC4.ExecuteSMU(nSocIndex, strSession, strScript, reply);

		bool status = m_BanffControl.fnSaveSimpleTXDumpToCsv(nSocIndex, Format("SendOneTrigerSMU %s", info.c_str()), sDumpFilePrefix);
		if (status == false)
		{
			g_pOP->LogError(nSocIndex,__FUNCTION__, "SaveSimpleTXDump FAILED! Before SendOneTrigerSMU");
			//return false;
		}
		return ret;
	}



	ret = g_pDEV->m_Visa.ExecuteCommand(FALSE, strSession, strScript);

	//bool status = m_BanffControl.fnSaveAllTXDumpToCsv(nSocIndex, Format("SendOneTrigerSMU %s", info.c_str()),sDumpFilePrefix);
	//if (status == false)
	//{
	//	g_pOP->LogError(nSocIndex,__FUNCTION__, "SaveAllTXDump FAILED! After SendOneTrigerSMU");
	//	return false;
	//}
	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Send One Triger SMU,boardIndex:%d Info:%s CMD:%s", nSocIndex, info.c_str(), command.toLatin1().data());
	return  ret;
}

bool DeviceController::ReadTxASIC_Temper(int nSocIndex, double * pResult)
{
	*pResult = 0.0;
	bool bRet = true;

	bRet = m_BanffControl.ReadTxASIC_Temper(nSocIndex, pResult);
	
	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Read Tx temperature:%f", *pResult);
	return bRet;
}

bool DeviceController::ReadRTraceValue(int nSocIndex, uInt16 * pRTrace, double * pRTraceOhm, std::string * pLog)
{
	bool bRet = 0;
	ushort ADC_READOUT;
	double RPU = 332000;
	bool status = m_BanffControl.fnReadRTraceValue(nSocIndex, ADC_READOUT);
	double ADC_V = (double)(1.5 / 4095) * ADC_READOUT;
	double RTraceValue = ADC_V * RPU / (1.5 - ADC_V);

	ADC_READOUT = ADC_READOUT / 1000.0;
	RTraceValue = RTraceValue / 1000.0;

	*pRTrace = ADC_READOUT;
	*pRTraceOhm = RTraceValue;  //RPD * (1.5 - ADC_V) / ADC_V;

	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Read Rtrace:%X ,RtraceOhm:%f", pRTrace,pRTrace);
	return bRet;
}


//ImageProcess
//#define SkipOld 0 //Cherish 0811
bool DeviceController::fnAE_process(int nSocIndex, QString sPatten, QString barcode, std::string FilePath, std::string fileName,int &ImgMean, int &AEInt)
{

	bool captureRet = false;
	bool writeRet = false;
	int Pedestal = 256;
	int RegValMin = 0;
	int RegValMax = 0;
	int GreenTarget = 818;
	int GreenOffset = 19;
	int AeCount = g_pINSP->m_FFBL_Config.GetInt("AECount",10);
	int cntRetry = 0;
	int RegValCur = 7700;
	int RegValInit = 0;
	FILE *fp60 = NULL;

	PUSHORT RawData;

	if (sPatten == "NB")//NB
	{
		RegValMin = g_pINSP->m_FFBL_Config.GetInt("RegValMin_NB", 3000);
		RegValMax = g_pINSP->m_FFBL_Config.GetInt("RegValMax_NB", 7700);
		RegValInit = g_pINSP->m_FFBL_Config.GetInt("RegValInit_NB", 1800);
	}
	else if(sPatten == "BB")//BB
	{
		RegValMin = g_pINSP->m_FFBL_Config.GetInt("RegValMin_BB", 100);
		RegValMax = g_pINSP->m_FFBL_Config.GetInt("RegValMax_BB", 800);
		RegValInit = g_pINSP->m_FFBL_Config.GetInt("RegValInit_BB", 8700);
	}
	else
	{
		//err here
		return false;
	}


	//Capture 4 Dummy Frames
	//fnGetOneFrame(nBoardindex,station,barcode, FilePath, fileName);
	for (size_t i = 0; i < 4; i++)
	{
		captureRet = g_pDEV->m_BanffControl.fnGetFFBLDummyFrame(nSocIndex);
		g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Capture Dummy Frame Count:[%d], Results:[%d]", i, captureRet);
		//Sleep(100);
	}

	while (cntRetry <= AeCount)
	{
		RawData = new USHORT[1104 * 1314];
		memset(RawData, 0, sizeof(short) * (1104 * 1314));

		//write I2C  0x146 0x147
		uchar high_byte2 = (RegValCur >> 8) & 0xFF;
		uchar low_byte2 = RegValCur & 0xFF;		

		int high_byte = (RegValCur >> 8) & 0xFF;
		int low_byte = RegValCur & 0xFF;
		g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Exposure time update RegValCur:[%d] [0x146]:[%x]; [0x147]:[%x]", RegValCur, high_byte, low_byte);

		writeRet = g_pDEV->m_BanffControl.WriteByte(nSocIndex, true, 0x146, high_byte);
		writeRet = g_pDEV->m_BanffControl.WriteByte(nSocIndex, true, 0x147, low_byte);

		//Delay 100ms
		Sleep(100);
		g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Exposure time Read :[%s]", g_pDEV->m_BanffControl.I2cReadByte(nSocIndex, true, 0x0146, 2));

		//Capture 2 dummy frames and discard
		for (size_t i = 0; i < 2; i++)
		{
			captureRet = g_pDEV->m_BanffControl.fnGetFFBLDummyFrame(nSocIndex);
			g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Capture Dummy Frame After Exposure Time Change:[%d]", i);
		}

		//Capture 1 frames to m_DataRawBuffer
		//captureRet = g_pDEV->m_BanffControl.fnGetFFBLOneFrame(nSocIndex, true, GROUP_FFBL, barcode, FilePath, Format("%s_AEProcess-%s-%d.raw", fileName.c_str(), sPatten.toLatin1().data(), cntRetry), RawData);
		captureRet = g_pDEV->m_BanffControl.fnGetFFBLExposureImg(nSocIndex, true, GROUP_FFBL, barcode, FilePath, Format("%s_AEProcess-%s-%d.raw", fileName.c_str(), sPatten.toLatin1().data(), cntRetry), RawData);

		if (!captureRet)
		{
			return false;
		}

		int rangeValue = 50;
#ifdef SkipOld // Calculator mean with OpenCV
		Mat src = Mat::zeros(BANFF_IMG_H, BANFF_IMG_W, CV_16UC1);;
		uchar *buffer = new uchar[BANFF_IMG_H*BANFF_IMG_W * 5 / 4];
		//fread(buffer, sizeof(uchar), BANFF_IMG_H * BANFF_IMG_W * 5 / 4, fp60);
		memcpy(buffer,RawData, BANFF_IMG_H*BANFF_IMG_W * 5 / 4);

		//fclose(fp60);
		int rangeHalf = rangeValue / 2;
		unsigned int nDst, nSrc;
		for (int i = 0; i < BANFF_IMG_H; i++)
		{
			for (int j = 0; j < BANFF_IMG_W; j += 4)
			{
				//10bit raw image allocate 16bit memory
				nDst = i * BANFF_IMG_W + j;
				nSrc = i * BANFF_IMG_W + ((j * 5) >> 2);
				src.at<ushort>(i, j + 0) = (ushort)(buffer[nSrc + 0] << 2) + (buffer[nSrc + 4] & 0x03);
				src.at<ushort>(i, j + 1) = (ushort)(buffer[nSrc + 1] << 2) + ((buffer[nSrc + 4] & 0x0C) >> 2);
				src.at<ushort>(i, j + 2) = (ushort)(buffer[nSrc + 2] << 2) + ((buffer[nSrc + 4] & 0x30) >> 4);
				src.at<ushort>(i, j + 3) = (ushort)(buffer[nSrc + 3] << 2) + ((buffer[nSrc + 4] & 0xC0) >> 6);
			}
		}

		double sumPixel = 0;
		for (int i = BANFF_IMG_H / 2 - 1 - rangeHalf; i < BANFF_IMG_H / 2 - 1 + rangeHalf; i++)
		{
			for (int j = BANFF_IMG_W / 2 - 1 - rangeHalf; j < BANFF_IMG_W / 2 - 1 + rangeHalf; j++)
			{
				sumPixel += src.at<ushort>(i, j);
			}
		}
		ImgMean = sumPixel / (rangeValue * rangeValue);

		delete[] buffer;
		buffer = NULL;
		#endif // 0

		ImgMean = g_pDEV->m_BanffControl.fnGetImgMean(RawData,BANFF_IMG_W,BANFF_IMG_H, rangeValue);

		delete[] RawData;
		RawData = NULL;

		g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Image mean value:[%d] with retry-%d;", ImgMean, cntRetry);

		if (ImgMean > 799 && ImgMean < 837)
		{
			if ((RegValCur >= RegValMin /*100*/) && (RegValCur <= RegValMax /*800*/))
			{
				//AE Passed;
				AEInt = RegValCur;
				g_pOP->LogInfo(nSocIndex, __FUNCTION__, "AE_PROCESS Successfully!    ImageMean:[%d]; AE Int:[%d]", ImgMean, AEInt);
				return true;
			}
			else
			{
				//AE FAILED;
				g_pOP->LogError(nSocIndex, __FUNCTION__, "ReginiValue value out of spec:[%d] spec Min:[%d]; Max:[%d]", RegValCur, RegValMin, RegValMax);
				return false;
			}
		}
		else
		{
			RegValCur = MIN(RegValCur * 754 / MAX(1, ImgMean - 64), RegValInit);
			AEInt = RegValCur;
			qDebug()<< "RegValCur:" << RegValCur << "ImgMean:" << ImgMean;
			g_pOP->LogInfo(nSocIndex, __FUNCTION__, "ReginiValue value:[%d] with retry - %d;", RegValCur, cntRetry);
		}

		cntRetry++;
	}

	if (!(cntRetry >= 10))
	{
		//AE FAILED
		g_pOP->LogError(nSocIndex, __FUNCTION__, "AE Process FAILED with count [%d]", cntRetry);
		return false;
	}
	return true;
}

bool DeviceController::fnGetNTCSMU(QString session, int nSocIndex, double& Temperature)
{
	BOOL status = FALSE;
	//从SMU读取对应的电阻值，然后根据公式计算出温度
	double dRtrace = 0.0;
	double dTemp = 0.0;
	bool ret = GetNtcOFF(session, nSocIndex, &dTemp, &dRtrace);
	Temperature = dTemp;
	
	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Get NTC Temp:%f", Temperature);
	return ret;
}


//PC2,PC3 call smu and PD DMM, RMT DMM
bool DeviceController::SendSMUCommandStart(int nSocIndex, QString session, QString script, QString & startTime, int timeRead)
{
	SMUExecuteInfo SMUInfo;
	QString commandStr;
	commandStr.append("SMUExecute");
	commandStr.append(";");
	commandStr.append(QString::number(nSocIndex));
	commandStr.append(";");
	commandStr.append(session);
	commandStr.append(";");
	commandStr.append(script);
	commandStr.append(";");
	commandStr.append("");
	commandStr.append(";");
	commandStr.append(QString::number(timeRead));
	commandStr.append(";");
	startTime = CFormatTime::fnGetCurrentFullDateTimeNoDot();
	commandStr.append(startTime);

	//return g_pCOMM->SendMsgToPC4(nSocIndex, commandStr.toLatin1());
	return true;
}

bool DeviceController::SendSMUResultStart(int nSocIndex, QString session, QString script, QString result, QString startTime, int timeRead)
{
	QString commandStr;
	commandStr.append("SMUResult");
	commandStr.append(";");
	commandStr.append(QString::number(nSocIndex));
	commandStr.append(";");
	commandStr.append(session);
	commandStr.append(";");
	commandStr.append(script);
	commandStr.append(";");
	commandStr.append(result);
	commandStr.append(";");
	commandStr.append(QString::number(timeRead));
	commandStr.append(";");
	commandStr.append(startTime);

	//return g_pCOMM->SendMsgToPC2or3BySocketIndex(nSocIndex, commandStr.toLatin1());
	return true;
}


bool DeviceController::SendFFBLlghtCommandStart(int nSocIndex, QString LightType, QString & startTime)
{
	QString commandStr;
	commandStr.append("FFBLlightExecute");
	commandStr.append(";");
	commandStr.append(QString::number(nSocIndex));
	commandStr.append(";");
	commandStr.append(LightType);
	commandStr.append(";");
	startTime = CFormatTime::fnGetCurrentFullDateTimeNoDot();
	commandStr.append(startTime);

	//return g_pCOMM->SendMsgToPC4(nSocIndex, commandStr.toLatin1());
	return true;
}

bool DeviceController::SendDPTWCommandStart(int nSocIndex, QString sFunction, QString & startTime)
{
	QString commandStr;
	commandStr.append(CMD_DPTWEXE);
	commandStr.append(";");
	commandStr.append(QString::number(nSocIndex));
	commandStr.append(";");
	commandStr.append(sFunction);
	commandStr.append(";");
	startTime = CFormatTime::fnGetCurrentFullDateTimeNoDot();
	commandStr.append(startTime);

	//return g_pCOMM->SendMsgToPC4(nSocIndex, commandStr.toLatin1());
	return true;
}

bool DeviceController::SendDPTWCommandResult(int nSocIndex, QString sFunction, float fDUTTemp, float fsensorTemp, QString & startTime)
{
	QString commandStr;
	commandStr.append(CMD_DPTWEXE);
	commandStr.append(";");
	commandStr.append(QString::number(nSocIndex));
	commandStr.append(";");
	commandStr.append(sFunction);
	commandStr.append(";");
	commandStr.append(QString::number(fDUTTemp));
	commandStr.append(";");
	commandStr.append(QString::number(fsensorTemp));
	commandStr.append(";");
	startTime = CFormatTime::fnGetCurrentFullDateTimeNoDot();
	commandStr.append(startTime);

	//return g_pCOMM->SendMsgToPC2or3BySocketIndex(nSocIndex, commandStr.toLatin1());
	return true;
}

bool DeviceController::SendShutterCmdStart(int nSocIndex, QString station, QString cmd, QString & keyWithTime)
{
	keyWithTime = QString("Socket%1_%2_%3_%4").arg(nSocIndex).arg(station).arg(cmd).arg(CFormatTime::fnGetCurrentFullDateTimeNoDot());
	QStringList list =
	{
		"SHUTTER",
		QString::number(nSocIndex),
		station,
		cmd,
		keyWithTime,
		"NG"
	};

	QString str = list.join(';');

	master::BaseResponse reply;
	return g_pCOMM->m_grpcToPC1.EventControl(nSocIndex, "SHUTTER", str, reply);
	//return g_pCOMM->SendMsgToPC1(nSocIndex, str.toLatin1());
}

bool DeviceController::SendShutterCmdResult(int nSocIndex, QString station, QString cmd, QString keyWithTime, QString result)
{
	QStringList list =
	{
		"SHUTTER",
		QString::number(nSocIndex),
		station,
		cmd,
		keyWithTime,
		result
	};

	QString str = list.join(';');
	//return g_pCOMM->SendMsgToPC2or3BySocketIndex(nSocIndex, str.toLatin1());
	return true;
}

bool DeviceController::SetShutterCmdResult(QString str)
{
	QStringList list = str.split(';');
	if (list.size() < 6)
	{
		return false;
	}

	QMutexLocker lock(&m_mutexShutterCmdResult);
	m_mapShutterCmdResult[list.at(4)] = list.at(5);
	return true;
}

bool DeviceController::GetShutterCmdResult(QString keyWithTime, QString & result)
{
	QMutexLocker lock(&m_mutexShutterCmdResult);
	if (m_mapShutterCmdResult.contains(keyWithTime))
	{
		QString result = m_mapShutterCmdResult.take(keyWithTime);

		QStringList list = result.split(';');
		if (list.size() < 6)
		{
			result = "NULL";
			return true;
		}
		result = list.at(5);
	}

	return false;
}

bool DeviceController::SendSocketPowerOff(int nSocIndex)
{
	//QStringList list =
	//{
	//	"POWER_OFF",
	//	QString::number(nSocIndex),
	//};

	//QString str = list.join(';');
	//return g_pCOMM->SendMsgToPC2or3BySocketIndex(nSocIndex, str.toLatin1());

	master::BaseResponse reply;
	if (nSocIndex >= 0 && nSocIndex < 4)
	{
		return g_pCOMM->m_grpcToPC2.EventControl(nSocIndex, "POWER_OFF", "", reply);
	}
	else if (nSocIndex >= 4 && nSocIndex < 8)
	{
		return g_pCOMM->m_grpcToPC3.EventControl(nSocIndex, "POWER_OFF", "", reply);
	}	

	return false;
}
bool DeviceController::SendToStopTest()
{
	//QStringList list =
	//{
	//	"STOP_TEST",
	//	//QString::number(nSocIndex),
	//};

	//QString str = list.join(';');
	//g_pCOMM->SendMsgToPC2or3BySocketIndex(2, str.toLatin1());//to PC2
	//g_pCOMM->SendMsgToPC2or3BySocketIndex(6, str.toLatin1());//to PC3
	//g_pCOMM->SendMsgToPC4(-1, str.toLatin1()); //to PC4
	//return true;

	master::BaseResponse reply;

	bool ret = g_pCOMM->m_grpcToPC2.EventControl(-1, "STOP_TEST", "", reply);
	ret &= g_pCOMM->m_grpcToPC3.EventControl(-1, "STOP_TEST", "", reply);
	ret &= g_pCOMM->m_grpcToPC4.EventControl(-1, "STOP_TEST", "", reply);

	return ret;
}

bool DeviceController::SendToSaveTxNVM(int nSocIndex, std::string sDumpFilePrefix)
{
	//QStringList list =
	//{
	//	"SAVE_TXNVM",
	//	QString::number(nSocIndex),
	//	QString::fromStdString(sDumpFilePrefix),
	//};

	//QString str = list.join(';');
	//g_pCOMM->SendMsgToPC2or3BySocketIndex(2, str.toLatin1());//to PC2
	//g_pCOMM->SendMsgToPC2or3BySocketIndex(6, str.toLatin1());//to PC3
	//return true;

	master::BaseResponse reply;

	bool ret = g_pCOMM->m_grpcToPC2.EventControl(nSocIndex, "SAVE_TXNVM", sDumpFilePrefix.c_str(), reply);
	ret &= g_pCOMM->m_grpcToPC3.EventControl(nSocIndex, "SAVE_TXNVM", sDumpFilePrefix.c_str(), reply);

	return ret;
}

bool DeviceController::SendToLotStart(QString sConfig, QString sLot, QString sTestMode, QString sRunMode)
{
	QStringList list =
	{
		"LOT_START",
		sConfig,
		sLot,
		sTestMode,
		sRunMode
	};

	QString str = list.join(';');

	//g_pCOMM->SendMsgToPC2or3BySocketIndex(2, str.toLatin1());//to PC2
	//g_pCOMM->SendMsgToPC2or3BySocketIndex(6, str.toLatin1());//to PC3
	//g_pCOMM->SendMsgToPC4(-1, str.toLatin1()); //to PC4
	//return true;

	master::BaseResponse reply;

	bool ret = g_pCOMM->m_grpcToPC2.EventControl(-1, "LOT_START", str, reply);
	ret &= g_pCOMM->m_grpcToPC3.EventControl(-1, "LOT_START", str, reply);
	ret &= g_pCOMM->m_grpcToPC4.EventControl(-1, "LOT_START", str, reply);

	return ret;
}

bool DeviceController::SendToLotEnd()
{
	QStringList list =
	{
		"LOT_END",
		//QString::number(nSocIndex),
	};

	QString str = list.join(';');
	//g_pCOMM->SendMsgToPC2or3BySocketIndex(2, str.toLatin1());//to PC2
	//g_pCOMM->SendMsgToPC2or3BySocketIndex(6, str.toLatin1());//to PC3
	//g_pCOMM->SendMsgToPC4(-1, str.toLatin1()); //to PC4
	//return true;

	master::BaseResponse reply;

	bool ret = g_pCOMM->m_grpcToPC2.EventControl(-1, "LOT_END", str, reply);
	ret &= g_pCOMM->m_grpcToPC3.EventControl(-1, "LOT_END", str, reply);
	ret &= g_pCOMM->m_grpcToPC4.EventControl(-1, "LOT_END", str, reply);

	return ret;
}

bool DeviceController::SendDILInspect(int nSocIndex, MtcpPacket packet)
{
	packet.LineAt(GROUP_IPCX, COMMAND).value = "DILInspect";

	REQList list = packet.GetListByGroups({ GROUP_IPCX, GROUP_TSCR, GROUP_DIL });
	QString WriteStr = MtcpPacket::ListToWriteStr(list);

	//return g_pCOMM->SendMsgToPC4(nSocIndex, WriteStr.toLocal8Bit());

	master::BaseResponse reply;

	return g_pCOMM->m_grpcToPC4.EventDevStart(nSocIndex, "DILInspect", WriteStr, reply);
}

bool DeviceController::SendDILInspectResult(int nSocIndex, MtcpPacket packet)
{
	packet.LineAt(GROUP_IPCX, COMMAND).value = "DILResult";

	REQList list = packet.GetListByGroups({ GROUP_IPCX, GROUP_TSCR, GROUP_DIL, GROUP_DILRES });
	QString WriteStr = MtcpPacket::ListToWriteStr(list);

	//return g_pCOMM->SendMsgToPC2or3BySocketIndex(nSocIndex, WriteStr.toLocal8Bit());
	master::BaseResponse reply;

	if (nSocIndex >= 0 && nSocIndex < 4)
	{
		return g_pCOMM->m_grpcToPC2.EventDevEnd(nSocIndex, "DILResult", WriteStr, reply);
	}
	else if (nSocIndex >= 4 && nSocIndex < 8)
	{
		return g_pCOMM->m_grpcToPC3.EventDevEnd(nSocIndex, "DILResult", WriteStr, reply);
	}
}


bool DeviceController::fnGetRxTemperature(int nSocIndex, double& temperature)
{
	bool status = false;
	double temp;

	status = m_BanffControl.fnReadRxTemperature(nSocIndex, temp);
	temperature = temp;

	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Read Rx temperature:%f", temp);
	return status;
}


std::string fnGetIMGName(DUTIMGNAME prefix, int suffix)
{
	string fileName;

	switch (prefix)
	{
	case ST200MTFIMG:
		fileName = Format("_ST200_MTF-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST200_MTF.raw" : "";
		break;
	case ST200DOTIMG:
		fileName = Format("_ST200_Dot-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST200_Dot.raw" : "";
		break;
	case ST200DOTAIMG:
		fileName = Format("_ST200_DotA-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST200_DotA.raw" : "";
		break;
	case ST200DOTBIMG:
		fileName = Format("_ST200_DotB-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST200_DotB.raw" : "";
		break;
	case ST200DOTABIMG:
		fileName = Format("_ST200_DotAB-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST200_DotAB.raw" : "";
		break;
	case ST200FLOODIMG:
		fileName = Format("_ST200_Flood-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST200_Flood.raw" : "";
		break;
	case ST600MTFIMG:
		fileName = Format("_ST600_MTF-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST600_MTF.raw" : "";
		break;
	case ST600DOTIMG:
		fileName = Format("_ST600_Dot-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST600_Dot.raw" : "";
		break;
	case ST600DOTAIMG:
		fileName = Format("_ST600_DotA-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST600_DotA.raw" : "";
		break;
	case ST600DOTBIMG:
		fileName = Format("_ST600_DotB-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST600_DotB.raw" : "";
		break;
	case ST600DOTABIMG:
		fileName = Format("_ST600_DotAB-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST600_DotAB.raw" : "";
		break;
	case ST600FLOODIMG:
		fileName = Format("_ST600_Flood-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST600_Flood.raw" : "";
		break;
	case ST250MTFIMG:
		fileName = Format("_ST250_MTF-%d.raw", suffix);
		//(suffix == 0) ? fileName = "_ST250_MTF.raw" : "";
		break;
	case ST250DARKIMG:
		fileName = Format("_ST250_Dark-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST250_Dark.raw" : "";
		break;
	case ST250DOTIMG:
		fileName = Format("_ST250_Dot-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST250_Dot.raw" : "";
		break;
	case ST250DOTAIMG:
		fileName = Format("_ST250_DotA-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST250_DotA.raw" : "";
		break;
	case ST250DOTBIMG:
		fileName = Format("_ST250_DotB-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST250_DotB.raw" : "";
		break;
	case ST250DOTABIMG:
		fileName = Format("_ST250_DotAB-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST250_DotAB.raw" : "";
		break;
	case ST250FLOODIMG:
		fileName = Format("_ST250_Flood-%d.raw",suffix);
		//(suffix == 0) ? fileName = "_ST250_Flood.raw" : "";
		break;
	default:
		break;
	}

	return fileName;
	//return string();
}

std::string fnGetJSONFileName(DUTIMGNAME prefix, int suffix)
{
	string fileName;

	switch (prefix)
	{
	case ST200MTFIMG:
		fileName = Format("_ST200_MTF-%d.json", suffix );
		//(suffix == 0) ? fileName = "_ST200_MTF.json" : "";
		break;
	case ST200DOTIMG:
		fileName = Format("_ST200_Dot-%d.json", suffix );
		//(suffix == 0) ? fileName = "_ST200_Dot.json" : "";
		break;
	case ST200DOTAIMG:
		fileName = Format("_ST200_DotA-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST200_DotA.json" : "";
		break;
	case ST200DOTBIMG:
		fileName = Format("_ST200_DotB-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST200_DotB.json" : "";
		break;
	case ST200DOTABIMG:
		fileName = Format("_ST200_DotAB-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST200_DotAB.json" : "";
		break;
	case ST200FLOODIMG:
		fileName = Format("_ST200_Flood-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST200_Flood.json" : "";
		break;
	case ST600MTFIMG:
		fileName = Format("_ST600_MTF-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST600_MTF.json" : "";
		break;
	case ST600DOTIMG:
		fileName = Format("_ST600_Dot-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST600_Dot.json" : "";
		break;
	case ST600DOTAIMG:
		fileName = Format("_ST600_DotA-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST600_DotA.json" : "";
		break;
	case ST600DOTBIMG:
		fileName = Format("_ST600_DotB-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST600_DotB.json" : "";
		break;
	case ST600DOTABIMG:
		fileName = Format("_ST600_DotAB-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST600_DotAB.json" : "";
		break;
	case ST600FLOODIMG:
		fileName = Format("_ST600_Flood-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST600_Flood.json" : "";
		break;
	case ST250MTFIMG:
		fileName = Format("_ST250_MTF-%d.json", suffix);
		//(suffix == 0) ? fileName = "_ST250_MTF.json" : "";
		break;
	case ST250DARKIMG:
		fileName = Format("_ST250_Dark-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST250_Dark.json" : "";
		break;
	case ST250DOTIMG:
		fileName = Format("_ST250_Dot-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST250_Dot.json" : "";
		break;
	case ST250DOTAIMG:
		fileName = Format("_ST250_DotA-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST250_DotA.json" : "";
		break;
	case ST250DOTBIMG:
		fileName = Format("_ST250_DotB-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST250_DotB.json" : "";
		break;
	case ST250DOTABIMG:
		fileName = Format("_ST250_DotAB-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST250_DotAB.json" : "";
		break;
	case ST250FLOODIMG:
		fileName = Format("_ST250_Flood-%d.json",suffix );
		//(suffix == 0) ? fileName = "_ST250_Flood.json" : "";
		break;
	default:
		break;
	}

	return fileName;
}


bool DeviceController::fnCreateJSONByName(JSONFORMAT stJSON, string filename)
{
	rapidjson::StringBuffer buf;
	//rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf); // it can word wrap

	writer.StartObject();

	try
	{
		writer.Key("RX");
		writer.StartObject();
		writer.Key("RxSettings");		writer.String(stJSON.RxSettings.c_str());
		writer.Key("RxAsicTemp_OFF");	writer.Double(stJSON.RxAsicTemp_OFF);
		writer.Key("RxAsicTemp_ON");	writer.Double(stJSON.RxAsicTemp_ON);
		writer.Key("Reg_0x120");		writer.String(stJSON.Reg_0x120.c_str());
		writer.Key("Reg_0x121");		writer.String(stJSON.Reg_0x121.c_str());
		writer.Key("Reg_0x146");		writer.String(stJSON.Reg_0x146.c_str());
		writer.Key("Reg_0x14A");		writer.String(stJSON.Reg_0x14A.c_str());  //TODO  要换顺序 只需要调整顺就行
		writer.Key("Reg_0x147");		writer.String(stJSON.Reg_0x147.c_str());
		writer.Key("Reg_0x15E");		writer.String(stJSON.Reg_0x15E.c_str());
		writer.Key("Reg_0x15F");		writer.String(stJSON.Reg_0x15F.c_str());
		writer.Key("aeShutterTime");		writer.Double(stJSON.aeShutterTime);
		writer.EndObject();

		writer.Key("TX");
		writer.StartObject();
		writer.Key("TxSettings");		writer.String(stJSON.TxSettings.c_str());
		writer.Key("subMode");		writer.String(stJSON.subMode.c_str());
		writer.Key("TxAsicTemp_OFF");	writer.Double(stJSON.TxAsicTemp_OFF);
		writer.Key("TxAsicTemp_ON");	writer.Double(stJSON.TxAsicTemp_ON);
		writer.Key("V_DOT");			writer.Double(stJSON.V_DOT);
		writer.Key("V_A");				writer.Double(stJSON.V_A);
		writer.Key("V_B");				writer.Double(stJSON.V_B);
		writer.Key("V_F");				writer.Double(stJSON.V_F);
		writer.Key("I_DOT");			writer.Double(stJSON.I_DOT);
		writer.Key("I_A");				writer.Double(stJSON.I_A);
		writer.Key("I_B");				writer.Double(stJSON.I_B);
		writer.Key("I_F");				writer.Double(stJSON.I_F);
		writer.Key("PW_A");				writer.Double(stJSON.PW_A);
		writer.Key("PW_B");				writer.Double(stJSON.PW_B);
		writer.Key("PW_DOT");			writer.Double(stJSON.PW_DOT);
		writer.Key("PW_F");				writer.Double(stJSON.PW_F);
		writer.EndObject();

		writer.Key("DUT");
		writer.StartObject();
		writer.Key("Serial");			writer.String(stJSON.Serial.c_str());
		writer.Key("RxASICID");			writer.String(stJSON.RxASICID.c_str());
		writer.Key("TxASICID");			writer.String(stJSON.TxASICID.c_str());
		writer.Key("Config");			writer.String(stJSON.Config.c_str());
		writer.Key("NTCTemp_OFF");		writer.Double(stJSON.NTCTemp_OFF);
		writer.Key("NTCTemp_ON");		writer.Double(stJSON.NTCTemp_ON);
		writer.Key("RTrace_OFF");		writer.Double(stJSON.RTrace_OFF);
		writer.Key("RTrace_ON");		writer.Double(stJSON.RTrace_ON);
		writer.EndObject();

		int iSocketIndex = std::stoi(stJSON.SocketSN);
		string sSocketSN = std::to_string(iSocketIndex+1);
		writer.Key("TEST");
		writer.StartObject();
		writer.Key("Station");			writer.String(stJSON.Station.c_str());
		writer.Key("SocketSN");			writer.String(sSocketSN.c_str());
		writer.Key("DateTime");			writer.String(stJSON.DateTime.c_str());
		writer.Key("TEC_Temperature");	writer.Double(stJSON.TEC_Temperature);
		writer.Key("ImageFileName");	writer.String(stJSON.ImageFileName.c_str());
		writer.EndObject();

		writer.EndObject();

		const char* json_content = buf.GetString();
		fprintf(stdout, "json content: %s\n", json_content);

#ifdef _MSC_VER
		const char* file_name = filename.c_str();
#else
		const char* file_name = "testdata/out.json";
#endif
		std::ofstream outfile;
		outfile.open(file_name);
		if (!outfile.is_open()) {
			fprintf(stderr, "FAILED to open file to write: %s\n", file_name);   //这里要加正式打印
			return FALSE;
		}

		outfile << json_content << std::endl;
		outfile.close();
	}
	catch (const std::exception&)
	{
		//issue occur;

		return FALSE;
	}

	g_pOP->LogDebug(-1, __FUNCTION__, "Create Json by Path:%s", filename.c_str());
	return TRUE;
}


bool DeviceController::Read_Tx_ASIC_ID(int nSocIndex, string& tx) {
	std::vector<uchar> readBuffer;
	bool ret = m_BanffControl.Read_Tx_ASIC_ID(nSocIndex, readBuffer);

	int size = readBuffer.size();
	string txValue = "0x";
	if (size > 0)
	{
		for (size_t i = 0; i < size; i++)
		{
			uchar buf = readBuffer.at(i);
			txValue = Format("%s%02X", txValue.c_str(), buf);
		}
	}
	tx = txValue;
	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Read Tx ID:%s", txValue.c_str());
	return ret;
}

bool DeviceController::Read_Rx_ASIC_ID(int nSocIndex, string& rx)
{
	string txValue = "";
	bool ret = m_BanffControl.fnReadRx_ASIC_ID(nSocIndex, txValue);
	rx = txValue;

	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Read Rx ID:%s", txValue.c_str());
	return ret;
}

bool DeviceController::Read_Tx_ASIC_Trim(int nSocIndex, string & trim)
{
	bool ret = m_BanffControl.fnReadTx_ASIC_Trim(nSocIndex, trim);

	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Read Rx Trim:%s", trim.c_str());
	return ret;
}

bool DeviceController::fnReadRTraceValue(int nSocIndex, double *RTraceValue) {
	unsigned short ADC_READOUT;
	double RPU = 332000;

	bool status = m_BanffControl.fnReadRTraceValue(nSocIndex, ADC_READOUT);
	double ADC_V = (double)(1.5 / 4095) * ADC_READOUT;
	*RTraceValue = ADC_V * RPU / (1.5 - ADC_V);

	ADC_READOUT = ADC_READOUT / 1000.0;
	*RTraceValue = *RTraceValue / 1000.0;

	g_pOP->LogDebug(nSocIndex,__FUNCTION__, (Format("ADC_V:%f" ,(ADC_V)).c_str()));
	g_pOP->LogDebug(nSocIndex,__FUNCTION__, "dRtrace:%f" , *RTraceValue);

	return status;
}

bool DeviceController::fnReadPinFaultValue(int nSocIndex, string &pinFault1, string& pinFault2)
{
	std::string value1 = "";
	std::string value2 = "";
	ushort uPinFault_1, uPinFault_2;
	bool ret = m_BanffControl.fnCheckRegValue(nSocIndex, uPinFault_1, uPinFault_2);
	value1 = to_string(uPinFault_1);// Format("0x%X", uPinFault_1);
	value2 = to_string(uPinFault_2);// Format("0x%X", uPinFault_2);
	pinFault1 = value1;
	pinFault2 = value2;
	return ret;
}

bool DeviceController::fnAdjustIntergretionTime(int nSocIndex, WORD ValTime, std::string & ValTimeCheck, std::string &data147)
{
	return false;

	// 0x18  0x146 
	ushort reg_0x146 = 0x146;
	//ret_write = mCanyonBanff.WriteI2C_16_Bit(nSocIndex, BANFF_RX_SLAVE_ADDRESS, BANFF_RX_INTERGRETION_TIME_ADDR, ValTime);
	//ValTimeCheck = mCanyonBanff.I2cRead(nSocIndex, strSlave, strAddrRead_3, nAddrLen, nDataLen);
	bool ret_write = m_BanffControl.I2cWrite16BitByte(nSocIndex, true, reg_0x146, ValTime);
	string value = m_BanffControl.I2cReadByte(nSocIndex, true, reg_0x146, 2);
	ValTimeCheck = value;
	data147 = m_BanffControl.I2cReadByte(nSocIndex, true, 0x147, 2);

	Sleep(100); //500  200  0712
	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "AdjustIntergretionTime,board:%d ValTime:%X,ValTimeCheck:%s data of 0x147:%s",nSocIndex,ValTime,ValTimeCheck.c_str(), data147.c_str());
	return ret_write;
}

bool DeviceController::fnReadTECTemper(int nSocIndex, float & TECTempValue)
{
	bool ret = false;
	try
	{
		QString sCOM = QString("STEC_PORT%1").arg(nSocIndex+1);
		//QString sCOM = QString("\\\\.\\COM%1").arg(nSocIndex);
		ret = m_StationTEC.fnReadTEC(sCOM, TECTempValue);
	}
	catch (const std::exception&)
	{
		ret = false;
	}
	
	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Read TEC Temper:%f", TECTempValue);
	qDebug() << "Read TEC Temper:" << TECTempValue;
	return ret;
}
bool DeviceController::setTECTemper(int nSocIndex, float & TECTempValue)
{
	bool ret = false;
	//TODO set and get tec 
	//double tecTemp = 0.0;

	try
	{
		QString sCOM = QString("STEC_PORT%1").arg(nSocIndex+1);
		ret = m_StationTEC.fnSetTEC(sCOM, TECTempValue);
	}
	catch (const std::exception&)
	{
		ret = false;
	}

	g_pOP->LogInfo(nSocIndex,__FUNCTION__, "Set TEC To Temper Value:%f", TECTempValue);
	qDebug() << "SET TEC Temper:" << TECTempValue;
	return ret;
}
bool DeviceController::setTECOffset(int nSocIndex, float & TECTempValue)
{
	bool ret = false;
	//TODO set and get tec 
	//double tecTemp = 0.0;

	try
	{
		QString sCOM = QString("STEC_PORT%1").arg(nSocIndex + 1);
		ret = m_StationTEC.fnSetTEC_OFFSET(sCOM, TECTempValue);
	}
	catch (const std::exception&)
	{
		ret = false;
	}

	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Set TEC Offset Value:%f", TECTempValue);
	qDebug() << "SET TEC offset:" << TECTempValue;
	return ret;
}

bool DeviceController::fnOpenLightPanel(QString Station)
{
	bool ret = false;
	QString reading;
	if (Station == GROUP_SFR60)
	{
		ret = m_PanelLight60.fnLIghtConnect(g_pINSP->m_SFR60Setting.GetString("LightPanel_IP","192.168.5.30"),
			g_pINSP->m_SFR60Setting.GetString("LightPanel_Port", "6600"));

		m_PanelLight60.fnLIghtOpenALL();
		
		ret = m_PanelLight60.fnLIghtSetLight(g_pINSP->m_SFR60Setting.GetString("LightPanel_CMD1", "SA0255#\n"), reading);
		ret = m_PanelLight60.fnLIghtSetLight(g_pINSP->m_SFR60Setting.GetString("LightPanel_CMD2", "SB0255#\n"), reading);
		ret = m_PanelLight60.fnLIghtSetLight(g_pINSP->m_SFR60Setting.GetString("LightPanel_CMD3", "SC0255#\n"), reading);
		ret = m_PanelLight60.fnLIghtSetLight(g_pINSP->m_SFR60Setting.GetString("LightPanel_CMD4", "SD0255#\n"), reading);
	}
	else if(Station == GROUP_SFR25)
	{
		ret = m_PanelLight25.fnLIghtConnect(g_pINSP->m_SFR25Setting.GetString("LightPanel_IP", "192.168.5.31"),
			g_pINSP->m_SFR25Setting.GetString("LightPanel_Port", "6600"));

		m_PanelLight25.fnLIghtOpenALL();

		ret = m_PanelLight25.fnLIghtSetLight(g_pINSP->m_SFR25Setting.GetString("LightPanel_CMD1", "SA0255#\n"), reading);
		ret = m_PanelLight25.fnLIghtSetLight(g_pINSP->m_SFR25Setting.GetString("LightPanel_CMD2", "SB0255#\n"), reading);
		ret = m_PanelLight25.fnLIghtSetLight(g_pINSP->m_SFR25Setting.GetString("LightPanel_CMD3", "SC0255#\n"), reading);
	}
	else if (Station == GROUP_SFR20)
	{
		ret = m_PanelLight20.fnLIghtConnect(g_pINSP->m_SFR20Setting.GetString("LightPanel_IP", "192.168.5.32"),
			g_pINSP->m_SFR20Setting.GetString("LightPanel_Port", "6600"));

		m_PanelLight20.fnLIghtOpenALL();

		ret = m_PanelLight20.fnLIghtSetLight(g_pINSP->m_SFR20Setting.GetString("LightPanel_CMD1", "SA0255#\n"), reading);
		ret = m_PanelLight20.fnLIghtSetLight(g_pINSP->m_SFR20Setting.GetString("LightPanel_CMD2", "SB0255#\n"), reading);
	}
	else
	{
		//LOGHERE
		g_pOP->LogInfo(-1, __FUNCTION__, "Open light Success.Panal:%s", Station.toLatin1().data());
	}

	if (!ret)
	{
		//LOGHERE
		g_pOP->LogError(-1, __FUNCTION__, "Open light FAILEDPanal:%s", Station.toLatin1().data());
		return false;
	}



	return true;
}

bool DeviceController::fnShutDownLightPanel(QString Station)
{
	bool ret = false;
	QString reading;
	if (Station == GROUP_SFR60)
	{
		//ret = m_PanelLight60.fnLIghtConnect(g_pINSP->m_SFR60Setting.GetString("LightPanel_IP", "192.168.5.30"),
		//	g_pINSP->m_SFR60Setting.GetString("LightPanel_Port", "6600"));

		ret = m_PanelLight60.fnLIghtSetLight("SA0000#\n", reading);
		ret = m_PanelLight60.fnLIghtSetLight("SB0000#\n", reading);
		ret = m_PanelLight60.fnLIghtSetLight("SC0000#\n", reading);
		ret = m_PanelLight60.fnLIghtSetLight("SD0000#\n", reading);

		m_PanelLight60.fnLIghtDisConnect();
	}
	else if (Station == GROUP_SFR25)
	{
		//ret = m_PanelLight25.fnLIghtConnect(g_pINSP->m_SFR25Setting.GetString("LightPanel_IP", "192.168.5.31"),
		//	g_pINSP->m_SFR25Setting.GetString("LightPanel_Port", "6600"));

		ret = m_PanelLight25.fnLIghtSetLight("SA0000#\n", reading);
		ret = m_PanelLight25.fnLIghtSetLight("SB0000#\n", reading);
		ret = m_PanelLight25.fnLIghtSetLight("SC0000#\n", reading);

		m_PanelLight25.fnLIghtDisConnect();
	}
	else if (Station == GROUP_SFR20)
	{
		//ret = m_PanelLight20.fnLIghtConnect(g_pINSP->m_SFR20Setting.GetString("LightPanel_IP", "192.168.5.32"),
		//	g_pINSP->m_SFR20Setting.GetString("LightPanel_Port", "6600"));

		ret = m_PanelLight20.fnLIghtSetLight("SA0000#\n", reading);
		ret = m_PanelLight20.fnLIghtSetLight("SB0000#\n", reading);

		m_PanelLight20.fnLIghtDisConnect();
	}
	else
	{
		//LOGHERE
	}

	if (!ret)
	{
		//LOGHERE
		return false;
	}

	return true;
}

bool DeviceController::fnGetACLValue(double & Tx, double & Ty)
{
	Tx = Ty = 0;

	if (g_pDEV->m_ACL.Connect("192.168.5.33", 8001))
	{
		for (int i = 0; i < 3; i++)
		{
			Sleep(100);
			char buf[1024] = { 0 };
			g_pDEV->m_ACL.GetReceiveData(buf, sizeof(buf));

			QString str = buf;
			QStringList lst = str.split(",");
			if (lst.size() < 5)
			{
				continue;
			}

			if (lst.at(1) == "N")
			{
				continue;
			}
			else
			{
				Ty = lst.at(2).toDouble();
				Tx = -lst.at(3).toDouble();
				break;
			}
		}
		g_pDEV->m_ACL.Close();
		g_pDEV->m_ACL.ClearReceiveData();

		if (Tx != 0 && Ty != 0)
			return true;
	}

	return false;
}

bool DeviceController::fnStationMvsImpl()
{
	for (int i = 0; i < 3; i++)
	{
		string cam = m_mvsCam.findAll();
		cam = cam.substr(0, cam.size() - 2);
		bool ret = m_mvsCam.init(cam);
		if (!ret)
		{
			g_pOP->LogError(-1, __FUNCTION__, "Open Station Vision Camera Failed!!!");
			MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Open Station Vision Camera Failed!!!", 0);			
		}
		else
		{
			g_pOP->LogInfo(-1, __FUNCTION__, "Open Station Vision Camera Success!!!");
			return true;
		}
	}
	return false;
}

bool DeviceController::fnStationMvsDestory()
{
	return m_mvsCam.close();;
}


//Station vision to get rotation Z		PC1
bool DeviceController::fnCapture(int nSocIndex, QString path)
{
	QDir dir(path);
	QStringList fileList;
	fileList = dir.entryList({ "*.bmp" }, QDir::Files | QDir::Readable, QDir::Name);
	for each (QString file in fileList)
	{
		QFile f;
		f.remove(path + "\\" + file);
	}

	string imgPath = m_mvsCam.capture();
	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Get capture, path = %s", imgPath.c_str());
	if (imgPath == "Can not get one frame")
	{
		g_pOP->LogError(nSocIndex, __FUNCTION__, "Get Capture Failed!!!");
		MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Get Capture Failed!!!", 0);
		return false;
	}

	QString file = QString("%1\\Image1_TZ%2_Socket%3.bmp").arg(path).arg(0).arg(nSocIndex + 1);
	if (!QFile::copy(imgPath.c_str(), file))
	{
		//return false;
	}
	QFile::remove(imgPath.c_str());

	return true;
}

//PC4
bool DeviceController::fnGetPictureDegree(int nSocIndex, QString file, QString & outPath, float & degree, bool bDebug)
{
	QString copyFile = file;

	cv::Mat imgGray = imread(copyFile.toStdString(), 0);
	if (imgGray.empty())
	{
		g_pOP->LogError(nSocIndex, __FUNCTION__, "Image is empty, path = %s", copyFile.toStdString().c_str());
		return false;
	}	

	cv::Mat imgRGB;
	cv::cvtColor(imgGray, imgRGB, cv::COLOR_GRAY2RGB);

	ImageProcessPara imgProcPara;
	imgProcPara.Init();
	imgProcPara.AdaptiveModel = 5;
	imgProcPara.DiffValue = -10;
	imgProcPara.ErosionFlag = 0;
	imgProcPara.MinMarkNum2 = 5;
	imgProcPara.MaxMarkNum2 = 150;
	imgProcPara.HeightWidthRatio2 = 0.5;
	imgProcPara.ROIStartX = g_pINSP->m_StationVisionSetting.GetInt("ROIStartX", 190);
	imgProcPara.ROIStartY = g_pINSP->m_StationVisionSetting.GetInt("ROIStartY", 510);
	imgProcPara.ROIEndX = g_pINSP->m_StationVisionSetting.GetInt("ROIEndX", 1300);
	imgProcPara.ROIEndY = g_pINSP->m_StationVisionSetting.GetInt("ROIEndY", 1600);

	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "ROI Value: StartX:%d, EndX:%d, StartY:%d, EndY:%d",
		imgProcPara.ROIStartX, imgProcPara.ROIEndX, imgProcPara.ROIStartY, imgProcPara.ROIEndY);

	float _degree = 0;
	cv::Point2f midPoint;
	MilDetecDegree(imgGray, imgRGB, imgProcPara, _degree, midPoint);
	
	double offset = g_pINSP->m_StationVisionSetting.GetDouble("OFFSET_SOCKET" + QString::number(nSocIndex + 1), 0);
	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Degree: %f, Offset:%f", _degree, offset);

	float tz = _degree - 90.0 + offset;	
	degree = tz;
	if (_degree == -999)
	{
		if (bDebug)
		{
			QString NewFile1 = copyFile;
			NewFile1.replace("TZ0", "TZ" + QString::number(-999));
			QFile::rename(copyFile, NewFile1);

			QString NewFile2 = NewFile1;
			NewFile2.replace("Image1", "Image2");
			string bmpFilePath = NewFile2.toStdString();
			imwrite(bmpFilePath.c_str(), imgRGB);
			outPath = NewFile2;
			degree = 0.0001;

			g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Debug Detec NG!!!, out path = %s", NewFile2.toStdString().c_str());
		}	
		else
		{
			outPath.clear();
			degree = 0.0001;
			g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Detec NG!!!");
		}
		return false;
	}

	QString NewFile1 = copyFile;
	NewFile1.replace("TZ0", "TZ" + QString::number(degree));
	QFile::rename(copyFile, NewFile1);

	QString NewFile2 = NewFile1;
	NewFile2.replace("Image1", "Image2");
	string bmpFilePath = NewFile2.toStdString();
	imwrite(bmpFilePath.c_str(), imgRGB);
	outPath = NewFile2;

	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Detec OK, value:%f, out path = %s", degree, NewFile2.toStdString().c_str());

	return true;
}

bool DeviceController::MeasureStrobe(int nSocIndex, float &fVol, float &fRaise, float &fFall, float &fDuration)
{

	int ret = 0;
	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Start strobe test");
	if (g_pDEV->m_StrobeIns.fnConnectBoard(g_pINSP->m_StrobeBoardSetting.GetString("Strobe_IP", "192.168.5.19"),
		g_pINSP->m_StrobeBoardSetting.GetString("StrobeData_Port", "15"),
		g_pINSP->m_StrobeBoardSetting.GetString("StrobeCMD_Port", "502")))
	{
		ret = g_pDEV->m_StrobeIns.fnStartTrigger();
		Sleep(500);
		g_pDEV->m_BanffControl.fnFireSync(nSocIndex); //just for send out a sync
		Sleep(1000);
		ret = g_pDEV->m_StrobeIns.fnReadTrigger();

		ret = g_pDEV->m_StrobeIns.fnGrabeStrobeData(fVol, fRaise, fFall, fDuration);
		g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Vol:[%f] Raise:[%f] Fall:[%f] Duration:[%f]", fVol, fRaise, fFall, fDuration);
		ret = g_pDEV->m_StrobeIns.fnDisConnectBoard();

	}
	else
	{
		MessageBoxManage::Instance()->PostMessageBox("", QString("Strobe board Connect FAILED,Socket:%1 ").arg(nSocIndex + 1), 0);
		g_pOP->LogInfo(-1, __FUNCTION__, "Strobe board Connect FAILED");
	}

	g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Start strobe test");

	return ret;
}


static std::mutex csv_mutex;
bool append_csv_fileold(std::string csv_path, std::string buf)
{
	if (buf.empty())
	{
		return false;
	}
	unique_lock<mutex> lock(csv_mutex);
	fstream out;
	int retry = 0;
	bool ret = false;
	while (ret == false && retry < 3) {
		out.open(csv_path, ios::app);
		ret = out.is_open();
		if (ret) {
			break;
		}
		::MessageBox(0, L"please close execl and copy data", L"warn", MB_OK);
		retry++;
		if (retry == 3)
			return false;
	}
	out.write(buf.c_str(), buf.length());
	out.close();
	return true;
}

bool add_csv_file_context(std::string csv_pah, list<string> context_v)
{
	std::error_code error;
	stringstream csv_buf;
	for (auto s : context_v)
	{
		csv_buf << s << ",";
	}
	csv_buf << "\n";
	return append_csv_fileold(csv_pah, csv_buf.str());
}

list<string> vec_to_list(vector<string> m_vec)
{
	list<string> m_list;
	m_list.assign(m_vec.begin(), m_vec.end());
	return m_list;
}

bool PushListToPacketList(vector<string> &m_context, vector<string> list, int count)
{
	int size = list.size();
	for (size_t i = 0; i < count; i++)
	{
		string value = " ";
		if (i < size)
		{
			value = list[i];
		}
		m_context.push_back(value);
	}
	return true;
}

vector<string> split2(const std::string & s, std::string delim)
{
	std::vector<std::string> elems;
	std::stringstream stream(s);
	std::string item;
	size_t n = delim.length();
	try {
		while (std::getline(stream, item, delim.at(0)))
		{
			for (int i = 1; i < n; i++) {
				stream.ignore(n - 1, delim.at(i));
			}
			elems.push_back(item);
		}
		return elems;
	}
	catch (...) {
		throw std::runtime_error("split2 Parsing error");
	}
}

string getTimestamp()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	string sTimestamp = Format("%04d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return  sTimestamp;
}

//QString getQStringTimeStamp() {
//	SYSTEMTIME st;
//	GetLocalTime(&st);
//	QString sTime = QString("%1-%2-%3 %4:%5:%6:%7").arg(st.wYear)
//		.arg(st.wMonth, 2, 10, QChar('0')) //// 表示2个字宽，10进制，未满字宽用'0'填补
//		.arg(st.wDay, 2, 10, QChar('0'))
//		.arg(st.wHour, 2, 10, QChar('0'))
//		.arg(st.wMinute, 2, 10, QChar('0'))
//		.arg(st.wSecond, 2, 10, QChar('0'))
//		.arg(st.wMilliseconds, 3, 10, QChar('0'));
//	return sTime;
//}

void fnCloseHvsSocket(bool isSaveTXnvm)
{
	if (PC1() ||PC4())
	{
		return;
	}
	bool res = false;
	for (int i = 0; i < 4; i++)
	{
		if (isSaveTXnvm)
		{
			res = g_pDEV->fnCanyouPowerOff(i, "AutoPowerOff");
		}
		else
		{
			res = g_pDEV->m_BanffControl.fnPowerOFF(i); 
		}
		
		if (!res)
		{
		}
	}
}


int appendContentListToCSV(QString filePath, QStringList list, bool iWithLimit) {
	// add one line to csv .to add multiple line,  : QStringList onelinelist = lines.join("\n");

	QString writeStr = list.join(",") .append("\n");
	QByteArray arr = writeStr.toLocal8Bit();

	QFile filewrite(filePath); //_SFR60.csv/
	bool ret = filewrite.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
	if (ret)
	{
		int fileSize = filewrite.size();
		/*if (fileSize == 0)
		{
			filewrite.write("BANFF_SCREEN\n");
		}*/

		filewrite.write(arr);

		/*if (fileSize == 0 && iWithLimit)
		{
			filewrite.write("Upper Limit----->\n");
			filewrite.write("Lower Limit----->\n");
		}*/
	}
	filewrite.close();

	return ret;
}

int PushSMUBufferToQStringList(QStringList &contextList, QString buffer, int count)
{
	//vector<string> smuBufferList600DOTB = split2(smuBuffer600DOTB, "|");
	QStringList bufferList = buffer.split("|");
	int size = bufferList.size();
	for (size_t i = 0; i < count; i++)
	{
		QString value = " ";
		if (i < size)
		{
			value = bufferList[i];
		}
		contextList.push_back(value);
	}
	return true;
}

std::string MergeJsonFormatToString(JSONFORMAT buffer) {
	std::string sVandI =Format("%f|%f|%f|%f|%f|%f|%f|%f",  (buffer.V_DOT) , (buffer.V_A) , (buffer.V_B) , (buffer.V_F) ,
		(buffer.I_DOT) , (buffer.I_A) , (buffer.I_B) , (buffer.I_F));
	return sVandI;
}

int HexToInt(std::string & hexString)
{
	int Dec = (int)strtol(hexString.c_str(), NULL, 16);
	return Dec;
}
float hextoaeShutterTime(std::string & hexString) {
	//string  sFrameLength = DataResultsArryST200DOT[i].Reg_0x15E;
	if (hexString.empty() || hexString.length()<=0)
	{
		return 0.0;
	}
	int frame = HexToInt(hexString);
	float shutterTime = 8.444 * frame; // /1000.0
	return shutterTime;
}
QString getTimeIntervalStringFromStartTime(QDateTime startTime, QDateTime currentTime) {
	//显示运行总时间
	QDateTime interval(QDate(2000, 1, 1), QTime(0, 0, 0, 0));	//以2000-1-1 0:0:0::0为基准，加上程序运行的总秒数，再用toString转换
	QString strInterval = "";
	if (startTime.isNull() || currentTime.isNull())
	{
		return strInterval;
	}
	if (startTime.addDays(1) > currentTime)
	{
		strInterval = interval.addSecs(startTime.secsTo(currentTime)).toString("hh:mm:ss");
	}
	else
	{
		strInterval = interval.addSecs(startTime.secsTo(currentTime)).toString("hh:mm:ss");
		//strInterval = interval.addSecs(startTime.secsTo(currentTime)).toString("ddd hh:mm:ss"); //test ddd周
		int day = startTime.daysTo(currentTime);
		strInterval = QString::number(day) + "D " + strInterval;
	}
	return strInterval;
}