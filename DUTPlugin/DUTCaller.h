#pragma once

#include "PluginBase/JupCaller.h"
#include "DutController.h"

/*
	该类是平台调用测试项的接口，若正确定义能在平台的测试流程编辑器上被使用，并加载到测试项中
*/
class DUTCaller : public JupCaller
{
public:
	DUTCaller();
	~DUTCaller();

	/*
		在该函数做特定的初始化操作，由平台调用该函数

		示例：默认调用父类接口的实现JupCaller::Initialize();
		根据当前插件的实际需要选择添加内容
	*/
	int Initialize() override;

	/*
		统一在该函数内注册所有测试项方法的函数

		示例：Plugin_Method_Add(DUTCaller, Demo_msleep100);
		其中DemoTestCaller为当前类的类名，Demo_msleep100为需要注册的函数名
	*/
	int RegisterMethod() override;

private:
	/*
		在此添加需要测试项方法的函数，函数类型必须为int (T::*)(JupData&)
		下列函数需要在RegisterMethod()中注册才能在平台上使用
	*/
	int Demo_msleep100(JupData& data);

	// 初始化Canyon
	int InitCanyon(JupData& data);
	// DUT POWER ON
	int DutPowerOn(JupData& data);
	// DUT POWER OFF
	int DutPowerOff(JupData& data);
	// 设置DOT参数
	int DutSetDotPara(JupData& data);
	// 设置Flood参数
	int DutSetFloodPara(JupData& data);

private:
	DutController* m_dut;
	int m_socketIndex = 3;
};
