#pragma once

#include "StdAfx.h"
using namespace DuiLib;
#include "MotionCard/MotionParameter.h"

class PositionConfigDlg : public WindowImplBase
{
public:
	PositionConfigDlg() {}
	PositionConfigDlg(WindowImplBase* p, MotionParameter* para, std::string axis, std::string pos, bool is_new_pos = false)
	{
		m_is_new_pos = is_new_pos;
		m_pos = pos;
		m_axis = axis;
		m_pMotionParameter = para;
		m_pParentWnd = p;
		Create(m_pParentWnd->GetHWND(), _T("Config"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	}
	virtual LPCTSTR GetWindowClassName() const { return _T("Config"); }
	virtual CDuiString GetSkinFile() { return _T("PosParameter.xml"); }
	virtual CDuiString GetSkinFolder() { return _T(""); }
	virtual UILIB_RESOURCETYPE GetResourceType() const { return UILIB_FILE; }
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void Notify(TNotifyUI& msg);
	virtual void InitWindow();

private:
	void OnBtnSaveClick(TNotifyUI & msg);

	// 更新界面显示
	void updateConfigDisplay(bool is_new = false);

private:
	CLabelUI*	m_pLable_CurrentAxis;
	CLabelUI*	m_pLable_AxisId;
	CEditUI*	m_pEdit_PosName;
	CEditUI*	m_pEdit_Distance;
	CEditUI*	m_pEdit_Spacing;
	CEditUI*	m_pEdit_PosMarkCn;

private:
	WindowImplBase* m_pParentWnd;
	MotionParameter* m_pMotionParameter;
	std::string m_axis;
	std::string m_pos;
	bool m_is_new_pos;
};

