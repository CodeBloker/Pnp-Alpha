#pragma once
#include "Common/JSerialPort.h"
#include "SimpleSerialPort.h"
#include "WzSerialPort.h"

struct LightComSetting
{
	std::string portName = "COM6";
	ULONG ulBaudRate = 19200;
	UCHAR ucByteSize = 8;
	UCHAR ucParity = 0;
	UCHAR ucStopBit = 1;
	ULONG ulHandshake = 1;
}; 

struct TempComSetting
{
	std::string portName = "\\\\.\\COM10";
	ULONG ulBaudRate = 9600;
	UCHAR ucByteSize = 8;
	UCHAR ucParity = 0;
	UCHAR ucStopBit = 0;
	ULONG ulHandshake = 1;
};

struct Temp2ComSetting
{
	std::string portName = "COM8";
	ULONG ulBaudRate = 9600;
	UCHAR ucByteSize = 8;
	UCHAR ucParity = 0;
	UCHAR ucStopBit = 0;
	ULONG ulHandshake = 1;
};

struct HeighComSetting1
{
	std::string portName = "COM9";
	ULONG ulBaudRate = 9600;
	UCHAR ucByteSize = 8;
	UCHAR ucParity = 0;
	UCHAR ucStopBit = 1;
	ULONG ulHandshake = 1;
};

struct HeighComSetting2
{
	std::string portName = "\\\\.\\COM12";
	ULONG ulBaudRate = 9600;
	UCHAR ucByteSize = 8;
	UCHAR ucParity = 0;
	UCHAR ucStopBit = 1;
	ULONG ulHandshake = 1;
};

struct HeighComSetting3
{
	std::string portName = "\\\\.\\COM13";
	ULONG ulBaudRate = 9600;
	UCHAR ucByteSize = 8;
	UCHAR ucParity = 0;
	UCHAR ucStopBit = 1;
	ULONG ulHandshake = 1;
};

struct KeyenceHeighComSetting
{
	//std::string portName = "\\\\.\\COM11";
	std::string portName = "COM9";
	ULONG ulBaudRate = 9600;
	UCHAR ucByteSize = 8;
	UCHAR ucParity = 0;
	UCHAR ucStopBit = 1;
	ULONG ulHandshake = 1;
};

class SerialControl
{
public:
	SerialControl();
	~SerialControl();

	static SerialControl*& GetInstance();

	// �򿪴���
	bool openSerialPort(std::string port_name);
	// �رմ���
	bool CloseSerialPort(std::string port_name);

	//************Alpha��Դ************//
	// ��/�رչ�Դ������
	bool OpenLightSource();
	bool CloseLightSource();
	// ��Դ����״̬
	bool IsLightSourceOpen();
	// �����1���������Դ
	bool OpenHikCamera1Light();
	// �����2���������Դ
	bool OpenHikCamera2Light();
	// �����й�Դ
	bool OpenAllLight();
	// �ر����й�Դ
	bool CloseAllLight();

	//************�¶ȴ�����************//
	// ��/�ر��¶ȿ�����
	bool OpenTempSensor();
	bool CloseTempSensor();
	// �¶ȴ���������״̬
	bool IsTempSensorOpen();
	// ��ȡ��ǰ�¶�
	std::string ReadTemp();
	// ��/�ر��¶ȿ�����2
	bool OpenTempSensor2();
	bool CloseTempSensor2();
	// �¶ȴ���������״̬2
	bool IsTempSensorOpen2();
	// ��ȡ��ǰ�¶�2
	std::string ReadTemp2();

	//************�߶ȴ�����************//
	// ��/�رո߶ȴ�����
	bool OpenHeighSensor1();
	bool CloseHeighSensor1();
	// �߶ȴ���������״̬
	bool IsHeighSensorOpen();
	// ��ȡ��ǰ�߶�ֵ(OMRAON1)
	std::string ReadHeigh1();
	// ��/�رո߶ȴ�����
	bool OpenHeighSensor2();
	bool CloseHeighSensor2();
	// ��ȡ��ǰ�߶�ֵ(OMRAON2)
	std::string ReadHeigh2();
	// ��/�رո߶ȴ�����
	bool OpenHeighSensor3();
	bool CloseHeighSensor3();
	// ��ȡ��ǰ�߶�ֵ(OMRAON3)
	std::string ReadHeigh3();

	//************����ʿ�߶ȴ�����************//
	// ��/�رո߶ȴ�����
	bool OpenKeyenceHeighSensor();
	bool CloseKeyenceHeighSensor();
	// ��ȡ��ǰ�߶�ֵ
	std::string ReadKeyenceHeigh();

private:
	std::string ParseTempSerialRecv(char* buf, int len);
	std::string ParseTemp2SerialRecv(char* buf, int len);
	std::string ParseHeighSerialRecv(const std::string& buf);
	std::string ParseKeyenceHeighSerialRecv(const std::string& buf);

private:
	JSerialPort mLightSerial;

	SimpleSerialPort mKeyenceHeighSerial;
	SimpleSerialPort mHeighSerial1;
	SimpleSerialPort mHeighSerial2;
	SimpleSerialPort mHeighSerial3;
	SimpleSerialPort mTempSerial;
	SimpleSerialPort mTempSerial2;

	WzSerialPort m_port;

	inline static SerialControl* m_SingleInstance = nullptr;
	inline static std::mutex m_Mutex;
};

