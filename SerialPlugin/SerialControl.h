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

	// 打开串口
	bool openSerialPort(std::string port_name);
	// 关闭串口
	bool CloseSerialPort(std::string port_name);

	//************Alpha光源************//
	// 打开/关闭光源控制器
	bool OpenLightSource();
	bool CloseLightSource();
	// 光源连接状态
	bool IsLightSourceOpen();
	// 打开相机1拍照所需光源
	bool OpenHikCamera1Light();
	// 打开相机2拍照所需光源
	bool OpenHikCamera2Light();
	// 打开所有光源
	bool OpenAllLight();
	// 关闭所有光源
	bool CloseAllLight();

	//************温度传感器************//
	// 打开/关闭温度控制器
	bool OpenTempSensor();
	bool CloseTempSensor();
	// 温度传感器连接状态
	bool IsTempSensorOpen();
	// 获取当前温度
	std::string ReadTemp();
	// 打开/关闭温度控制器2
	bool OpenTempSensor2();
	bool CloseTempSensor2();
	// 温度传感器连接状态2
	bool IsTempSensorOpen2();
	// 获取当前温度2
	std::string ReadTemp2();

	//************高度传感器************//
	// 打开/关闭高度传感器
	bool OpenHeighSensor1();
	bool CloseHeighSensor1();
	// 高度传感器连接状态
	bool IsHeighSensorOpen();
	// 获取当前高度值(OMRAON1)
	std::string ReadHeigh1();
	// 打开/关闭高度传感器
	bool OpenHeighSensor2();
	bool CloseHeighSensor2();
	// 获取当前高度值(OMRAON2)
	std::string ReadHeigh2();
	// 打开/关闭高度传感器
	bool OpenHeighSensor3();
	bool CloseHeighSensor3();
	// 获取当前高度值(OMRAON3)
	std::string ReadHeigh3();

	//************基恩士高度传感器************//
	// 打开/关闭高度传感器
	bool OpenKeyenceHeighSensor();
	bool CloseKeyenceHeighSensor();
	// 获取当前高度值
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

