#include "DUTPlugin.h"
#include "JError.h"
#include "JVersion.h"
#include "DUTCaller.h"
#include "DutMainDlg.h"
#include <atlbase.h>

//int  WinMain(
//	HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR     lpCmdLine,
//	int       nShowCmd
//) {
//
//	JupGetPlugin();
//}

DUTPlugin::DUTPlugin()
{
	m_error.reset(new JError());		//实例化插件的错误码信息
	m_version.reset(new JVersion());	//实例化插件的版本信息

	RegisterCaller<DUTCaller>();	//注册导出测试项，注册后DemoTestCaller类的导出方法才能加入测试流程
	//RegisterSubDlg<DemoViewer>();		//注册导出界面，注册后DemoViewer类才能加载到平台的dock页面上

	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + "Resource");
	m_rootDlg.reset(new DutMainDlg());
}

DUTPlugin::~DUTPlugin()
{
}

JupPluginBase * JupGetPlugin()
{
	JupPluginBase * p = JupSingletonPointer<DUTPlugin>().Get();
	return p;
}
