#pragma once

#include "StdAfx.h"
using namespace DuiLib;
#include "MilManager.h"

class MilDlg : public JupSubDialog
{
public:
	MilDlg();
	virtual ~MilDlg();

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

	LRESULT CustomEvent(JupCustomEvent* event) override;

private:
	// 界面按钮事件响应
	void OnBtnClick(TNotifyUI & msg);
	void OnBtnImagePathClick(TNotifyUI & msg);
	void OnBtnImageCalculateClick(TNotifyUI & msg);
	void OnBtnClearUIClick(TNotifyUI & msg);

private:
	CEditUI* m_pEdit_ImageFile;
	CComboUI* m_pCom_Index;
	CEditUI* m_pEdit_Degree;
	CEditUI* m_pEdit_Distance;
	CEditUI* m_pEdit_midPointX;
	CEditUI* m_pEdit_midPointY;
	CLabelUI* m_pLable_OutputResult;

	COptionUI* m_pOp_BottomCross;
	COptionUI* m_pOp_PNPCross;
	COptionUI* m_pOp_PNPCrossAndCircle;

private:
	MilManager* m_milManager;
	int socketIndex = 0;

public:
	//PNP视觉与底部视觉的校准
	void MilDigPnpVisualCalibrationGetResult(std::string m_image_ptr);
	//PNP吸嘴校准
	void MilDigNozzleVisualCalibrationGetResult(std::string m_image_ptr);

//用来测试
public:
	void funcTest();
};