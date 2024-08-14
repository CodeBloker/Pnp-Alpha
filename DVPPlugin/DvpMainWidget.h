#pragma once
#include "StdAfx.h"
using namespace DuiLib;

#include "DvpCamera_Manage.h"
#include "opencv2/opencv.hpp"

class DvpMainWidget : public JupSubDialog
{
public:
	DvpMainWidget();
	virtual ~DvpMainWidget();

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

private:
	void EnableControls(bool bIsCameraReady);
	void DisplayOneFrameImage(char* imageData, int width, int height);
	HBITMAP ConvertCharToHBITMAP(char* imageData, int width, int height);

private:
	// 界面按钮事件响应
	void OnBtnClick(TNotifyUI & msg);
	void OnBtnDeviceSerchClick(TNotifyUI & msg);
	void OnBtnDeviceOpenClick(TNotifyUI & msg);
	void OnBtnDeviceCloseClick(TNotifyUI & msg);
	void OnRadioContinueModeClick(TNotifyUI & msg);
	void OnRadioSwTrigerModeClick(TNotifyUI & msg);
	void OnRadioHwTrigerModeClick(TNotifyUI & msg);
	void OnBtnStartGrabbingClick(TNotifyUI & msg);
	void OnBtnStopGrabbingClick(TNotifyUI & msg);
	void OnBtnSoftwareOnceClick(TNotifyUI & msg);
	void OnBtnOpenParamsGUIClick(TNotifyUI & msg);

private:
	CComboUI*  m_pCombo_DeviceList;
	CButtonUI* m_pBtn_DeviceSerch;
	CButtonUI* m_pBtn_DeviceOpen;
	CButtonUI* m_pBtn_DeviceClose;
	CButtonUI* m_pBtn_DeviceStart;
	CButtonUI* m_pBtn_DeviceStop;
	CButtonUI* m_pBtn_SoftOnce;
	COptionUI* m_pOp_ImageSaveBmp;
	COptionUI* m_pOp_ImageSaveJepg;
	COptionUI* m_pOp_ImageSavePng;
	COptionUI* m_pOp_ImageSaveTif;
	CButtonUI* m_pBtn_OpenParamsGUI;

	CLabelUI*  m_pLable_Image;

	COptionUI* m_pOp_ContinueMode;
	COptionUI* m_pOp_SwTriggerMode;
	COptionUI* m_pOp_HwTriggerMode;
	
private:
	DvpCamera_Manage* m_dvpCamera;
	std::string m_curCamera;
};