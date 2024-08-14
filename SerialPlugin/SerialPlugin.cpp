#include "SerialPlugin.h"

#include "JError.h"
#include "JVersion.h"
#include "SerialCaller.h"
#include "SerialView.h"

SerialPlugin::SerialPlugin()
{
	m_error.reset(new JError());		//实例化插件的错误码信息
	m_version.reset(new JVersion());	//实例化插件的版本信息

	RegisterCaller<SerialCaller>();	//注册导出测试项，注册后DemoTestCaller类的导出方法才能加入测试流程
	//RegisterSubDlg<SerialViewer>();		//注册导出界面，注册后DemoViewer类才能加载到平台的dock页面上

	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + "Resource");
	m_rootDlg.reset(new SerialView);
	//auto a = m_rootDlg->Create(NULL, _T("SerialView"), UI_WNDSTYLE_CHILD, WS_EX_OVERLAPPEDWINDOW, 0, 0, 0, 0);
}

SerialPlugin::~SerialPlugin()
{
}

JupPluginBase * JupGetPlugin()
{
	JupPluginBase * p = JupSingletonPointer<SerialPlugin>().Get();
	return p;
}
