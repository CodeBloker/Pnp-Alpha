#include "TcpPlugin.h"

#include "JError.h"
#include "JVersion.h"
#include "TcpPluginCaller.h"
#include "TcpPluginView.h"

TcpPlugin::TcpPlugin()
{
	m_error.reset(new JError());		//实例化插件的错误码信息
	m_version.reset(new JVersion());	//实例化插件的版本信息

	RegisterCaller<TcpPluginCaller>();	//注册导出测试项，注册后TcpPluginCaller类的导出方法才能加入测试流程
	//RegisterSubDlg<TcpPluginViewer>();		//注册导出界面，注册后TcpPluginViewer类才能加载到平台的dock页面上

	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + "Resource");
	m_rootDlg.reset(new TcpPluginView);
	//auto a = m_rootDlg->Create(NULL, _T("TcpPluginView"), UI_WNDSTYLE_CHILD, WS_EX_OVERLAPPEDWINDOW, 0, 0, 0, 0);
}

TcpPlugin::~TcpPlugin()
{
}

JupPluginBase * JupGetPlugin()
{
	JupPluginBase * p = JupSingletonPointer<TcpPlugin>().Get();
	return p;
}
