#pragma once
#include "ADLink_Define.h"

class AdlinkDispatch
{
public:
	AdlinkDispatch();
	~AdlinkDispatch();

public:
	/*********************轴********************/
	/*
	 * @brief: 初始化板卡
	 * @param: card_num：卡号
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 InitCard(I32 card_num);
	/*
	 * @brief: 关闭板卡
	 * @param: 
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 CloseAllCard();
	/*
	 * @brief: 导入参数配置文件
	 * @param: file_name:文件名
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 LoadParamFile(const char * file_name);
	/*
	 * @brief: 扫描总线状态
	 * @param: bus_no:总线号
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 ScanBus(I32 bus_no);
	/*
	 * @brief: 清除轴错误
	 * @param: axis_id:轴号
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 ClearAxisAlarm(I32 axis_id);
	/*
	 * @brief: 设置现场总线相关参数
	 * @param: card_id：卡号；bus_no:总线端口号；bus_param_no：现场总线参数编号;bus_param:现场总线参数数据
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 SetFieldBusParam(I32 card_id, I32 bus_no, I32 bus_param_no, I32 bus_param);
	/*
	 * @brief: 开启网络总线
	 * @param: card_id：卡号；bus_no:总线端口号；start_axis_id：开始轴编号
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 StartFieldBus(I32 card_id, I32 bus_no, I32 start_axis_id);
	/*
	 * @brief: 关闭网络总线
	 * @param: card_id：卡号；bus_no:总线号
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 StopFieldBus(I32 card_id, I32 bus_no);
	/*
	 * @brief: 设置轴参数
	 * @param: axis_id:轴号；start_v：开始速度；max_v：最大速度；end_v：结束速度；acc：加速度；dec：减速度
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 SetAxisParam(I32 axis_id, F64 start_v, F64 max_v, F64 end_v, F64 acc, F64 dec);
	/*
	 * @brief: 轴使能
	 * @param: axis_id:轴号
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 AxisOn(I32 axis_id);
	/*
	 * @brief: 轴失能
	 * @param: axis_id:轴号
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 AxisOff(I32 axis_id);
	/*
	 * @brief: 轴状态
	 * @param: axis_id:轴号
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 GetAxisStatus(I32 axis_id, AxisStatus status);
	/*
	 * @brief: 获得轴位置
	 * @param: axis_id:轴号; positon:轴位置脉冲数
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 GetAxisPosition(I32 axis_id, F64 &positon);
	/*
	 * @brief: 轴走相对位置运动
	 * @param: axis_id:轴号; distance:相对距离; max_speed:最大运动速度
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 RelativeMove(I32 axis_id, I32 distance, I32 max_speed);
	/*
	 * @brief: 等待轴走相对位置运动到位
	 * @param: axis_name:轴名; distance:相对距离
	 * @return: 0代表无错误,非0表示错误码
	 */
	//I32 WaitAxisRelativeMove(I8 axis_name, I32 distance);
	/*
	 * @brief: 轴走绝对位置运动
	 * @param: axis_id:轴号; distance:相对距离; max_speed:最大运动速度
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 AbsMove(I32 axis_id, I32 distance, I32 max_speed);
	/*
	 * @brief: 等待轴走绝对位置运动到位
	 * @param: axis_name:轴名; distance:相对距离
	 * @return: 0代表无错误,非0表示错误码
	 */
	//I32 WaitAxisAbsMove(I8 axis_name, I32 distance);
	/*
	 * @brief: 轴停止运动
	 * @param: axis_id:轴号; stop_dec:停止减速度
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 StopAxis(I32 axis_id, F64 stop_dec);
	/*
	 * @brief: 轴紧急停止运动
	 * @param: axis_id:轴号
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 EMGStop(I32 axis_id);
	/*
	 * @brief: 轴回零运动
	 * @param: axis_id:轴号；mode：模式；dir：方向；curve：曲线速度；acc：加速度；vm：最大速度；vo：爬行速度；offset：偏移；eza：Z相
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 setAxisHomePara(I32 axis_id, I32 mode, I32 dir, I32 curve, I32 acc, I32 vm, I32 vo, I32 offset, I32 eza);
	/*
	 * @brief: 轴回零运动
	 * @param: axis_id:轴号；slave_id：从地址
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 axisHome(I32 axis_id);
	/*
	 * @brief: 轴走绝对位置运动
	 * @param: axis_id:轴号
	 * @return: 0代表无错误,非0表示错误码
	 */
	//I32 WaitAxisHome(I32 axis_id);
	/*
	 * @brief: 判断轴是否繁忙状态
	 * @param: axis_id:轴号
	 * @return: true表示繁忙
	 */
	bool IsAxisBusy(I32 axis_id);
	/*
	 * @brief: 判断轴运动是否完成
	 * @param: axis_id:轴号
	 * @return: true表示已完成
	 */
	bool IsMoveDone(I32 axis_id);
	/*
	 * @brief: 设置零点位置(因暂无回零使用，手动控制并设定零点位置)
	 * @param: axis_id:轴号
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 SetAxisHomePos(I32 axis_id);
	/*
	 * @brief: 获得轴报警
	 * @param: axis_id:轴号
	 * @return: 运动 IO 状态的值
	 */
	bool GetAlarm(I32 axis_id);
	/*
	 * @brief: 获得负极限
	 * @param: axis_id:轴号
	 * @return: 运动 IO 状态的值
	 */
	bool GetPEL(I32 axis_id);
	/*
	 * @brief: 获得正极限
	 * @param: axis_id:轴号
	 * @return: 运动 IO 状态的值
	 */
	bool GetNEL(I32 axis_id);
	/*
	 * @brief: 获得原点信号
	 * @param: axis_id:轴号
	 * @return: 运动 IO 状态的值
	 */
	bool GetORG(I32 axis_id);
	/*
	 * @brief: 获得使能状态
	 * @param: axis_id:轴号
	 * @return: 运动 IO 状态的值
	 */
	bool GetSvon(I32 axis_id);

	/*********************IO********************/
	/*
	 * @brief: 设置IO输出
	 * @param: card_id：卡号；do_value:数字输出的值；mod_no：从站设备的索引；ch_no：数字输出通道的索引
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 SetChannelDo(I32 card_id, I32 mod_no, I32 ch_no, I32 do_value);
	/*
	 * @brief: 获得IO输出
	 * @param: card_id：卡号；do_value:数字输出的值；mod_no：从站设备的索引；ch_no：数字输出通道的索引
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 GetChannelDo(I32 card_id, I32 mod_no, I32 ch_no, I32 &do_value);
	/*
	 * @brief: 设置IO输入
	 * @param: card_id：卡号；do_value:数字输入的值；mod_no：从站设备的索引；ch_no：数字输出通道的索引
	 * @return: 0代表无错误,非0表示错误码
	 */
	I32 GetChannelDi(I32 card_id, I32 mod_no, I32 ch_no, I32 &di_value);

private:
	I32 m_Card_No = 0;
	I32 m_BUS_No = 0;
};

