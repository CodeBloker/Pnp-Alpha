#pragma once

#include "PluginBase/JupCaller.h"
#include "SerialControl.h"

/*
	该类是平台调用测试项的接口，若正确定义能在平台的测试流程编辑器上被使用，并加载到测试项中
*/
class SerialCaller : public JupCaller
{
public:
	SerialCaller();
	~SerialCaller();

	/*
		在该函数做特定的初始化操作，由平台调用该函数

		示例：默认调用父类接口的实现JupCaller::Initialize();
		根据当前插件的实际需要选择添加内容
	*/
	int Initialize() override;

	/*
		统一在该函数内注册所有测试项方法的函数

		示例：Plugin_Method_Add(SerialCaller, Demo_msleep100);
		其中DemoTestCaller为当前类的类名，Demo_msleep100为需要注册的函数名
	*/
	int RegisterMethod() override;

private:
	/*
		在此添加需要测试项方法的函数，函数类型必须为int (T::*)(JupData&)
		下列函数需要在RegisterMethod()中注册才能在平台上使用
	*/
	int Demo_msleep100(JupData& data);

	//**************Alpha光源控制器*****************//
	// 打开串口
	int OpenAlphaLightSource(JupData& data);
	// 关闭串口
	int CloseAlphaLightSource(JupData& data);
	// 打开所有光源
	int OpenAllAlphaLightSource(JupData& data);
	// 关闭所有光源
	int CloseAllAlphaLightSource(JupData& data);

	//****************温度传感器*******************//
	// 打开串口
	int OpenSensorTemperature(JupData& data);
	// 关闭串口
	int CloseSensorTemperature(JupData& data);
	// 获取温度
	int GetSensorTemperature(JupData& data);

	//****************高度传感器*******************//
	// 打开串口
	int OpenSensorHeigh(JupData& data);
	// 关闭串口
	int CloseSensorHeigh(JupData& data);
	// 获取高度1(OMRON)
	int GetOmronSensor1HeighValue(JupData& data);
	// 获取高度2(OMRON)
	int GetOmronSensor2HeighValue(JupData& data);
	// 获取高度3(OMRON)
	int GetOmronSensor3HeighValue(JupData& data);
	// 获取高度(KEYENCE)
	int GetKeyenceSensorHeighValue(JupData& data);

private:
	SerialControl* m_Serial;
};
