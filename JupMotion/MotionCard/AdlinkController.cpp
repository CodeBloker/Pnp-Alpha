#include "AdlinkController.h"
#include "JupCore.h"

std::string ToHexString(unsigned char* input, int datasize)
{
	char output[3];
	std::string result;
	for (int j = 0; j < datasize; j++)
	{
		sprintf_s(output, 3, "%02X", input[j]);
		result += output;
	}
	return result;
}

AdlinkController::AdlinkController()
{
	m_pMotionParameter = new MotionParameter();
}

AdlinkController::~AdlinkController()
{
	if (m_pMotionParameter)
	{
		delete m_pMotionParameter;
	}		
}

int AdlinkController::InitAdlinkCard()
{
	/****************************7856控制IO临时使用********************************/
	// 初始化设备
	if (0 != InitCard(CardConfig::CardNo))
	{
		return JError::ERR_CardInit;
	}
	// 开启总线网络
	if (0 != StartFieldBus(CardConfig::CardNo, CardConfig::BusNo, CardConfig::StartAxisId))
	{
		return JError::ERR_StartFieldBus;
	}

	// 飞拍设置
	if (0 != ResetTriggerPos("AxisYPnp"))
	{
		return JError::ERR_StartFieldBus;
	}
	//auto paras = m_pMotionParameter->GetAxisPosInfo("AxisYPnp", "DownCamera");
	//if (0 != ResetTriggerPos(CardConfig::CardNo, paras->distance))
	//{
	//	return JError::ERR_StartFieldBus;
	//}
	//std::vector<double> pos_list;
	//pos_list.push_back(paras->distance);
	//if (0 != SetTriggerListPos("AxisYPnp", EnumMotorTriggerMode::NegativeD01D02Mode, pos_list))
	//{
	//	return JError::ERR_StartFieldBus;
	//}

	auto axisList = m_pMotionParameter->GetAxisNameList();
	for (auto axis : axisList)
	{
		auto info = m_pMotionParameter->GetAxisParam(axis);
		// 轴使能
		if (0 != AxisOn(info->axisNum))
		{
			return JError::ERR_AxisServoOnAll;
		}
		// 设置原点位置（因无原点信号，手动移动轴到位置后设置当前点为原点）
		if (0 != SetAxisHomePos(info->axisNum))
		{
			return JError::ERR_CardInit;
		}
	}
	m_IsCardInit = true;
	return 0;
}

int AdlinkController::CloseAdlinkCard()
{
	// 关闭总线
	if (StopFieldBus(CardConfig::CardNo, CardConfig::BusNo))
	{
		return JError::ERR_StopFieldBus;
	}
	// 关闭所有板卡
	if (CloseAllCard())
	{
		m_IsCardInit = false;
	}
	return 0;
}

bool AdlinkController::IsCardInit()
{
	return m_IsCardInit;
}

int AdlinkController::AxisServoOn(std::string axisName)
{
	auto paras = m_pMotionParameter->GetAxisParam(axisName);

	if (0 != AxisOn(paras->axisNum))
	{
		return JError::ERR_AxisServo;
	}
	return 0;
}

int AdlinkController::AxisServoOff(std::string axisName)
{
	auto paras = m_pMotionParameter->GetAxisParam(axisName);

	if (0 != AxisOff(paras->axisNum))
	{
		return JError::ERR_AxisServo;
	}
	return 0;
}

int AdlinkController::AxisAbsMove(const std::string & axisName, double distance, double dbOffset, double ratio)
{
	m_bSetStopWait = false;
	// 获取轴参数
	auto para = m_pMotionParameter->GetAxisParam(axisName);
	double maxVel = para->maxVel * (ratio / 100.0);
	double accVel = para->accVel * (ratio / 100.0);
	double decVel = para->decVel * (ratio / 100.0);
	//if (halspeed)
	//{
	//	maxVel = para->maxVel * 0.6;
	//	accVel = para->accVel * 0.6;
	//	decVel = para->decVel * 0.6;
	//}
	// 设置运动参数
	if (0 != SetAxisParam(para->axisNum, 0, maxVel, 0, accVel, decVel))
	{
		return JError::ERR_SetMoveParam;
	}
	// 根据当量换算实际脉冲
	int nPulse = para->equiv * (distance + dbOffset);
	// 轴运动
	if (0 != AbsMove(para->axisNum, nPulse, maxVel))
	{
		return JError::ERR_MoveToPos;
	}
	return 0;
}

int AdlinkController::WaitAxisAbsMove(const std::string & axisName, double distance)
{
	double timeOut = jCore->GlobalSettings().ReadDouble("Test_Settings", "MotionTimeOut");
	auto para = m_pMotionParameter->GetAxisParam(axisName);

	long dieTime = GetTickCount() + (long)timeOut;

	while (true)
	{
		Sleep(5);
		if (m_bSetStopWait)
		{
			StopAxis(para->axisNum, 0);
			return JError::ERR_StopWaitMove;
		}

		long curTime = GetTickCount();

		if (curTime > dieTime)
		{
			StopAxis(para->axisNum, 0);
			return JError::ERR_MotionMoveTimeOut;
		}

		// 所有轴软件限位
		//double dbCurPos = GetCurrentPos(axisName);
		//int nDir = 0;
		//if (dbCurPos - distance > 0)
		//	nDir = -1;
		//else
		//	nDir = 1;
		//int nRet = SoftWare_AutoCheck(axisName, nDir);
		//if (0 != nRet)
		//{
		//	StopAxisMove(axisName);
		//	return JError::ERR_SW_AxisSafetyCheckZ;
		//}

		// 检查轴当前位置是否与预设位置相等
		double currentPos_pulse;
		GetAxisPosition(para->axisNum, currentPos_pulse);
		double currentPos_mm = currentPos_pulse / para->equiv;
		bool isEqul = abs(distance - currentPos_mm) <= para->allowErrorPos;
		// 检查轴是否停止
		bool isBusy = IsAxisBusy(para->axisNum);
		if (isBusy || !isEqul)
		{
			continue;
		}
		else
		{
			break;
		}
	}
	return 0;
}

int AdlinkController::AxisAbsMoveToPos(const std::string & axisName, const std::string & strPositionName, double dbOffset)
{
	auto para = m_pMotionParameter->GetAxisPosInfo(axisName, strPositionName);
	return AxisAbsMove(axisName, para->distance, dbOffset);
}

int AdlinkController::AxisMoveDistance(const std::string & axisName, double distance)
{
	m_bSetStopWait = false;
	dbBeginPos = 0.0;

	auto para = m_pMotionParameter->GetAxisParam(axisName);

	if (0 != SetAxisParam(para->axisNum, 0, para->maxVel, 0, para->accVel, para->decVel))
	{
		return JError::ERR_SetMoveParam;
	}
	int nPulse = distance * para->equiv;
	dbBeginPos = GetCurrentPos(axisName);
	if (0 != RelativeMove(para->axisNum, nPulse, para->maxVel))
	{
		return JError::ERR_MoveDistance;
	}
	return 0;
}

int AdlinkController::WaitAxisMoveDistance(const std::string & axisName, double distance)
{
	double timeOut = jCore->GlobalSettings().ReadDouble("Test_Settings", "MotionTimeOut");

	auto para = m_pMotionParameter->GetAxisParam(axisName);

	long dieTime = GetTickCount() + (long)timeOut;

	while (true)
	{
		Sleep(5);
		if (m_bSetStopWait)
		{
			StopAxis(para->axisNum, 0);
			return JError::ERR_StopWaitMove;
		}

		long curTime = GetTickCount();

		if (curTime > dieTime)
		{
			StopAxis(para->axisNum, 0);
			return JError::ERR_MotionMoveTimeOut;
		}

		// 限位检查
		//int nDir = 0;
		//double dbCurPos = GetCurrentPos(axisName);
		//if (dbCurPos - dbBeginPos > 0)
		//	nDir = 1;
		//else
		//	nDir = -1;
		//int nRet = SoftWare_AutoCheck(axisName, nDir);
		//if (0 != nRet)
		//{
		//	StopAxisMove(axisName);
		//	return JError::ERR_SW_AxisSafetyCheckZ;
		//}

		// 检查轴当前位置是否与预设位置相等
		double currentPos_pulse;
		GetAxisPosition(para->axisNum, currentPos_pulse);
		double currentPos_mm = currentPos_pulse / para->equiv;

		bool isEqul = abs(abs(currentPos_mm) - abs(dbBeginPos)) >= (abs(distance) - para->allowErrorPos);
		bool isDone = IsMoveDone(para->axisNum);
		if (!isDone || !isEqul)
		{
			continue;
		}
		else
		{
			break;
		}
	}
}

int AdlinkController::StopAxisMove(const std::string & axisName)
{
	int nAxisIndex = m_pMotionParameter->GetAxisParam(axisName)->axisNum;

	if (0 != StopAxis(nAxisIndex, 0))
	{
		return JError::ERR_StopMoveAxis;
	}
	return 0;
}

int AdlinkController::EMG_StopAxisMove(const std::string & axisName)
{
	int nAxisIndex = m_pMotionParameter->GetAxisParam(axisName)->axisNum;

	if (0 != EMGStop(nAxisIndex))
	{
		return JError::ERR_EMGStopMoveAxis;
	}
	return 0;
}

bool AdlinkController::IsAlarm(const std::string & axisName)
{
	int nAxisIndex = m_pMotionParameter->GetAxisParam(axisName)->axisNum;

	return GetAlarm(nAxisIndex);
}

bool AdlinkController::IsPEL(const std::string & axisName)
{
	int nAxisIndex = m_pMotionParameter->GetAxisParam(axisName)->axisNum;

	return GetPEL(nAxisIndex);
}

bool AdlinkController::IsNEL(const std::string & axisName)
{
	int nAxisIndex = m_pMotionParameter->GetAxisParam(axisName)->axisNum;

	return GetNEL(nAxisIndex);
}

bool AdlinkController::IsORG(const std::string & axisName)
{
	int nAxisIndex = m_pMotionParameter->GetAxisParam(axisName)->axisNum;

	return GetORG(nAxisIndex);
}

bool AdlinkController::IsSvon(const std::string & axisName)
{
	int nAxisIndex = m_pMotionParameter->GetAxisParam(axisName)->axisNum;

	return GetSvon(nAxisIndex);
}

int AdlinkController::IO_SetOutput(int card_num, int mod_num, int bit_num, int on_off)
{
	// 干涉检查

	// 执行io指令
	return SetChannelDo(card_num, mod_num, bit_num, on_off);
}

int AdlinkController::IO_GetOutput(int card_num, int mod_num, int bit_num)
{
	I32 on_off = -1;
	int ret = GetChannelDo(card_num, mod_num, bit_num, on_off);
	if (ret == 0)
		return on_off;
	else
		return ret;
}

int AdlinkController::IO_GetInput(int card_num, int mod_num, int bit_num)
{
	I32 on_off = -1;
	int ret = GetChannelDi(card_num, mod_num, bit_num, on_off);
	if (ret == 0)
		return on_off;
	else
		return ret;
}

int AdlinkController::ResetTriggerPos(int axis_id, double pos)
{
	INT32 ReData = 0;

	///////以当前位置为零点
	UINT16 ODIndex = 0x2018;
	UINT16 ODSubIndex = 0x5;
	INT32 CommdData = 1;//0：不使能 //1：使能(上升沿有效)
	UINT32 DataLen = 2;
	int ret = WriteReadSDO(2, ODIndex, ODSubIndex, CommdData, DataLen, ReData);
	if (ret < 0) return -1;

	ODIndex = 0x2018;
	ODSubIndex = 0x5;
	CommdData = 0;//0：不使能 //1：使能(上升沿有效)
	DataLen = 2;
	ret = WriteReadSDO(2, ODIndex, ODSubIndex, CommdData, DataLen, ReData);
	if (ret < 0) return -2;
	return 0;
}

int AdlinkController::ResetTriggerPos(const std::string& axisName)
{
	auto para = m_pMotionParameter->GetAxisParam(axisName);
	INT32 ReData = 0;

	///////以当前位置为零点
	UINT16 ODIndex = 0x2018;
	UINT16 ODSubIndex = 0x5;
	INT32 CommdData = 1;//0：不使能 //1：使能(上升沿有效)
	UINT32 DataLen = 2;
	int ret = WriteReadSDO(para->axisNum, ODIndex, ODSubIndex, CommdData, DataLen, ReData);
	if (ret < 0) return -1;

	ODIndex = 0x2018;
	ODSubIndex = 0x5;
	CommdData = 0;//0：不使能 //1：使能(上升沿有效)
	DataLen = 2;
	ret = WriteReadSDO(para->axisNum, ODIndex, ODSubIndex, CommdData, DataLen, ReData);
	if (ret < 0) return -2;
	return 0;
}

int AdlinkController::SetTriggerListPos(std::string axisName, EnumMotorTriggerMode trigger_mode, std::vector<double> pos_list)
{
	INT32 ReData = 0;
	///////清空标志位
	UINT16 ODIndex = 0x2018;
	UINT16 ODSubIndex = 0x1;
	INT32 CommdData = 0;  ////0：不使能 ////1：使能(上升沿有效)
	UINT32 DataLen = 2;
	int ret = WriteReadSDO(2, ODIndex, ODSubIndex, CommdData, DataLen, ReData, true, false);
	if (ret < 0) return -1;

	///////设置标志位
	ODIndex = 0x2018;
	ODSubIndex = 0x1;
	CommdData = 1;  ////0：不使能 ////1：使能(上升沿有效)
	DataLen = 2;
	ret = WriteReadSDO(2, ODIndex, ODSubIndex, CommdData, DataLen, ReData, true, false);
	if (ret < 0) return -2;

	/////////////位置比较模式选择
	ODIndex = 0x2018;
	ODSubIndex = 0x4;
	CommdData = 0;//0-单次绝对比较模式 //1-循环增量比较模式
	DataLen = 2;
	ret = WriteReadSDO(2, ODIndex, ODSubIndex, CommdData, DataLen, ReData, true, false);
	if (ret < 0) return -3;

	///////位置比较输出宽度
	ODIndex = 0x2018;
	ODSubIndex = 0x6;
	CommdData = 300;//0.0ms~204.7ms
	DataLen = 2;
	ret = WriteReadSDO(2, ODIndex, ODSubIndex, CommdData, DataLen, ReData, true, false);
	if (ret < 0) return -4;

	///////比较逻辑的起始
	ODIndex = 0x2018;
	ODSubIndex = 0x8;
	CommdData = 1;//0-30
	DataLen = 2;
	ret = WriteReadSDO(2, ODIndex, ODSubIndex, CommdData, DataLen, ReData, true, false);
	if (ret < 0) return -5;

	///////比较逻辑的终点
	ODIndex = 0x2018;
	ODSubIndex = 0x9;
	CommdData = pos_list.size();//0-30
	DataLen = 2;
	ret = WriteReadSDO(2, ODIndex, ODSubIndex, CommdData, DataLen, ReData, true, false);
	if (ret < 0) return -6;

	/////设置触发位置
	//获取电子齿轮比分子
	ODIndex = 0x2005;
	ODSubIndex = 0x08;
	CommdData = 0;
	DataLen = 4;
	ret = WriteReadSDO(2, ODIndex, ODSubIndex, CommdData, DataLen, ReData, false, true);
	if (ret < 0) return -7;
	double MotorResolutionDenominator = 8388608/*ReData*/;
	//获取电子齿轮比分母
	ODIndex = 0x2005;
	ODSubIndex = 0x0A;
	CommdData = 0;
	DataLen = 4;
	ret = WriteReadSDO(2, ODIndex, ODSubIndex, CommdData, DataLen, ReData, false, true);
	if (ret < 0) return -8;
	double MotorResolutionMolecule = 10000/*ReData*/;

	auto para = m_pMotionParameter->GetAxisParam(axisName);
	for (int i = 0; i < pos_list.size(); i++)
	{
		double PositionInPulse = (para->equiv * pos_list[i]);

		////设置位置
		ODIndex = 0x2019;
		ODSubIndex = (unsigned short)(1 + i * 3);/////0x1;/////////0x01 0x04 0x07 0x0A 0x0D 0x10 0x13 0x16
		CommdData = (INT32)(PositionInPulse * MotorResolutionDenominator / MotorResolutionMolecule);//位置
		DataLen = 4;
		ret = WriteReadSDO(2, ODIndex, ODSubIndex, CommdData, DataLen, ReData, true, false);
		if (ret < 0) return -9;

		////设置模式
		ODIndex = 0x2019;
		ODSubIndex = (unsigned short)(3 + i * 3); ///////0x3;/////////0x03 0x06 0x09 0x0C 0x0F 0x12 0x01 0x01
		switch (trigger_mode)//////TriggerMode;///0 比较逻辑跳过该点  1 正向穿越比较输出  2 反向穿越比较输出  3 正反向穿越比较输出
		{
		case EnumMotorTriggerMode::SkipMode:
			CommdData = 0;
			break;
		case EnumMotorTriggerMode::PositiveMode:
			CommdData = 1;
			break;
		case EnumMotorTriggerMode::NegativeMode:
			CommdData = 2;
			break;
		case EnumMotorTriggerMode::NegativeD01D02Mode:
			CommdData = 386;
			break;
		case EnumMotorTriggerMode::AutoMode:
			CommdData = (GetCurrentPos(axisName) < pos_list[i]) ? 1 : 2;
			break;
		}
		DataLen = 2;
		ret = WriteReadSDO(2, ODIndex, ODSubIndex, CommdData, DataLen, ReData, true, false);
		if (ret < 0) return -10;
	}
	return 0;
}

int AdlinkController::WriteReadSDO(int axis_slave, UINT16 ODIndex, UINT16 ODSubIndex, INT32 CommdData, UINT32 DataLen, INT32 & ReData, bool IsWrite, bool IsRead, int time_out)
{
	ReData = 0;

	INT32 BUS_No = 0;
	int ret = 0;

	U8 SetData[32];
	for (int i = 0; i < 8; i++)
	{
		SetData[i] = ((CommdData >> (i * 8)) & 0xFF);
	}

	if (IsWrite)
	{
		ret = APS_set_field_bus_sdo(CardConfig::CardNo, BUS_No, axis_slave, ODIndex, ODSubIndex, SetData, DataLen, time_out, 0);
		if (ret < 0) return ret;
	}
	//if (IsRead)
	//{
	//	U32 OutDataLength = 0;
	//	U8 OutData[32];
	//	std::string str, tempstr;
	//	bool stringflag = false;
	//	ret = APS_get_field_bus_sdo(CardConfig::CardNo, BUS_No, axis_slave, ODIndex, ODSubIndex, OutData, DataLen, &OutDataLength, time_out, 0);
	//	if (ret < 0) return ret;
	//	for (int i = 1; i <= 32; i++)
	//	{
	//		tempstr = ToHexString(&OutData[32 - i], 1);
	//		//tempstr = std::string(2 - tempstr.length(), '0') + tempstr; //左边补位0
	//		str += tempstr;
	//		if (((i - 1) >= 8) && (OutData[i - 1] != 0))
	//			stringflag = true;
	//	}
	//	str = "0x" + str;
	//	if (stringflag)
	//	{
	//		return -1;
	//	}
	//	else
	//	{
	//		//ReData = Convert.ToInt32(str, 16);
	//		ReData = stoi(str, 0, 16);
	//	}
	//}
	//if (IsWrite && IsRead)
	//{
	//	if (CommdData != ReData)
	//	{
	//		return -2;
	//	}
	//}
	return 0;
}

int AdlinkController::WriteReadPDO(UINT16 ByteOffset, UINT16 Size, UINT & Value, bool IsWrite, bool IsRead)
{
	return 0;
}

MotionParameter * AdlinkController::GetMotionParameter()
{
	return m_pMotionParameter;
}

int AdlinkController::AxisMoveDistance(const std::string & axisName, double distance, double maxVel, double accVel, double decVel)
{
	m_bSetStopWait = false;
	dbBeginPos = 0.0;

	auto para = m_pMotionParameter->GetAxisParam(axisName);

	if (0 != SetAxisParam(para->axisNum, 0, maxVel, 0, accVel, decVel))
	{
		return JError::ERR_SetMoveParam;
	}
	int nPulse = distance * para->equiv;
	dbBeginPos = GetCurrentPos(axisName);
	if (0 != RelativeMove(para->axisNum, nPulse, maxVel))
	{
		return JError::ERR_MoveDistance;
	}
	return 0;
}

void AdlinkController::AxisStopWait()
{
	m_bSetStopWait = true;
}

int AdlinkController::AxisHome(const std::string & axisName)
{
	m_bSetStopWait = false;

	auto para = m_pMotionParameter->GetAxisParam(axisName);

	int Mode = para->homeMode;
	int Dir = para->homeDir;
	double Curve = para->homeCurve;
	double Acc = para->homeAccVel;
	double MV = para->homeMaxVel;
	double VO = para->homeMinVel;
	double EZA = para->homeEZA;
	int offset = para->homeOffsetPos;

	if (0 != setAxisHomePara(para->axisNum, Mode, Dir, Curve, Acc, MV, VO, offset, EZA))
	{
		return JError::ERR_SetMoveParam;
	}

	if (0 != axisHome(para->axisNum))
	{
		return JError::ERR_MotionHome;
	}
	return 0;
}

int AdlinkController::WaitAxisHome(const std::string & axisName)
{
	int nAxisIndex = m_pMotionParameter->GetAxisParam(axisName)->axisNum;
	double timeOut = jCore->GlobalSettings().ReadDouble("Test_Settings", "MotionTimeOut");

	I32 motion_status;

	long dieTime = GetTickCount() + (long)timeOut;

	while (true)
	{
		Sleep(5);
		if (m_bSetStopWait)
		{
			StopAxis(nAxisIndex, 0);
			return JError::ERR_StopWaitMove;
		}

		long curTime = GetTickCount();

		if (curTime > dieTime)
		{
			StopAxis(nAxisIndex, 0);
			return JError::ERR_MotionMoveTimeOut;
		}

		//if (m_bSoftWareLimitTriggered)
		//{
		//	StopAxisMove(axisName);
		//	return JError::ERR_SW_AxisSafetyCheckZ;
		//}
		double currentPos_pulse;
		GetAxisPosition(nAxisIndex, currentPos_pulse);
		bool isHomePos = (abs(currentPos_pulse) <= 50) ? true : false;
		bool isDone = IsMoveDone(nAxisIndex);
		if (isDone && isHomePos)
		{
			break;
		}
		else
		{
			continue;
		}
	}
	// 编码器，计数器清零
	if (0 != SetAxisHomePos(nAxisIndex))
	{
		return JError::ERR_MotionHome;
	}
	// 轴回零标志位置为true, 代表该轴已经执行过回零保护
	{
		auto axisInfo = m_pMotionParameter->GetAxisParam(axisName);
		axisInfo->IsMoveZero = true;
	}
	return 0;
}

double AdlinkController::GetCurrentPos(const std::string & axisName)
{
	auto para = m_pMotionParameter->GetAxisParam(axisName);
	double dbPos = 0;
	GetAxisPosition(para->axisNum, dbPos);
	dbPos = dbPos / para->equiv;
	return dbPos;
}
