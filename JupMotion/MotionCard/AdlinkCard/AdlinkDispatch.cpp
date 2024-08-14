#include "AdlinkDispatch.h"
#include "JError.h"

AdlinkDispatch::AdlinkDispatch()
{
}

AdlinkDispatch::~AdlinkDispatch()
{
}

I32 AdlinkDispatch::InitCard(I32 card_num)
{
	// Card ID information in bit format
	// 如果 BoardID_InBits 的值是 0x11，那就意味着您的系统中有两张板卡 ，并且板卡ID号是 0 和 4
	I32 boardID_InBits;
	//I32 boardID_InBits = 3;
	I32 ret = APS_initial(&boardID_InBits, INIT_AUTO_CARD_ID); // INIT_AUTO_CARD_ID自动模式
	// 有7856和8332俩张卡，boardID_InBits必须等于0x11
	if (boardID_InBits != /*0x11*/1)
	{
		return InitialError;
	}
	return NoError;
}

I32 AdlinkDispatch::CloseAllCard()
{
	if (!APS_close())
	{
		return CloseCardError;
	}
	return NoError;
}

I32 AdlinkDispatch::LoadParamFile(const char * file_name)
{
	return APS_load_param_from_file(file_name);
}

I32 AdlinkDispatch::ScanBus(I32 bus_no)
{
	return 0;
}

I32 AdlinkDispatch::ClearAxisAlarm(I32 axis_id)
{
	return I32();
}

I32 AdlinkDispatch::SetFieldBusParam(I32 card_id, I32 bus_no, I32 bus_param_no, I32 bus_param)
{
	return APS_set_field_bus_param(card_id, bus_no, bus_param_no, bus_param);
}

I32 AdlinkDispatch::StartFieldBus(I32 card_id, I32 bus_no, I32 start_axis_id)
{
	if (APS_start_field_bus(card_id, bus_no, start_axis_id))
		return StartFieldBusError;
	else
		return NoError;
}

I32 AdlinkDispatch::StopFieldBus(I32 card_id, I32 bus_no)
{
	if (APS_stop_field_bus(card_id, bus_no))
		return StopFieldBusError;
	else
		return NoError;
}

I32 AdlinkDispatch::SetAxisParam(I32 axis_id, F64 start_v, F64 max_v, F64 end_v, F64 acc, F64 dec)
{
	// 检查运动 IO 状态。例如 ORG，PEL，MEL，SVON，INP 等
	if (!((APS_motion_io_status(axis_id) >> MIO_SVON) & 1))
	{
		return SetParaError_MIO_SVON;
	}

	// 移动加速 / 减速速度模式
	//if (APS_set_axis_param_f(axis_id, PRA_SF, 0)) 
	//	return SetParaError_PRA_SF;
	// 开始速度
	if (APS_set_axis_param(axis_id, PRA_VS, (I32)start_v))
		;//return SetParaError_PRA_VS;
	// 终止速度
	if (APS_set_axis_param(axis_id, PRA_VE, (I32)end_v))
		;//return SetParaError_PRA_VE;
	// 最大速度
	if (APS_set_axis_param(axis_id, PRA_VM, (I32)max_v))
		;//return SetParaError_PRA_VM;
	// 加速度
	if (APS_set_axis_param(axis_id, PRA_ACC, (I32)acc))
		;//return SetParaError_PRA_ACC;
	// 减速度
	if (APS_set_axis_param(axis_id, PRA_DEC, (I32)dec))
		;//return SetParaError_PRA_DEC;

	return NoError;
}

I32 AdlinkDispatch::AxisOn(I32 axis_id)
{
	return APS_set_servo_on(axis_id, AxisEnable::Enable);
}

I32 AdlinkDispatch::AxisOff(I32 axis_id)
{
	return APS_set_servo_on(axis_id, AxisEnable::Disable);
}

I32 AdlinkDispatch::GetAxisStatus(I32 axis_id, AxisStatus status)
{
	I32 command_position;
	I32 feedback_position;
	I32 target_position;
	I32 error_position;
	I32 command_velocity;
	I32 feedback_velocity;
	I32 motion_status;
	I32 motion_io;

	// 指令位置
	if (APS_get_command(axis_id, &command_position))
		return GetAxisCommandPositionError;
	// 反馈位置
	if (APS_get_position(axis_id, &feedback_position))
		return GetAxisFeedbackPositionError;
	// 指令速度
	if (APS_get_command_velocity(axis_id, &command_velocity))
		return GetAxisCommandVelocityError;
	// 反馈速度
	if (APS_get_feedback_velocity(axis_id, &feedback_velocity))
		return GetAxisFeedbackVelocityError;
	// 错误位置
	if (APS_get_error_position(axis_id, &error_position))
		return GetAxisErrorPositionError;
	// 目标位置
	if (APS_get_target_position(axis_id, &target_position))
		return GetAxisTargetPositionError;

	status.motion_status = APS_motion_status(axis_id);
	status.motion_io = APS_motion_io_status(axis_id);
	status.command_position = command_position;
	status.feedback_position = feedback_position;
	status.command_velocity = command_velocity;
	status.feedback_velocity = feedback_velocity;
	status.error_position = error_position;
	status.target_position = target_position;

	return NoError;
}

I32 AdlinkDispatch::GetAxisPosition(I32 axis_id, F64 & positon)
{
	return APS_get_position_f(axis_id, &positon);;
}

I32 AdlinkDispatch::RelativeMove(I32 axis_id, I32 distance, I32 max_speed)
{
	if (!((APS_motion_io_status(axis_id) >> MIO_SVON) & 1))
	{
		return AxisStatusServeOffError;
	}
	return APS_relative_move(axis_id, distance, max_speed);
}

I32 AdlinkDispatch::AbsMove(I32 axis_id, I32 distance, I32 max_speed)
{
	if (!((APS_motion_io_status(axis_id) >> MIO_SVON) & 1))
	{
		return AxisStatusServeOffError;
	}
	return APS_absolute_move(axis_id, distance, max_speed);
}

I32 AdlinkDispatch::StopAxis(I32 axis_id, F64 stop_dec)
{
	if (APS_set_axis_param_f(axis_id, PRA_STP_DEC, stop_dec))
		return SetParaError_PRA_STP_DEC;
	return APS_stop_move(axis_id);
}

I32 AdlinkDispatch::EMGStop(I32 axis_id)
{
	return APS_emg_stop(axis_id);
}

I32 AdlinkDispatch::setAxisHomePara(I32 axis_id, I32 mode, I32 dir, I32 curve, I32 acc, I32 vm, I32 vo, I32 offset, I32 eza)
{
	// 归零模式设定
	if (APS_set_axis_param(axis_id, PRA_HOME_MODE, mode))
		;//return JError::ERR_SetMoveParam;
	// 归零方向 0: 正方向 1: 反方向
	if (APS_set_axis_param(axis_id, PRA_HOME_DIR, dir))
		;//return JError::ERR_SetMoveParam;
	// 归零运动加速/减速度模式 0: T-曲线 1: S-曲线
	if (APS_set_axis_param_f(axis_id, PRA_HOME_CURVE, curve))
		;//return JError::ERR_SetMoveParam;
	// 归零运动加/减速率 
	if (APS_set_axis_param(axis_id, PRA_HOME_ACC, acc))
		;//return JError::ERR_SetMoveParam;
	// 归零的最大速度
	if (APS_set_axis_param(axis_id, PRA_HOME_VM, vm))
		;//return JError::ERR_SetMoveParam;
	// 归零的最大速度 
	if (APS_set_axis_param(axis_id, PRA_HOME_VO, vo))
		;//return JError::ERR_SetMoveParam;
	if (APS_set_axis_param(axis_id, PRA_HOME_OFFSET, offset))
		;//return JError::ERR_SetMoveParam;
	// 启用EZ信号 0：禁用 1：启用
	if (APS_set_axis_param(axis_id, PRA_HOME_EZA, eza))
		;//return JError::ERR_SetMoveParam ;
	return 0;
}

I32 AdlinkDispatch::axisHome(I32 axis_id)
{
	if (!((APS_motion_io_status(axis_id) >> MIO_SVON) & 1))
	{
		return AxisStatusServeOffError;
	}
	return APS_home_move(axis_id); //Start homing 
}

bool AdlinkDispatch::IsAxisBusy(I32 axis_id)
{
	int motion_status = APS_motion_status(axis_id);
	if ((motion_status &  (0x01 << 0)) == 0)
	{
		return true;
	}

	if ((motion_status & (0x01 << 6)) != 0)
	{
		return true;
	}

	return false;
}

bool AdlinkDispatch::IsMoveDone(I32 axis_id)
{
	int motion_status = APS_motion_status(axis_id);
	if ((motion_status >> 5 & 1) == 1 && (motion_status >> 6 & 1) == 0)
	{
		return true;
	}
	return false;
}

I32 AdlinkDispatch::SetAxisHomePos(I32 axis_id)
{
	if (APS_set_position(axis_id, 0))
		return -1;
	if (APS_set_command(axis_id, 0))
		return -2;
	return 0;
}

bool AdlinkDispatch::GetAlarm(I32 axis_id)
{
	int io_status = APS_motion_io_status(axis_id);
	if ((io_status & (0x01 << 0)) != 0)
	{
		return true;
	}
	return false;
}

bool AdlinkDispatch::GetPEL(I32 axis_id)
{
	int io_status = APS_motion_io_status(axis_id);
	if ((io_status & (0x01 << 1)) != 0)
	{
		return true;
	}
	return false;
}

bool AdlinkDispatch::GetNEL(I32 axis_id)
{
	int io_status = APS_motion_io_status(axis_id);
	if ((io_status & (0x01 << 2)) != 0)
	{
		return true;
	}
	return false;
}

bool AdlinkDispatch::GetORG(I32 axis_id)
{
	int io_status = APS_motion_io_status(axis_id);
	if ((io_status & (0x01 << 3)) != 0)
	{
		return true;
	}
	return false;
}

bool AdlinkDispatch::GetSvon(I32 axis_id)
{
	int io_status = APS_motion_io_status(axis_id);
	if ((io_status & (0x01 << 0)) != 7)
	{
		return true;
	}
	return false;
}

I32 AdlinkDispatch::SetChannelDo(I32 card_id, I32 mod_no, I32 ch_no, I32 do_value)
{
	// 第二个参数0为现场总线索引（仅支持索引0）
	return APS_set_field_bus_d_channel_output(card_id, 0, mod_no, ch_no, do_value);
}

I32 AdlinkDispatch::GetChannelDo(I32 card_id, I32 mod_no, I32 ch_no, I32 & do_value)
{
	// 第二个参数0为现场总线索引（仅支持索引0）
	return APS_get_field_bus_d_channel_output(card_id, 0, mod_no, ch_no, &do_value);
}

I32 AdlinkDispatch::GetChannelDi(I32 card_id, I32 mod_no, I32 ch_no, I32 & di_value)
{
	// 第二个参数0为现场总线索引（仅支持索引0）
	return APS_get_field_bus_d_channel_input(card_id, 0, mod_no, ch_no, &di_value);
}
