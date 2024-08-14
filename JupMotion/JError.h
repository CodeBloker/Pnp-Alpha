#pragma once

#pragma once

#include "PluginBase/JupError.h"

/*
	该类是平台加载错误码信息的接口，若正确定义能显示在平台系统设置的ErrorHanding页面上
*/
class JError : public JupError
{
public:
	explicit JError() {}
	~JError() {}

	/*
		枚举的变量名表示错误名，枚举的变量值表示错误码
	*/
	enum E_error
	{
		ERR_CardInit = 10000,//初始化失败
		ERR_StartFieldBus,   //初始化总线失败
		ERR_StopFieldBus,    //关闭总线失败
		ERR_AxisServoOnAll,  //使能电机失败
		ERR_MotionMoveTimeOut,//移动超时
		ERR_MotionHomeTimeOut,
		ERR_MotionSafetyError,//超过安全位置
		ERR_SetMoveParam,//设置移动参数失败
		ERR_AxisServo,
		ERR_MoveToPos,//移动到设定位置失败
		ERR_MoveDistance,//移动固定距离失败
		ERR_Movement_Exceeds_Limit,//移动完成后检测误差超过设置
		ERR_StopMoveAxis,
		ERR_EMGStopMoveAxis,
		ERR_MotionHome,//回原移动失败
		ERR_StopWaitMove,//停止轴移动
		ERR_WaitHome_ORG_Not_Triggered,//回原后未触发原点传感器
		ERR_PEl,//正极限触发
		ERR_NEL,//负极限触发
		ERR_Anti_Collision_Sensor_Triggered_X,//积分球X轴方向防撞感应
		ERR_Anti_Collision_Sensor_Triggered_Y,//积分球Y轴方向防撞感应
		ERR_Read_Sensor_Value,
		ERR_EyeBox_Movement_Exceeds_Limit,
		ERR_OpenSafetyDoor,
		ERR_OpenAllClampingCylinders,
		ERR_CloseSafetyDoor,
		ERR_CloseAllClampingCylinders,
		ERR_TurnOn_IonFan,
		ERR_TurnOff_IonFan,
		ERR_EyeBoxConfig,
		ERR_Read_EyeBoxIndex,//获取当前测试次数失败
		ERR_Read_EyeBoxLoop,//获取EyeBoxLoop数据失败
		ERR_SW_AxisSafetyCheckY, //软件轴卡安全检测
		ERR_SW_AxisSafetyCheckZ, //软件轴卡安全检测
		ERR_HW_AxisSafetyCheck, //硬件轴卡安全检测
		ERR_DUT_NotExist,                // 未检测到待测物
		ERR_DUT_StillExist,                // 待测物残留
		ERR_DUT_AirPressure,	// 总气压异常
		ERR_SafetyDoorOpen,		// 检测到左右两侧门未
		ERR_GratingTrigger,
		ERR_ThermoHygro,
		ERR_SmallPushBlockIn, // 小推块进未到位
		ERR_SmallPushBlockOut, // 小推块出未到位
		ERR_BigPushBlockIn, // 大推块进未到位
		ERR_BigPushBlockOut, // 大推块出未到位
		ERR_GripperSensingIsNotOn, // 夹爪感应没有ON
		ERR_GripperSensingIsNotOff, // 夹爪感应没有Off
	};

	/*
		返回错误提示，下列是默认数据，需结合枚举E_error自定义修改并删除默认数据
		格式为<错误码, <中文提示, 英文提示>>
	*/
	std::map<int, ErrorPrompt>& ErrorPrompts() override
	{
		static std::map<int, ErrorPrompt> errorPrompts = {
		{ERR_CardInit,							{"ERR_CardInit",
												"初始化失败",
												"Initialization failed"}},
		{ERR_MotionMoveTimeOut,					{"ERR_MotionMoveTimeOut",
												"移动超时",
												"Move timeout"}},
		{ERR_MotionHomeTimeOut,					{"ERR_MotionMoveTimeOut",
												"回原超时",
												"Home timeout"}},
		{ERR_MotionSafetyError,					{"ERR_MotionSafetyError",
												"超过安全位置",
												"Exceeded safe position"}},
		{ERR_SetMoveParam,						{"ERR_SetMoveParam",
												"设置移动参数失败",
												"Failed to set move parameters"}},
		{ERR_AxisServo,							{"ERR_AxisServo",
												"未设置轴卡使能",
												"Axis card enabled not set"}},
		{ERR_MoveToPos,							{"ERR_MoveToPos",
												"移动到设定位置失败",
												"Moving to the set position failed"}},
		{ERR_MoveDistance,						{"ERR_MoveDistance",
												"移动固定距离失败",
												"Moving fixed distance failed"}},
		{ERR_Movement_Exceeds_Limit,			{"ERR_Movement_Exceeds_Limit",
												"移动完成后检测误差超过设置",
												"Detection error exceeds the setting after the move is completed"}},
		{ERR_StopMoveAxis,						{"ERR_StopMoveAxis",
												"停止移动失败",
												"Stop moving failed"}},
		{ERR_EMGStopMoveAxis,					{"ERR_EMGStopMoveAxis",
												"急停失败",
												"Emergency stop failed"}},
		{ERR_MotionHome,						{"ERR_MotionHome",
												"回原移动失败",
												"Failed to move back to original location"}},
		{ERR_StopWaitMove,						{"ERR_StopWaitMove",
												"停止等待轴移动",
												"Stop waiting for axis movement"}},
		{ERR_WaitHome_ORG_Not_Triggered,		{"ERR_WaitHome_ORG_Not_Triggered",
												"回原后未触发原点传感器",
												"The origin sensor was not triggered after returning to its original position"}},
		{ERR_PEl,								{"ERR_PEl",
												"正极限触发",
												"Positive Limit Trigger"}},
		{ERR_NEL,								{"ERR_NEL",
												"负极限触发",
												"Negative Limit Trigger"}},
		{ERR_Anti_Collision_Sensor_Triggered_X, {"ERR_Anti_Collision_Sensor_Triggered_X",
												"积分球X轴方向防撞感应",
												"Integration Ball X-axis Collision Avoidance Sensing"}},
		{ERR_Anti_Collision_Sensor_Triggered_Y, {"ERR_Anti_Collision_Sensor_Triggered_Y",
												"积分球Y轴方向防撞感应",
												"Integration Ball Y-axis Collision Avoidance Sensing"}},
		{ERR_Read_Sensor_Value,					{"ERR_Read_Sensor_Value",
												"读距离传感器失败",
												"Reading distance sensor failed"}},
		{ERR_EyeBox_Movement_Exceeds_Limit,		{"ERR_EyeBox_Movement_Exceeds_Limit",
												"超过EyeBox距离限制",
												"Exceeding EyeBox distance limit"}},
		{ERR_OpenSafetyDoor,					{"ERR_OpenSafetyDoor",
												"打开安全门失败",
												"Failed to open the safety door"}},
		{ERR_OpenAllClampingCylinders,			{"ERR_OpenAllClampingCylinders",
												"打开夹爪气缸失败",
												"Failed to open the gripper cylinder"}},
		{ERR_CloseSafetyDoor,					{"ERR_CloseSafetyDoor",
												"关闭安全门失败",
												"Closing the safety door failed"}},
		{ERR_CloseAllClampingCylinders,			{"ERR_CloseAllClampingCylinders",
												"关闭夹爪气缸失败",
												"Closing the gripper cylinder failed"}},
		{ERR_TurnOn_IonFan,						{"ERR_TurnOn_IonFan",
												"打开离子吹风失败",
												"Failed to open ion fan"}},
		{ERR_TurnOff_IonFan,					{"ERR_TurnOff_IonFan",
												"关闭离子吹风失败",
												"Failed to turn off ion fan"}},
		{ERR_EyeBoxConfig,						{"ERR_EyeBoxConfig",
												"EyeBox配置错误",
												"EyeBox configuration error"}},
		{ERR_Read_EyeBoxIndex,					{"ERR_Read_EyeBoxIndex",
												"获取当前EyeBox测试次数失败",
												"Failed to obtain the current number of EyeBox tests"}},
		{ERR_Read_EyeBoxLoop,					{"ERR_Read_EyeBoxLoop",
												"获取EyeBoxLoop数据失败",
												"Failed to obtain EyeBoxLoop data"}},
		{ERR_SW_AxisSafetyCheckY,				{"ERR_SW_AxisSafetyCheckY",
												"软件 轴卡Y安全检测触发",
												"Software Axis Card Y Security Detection Triggered"}},
		{ERR_SW_AxisSafetyCheckZ,				{"ERR_SW_AxisSafetyCheckZ",
												"软件 轴卡Z安全检测触发",
												"Software Axis Card Z Security Detection Triggered"}},
		{ERR_HW_AxisSafetyCheck,				{"ERR_HW_AxisSafetyCheck",
												"硬件 轴卡安全检测触发",
												"Hardware axis card security detection triggered"}},
		{ERR_DUT_NotExist,						{"ERR_DUT_NotExist",
												"未检测到待测物",
												"No test object detected"}},
		{ERR_DUT_StillExist,					{"ERR_DUT_StillExist",
												"待测物残留",
												"Residues of the tested substance"}},
		{ERR_DUT_AirPressure,					{"ERR_DUT_AirPressure",
												"总气压异常",
												"Abnormal total pressure"}},
		{ERR_SafetyDoorOpen,					{"ERR_SafetyDoorOpen",
												"门未关闭",
												"Safety door open"}},
		{ERR_GratingTrigger,					{"ERR_GratingTrigger",
												"光栅触发",
												"GratingTrigger"}},
		{ERR_ThermoHygro,						{"ERR_ThermoHygro",
												"温湿度异常",
												"ThermoHygro error"}},
		{ERR_SmallPushBlockIn,					{"ERR_SmallPushBlockIn",
												"小推快动作异常(进)",
												"Abnormal action of small push block(In)"}},
		{ERR_SmallPushBlockOut,					{"ERR_SmallPushBlockOut",
												"小推快动作异常(出)",
												"Abnormal action of small push block(Out)"}},
		{ERR_BigPushBlockIn,					{"ERR_BigPushBlockIn",
												"大推快动作异常(进)",
												"Abnormal action of big push block(In)"}},
		{ERR_BigPushBlockOut,					{"ERR_BigPushBlockOut",
												"大推快动作异常(出)",
												"Abnormal action of big push block(Out)"}},
		{ERR_GripperSensingIsNotOn,				{"ERR_GripperSensingIsNotOn",
												"夹爪感应没有ON",
												"Gripper sensing is not on"}},
		{ERR_GripperSensingIsNotOff,			{"ERR_GripperSensingIsNotOff",
												"夹爪感应没有OFF",
												"Gripper sensing is not off"}},
		};
		return errorPrompts;
	}
};
