#pragma once
#include "AdlinkCard/AdlinkDispatch.h"
#include "MotionParameter.h"

class AdlinkController :public AdlinkDispatch
{
public:
	AdlinkController();
	~AdlinkController();

	// ��ʼ���忨
	int InitAdlinkCard();
	// �Ͽ��忨
	int CloseAdlinkCard();
	// �忨��ʼ��״̬
	bool IsCardInit();
	// ��ʹ��
	int AxisServoOn(std::string axisName);
	// ��ʧ��
	int AxisServoOff(std::string axisName);
	// �˶����������꣨�����˶���
	int AxisAbsMove(const std::string& axisName, double distance, double dbOffset = 0.0, double ratio = 100);
	// �ȴ��˶�����������
	int WaitAxisAbsMove(const std::string& axisName, double distance);
	// �ƶ���Ԥ��λ��
	int AxisAbsMoveToPos(const std::string& axisName, const std::string& strPositionName, double dbOffset = 0.0);
	// �˶���������꣨����˶���
	int AxisMoveDistance(const std::string& axisName, double distance);
	int WaitAxisMoveDistance(const std::string& axisName, double distance);
	// ֹͣ�ƶ�
	int	StopAxisMove(const std::string& axisName);
	// ��ͣ ֹͣ�ƶ�
	int EMG_StopAxisMove(const std::string& axisName);
	// ���ú����еȴ�ֱ�ӷ���
	void AxisStopWait();
	// ��ԭ
	int AxisHome(const std::string& axisName);
	// �ȴ���ԭ
	int WaitAxisHome(const std::string& axisName);
	// ��ȡmm
	double GetCurrentPos(const std::string& axisName);
	// ��״̬������/������λ/ԭ���ź�/ʹ�ܣ�
	bool IsAlarm(const std::string& axisName);
	bool IsPEL(const std::string& axisName);
	bool IsNEL(const std::string& axisName);
	bool IsORG(const std::string& axisName);
	bool IsSvon(const std::string& axisName);

	//����IO����
	int IO_SetOutput(int card_num, int mod_num, int bit_num, int on_off);
	int IO_GetOutput(int card_num, int mod_num, int bit_num);
	int IO_GetInput(int card_num, int mod_num, int bit_num);

	// ������غ���
	// λ�ñȽ�ʵʱλ������(ֻ���ڻ�ԭ�Ժ��ʱ��ʹ��һ��)
	int ResetTriggerPos(int axis_id, double pos);
	int ResetTriggerPos(const std::string& axisName);
	// ���÷�������������
	int SetTriggerListPos(std::string axisName, EnumMotorTriggerMode trigger_mode, std::vector<double> pos_list);
	// ��д������
	int WriteReadSDO(int axis_slave, UINT16 ODIndex, UINT16 ODSubIndex, INT32 CommdData, UINT32 DataLen, INT32& ReData, bool IsWrite = true, bool IsRead = true, int time_out = 3000);
	int WriteReadPDO(UINT16 ByteOffset, UINT16 Size, UINT& Value, bool IsWrite = true, bool IsRead = true);

	// ����
	MotionParameter* GetMotionParameter();

private:
	MotionParameter* m_pMotionParameter;
	bool m_bSetStopWait = false;
	// ����˶���¼��ʼλ��
	double dbBeginPos;
	// �忨��ʼ��״̬
	bool m_IsCardInit = false;

public:
	// PNPУ׼ʱ�õ����˶�����
	// У׼�˶���������꣨����˶���
	int AxisMoveDistance(const std::string& axisName, double distance, double maxVel, double accVel, double decVel);
};

