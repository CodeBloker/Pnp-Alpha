#pragma once
#include "StdAfx.h"
using namespace DuiLib;

#include "HIPACamera.h"
#include "opencv2/opencv.hpp"

class HIPAMainWidget : public JupSubDialog
{
public:
	HIPAMainWidget();
	virtual ~HIPAMainWidget();

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
	void ShowMsg(std::string csMessage, int nErrorNum);
	void DisplayOneFrameImage(MV_DISPLAY_FRAME_INFO* info);
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
	void OnBtnSaveImageBmpClick(TNotifyUI & msg);
	void OnBtnSaveImageJpegClick(TNotifyUI & msg);
	void OnBtnSaveImagePngClick(TNotifyUI & msg);
	void OnBtnSaveImageTifClick(TNotifyUI & msg);
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

private:
	CComboUI*  m_pCombo_DeviceList;
	CButtonUI* m_pBtn_DeviceSerch;
	CButtonUI* m_pBtn_DeviceOpen;
	CButtonUI* m_pBtn_DeviceClose;
	CButtonUI* m_pBtn_DeviceStart;
	CButtonUI* m_pBtn_DeviceStop;
	CButtonUI* m_pBtn_SoftOnce;

	CLabelUI*  m_pLable_Image;
	CEditUI*   m_pEdit_Gain;
	CEditUI*   m_pEdit_ExposureTime;
	CEditUI*   m_pEdit_FrameRate;
	CEditUI*   m_pEdit_Sharpness;
	CEditUI*   m_pEdit_Gamma;

	COptionUI* m_pOp_ContinueMode;
	COptionUI* m_pOp_SwTriggerMode;
	COptionUI* m_pOp_HwTriggerMode;
	
private:
	HIPACamera* m_hikCamera;
	std::string m_curCamera;
};