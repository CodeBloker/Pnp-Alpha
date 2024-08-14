#pragma once
#include "CPluginDlg.h"

//#include "UIlib.h"
//using namespace DuiLib;

// 移动完成消息
#define WM_TIPS_RECV_MOVEDONE (WM_USER + 1)
#define WM_TIPS_SEND_STOP (WM_USER + 2)

class MyTipsDialog : public WindowImplBase
{
public:
	MyTipsDialog() {}
	MyTipsDialog(WindowImplBase* p, CDuiString log, int axis_no)
	{
		m_pParentWnd = p;
		Create(m_pParentWnd->GetHWND(), _T("Tips"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
		SetText(log);
		m_cur_axis = axis_no;
	}
	virtual LPCTSTR GetWindowClassName() const { return _T("Tips"); }
	virtual CDuiString GetSkinFile() { return _T("MyTipsDialog.xml"); }
	virtual CDuiString GetSkinFolder() { return _T(""); }
	virtual UILIB_RESOURCETYPE GetResourceType() const { return UILIB_FILE; }
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void Notify(TNotifyUI& msg);
	void SetText(CDuiString log);
private:
	void OnMoveDone(WPARAM wParam, LPARAM lParam);
	WindowImplBase* m_pParentWnd;
	int m_cur_axis;
};

