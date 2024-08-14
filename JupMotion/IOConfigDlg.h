#pragma once

#include "StdAfx.h"
using namespace DuiLib;
#include "MotionCard/MotionParameter.h"

class IOConfigDlg : public WindowImplBase
{
public:
	IOConfigDlg(WindowImplBase* p, MotionParameter* para, MotionIO* io, bool is_input, bool is_new = false)
	{
		m_is_new = is_new;
		m_is_input = is_input;
		m_io = io;
		m_pMotionParameter = para;
		m_pParentWnd = p;
		Create(m_pParentWnd->GetHWND(), _T("IOConfigDlg"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	}

	virtual LPCTSTR GetWindowClassName() const { return _T("IOConfigDlg"); }
	virtual CDuiString GetSkinFile() { return _T("IOParameter.xml"); }
	virtual CDuiString GetSkinFolder() { return _T(""); }
	virtual UILIB_RESOURCETYPE GetResourceType() const { return UILIB_FILE; }
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void Notify(TNotifyUI& msg);
	virtual void InitWindow();

private:
	void OnBtnSaveClick(TNotifyUI & msg);
	// 更新界面显示
	void updateConfigDisplay();

private:
	CEditUI*	m_pEdit_IONameEn;
	CEditUI*	m_pEdit_IONameCn;
	CEditUI*	m_pEdit_GroupName;
	CEditUI*	m_pEdit_CardType;
	CEditUI*	m_pEdit_CardNum;
	CEditUI*	m_pEdit_BitNum;
	CEditUI*	m_pEdit_IsUse;
	CEditUI*	m_pEdit_ElectricalLevel;

private:
	WindowImplBase* m_pParentWnd;
	MotionParameter* m_pMotionParameter;
	MotionIO* m_io;
	bool m_is_input;
	bool m_is_new;
};

