#pragma once
#include "StdAfx.h"
using namespace DuiLib;

class DemoView : public JupSubDialog
{
public:
	DemoView();
	virtual ~DemoView();

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
};