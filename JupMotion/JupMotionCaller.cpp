#include "JupMotionCaller.h"
#include "JError.h"
#include "Macro.h"
#include "CPluginDlg.h"

#include <direct.h>
#include <io.h>
#include "../_INCLUDE/ProjectEvent.h"
using namespace ProjectEvent;

std::vector<std::string> m_TxAngle;
std::vector<std::string> m_TyAngle;

int test_count = 0;
std::string sub_folder;

#define Plugin_Method_Add(T, f) appendMethod(#f, transformMethod<T>(&T::f));
static JError s_error;

JupMotionCaller::JupMotionCaller()
{
	m_pMotion = g_pMotion;
}

JupMotionCaller::~JupMotionCaller()
{

}

/*
	在该函数做特定的初始化操作，一般由平台调用该函数

	示例：默认调用父类接口的实现JupCaller::Initialize();
	根据当前插件的实际需要选择添加内容
*/
int JupMotionCaller::Initialize()
{
	return JupCaller::Initialize();
}

/*
	统一在此注册所有测试项方法的函数

	示例：Plugin_Method_Add(DemoTestCaller, Demo_msleep100);
	其中参数1：DemoTestCaller为当前类的类名，参数2：Demo_msleep100为需要注册的函数名
*/
int JupMotionCaller::RegisterMethod()
{
	Plugin_Method_Add(JupMotionCaller, MainTestStart);
	Plugin_Method_Add(JupMotionCaller, TestWaitSleep);
	Plugin_Method_Add(JupMotionCaller, ResetData);
	Plugin_Method_Add(JupMotionCaller, TestStartCheck);
	// Alpha
	Plugin_Method_Add(JupMotionCaller, moveToPosA1);
	Plugin_Method_Add(JupMotionCaller, moveToPosA2);
	Plugin_Method_Add(JupMotionCaller, moveToPosA3);
	Plugin_Method_Add(JupMotionCaller, moveToPosA4);
	Plugin_Method_Add(JupMotionCaller, moveToPosA5);
	Plugin_Method_Add(JupMotionCaller, moveToPosA6);
	Plugin_Method_Add(JupMotionCaller, moveToPosA7);
	Plugin_Method_Add(JupMotionCaller, moveToPosB1);
	Plugin_Method_Add(JupMotionCaller, moveToPosB2);
	Plugin_Method_Add(JupMotionCaller, moveToPosB3);
	Plugin_Method_Add(JupMotionCaller, moveToPosB4);
	Plugin_Method_Add(JupMotionCaller, moveToPosB5);
	Plugin_Method_Add(JupMotionCaller, moveToPosB6);
	Plugin_Method_Add(JupMotionCaller, moveToPosB7);
	Plugin_Method_Add(JupMotionCaller, moveToPosC1);
	Plugin_Method_Add(JupMotionCaller, moveToPosC2);
	Plugin_Method_Add(JupMotionCaller, moveToPosC3);
	Plugin_Method_Add(JupMotionCaller, moveToPosC4);
	Plugin_Method_Add(JupMotionCaller, moveToPosC5);
	Plugin_Method_Add(JupMotionCaller, moveToPosC6);
	Plugin_Method_Add(JupMotionCaller, moveToPosC7);
	Plugin_Method_Add(JupMotionCaller, moveToPosZero);
	Plugin_Method_Add(JupMotionCaller, AxisTxTyHome);
	// pnp doe
	Plugin_Method_Add(JupMotionCaller, PnpDoeResetData);
	Plugin_Method_Add(JupMotionCaller, AxisLoadPnpHome);
	Plugin_Method_Add(JupMotionCaller, AxisLoadResetPosition);
	Plugin_Method_Add(JupMotionCaller, AxisLoadPnpToPosPhoto);
	Plugin_Method_Add(JupMotionCaller, AxisLoadPnpToPosTray);
	Plugin_Method_Add(JupMotionCaller, AxisXRLoadPnpToPosTray);
	Plugin_Method_Add(JupMotionCaller, AxisZPeriodicMotion);
	Plugin_Method_Add(JupMotionCaller, CylLoadPnpToPickDut);
	Plugin_Method_Add(JupMotionCaller, AxisLoadSetParameter);
	Plugin_Method_Add(JupMotionCaller, AxisLoadPnpCommandToPosSocket);
	Plugin_Method_Add(JupMotionCaller, AxisLoadPnpWaitMoveToPosSocket);
	Plugin_Method_Add(JupMotionCaller, CylLoadPnpToPutDut);
	// DIL
	Plugin_Method_Add(JupMotionCaller, AxisDILXDILYHome);
	Plugin_Method_Add(JupMotionCaller, AxisDILXDILYToSocketPos);

	Plugin_Method_Add(JupMotionCaller, AlarmMotionError);
	Plugin_Method_Add(JupMotionCaller, WaitStartTestSignal);
	Plugin_Method_Add(JupMotionCaller, IsTheLastStep);

	//Auto 校准动作
	Plugin_Method_Add(JupMotionCaller, CalibraTestStartCheck);
	Plugin_Method_Add(JupMotionCaller, moveToReadyPnpPos);

	Plugin_Method_Add(JupMotionCaller, takePhotoToCalibraPosA1);
	Plugin_Method_Add(JupMotionCaller, moveToPnpCailbraPosA1);

	Plugin_Method_Add(JupMotionCaller, takePhotoToCalibraPosA2);
	Plugin_Method_Add(JupMotionCaller, moveToPnpCailbraPosA2);

	Plugin_Method_Add(JupMotionCaller, takePhotoToCalibraPosA3);
	Plugin_Method_Add(JupMotionCaller, moveToPnpCailbraPosA3);

	Plugin_Method_Add(JupMotionCaller, takePhotoToFinalPosA4);
	Plugin_Method_Add(JupMotionCaller, saveCurrentPnpPos);

	Plugin_Method_Add(JupMotionCaller, moveToReadyNozzlePos);

	Plugin_Method_Add(JupMotionCaller, takePhotoToCalibraPosB1);
	Plugin_Method_Add(JupMotionCaller, moveToPnpCailbraPosB1);

	Plugin_Method_Add(JupMotionCaller, takePhotoToCalibraPosB2);
	Plugin_Method_Add(JupMotionCaller, moveToPnpCailbraPosB2);

	Plugin_Method_Add(JupMotionCaller, takePhotoToCalibraPosB3);
	Plugin_Method_Add(JupMotionCaller, moveToPnpCailbraPosB3);

	Plugin_Method_Add(JupMotionCaller, takePhotoToFinalPosB4);
	Plugin_Method_Add(JupMotionCaller, saveCurrentPnpAndNozzlePos);

	Plugin_Method_Add(JupMotionCaller, CalPnpDistance);


	return 0;
}

int JupMotionCaller::MainTestStart(JupData & resultTable)
{
	//jCore->notifyToMainGuI(new MainUIUpdateEvent("MachineStatus", "Running"));
	//jCore->notifyToMainGuI(new MainUIUpdateEvent("DutResult", "Testing"));
	//jCore->notifyToMainGuI(new MainUIUpdateEvent("CMD", "Main-TestStart"));
	//Sleep(200);

	//REQList reqlist = 0;//jCore->GetPreMtcpPacket().GetListByGroups(std::stringList());
	//resultTable.AddList(reqlist);

	//resultTable.AddLine(REQLine("station_information", "start_time", QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss")));
	//resultTable.AddLine(REQLine("TestCT", "CT_start_time", QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss")));
	return 0;
}

int JupMotionCaller::ResetData(JupData & data)
{
	test_count = 0;
	// 每日创建一个文件夹
	std::string file_path = jCore->GlobalSettings().ReadString("AlphaDoe", "ImagePath") + Jup::GetLocalTime(1);	
	if (access(file_path.c_str(), 0) == -1)
	{
		int flag = mkdir(file_path.c_str());
		if (flag != 0)
		{
			// 创建失败
			return -1;
		}
	}
	// 每次测试创建一个文件夹
	sub_folder = file_path + "/" + Jup::GetLocalTime(2);
	int flag = mkdir(sub_folder.c_str());
	if (flag != 0)
	{
		// 创建失败
		return -1;
	}
	// 清除位置角度记录值
	m_TxAngle.clear();
	m_TyAngle.clear();
	return 0;
}

int JupMotionCaller::TestWaitSleep(JupData & data)
{
	// 测试达一定次数睡眠等待一段时间
	int wait_circle = jCore->GlobalSettings().ReadInt("AlphaDoe", "WaitCircle");
	if ((test_count > 0) && (0 == (test_count % wait_circle)))
	{
		int coolling_time = jCore->GlobalSettings().ReadInt("AlphaDoe", "WaitTime");
		Sleep(coolling_time * 60 * 1000);
	}
	return 0;
}

int JupMotionCaller::TestStartCheck(JupData & resultTable)
{
	int save_circle = jCore->GlobalSettings().ReadInt("AlphaDoe", "SaveCircle");
	// 满足存图条件时创建文件夹存图
	if (0 == (test_count % save_circle))
	{
		char buf[256] = { 0 };
		sprintf_s(buf, "%s/Circle_%d_%s", sub_folder.c_str(), test_count, Jup::GetLocalTime(3));
		int flag = mkdir(buf);
		if (flag != 0)
		{
			// 创建失败
			return -1;
		}
		else
		{
			resultTable.SetValue("HikData", "SaveImage", true);
			resultTable.SetValue("HikData", "ImagePath", buf);
		}
	}
	else
	{
		// 不满足存图条件时临时存图，后面删掉
		resultTable.SetValue("HikData", "SaveImage", false);
		resultTable.SetValue("HikData", "ImagePath", sub_folder.c_str());
	}

	// 更新测试计数
	resultTable.SetValue("HikData", "TestCount", test_count);
	resultTable.SetValue("HikData", "TestStartTime", Jup::GetLocalTime(0));
	test_count++;

	return 0;
}

int JupMotionCaller::moveToPosA1(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "A1");
	RzTxMoveToPos(POSNAME_A1);
	Sleep(100);
	return 0;
}

int JupMotionCaller::moveToPosA2(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "A2");
	RzTxMoveToPos(POSNAME_A2);
	return 0;
}

int JupMotionCaller::moveToPosA3(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "A3");
	RzTxMoveToPos(POSNAME_A3);
	return 0;
}

int JupMotionCaller::moveToPosA4(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "A4");
	RzTxMoveToPos(POSNAME_A4);
	return 0;
}

int JupMotionCaller::moveToPosA5(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "A5");
	RzTxMoveToPos(POSNAME_A5);
	return 0;
}

int JupMotionCaller::moveToPosA6(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "A6");
	RzTxMoveToPos(POSNAME_A6);
	return 0;
}

int JupMotionCaller::moveToPosA7(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "A7");
	RzTxMoveToPos(POSNAME_A7);
	return 0;
}

int JupMotionCaller::moveToPosB1(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "B1");
	RzTxMoveToPos(POSNAME_B1);
	return 0;
}

int JupMotionCaller::moveToPosB2(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "B2");
	RzTxMoveToPos(POSNAME_B2);
	return 0;
}

int JupMotionCaller::moveToPosB3(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "B3");
	RzTxMoveToPos(POSNAME_B3);
	return 0;
}

int JupMotionCaller::moveToPosB4(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "B4");
	RzTxMoveToPos(POSNAME_B4);
	return 0;
}

int JupMotionCaller::moveToPosB5(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "B5");
	RzTxMoveToPos(POSNAME_B5);
	return 0;
}

int JupMotionCaller::moveToPosB6(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "B6");
	RzTxMoveToPos(POSNAME_B6);
	return 0;
}

int JupMotionCaller::moveToPosB7(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "B7");
	RzTxMoveToPos(POSNAME_B7);
	return 0;
}

int JupMotionCaller::moveToPosC1(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "C1");
	RzTxMoveToPos(POSNAME_C1);
	return 0;
}

int JupMotionCaller::moveToPosC2(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "C2");
	RzTxMoveToPos(POSNAME_C2);
	return 0;
}

int JupMotionCaller::moveToPosC3(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "C3");
	RzTxMoveToPos(POSNAME_C3);
	return 0;
}

int JupMotionCaller::moveToPosC4(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "C4");
	RzTxMoveToPos(POSNAME_C4);
	return 0;
}

int JupMotionCaller::moveToPosC5(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "C5");
	RzTxMoveToPos(POSNAME_C5);
	return 0;
}

int JupMotionCaller::moveToPosC6(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "C6");
	RzTxMoveToPos(POSNAME_C6);
	return 0;
}

int JupMotionCaller::moveToPosC7(JupData & resultTable)
{
	resultTable.SetValue("HikData", "PosName", "C7");
	RzTxMoveToPos(POSNAME_C7);
	// 记录点位角度信息并清除重置数据结构
	resultTable.SetValue("PosAngle", "AxisTx", Jup::Join(m_TxAngle, ","));
	resultTable.SetValue("PosAngle", "AxisTy", Jup::Join(m_TyAngle, ","));
	m_TxAngle.clear();
	m_TyAngle.clear();
	return 0;
}

int JupMotionCaller::moveToPosZero(JupData & resultTable)
{
	//RzTxMoveToPos(POSNAME_Rz_PosInitial, POSNAME_Tx_PosInitial);
	return 0;
}

int JupMotionCaller::AxisTxTyHome(JupData & resultTable)
{
	int nRet1 = m_pMotion->AxisHome(AXIS_Name_Tx);
	int nRet2 = m_pMotion->AxisHome(AXIS_Name_Ty);
	if (nRet1 != 0 || nRet2 != 0)
	{
		return -1;
	}
	m_pMotion->WaitAxisHome(AXIS_Name_Tx);
	m_pMotion->WaitAxisHome(AXIS_Name_Ty);
	return 0;
}


int JupMotionCaller::WaitStartTestSignal(JupData & resultTable)
{
	char log[LOG_MAXSIZE] = "";
	std::string str("start");

	// skip grating check
	//m_pMotion->m_bWaitLoading = true;
	bool bSoftWareManual = false;
	bool bHardWareManual = false;
	//bSoftWareManual = m_pMotion->GetSoftWareManual();
	//bSoftWareManual = true;

	//bHardWareManual = m_pMotion->GetHardWareManual(); // false 手动

	bool bManualStartSignal = false;
	//bManualStartSignal = m_pMotion->CheckManualLoad();

	bool bAutoStartSignal = false;/* rc start test signal */

	if (bManualStartSignal)
	{
		if (bSoftWareManual && !bHardWareManual)
		{
			//m_pMotion->m_bWaitLoading = false;
			sprintf(log, "Manual start signal triggered, Device running mode is Manual Mode, test start!");
			PluginWriteLog(JLogLevel::Info, __FUNCTION__, str);
			return 0;
		}
		else
		{
			//m_pMotion->m_bWaitLoading = false;
			sprintf(log, "Manual start signal triggered, Device running mode is not manual mode, ingored signal!");
			PluginWriteLog(JLogLevel::Info, __FUNCTION__, str);
			return -1;
		}
	}

	if (bAutoStartSignal)
	{
		// 检查RC
		if (!bSoftWareManual && bHardWareManual)
		{
			//m_pMotion->m_bWaitLoading = false;
			sprintf(log, "Auto start signal triggered, Device running mode is auto Mode, test start!");
			PluginWriteLog(JLogLevel::Info, __FUNCTION__, str);
			return 0;
		}
		else
		{
			//m_pMotion->m_bWaitLoading = false;
			sprintf(log, "Auto start signal triggered, Device running mode is not auto Mode, ingored signal!");
			PluginWriteLog(JLogLevel::Info, __FUNCTION__, str);
			return -1;
		}
	}

	//m_pMotion->m_bWaitLoading = false;
	return -1;
}

int JupMotionCaller::AlarmMotionError(JupData & resultTable)
{
	char log[LOG_MAXSIZE] = "";
	std::string str("start");
	sprintf(log, "AlarmError!!!");

	PluginWriteLog(JLogLevel::Error, __FUNCTION__, str);
	return 0;
}

int JupMotionCaller::PnpDoeResetData(JupData & data)
{
	// 重置数据
	std::string strStartTime_0, strStartTime_1, strStartTime_3;
	strStartTime_0 = Jup::GetLocalTime(0);
	strStartTime_1 = Jup::GetLocalTime(1);
	strStartTime_3 = Jup::GetLocalTime(3);
	data.SetValue("MotionData", "StartTime_0", strStartTime_0);
	data.SetValue("MotionData", "StartTime_1", strStartTime_1);
	data.SetValue("MotionData", "StartTime_3", strStartTime_3);

	return 0;
}

int JupMotionCaller::AxisLoadPnpHome(JupData & resultTable)
{
	int nRet_x = m_pMotion->AxisHome(AXIS_Name_XPnp);
	int nRet_z = m_pMotion->AxisHome(AXIS_Name_ZPnp);
	int nRet_r = m_pMotion->AxisHome(AXIS_Name_RPnp);
	if (nRet_x != 0 && nRet_z != 0 && nRet_r != 0)
	{
		PluginWriteLog(JLogLevel::Error, __FUNCTION__, _T("Moving to the home position failed"));
		return -10008;
	}
	m_pMotion->WaitAxisHome(AXIS_Name_XPnp);
	m_pMotion->WaitAxisHome(AXIS_Name_ZPnp);
	m_pMotion->WaitAxisHome(AXIS_Name_RPnp);
	m_pMotion->IO_SetOutput(CardConfig::CardNo, IO_ModNo::No1, IO_Out_Channel::SocketCoverUp, IO_Status::OFF);
	m_pMotion->IO_SetOutput(CardConfig::CardNo, IO_ModNo::No1, IO_Out_Channel::SocketCoverOut, IO_Status::OFF);

	int nRet = m_pMotion->AxisHome(AXIS_Name_YPnp);
	m_pMotion->WaitAxisHome(AXIS_Name_YPnp);
	if (nRet != 0)
	{
		PluginWriteLog(JLogLevel::Error, __FUNCTION__, _T("Moving to the home position failed"));
		return -10008;
	}
	jCore->SendEvent(g_MotionWidget, &JMotionIsHomeEvent(true));
	return 0;
}

int JupMotionCaller::AxisLoadResetPosition(JupData & resultTable)
{
	auto info = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_YPnp, POSNAME_YPnp_Load);
	int nRet = m_pMotion->ResetTriggerPos(info->axisID, info->distance);
	return 0;
}

int JupMotionCaller::AxisLoadPnpToPosPhoto(JupData & resultTable)
{
	auto info = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_YPnp, POSNAME_YPnp_TopCam);
	int nRet = m_pMotion->AxisAbsMove(AXIS_Name_YPnp, info->distance);
	if (nRet != 0)
	{
		PluginWriteLog(JLogLevel::Error, __FUNCTION__, _T("Moving to the set position failed"));
		return -10009;
	}
	m_pMotion->WaitAxisAbsMove(AXIS_Name_YPnp, info->distance);
	std::string takeDutImagePath = "TakeUp";
	resultTable.SetValue("MotionData", "TakeDutImagePath", takeDutImagePath);
	resultTable.SetValue("MotionData", "TakeUpOrLayDown", true);
	return 0;
}

int JupMotionCaller::AxisLoadPnpToPosTray(JupData & resultTable)
{
	auto info = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_YPnp, POSNAME_YPnp_Load);
	int nRet = m_pMotion->AxisAbsMove(AXIS_Name_YPnp, info->distance);
	if (nRet != 0)
	{
		PluginWriteLog(JLogLevel::Error, __FUNCTION__, _T("Moving to the set position failed"));
		return -10009;
	}
	m_pMotion->WaitAxisAbsMove(AXIS_Name_YPnp, info->distance);

	return 0;
}

int JupMotionCaller::AxisXRLoadPnpToPosTray(JupData & resultTable)
{
	auto info_x = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_XPnp, POSNAME_XPnp_WorkPos);
	auto info_r = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_RPnp, POSNAME_RPnp_WorkPos);

	int nRet_x = m_pMotion->AxisAbsMove(AXIS_Name_XPnp, info_x->distance);
	int nRet_r = m_pMotion->AxisAbsMove(AXIS_Name_RPnp, info_r->distance);
	if (nRet_x != 0 && nRet_r != 0)
	{
		PluginWriteLog(JLogLevel::Error, __FUNCTION__, _T("Moving to the set position failed"));
		return -10009;
	}

	m_pMotion->WaitAxisAbsMove(AXIS_Name_XPnp, info_x->distance);
	m_pMotion->WaitAxisAbsMove(AXIS_Name_RPnp, info_r->distance);
	return 0;
}

int JupMotionCaller::AxisZPeriodicMotion(JupData & resultTable)
{
	//Z轴下落
	auto info_z = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_ZPnp, POSNAME_ZPnp_WorkPos);
	int nRet_z = m_pMotion->AxisAbsMove(AXIS_Name_ZPnp, info_z->distance);
	if (nRet_z != 0)
	{
		PluginWriteLog(JLogLevel::Error, __FUNCTION__, _T("Moving to the set position failed"));
		return -10009;
	}
	m_pMotion->WaitAxisAbsMove(AXIS_Name_ZPnp, info_z->distance);

	//启动吸嘴

	//Z轴上升
	info_z = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_ZPnp, POSNAME_ZPnp_SafetyPos);
	nRet_z = m_pMotion->AxisAbsMove(AXIS_Name_ZPnp, info_z->distance);
	if (nRet_z != 0)
	{
		PluginWriteLog(JLogLevel::Error, __FUNCTION__, _T("Moving to the set position failed"));
		return -10009;
	}
	m_pMotion->WaitAxisAbsMove(AXIS_Name_ZPnp, info_z->distance);
	return 0;
}

int JupMotionCaller::CylLoadPnpToPickDut(JupData & resultTable)
{
	return 0;
}

int JupMotionCaller::AxisLoadSetParameter(JupData & resultTable)
{
	//auto info = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_YPnp, POSNAME_YPnp_BottomCam);
	auto info1 = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_YPnp, POSNAME_AXISY_B2B);
	auto info2 = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_YPnp, POSNAME_AXISY_2DBC);
	std::vector<double> posList;
	posList.push_back(info1->distance);
	posList.push_back(info2->distance);
	int nRet = m_pMotion->SetTriggerListPos(AXIS_Name_YPnp, EnumMotorTriggerMode::NegativeD01D02Mode, posList);
	return 0;
}

int JupMotionCaller::AxisLoadPnpCommandToPosSocket(JupData & resultTable)
{
	auto info = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_YPnp, POSNAME_YPnp_UnLoadCam);

	int nRet = m_pMotion->AxisAbsMove(AXIS_Name_YPnp, info->distance);
	if (nRet != 0)
	{
		PluginWriteLog(JLogLevel::Error, __FUNCTION__, _T("Moving to the set position failed"));
		return -10009;
	}

	return 0;
}

int JupMotionCaller::AxisLoadPnpWaitMoveToPosSocket(JupData & resultTable)
{
	auto info = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_YPnp, POSNAME_YPnp_UnLoadCam);

	m_pMotion->WaitAxisAbsMove(AXIS_Name_YPnp, info->distance);

	std::string takeDutImagePath = "PutDown";
	resultTable.SetValue("MotionData", "TakeDutImagePath", takeDutImagePath);
	resultTable.SetValue("MotionData", "TakeUpOrLayDown", false);
	return 0;
}

int JupMotionCaller::CylLoadPnpToPutDut(JupData & resultTable)
{
	return 0;
}

int JupMotionCaller::IsTheLastStep(JupData & resultTable)
{
	int CurrentCount = 1;
	int TestCount = jCore->GlobalSettings().ReadInt("PnpDoe", "TestCount");
	std::string strCurrentCount = resultTable.GetValue("MotionTest", "CurrentCount");
	if (!strCurrentCount.empty())
	{
		CurrentCount = std::atoi(strCurrentCount.c_str());
	}

	if (CurrentCount > TestCount)
	{
		resultTable.SetValue("MotionTest", "CurrentCount", 1);
		return -1;
	}
	resultTable.SetValue("MotionTest", "CurrentCount", CurrentCount + 1);
	return 0;
}

int JupMotionCaller::AxisDILXDILYHome(JupData & resultTable)
{
	//int nRet1 = m_pMotion->AxisHome(AXIS_Name_DILX);
	//int nRet2 = m_pMotion->AxisHome(AXIS_Name_DILY);
	//if (nRet1 != 0 || nRet2 != 0)
	//{
	//	return -1;
	//}
	//m_pMotion->WaitAxisHome(AXIS_Name_DILX);
	//m_pMotion->WaitAxisHome(AXIS_Name_DILY);
	return 0;
}

int JupMotionCaller::AxisDILXDILYToSocketPos(JupData & resultTable)
{
	//auto info1 = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_DILX, POSNAME_DIL_Socket_X);
	//auto info2 = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_DILY, POSNAME_DIL_Socket_Y);

	//int nRet1 = m_pMotion->AxisAbsMove(AXIS_Name_DILX, info1->distance);
	//int nRet2 = m_pMotion->AxisAbsMove(AXIS_Name_DILY, info2->distance);
	//m_pMotion->WaitAxisAbsMove(AXIS_Name_DILX, info1->distance);
	//m_pMotion->WaitAxisAbsMove(AXIS_Name_DILY, info2->distance);

	return 0;
}

int JupMotionCaller::CalibraTestStartCheck(JupData & data)
{
	// 更新测试计数
	data.SetValue("JupMotion", "TestCount", test_count);
	data.SetValue("JupMotion", "TestStartTime", Jup::GetLocalTime(0));
	test_count++;
	return 0;
}

int JupMotionCaller::moveToReadyPnpPos(JupData & data)
{
	//运动到准备位置
	MoveToReadyPos(POSNAME_CailbraReadyPos);
	return 0;
}

int JupMotionCaller::takePhotoToCalibraPosA1(JupData & data)
{
	//执行取图流程，并算出校准值，得出校准的Tx和Ty的运动距离
	return 0;
}

int JupMotionCaller::moveToPnpCailbraPosA1(JupData & data)
{
	MoveToCailbraPos(-10, -10, 60000.0, 5000000.0, 5000000.0);
	return 0;
}

int JupMotionCaller::takePhotoToCalibraPosA2(JupData & data)
{
	//执行取图流程，并算出校准值，得出校准的Tx和Ty的运动距离
	return 0;
}

int JupMotionCaller::moveToPnpCailbraPosA2(JupData & data)
{
	MoveToCailbraPos(10, 10, 60000.0, 5000000.0, 5000000.0);
	return 0;
}

int JupMotionCaller::takePhotoToCalibraPosA3(JupData & data)
{
	//执行取图流程，并算出校准值，得出校准的Tx和Ty的运动距离
	return 0;
}

int JupMotionCaller::moveToPnpCailbraPosA3(JupData & data)
{
	MoveToCailbraPos(5, 5, 60000.0, 5000000.0, 5000000.0);
	return 0;
}

int JupMotionCaller::takePhotoToFinalPosA4(JupData & data)
{
	//拍出最终中心重合图片
	return 0;
}

int JupMotionCaller::saveCurrentPnpPos(JupData & data)
{
	double AxisX_Pos = m_pMotion->GetCurrentPos(AXIS_Name_XPnp);
	double AxisY_Pos = m_pMotion->GetCurrentPos(AXIS_Name_YPnp);

	data.SetValue("JupMotion", "PnpAxisXPos_font", AxisX_Pos);
	data.SetValue("JupMotion", "PnpAxisYPos_font", AxisY_Pos);

	return 0;
}

int JupMotionCaller::moveToReadyNozzlePos(JupData & data)
{
	//运动到准备位置
	MoveToReadyPos(POSNAME_NozzleCailbraReadyPos);
	return 0;
}

int JupMotionCaller::takePhotoToCalibraPosB1(JupData & data)
{
	return 0;
}

int JupMotionCaller::moveToPnpCailbraPosB1(JupData & data)
{
	MoveToNozzleCailbraPos(-10, -10, -0.2, 60000.0, 5000000.0, 5000000.0);
	return 0;
}

int JupMotionCaller::takePhotoToCalibraPosB2(JupData & data)
{
	return 0;
}

int JupMotionCaller::moveToPnpCailbraPosB2(JupData & data)
{
	MoveToNozzleCailbraPos(10, 10, 0.4, 60000.0, 5000000.0, 5000000.0);
	return 0;
}

int JupMotionCaller::takePhotoToCalibraPosB3(JupData & data)
{
	return 0;
}

int JupMotionCaller::moveToPnpCailbraPosB3(JupData & data)
{
	MoveToNozzleCailbraPos(5, 5, -0.2, 60000.0, 5000000.0, 5000000.0);
	return 0;
}

int JupMotionCaller::takePhotoToFinalPosB4(JupData & data)
{
	return 0;
}

int JupMotionCaller::saveCurrentPnpAndNozzlePos(JupData & data)
{
	double AxisX_Pos = m_pMotion->GetCurrentPos(AXIS_Name_XPnp);
	double AxisY_Pos = m_pMotion->GetCurrentPos(AXIS_Name_YPnp);

	data.SetValue("JupMotion", "NozzleCFOV_X", "N/A");
	data.SetValue("JupMotion", "NozzleCFOV_Y", "N/A");
	data.SetValue("JupMotion", "NozzleCFOV_R", "N/A");
	data.SetValue("JupMotion", "NozzleCFOV_PnpXPos", AxisX_Pos);
	data.SetValue("JupMotion", "NozzleCFOV_PnpYPos", AxisY_Pos);
	return 0;
}

int JupMotionCaller::CalPnpDistance(JupData & data)
{
	double a = data.GetDouble("JupMotion", "NozzleCFOV_PnpXPos");
	double b = data.GetDouble("JupMotion", "NozzleCFOV_PnpYPos");
	double c = data.GetDouble("JupMotion", "PnpAxisXPos_font");
	double d = data.GetDouble("JupMotion", "PnpAxisYPos_font");
	double pnpXPosDelta = abs(data.GetDouble("JupMotion", "NozzleCFOV_PnpXPos")) - abs(data.GetDouble("JupMotion", "PnpAxisXPos_font"));
	double pnpYPosDelta = abs(data.GetDouble("JupMotion", "NozzleCFOV_PnpYPos")) - abs(data.GetDouble("JupMotion", "PnpAxisYPos_font"));

	data.SetValue("JupMotion", "CalPnpDelta_X", pnpXPosDelta);
	data.SetValue("JupMotion", "CalPnpDelta_Y", pnpYPosDelta);
	return 0;
}

void JupMotionCaller::RzTxMoveToPos(const std::string & pos_name)
{
	auto info1 = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_Tx, pos_name);
	auto info2 = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_Ty, pos_name);

	//double run_speed = 100;
	//if (pos_name == POSNAME_A1)
	//{
	//	run_speed = 60;
	//}

	std::string run_mode =  jCore->GlobalSettings().ReadString("AlphaDoe", "RunMode");
	if (run_mode == "ALL")
	{
		// 1.Tx和Ty一起跑
		int nRet1 = m_pMotion->AxisAbsMove(AXIS_Name_Tx, info1->distance/*, 0.0, run_speed*/);
		int nRet2 = m_pMotion->AxisAbsMove(AXIS_Name_Ty, info2->distance);
		m_pMotion->WaitAxisAbsMove(AXIS_Name_Tx, info1->distance);
		m_pMotion->WaitAxisAbsMove(AXIS_Name_Ty, info2->distance);
	}
	else if (run_mode == "TX")
	{
		// 2.只跑TX
		int nRet1 = m_pMotion->AxisAbsMove(AXIS_Name_Tx, info1->distance);
		m_pMotion->WaitAxisAbsMove(AXIS_Name_Tx, info1->distance);
	}
	else if (run_mode == "TY")
	{
		// 3.只跑TY
		int nRet2 = m_pMotion->AxisAbsMove(AXIS_Name_Ty, info2->distance);
		m_pMotion->WaitAxisAbsMove(AXIS_Name_Ty, info2->distance);
	}
	else
	{
		//4.Tx和Ty全不跑
	}

	// 只拍A1,B4,C7三个点
	if (pos_name == POSNAME_A1 || pos_name == POSNAME_B4 || pos_name == POSNAME_C7)
	{
		int move_wait = jCore->GlobalSettings().ReadInt("AlphaDoe", "AxisMoveWait");
		Sleep(move_wait);

		auto angle_tx = m_pMotion->GetCurrentPos(AXIS_Name_Tx);
		m_TxAngle.push_back(std::to_string(angle_tx));
		auto angle_ty = m_pMotion->GetCurrentPos(AXIS_Name_Ty);
		m_TyAngle.push_back(std::to_string(angle_ty));
	}
	//int move_wait = jCore->GlobalSettings().ReadInt("AlphaDoe", "AxisMoveWait");
	//Sleep(move_wait);

	// 记录位置角度信息
	//auto angle_tx = m_pMotion->GetCurrentPos(AXIS_Name_Tx);
	//m_TxAngle.push_back(std::to_string(angle_tx));
	//auto angle_ty = m_pMotion->GetCurrentPos(AXIS_Name_Ty);
	//m_TyAngle.push_back(std::to_string(angle_ty));
}

void JupMotionCaller::MoveToReadyPos(const std::string & pos_name)
{
	auto info1 = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_XPnp, pos_name);
	auto info2 = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_YPnp, pos_name);

	int nRet1 = m_pMotion->AxisAbsMove(AXIS_Name_XPnp, info1->distance/*, 0.0, run_speed*/);
	int nRet2 = m_pMotion->AxisAbsMove(AXIS_Name_YPnp, info2->distance);
	m_pMotion->WaitAxisAbsMove(AXIS_Name_XPnp, info1->distance);
	m_pMotion->WaitAxisAbsMove(AXIS_Name_YPnp, info2->distance);


	if (pos_name == POSNAME_NozzleCailbraReadyPos)
	{
		auto info3 = m_pMotion->GetMotionParameter()->GetAxisPosInfo(AXIS_Name_RPnp, pos_name);
		int nRet3 = m_pMotion->AxisAbsMove(AXIS_Name_RPnp, info3->distance);
		m_pMotion->WaitAxisAbsMove(AXIS_Name_RPnp, info3->distance);
	}
}

void JupMotionCaller::MoveToCailbraPos(double AxisX_distance, double AxisY_distance, double maxVel, double accVel, double decVel)
{
	int nRet1 = m_pMotion->AxisMoveDistance(AXIS_Name_XPnp, AxisX_distance, maxVel, accVel, decVel);
	int nRet2 = m_pMotion->AxisMoveDistance(AXIS_Name_YPnp, AxisY_distance, maxVel, accVel, decVel);
	m_pMotion->WaitAxisMoveDistance(AXIS_Name_XPnp, AxisX_distance);
	m_pMotion->WaitAxisMoveDistance(AXIS_Name_YPnp, AxisY_distance);
}

void JupMotionCaller::MoveToNozzleCailbraPos(double AxisX_distance, double AxisY_distance, double AxisR_distance, double maxVel, double accVel, double decVel)
{
	int nRet1 = m_pMotion->AxisMoveDistance(AXIS_Name_XPnp, AxisX_distance, maxVel, accVel, decVel);
	int nRet2 = m_pMotion->AxisMoveDistance(AXIS_Name_YPnp, AxisY_distance, maxVel, accVel, decVel);
	int nRet3 = m_pMotion->AxisMoveDistance(AXIS_Name_RPnp, AxisR_distance);
	m_pMotion->WaitAxisMoveDistance(AXIS_Name_XPnp, AxisX_distance);
	m_pMotion->WaitAxisMoveDistance(AXIS_Name_YPnp, AxisY_distance);
	m_pMotion->WaitAxisMoveDistance(AXIS_Name_RPnp, AxisR_distance);
}

void JupMotionCaller::PluginWriteLog(JLogLevel level, std::string strfunc, const std::string str)
{
	jCore->Logger("JupMotion.dll").Log(level, strfunc, str);
	//jCore->WriteProcessLog(m_proName, level, strfunc, str);
}