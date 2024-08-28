#pragma once

#include "PluginBase/JupCaller.h"
#include "DvpCamera_Manage.h"

/*
	该类是平台调用测试项的接口，若正确定义能在平台的测试流程编辑器上被使用，并加载到测试项中
*/
class DvpCaller : public JupCaller
{
public:
	DvpCaller();
	~DvpCaller();

	/*
		在该函数做特定的初始化操作，由平台调用该函数

		示例：默认调用父类接口的实现JupCaller::Initialize();
		根据当前插件的实际需要选择添加内容
	*/
	int Initialize() override;

	/*
		统一在该函数内注册所有测试项方法的函数

		示例：Plugin_Method_Add(HIKCaller, Demo_msleep100);
		其中DemoTestCaller为当前类的类名，Demo_msleep100为需要注册的函数名
	*/
	int RegisterMethod() override;

private:
	/*
		在此添加需要测试项方法的函数，函数类型必须为int (T::*)(JupData&)
		下列函数需要在RegisterMethod()中注册才能在平台上使用
	*/
	int Demo_msleep100(JupData& data);

	// pnp Doe
	// 重置相机参数（关闭采集等）
	int LoadPnpDoeResetDatas(JupData& data);
	// 设置上相机参数（触发模式，触发源，曝光参数等）
	int SetTopCameraHwParameter(JupData& data);
	// 设置上下机参数（触发模式，触发源，曝光参数等）
	int SetDownCameraHwParameter(JupData& data);
	// 开启采集线程，等待触发信号获得图片
	int StartCaptureTopImageThread(JupData& data);
	int StartCaptureTopImageUpDutThread(JupData& data);//用来上料的时候触发拍照求出补偿
	int StartCaptureTopImagePutDownDutThread(JupData& data);//用来下料的时候触发拍照求出补偿
	int StartCaptureTopImageSocketMarkAndB2BThread(JupData& data);//用来下料完成的时候触发拍照求出SocketMark点和B2B的距离
	int StartCaptureBottomImageThread(JupData& data);

private:
	DvpCamera_Manage* m_pCamera;
	std::string cameraTop_serial = "DVP TOP Vision";
	std::string cameraBottom_serial = "DVP Bottom Vision";
};
