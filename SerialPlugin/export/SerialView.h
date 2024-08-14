#pragma once
#include "StdAfx.h"
using namespace DuiLib;

#include "SerialControl.h"

class SerialView : public JupSubDialog
{
public:
	SerialView();
	virtual ~SerialView();

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

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

	LRESULT CustomEvent(JupCustomEvent* event) override;

private:
	void ShowMsg(const char* str);

private:
	// 界面按钮事件响应
	void OnBtnClick(TNotifyUI & msg);
	void OnBtnAlphaLight1OpenClick(TNotifyUI & msg);
	void OnBtnAlphaLight2OpenClick(TNotifyUI & msg);
	void OnBtnAlphaOpenAllLightClick(TNotifyUI & msg);
	void OnBtnAlphaCloseAllLightClick(TNotifyUI & msg);
	void OnBtnTemp1GetClick(TNotifyUI & msg);
	void OnBtnTemp2GetClick(TNotifyUI & msg);
	void OnBtnHeigh1GetClick(TNotifyUI & msg);
	void OnBtnHeigh2GetClick(TNotifyUI & msg);
	void OnBtnHeigh3GetClick(TNotifyUI & msg);

	void OnBtnCommandSendClick(TNotifyUI & msg);
	void OnBtnClearUIClick(TNotifyUI & msg);

private:
	CListUI* m_pList_Output;
	CEditUI* m_pEdit_Input;

private:
	SerialControl* m_pSerial;
};