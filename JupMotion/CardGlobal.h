#ifndef DMCCARD_GLOBAL_H
#define DMCCARD_GLOBAL_H

#define DataID				"ID"
//*****************Axis******************//
#define Axis_AxisName		"axisName"
#define Axis_AxisNameCn		"axisNameCn"
#define Axis_MotorType		"motorType"
#define Axis_CardType		"cardType"
#define Axis_CardNum		"cardNum"
#define Axis_AxisNum		"axisNum"
#define Axis_Minvel			"minVel"
#define Axis_MaxVel			"maxVel"
#define Axis_AccVel			"accVel"
#define Axis_DecVel			"decVel"
#define Axis_StopVel		"stopVel"
#define Axis_SPara			"sPara"
#define Axis_ErrorPos		"allowErrorPos"
#define Axis_Equiv			"equiv"
#define Axis_Lead			"lead"
#define Axis_HomeMode		"homeMode"
#define Axis_HomeDir		"homeDir"
#define Axis_HomeMinVel		"homeMinVel"
#define Axis_HomeMaxVel		"homeMaxVel"
#define Axis_HomeAccVel		"homeAccVel"
#define Axis_HomeDecVel		"homeDecVel"
#define Axis_HomeOffSetPos	"homeOffsetPos"
#define Axis_HomeCurve		"homeCurve"
#define Axis_HomeEZA		"homeEZA"
#define Axis_MsTimeOut		"msTimeout"
#define Axis_UseDelay		"useDelay"
#define Axis_UseLimit		"useLimit"
#define Axis_PositiveLimit	"positiveLimit"
#define Axis_NegativeLimit	"negativeLimit"

//******************IO********************//
#define IO_Name				"IOName"
#define IO_CardNum			"cardNum"
#define IO_BitNum			"bitNum"
#define IO_State			"state"
#define IO_IsUsed			"isUsed"
#define IO_HighName			"highName"
#define IO_CnName			"cnName"
#define IO_Group			"IOGroup"
#define IO_CardType			"cardType"

//*******DMC MoveCondtion*************
#define MOVE_ConditionType "ConditionType"
#define MOVE_ConditionName "ConditionName"
#define MOVE_ConditionValue "ConditionValue"

//*******DMC Model&&Postion*************
#define Model_Name  "modelName"
#define Notes "notes"
#define Postion_Name "posName"
#define PositionValue "posValue"
#define PositionSpacing "posSpacing"

//*******DMC interference*************
#define Interference_Name "interferenceName" 
#define Interference_Data "interferenceData"

//*******数据库字段名***************
#define DatabaseFields_ID "ID"
#define DatabaseFields_Position "Position"
#define DatabaseFields_Model "Model"
#define DatabaseFields_AxisName "AxisName"
#define DatabaseFields_AxisID   "AxisID" 
#define DatabaseFields_ModelID   "ModelID" 
#define DatabaseFields_PostionID   "PostionID" 


#endif // !DMCCARD_GLOBAL_H