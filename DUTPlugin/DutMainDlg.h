#pragma once
#include "StdAfx.h"
using namespace DuiLib;

#include "DutController.h"

class DutMainDlg : public JupSubDialog
{
public:
	DutMainDlg();
	virtual ~DutMainDlg();

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
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	
	void OnExit(TNotifyUI& msg);	

	LRESULT CustomEvent(JupCustomEvent* event) override;

private:
	// 界面按钮事件响应
	void OnBtnClick(TNotifyUI & msg);
	void OnBtnDutPowerOnClick(TNotifyUI & msg);
	void OnBtnDutPowerOffClick(TNotifyUI & msg);
	void OnBtnDutInitClick(TNotifyUI & msg);
	void OnBtnDutReadTxClick(TNotifyUI & msg);

	void OnBtnI2CAddrReadClick(TNotifyUI & msg);
	void OnBtnI2CAddrWriteClick(TNotifyUI & msg);

	void OnBtnSwitchToDotClick(TNotifyUI & msg);
	void OnBtnSwitchToFloodClick(TNotifyUI & msg);

private:
	std::string getOpenFileName();
	std::string openPathSaveFileDir();

	void ShowMsg(const char* msg);

private:
	CTabLayoutUI* m_pControl;

	CEditUI* m_pEdit_I2CInput;
	CListUI* m_pList_I2COutput;
	CEditUI* m_pEdit_I2CAddr;
	CEditUI* m_pEdit_I2CData;

private:
	DutController* m_dut;
	int socketIndex = 3;
};