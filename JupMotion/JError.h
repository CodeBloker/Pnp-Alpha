#pragma once

#pragma once

#include "PluginBase/JupError.h"

/*
	������ƽ̨���ش�������Ϣ�Ľӿڣ�����ȷ��������ʾ��ƽ̨ϵͳ���õ�ErrorHandingҳ����
*/
class JError : public JupError
{
public:
	explicit JError() {}
	~JError() {}

	/*
		ö�ٵı�������ʾ��������ö�ٵı���ֵ��ʾ������
	*/
	enum E_error
	{
		ERR_CardInit = 10000,//��ʼ��ʧ��
		ERR_StartFieldBus,   //��ʼ������ʧ��
		ERR_StopFieldBus,    //�ر�����ʧ��
		ERR_AxisServoOnAll,  //ʹ�ܵ��ʧ��
		ERR_MotionMoveTimeOut,//�ƶ���ʱ
		ERR_MotionHomeTimeOut,
		ERR_MotionSafetyError,//������ȫλ��
		ERR_SetMoveParam,//�����ƶ�����ʧ��
		ERR_AxisServo,
		ERR_MoveToPos,//�ƶ����趨λ��ʧ��
		ERR_MoveDistance,//�ƶ��̶�����ʧ��
		ERR_Movement_Exceeds_Limit,//�ƶ���ɺ�����������
		ERR_StopMoveAxis,
		ERR_EMGStopMoveAxis,
		ERR_MotionHome,//��ԭ�ƶ�ʧ��
		ERR_StopWaitMove,//ֹͣ���ƶ�
		ERR_WaitHome_ORG_Not_Triggered,//��ԭ��δ����ԭ�㴫����
		ERR_PEl,//�����޴���
		ERR_NEL,//�����޴���
		ERR_Anti_Collision_Sensor_Triggered_X,//������X�᷽���ײ��Ӧ
		ERR_Anti_Collision_Sensor_Triggered_Y,//������Y�᷽���ײ��Ӧ
		ERR_Read_Sensor_Value,
		ERR_EyeBox_Movement_Exceeds_Limit,
		ERR_OpenSafetyDoor,
		ERR_OpenAllClampingCylinders,
		ERR_CloseSafetyDoor,
		ERR_CloseAllClampingCylinders,
		ERR_TurnOn_IonFan,
		ERR_TurnOff_IonFan,
		ERR_EyeBoxConfig,
		ERR_Read_EyeBoxIndex,//��ȡ��ǰ���Դ���ʧ��
		ERR_Read_EyeBoxLoop,//��ȡEyeBoxLoop����ʧ��
		ERR_SW_AxisSafetyCheckY, //����Ῠ��ȫ���
		ERR_SW_AxisSafetyCheckZ, //����Ῠ��ȫ���
		ERR_HW_AxisSafetyCheck, //Ӳ���Ῠ��ȫ���
		ERR_DUT_NotExist,                // δ��⵽������
		ERR_DUT_StillExist,                // ���������
		ERR_DUT_AirPressure,	// ����ѹ�쳣
		ERR_SafetyDoorOpen,		// ��⵽����������δ
		ERR_GratingTrigger,
		ERR_ThermoHygro,
		ERR_SmallPushBlockIn, // С�ƿ��δ��λ
		ERR_SmallPushBlockOut, // С�ƿ��δ��λ
		ERR_BigPushBlockIn, // ���ƿ��δ��λ
		ERR_BigPushBlockOut, // ���ƿ��δ��λ
		ERR_GripperSensingIsNotOn, // ��צ��Ӧû��ON
		ERR_GripperSensingIsNotOff, // ��צ��Ӧû��Off
	};

	/*
		���ش�����ʾ��������Ĭ�����ݣ�����ö��E_error�Զ����޸Ĳ�ɾ��Ĭ������
		��ʽΪ<������, <������ʾ, Ӣ����ʾ>>
	*/
	std::map<int, ErrorPrompt>& ErrorPrompts() override
	{
		static std::map<int, ErrorPrompt> errorPrompts = {
		{ERR_CardInit,							{"ERR_CardInit",
												"��ʼ��ʧ��",
												"Initialization failed"}},
		{ERR_MotionMoveTimeOut,					{"ERR_MotionMoveTimeOut",
												"�ƶ���ʱ",
												"Move timeout"}},
		{ERR_MotionHomeTimeOut,					{"ERR_MotionMoveTimeOut",
												"��ԭ��ʱ",
												"Home timeout"}},
		{ERR_MotionSafetyError,					{"ERR_MotionSafetyError",
												"������ȫλ��",
												"Exceeded safe position"}},
		{ERR_SetMoveParam,						{"ERR_SetMoveParam",
												"�����ƶ�����ʧ��",
												"Failed to set move parameters"}},
		{ERR_AxisServo,							{"ERR_AxisServo",
												"δ�����Ῠʹ��",
												"Axis card enabled not set"}},
		{ERR_MoveToPos,							{"ERR_MoveToPos",
												"�ƶ����趨λ��ʧ��",
												"Moving to the set position failed"}},
		{ERR_MoveDistance,						{"ERR_MoveDistance",
												"�ƶ��̶�����ʧ��",
												"Moving fixed distance failed"}},
		{ERR_Movement_Exceeds_Limit,			{"ERR_Movement_Exceeds_Limit",
												"�ƶ���ɺ�����������",
												"Detection error exceeds the setting after the move is completed"}},
		{ERR_StopMoveAxis,						{"ERR_StopMoveAxis",
												"ֹͣ�ƶ�ʧ��",
												"Stop moving failed"}},
		{ERR_EMGStopMoveAxis,					{"ERR_EMGStopMoveAxis",
												"��ͣʧ��",
												"Emergency stop failed"}},
		{ERR_MotionHome,						{"ERR_MotionHome",
												"��ԭ�ƶ�ʧ��",
												"Failed to move back to original location"}},
		{ERR_StopWaitMove,						{"ERR_StopWaitMove",
												"ֹͣ�ȴ����ƶ�",
												"Stop waiting for axis movement"}},
		{ERR_WaitHome_ORG_Not_Triggered,		{"ERR_WaitHome_ORG_Not_Triggered",
												"��ԭ��δ����ԭ�㴫����",
												"The origin sensor was not triggered after returning to its original position"}},
		{ERR_PEl,								{"ERR_PEl",
												"�����޴���",
												"Positive Limit Trigger"}},
		{ERR_NEL,								{"ERR_NEL",
												"�����޴���",
												"Negative Limit Trigger"}},
		{ERR_Anti_Collision_Sensor_Triggered_X, {"ERR_Anti_Collision_Sensor_Triggered_X",
												"������X�᷽���ײ��Ӧ",
												"Integration Ball X-axis Collision Avoidance Sensing"}},
		{ERR_Anti_Collision_Sensor_Triggered_Y, {"ERR_Anti_Collision_Sensor_Triggered_Y",
												"������Y�᷽���ײ��Ӧ",
												"Integration Ball Y-axis Collision Avoidance Sensing"}},
		{ERR_Read_Sensor_Value,					{"ERR_Read_Sensor_Value",
												"�����봫����ʧ��",
												"Reading distance sensor failed"}},
		{ERR_EyeBox_Movement_Exceeds_Limit,		{"ERR_EyeBox_Movement_Exceeds_Limit",
												"����EyeBox��������",
												"Exceeding EyeBox distance limit"}},
		{ERR_OpenSafetyDoor,					{"ERR_OpenSafetyDoor",
												"�򿪰�ȫ��ʧ��",
												"Failed to open the safety door"}},
		{ERR_OpenAllClampingCylinders,			{"ERR_OpenAllClampingCylinders",
												"�򿪼�צ����ʧ��",
												"Failed to open the gripper cylinder"}},
		{ERR_CloseSafetyDoor,					{"ERR_CloseSafetyDoor",
												"�رհ�ȫ��ʧ��",
												"Closing the safety door failed"}},
		{ERR_CloseAllClampingCylinders,			{"ERR_CloseAllClampingCylinders",
												"�رռ�צ����ʧ��",
												"Closing the gripper cylinder failed"}},
		{ERR_TurnOn_IonFan,						{"ERR_TurnOn_IonFan",
												"�����Ӵ���ʧ��",
												"Failed to open ion fan"}},
		{ERR_TurnOff_IonFan,					{"ERR_TurnOff_IonFan",
												"�ر����Ӵ���ʧ��",
												"Failed to turn off ion fan"}},
		{ERR_EyeBoxConfig,						{"ERR_EyeBoxConfig",
												"EyeBox���ô���",
												"EyeBox configuration error"}},
		{ERR_Read_EyeBoxIndex,					{"ERR_Read_EyeBoxIndex",
												"��ȡ��ǰEyeBox���Դ���ʧ��",
												"Failed to obtain the current number of EyeBox tests"}},
		{ERR_Read_EyeBoxLoop,					{"ERR_Read_EyeBoxLoop",
												"��ȡEyeBoxLoop����ʧ��",
												"Failed to obtain EyeBoxLoop data"}},
		{ERR_SW_AxisSafetyCheckY,				{"ERR_SW_AxisSafetyCheckY",
												"��� �ῨY��ȫ��ⴥ��",
												"Software Axis Card Y Security Detection Triggered"}},
		{ERR_SW_AxisSafetyCheckZ,				{"ERR_SW_AxisSafetyCheckZ",
												"��� �ῨZ��ȫ��ⴥ��",
												"Software Axis Card Z Security Detection Triggered"}},
		{ERR_HW_AxisSafetyCheck,				{"ERR_HW_AxisSafetyCheck",
												"Ӳ�� �Ῠ��ȫ��ⴥ��",
												"Hardware axis card security detection triggered"}},
		{ERR_DUT_NotExist,						{"ERR_DUT_NotExist",
												"δ��⵽������",
												"No test object detected"}},
		{ERR_DUT_StillExist,					{"ERR_DUT_StillExist",
												"���������",
												"Residues of the tested substance"}},
		{ERR_DUT_AirPressure,					{"ERR_DUT_AirPressure",
												"����ѹ�쳣",
												"Abnormal total pressure"}},
		{ERR_SafetyDoorOpen,					{"ERR_SafetyDoorOpen",
												"��δ�ر�",
												"Safety door open"}},
		{ERR_GratingTrigger,					{"ERR_GratingTrigger",
												"��դ����",
												"GratingTrigger"}},
		{ERR_ThermoHygro,						{"ERR_ThermoHygro",
												"��ʪ���쳣",
												"ThermoHygro error"}},
		{ERR_SmallPushBlockIn,					{"ERR_SmallPushBlockIn",
												"С�ƿ춯���쳣(��)",
												"Abnormal action of small push block(In)"}},
		{ERR_SmallPushBlockOut,					{"ERR_SmallPushBlockOut",
												"С�ƿ춯���쳣(��)",
												"Abnormal action of small push block(Out)"}},
		{ERR_BigPushBlockIn,					{"ERR_BigPushBlockIn",
												"���ƿ춯���쳣(��)",
												"Abnormal action of big push block(In)"}},
		{ERR_BigPushBlockOut,					{"ERR_BigPushBlockOut",
												"���ƿ춯���쳣(��)",
												"Abnormal action of big push block(Out)"}},
		{ERR_GripperSensingIsNotOn,				{"ERR_GripperSensingIsNotOn",
												"��צ��Ӧû��ON",
												"Gripper sensing is not on"}},
		{ERR_GripperSensingIsNotOff,			{"ERR_GripperSensingIsNotOff",
												"��צ��Ӧû��OFF",
												"Gripper sensing is not off"}},
		};
		return errorPrompts;
	}
};
