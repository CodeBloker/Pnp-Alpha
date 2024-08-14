#include "AlphaCalibrationPluginView.h"
#include <future>
#include "JupCore.h"

#include "../_INCLUDE/ProjectEvent.h"
using namespace ProjectEvent;

AlphaCalibrationPluginView::AlphaCalibrationPluginView()
{
}

AlphaCalibrationPluginView::~AlphaCalibrationPluginView()
{	
}

UILIB_RESOURCETYPE AlphaCalibrationPluginView::GetResourceType() const
{
	return UILIB_ZIP;
}

CDuiString AlphaCalibrationPluginView::GetSkinFolder()
{
	return "";
}

CDuiString AlphaCalibrationPluginView::GetSkinFile()
{
	return "expand_frame.xml";
}

CDuiString AlphaCalibrationPluginView::GetZIPFileName() const
{
	return "PluginAlphaCalibration.zip";
}

LPCTSTR AlphaCalibrationPluginView::GetWindowClassName() const
{
	return "AlphaCalibrationPluginView";
}

LRESULT AlphaCalibrationPluginView::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return FALSE;
}

void AlphaCalibrationPluginView::InitWindow()
{	
	jCore->RegisterEventWindow(g_CalibrationWidget, this);

	m_pOp_CameraTxSelect = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_CameraTx")));
	m_pOp_CameraTySelect = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_CameraTy")));
	m_pOp_CameraIdsSelect = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_CameraAlpha")));
	m_pEdit_TxExposure = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TxExposure")));
	m_pEdit_TyExposure = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TyExposure")));
	m_pEdit_IdsExposure = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_IdsExposure")));
	m_pEdit_TxGain = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TxGain")));
	m_pEdit_TyGain = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TyGain")));
	m_pEdit_IdsGain = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_IdsGain")));
	m_pEdit_TxPixel_x = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TxResult_x")));
	m_pEdit_TxPixel_y = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TxResult_y")));
	m_pEdit_TyPixel_x = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TyResult_x")));
	m_pEdit_TyPixel_y = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TyResult_y")));
	m_pEdit_IdsPixel_x = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_IdsResult_x")));
	m_pEdit_IdsPixel_y = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_IdsResult_y")));
	m_pOp_TxContinueCapture = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_TxContinueImage")));
	m_pOp_TyContinueCapture = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_TyContinueImage")));
	m_pOp_IdsContinueCapture = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_AlphaContinueImage")));

	m_pBtn_TxExposureSet = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_TxExposureSet")));
	m_pBtn_TyExposureSet = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_TyExposureSet")));
	m_pBtn_IdsExposureSet = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_IdsExposureSet")));
	m_pBtn_TxGainSet = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_TxGainSet")));
	m_pBtn_TyGainSet = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_TyGainSet")));
	m_pBtn_IdsGainSet = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_IdsGainSet")));
	m_pBtn_TxParasGet = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_TxParasGet")));
	m_pBtn_TyParasGet = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_TyParasGet")));
	m_pBtn_IdsParasGet = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_IdsParasGet")));
	m_pBtn_DeviceOpen = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_DeviceOpen")));
	m_pBtn_DeviceClose = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_DeviceClose")));
	m_pBtn_StartGrab = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_StartGrab")));
	m_pBtn_StopGrab = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_StopGrab")));

	m_pEdit_TxPos1 = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TxPos1")));
	m_pEdit_TxPos2 = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TxPos2")));
	m_pEdit_TxPos3 = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TxPos3")));
	m_pEdit_TyPos1 = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TyPos1")));
	m_pEdit_TyPos2 = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TyPos2")));
	m_pEdit_TyPos3 = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TyPos3")));
	m_pOp_OfflineMode = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_OfflineMode")));
	m_pEdit_Pos1PointX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Pos1PointX")));
	m_pEdit_Pos2PointX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Pos2PointX")));
	m_pEdit_Pos3PointX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Pos3PointX")));
	m_pEdit_Pos1PointY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Pos1PointY")));
	m_pEdit_Pos2PointY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Pos2PointY")));
	m_pEdit_Pos3PointY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Pos3PointY")));
	m_pEdit_TxResultX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TxResultX")));
	m_pEdit_TxResultY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TxResultY")));
	m_pLable_TxThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_TxThreshold")));
	m_pEdit_TyResultX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TyResultX")));
	m_pEdit_TyResultY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TyResultY")));
	m_pLable_TyThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_TyThreshold")));

	m_pEdit_PointX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_PointX")));
	m_pEdit_PointY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_PointY")));
	m_pEdit_PointR = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_PointR")));

	m_pLable_Image1 = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("hik_image1")));
	m_pLable_Image2 = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("hik_image2")));
	m_pLable_Image3 = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("hik_image3")));
	m_pLable_Image4 = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("hik_image4")));
	m_pLable_Image5 = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("hik_image5")));
	m_pLable_Image6 = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("hik_image6")));

	m_pOp_TxCameraFocal = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_TxCameraFocal")));
	m_pOp_TyCameraFocal = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_TyCameraFocal")));
	m_pOp_AlphaCameraFocal = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_AlphaCameraFocal")));
	m_pLable_TxCameraFocal = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_TxCameraFocal")));
	m_pLable_TyCameraFocal = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_TyCameraFocal")));
	m_pLable_AlphaCameraFocal = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_AlphaCameraFocal")));
	m_pLable_TxFocalThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_TxFocalThreshold")));
	m_pLable_TyFocalThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_TyFocalThreshold1")));
	m_pLable_AlphaFocalThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_AlphaFocalThreshold1")));
	m_pBtn_AlphaAutoFocal = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_AlphaAutoFocal")));

	m_pEdit_TxDertaX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TxDertaX")));
	m_pLable_TxDertaXThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_TxDertaXThreshold")));
	m_pLable_Axis1Advice = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_Axis1Advice")));
	m_pEdit_TxDertaY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TxDertaY")));
	m_pLable_TxDertaYThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_TxDertaYThreshold")));
	m_pLable_Axis2Advice = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_Axis2Advice")));
	m_pEdit_AlphaDertaX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_AlphaDertaX")));
	m_pLable_AlphaDertaXThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_AlphaDertaXThreshold")));
	m_pLable_Axis3Advice = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_Axis3Advice")));
	m_pEdit_AlphaDertaY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_AlphaDertaY")));
	m_pLable_AlphaDertaYThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_AlphaDertaYThreshold")));
	m_pLable_Axis4Advice = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_Axis4Advice")));
	m_pEdit_TyDertaX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TyDertaX")));
	m_pLable_TyDertaXThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_TyDertaXThreshold")));
	m_pLable_Axis5Advice = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_Axis5Advice")));
	m_pEdit_TyDertaY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_TyDertaY")));
	m_pLable_TyDertaYThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_TyDertaYThreshold")));
	m_pLable_Axis6Advice = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_Axis6Advice")));

	m_pLable_TxStatus = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_TxStatus")));
	m_pLable_TyStatus = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_TyStatus")));
	m_pLable_IdsStatus = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_IdsStatus")));

	m_pOp_TxCalibration = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("radio_Tx")));
	m_pOp_TyCalibration = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("radio_Ty")));
	m_pOp_OqcTxCalibration = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("radio_OqcTx")));
	m_pOp_OqcTyCalibration = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("radio_OqcTy")));

	// OQC
	m_pOp_OqcMode = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_OqcMode")));
	m_pEdit_OqcTy_x = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_OqcTy_x")));
	m_pEdit_OqcTy_y = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_OqcTy_y")));
	m_pEdit_OqcAlpha_x = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_OqcAlpha_x")));
	m_pEdit_OqcAlpha_y = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_OqcAlpha_y")));
	m_pEdit_OqcTyDertaX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_OqcTyDertaX")));
	m_pEdit_OqcTyDertaY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_OqcTyDertaY")));
	m_pLable_OqcTyDertaXThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_OqcTyDertaXThreshold")));
	m_pLable_OqcTyDertaYThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_OqcTyDertaYThreshold")));
	m_pLable_OqcAxis5Advice = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_OqcAxis5Advice")));
	m_pLable_OqcAxis6Advice = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_OqcAxis6Advice")));
	m_pEdit_OqcAlphaDertaX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_OqcAlphaDertaX")));
	m_pEdit_OqcAlphaDertaY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_OqcAlphaDertaY")));
	m_pLable_OqcAlphaDertaXThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_OqcAlphaDertaXThreshold")));
	m_pLable_OqcAlphaDertaYThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_OqcAlphaDertaYThreshold")));
	m_pLable_OqcAxis3Advice = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_OqcAxis3Advice")));
	m_pLable_OqcAxis4Advice = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_OqcAxis4Advice")));
	m_pEdit_OqcTxResultX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_OqcTxResultX")));
	m_pEdit_OqcTxResultY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_OqcTxResultY")));
	m_pLable_OqcTxThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_OqcTxThreshold")));
	m_pEdit_OqcTyResultX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_OqcTyResultX")));
	m_pEdit_OqcTyResultY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_OqcTyResultY")));
	m_pLable_OqcTyThreshold = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("lable_OqcTyThreshold")));
	m_pBtn_OqcStartTest = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_OqcStartAutoCalibration")));

	m_pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabTest")));

	m_pLable_TxThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "TxResultThreshold").c_str());
	m_pLable_TyThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "TyResultThreshold").c_str());
	m_pLable_TxFocalThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "TxFocalThreshold").c_str());
	m_pLable_TyFocalThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "TyFocalThreshold").c_str());
	m_pLable_AlphaFocalThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "IdsFocalThreshold").c_str());
	m_pLable_TxDertaXThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "TxDertaXThreshold").c_str());
	m_pLable_TxDertaYThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "TxDertaYThreshold").c_str());
	m_pLable_TyDertaXThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "TyDertaXThreshold").c_str());
	m_pLable_TyDertaYThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "TyDertaYThreshold").c_str());
	m_pLable_AlphaDertaXThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "IdsDertaXThreshold").c_str());
	m_pLable_AlphaDertaYThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "IdsDertaYThreshold").c_str());

	m_pLable_OqcTyDertaXThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "TyDertaXThreshold").c_str());
	m_pLable_OqcTyDertaYThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "TyDertaYThreshold").c_str());
	m_pLable_OqcAlphaDertaXThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "IdsDertaXThreshold").c_str());
	m_pLable_OqcAlphaDertaYThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "IdsDertaYThreshold").c_str());
	m_pLable_OqcTxThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "TxResultThreshold").c_str());
	m_pLable_OqcTyThreshold->SetText(jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "TyResultThreshold").c_str());

	m_pOp_CameraTxSelect->Selected(true);
	m_pOp_CameraTySelect->Selected(true);
	m_pOp_CameraIdsSelect->Selected(true);
}

void AlphaCalibrationPluginView::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
}

void AlphaCalibrationPluginView::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		CDuiString senderName = msg.pSender->GetName();
		if (senderName == "btn_TxExposureSet")
			OnBtnTxExposureSetClick(msg);
		else if (senderName == _T("btn_TxGainSet"))
			OnBtnTxGainSetClick(msg);
		else if (senderName == _T("btn_TxParasGet"))
			OnBtnTxParasGetClick(msg);
		else if (senderName == _T("btn_TyExposureSet"))
			OnBtnTyExposureSetClick(msg);
		else if (senderName == _T("btn_TyGainSet"))
			OnBtnTyGainSetClick(msg);
		else if (senderName == _T("btn_TyParasGet"))
			OnBtnTyParasGetClick(msg);
		else if (senderName == _T("btn_IdsExposureSet"))
			OnBtnIdsExposureSetClick(msg);
		else if (senderName == _T("btn_IdsGainSet"))
			OnBtnIdsGainSetClick(msg);
		else if (senderName == _T("btn_IdsParasGet"))
			OnBtnIdsParasGetClick(msg);
		else if (senderName == _T("btn_DeviceOpen"))
			OnBtnDeviceOpenClick(msg);
		else if (senderName == _T("btn_DeviceClose"))
			OnBtnDeviceCloseClick(msg);
		else if (senderName == _T("btn_StartGrab"))
			OnBtnStartGrabClick(msg);
		else if (senderName == _T("btn_StopGrab"))
			OnBtnStopGrabClick(msg);
		else if (senderName == _T("btn_StartAutoCalibration"))
			OnBtnStartAutoCalibrationClick(msg);
		else if (senderName == _T("btn_SelectOfflineImage"))
			OnBtnSelectOfflineImageClick(msg);
		else if (senderName == _T("btn_CalibrationConfirm"))
			OnBtnCalibrationConfirmClick(msg);
		else if (senderName == _T("btn_OqcStartAutoCalibration"))
			OnOqcStartTestClick(msg);
		else if (senderName == _T("radio_Tx"))
			OnRadioTxClick(msg);
		else if (senderName == _T("radio_Ty"))
			OnRadioTyClick(msg);
		else if (senderName == _T("radio_OqcTx"))
			OnRadioOqcTxClick(msg);
		else if (senderName == _T("radio_OqcTy"))
			OnRadioOqcTyClick(msg);
	}
	else if (msg.sType == DUI_MSGTYPE_SELECTCHANGED)
	{
		CDuiString senderName = msg.pSender->GetName();
		 if (senderName == _T("check_CameraTx"))
			 OnCheckTxSelectClick(msg);
		 else if (senderName == _T("check_CameraTy"))
			 OnCheckTySelectClick(msg);
		 else if (senderName == _T("check_CameraAlpha"))
			 OnCheckIdsSelectClick(msg);
		 else if (senderName == _T("check_TxContinueImage"))
			 OnCheckTxContinueClick(msg);
		 else if (senderName == _T("check_TyContinueImage"))
			 OnCheckTyContinueClick(msg);
		 else if (senderName == _T("check_AlphaContinueImage"))
			 OnCheckIdsContinueClick(msg);
		 else if (senderName == _T("check_OfflineMode"))
			 OnCheckOfflineClick(msg);
		 else if (senderName == _T("check_OqcMode"))
			 OnCheckOqcModeClick(msg);
		 else if (senderName == _T("tab_Calibration"))
			 m_pControl->SelectItem(0);
		 else if (senderName == _T("tab_Motion"))
			 m_pControl->SelectItem(1);
		 else if (senderName == _T("tab_Analysis"))
			 m_pControl->SelectItem(2);
		 else if (senderName == _T("tab_Oqc"))
			 m_pControl->SelectItem(3);
	}
}

LRESULT AlphaCalibrationPluginView::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT res = 0;

	if (uMsg == WM_CREATE)
	{
	}

	res = __super::HandleMessage(uMsg, wParam, lParam);
	return res;
}

LRESULT AlphaCalibrationPluginView::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT AlphaCalibrationPluginView::CustomEvent(JupCustomEvent * event)
{
	JupCustomEvent::eType type = event->Type();
	if (type == ProjectEvent::e_JCalibrationEvent)
	{
		auto e = dynamic_cast<JCalibrationEvent*>(event);
		if (e->m_command == "DisplayOnceFrame")
		{
			if (e->m_camera == "TX")
				DisplayTxOneFrameImage(e->m_pData, e->m_nWidth, e->m_nHeight);
			else if (e->m_camera == "TY")
				DisplayTyOneFrameImage(e->m_pData, e->m_nWidth, e->m_nHeight);
			else if (e->m_camera == "IDS")
				DisplayIdsOneFrameImage(e->m_pData, e->m_nWidth, e->m_nHeight);
		}
		else if (e->m_command == "DisplayPixel")
		{
			if (e->m_camera == "TX")
			{
				CDuiString strVal;
				strVal.Format("%.2f", e->m_point_x);
				m_pEdit_TxPixel_x->SetText(strVal);
				if (m_circle_point_x >= 0.0)
				{
					strVal.Format("%.2f", e->m_point_x - m_circle_point_x);
					m_pEdit_TxDertaX->SetText(strVal);
					double threshold_x = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TxDertaXThreshold");
					if (abs(e->m_point_x - m_circle_point_x) <= threshold_x)
					{
						m_pEdit_TxDertaX->SetBkColor(0xFF00FF00);
						m_pLable_Axis1Advice->SetText((std::string("轴1无需调整")).c_str());
					}
					else
					{
						m_pEdit_TxDertaX->SetBkColor(0xFFFF0000);
						if (e->m_point_x - m_circle_point_x > 0)
							m_pLable_Axis1Advice->SetText((std::string("轴1向 - 方向调整")).c_str());
						else
							m_pLable_Axis1Advice->SetText((std::string("轴1向 + 方向调整")).c_str());
					}
				}
				strVal.Format("%.2f", e->m_point_y);
				m_pEdit_TxPixel_y->SetText(strVal);
				if (m_circle_point_y >= 0.0)
				{
					strVal.Format("%.2f", e->m_point_y - m_circle_point_y);
					m_pEdit_TxDertaY->SetText(strVal);
					double threshold_y = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TxDertaYThreshold");
					if (abs(e->m_point_y - m_circle_point_y) <= threshold_y)
					{
						m_pEdit_TxDertaY->SetBkColor(0xFF00FF00);
						m_pLable_Axis2Advice->SetText((std::string("轴2无需调整")).c_str());
					}
					else
					{
						m_pEdit_TxDertaY->SetBkColor(0xFFFF0000);
						if (e->m_point_y - m_circle_point_y > 0)
							m_pLable_Axis2Advice->SetText((std::string("轴2向 - 方向调整")).c_str());
						else
							m_pLable_Axis2Advice->SetText((std::string("轴2向 + 方向调整")).c_str());
					}
				}
			}
			else if (e->m_camera == "TY")
			{
				double point_x_value;
				double point_y_value;
				if (m_oqc_enable)
				{
					point_x_value = atof(m_pEdit_OqcTy_x->GetText().GetData());
					point_y_value = atof(m_pEdit_OqcTy_y->GetText().GetData());
				}
				else
				{
					point_x_value = m_circle_point_x;
					point_y_value = m_circle_point_y;
				}

				CDuiString strVal;
				strVal.Format("%.2f", e->m_point_x);
				m_pEdit_TyPixel_x->SetText(strVal);
				if (point_x_value >= 0.0)
				{
					strVal.Format("%.2f", e->m_point_x - point_x_value);
					if (m_oqc_enable)
						m_pEdit_OqcTyDertaX->SetText(strVal);
					else
						m_pEdit_TyDertaX->SetText(strVal);
					double threshold_x = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TyDertaXThreshold");
					if (abs(e->m_point_x - point_x_value) <= threshold_x)
					{
						if (m_oqc_enable)
						{
							m_pEdit_OqcTyDertaX->SetBkColor(0xFF00FF00);
							m_pLable_OqcAxis5Advice->SetText((std::string("轴3无需调整")).c_str());
						}
						else
						{
							m_pEdit_TyDertaX->SetBkColor(0xFF00FF00);
							m_pLable_Axis5Advice->SetText((std::string("轴5无需调整")).c_str());
						}
					}
					else
					{
						if (m_oqc_enable)
						{
							m_pEdit_OqcTyDertaX->SetBkColor(0xFFFF0000);
							if (e->m_point_x - point_x_value > 0)
								m_pLable_OqcAxis5Advice->SetText((std::string("轴3向 - 方向调整")).c_str());
							else
								m_pLable_OqcAxis5Advice->SetText((std::string("轴3向 + 方向调整")).c_str());
						}
						else
						{
							m_pEdit_TyDertaX->SetBkColor(0xFFFF0000);
							if (e->m_point_x - point_x_value > 0)
								m_pLable_Axis5Advice->SetText((std::string("轴5向 - 方向调整")).c_str());
							else
								m_pLable_Axis5Advice->SetText((std::string("轴5向 + 方向调整")).c_str());
						}
					}
				}
				strVal.Format("%.2f", e->m_point_y);
				m_pEdit_TyPixel_y->SetText(strVal);
				if (point_y_value >= 0.0)
				{
					strVal.Format("%.2f", e->m_point_y - point_y_value);
					if (m_oqc_enable)
						m_pEdit_OqcTyDertaY->SetText(strVal);
					else
						m_pEdit_TyDertaY->SetText(strVal);
					double threshold_y = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TyDertaYThreshold");
					if (abs(e->m_point_y - point_y_value) <= threshold_y)
					{
						if (m_oqc_enable)
						{
							m_pEdit_OqcTyDertaY->SetBkColor(0xFF00FF00);
							m_pLable_OqcAxis6Advice->SetText((std::string("轴2无需调整")).c_str());
						}
						else
						{
							m_pEdit_TyDertaY->SetBkColor(0xFF00FF00);
							m_pLable_Axis6Advice->SetText((std::string("轴6无需调整")).c_str());
						}
					}
					else
					{
						if (m_oqc_enable)
						{
							m_pEdit_OqcTyDertaY->SetBkColor(0xFFFF0000);
							if (e->m_point_y - point_y_value > 0)
								m_pLable_OqcAxis6Advice->SetText((std::string("轴2向 - 方向调整")).c_str());
							else
								m_pLable_OqcAxis6Advice->SetText((std::string("轴2向 + 方向调整")).c_str());
						}
						else
						{
							m_pEdit_TyDertaY->SetBkColor(0xFFFF0000);
							if (e->m_point_y - point_y_value > 0)
								m_pLable_Axis6Advice->SetText((std::string("轴6向 - 方向调整")).c_str());
							else
								m_pLable_Axis6Advice->SetText((std::string("轴6向 + 方向调整")).c_str());
						}
					}
				}
			}
			else
			{
				double point_x_value;
				double point_y_value;
				if (m_oqc_enable)
				{
					point_x_value = atof(m_pEdit_OqcAlpha_x->GetText().GetData());
					point_y_value = atof(m_pEdit_OqcAlpha_y->GetText().GetData());
				}
				else
				{
					point_x_value = m_alpha_center_x / 2;
					point_y_value = m_alpha_center_y / 2;
				}
				CDuiString strVal;
				strVal.Format("%.2f", e->m_point_x);
				m_pEdit_IdsPixel_x->SetText(strVal);
				strVal.Format("%.2f", e->m_point_x - point_x_value);
				if (m_oqc_enable)
					m_pEdit_OqcAlphaDertaX->SetText(strVal);
				else
					m_pEdit_AlphaDertaX->SetText(strVal);
				double threshold_x = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "IdsDertaXThreshold");		
				if (abs(e->m_point_x - point_x_value) <= threshold_x)
				{
					if (m_oqc_enable)
					{
						m_pEdit_OqcAlphaDertaX->SetBkColor(0xFF00FF00);
						m_pLable_OqcAxis3Advice->SetText((std::string("轴3无需调整")).c_str());
					}
					else
					{
						m_pEdit_AlphaDertaX->SetBkColor(0xFF00FF00);
						m_pLable_Axis3Advice->SetText((std::string("轴3无需调整")).c_str());
					}
				}
				else
				{
					if (m_oqc_enable)
					{
						m_pEdit_OqcAlphaDertaX->SetBkColor(0xFFFF0000);
						if (e->m_point_x - point_x_value > 0)
							m_pLable_OqcAxis3Advice->SetText((std::string("轴3向 - 方向调整")).c_str());
						else
							m_pLable_OqcAxis3Advice->SetText((std::string("轴3向 + 方向调整")).c_str());
					}
					else
					{
						m_pEdit_AlphaDertaX->SetBkColor(0xFFFF0000);
						if (e->m_point_x - point_x_value > 0)
							m_pLable_Axis3Advice->SetText((std::string("轴3向 - 方向调整")).c_str());
						else
							m_pLable_Axis3Advice->SetText((std::string("轴3向 + 方向调整")).c_str());
					}
				}
				strVal.Format("%.2f", e->m_point_y);
				m_pEdit_IdsPixel_y->SetText(strVal);
				strVal.Format("%.2f", e->m_point_y - point_y_value);
				if (m_oqc_enable)
					m_pEdit_OqcAlphaDertaY->SetText(strVal);
				else
					m_pEdit_AlphaDertaY->SetText(strVal);
				double threshold_y = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "IdsDertaYThreshold");
				if (abs(e->m_point_y - point_y_value) <= threshold_y)
				{
					if (m_oqc_enable)
					{
						m_pEdit_OqcAlphaDertaY->SetBkColor(0xFF00FF00);
						m_pLable_OqcAxis4Advice->SetText((std::string("轴1无需调整")).c_str());
					}
					else
					{
						m_pEdit_AlphaDertaY->SetBkColor(0xFF00FF00);
						m_pLable_Axis4Advice->SetText((std::string("轴4无需调整")).c_str());
					}
				}
				else
				{
					if (m_oqc_enable)
					{
						m_pEdit_OqcAlphaDertaY->SetBkColor(0xFFFF0000);
						if (e->m_point_y - point_y_value > 0)
							m_pLable_OqcAxis4Advice->SetText((std::string("轴1向 - 方向调整")).c_str());
						else
							m_pLable_OqcAxis4Advice->SetText((std::string("轴1向 + 方向调整")).c_str());
					}
					else
					{
						m_pEdit_AlphaDertaY->SetBkColor(0xFFFF0000);
						if (e->m_point_y - point_y_value > 0)
							m_pLable_Axis4Advice->SetText((std::string("轴4向 - 方向调整")).c_str());
						else
							m_pLable_Axis4Advice->SetText((std::string("轴4向 + 方向调整")).c_str());
					}
				}
			}
		}
	}
	return 0;
}

void AlphaCalibrationPluginView::OnBtnTxExposureSetClick(TNotifyUI & msg)
{
}

void AlphaCalibrationPluginView::OnBtnTyExposureSetClick(TNotifyUI & msg)
{
}

void AlphaCalibrationPluginView::OnBtnIdsExposureSetClick(TNotifyUI & msg)
{
}

void AlphaCalibrationPluginView::OnBtnTxGainSetClick(TNotifyUI & msg)
{
}

void AlphaCalibrationPluginView::OnBtnTyGainSetClick(TNotifyUI & msg)
{
}

void AlphaCalibrationPluginView::OnBtnIdsGainSetClick(TNotifyUI & msg)
{
}

void AlphaCalibrationPluginView::OnBtnTxParasGetClick(TNotifyUI & msg)
{
}

void AlphaCalibrationPluginView::OnBtnTyParasGetClick(TNotifyUI & msg)
{
}

void AlphaCalibrationPluginView::OnBtnIdsParasGetClick(TNotifyUI & msg)
{
}

void AlphaCalibrationPluginView::OnBtnDeviceOpenClick(TNotifyUI & msg)
{
	if (!m_tx_select && !m_ty_select && !m_ids_select)
	{
		MessageBox(this->GetHWND(), "Please select camera first!", _T("Error"), MB_OK);
		return;
	}
	int ret = 0;
	if (m_tx_select)
	{
		m_pLable_TxStatus->SetBkColor(0xFFFFDB00);
		const char* data_str = "TX";
		ret = jCore->SendEvent(g_HikWidget, &JHikEvent("OpenDevice", (void*)data_str));
		if (ret == 0)
			m_pLable_TxStatus->SetBkColor(0xFF00FF00);
	}
	if (m_ty_select)
	{
		m_pLable_TyStatus->SetBkColor(0xFFFFDB00);
		const char* data_str = "TY";
		ret = jCore->SendEvent(g_HikWidget, &JHikEvent("OpenDevice", (void*)data_str));
		if (ret == 0)
			m_pLable_TyStatus->SetBkColor(0xFF00FF00);
	}
	if (m_ids_select)
	{
		m_pLable_IdsStatus->SetBkColor(0xFFFFDB00);
		ret = jCore->SendEvent(g_IdsWidget, &JIdsEvent("OpenDevice", NULL));
		if (ret == 0)
			m_pLable_IdsStatus->SetBkColor(0xFF00FF00);
	}
	if (ret == 0)
	{
		EnableBtn(true);
		m_pEdit_TxPixel_x->SetText("0");
		m_pEdit_TyPixel_x->SetText("0");
		m_pEdit_IdsPixel_x->SetText("0");
		m_pEdit_TxPixel_y->SetText("0");
		m_pEdit_TyPixel_y->SetText("0");
		m_pEdit_IdsPixel_y->SetText("0");
	}
}

void AlphaCalibrationPluginView::OnBtnDeviceCloseClick(TNotifyUI & msg)
{
	int ret = 0;
	if (m_tx_select)
	{
		const char* data_str = "TX";
		ret = jCore->SendEvent(g_HikWidget, &JHikEvent("CloseDevice", (void*)data_str));
		if (ret == 0)
			m_pLable_TxStatus->SetBkColor(0xFFACACAC);
	}
	if (m_ty_select)
	{
		const char* data_str = "TY";
		ret = jCore->SendEvent(g_HikWidget, &JHikEvent("CloseDevice", (void*)data_str));
		if (ret == 0)
			m_pLable_TyStatus->SetBkColor(0xFFACACAC);
	}
	if (m_ids_select)
	{
		ret = jCore->SendEvent(g_IdsWidget, &JIdsEvent("CloseDevice", NULL));
		if (ret == 0)
			m_pLable_IdsStatus->SetBkColor(0xFFACACAC);
	}
	EnableBtn(false);
	//if (m_tx_select)
	//	m_pLable_Image1->SetBkImage("");
	//if (m_ty_select)
	//	m_pLable_Image2->SetBkImage("");
	//if (m_ids_select)
	//	m_pLable_Image3->SetBkImage("");
	start_camera = false;
}

void AlphaCalibrationPluginView::OnBtnStartGrabClick(TNotifyUI & msg)
{
	int ret = 0;
	if (m_tx_select)
	{
		const char* data_str = "TX";
		ret = jCore->SendEvent(g_HikWidget, &JHikEvent("StartGrab", (void*)data_str));
	}
	if (m_ty_select)
	{
		const char* data_str = "TY";
		ret = jCore->SendEvent(g_HikWidget, &JHikEvent("StartGrab", (void*)data_str));
	}
	if (m_ids_select)
	{
		ret = jCore->SendEvent(g_IdsWidget, &JIdsEvent("StartGrab", NULL));
	}
	if (ret == 0)
	{
		m_pBtn_StopGrab->SetEnabled(true);
		m_pBtn_StartGrab->SetEnabled(false);
		m_pBtn_DeviceClose->SetEnabled(false);
		if (m_tx_select)
		{
			m_pBtn_TxExposureSet->SetEnabled(false);
			m_pBtn_TxGainSet->SetEnabled(false);
			m_pBtn_TxParasGet->SetEnabled(false);
		}
		if (m_ty_select)
		{
			m_pBtn_TyExposureSet->SetEnabled(false);
			m_pBtn_TyGainSet->SetEnabled(false);
			m_pBtn_TyParasGet->SetEnabled(false);
		}
		if (m_ids_select)
		{
			m_pBtn_IdsExposureSet->SetEnabled(false);
			m_pBtn_IdsGainSet->SetEnabled(false);
			m_pBtn_IdsParasGet->SetEnabled(false);
		}
		start_camera = true;
	}
}

void AlphaCalibrationPluginView::OnBtnStopGrabClick(TNotifyUI & msg)
{
	if (m_tx_select)
	{
		const char* data_str = "TX";
		jCore->SendEvent(g_HikWidget, &JHikEvent("StopGrab", (void*)data_str));
	}
	if (m_ty_select)
	{
		const char* data_str = "TY";
		jCore->SendEvent(g_HikWidget, &JHikEvent("StopGrab", (void*)data_str));
	}
	if (m_ids_select)
	{
		jCore->SendEvent(g_IdsWidget, &JIdsEvent("StopGrab", NULL));
	}
	m_pBtn_StopGrab->SetEnabled(false);
	m_pBtn_StartGrab->SetEnabled(true);
	m_pBtn_DeviceClose->SetEnabled(true);
	if (m_tx_select)
	{
		m_pBtn_TxExposureSet->SetEnabled(true);
		m_pBtn_TxGainSet->SetEnabled(true);
		m_pBtn_TxParasGet->SetEnabled(true);
		DisplayTxOneFrameImage(m_last_tx.pLastMem, m_last_tx.nWidth, m_last_tx.nHeight, false);
	}
	if (m_ty_select)
	{
		m_pBtn_TyExposureSet->SetEnabled(true);
		m_pBtn_TyGainSet->SetEnabled(true);
		m_pBtn_TyParasGet->SetEnabled(true);
		DisplayTyOneFrameImage(m_last_ty.pLastMem, m_last_ty.nWidth, m_last_ty.nHeight, false);
	}
	if (m_ids_select)
	{
		m_pBtn_IdsExposureSet->SetEnabled(true);
		m_pBtn_IdsGainSet->SetEnabled(true);
		m_pBtn_IdsParasGet->SetEnabled(true);
		DisplayIdsOneFrameImage(m_last_ids.pLastMem, m_last_ids.nWidth, m_last_ids.nHeight, false);
	}
	start_camera = false;
}

void AlphaCalibrationPluginView::OnCheckTxSelectClick(TNotifyUI & msg)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	if (m_pOp_CameraTxSelect->IsSelected())
		m_tx_select = true;
	else
		m_tx_select = false;	
}

void AlphaCalibrationPluginView::OnCheckTySelectClick(TNotifyUI & msg)
{
	if (m_pOp_CameraTySelect->IsSelected())
		m_ty_select = true;
	else
		m_ty_select = false;
}

void AlphaCalibrationPluginView::OnCheckIdsSelectClick(TNotifyUI & msg)
{
	if (m_pOp_CameraIdsSelect->IsSelected())
		m_ids_select = true;
	else
		m_ids_select = false;
}

void AlphaCalibrationPluginView::OnCheckTxContinueClick(TNotifyUI & msg)
{
	if (m_pOp_TxContinueCapture->IsSelected())
		m_tx_continue = true;
	else
		m_tx_continue = false;
}

void AlphaCalibrationPluginView::OnCheckTyContinueClick(TNotifyUI & msg)
{
	if (m_pOp_TyContinueCapture->IsSelected())
		m_ty_continue = true;
	else
		m_ty_continue = false;
}

void AlphaCalibrationPluginView::OnCheckIdsContinueClick(TNotifyUI & msg)
{
	if (m_pOp_IdsContinueCapture->IsSelected())
		m_ids_continue = true;
	else
		m_ids_continue = false;
}

void AlphaCalibrationPluginView::OnCheckOqcModeClick(TNotifyUI & msg)
{
	if (m_pOp_OqcMode->IsSelected())
		m_oqc_enable = true;
	else
		m_oqc_enable = false;
	m_pBtn_OqcStartTest->SetEnabled(m_oqc_enable);
}

void AlphaCalibrationPluginView::OnOqcStartTestClick(TNotifyUI & msg)
{
	OnBtnStartAutoCalibrationClick(msg);
}

void AlphaCalibrationPluginView::OnRadioOqcTxClick(TNotifyUI & msg)
{
	m_is_tx_calibration = true;
	m_pOp_TxCalibration->Selected(true);
}

void AlphaCalibrationPluginView::OnRadioOqcTyClick(TNotifyUI & msg)
{
	m_is_tx_calibration = false;
	m_pOp_TyCalibration->Selected(true);
}

void AlphaCalibrationPluginView::OnBtnCalibrationConfirmClick(TNotifyUI & msg)
{
	m_pOp_TxContinueCapture->Selected(false);
	m_pOp_TyContinueCapture->Selected(false);
	m_pOp_IdsContinueCapture->Selected(false);
}

void AlphaCalibrationPluginView::OnBtnStartAutoCalibrationClick(TNotifyUI & msg)
{
	// 检查线程是否已经在执行
	if (is_thread_start)
	{
		MessageBox(this->GetHWND(), "Thread on running!", _T("Error"), MB_OK);
		return;
	}
	// 清空显示框
	ClearAutoCalibrationDisplay();
	// 离线模式先选择图片
	if (m_pOp_OfflineMode->IsSelected() && m_offline_image.size() < 0)
	{
		MessageBox(this->GetHWND(), "Please select offline image first!", _T("Error"), MB_OK);
		return;
	}
	// 未启用相机时不进入测试
	if (!start_camera && !m_offline)
	{
		MessageBox(this->GetHWND(), "Please start camera first!", _T("Error"), MB_OK);
		return;
	}
	std::thread t(&AlphaCalibrationPluginView::StartAutoCalibrationAsync, this);
	t.detach();
	is_thread_start = true;
}

void AlphaCalibrationPluginView::OnBtnSelectOfflineImageClick(TNotifyUI & msg)
{
	m_offline_image = chooseFiles();
}

void AlphaCalibrationPluginView::OnCheckOfflineClick(TNotifyUI & msg)
{
	if (m_pOp_OfflineMode->IsSelected())
		m_offline = true;
	else
		m_offline = false;
}

void AlphaCalibrationPluginView::OnRadioTxClick(TNotifyUI & msg)
{
	m_is_tx_calibration = true;
	m_pOp_OqcTxCalibration->Selected(true);
}

void AlphaCalibrationPluginView::OnRadioTyClick(TNotifyUI & msg)
{
	m_is_tx_calibration = false;
	m_pOp_OqcTyCalibration->Selected(true);
}

void AlphaCalibrationPluginView::DisplayTxOneFrameImage(unsigned char * pData, unsigned short nWidth, unsigned short nHeight, bool is_online)
{
	m_pLable_Image1->SetBkImage("");

	HBITMAP hBmp = ConvertCharToHBITMAP("TX", (char*)pData, nWidth, nHeight, is_online);

	CDuiString sCtrlKey = "ImageTx";
	m_PaintManager.RemoveImage(sCtrlKey, true);
	m_PaintManager.AddImage(sCtrlKey, hBmp, nWidth, nHeight, false, true);
	m_PaintManager.ReloadSharedImages();
	m_pLable_Image1->SetBkImage(sCtrlKey);

	if (is_online)
	{
		// 记录最后一张图片
		m_last_tx.pLastMem = pData;
		m_last_tx.nWidth = nWidth;
		m_last_tx.nHeight = nHeight;
	}

	// 连续计算(放入异步线程中，未算完不执行下一帧计算，只连续显示)
	if (m_tx_continue && (!m_tx_thread.valid() || m_tx_thread._Is_ready()))
	{
		m_tx_thread = std::async(std::launch::async, &AlphaCalibrationPluginView::GetTxCameraPixelResult, this, true);
	}
}

void AlphaCalibrationPluginView::DisplayTyOneFrameImage(unsigned char * pData, unsigned short nWidth, unsigned short nHeight, bool is_online)
{
	m_pLable_Image2->SetBkImage("");

	HBITMAP hBmp = ConvertCharToHBITMAP("TY", (char*)pData, nWidth, nHeight, is_online);

	CDuiString sCtrlKey = "ImageTy";
	m_PaintManager.RemoveImage(sCtrlKey, true);
	m_PaintManager.AddImage(sCtrlKey, hBmp, nWidth, nHeight, false, true);
	m_PaintManager.ReloadSharedImages();
	m_pLable_Image2->SetBkImage(sCtrlKey);

	if (is_online)
	{
		// 记录最后一张图片
		m_last_ty.pLastMem = pData;
		m_last_ty.nWidth = nWidth;
		m_last_ty.nHeight = nHeight;
	}

	// 连续计算(放入异步线程中，未算完不执行下一帧计算，只连续显示)
	if (m_ty_continue && (!m_ty_thread.valid() || m_ty_thread._Is_ready()))
	{
		m_ty_thread = std::async(std::launch::async, &AlphaCalibrationPluginView::GetTyCameraPixelResult, this, true);
	}
}

void AlphaCalibrationPluginView::DisplayIdsOneFrameImage(unsigned char * pData, unsigned short nWidth, unsigned short nHeight, bool is_online)
{
	m_pLable_Image3->SetBkImage("");

	HBITMAP hBmp = ConvertCharToHBITMAP("IDS", (char*)pData, nWidth, nHeight, is_online);

	CDuiString sCtrlKey = "ImageIds";
	m_PaintManager.RemoveImage(sCtrlKey, true);
	m_PaintManager.AddImage(sCtrlKey, hBmp, nWidth, nHeight, false, true);
	m_PaintManager.ReloadSharedImages();
	m_pLable_Image3->SetBkImage(sCtrlKey);

	if (is_online)
	{
		// 记录最后一张图片
		m_last_ids.pLastMem = pData;
		m_last_ids.nWidth = nWidth;
		m_last_ids.nHeight = nHeight;
	}

	// 连续计算(放入异步线程中，未算完不执行下一帧计算，只连续显示)
	if (m_ids_continue && (!m_ids_thread.valid() || m_ids_thread._Is_ready()))
	{
		m_ids_thread = std::async(std::launch::async, &AlphaCalibrationPluginView::GetIdsCameraPixelResult, this, true);
	}
}

HBITMAP AlphaCalibrationPluginView::ConvertCharToHBITMAP(std::string camera_name, char * imageData, int width, int height, bool is_online)
{
	// 创建一个Mat对象（原图8位深，用CV_8UC1）
	cv::Mat img(height, width, CV_8UC1, imageData);
	if (img.data == NULL)
	{
		return HBITMAP();
	}

	// 转换成24位RGB格式
	cv::cvtColor(img, img, CV_GRAY2RGB);

	cv::Scalar status_color;
	if (is_online)
		status_color = cv::Scalar(0, 255, 0);
	else
		status_color = cv::Scalar(192, 192, 192);

	if (camera_name == "IDS")
	{
		// 画十字
		cv::line(img, cv::Point(width / 2 - 50, height / 2), cv::Point(width / 2 + 50, height / 2), cv::Scalar(0, 0, 255), 5);
		cv::line(img, cv::Point(width / 2, height / 2 - 50), cv::Point(width / 2, height / 2 + 50), cv::Scalar(0, 0, 255), 5);
		// 画矩形
		cv::rectangle(img, cv::Point(width / 2 - 300, height / 2 - 300), cv::Point(width / 2 + 300, height / 2 + 300), cv::Scalar(0, 0, 255), 2);
		// 画圆点表示相机是否在线
		circle(img, cv::Point2f(60, 90), 30, status_color, -1, 8, 1);
		// 画相机名
		cv::putText(img, camera_name, cv::Point(70, 65), cv::FONT_HERSHEY_COMPLEX, 2.0, cv::Scalar(0, 0, 255), 3);
	}
	else
	{
		// 画圆点表示相机是否在线
		circle(img, cv::Point2f(85, 130), 60, status_color, -1, 8, 1);
		// 画相机名
		cv::putText(img, camera_name, cv::Point(100, 130), cv::FONT_HERSHEY_COMPLEX, 5.0, cv::Scalar(0, 0, 255), 3);
	}

	// 创建BITMAPINFO
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;

	// 创建HBITMAP
	//HDC hdc = GetDC(NULL);
	void* bits;
	HBITMAP hbm = CreateDIBSection(/*hdc*/NULL, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
	//ReleaseDC(NULL, hdc);

	// 将数据复制到HBITMAP
	if (hbm) {
		memcpy(bits, img.data, width * height * 3); // RGB每个像素3字节
	}

	return hbm;
}

void AlphaCalibrationPluginView::ClearAutoCalibrationDisplay()
{
	m_pEdit_Pos1PointX->SetText("");
	m_pEdit_Pos2PointX->SetText("");
	m_pEdit_Pos3PointX->SetText("");
	m_pEdit_Pos1PointY->SetText("");
	m_pEdit_Pos2PointY->SetText("");
	m_pEdit_Pos3PointY->SetText("");
	m_pEdit_PointX->SetText("");
	m_pEdit_PointY->SetText("");
	m_pEdit_PointR->SetText("");
	m_circle_point_x = -1.0;
	m_circle_point_y = -1.0;
}

void AlphaCalibrationPluginView::GetAutoCalibrationPosInfos(std::string& cur_cam, double & pos1, double & pos2, double & pos3)
{
	if (m_is_tx_calibration)
	{
		cur_cam = "TX";
		pos1 = std::atof(m_pEdit_TxPos1->GetText().GetData());
		pos2 = std::atof(m_pEdit_TxPos2->GetText().GetData());
		pos3 = std::atof(m_pEdit_TxPos3->GetText().GetData());
	}
	else if (m_ty_select)
	{
		cur_cam = "TY";
		pos1 = std::atof(m_pEdit_TyPos1->GetText().GetData());
		pos2 = std::atof(m_pEdit_TyPos2->GetText().GetData());
		pos3 = std::atof(m_pEdit_TyPos3->GetText().GetData());
	}
}

double AlphaCalibrationPluginView::GetImgQualityScore(cv::Mat src, int flag)
{
	cv::Mat imgLaplance;
	cv::Mat imageSobel;
	cv::Mat meanValueImage;
	cv::Mat meanImage;
	cv::Mat BlurMat;
	cv::Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	//中值模糊 降低图像噪音
	//Cv2.MedianBlur(gray, BlurMat, 5);
	boxFilter(gray, BlurMat,CV_8UC3, cv::Size(11, 11));
	std::string method;
	double meanValue = 0;
	if (flag == 1)
	{
		//方差法
		meanStdDev(BlurMat, meanValueImage, meanImage);
		meanValue = meanImage.at<double>(0, 0);
		method = "MeanStdDev";
	}
	else if (flag == 0)
	{
		//拉普拉斯
		Laplacian(BlurMat, imgLaplance, CV_16S, 5, 1);
		convertScaleAbs(imgLaplance, imgLaplance);
		//结果放大两倍,拉开差距
		meanValue = mean(imgLaplance)[0] * 10;
		method = "Laplacian";
	}
	else
	{
		//索贝尔
		Sobel(BlurMat, imageSobel, CV_16S, 3, 3, 5);
		convertScaleAbs(imageSobel, imageSobel);
		//结果放大两倍,拉开差距
		meanValue = mean(imageSobel)[0] * 10;
		method = "Sobel";

	}
	//Cv2.Sobel(gray, imgSobel, MatType.CV_16U, 2, 2);
	//meanValue2 = Cv2.Mean(imgSobel)[0];
	//CDuiString methodStr;
	//methodStr.Format("(%s Method): %s", method, meanValue);
	//cv::putText(src, std::string(methodStr), cv::Point(1, 20), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 1);
	cv::imshow(method, src);
	return meanValue;
}

void AlphaCalibrationPluginView::GetCameraImgQualityScore(std::string camera_name, bool is_continues)
{
	std::string image_path;
	if (is_continues)
		image_path = jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "ImageOutputPath") + "TX_AliveGet";
	else
		image_path = jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "ImageOutputPath") + "TX_" + Jup::GetLocalTime(3);
	jCore->SendEvent(g_HikWidget, &JHikEvent("SaveOneFrame", (void*)image_path.c_str()));

	cv::Mat src = cv::imread(image_path);
	double value = GetImgQualityScore(src);
	CDuiString strVal;
	strVal.Format("%.2f", value);
	//m_pEdit_Focal->SetText(strVal);
}

void AlphaCalibrationPluginView::GetPosImagePointResult(std::string current_cam, double distance, double & point_x, double & point_y)
{
	std::string image_pos;
	if (m_pOp_OfflineMode->IsSelected())
		image_pos = m_offline_image[0];
	else
	{
		std::string axis_name;
		double speed_ratio;
		if (current_cam == "TX")
		{
			axis_name = "AxisTx";
			speed_ratio = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TxAxisSpeedRatio");
		}
		else
		{
			axis_name = "AxisTy";
			speed_ratio = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TyAxisSpeedRatio");
		}
		// 移动到点位（发消息）
		JMotionEvent motionEvent(axis_name.c_str(), distance, speed_ratio);
		jCore->SendEvent(g_MotionWidget, &motionEvent);
		Sleep(1000);
		// 获取点位图片（发消息）
		image_pos = jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "ImageOutputPath") + current_cam + "_" + Jup::GetLocalTime(3);
		jCore->SendEvent(g_HikWidget, &JHikEvent("SaveOneFrame", (void*)image_pos.c_str()));
	}
	// 计算第一个点位图片
	GetCirclePixelResult(current_cam, image_pos + ".bmp", point_x, point_y, true);
}

bool AlphaCalibrationPluginView::GetCirclePixelResult(std::string camera_name, std::string file_name, double & point_x, double & point_y, bool wait_result)
{
	// MIL计算坐标
	std::string file_mmf;
	if (camera_name == "TX")
		file_mmf = "./Config/TX.mmf";
	else if (camera_name == "TY")
		file_mmf = "./Config/TY.mmf";
	else
		file_mmf = "./Config/IDS.mmf";
	JMilFindModelEvent milEvent(file_name, file_mmf, wait_result);
	jCore->SendEvent(g_MilWidget, &milEvent);
	if (wait_result)
	{
		point_x = milEvent.m_pointX;
		point_y = milEvent.m_pointY;
	}
	return true;
}

bool AlphaCalibrationPluginView::GetCircleCenterResult(std::string camera_name, CEditUI* result_edit, double val1, double val2, double val3, bool wait_result)
{
	double threshold;
	if (camera_name == "TX")
		threshold = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TxResultThreshold");
	else
		threshold = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TyResultThreshold");
	double max, min;
	max = min = val1;
	if (val2 > max)
		max = val2;
	if (val3 > max)
		max = val3;
	if (val2 < min)
		min = val2;
	if (val3 < min)
		min = val3;

	double result = max - min;

	CDuiString strVal;
	strVal.Format("%.2f", result);
	result_edit->SetText(strVal);
	if (result <= threshold)
		result_edit->SetBkColor(0xFF00FF00);
	else
		result_edit->SetBkColor(0xFFFF0000);
	return result <= threshold ? true : false;
}

std::string AlphaCalibrationPluginView::ScalarCircle(std::string camera_name, double x1, double y1, double x2, double y2, double x3, double y3, double center_x, double center_y, double center_r)
{
	if (x1 < 0.0 || y1 < 0.0 || x2 < 0.0 || y2 < 0.0 || x3 < 0.0 || y3 < 0.0 || center_x <= 0.0 || center_y <= 0.0 || center_r <= 0.0 || center_x >= (2448-300) || center_y >= (2048 - 300))
	{
		return "";
	}
	try
	{
		//初始化一张图片，全部为黑色
		cv::Mat dst(2048, 2448, CV_8UC3, cv::Scalar(0, 0, 0));
		//随便定义三个点
		cv::Point2f p1, p2, p3;
		p1.x = x1;
		p1.y = y1;
		p2.x = x2;
		p2.y = y2;
		p3.x = x3;
		p3.y = y3;
		//画出三个点
		circle(dst, p1, 3, cv::Scalar(0, 0, 255), -1, 8, 0);
		circle(dst, p2, 3, cv::Scalar(0, 255, 255), -1, 8, 0);
		circle(dst, p3, 3, cv::Scalar(255, 255, 128), -1, 8, 0);
		//定义一个圆的数据结构体对象
		cv::Point2f CD;
		CD.x = center_x;
		CD.y = center_y;
		circle(dst, CD, 3, cv::Scalar(255, 255, 255), -1, 8, 0);//画出圆心
		circle(dst, CD, center_r, cv::Scalar(0, 255, 0), 1, 8, 0);//画出圆
		// 裁剪图片
		cv::Rect area(center_x - 300, center_y - 300, 600, 600);
		cv::Mat cropped_image = dst(area);
		// 画坐标
		CDuiString circleStr;
		circleStr.Format("Pos1:(%.2f,%.2f)", x1, y1);
		cv::putText(cropped_image, std::string(circleStr), cv::Point(1, 525), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 0, 255), 2);
		circleStr.Format("Pos2:(%.2f,%.2f)", x2, y2);
		cv::putText(cropped_image, std::string(circleStr), cv::Point(1, 555), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 255), 2);
		circleStr.Format("Pos3:(%.2f,%.2f)", x3, y3);
		cv::putText(cropped_image, std::string(circleStr), cv::Point(1, 585), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 128), 2);
		circleStr.Format("Fitting:(%.2f,%.2f)", center_x, center_y);
		cv::putText(cropped_image, std::string(circleStr), cv::Point(230, 330), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);
		// 画相机名
		cv::putText(cropped_image, camera_name, cv::Point(5, 35), cv::FONT_HERSHEY_SIMPLEX, 1.2, cv::Scalar(0, 0, 255), 2);
		// 显示图片
		cv::Mat new_image;
		cv::resize(cropped_image, new_image, cv::Size(420, 420));
		std::string default_path = jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "ImageOutputPath");
		std::string file_name = default_path + camera_name + "_" + Jup::GetLocalTime(3) + ".bmp";
		return cv::imwrite(file_name, new_image) ? file_name : "";
	}
	catch (const std::exception& e)
	{
		throw e.what();
	}
}

void AlphaCalibrationPluginView::GetTxCameraPixelResult(bool is_continues)
{
	std::string image_path;
	if (is_continues)
		image_path = jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "ImageOutputPath") + "TX_AliveGet";
	else
		image_path = jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "ImageOutputPath") + "TX_" + Jup::GetLocalTime(3);
	jCore->SendEvent(g_HikWidget, &JHikEvent("SaveOneFrame", (void*)image_path.c_str()));

	double point_x = 0.0;
	double point_y = 0.0;
	GetCirclePixelResult("TX", image_path + ".bmp", point_x, point_y);
	//CDuiString strVal;
	//strVal.Format("%.2f", point_x);
	//m_pEdit_TxPixel_x->SetText(strVal);
	//strVal.Format("%.2f", point_y);
	//m_pEdit_TxPixel_y->SetText(strVal);
}

void AlphaCalibrationPluginView::GetTyCameraPixelResult(bool is_continues)
{
	std::string image_path;
	if (is_continues)
		image_path = jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "ImageOutputPath") + "TY_AliveGet";
	else
		image_path = jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "ImageOutputPath") + "TY_" + Jup::GetLocalTime(3);
	jCore->SendEvent(g_HikWidget, &JHikEvent("SaveOneFrame", (void*)image_path.c_str()));

	double point_x = 0.0;
	double point_y = 0.0;
	GetCirclePixelResult("TY", image_path + ".bmp", point_x, point_y);
	//CDuiString strVal;
	//strVal.Format("%.2f", point_x);
	//m_pEdit_TyPixel_x->SetText(strVal);
	//strVal.Format("%.2f", point_y);
	//m_pEdit_TyPixel_y->SetText(strVal);
}

void AlphaCalibrationPluginView::GetIdsCameraPixelResult(bool is_continues)
{
	std::string image_path;
	if (is_continues)
		image_path = jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "ImageOutputPath") + "Ids_AliveGet.bmp";
	else
		image_path = jCore->GlobalSettings().ReadString("AlphaAutoCalibration", "ImageOutputPath") + "IDS_" + Jup::GetLocalTime(3) + ".bmp";
	jCore->SendEvent(g_IdsWidget, &JIdsEvent("SaveOneFrame", image_path.c_str()));

	double point_x = 0.0;
	double point_y = 0.0;
	GetCirclePixelResult("IDS", image_path, point_x, point_y);
	//CDuiString strVal;
	//strVal.Format("%.2f", point_x);
	//m_pEdit_IdsPixel_x->SetText(strVal);
	//strVal.Format("%.2f", point_y);
	//m_pEdit_IdsPixel_y->SetText(strVal);
}

std::vector<std::string> AlphaCalibrationPluginView::chooseFiles()
{
	OPENFILENAME ofn;
	TCHAR szOpenFileNames[80 * MAX_PATH] = { 0 };
	TCHAR szPath[MAX_PATH];
	TCHAR szFileName[80 * MAX_PATH];
	int nLen = 0;
	TCHAR* p = NULL;
	ZeroMemory(&ofn, sizeof(ofn));
	// 结构体大小
	ofn.lStructSize = sizeof(ofn);
	// 拥有着窗口句柄
	ofn.hwndOwner = NULL;
	// 接收返回的文件名，注意第一个字符需要为NULL
	ofn.lpstrFile = szOpenFileNames;
	// 缓冲区长度
	ofn.nMaxFile = sizeof(szOpenFileNames);
	// _T可替换为TEXT，使用_T需要引tchar.h
	ofn.lpstrFile[0] = _T('\0');
	// 设置过滤
	ofn.lpstrFilter = _T("All\0*.*\0*.bmp\0\0");
	// 过滤器索引
	ofn.nFilterIndex = 1;
	// 窗口标题
	ofn.lpstrTitle = _T("Select Image:");
	// 文件必须存在、允许多选、隐藏只读选项、对话框使用资源管理器风格的用户界面
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_EXPLORER | OFN_NOCHANGEDIR;
	// 如果打开文件失败，则不操作
	if (!::GetOpenFileName(&ofn)) {
		return std::vector<std::string>();
	}
	// 把第一个文件名前的复制到szPath,即:  
	// 如果只选了一个文件,就复制到最后一个'/'  
	// 如果选了多个文件,就复制到第一个NULL字符  
	lstrcpyn(szPath, szOpenFileNames, ofn.nFileOffset);
	// 当只选了一个文件时,下面这个NULL字符是必需的.  
	// 这里不区别对待选了一个和多个文件的情况
	szPath[ofn.nFileOffset] = '\0';
	nLen = lstrlen(szPath);
	// 如果选了多个文件,则必须加上'//'  
	if (szPath[nLen - 1] != '\\') {
		lstrcat(szPath, _T("\\"));
	}
	// 把指针移到第一个文件  
	p = szOpenFileNames + ofn.nFileOffset;
	// 对szFileName进行清零
	ZeroMemory(szFileName, sizeof(szFileName));
	// 定义字符串，用于拼接所选的所有文件的完整路径
	std::vector<std::string> strVec;
	while (*p) {
		// 读取文件名
		std::string fileName = p;
		// 读取文件所在文件夹路径
		std::string filePath = szPath;
		// 拼接文件完整路径
		std::string completePath = filePath + fileName;
		// 记录文件路径
		Jup::Replace(completePath, "\\", "/");
		strVec.push_back(completePath);
		//移至下一个文件
		p += lstrlen(p) + 1;
	}
	return strVec;
}

void AlphaCalibrationPluginView::StartAutoCalibrationAsync()
{
	// 先关闭实时计算
	bool tx_select = m_tx_select;
	bool ty_select = m_ty_select;
	bool ids_select = m_ids_select;
	if (m_pOp_TxContinueCapture->IsSelected())
		m_pOp_TxContinueCapture->Selected(false);
	if (m_pOp_TyContinueCapture->IsSelected())
		m_pOp_TyContinueCapture->Selected(false);
	if (m_pOp_IdsContinueCapture->IsSelected())
		m_pOp_IdsContinueCapture->Selected(false);

	// 获取运动点位信息
	std::string current_cam;
	double distance_pos1;
	double distance_pos2;
	double distance_pos3;
	GetAutoCalibrationPosInfos(current_cam, distance_pos1, distance_pos2, distance_pos3);

	// 执行第一个点位
	double point1_x;
	double point1_y;
	GetPosImagePointResult(current_cam, distance_pos1, point1_x, point1_y);
	CDuiString strVal;
	strVal.Format("%.2f", point1_x);
	m_pEdit_Pos1PointX->SetText(strVal);
	strVal.Format("%.2f", point1_y);
	m_pEdit_Pos1PointY->SetText(strVal);

	// 执行第二个点位
	double point2_x;
	double point2_y;
	GetPosImagePointResult(current_cam, distance_pos2, point2_x, point2_y);
	strVal.Format("%.2f", point2_x);
	m_pEdit_Pos2PointX->SetText(strVal);
	strVal.Format("%.2f", point2_y);
	m_pEdit_Pos2PointY->SetText(strVal);

	// 执行第三个点位
	double point3_x;
	double point3_y;
	GetPosImagePointResult(current_cam, distance_pos3, point3_x, point3_y);
	strVal.Format("%.2f", point3_x);
	m_pEdit_Pos3PointX->SetText(strVal);
	strVal.Format("%.2f", point3_y);
	m_pEdit_Pos3PointY->SetText(strVal);

	// 获取三个点计算结果（Max-Min 与阈值比较）
	bool point_x_result = false;
	bool point_y_result = false;
	if (m_is_tx_calibration)
	{
		if (m_oqc_enable)
			point_x_result = GetCircleCenterResult(current_cam, m_pEdit_OqcTxResultX, point1_x, point2_x, point3_x);
		else
			point_x_result = GetCircleCenterResult(current_cam, m_pEdit_TxResultX, point1_x, point2_x, point3_x);
	}
	else
	{
		if (m_oqc_enable)
			point_x_result = GetCircleCenterResult(current_cam, m_pEdit_OqcTyResultX, point1_x, point2_x, point3_x);
		else
			point_x_result = GetCircleCenterResult(current_cam, m_pEdit_TyResultX, point1_x, point2_x, point3_x);
	}

	if (m_is_tx_calibration)
	{
		if (m_oqc_enable)
			point_y_result = GetCircleCenterResult(current_cam, m_pEdit_OqcTxResultY, point1_y, point2_y, point3_y);
		else
			point_y_result = GetCircleCenterResult(current_cam, m_pEdit_TxResultY, point1_y, point2_y, point3_y);
	}	
	else
	{
		if (m_oqc_enable)
			point_y_result = GetCircleCenterResult(current_cam, m_pEdit_OqcTyResultY, point1_y, point2_y, point3_y);
		else
			point_y_result = GetCircleCenterResult(current_cam, m_pEdit_TyResultY, point1_y, point2_y, point3_y);
	}
	
	// 计算拟合圆心坐标
	JMilFindCenterEvent milEvent(point1_x, point1_y, point2_x, point2_y, point3_x, point3_y);
	jCore->SendEvent(g_MilWidget, &milEvent);
	strVal.Format("%.2f", milEvent.m_pointX);
	m_pEdit_PointX->SetText(strVal);
	strVal.Format("%.2f", milEvent.m_pointY);
	m_pEdit_PointY->SetText(strVal);
	strVal.Format("%.2f", milEvent.m_pointR);
	m_pEdit_PointR->SetText(strVal);
	std::string image_name = ScalarCircle(current_cam, point1_x, point1_y, point2_x, point2_y, point3_x, point3_y, milEvent.m_pointX, milEvent.m_pointY, milEvent.m_pointR);
	CDuiString imageStr;
	imageStr.Format("file='%s' dest='40,0,460,420'", image_name.c_str());
	if (current_cam == "TX")
		m_pLable_Image4->SetAttribute("bkimage", imageStr);
	else
		m_pLable_Image5->SetAttribute("bkimage", imageStr);

	// 计算补偿偏移值 （X_Center-X2  Y_Center-Y2）
	m_circle_point_x = milEvent.m_pointX;
	m_circle_point_y = milEvent.m_pointY;
	double derta_x = point2_x - m_circle_point_x;
	double derta_y = point2_y - m_circle_point_y;
	if (m_is_tx_calibration)
	{
		if (!m_oqc_enable)
		{
			strVal.Format("%.2f", derta_x);
			m_pEdit_TxDertaX->SetText(strVal);
			double threshold_x = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TxDertaXThreshold");
			if (abs(derta_x) <= threshold_x)
				m_pEdit_TxDertaX->SetBkColor(0xFF00FF00);
			else
				m_pEdit_TxDertaX->SetBkColor(0xFFFF0000);
			strVal.Format("%.2f", derta_y);
			m_pEdit_TxDertaY->SetText(strVal);
			double threshold_y = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TxDertaYThreshold");
			if (abs(derta_y) <= threshold_y)
				m_pEdit_TxDertaY->SetBkColor(0xFF00FF00);
			else
				m_pEdit_TxDertaY->SetBkColor(0xFFFF0000);
		}
	}
	else
	{
		if (!m_oqc_enable)
		{
			strVal.Format("%.2f", derta_x);
			m_pEdit_TyDertaX->SetText(strVal);
			double threshold_x = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TyDertaXThreshold");
			if (abs(derta_x) <= threshold_x)
				m_pEdit_TyDertaX->SetBkColor(0xFF00FF00);
			else
				m_pEdit_TyDertaX->SetBkColor(0xFFFF0000);
			strVal.Format("%.2f", derta_y);
			m_pEdit_TyDertaY->SetText(strVal);
			double threshold_y = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TyDertaYThreshold");
			if (abs(derta_y) <= threshold_y)
				m_pEdit_TyDertaY->SetBkColor(0xFF00FF00);
			else
				m_pEdit_TyDertaY->SetBkColor(0xFFFF0000);
		}
	}

	if (point_x_result && point_y_result)
	{
		// 判断结果，X,Y都小于阈值时，实时计算拟合中心坐标改为三点重心
		m_circle_point_x = (point1_x + point2_x + point3_x) / 3;
		m_circle_point_y = (point1_y + point2_y + point3_y) / 3;
	}

	is_thread_start = false;
    
	// 回到点位2
	if (!m_pOp_OfflineMode->IsSelected())
	{
		// 移动到点位2（发消息）
		std::string axis_name;
		double speed_ratio;
		if (m_is_tx_calibration)
		{
			axis_name = "AxisTx";
			speed_ratio = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TxAxisSpeedRatio");
		}
		else
		{
			axis_name = "AxisTy";
			speed_ratio = jCore->GlobalSettings().ReadDouble("AlphaAutoCalibration", "TyAxisSpeedRatio");
		}
		JMotionEvent motionEvent(axis_name.c_str(), distance_pos2, speed_ratio);
		jCore->SendEvent(g_MotionWidget, &motionEvent);
	}

	// 开启实时计算
	if (tx_select && m_is_tx_calibration)
		m_pOp_TxContinueCapture->Selected(true);
	if (ty_select && !m_is_tx_calibration)
		m_pOp_TyContinueCapture->Selected(true);
	if (ids_select && m_is_tx_calibration)
		m_pOp_IdsContinueCapture->Selected(true);
}

void AlphaCalibrationPluginView::EnableBtn(bool is_enable)
{
	m_pOp_CameraTxSelect->SetEnabled(!is_enable);
	m_pOp_CameraTySelect->SetEnabled(!is_enable);
	m_pOp_CameraIdsSelect->SetEnabled(!is_enable);
	if (m_tx_select)
	{
		m_pBtn_TxExposureSet->SetEnabled(is_enable);
		m_pBtn_TxGainSet->SetEnabled(is_enable);
		m_pBtn_TxParasGet->SetEnabled(is_enable);
	}
	if (m_ty_select)
	{
		m_pBtn_TyExposureSet->SetEnabled(is_enable);
		m_pBtn_TyGainSet->SetEnabled(is_enable);
		m_pBtn_TyParasGet->SetEnabled(is_enable);
	}
	if (m_ids_select)
	{
		m_pBtn_IdsExposureSet->SetEnabled(is_enable);
		m_pBtn_IdsGainSet->SetEnabled(is_enable);
		m_pBtn_IdsParasGet->SetEnabled(is_enable);
	}
	m_pBtn_DeviceOpen->SetEnabled(!is_enable);
	m_pBtn_DeviceClose->SetEnabled(is_enable);
	m_pBtn_StartGrab->SetEnabled(is_enable);
	if (!is_enable)
	{
		m_pBtn_StopGrab->SetEnabled(false);
	}
}
