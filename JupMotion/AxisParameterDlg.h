#pragma once

#include "StdAfx.h"
using namespace DuiLib;

class AxisParameterDlg : public WindowImplBase
{
public:
	AxisParameterDlg() {}
	AxisParameterDlg(WindowImplBase* p)
	{
		m_pParentWnd = p;
		Create(m_pParentWnd->GetHWND(), _T("AxisParameter"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	}
	virtual LPCTSTR GetWindowClassName() const { return _T("AxisParameterDlg"); }
	virtual CDuiString GetSkinFile() { return _T("AxisParameter.xml"); }
	virtual CDuiString GetSkinFolder() { return _T(""); }
	virtual UILIB_RESOURCETYPE GetResourceType() const { return UILIB_FILE; }
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void Notify(TNotifyUI& msg);

private:
	void OnBtnAxisParasSaveClick(TNotifyUI & msg);

private:
	WindowImplBase* m_pParentWnd;
};

