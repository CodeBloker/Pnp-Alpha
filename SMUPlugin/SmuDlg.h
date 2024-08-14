#pragma once

#include "StdAfx.h"
using namespace DuiLib;
#include "../Controller/SmuControl.h"

class SmuDlg : public JupSubDialog
{
public:
	SmuDlg();
	virtual ~SmuDlg();

public:
	UILIB_RESOURCETYPE GetResourceType() const override;
	CDuiString GetSkinFolder() override;
	CDuiString GetSkinFile() override;
	CDuiString GetZIPFileName() const override;
	LPCTSTR GetWindowClassName() const override;

protected:
	LRESULT ResponseDefaultKeyEvent(WPARAM wParam) override;
	void InitWindow() override;
	void OnFinalMessage(HWND hWnd) override;
	void Notify(TNotifyUI& msg) override;

	CControlUI* CreateControl(LPCTSTR pstrClass) override;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	
	void OnExit(TNotifyUI& msg);	

private:
	void ShowMsg(const char* str);

private:
	// 界面按钮事件响应
	void OnBtnClick(TNotifyUI & msg);
	void OnBtnSmuConnectClick(TNotifyUI & msg);
	void OnBtnSmuDisConnectClick(TNotifyUI & msg);
	void OnBtnSmuBufReadClick(TNotifyUI & msg);
	void OnBtnSmuVersionClick(TNotifyUI & msg);
	void OnBtnSmuDotLightClick(TNotifyUI & msg);
	void OnBtnSmuFloodLightClick(TNotifyUI & msg);
	void OnBtnSmuDarkLightClick(TNotifyUI & msg);

	void OnBtnSmuCommandSendClick(TNotifyUI & msg);
	void OnBtnSmuClearUIClick(TNotifyUI & msg);

private:
	CListUI* m_pList_SmuOutput;
	CEditUI* m_pEdit_SmuCommand;

private:
	SmuControl* m_smu;
};