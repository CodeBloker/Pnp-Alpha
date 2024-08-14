#pragma once

#include "StdAfx.h"
using namespace DuiLib;

class IDSCamera;

#define TIMER_IMAGE		(1001)


class JRootDlg : public JupSubDialog
{
public:
	JRootDlg();
	virtual ~JRootDlg();

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
	HBITMAP ConvertCharToHBITMAP(char* imageData, int width, int height);
	void DisplayOneFrameImage(const char* image, int width, int height);

private:
	// 界面按钮事件响应
	void OnBtnClick(TNotifyUI & msg);
	void OnBtnExposureTimeGetClick(TNotifyUI & msg);
	void OnBtnExposureTimeSetClick(TNotifyUI & msg);
	void OnBtnFrameRateGetClick(TNotifyUI & msg);
	void OnBtnFrameRateSetClick(TNotifyUI & msg);
	void OnBtnSharpnessGetClick(TNotifyUI & msg);
	void OnBtnSharpnessSetClick(TNotifyUI & msg);
	void OnBtnGainGetClick(TNotifyUI & msg);
	void OnBtnGainSetClick(TNotifyUI & msg);
	void OnBtnGammaGetClick(TNotifyUI & msg);
	void OnBtnGammaSetClick(TNotifyUI & msg);
	void OnBtnOpenCameraClick(TNotifyUI & msg);
	void OnBtnCloseCameraClick(TNotifyUI & msg);
	void OnBtnStartGrabbingClick(TNotifyUI & msg);
	void OnBtnStopGrabbingClick(TNotifyUI & msg);
	void OnRadioTrigerOffClick(TNotifyUI & msg);
	void OnRadioTrigerSwClick(TNotifyUI & msg);
	void OnRadioTrigerHwClick(TNotifyUI & msg);

private:
	IDSCamera* m_camera;	

private:
	CEditUI* m_pEditExposureTime;
	CEditUI* m_pEditFrameRate;
	CEditUI* m_pEditSharpness;
	CEditUI* m_pEditGain;
	CEditUI* m_pEditGamma;

	COptionUI* m_pOp_TriggerOff;
	COptionUI* m_pOp_TriggerSw;
	COptionUI* m_pOp_TriggerHw;

	CLabelUI *m_pLableImage;
};