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
		在该函数做特定的初始化操作，由平台调用该函数

		示例：默认调用父类接口的实现JupCaller::Initialize();
		根据当前插件的实际需要选择添加内容
	*/
	int Initialize() override;

	/*
		统一在该函数内注册所有测试项方法的函数

		示例：Plugin_Method_Add(DemoTestCaller, Demo_msleep100);
		其中DemoTestCaller为当前类的类名，Demo_msleep100为需要注册的函数名
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

	// pnp飞拍DOE
	// 重置doe数据
	int PnpDoeResetData(JupData& data);
	// pnp轴回零
	int AxisLoadPnpHome(JupData& resultTable);
	// 重置飞拍实时位置
	int AxisLoadResetPosition(JupData& resultTable);
	// pnp轴移动到拍照位置
	int AxisLoadPnpToPosPhoto(JupData& resultTable);
	// pnp轴移动到tray盘位置
	int AxisLoadPnpToPosTray(JupData& resultTable);
	// X&R轴移动到工作位置
	int AxisXRLoadPnpToPosTray(JupData& resultTable);
	// Z轴上下移动一次
	int AxisZPeriodicMotion(JupData& resultTable);
	// pnp吸嘴从tray盘取dut
	int CylLoadPnpToPickDut(JupData& resultTable);
	// 设置飞拍参数
	int AxisLoadSetParameter(JupData& resultTable);
	// 发送pnp轴移动到socket放dut位置指令
	int AxisLoadPnpCommandToPosSocket(JupData& resultTable);
	// 检查等待pnp轴移动到socket放dut位置指令完成
	int AxisLoadPnpWaitMoveToPosSocket(JupData& resultTable);
	// pnp吸嘴放dut到socket
	int CylLoadPnpToPutDut(JupData& resultTable);

	int IsTheLastStep(JupData& resultTable);

	// DIL相机采集DUT图像轴控制
	// DIL相机轴回零
	int AxisDILXDILYHome(JupData& resultTable);
	// DIL相机轴移动到拍照位置
	int AxisDILXDILYToSocketPos(JupData& resultTable);


	//Auto 校准动作
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

