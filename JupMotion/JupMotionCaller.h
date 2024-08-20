#pragma once

//#include "MotionCard/MotionController.h"
#include "MotionCard/AdlinkController.h"
#include "PluginBase/JupCaller.h"
#include "JupCore.h"

#define TESTSLEEP 0

#define CHECK_NO	(-10086)

class JupDefine
{
public:
	enum LogLevel
	{
		Error = 0,
		Info,
		Warn,
		Debug,
	};
};

#define LOG_MAXSIZE (256)
class JupMotionCaller : public JupCaller
{
public:
	JupMotionCaller();
	virtual ~JupMotionCaller();

	/*
		�ڸú������ض��ĳ�ʼ����������ƽ̨���øú���

		ʾ����Ĭ�ϵ��ø���ӿڵ�ʵ��JupCaller::Initialize();
		���ݵ�ǰ�����ʵ����Ҫѡ���������
	*/
	int Initialize() override;

	/*
		ͳһ�ڸú�����ע�����в�������ĺ���

		ʾ����Plugin_Method_Add(DemoTestCaller, Demo_msleep100);
		����DemoTestCallerΪ��ǰ���������Demo_msleep100Ϊ��Ҫע��ĺ�����
	*/
	int RegisterMethod() override;

	int MainTestStart(JupData& resultTable);

	int ResetData(JupData& data);

	int TestWaitSleep(JupData& data);

	int TestStartCheck(JupData& resultTable);
	// Alpha
	int moveToPosA1(JupData& resultTable);
	int moveToPosA2(JupData& resultTable);
	int moveToPosA3(JupData& resultTable);
	int moveToPosA4(JupData& resultTable);
	int moveToPosA5(JupData& resultTable);
	int moveToPosA6(JupData& resultTable);
	int moveToPosA7(JupData& resultTable);
	int moveToPosB1(JupData& resultTable);
	int moveToPosB2(JupData& resultTable);
	int moveToPosB3(JupData& resultTable);
	int moveToPosB4(JupData& resultTable);
	int moveToPosB5(JupData& resultTable);
	int moveToPosB6(JupData& resultTable);
	int moveToPosB7(JupData& resultTable);
	int moveToPosC1(JupData& resultTable);
	int moveToPosC2(JupData& resultTable);
	int moveToPosC3(JupData& resultTable);
	int moveToPosC4(JupData& resultTable);
	int moveToPosC5(JupData& resultTable);
	int moveToPosC6(JupData& resultTable);
	int moveToPosC7(JupData& resultTable);
	int moveToPosZero(JupData& resultTable);
	int AxisTxTyHome(JupData& resultTable);

	int WaitStartTestSignal(JupData& resultTable);
	int AlarmMotionError(JupData& resultTable);

	// pnp����DOE
	// ����doe����
	int PnpDoeResetData(JupData& data);
	// pnp�����
	int AxisLoadPnpHome(JupData& resultTable);
	// ���÷���ʵʱλ��
	int AxisLoadResetPosition(JupData& resultTable);
	// pnp���ƶ�������λ��
	int AxisLoadPnpToPosPhoto(JupData& resultTable);
	// pnp���ƶ���tray��λ��
	int AxisLoadPnpToPosTray(JupData& resultTable);
	// X&R���ƶ�������λ��
	int AxisXRLoadPnpToPosTray(JupData& resultTable);
	// Z�������ƶ�һ��
	int AxisZPeriodicMotion(JupData& resultTable);
	// pnp�����tray��ȡdut
	int CylLoadPnpToPickDut(JupData& resultTable);
	// ���÷��Ĳ���
	int AxisLoadSetParameter(JupData& resultTable);
	// ����pnp���ƶ���socket��dutλ��ָ��
	int AxisLoadPnpCommandToPosSocket(JupData& resultTable);
	// ���ȴ�pnp���ƶ���socket��dutλ��ָ�����
	int AxisLoadPnpWaitMoveToPosSocket(JupData& resultTable);
	// pnp�����dut��socket
	int CylLoadPnpToPutDut(JupData& resultTable);

	int IsTheLastStep(JupData& resultTable);

	// DIL����ɼ�DUTͼ�������
	// DIL��������
	int AxisDILXDILYHome(JupData& resultTable);
	// DIL������ƶ�������λ��
	int AxisDILXDILYToSocketPos(JupData& resultTable);


	//Auto У׼����
	int CalibraTestStartCheck(JupData& data);
	//Group A
	int moveToReadyPnpPos(JupData& data);

	int takePhotoToCalibraPosA1(JupData& data);
	int moveToPnpCailbraPosA1(JupData& data);

	int takePhotoToCalibraPosA2(JupData& data);
	int moveToPnpCailbraPosA2(JupData& data);

	int takePhotoToCalibraPosA3(JupData& data);
	int moveToPnpCailbraPosA3(JupData& data);

	int takePhotoToFinalPosA4(JupData& data);
	int saveCurrentPnpPos(JupData& data);

	//GroupB
	int moveToReadyNozzlePos(JupData& data);

	int takePhotoToCalibraPosB1(JupData& data);
	int moveToPnpCailbraPosB1(JupData& data);

	int takePhotoToCalibraPosB2(JupData& data);
	int moveToPnpCailbraPosB2(JupData& data);

	int takePhotoToCalibraPosB3(JupData& data);
	int moveToPnpCailbraPosB3(JupData& data);

	int takePhotoToFinalPosB4(JupData& data);
	int saveCurrentPnpAndNozzlePos(JupData& data);

	//GroupC
	int CalPnpDistance(JupData& data);


private:
	void RzTxMoveToPos(const std::string& pos_name);
	void MoveToReadyPos(const std::string& pos_name);
	void MoveToCailbraPos(double AxisX_distance, double AxisY_distance, double maxVel, double accVel, double decVel);
	void MoveToNozzleCailbraPos(double AxisX_distance, double AxisY_distance, double AxisR_distance, double maxVel, double accVel, double decVel);

private:
	// log
	void PluginWriteLog(JLogLevel level, std::string strFunc, const std::string str);

private:

	AdlinkController* m_pMotion;
};

