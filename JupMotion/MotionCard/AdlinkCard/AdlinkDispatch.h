#pragma once
#include "ADLink_Define.h"

class AdlinkDispatch
{
public:
	AdlinkDispatch();
	~AdlinkDispatch();

public:
	/*********************��********************/
	/*
	 * @brief: ��ʼ���忨
	 * @param: card_num������
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 InitCard(I32 card_num);
	/*
	 * @brief: �رհ忨
	 * @param: 
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 CloseAllCard();
	/*
	 * @brief: ������������ļ�
	 * @param: file_name:�ļ���
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 LoadParamFile(const char * file_name);
	/*
	 * @brief: ɨ������״̬
	 * @param: bus_no:���ߺ�
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 ScanBus(I32 bus_no);
	/*
	 * @brief: ��������
	 * @param: axis_id:���
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 ClearAxisAlarm(I32 axis_id);
	/*
	 * @brief: �����ֳ�������ز���
	 * @param: card_id�����ţ�bus_no:���߶˿ںţ�bus_param_no���ֳ����߲������;bus_param:�ֳ����߲�������
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 SetFieldBusParam(I32 card_id, I32 bus_no, I32 bus_param_no, I32 bus_param);
	/*
	 * @brief: ������������
	 * @param: card_id�����ţ�bus_no:���߶˿ںţ�start_axis_id����ʼ����
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 StartFieldBus(I32 card_id, I32 bus_no, I32 start_axis_id);
	/*
	 * @brief: �ر���������
	 * @param: card_id�����ţ�bus_no:���ߺ�
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 StopFieldBus(I32 card_id, I32 bus_no);
	/*
	 * @brief: ���������
	 * @param: axis_id:��ţ�start_v����ʼ�ٶȣ�max_v������ٶȣ�end_v�������ٶȣ�acc�����ٶȣ�dec�����ٶ�
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 SetAxisParam(I32 axis_id, F64 start_v, F64 max_v, F64 end_v, F64 acc, F64 dec);
	/*
	 * @brief: ��ʹ��
	 * @param: axis_id:���
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 AxisOn(I32 axis_id);
	/*
	 * @brief: ��ʧ��
	 * @param: axis_id:���
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 AxisOff(I32 axis_id);
	/*
	 * @brief: ��״̬
	 * @param: axis_id:���
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 GetAxisStatus(I32 axis_id, AxisStatus status);
	/*
	 * @brief: �����λ��
	 * @param: axis_id:���; positon:��λ��������
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 GetAxisPosition(I32 axis_id, F64 &positon);
	/*
	 * @brief: �������λ���˶�
	 * @param: axis_id:���; distance:��Ծ���; max_speed:����˶��ٶ�
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 RelativeMove(I32 axis_id, I32 distance, I32 max_speed);
	/*
	 * @brief: �ȴ��������λ���˶���λ
	 * @param: axis_name:����; distance:��Ծ���
	 * @return: 0�����޴���,��0��ʾ������
	 */
	//I32 WaitAxisRelativeMove(I8 axis_name, I32 distance);
	/*
	 * @brief: ���߾���λ���˶�
	 * @param: axis_id:���; distance:��Ծ���; max_speed:����˶��ٶ�
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 AbsMove(I32 axis_id, I32 distance, I32 max_speed);
	/*
	 * @brief: �ȴ����߾���λ���˶���λ
	 * @param: axis_name:����; distance:��Ծ���
	 * @return: 0�����޴���,��0��ʾ������
	 */
	//I32 WaitAxisAbsMove(I8 axis_name, I32 distance);
	/*
	 * @brief: ��ֹͣ�˶�
	 * @param: axis_id:���; stop_dec:ֹͣ���ٶ�
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 StopAxis(I32 axis_id, F64 stop_dec);
	/*
	 * @brief: �����ֹͣ�˶�
	 * @param: axis_id:���
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 EMGStop(I32 axis_id);
	/*
	 * @brief: ������˶�
	 * @param: axis_id:��ţ�mode��ģʽ��dir������curve�������ٶȣ�acc�����ٶȣ�vm������ٶȣ�vo�������ٶȣ�offset��ƫ�ƣ�eza��Z��
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 setAxisHomePara(I32 axis_id, I32 mode, I32 dir, I32 curve, I32 acc, I32 vm, I32 vo, I32 offset, I32 eza);
	/*
	 * @brief: ������˶�
	 * @param: axis_id:��ţ�slave_id���ӵ�ַ
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 axisHome(I32 axis_id);
	/*
	 * @brief: ���߾���λ���˶�
	 * @param: axis_id:���
	 * @return: 0�����޴���,��0��ʾ������
	 */
	//I32 WaitAxisHome(I32 axis_id);
	/*
	 * @brief: �ж����Ƿ�æ״̬
	 * @param: axis_id:���
	 * @return: true��ʾ��æ
	 */
	bool IsAxisBusy(I32 axis_id);
	/*
	 * @brief: �ж����˶��Ƿ����
	 * @param: axis_id:���
	 * @return: true��ʾ�����
	 */
	bool IsMoveDone(I32 axis_id);
	/*
	 * @brief: �������λ��(�����޻���ʹ�ã��ֶ����Ʋ��趨���λ��)
	 * @param: axis_id:���
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 SetAxisHomePos(I32 axis_id);
	/*
	 * @brief: ����ᱨ��
	 * @param: axis_id:���
	 * @return: �˶� IO ״̬��ֵ
	 */
	bool GetAlarm(I32 axis_id);
	/*
	 * @brief: ��ø�����
	 * @param: axis_id:���
	 * @return: �˶� IO ״̬��ֵ
	 */
	bool GetPEL(I32 axis_id);
	/*
	 * @brief: ���������
	 * @param: axis_id:���
	 * @return: �˶� IO ״̬��ֵ
	 */
	bool GetNEL(I32 axis_id);
	/*
	 * @brief: ���ԭ���ź�
	 * @param: axis_id:���
	 * @return: �˶� IO ״̬��ֵ
	 */
	bool GetORG(I32 axis_id);
	/*
	 * @brief: ���ʹ��״̬
	 * @param: axis_id:���
	 * @return: �˶� IO ״̬��ֵ
	 */
	bool GetSvon(I32 axis_id);

	/*********************IO********************/
	/*
	 * @brief: ����IO���
	 * @param: card_id�����ţ�do_value:���������ֵ��mod_no����վ�豸��������ch_no���������ͨ��������
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 SetChannelDo(I32 card_id, I32 mod_no, I32 ch_no, I32 do_value);
	/*
	 * @brief: ���IO���
	 * @param: card_id�����ţ�do_value:���������ֵ��mod_no����վ�豸��������ch_no���������ͨ��������
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 GetChannelDo(I32 card_id, I32 mod_no, I32 ch_no, I32 &do_value);
	/*
	 * @brief: ����IO����
	 * @param: card_id�����ţ�do_value:���������ֵ��mod_no����վ�豸��������ch_no���������ͨ��������
	 * @return: 0�����޴���,��0��ʾ������
	 */
	I32 GetChannelDi(I32 card_id, I32 mod_no, I32 ch_no, I32 &di_value);

private:
	I32 m_Card_No = 0;
	I32 m_BUS_No = 0;
};

