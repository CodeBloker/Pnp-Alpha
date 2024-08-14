#include "AlphaCalibrationPlugin.h"

#include "JError.h"
#include "JVersion.h"
#include "AlphaCalibrationPluginCaller.h"
#include "AlphaCalibrationPluginView.h"

AlphaCalibrationPlugin::AlphaCalibrationPlugin()
{
	m_error.reset(new JError());		//实例化插件的错误码信息
	m_version.reset(new JVersion());	//实例化插件的版本信息

	RegisterCaller<AlphaCalibrationPluginCaller>();	//注册导出测试项，注册后AlphaCalibrationPluginCaller类的导出方法才能加入测试流程
	//RegisterSubDlg<AlphaCalibrationPluginViewer>();		//注册导出界面，注册后AlphaCalibrationPluginViewer类才能加载到平台的dock页面上

	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + "Resource");
	m_rootDlg.reset(new AlphaCalibrationPluginView);
	//auto a = m_rootDlg->Create(NULL, _T("AlphaCalibrationPluginView"), UI_WNDSTYLE_CHILD, WS_EX_OVERLAPPEDWINDOW, 0, 0, 0, 0);
}

AlphaCalibrationPlugin::~AlphaCalibrationPlugin()
{
}

JupPluginBase * JupGetPlugin()
{
	JupPluginBase * p = JupSingletonPointer<AlphaCalibrationPlugin>().Get();
	return p;
}
