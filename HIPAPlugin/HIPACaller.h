#pragma once

#include "PluginBase/JupCaller.h"
#include "HIPACamera.h"

/*
	该类是平台调用测试项的接口，若正确定义能在平台的测试流程编辑器上被使用，并加载到测试项中
*/
class HIPACaller : public JupCaller
{
public:
	HIPACaller();
	~HIPACaller();

	/*
		在该函数做特定的初始化操作，由平台调用该函数

		示例：默认调用父类接口的实现JupCaller::Initialize();
		根据当前插件的实际需要选择添加内容
	*/
	int Initialize() override;

	/*
		统一在该函数内注册所有测试项方法的函数

		示例：Plugin_Method_Add(HIPACaller, Demo_msleep100);
		其中DemoTestCaller为当前类的类名，Demo_msleep100为需要注册的函数名
	*/
	int RegisterMethod() override;

private:
	/*
		在此添加需要测试项方法的函数，函数类型必须为int (T::*)(JupData&)
		下列函数需要在RegisterMethod()中注册才能在平台上使用
	*/
	int Demo_msleep100(JupData& data);

	// 设置Tx相机参数（触发模式，触发源，曝光参数等）
	int SetTxCameraParameter(JupData& data);
	// 设置上下机参数（触发模式，触发源，曝光参数等）
	int SetTyCameraParameter(JupData& data);
	// 相机1获取图片
	int GetCameraImage1(JupData& data);
	// 相机1获取图片
	int GetCameraImage2(JupData& data);

	// pnp Doe
	// 重置相机参数（关闭采集等）
	int LoadPnpDoeResetDatas(JupData& data);
	// 设置上相机参数（触发模式，触发源，曝光参数等）
	int SetTopCameraHwParameter(JupData& data);
	// 设置上下机参数（触发模式，触发源，曝光参数等）
	int SetDownCameraHwParameter(JupData& data);
	// 开启采集线程，等待触发信号获得图片
	int StartCaptureTopImageThread(JupData& data);
	int StartCaptureBottomImageThread(JupData& data);
	// 保存图片，计算结果
	int SaveTopImageAndCalculate(JupData& data);
	int SaveBottomImageAndCalculate(JupData& data);

private:
	HIPACamera* m_pCamera;
	std::string cameraTx_serial = "TX";
	std::string cameraTy_serial = "TY"; 
	std::string cameraTop_serial = "TOP Vision";
	std::string cameraBottom_serial = "Bottom Vision";
};
