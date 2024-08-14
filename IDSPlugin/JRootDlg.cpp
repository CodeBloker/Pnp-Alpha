#include "JRootDlg.h"
#include <atltime.h>
#include <string>
#include <opencv2/core/cuda.hpp>
//#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include "IDSCamera.h"

#include "JupCore.h"
#include "../_INCLUDE/ProjectEvent.h"
using namespace ProjectEvent;

JRootDlg::JRootDlg()
{
	m_camera = new IDSCamera();
}

JRootDlg::~JRootDlg()
{	
}

UILIB_RESOURCETYPE JRootDlg::GetResourceType() const
{
	return UILIB_ZIP;
}

CDuiString JRootDlg::GetSkinFolder()
{
	return CDuiString();
}

CDuiString JRootDlg::GetSkinFile()
{
	return "main_frame.xml";
}

CDuiString JRootDlg::GetZIPFileName() const
{
	return _T("PluginIDS.zip");
}

LPCTSTR JRootDlg::GetWindowClassName() const
{
	return "JRootDlg";
}

LRESULT JRootDlg::ResponseDefaultKeyEvent(WPARAM wParam)
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

void JRootDlg::InitWindow()
{	
	jCore->RegisterEventWindow(g_IdsWidget, this);

	m_pEditExposureTime = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_exposureTime")));
	m_pEditFrameRate = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_frameRate")));
	m_pEditSharpness = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_sharpness")));
	m_pEditGain = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_gain")));
	m_pEditGamma = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_gamma")));
	m_pLableImage = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("ids_image")));

	m_pOp_TriggerOff = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_TriggerOff")));
	m_pOp_TriggerSw = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_TriggerSw")));
	m_pOp_TriggerHw = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_TriggerHw")));
}

void JRootDlg::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	PostQuitMessage(0);
}

void JRootDlg::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		OnBtnClick(msg);
	}
	else if (msg.sType == DUI_MSGTYPE_SELECTCHANGED)
	{
	
	}
	else if (msg.sType == DUI_MSGTYPE_ITEMCLICK)
	{
	
	}
}

CControlUI * JRootDlg::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT JRootDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
	}
	if (uMsg == WM_TIMER)
	{
		return 0;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT JRootDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	int ret = MessageBoxA(NULL, "是否退出程序？", "Quit", MB_YESNO);
	if (ret == IDYES)
		bHandled = FALSE;	//TRUE表示不处理
	else
		bHandled = TRUE;
	return 0;
}

LRESULT JRootDlg::CustomEvent(JupCustomEvent * event)
{
	JupCustomEvent::eType type = event->Type();
	if (type == ProjectEvent::e_JIdsEvent)
	{
		auto e = dynamic_cast<JIdsEvent*>(event);
		if (0 == strcmp(e->m_command, "DisplayOnceFrame"))
		{
			int width = m_camera->getWidth();
			int height = m_camera->getHeight();
			DisplayOneFrameImage((const char*)e->m_ptr, width, height);
		}
		else if (0 == strcmp(e->m_command, "OpenDevice"))
		{
			bool ret = m_camera->OpenCamera();
			if (!ret)
			{
				MessageBox(this->GetHWND(), "OpenDevice IDS failed!", _T("Error"), MB_OK);
				return -1;
			}
			// 设置连续采集模式
			//ret = m_camera->SetTrigger(IS_WAIT, IS_SET_TRIGGER_OFF);
			//if (!ret)
			//{
			//	MessageBox(this->GetHWND(), "IDS SetTrigger failed!", _T("Error"), MB_OK);
			//	return -2;
			//}
			MessageBox(this->GetHWND(), "OpenDevice IDS success!", _T("Tips"), MB_OK);
		}
		else if (0 == strcmp(e->m_command, "CloseDevice"))
		{
			m_camera->ExitCamera();
			MessageBox(this->GetHWND(), "CloseDevice IDS success!", _T("Tips"), MB_OK);
		}
		else if (0 == strcmp(e->m_command, "StartGrab"))
		{
			int ret = m_camera->StartGrabbingImage(true);
			if (ret != 0)
			{
				MessageBox(this->GetHWND(), "IDS StartGrabbingImage failed!", _T("Error"), MB_OK);
				return -3;
			}
		}
		else if (0 == strcmp(e->m_command, "StopGrab"))
		{
			int ret = m_camera->StopGrabbingImage();
			if (ret != 0)
			{
				MessageBox(this->GetHWND(), "IDS StopGrabbingImage failed!", _T("Error"), MB_OK);
				return -4;
			}
		}
		else if (0 == strcmp(e->m_command, "SaveOneFrame"))
		{
			std::string file_path = (const char*)e->m_ptr;
			bool ret = m_camera->SaveImage(file_path.c_str());
			if (!ret)
			{
				//MessageBox(this->GetHWND(), "SetSaveImage IDS failed!", _T("Error"), MB_OK);
				return -5;
			}
		}
	}

	return 0;
}

HBITMAP JRootDlg::ConvertCharToHBITMAP(char * imageData, int width, int height)
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

void JRootDlg::DisplayOneFrameImage(const char * image, int width, int height)
{
	m_pLableImage->SetBkImage("");
	unsigned char* pData = (unsigned char*)image;
	unsigned short nWidth = width;
	unsigned short nHeight = height;

	HBITMAP hBmp = ConvertCharToHBITMAP((char*)pData, nWidth, nHeight);

	CDuiString sCtrlKey = "Image";
	m_PaintManager.RemoveImage(sCtrlKey, true);
	m_PaintManager.AddImage(sCtrlKey, hBmp, nWidth, nHeight, false, true);
	m_PaintManager.ReloadSharedImages();
	m_pLableImage->SetBkImage(sCtrlKey);
}

void JRootDlg::OnBtnClick(TNotifyUI & msg)
{
	if (msg.pSender->GetName() == _T("btn_exposureTimeGet"))
	{
		OnBtnExposureTimeGetClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_exposureTimeSet"))
	{
		OnBtnExposureTimeSetClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_frameRateGet"))
	{
		OnBtnFrameRateGetClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_frameRateSet"))
	{
		OnBtnFrameRateSetClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_sharpnessGet"))
	{
		OnBtnSharpnessGetClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_sharpnessSet"))
	{
		OnBtnSharpnessSetClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_gainGet"))
	{
		OnBtnGainGetClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_gainSet"))
	{
		OnBtnGainSetClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_gammaGet"))
	{
		OnBtnGammaGetClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_gammaSet"))
	{
		OnBtnGammaSetClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_openCamera"))
	{
		OnBtnOpenCameraClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_closeCamera"))
	{
		OnBtnCloseCameraClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_stopGrabbing"))
	{
		OnBtnStopGrabbingClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_startGrabbing"))
	{
		OnBtnStartGrabbingClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_TriggerOff"))
	{
		OnRadioTrigerOffClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_TriggerSw"))
	{
		OnRadioTrigerSwClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_TriggerHw"))
	{
		OnRadioTrigerHwClick(msg);
	}
}

void JRootDlg::OnBtnExposureTimeGetClick(TNotifyUI & msg)
{
	double nExposure = m_camera->ReadExposure();
	CDuiString editString;
	editString.Format(_T("%.4f"), nExposure);
	m_pEditExposureTime->SetText(editString);
}

void JRootDlg::OnBtnExposureTimeSetClick(TNotifyUI & msg)
{
	CDuiString editString;
	editString = m_pEditExposureTime->GetText();
	if (editString.IsEmpty())
	{
		MessageBox(this->GetHWND(), _T("Input is empty!"), _T("Error"), MB_OK);
	}

	bool ret = m_camera->SetExposure(std::stof(editString.GetData()));
	if (ret)
	{
		MessageBox(this->GetHWND(), _T("Set exposureTime value successful!"), _T("Success"), MB_OK);
	}
	else
	{
		MessageBox(this->GetHWND(), _T("Set exposureTime failed!"), _T("Error"), MB_OK);
	}
}

void JRootDlg::OnBtnFrameRateGetClick(TNotifyUI & msg)
{
	double nFrameRate = m_camera->ReadFrameRate();
	CDuiString editString;
	editString.Format(_T("%.4f"), nFrameRate);
	m_pEditFrameRate->SetText(editString);
}

void JRootDlg::OnBtnFrameRateSetClick(TNotifyUI & msg)
{
	CDuiString editString;
	editString = m_pEditFrameRate->GetText();
	if (editString.IsEmpty())
	{
		MessageBox(this->GetHWND(), _T("Input is empty!"), _T("Error"), MB_OK);
	}

	bool ret = m_camera->SetFrameRate(std::stof(editString.GetData()));
	if (ret)
	{
		MessageBox(this->GetHWND(), _T("Set frameRate value successful!"), _T("Success"), MB_OK);
	}
	else
	{
		MessageBox(this->GetHWND(), _T("Set frameRate failed!"), _T("Error"), MB_OK);
	}
}

void JRootDlg::OnBtnSharpnessGetClick(TNotifyUI & msg)
{
	// The camera model used here does not support this function or setting.
	//int nSharpness = m_camera->ReadSharpness();
	//CDuiString editString;
	//editString.Format(_T("%d"), nSharpness);
	//m_pEditSharpness->SetText(editString);
}

void JRootDlg::OnBtnSharpnessSetClick(TNotifyUI & msg)
{
}

void JRootDlg::OnBtnGainGetClick(TNotifyUI & msg)
{

}

void JRootDlg::OnBtnGainSetClick(TNotifyUI & msg)
{


}

void JRootDlg::OnBtnGammaGetClick(TNotifyUI & msg)
{
	int nGamma = m_camera->ReadGamma();
	CDuiString editString;
	editString.Format(_T("%d"), nGamma);
	m_pEditGamma->SetText(editString);
}

void JRootDlg::OnBtnGammaSetClick(TNotifyUI & msg)
{
	CDuiString editString;
	editString = m_pEditGamma->GetText();
	if (editString.IsEmpty())
	{
		MessageBox(this->GetHWND(), _T("Input is empty!"), _T("Error"), MB_OK);
	}

	bool ret = m_camera->SetGamma(std::stoi(editString.GetData()));
	if (ret)
	{
		MessageBox(this->GetHWND(), _T("Set gamma value successful!"), _T("Success"), MB_OK);
	}
	else
	{
		MessageBox(this->GetHWND(), _T("Set gamma value failed!"), _T("Error"), MB_OK);
	}
}

void JRootDlg::OnBtnOpenCameraClick(TNotifyUI & msg)
{
	if (m_camera->OpenCamera())
	{
		MessageBox(this->GetHWND(), _T("Open camera successful!"), _T("Success"), MB_OK);
		// 获取参数值并显示
		OnBtnExposureTimeGetClick(msg);
		OnBtnFrameRateGetClick(msg);
		OnBtnSharpnessGetClick(msg);
		OnBtnGainGetClick(msg);
		OnBtnGammaGetClick(msg);
		//SetTimer(this->GetHWND(), TIMER_IMAGE, 20, NULL);
	}
	else
	{
		MessageBox(this->GetHWND(), _T("Open camera failed!"), _T("Error"), MB_OK);
	}
}

void JRootDlg::OnBtnCloseCameraClick(TNotifyUI & msg)
{
	m_camera->ExitCamera();
}

void JRootDlg::OnBtnStartGrabbingClick(TNotifyUI & msg)
{
	m_camera->StartGrabbingImage();
}

void JRootDlg::OnBtnStopGrabbingClick(TNotifyUI & msg)
{
	m_camera->StopGrabbingImage();
}

void JRootDlg::OnRadioTrigerOffClick(TNotifyUI & msg)
{
	int ret = m_camera->SetTrigger(IS_WAIT, IS_SET_TRIGGER_OFF);
	if (!ret)
	{
		return;
	}
	m_pOp_TriggerOff->Selected(true);
	m_pOp_TriggerSw->Selected(false);
	m_pOp_TriggerHw->SetEnabled(false);
}

void JRootDlg::OnRadioTrigerSwClick(TNotifyUI & msg)
{
	int ret = m_camera->SetTrigger(5000, IS_SET_TRIGGER_SOFTWARE);
	if (!ret)
	{
		return;
	}
	m_pOp_TriggerOff->Selected(false);
	m_pOp_TriggerSw->Selected(true);
	m_pOp_TriggerHw->SetEnabled(false);
}

void JRootDlg::OnRadioTrigerHwClick(TNotifyUI & msg)
{
	int ret = m_camera->SetTrigger(5000, IS_SET_TRIGGER_HI_LO);
	if (!ret)
	{
		return;
	}
	m_pOp_TriggerOff->Selected(false);
	m_pOp_TriggerSw->Selected(false);
	m_pOp_TriggerHw->SetEnabled(true);
}
