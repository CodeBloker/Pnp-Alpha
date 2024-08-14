#include "SmuPlugin.h"
#include "JError.h"
#include "JVersion.h"
#include "Caller/SmuCaller.h"
#include "SmuDlg.h"
#include <atlbase.h>

SmuPlugin::SmuPlugin()
{
	m_error.reset(new JError());		//实例化插件的错误码信息
	m_version.reset(new JVersion());	//实例化插件的版本信息

	RegisterCaller<SmuCaller>();	//注册导出测试项，注册后DemoTestCaller类的导出方法才能加入测试流程
	//RegisterSubDlg<DemoViewer>();		//注册导出界面，注册后DemoViewer类才能加载到平台的dock页面上

	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + "Resource");
	m_rootDlg.reset(new SmuDlg());
}

SmuPlugin::~SmuPlugin()
{
}

JupPluginBase * JupGetPlugin()
{
	JupPluginBase * p = JupSingletonPointer<SmuPlugin>().Get();
	return p;
}
