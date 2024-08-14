#pragma once

// 定时器定义
#define TIMER_CONNECT				(1001)
#define TIMER_IO					(1002)
#define TIMER_AXISPOS				(1003)
#define TIMER_CARD_STATUS			(1004)

// 颜色定义
#define STATE_COLOR_RED				(0xFFFF0000)
#define STATE_COLOR_GREEN			(0xFF00FF00)
#define STATE_COLOR_WHITE			(0xFFFFFFFF)
#define STATE_COLOR_GRAY			(0xFFF7F6F6)
#define STATE_COLOR_GRAY1			(0xFFC5D4F2)

// 轴控件名定义
#define	Btn_CardConnect				"btn_cardConnect"				// 连接板卡
#define	Btn_CardClose				"btn_cardClose"					// 断开板卡
#define	List_AxisList				"list_Axis"						// 轴名列表
#define	Lable_CurrentAxis			"lable_CurAxis"					// 当前轴名
#define	List_AxisPos				"list_AxisPos"					// 轴位置列表
#define	Btn_AxisPosParasSave		"btn_AxisPosParasSave"			// 保存位置参数
#define	Btn_AxisPosAdd				"btn_AxisPosAdd"				// 添加位置
#define	Btn_AxisPosDel				"btn_AxisPosDel"				// 删除位置
#define	Btn_AxisNRelativeMove		"btn_nRelativeMove"				// 负向相对运动
#define	Edit_AxisRelativeMove		"edit_RelativeMove"				// 相对运动物理位置值(mm/°)
#define	Btn_AxisPositiveMove		"btn_PositiveMove"				// 正向相对运动
#define	Btn_AxisAbsMove				"btn_AbsMove"					// 绝对运动
#define	Lable_AxisCurrentPos		"lable_CurPos"					// 当前轴位置
#define	Btn_AxisParasDlgOpen		"btn_AxisParasDlgOpen"			// 打开轴参数配置界面
#define	Btn_AxisAdd					"btn_AxisAdd"					// Ìí¼ÓÎ»ÖÃ
#define	Btn_AxisDel					"btn_AxisDel"					// É¾³ýÎ»ÖÃ
#define	Btn_AxisEnable				"btn_AxisEnable"				// 轴使能
#define	Btn_AxisDisable				"btn_AxisDisable"				// 轴失能
#define	Btn_AxisHome				"btn_AxisHome"					// 轴回零运动
#define	Btn_AxisStop				"btn_AxisStop"					// 轴停止运动
#define	Btn_AxisVmoveNegative		"btn_vmove_negative"			// 轴按住持续后退
#define	Btn_AxisVmovePositive		"btn_vmove_positive"			// 轴按住持续前进
#define	Btn_AxisClearError			"btn_AxisClearError"			// 轴清除错误
#define	Btn_CardReset				"btn_CardReset"					// 板卡热复位
#define	Lable_CardAlarm				"lable_CardAlarm"				// 轴报警状态
#define	Lable_CardServo				"lable_CardServo"				// 轴伺服状态
#define	Lable_CardPEL				"lable_CardPEL"					// 轴正极限状态
#define	Lable_CardORG				"lable_CardORG"					// 轴原点状态
#define	Lable_CardNEL				"lable_CardNEL"					// 轴负极限状态
#define	Lable_CardConnectStatus		"lable_CardConnectStatus"		// 板卡连接状态
#define	Lable_PosName				"lable_PosName"					// 点位界面移动按钮
#define	Lable_PosValue				"lable_PosValue"				// 点位界面移动按钮
#define	Edit_PosStep				"edit_PosStep"					// 点位界面移动按钮
#define	Btn_AxisPosMove				"btn_AxisPosMove"				// 点位界面移动按钮
#define	Edit_PosValueDebug			"edit_PosValueDebug"			// 点位界面移动按钮
#define	Btn_SocketCoveOpen			"btn_SocketCoveOpen"			// socket盖子打开
#define	Btn_SocketCoveClose			"btn_SocketCoveClose"			// socket盖子关闭
#define	Btn_SocketCoveUp			"btn_SocketCoveUp"				// socket盖子上升
#define	Btn_SocketCoveDown			"btn_SocketCoveDown"			// socket盖子下降
#define	Btn_SocketCoveCloseDown		"btn_SocketCoveCloseDown"		// socket盖子关闭并下降
#define	Btn_SocketCoveUpOpen		"btn_SocketCoveUpOpen"			// socket盖子上升并打开
#define	Btn_CylHoldDut				"btn_CylHoldDut"				// 真空吸吸紧DUT
#define	Btn_CylPutDut				"btn_CylPutDut"					// 真空吸松开DUT

// 轴名
#define AXIS_Name_Ty				"AxisTy"
#define AXIS_Name_Tx				"AxisTx"
#define AXIS_Name_YPnp				"AxisYPnp"
#define AXIS_Name_XPnp				"AxisXPnp"
#define AXIS_Name_ZPnp				"AxisZPnp"
#define AXIS_Name_RPnp				"AxisRPnp"
#define AXIS_Name_DILX				"AxisDILX"
#define AXIS_Name_DILY				"AxisDILY"

// 位置名
#define POSNAME_A1					"A1" 
#define POSNAME_A2					"A2" 
#define POSNAME_A3					"A3" 
#define POSNAME_A4					"A4" 
#define POSNAME_A5					"A5" 
#define POSNAME_A6					"A6" 
#define POSNAME_A7					"A7" 
#define POSNAME_B1					"B1" 
#define POSNAME_B2					"B2" 
#define POSNAME_B3					"B3" 
#define POSNAME_B4					"B4" 
#define POSNAME_B5					"B5" 
#define POSNAME_B6					"B6" 
#define POSNAME_B7					"B7" 
#define POSNAME_C1					"C1" 
#define POSNAME_C2					"C2" 
#define POSNAME_C3					"C3" 
#define POSNAME_C4					"C4" 
#define POSNAME_C5					"C5" 
#define POSNAME_C6					"C6" 
#define POSNAME_C7					"C7" 
#define POSNAME_Initial				"Initial"

#define POSNAME_YPnp_Load		"PickUpDut" 
#define POSNAME_YPnp_UnLoad		"PutDownDut" 
#define POSNAME_YPnp_UnLoadCam	"UnLoadCam"
#define POSNAME_YPnp_BottomCam	"DownCamera" 
#define POSNAME_YPnp_TopCam		"UpCamera" 
#define POSNAME_RPnp_WorkPos	"AxisRWorkPos"
#define POSNAME_XPnp_WorkPos	"AxisXWorkPos"
#define POSNAME_ZPnp_WorkPos	"AxisZWorkPos"
#define POSNAME_ZPnp_SafetyPos	"AxisZSafetyPos"

//DUT两个飞拍点位
#define POSNAME_AXISY_B2B		"B2BAxisY"
#define POSNAME_AXISY_2DBC		"Dut_2DBC_AxisY"


#define POSNAME_DIL_Socket_X		"DILAXisXSocket" 
#define POSNAME_DIL_Socket_Y		"DILAXisYSocket" 


//Auto 校准点位
#define POSNAME_CailbraReadyPos		"CailbraReadyPos"

