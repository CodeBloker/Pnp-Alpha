#pragma once

#include "PluginBase/JupCaller.h"
#include "TcpController.h"

/*
	该类是平台调用测试项的接口，若正确定义能在平台的测试流程编辑器上被使用，并加载到测试项中
*/
class TcpPluginCaller : public JupCaller
{
public:
	TcpPluginCaller();
	~TcpPluginCaller();

	/*
		在该函数做特定的初始化操作，由平台调用该函数

		示例：默认调用父类接口的实现JupCaller::Initialize();
		根据当前插件的实际需要选择添加内容
	*/
	int Initialize() override;

	/*
		统一在该函数内注册所有测试项方法的函数

		示例：Plugin_Method_Add(TcpPluginCaller, Demo_msleep100);
		其中TcpPluginCaller为当前类的类名，Demo_msleep100为需要注册的函数名
	*/
	int RegisterMethod() override;

private:
	/*
		在此添加需要测试项方法的函数，函数类型必须为int (T::*)(JupData&)
		下列函数需要在RegisterMethod()中注册才能在平台上使用
	*/
	int Demo_msleep100(JupData& data);

	// ACL获取俯仰值
	int GetACLValues(JupData& data);

	// Confocal Sensor获得值
	int GetConfocalSensorValue1(JupData& data);
	int GetConfocalSensorValue2(JupData& data);

private:
	TcpController* m_tcp;
};
