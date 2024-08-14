#pragma once

#include "StdAfx.h"
using namespace DuiLib;
#include "MotionCard/MotionParameter.h"

class CardConfigDlg : public WindowImplBase
{
public:
	CardConfigDlg() {}
	CardConfigDlg(WindowImplBase* p, MotionParameter* para, std::string axis, bool is_new_axis = false)
	{
		m_is_new_axis = is_new_axis;
		m_axis = axis;
		m_pMotionParameter = para;
		m_pParentWnd = p;
		Create(m_pParentWnd->GetHWND(), _T("Config"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	}
	virtual LPCTSTR GetWindowClassName() const { return _T("Config"); }
	virtual CDuiString GetSkinFile() { return _T("AxisParameter.xml"); }
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
	// 基础参数
	CEditUI*	m_pEdit_CurrentAxis;
	CEditUI*	m_pEdit_CurrentAxisCn;
	CEditUI*	m_pEdit_MotorType;
	CEditUI*	m_pEdit_CardType;
	CEditUI*	m_pEdit_CardNum;
	CEditUI*	m_pEdit_AxisNum;
	// 运动参数
	CEditUI*	m_pEdit_AxisMinSpeed;
	CEditUI*	m_pEdit_AxisMaxSpeed;
	CEditUI*	m_pEdit_AxisAcc;
	CEditUI*	m_pEdit_AxisDec;
	CEditUI*	m_pEdit_AxisStopSpeed;
	CEditUI*	m_pEdit_AxisCurve;
	CEditUI*	m_pEdit_AllowErrorPos;
	CEditUI*	m_pEdit_Scale;
	CEditUI*	m_pEdit_Lead;
	// 回零参数
	CEditUI*	m_pEdit_HomeMode;
	CEditUI*	m_pEdit_HomeDir;
	CEditUI*	m_pEdit_HomeMinSpeed;
	CEditUI*	m_pEdit_HomeMaxSpeed;
	CEditUI*	m_pEdit_HomeAcc;
	CEditUI*	m_pEdit_HomeDec;
	CEditUI*	m_pEdit_HomeOffset;
	CEditUI*	m_pEdit_HomeCurve;
	CEditUI*	m_pEdit_HomeEZA;
	// 超时参数
	CEditUI*	m_pEdit_UseDelay;
	CEditUI*	m_pEdit_DelayTime;
	// 限位参数
	CEditUI*	m_pEdit_UseLimit;
	CEditUI*	m_pEdit_PositiveLimit;
	CEditUI*	m_pEdit_NegativeLimit;

private:
	WindowImplBase* m_pParentWnd;
	MotionParameter* m_pMotionParameter;
	std::string m_axis;
	bool m_is_new_axis;
};

