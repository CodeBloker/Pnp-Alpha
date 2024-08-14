#include "HIPAMainWidget.h"

#include <future>
#include "JupCore.h"
#include "../_INCLUDE/ProjectEvent.h"
using namespace ProjectEvent;

HIPAMainWidget::HIPAMainWidget()
{
	m_hikCamera = HIPACamera::GetInstance();
}

HIPAMainWidget::~HIPAMainWidget()
{
	if (m_hikCamera)
	{
		std::vector<std::string> cameraList = m_hikCamera->EnumDevice();
		for (auto camera : cameraList)
		{
			m_hikCamera->CloseDivice(camera);
		}
	}
}

UILIB_RESOURCETYPE HIPAMainWidget::GetResourceType() const
{
	return UILIB_ZIP;
}

CDuiString HIPAMainWidget::GetSkinFolder()
{
	return "";
}

CDuiString HIPAMainWidget::GetSkinFile()
{
	return "main_frame.xml";
}

CDuiString HIPAMainWidget::GetZIPFileName() const
{
	return _T("PluginHIK.zip");
}

LPCTSTR HIPAMainWidget::GetWindowClassName() const
{
	return "HIPAMainWidget";
}

LRESULT HIPAMainWidget::ResponseDefaultKeyEvent(WPARAM wParam)
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

void HIPAMainWidget::InitWindow()
{	
	jCore->RegisterEventWindow(g_HikWidget, this);

	m_pCombo_DeviceList = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("cmb_DeviceList")));
	m_pBtn_DeviceSerch = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_DeviceSerch")));
	m_pBtn_DeviceOpen = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_DeviceOpen")));
	m_pBtn_DeviceClose = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_DeviceClose")));
	m_pBtn_DeviceStart = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_StartGrab")));
	m_pBtn_DeviceStop = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_StopGrab")));
	m_pBtn_SoftOnce = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_SoftOnce")));

	m_pLable_Image = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("hik_image")));
	m_pEdit_Gain = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_gain")));
	m_pEdit_ExposureTime = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_exposureTime")));
	m_pEdit_FrameRate = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_frameRate")));
	m_pEdit_Sharpness = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_sharpness")));
	m_pEdit_Gamma = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_gamma")));
	m_pOp_ContinueMode = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_ContinueMode")));
	m_pOp_SwTriggerMode = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_SwTriggerMode")));
	m_pOp_HwTriggerMode = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_HwTriggerMode")));

	std::vector<std::string> cameraList = m_hikCamera->EnumDevice();
	for (auto camera : cameraList)
	{
		CListLabelElementUI* item = new CListLabelElementUI;
		item->SetText(camera.c_str());
		item->SetFixedHeight(26);
		m_pCombo_DeviceList->Add(item);
	}
	m_pCombo_DeviceList->SelectItem(0);
	m_pBtn_DeviceStop->SetEnabled(false);
	m_pBtn_DeviceSerch->SetEnabled(false);
	m_pBtn_SoftOnce->SetEnabled(false);
}

void HIPAMainWidget::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	PostQuitMessage(0);
}

void HIPAMainWidget::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		OnBtnClick(msg);
	}
	if (msg.sType == DUI_MSGTYPE_ITEMSELECT && msg.pSender->GetName() == _T("cmb_DeviceList"))
	{
		m_curCamera = m_pCombo_DeviceList->GetText().GetData();
	}
}

CControlUI * HIPAMainWidget::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT HIPAMainWidget::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
	}
	//if (uMsg == WM_USER_DISPLAY_IMAGE)
	//{
	//	DisplayOneFrameImage((MV_DISPLAY_FRAME_INFO*)lParam);
	//}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT HIPAMainWidget::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	int ret = MessageBoxA(NULL, "是否退出程序？", "Quit", MB_YESNO);
	if (ret == IDYES)
		bHandled = FALSE;	//TRUE表示不处理
	else
		bHandled = TRUE;
	return 0;
}

LRESULT HIPAMainWidget::CustomEvent(JupCustomEvent * event)
{
	JupCustomEvent::eType type = event->Type();
	if (type == ProjectEvent::e_JHikEvent)
	{
		auto e = dynamic_cast<JHikEvent*>(event);
		if (0 == strcmp(e->m_command, "DisplayOnceFrame"))
		{
			DisplayOneFrameImage((MV_DISPLAY_FRAME_INFO*)e->m_ptr);
		}
		else if (0 == strcmp(e->m_command, "OpenDevice"))
		{
			m_curCamera = (const char*)e->m_ptr;
			TNotifyUI msg;
			CDuiString str;
			int nRet = m_hikCamera->OpenDevice(m_curCamera);
			if (nRet != MV_OK)
			{
				str.Format("OpenDevice %s failed!", m_curCamera);
				MessageBox(this->GetHWND(), str, _T("Error"), MB_OK);
				return -1;
			}
			// 修改触发源
			nRet = m_hikCamera->SetTriggerSource(m_curCamera, false);
			if (nRet != MV_OK)
			{
				str.Format("%s SetTriggerSource failed!", m_curCamera);
				MessageBox(this->GetHWND(), str, _T("Error"), MB_OK);
				return -2;
			}
			// 修改触发模式
			nRet = m_hikCamera->SetTriggerMode(m_curCamera, false);
			if (nRet != MV_OK)
			{
				str.Format("%s SetTriggerMode failed!", m_curCamera);
				MessageBox(this->GetHWND(), str, _T("Error"), MB_OK);
				return -3;
			}
			str.Format("Open camera %s success", m_curCamera);
			MessageBox(this->GetHWND(), str, _T("Tips"), MB_OK);
		}
		else if (0 == strcmp(e->m_command, "CloseDevice"))
		{
			m_curCamera = (const char*)e->m_ptr;
			TNotifyUI msg;
			CDuiString str;
			int ret = m_hikCamera->CloseDivice(m_curCamera);
			if (ret != MV_OK)
			{
				str.Format("CloseDivice %s failed!", m_curCamera);
				MessageBox(this->GetHWND(), str, _T("Error"), MB_OK);
				return -4;
			}
			str.Format("Close camera %s success", m_curCamera);
			MessageBox(this->GetHWND(), str, _T("Tips"), MB_OK);
		}
		else if (0 == strcmp(e->m_command, "StartGrab"))
		{
			m_curCamera = (const char*)e->m_ptr;
			TNotifyUI msg;
			int ret = m_hikCamera->StartGrabbing(m_curCamera, true, true);
			if (MV_OK != ret)
			{
				CDuiString str;
				str.Format("StartGrabbing %s failed!", m_curCamera);
				MessageBox(this->GetHWND(), str, _T("Error"), MB_OK);
				return -5;
			}
		}
		else if (0 == strcmp(e->m_command, "StopGrab"))
		{
			m_curCamera = (const char*)e->m_ptr;
			TNotifyUI msg;
			int ret = m_hikCamera->StopGrabbing(m_curCamera);
			if (MV_OK != ret)
			{
				CDuiString str;
				str.Format("StopGrabbing %s failed!", m_curCamera);
				MessageBox(this->GetHWND(), str, _T("Error"), MB_OK);
				return -6;
			}
		}
		else if (0 == strcmp(e->m_command, "SaveOneFrame"))
		{
			std::string file_path = (const char*)e->m_ptr;
			if (file_path.find("TX_") != std::string::npos)
				m_curCamera = "TX";
			else
				m_curCamera = "TY";
			TNotifyUI msg;
			int ret = m_hikCamera->SetSaveImageType(m_curCamera, file_path);
			if (ret != MV_OK)
			{
				//CDuiString str;
				//str.Format("SetSaveImageType %s failed!", m_curCamera);
				//MessageBox(this->GetHWND(), str, _T("Error"), MB_OK);
				return -7;
			}
		}
	}

	return 0;
}

void HIPAMainWidget::EnableControls(bool bIsCameraReady)
{

}

void HIPAMainWidget::ShowMsg(std::string csMessage, int nErrorNum)
{
	std::string errorMsg;
	if (nErrorNum == 0)
	{
		errorMsg = csMessage;
	}
	else
	{
		char buf[50];
		sprintf(buf, ("%s: Error = %x: "), csMessage, nErrorNum);
		errorMsg = buf;
	}

	switch (nErrorNum)
	{
	case MV_E_HANDLE:           errorMsg += "Error or invalid handle ";                                         break;
	case MV_E_SUPPORT:          errorMsg += "Not supported function ";                                          break;
	case MV_E_BUFOVER:          errorMsg += "Cache is full ";                                                   break;
	case MV_E_CALLORDER:        errorMsg += "Function calling order error ";                                    break;
	case MV_E_PARAMETER:        errorMsg += "Incorrect parameter ";                                             break;
	case MV_E_RESOURCE:         errorMsg += "Applying resource failed ";                                        break;
	case MV_E_NODATA:           errorMsg += "No data ";                                                         break;
	case MV_E_PRECONDITION:     errorMsg += "Precondition error, or running environment changed ";              break;
	case MV_E_VERSION:          errorMsg += "Version mismatches ";                                              break;
	case MV_E_NOENOUGH_BUF:     errorMsg += "Insufficient memory ";                                             break;
	case MV_E_ABNORMAL_IMAGE:   errorMsg += "Abnormal image, maybe incomplete image because of lost packet ";   break;
	case MV_E_UNKNOW:           errorMsg += "Unknown error ";                                                   break;
	case MV_E_GC_GENERIC:       errorMsg += "General error ";                                                   break;
	case MV_E_GC_ACCESS:        errorMsg += "Node accessing condition error ";                                  break;
	case MV_E_ACCESS_DENIED:	errorMsg += "No permission ";                                                   break;
	case MV_E_BUSY:             errorMsg += "Device is busy, or network disconnected ";                         break;
	case MV_E_NETER:            errorMsg += "Network error ";                                                   break;
	}
	MessageBox(this->GetHWND(), errorMsg.c_str(), TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
}

void HIPAMainWidget::DisplayOneFrameImage(MV_DISPLAY_FRAME_INFO* info)
{
	m_pLable_Image->SetBkImage("");
	MV_DISPLAY_FRAME_INFO stDisplayInfo = { 0 };
	stDisplayInfo = *info;
	unsigned char* pData = stDisplayInfo.pData;
	unsigned short nWidth = stDisplayInfo.nWidth;
	unsigned short nHeight = stDisplayInfo.nHeight;

	// 方式一
	HBITMAP hBmp = ConvertCharToHBITMAP((char*)pData, nWidth, nHeight);

	CDuiString sCtrlKey = "Image";
	m_PaintManager.RemoveImage(sCtrlKey, true);
	m_PaintManager.AddImage(sCtrlKey, hBmp, nWidth, nHeight, false, true);
	m_PaintManager.ReloadSharedImages();
	m_pLable_Image->SetBkImage(sCtrlKey);
}

HBITMAP HIPAMainWidget::ConvertCharToHBITMAP(char * imageData, int width, int height)
{
	// 创建一个Mat对象（原图8位深，用CV_8UC1）
	cv::Mat img(height, width, CV_8UC1, imageData);
	// 转换成24位RGB格式
	cv::cvtColor(img, img, CV_GRAY2RGB);

	// 创建BITMAPINFO
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
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

void HIPAMainWidget::OnBtnClick(TNotifyUI & msg)
{
	CDuiString senderName = msg.pSender->GetName();

	if (senderName == _T("btn_DeviceSerch"))
		OnBtnDeviceSerchClick(msg);
	else if (senderName == _T("btn_DeviceOpen"))
		OnBtnDeviceOpenClick(msg);
	else if (senderName == _T("btn_DeviceClose"))
		OnBtnDeviceCloseClick(msg);
	else if (senderName == _T("btn_StartGrab"))
		OnBtnStartGrabbingClick(msg);
	else if (senderName == _T("btn_StopGrab"))
		OnBtnStopGrabbingClick(msg);
	else if (senderName == _T("btn_SoftOnce"))
		OnBtnSoftwareOnceClick(msg);
	else if (senderName == _T("btn_exposureTimeGet"))
		OnBtnExposureTimeGetClick(msg);
	else if (senderName == _T("btn_exposureTimeSet"))
		OnBtnExposureTimeSetClick(msg);
	else if (senderName == _T("btn_frameRateGet"))
		OnBtnFrameRateGetClick(msg);
	else if (senderName == _T("btn_frameRateSet"))
		OnBtnFrameRateSetClick(msg);
	else if (senderName == _T("btn_sharpnessGet"))
		OnBtnSharpnessGetClick(msg);
	else if (senderName == _T("btn_sharpnessSet"))
		OnBtnSharpnessSetClick(msg);
	else if (senderName == _T("btn_gainGet"))
		OnBtnGainGetClick(msg);
	else if (senderName == _T("btn_gainSet"))
		OnBtnGainSetClick(msg);
	else if (senderName == _T("btn_gammaGet"))
		OnBtnGammaGetClick(msg);
	else if (senderName == _T("btn_gammaSet"))
		OnBtnGammaSetClick(msg);
	else if (senderName == _T("btn_ImageSaveBmp"))
		OnBtnSaveImageBmpClick(msg);
	else if (senderName == _T("btn_ImageSaveJpeg"))
		OnBtnSaveImageJpegClick(msg);
	else if (senderName == _T("btn_ImageSavePng"))
		OnBtnSaveImagePngClick(msg);
	else if (senderName == _T("btn_ImageSaveTif"))
		OnBtnSaveImageTifClick(msg);
	else if (senderName == _T("btn_ContinueMode"))
		OnRadioContinueModeClick(msg);
	else if (senderName == _T("btn_SwTriggerMode"))
		OnRadioSwTrigerModeClick(msg);
	else if (senderName == _T("btn_HwTriggerMode"))
		OnRadioHwTrigerModeClick(msg);
}

void HIPAMainWidget::OnBtnDeviceSerchClick(TNotifyUI & msg)
{
	m_pCombo_DeviceList->RemoveAll();
	auto deviceList = m_hikCamera->EnumDevice();
	if (deviceList.empty())
	{
		ShowMsg("No device", 0);
		return;
	}
	// 添加到界面列表
	for (size_t i = 0; i < deviceList.size(); i++)
	{
		std::string device = deviceList[i];
		CListLabelElementUI* item = new CListLabelElementUI;
		item->SetText(device.c_str());
		item->SetFixedHeight(26);
		m_pCombo_DeviceList->AddAt(item, i);
	}
	m_pCombo_DeviceList->SelectItem(0);
}

void HIPAMainWidget::OnBtnDeviceOpenClick(TNotifyUI & msg)
{
	int ret = m_hikCamera->OpenDevice(m_curCamera);
	if (ret != MV_OK)
	{
		ShowMsg("Open Fail", ret);
		return;
	}
	ShowMsg("Open Success", ret);
	// 获取并显示参数
	ret = m_hikCamera->GetTriggerMode(m_curCamera);
	if (MV_TRIGGER_MODE_ON == ret)
	{
		OnRadioSwTrigerModeClick(msg);
	}
	else
	{
		OnRadioContinueModeClick(msg);
	}
	m_pBtn_DeviceOpen->SetEnabled(false);
	m_pBtn_DeviceClose->SetEnabled(true);
	m_pBtn_DeviceStart->SetEnabled(true);
	m_pBtn_DeviceStop->SetEnabled(false);
}

void HIPAMainWidget::OnBtnDeviceCloseClick(TNotifyUI & msg)
{
	int ret = m_hikCamera->CloseDivice(m_curCamera);
	if (ret != MV_OK)
	{
		ShowMsg("Close Fail", ret);
		return;
	}
	ShowMsg("Close Success", ret);
	m_pBtn_DeviceOpen->SetEnabled(true);
	m_pBtn_DeviceClose->SetEnabled(false);
	m_pBtn_DeviceStart->SetEnabled(false);
	m_pBtn_DeviceStop->SetEnabled(false);
}

void HIPAMainWidget::OnRadioContinueModeClick(TNotifyUI & msg)
{
	// 修改触发源
	int nRet = m_hikCamera->SetTriggerSource(m_curCamera, false);
	if (nRet != MV_OK)
	{
		return;
	}
	// 修改触发模式
	nRet = m_hikCamera->SetTriggerMode(m_curCamera, false);
	if (nRet != MV_OK)
	{
		return;
	}
	m_pBtn_SoftOnce->SetEnabled(false);
}

void HIPAMainWidget::OnRadioSwTrigerModeClick(TNotifyUI & msg)
{
	// 修改触发源
	int nRet = m_hikCamera->SetTriggerSource(m_curCamera, true);
	if (nRet != MV_OK)
	{
		return;
	}
	// 修改触发模式
	nRet = m_hikCamera->SetTriggerMode(m_curCamera, true);
	if (nRet != MV_OK)
	{
		return;
	}
	m_pBtn_SoftOnce->SetEnabled(true);
}

void HIPAMainWidget::OnRadioHwTrigerModeClick(TNotifyUI & msg)
{
	// 修改触发源
	int nRet = m_hikCamera->SetTriggerSource(m_curCamera, false);
	if (nRet != MV_OK)
	{
		return;
	}
	// 修改触发模式
	nRet = m_hikCamera->SetTriggerMode(m_curCamera, true);
	if (nRet != MV_OK)
	{
		return;
	}
	m_pBtn_SoftOnce->SetEnabled(false);
}

void HIPAMainWidget::OnBtnStartGrabbingClick(TNotifyUI & msg)
{
	int ret = m_hikCamera->StartGrabbing(m_curCamera);
	if (MV_OK != ret)
	{
		ShowMsg("StartGrabbing Fail", ret);
		return;
	}
	m_pOp_ContinueMode->SetEnabled(false);
	m_pOp_SwTriggerMode->SetEnabled(false);
	m_pOp_HwTriggerMode->SetEnabled(false);
	m_pBtn_DeviceStart->SetEnabled(false);
	m_pBtn_DeviceStop->SetEnabled(true);
}

void HIPAMainWidget::OnBtnStopGrabbingClick(TNotifyUI & msg)
{
	int ret = m_hikCamera->StopGrabbing(m_curCamera);
	if (MV_OK != ret)
	{
		ShowMsg("StopGrabbing Fail", ret);
		return;
	}
	m_pOp_ContinueMode->SetEnabled(true);
	m_pOp_SwTriggerMode->SetEnabled(true);
	m_pOp_HwTriggerMode->SetEnabled(true);
	m_pBtn_DeviceStart->SetEnabled(true);
	m_pBtn_DeviceStop->SetEnabled(false);
}

void HIPAMainWidget::OnBtnSoftwareOnceClick(TNotifyUI & msg)
{
	int ret = m_hikCamera->SoftwareOnce(m_curCamera);
	if (MV_OK != ret)
	{
		ShowMsg("SoftwareOnce Fail", ret);
		return;
	}
}

void HIPAMainWidget::OnBtnSaveImageBmpClick(TNotifyUI & msg)
{
	m_pLable_Image->SetText("");
	std::string file_name = IMAGE_PATH_DEFAULT + m_curCamera + "_" + Jup::GetLocalTime(3);
	int ret = m_hikCamera->SetSaveImageType(m_curCamera, file_name);
	if (ret != MV_OK)
	{
		ShowMsg("SAVE_IAMGE_TYPE:Bmp Fail", ret);
		return;
	}
	ShowMsg("Success", ret);
}

void HIPAMainWidget::OnBtnSaveImageJpegClick(TNotifyUI & msg)
{
	std::string file_name = IMAGE_PATH_DEFAULT + m_curCamera + "_" + Jup::GetLocalTime(3);
	int ret = m_hikCamera->SetSaveImageType(m_curCamera, file_name);
	if (ret != MV_OK)
	{
		ShowMsg("SAVE_IAMGE_TYPE:Jpeg Fail", ret);
		return;
	}
	ShowMsg("Success", ret);
}

void HIPAMainWidget::OnBtnSaveImagePngClick(TNotifyUI & msg)
{
	std::string file_name = IMAGE_PATH_DEFAULT + m_curCamera + "_" + Jup::GetLocalTime(3);
	int ret = m_hikCamera->SetSaveImageType(m_curCamera, file_name);
	if (ret != MV_OK)
	{
		ShowMsg("SAVE_IAMGE_TYPE:Png Fail", ret);
		return;
	}
	ShowMsg("Success", ret);
}

void HIPAMainWidget::OnBtnSaveImageTifClick(TNotifyUI & msg)
{
	std::string file_name = IMAGE_PATH_DEFAULT + m_curCamera + "_" + Jup::GetLocalTime(3);
	int ret = m_hikCamera->SetSaveImageType(m_curCamera, file_name);
	if (ret != MV_OK)
	{
		ShowMsg("SAVE_IAMGE_TYPE:Tif Fail", ret);
		return;
	}
	ShowMsg("Success", ret);
}

void HIPAMainWidget::OnBtnExposureTimeGetClick(TNotifyUI & msg)
{
	float exVal;
	int ret = m_hikCamera->GetExposureTime(m_curCamera, exVal);
	if (ret != MV_OK)
	{
		ShowMsg("Get ExposureTime Fail", ret);
		return;
	}
	CDuiString strVal;
	strVal.Format("%.2f", exVal);
	m_pEdit_ExposureTime->SetText(strVal);
}

void HIPAMainWidget::OnBtnExposureTimeSetClick(TNotifyUI & msg)
{
	auto strVal = m_pEdit_ExposureTime->GetText().GetData();
	int ret = m_hikCamera->SetExposureTime(m_curCamera, atof(strVal));
	if (ret != MV_OK)
	{
		ShowMsg("Get ExposureTime Fail", ret);
		return;
	}
	ShowMsg("Set ExposureTime Success", 0);
}

void HIPAMainWidget::OnBtnFrameRateGetClick(TNotifyUI & msg)
{
	float val;
	int ret = m_hikCamera->GetFrameRate(m_curCamera, val);
	if (ret != MV_OK)
	{
		ShowMsg("Get FrameRate Fail", ret);
		return;
	}
	CDuiString strVal;
	strVal.Format("%.2f", val);
	m_pEdit_FrameRate->SetText(strVal);
}

void HIPAMainWidget::OnBtnFrameRateSetClick(TNotifyUI & msg)
{
	auto strVal = m_pEdit_FrameRate->GetText().GetData();
	int ret = m_hikCamera->SetFrameRate(m_curCamera, atof(strVal));
	if (ret != MV_OK)
	{
		ShowMsg("Get FrameRate Fail", ret);
		return;
	}
	ShowMsg("Set FrameRate Success", 0);
}

void HIPAMainWidget::OnBtnSharpnessGetClick(TNotifyUI & msg)
{
}

void HIPAMainWidget::OnBtnSharpnessSetClick(TNotifyUI & msg)
{
}

void HIPAMainWidget::OnBtnGainGetClick(TNotifyUI & msg)
{
	float gainVal;
	int ret = m_hikCamera->GetGain(m_curCamera, gainVal);
	if (ret != MV_OK)
	{
		ShowMsg("Get Gain Fail", ret);
		return;
	}
	CDuiString strVal;
	strVal.Format("%.2f", gainVal);
	m_pEdit_Gain->SetText(strVal);
}

void HIPAMainWidget::OnBtnGainSetClick(TNotifyUI & msg)
{
	auto strVal = m_pEdit_Gain->GetText().GetData();
	int ret = m_hikCamera->SetGain(m_curCamera, atof(strVal));
	if (ret != MV_OK)
	{
		ShowMsg("Get Gain Fail", ret);
		return;
	}
	ShowMsg("Set Gain Success", 0);
}

void HIPAMainWidget::OnBtnGammaGetClick(TNotifyUI & msg)
{
}

void HIPAMainWidget::OnBtnGammaSetClick(TNotifyUI & msg)
{
}