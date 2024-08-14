#pragma once

#include "StdAfx.h"
using namespace DuiLib;
#include "MilManager.h"
#include "CameraDILManager.h"
#include <future>

#include "JupCore.h"
#include "../_INCLUDE/ProjectEvent.h"
using namespace ProjectEvent;

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
	void OnBtnMilCameraOpenClick(TNotifyUI & msg);
	void OnBtnMilCameraCloseClick(TNotifyUI & msg);
	void OnRadioContinueModeClick(TNotifyUI & msg);
	void OnRadioHwTrigerModeClick(TNotifyUI & msg);
	void OnBtnStartGrabbingClick(TNotifyUI & msg);
	void OnBtnStopGrabbingClick(TNotifyUI & msg);
	void OnBtnLoadParasFromFileClick(TNotifyUI & msg);

	void OnBtnExposureTimeGetClick(TNotifyUI & msg);
	void OnBtnExposureTimeSetClick(TNotifyUI & msg);
	void OnBtnFrameRateGetClick(TNotifyUI & msg);
	void OnBtnFrameRateSetClick(TNotifyUI & msg);
	void OnBtnGainGetClick(TNotifyUI & msg);
	void OnBtnGainSetClick(TNotifyUI & msg);
	void OnBtnBlackLevelGetClick(TNotifyUI & msg);
	void OnBtnBlackLevelSetClick(TNotifyUI & msg);

	void OnBtnTriggerModeTimeoutSetClick(TNotifyUI & msg);
	void OnBtnTemperatureClick(TNotifyUI & msg);
	void OnBtnRunModeGetClick(TNotifyUI & msg);
	void OnBtnRunModeSetClick(TNotifyUI & msg);

	void OnBtnDotConfigClick(TNotifyUI & msg);
	void OnBtnFloodConfigClick(TNotifyUI & msg);

private:
	HBITMAP ConvertCharToHBITMAP(char* imageData, int width, int height);
	void DisplayOneFrameImage(const char* image, int width, int height);

	// 自动标定计算圆心坐标
	void GetPixelResult(std::string camera_name, JMilFindModelEvent* e, bool is_wait);

private:
	CEditUI* m_pEdit_ExposureTime;
	CEditUI* m_pEdit_FrameRate;
	CEditUI* m_pEdit_Gain;
	CEditUI* m_pEdit_BlackLevel;
	CEditUI* m_pEdit_Timeout;
	CEditUI* m_pEdit_Temperature;
	CEditUI* m_pEdit_runMode;
	CLabelUI* m_pLable_MilImage;

private:
	MilManager* m_milManager;
	CameraDILManager* m_camera;

	// 计算线程（用于自动标定，异步执行）
	std::future<void> m_tx_thread;
	std::future<void> m_ty_thread;
	std::future<void> m_ids_thread;
};