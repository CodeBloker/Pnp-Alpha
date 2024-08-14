#pragma once

#include "APS168.h"
#include "type_def.h"
#include "ErrorCodeDef.h"
#include "APS_Define.h"
#include <map>

enum AxisEnable
{
	Disable = 0,
	Enable
};

// PCIe-833x 运动状态描述表
enum AxisMovingStatus
{
	CSTP = 0,	//命令已停止（但可能正在运行）
	VM,			//处于最大速度
	ACC,		//加速
	DEC,		//减速
	DIR,		//运动方向（1：正方向；0：反方向）
	MDN,		//动作完成。 0：运动中； 1：运动完成（可能是异常停止）
	HMV			//正在归零
};

enum AdlinkStatus
{
	NoError = 0,
	InitialError,
	StopFieldBusError,
	CloseCardError,
	StartFieldBusError,
	SetParaError_MIO_SVON,
	SetParaError_PRA_SF,
	SetParaError_PRA_VS,
	SetParaError_PRA_VE,
	SetParaError_PRA_VM,
	SetParaError_PRA_ACC,
	SetParaError_PRA_DEC,
	SetParaError_PRA_STP_DEC,
	GetAxisCommandPositionError,
	GetAxisFeedbackPositionError,	
	GetAxisCommandVelocityError,
	GetAxisFeedbackVelocityError,
	GetAxisErrorPositionError,
	GetAxisTargetPositionError,
	AxisStatusServeOffError
};


enum RUNNING_RESULT
{
	NO_RUN_ERROR = 1000,
	ADLINK_MOTION_NO_ERROR,
	ADLINK_MOTION_INIT_ERROR,
	ADLINK_MOTION_STOP_BUS_ERROR,
	ADLINK_MOTION_CLOSE_ERROR,
	ADLINK_MOTION_LOAD_ERROR,
	ADLINK_SCANBUS_ERROR,
	ADLINK_STARTFIELDBUS_ERROR,
	ADLINK_AXIS_SERVEON_ERROR,
	ADLINK_AXIS_SERVEOFF_ERROR,
	ADLINK_AXIS_MOVEHOME_ERROR,
	ADLINK_AXIS_SETPARA_ERROR,
	ADLINK_AXIS_SERVEOFF,
	ADLINK_AXIS_HOME_ERROR,
	ADLINK_AXIS_HOME_TIMEOUT,
	ADLINK_AXIS_HOME_COMPLETE,
	ADLINK_AXIS_HOME_UNCOMPLETE,
	ADLINK_AXIS_MOVE_TIMEOUT,
	RUN_STOP,
	EMG_STOP,
	ADLINK_CARD_NEEDINIT,
	ADLINK_BUS_NEEDINIT,
	ADLINK_LONGMEN_PARAM_SET_ERROR,
	ADLINK_CYLINDER_CHECK_TIMEOUT
};

struct AxisStatus
{
	I32 command_position;
	I32 feedback_position;
	I32 target_position;
	I32 error_position;
	I32 command_velocity;
	I32 feedback_velocity;
	I32 motion_io;
	I32 motion_status;
	AxisStatus()
	{
		command_position = 0.0;
		feedback_position = 0.0;
		target_position = 0.0;
		error_position = 0.0;
		command_velocity = 0.0;
		feedback_velocity = 0.0;
		motion_io = 0;
		motion_status = 0;
	}
};

struct Axis_MotionIO_Status
{
	int ALM;// Servo alarm.
	int PEL;// Positive end limit.
	int MEL;// Negative end limit.
	int ORG;// ORG (Home)
	int EMG;// Emergency stop
	int EZ; // EZ.
	int INP;// In position.
	int SVON;// Servo on signal.

	Axis_MotionIO_Status()
	{
		ALM = 0;
		PEL = 0;
		MEL = 0;
		ORG = 0;
		EMG = 0;
		EZ = 0;
		INP = 0;
		SVON = 0;
	}
};

enum EnumMotorTriggerMode
{
	SkipMode = 0,//跳过该点
	PositiveMode = 1,//正方向穿越触发
	NegativeMode = 2,//负方向穿越触发
	PositiveNegativeMode = 3,//正负方向穿越触发
	AutoMode = 4,//自动判别穿越触发
	NegativeD01D02Mode = 5,//负方向穿越触发D01D02输出使能
};