#pragma once
#include <string>
#include "json/json.h"
#include "CardGlobal.h"

class MotionAxis
{
public:
	int axisID = 0;
	std::string axisName;
	std::string axisNameCn;
	std::string motorType;
	std::string cardType;
	int cardNum = 0;
	int axisNum = 0;
	double minVel = 3000.0;
	double maxVel = 5000.0;
	double accVel = 50000.0;
	double decVel = 50000.0;
	double stopVel = 0.0;
	double sPara = 0.0;
	double allowErrorPos = 0.005;
	double equiv = 1000;
	double lead = 0;
	int homeMode = 0;
	int homeDir = 0;
	double homeMinVel = 2000.0;
	double homeMaxVel = 3000.0;
	double homeAccVel = 30000.0;
	double homeDecVel = 30000.0;
	double homeOffsetPos = 0.0;
	double homeCurve = 0.0;
	int homeEZA = 0;
	int msTimeout = 30000;
	bool useDelay = 0;
	bool useLimit = 0;
	double positiveLimit = 0.0;
	double negativeLimit = 0.0;

	inline Json::Value toJSonObject()
	{
		Json::Value ob;
		ob[DataID] = axisID;
		ob[Axis_AxisName] = axisName;
		ob[Axis_AxisNameCn] = axisNameCn;
		ob[Axis_MotorType] = motorType;
		ob[Axis_CardType] = cardType;
		ob[Axis_CardNum] = cardNum;
		ob[Axis_AxisNum] = axisNum;
		ob[Axis_Minvel] = minVel;
		ob[Axis_MaxVel] = maxVel;
		ob[Axis_AccVel] = accVel;
		ob[Axis_DecVel] = decVel;
		ob[Axis_StopVel] = stopVel;
		ob[Axis_SPara] = sPara;
		ob[Axis_ErrorPos] = allowErrorPos;
		ob[Axis_Equiv] = equiv;
		ob[Axis_Lead] = lead;
		ob[Axis_HomeMode] = homeMode;
		ob[Axis_HomeDir] = homeDir;
		ob[Axis_HomeMinVel] = homeMinVel;
		ob[Axis_HomeMaxVel] = homeMaxVel;
		ob[Axis_HomeAccVel] = homeAccVel;
		ob[Axis_HomeDecVel] = homeDecVel;
		ob[Axis_HomeOffSetPos] = homeOffsetPos;
		ob[Axis_HomeCurve] = homeCurve;
		ob[Axis_HomeEZA] = homeEZA;
		ob[Axis_MsTimeOut] = msTimeout;
		ob[Axis_UseDelay]= useDelay;
		ob[Axis_UseLimit]= useLimit;
		ob[Axis_PositiveLimit]= positiveLimit;
		ob[Axis_NegativeLimit]= negativeLimit;
		return ob;
	}
};

class AxisPosition
{
public:
	int posID;
	int axisID;
	std::string axisName;
	std::string posName;
	double distance;
	double spacing;
	std::string notes;
};