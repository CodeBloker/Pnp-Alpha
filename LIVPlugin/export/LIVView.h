#pragma once

#include "StdAfx.h"
using namespace DuiLib;

class LIVView : public JupSubDialog
{
public:
	LIVView();
	virtual ~LIVView();

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

	LRESULT CustomEvent(JupCustomEvent* event) override;
};