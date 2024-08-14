#include "JupMotionPlugin.h"

#include "JError.h"
#include "JVersion.h"
#include "JupMotionCaller.h"
#include "CPluginDlg.h"
#include <atlbase.h>

JupMotionPlugin::JupMotionPlugin()
{
	m_error.reset(new JError());		//实例化插件的错误码信息
	m_version.reset(new JVersion());	//实例化插件的版本信息

	//RegisterSubDlg<DemoViewer>();		//注册导出界面，注册后DemoViewer类才能加载到平台的dock页面上
	RegisterCaller<JupMotionCaller>();	//注册导出测试项，注册后DemoTestCaller类的导出方法才能加入测试流程

	//CPaintManagerUI::SetResourceDll(reinterpret_cast<HMODULE>(&__ImageBase));
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + "Resource");
	m_rootDlg.reset(new CPluginDlg());
	//auto a = m_rootDlg->Create(NULL, _T("Motion"), UI_WNDSTYLE_DIALOG, WS_EX_OVERLAPPEDWINDOW);
}

JupMotionPlugin::~JupMotionPlugin()
{
}

JupPluginBase * JupGetPlugin()
{
	JupPluginBase * p = JupSingletonPointer<JupMotionPlugin>().Get();
	return p;
}
