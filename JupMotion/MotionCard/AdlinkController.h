#pragma once
#include "AdlinkCard/AdlinkDispatch.h"
#include "MotionParameter.h"

class AdlinkController :public AdlinkDispatch
{
public:
	AdlinkController();
	~AdlinkController();

	// 初始化板卡
	int InitAdlinkCard();
	// 断开板卡
	int CloseAdlinkCard();
	// 板卡初始化状态
	bool IsCardInit();
	// 轴使能
	int AxisServoOn(std::string axisName);
	// 轴失能
	int AxisServoOff(std::string axisName);
	// 运动到绝对坐标（绝对运动）
	int AxisAbsMove(const std::string& axisName, double distance, double dbOffset = 0.0, double ratio = 100);
	// 等待运动到绝对坐标
	int WaitAxisAbsMove(const std::string& axisName, double distance);
	// 移动到预设位置
	int AxisAbsMoveToPos(const std::string& axisName, const std::string& strPositionName, double dbOffset = 0.0);
	// 运动到相对坐标（相对运动）
	int AxisMoveDistance(const std::string& axisName, double distance);
	int WaitAxisMoveDistance(const std::string& axisName, double distance);
	// 停止移动
	int	StopAxisMove(const std::string& axisName);
	// 急停 停止移动
	int EMG_StopAxisMove(const std::string& axisName);
	// 设置后所有等待直接返回
	void AxisStopWait();
	// 回原
	int AxisHome(const std::string& axisName);
	// 等待回原
	int WaitAxisHome(const std::string& axisName);
	// 获取mm
	double GetCurrentPos(const std::string& axisName);
	// 轴状态（报警/正负限位/原点信号/使能）
	bool IsAlarm(const std::string& axisName);
	bool IsPEL(const std::string& axisName);
	bool IsNEL(const std::string& axisName);
	bool IsORG(const std::string& axisName);
	bool IsSvon(const std::string& axisName);

	//单个IO设置
	int IO_SetOutput(int card_num, int mod_num, int bit_num, int on_off);
	int IO_GetOutput(int card_num, int mod_num, int bit_num);
	int IO_GetInput(int card_num, int mod_num, int bit_num);

	// 飞拍相关函数
	// 位置比较实时位置清零(只有在回原以后的时候使用一次)
	int ResetTriggerPos(int axis_id, double pos);
	int ResetTriggerPos(const std::string& axisName);
	// 设置飞拍驱动器参数
	int SetTriggerListPos(std::string axisName, EnumMotorTriggerMode trigger_mode, std::vector<double> pos_list);
	// 读写驱动器
	int WriteReadSDO(int axis_slave, UINT16 ODIndex, UINT16 ODSubIndex, INT32 CommdData, UINT32 DataLen, INT32& ReData, bool IsWrite = true, bool IsRead = true, int time_out = 3000);
	int WriteReadPDO(UINT16 ByteOffset, UINT16 Size, UINT& Value, bool IsWrite = true, bool IsRead = true);

	// 参数
	MotionParameter* GetMotionParameter();

private:
	MotionParameter* m_pMotionParameter;
	bool m_bSetStopWait = false;
	// 相对运动记录起始位置
	double dbBeginPos;
	// 板卡初始化状态
	bool m_IsCardInit = false;

public:
	// PNP校准时用的轴运动函数
	// 校准运动到相对坐标（相对运动）
	int AxisMoveDistance(const std::string& axisName, double distance, double maxVel, double accVel, double decVel);
};

