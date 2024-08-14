#pragma once
#include "StdAfx.h"
using namespace DuiLib;

class TcpController;

class TcpPluginView : public JupSubDialog
{
public:
	TcpPluginView();
	virtual ~TcpPluginView();

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
	void ShowMsg(const char* msg);

private:
	// 界面按钮事件响应
	void OnBtnClick(TNotifyUI & msg);
	void OnClearListClick(TNotifyUI & msg);
	// ACL获取值
	void OnGetACLValuesClick(TNotifyUI & msg);

	// Confocal Sensor
	void OnConfocalGetValue1Click(TNotifyUI & msg);
	void OnConfocalGetValue2Click(TNotifyUI & msg);

private:
	CListUI* m_pList_TcpOutput;

private:
	TcpController* m_tcp;
};
