#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "json/json.h"
#include "Common/JupCommon.h"
#include "Common/JIniSettings.h"
#include "Base/JupGlobal.h"
#include "JError.h"
#include "sqlite3.h"
#include "CardAxis.h"
#include "CardIO.h"

#pragma execution_character_set("utf-8")

#pragma comment (lib, "APS168x64.lib")

using AxisHash = std::map<std::string, MotionAxis*>;
using PosHash = std::map<std::string, std::map<std::string, AxisPosition*>>;
using PosList = std::map<std::string, std::vector<AxisPosition*>>;
using IOHash = std::map<std::string, MotionIO*>;

// 卡参数定义
enum CardConfig
{
	CardNo = 0,
	BusNo = 0,
	BusParamNo = 1,
	BusParam = 2,
	StartAxisId = 0
};

// 从站设备的索引。 （从0开始）
enum IO_ModNo
{
	No0 = 3,
	No1
};

// 数字输出的值。
enum IO_Status
{
	OFF = 0,
	ON
};

// 数字输出通道的索引。 （从0开始）
enum IO_Out_Channel
{
	D00 = 0,
	//D01,
	SocketCoverUp,
	SocketCoverOut
};

class MotionParameter
{
public:
	MotionParameter();
	~MotionParameter();

public:
	// 从db导入参数
	bool LoadParameterFromDB();
	// 从db导入轴参数
	bool LoadAxisInfos();
	// 从db导入点位参数
	bool LoadPositionInfos();
	// 从db导入IO输出参数
	bool LoadOutputInfos();
	// 从db导入IO输入参数
	bool LoadInputInfos();

	// 更新/添加轴参数到db
	bool UpdateAxisInfos(MotionAxis* axis_update_info);
	// 从db删除轴配置
	bool DeleteAxisInfos(const std::string& axis_name);
	// 更新/添加点位参数到db
	bool UpdatePosInfos(AxisPosition* pos_update_info);
	// 从db删除点位配置
	bool DeletePosInfos(const std::string& pos_name, bool update_pos_infos = true);
	// 更新/添加IO参数到db
	bool UpdateIOInfos(MotionIO* io_update_info, bool is_input_io);
	// 从db删除IO配置
	bool DeleteIOInfos(const std::string& io_name, bool is_input_io);

public:
	// 检查轴是否存在
	bool IsContainAxis(const std::string& axis_name);
	// 获取点位信息
	AxisPosition* GetAxisPosInfo(const std::string& axis_name, const std::string& pos_name);
	// 获取轴参数信息
	MotionAxis* GetAxisParam(const std::string& axis_name);
	// 获得IO输入信息 (is_en区分中文名和英文名)
	MotionIO* GetInputIOInfo(const std::string& io_name, bool is_en = true);
	// 更新输入IO是否使用状态（用于屏蔽IO信号）
	void UpdataInputIOUseStatus(const std::string& io_name, bool is_use);
	// 获得IO输出信息 (is_en区分中文名和英文名)
	MotionIO* GetOutputIOInfo(const std::string& io_name, bool is_en = true);

	// 获取点位信息列表
	std::vector<AxisPosition*> GetAxisPosListInfo(const std::string& axis_name);
	// 获取轴参数信息列表
	std::vector<std::string> GetAxisNameList();
	// 获取IO输入信息列表
	IOHash GetInputIOList();
	// 获取IO输出信息列表
	IOHash GetOutputIOList();

private:
	sqlite3* m_db = NULL;					//数据库对象
	AxisHash m_axises;						//轴名得到轴的参数信息
	PosHash  m_poses;						//轴名得到轴的位置信息
	IOHash   m_inputs;						//IO名得到IO的输入信息
	IOHash   m_outputs;						//IO名得到IO的输出信息

	PosList  m_posesList;					//轴位置列表
	std::vector<std::string> m_axisList;	//轴名列表
};

