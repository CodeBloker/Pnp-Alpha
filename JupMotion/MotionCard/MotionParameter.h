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

// ����������
enum CardConfig
{
	CardNo = 0,
	BusNo = 0,
	BusParamNo = 1,
	BusParam = 2,
	StartAxisId = 0
};

// ��վ�豸�������� ����0��ʼ��
enum IO_ModNo
{
	No0 = 3,
	No1
};

// ���������ֵ��
enum IO_Status
{
	OFF = 0,
	ON
};

// �������ͨ���������� ����0��ʼ��
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
	// ��db�������
	bool LoadParameterFromDB();
	// ��db���������
	bool LoadAxisInfos();
	// ��db�����λ����
	bool LoadPositionInfos();
	// ��db����IO�������
	bool LoadOutputInfos();
	// ��db����IO�������
	bool LoadInputInfos();

	// ����/����������db
	bool UpdateAxisInfos(MotionAxis* axis_update_info);
	// ��dbɾ��������
	bool DeleteAxisInfos(const std::string& axis_name);
	// ����/��ӵ�λ������db
	bool UpdatePosInfos(AxisPosition* pos_update_info);
	// ��dbɾ����λ����
	bool DeletePosInfos(const std::string& pos_name, bool update_pos_infos = true);
	// ����/���IO������db
	bool UpdateIOInfos(MotionIO* io_update_info, bool is_input_io);
	// ��dbɾ��IO����
	bool DeleteIOInfos(const std::string& io_name, bool is_input_io);

public:
	// ������Ƿ����
	bool IsContainAxis(const std::string& axis_name);
	// ��ȡ��λ��Ϣ
	AxisPosition* GetAxisPosInfo(const std::string& axis_name, const std::string& pos_name);
	// ��ȡ�������Ϣ
	MotionAxis* GetAxisParam(const std::string& axis_name);
	// ���IO������Ϣ (is_en������������Ӣ����)
	MotionIO* GetInputIOInfo(const std::string& io_name, bool is_en = true);
	// ��������IO�Ƿ�ʹ��״̬����������IO�źţ�
	void UpdataInputIOUseStatus(const std::string& io_name, bool is_use);
	// ���IO�����Ϣ (is_en������������Ӣ����)
	MotionIO* GetOutputIOInfo(const std::string& io_name, bool is_en = true);

	// ��ȡ��λ��Ϣ�б�
	std::vector<AxisPosition*> GetAxisPosListInfo(const std::string& axis_name);
	// ��ȡ�������Ϣ�б�
	std::vector<std::string> GetAxisNameList();
	// ��ȡIO������Ϣ�б�
	IOHash GetInputIOList();
	// ��ȡIO�����Ϣ�б�
	IOHash GetOutputIOList();

private:
	sqlite3* m_db = NULL;					//���ݿ����
	AxisHash m_axises;						//�����õ���Ĳ�����Ϣ
	PosHash  m_poses;						//�����õ����λ����Ϣ
	IOHash   m_inputs;						//IO���õ�IO��������Ϣ
	IOHash   m_outputs;						//IO���õ�IO�������Ϣ

	PosList  m_posesList;					//��λ���б�
	std::vector<std::string> m_axisList;	//�����б�
};

