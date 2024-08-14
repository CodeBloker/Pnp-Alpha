#pragma once
#include "CPluginDlg.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetCurrentPath(CPaintManagerUI::GetInstancePath());
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + "PluginMotionSkin");   // 设置资源的默认路径（此处设置为和exe在同一目录）
	//CPaintManagerUI::SetResourceZip(_T("PluginMotionSkin"));
	//CPaintManagerUI::ReloadSkin();
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;

	CPluginDlg* PluginDlg = new CPluginDlg();
	PluginDlg->Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	PluginDlg->CenterWindow();
	PluginDlg->ShowWindow(true);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	return 0;
}