#include "DvpMainWidget.h"

#include <future>
#include "JupCore.h"
#include <filesystem>
#include "../_INCLUDE/ProjectEvent.h"
using namespace ProjectEvent;

DvpMainWidget::DvpMainWidget()
{
	m_dvpCamera = DvpCamera_Manage::GetInstance();
}

DvpMainWidget::~DvpMainWidget()
{
	if (m_dvpCamera)
	{
		std::vector<std::string> cameraList = m_dvpCamera->EnumDevice();
		for (auto camera : cameraList)
		{
			m_dvpCamera->CloseDivice(camera);
		}
	}
}

UILIB_RESOURCETYPE DvpMainWidget::GetResourceType() const
{
	return UILIB_ZIP;
}

CDuiString DvpMainWidget::GetSkinFolder()
{
	return "";
}

CDuiString DvpMainWidget::GetSkinFile()
{
	return "expand_frame.xml";
}

CDuiString DvpMainWidget::GetZIPFileName() const
{
	return _T("PluginDVP.zip");
}

LPCTSTR DvpMainWidget::GetWindowClassName() const
{
	return "DVPMainWidget";
}

LRESULT DvpMainWidget::ResponseDefaultKeyEvent(WPARAM wParam)
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

void DvpMainWidget::InitWindow()
{	
	jCore->RegisterEventWindow(g_DvpWidget, this);

	m_pCombo_DeviceList = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("cmb_DeviceList")));
	m_pBtn_DeviceSerch = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_DeviceSerch")));
	m_pBtn_DeviceOpen = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_DeviceOpen")));
	m_pBtn_DeviceClose = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_DeviceClose")));
	m_pBtn_DeviceStart = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_StartGrab")));
	m_pBtn_DeviceStop = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_StopGrab")));
	m_pBtn_SoftOnce = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_SoftOnce")));
	m_pOp_ImageSaveBmp = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_ImageSaveBmp")));
	m_pOp_ImageSaveJepg = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_ImageSaveJpeg")));
	m_pOp_ImageSavePng = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_ImageSavePng")));
	m_pOp_ImageSaveTif = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_ImageSaveTif")));
	m_pBtn_OpenParamsGUI = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_OpenParamsGUI")));

	m_pLable_Image = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("dvp_image")));
	m_pOp_ContinueMode = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_ContinueMode")));
	m_pOp_SwTriggerMode = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_SwTriggerMode")));
	m_pOp_HwTriggerMode = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_HwTriggerMode")));

	//m_edit_m_templateX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_m_templateX")));
	//m_edit_m_templateY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_m_templateY")));
	//m_edit_Pnp_x = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Pnp_x")));
	//m_edit_Pnp_y = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Pnp_y")));
	//m_edit_deltaPnpx = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_deltaPnpx")));
	//m_edit_deltaPnpy = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_deltaPnpy")));

	//m_edit_m_tempX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_m_tempX")));
	//m_edit_m_tempY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_m_tempY")));
	//m_edit_m_tempR = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_m_tempR")));
	//m_edit_Nozzle_x = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Nozzle_x")));
	//m_edit_Nozzle_y = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Nozzle_y")));
	//m_edit_Nozzle_r = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Nozzle_r")));
	//m_edit_deltaNozzleX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_deltaNozzleX")));
	//m_edit_deltaNozzleY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_deltaNozzleY")));
	//m_edit_deltaNozzleR = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_deltaNozzleR")));

	m_edit_normalX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_normalX")));
	m_edit_normalY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_normalY")));
	m_edit_normalR = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_normalR")));

	m_edit_actualX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_actualX")));
	m_edit_actualY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_actualY")));
	m_edit_actualR = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_actualR")));

	m_edit_deltaX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_deltaX")));
	m_edit_deltaY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_deltaY")));
	m_edit_deltaR = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_deltaR")));


	m_pOp_PnpCalibration = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_PnpCalibration")));
	m_pOp_NozzleCalibration = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("check_NozzleCalibration")));


	std::vector<std::string> cameraList = m_dvpCamera->EnumDevice();
	for (auto camera : cameraList)
	{
		/*int ret = m_dvpCamera->OpenDevice(camera);
		if (MV_OK != ret)
		{
			std::string msg = camera + " camera open fail";
			MessageBox(this->GetHWND(), msg.c_str(), _T("Error"), MB_OK);
		}*/
		CListLabelElementUI* item = new CListLabelElementUI;
		item->SetText(camera.c_str());
		item->SetFixedHeight(26);
		m_pCombo_DeviceList->Add(item);
		//m_curCamera = camera;
		//TNotifyUI msg;
		//OnRadioContinueModeClick(msg);
	}
	m_pCombo_DeviceList->SelectItem(0);
	//m_pBtn_DeviceStart->SetEnabled(false);
	m_pBtn_DeviceStop->SetEnabled(false);
	m_pBtn_DeviceSerch->SetEnabled(false);
	m_pBtn_DeviceOpen->SetEnabled(true);
	m_pBtn_SoftOnce->SetEnabled(false);
}

void DvpMainWidget::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	PostQuitMessage(0);
}

void DvpMainWidget::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		OnBtnClick(msg);
	}
	else if (msg.sType == DUI_MSGTYPE_SELECTCHANGED)
	{
		CDuiString senderName = msg.pSender->GetName();
		if (senderName == _T("check_PnpCalibration"))
		{
			//具体函数
			OnCheckPnpCalibrationSelectClick(msg);
		}
		else if (senderName == _T("check_NozzleCalibration"))
		{
			//具体函数
			OnCheckNozzleCalibrationSelectClick(msg);
		}
	}
	if (msg.sType == DUI_MSGTYPE_ITEMSELECT && msg.pSender->GetName() == _T("cmb_DeviceList"))
	{
		m_curCamera = m_pCombo_DeviceList->GetText().GetData();
	}
}

CControlUI * DvpMainWidget::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT DvpMainWidget::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT DvpMainWidget::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	int ret = MessageBoxA(NULL, "是否退出程序？", "Quit", MB_YESNO);
	if (ret == IDYES)
		bHandled = FALSE;	//TRUE表示不处理
	else
		bHandled = TRUE;
	return 0;
}

LRESULT DvpMainWidget::CustomEvent(JupCustomEvent * event)
{
	JupCustomEvent::eType type = event->Type();
	if (type == ProjectEvent::e_JDvpEvent)
	{
		auto e = dynamic_cast<JDvpEvent*>(event);
		DisplayOneFrameImage((char*)e->m_ptr, e->m_width, e->m_height);
	}
	else if (type == ProjectEvent::e_JDvpPnpCalibrationEvent)
	{
		//清空背景图片
		//m_pLable_Image->SetBkImage("");
		//m_pLable_Image->Invalidate();
		auto e = dynamic_cast<JDvpPnpCalibrationEvent*>(event);
		if (m_pOp_PnpCalibration->IsSelected())
		{
			std::string testImage = "C:\\Users\\CTOS\\Desktop\\TEST0812\\2024-08-10_10-41-04_314.bmp";
			GetImagePointResult(e->resultImagePath, true);
			m_pLable_Image->SetBkImage(e->resultImagePath.c_str());
		}
		else if (m_pOp_NozzleCalibration->IsSelected())
		{
			std::string testImage = "C:\\Users\\CTOS\\Desktop\\TEST0812\\2024-08-12_09-44-12_376.bmp";
			GetImagePointResult(e->resultImagePath, true);
			m_pLable_Image->SetBkImage(e->resultImagePath.c_str());
		}
		else
		{
			GetImagePointResult(e->resultImagePath, true);
			m_pLable_Image->SetBkImage(e->resultImagePath.c_str());
		}
		
	}

	return 0;
}

void DvpMainWidget::EnableControls(bool bIsCameraReady)
{

}

void DvpMainWidget::DisplayOneFrameImage(char* imageData, int width, int height)
{
	m_pLable_Image->SetBkImage("");
	// 方式一
	HBITMAP hBmp = ConvertCharToHBITMAP(imageData, width, height);

	CDuiString sCtrlKey = "Image";
	m_PaintManager.RemoveImage(sCtrlKey, true);
	m_PaintManager.AddImage(sCtrlKey, hBmp, width, height, false, true);
	m_PaintManager.ReloadSharedImages();
	m_pLable_Image->SetBkImage(sCtrlKey);
}

HBITMAP DvpMainWidget::ConvertCharToHBITMAP(char * imageData, int width, int height)
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

void DvpMainWidget::OnBtnClick(TNotifyUI & msg)
{
	if (msg.pSender->GetName() == _T("btn_DeviceSerch"))
	{
		OnBtnDeviceSerchClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_DeviceOpen"))
	{
		OnBtnDeviceOpenClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_DeviceClose"))
	{
		OnBtnDeviceCloseClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_StartGrab"))
	{
		OnBtnStartGrabbingClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_StopGrab"))
	{
		OnBtnStopGrabbingClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_SoftOnce"))
	{
		OnBtnSoftwareOnceClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_OpenParamsGUI"))
	{
		OnBtnOpenParamsGUIClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_ContinueMode"))
	{
		OnRadioContinueModeClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_SwTriggerMode"))
	{
		OnRadioSwTrigerModeClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_HwTriggerMode"))
	{
		OnRadioHwTrigerModeClick(msg);
	}
}

void DvpMainWidget::OnBtnDeviceSerchClick(TNotifyUI & msg)
{
	m_pCombo_DeviceList->RemoveAll();
	auto deviceList = m_dvpCamera->EnumDevice();
	if (deviceList.empty())
	{
		MessageBox(this->GetHWND(), "No device", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
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

void DvpMainWidget::OnBtnDeviceOpenClick(TNotifyUI & msg)
{
	std::string strErrorMsg;
	if (m_pOp_ContinueMode->IsSelected())
	{
		int ret = m_dvpCamera->OpenDevice(m_curCamera, strErrorMsg,true);
		if (ret != 0)
		{
			MessageBox(this->GetHWND(), "Open Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
			return;
		}
		// 修改触发模式
		if (!m_dvpCamera->SetTriggerMode(m_curCamera, false))
		{
			MessageBox(this->GetHWND(), "Set Trigger Mode Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
			return;
		}
		m_pBtn_SoftOnce->SetEnabled(false);
		m_pOp_ContinueMode->SetEnabled(false);
		m_pOp_SwTriggerMode->SetEnabled(false);
		m_pOp_HwTriggerMode->SetEnabled(false);
		MessageBox(this->GetHWND(), "Open Success", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
	}
	else if(m_pOp_SwTriggerMode->IsSelected())
	{
		int ret = m_dvpCamera->OpenDevice(m_curCamera, strErrorMsg);
		if (ret != 0)
		{
			MessageBox(this->GetHWND(), "Open Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
			return;
		}
		m_pOp_ContinueMode->SetEnabled(false);
		// 修改触发源
		if (!m_dvpCamera->SetTriggerSource(m_curCamera, TRIGGER_SOURCE_SOFTWARE))
		{
			MessageBox(this->GetHWND(), "Set Trigger Source Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
			return;
		}
		// 修改触发模式
		if (!m_dvpCamera->SetTriggerMode(m_curCamera, true))
		{
			MessageBox(this->GetHWND(), "Set Trigger Mode Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
			return;
		}
		m_pBtn_SoftOnce->SetEnabled(true);
		m_pOp_ContinueMode->SetEnabled(false);
		m_pOp_SwTriggerMode->SetEnabled(false);
		m_pOp_HwTriggerMode->SetEnabled(false);
		MessageBox(this->GetHWND(), "Open Success", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
	}
	else if (m_pOp_HwTriggerMode->IsSelected())
	{
		// 修改触发源
		if (!m_dvpCamera->SetTriggerSource(m_curCamera, TRIGGER_SOURCE_LINE3))
		{
			MessageBox(this->GetHWND(), "Set Trigger Source Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
			return;
		}
		// 修改触发模式
		if (!m_dvpCamera->SetTriggerMode(m_curCamera, true))
		{
			MessageBox(this->GetHWND(), "Set Trigger Mode Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
			return;
		}
		m_pBtn_SoftOnce->SetEnabled(false);
		m_pOp_ContinueMode->SetEnabled(false);
		m_pOp_SwTriggerMode->SetEnabled(false);
		m_pOp_HwTriggerMode->SetEnabled(false);
		MessageBox(this->GetHWND(), "Open Success", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
	}
	else
	{
		MessageBox(this->GetHWND(), "Please Select Trigger Mode!", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
	}
	//// 获取并显示参数
	//bool TrigerMode = false;
	//if (m_dvpCamera->GetTriggerMode(m_curCamera, TrigerMode))
	//{
	//	if (TrigerMode)
	//	{
	//		m_pOp_SwTriggerMode->Selected(true);
	//		OnRadioSwTrigerModeClick(msg);
	//	}
	//	else
	//	{
	//		m_pOp_ContinueMode->Selected(true);
	//		OnRadioContinueModeClick(msg);
	//	}
	//}
	//MessageBox(this->GetHWND(), "Open Success", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
}

void DvpMainWidget::OnBtnDeviceCloseClick(TNotifyUI & msg)
{
	int ret = m_dvpCamera->CloseDivice(m_curCamera);
	if (ret != 0)
	{
		MessageBox(this->GetHWND(), "Close Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
		return;
	}
	m_pOp_ContinueMode->SetEnabled(true);
	m_pOp_SwTriggerMode->SetEnabled(true);
	m_pOp_HwTriggerMode->SetEnabled(true);
	MessageBox(this->GetHWND(), "Close Success", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
}

void DvpMainWidget::OnRadioContinueModeClick(TNotifyUI & msg)
{
	// 修改触发模式
	//if (!m_dvpCamera->SetTriggerMode(m_curCamera, false))
	//{
	//	MessageBox(this->GetHWND(), "Set Trigger Mode Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
	//	return;
	//}
	//m_pBtn_SoftOnce->SetEnabled(false);
	//MessageBox(this->GetHWND(), "Set Trigger Mode Success", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
}

void DvpMainWidget::OnRadioSwTrigerModeClick(TNotifyUI & msg)
{
	// 修改触发源
	//if (!m_dvpCamera->SetTriggerSource(m_curCamera, TRIGGER_SOURCE_SOFTWARE))
	//{
	//	MessageBox(this->GetHWND(), "Set Trigger Source Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
	//	return;
	//}
	//// 修改触发模式
	//if (!m_dvpCamera->SetTriggerMode(m_curCamera, true))
	//{
	//	MessageBox(this->GetHWND(), "Set Trigger Mode Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
	//	return;
	//}
	//m_pBtn_SoftOnce->SetEnabled(true);
	//MessageBox(this->GetHWND(), "Set Trigger Mode Success", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
}

void DvpMainWidget::OnRadioHwTrigerModeClick(TNotifyUI & msg)
{
	// 修改触发源
	//if (!m_dvpCamera->SetTriggerSource(m_curCamera, TRIGGER_SOURCE_LINE3))
	//{
	//	MessageBox(this->GetHWND(), "Set Trigger Source Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
	//	return;
	//}
	//// 修改触发模式
	//if (!m_dvpCamera->SetTriggerMode(m_curCamera, true))
	//{
	//	MessageBox(this->GetHWND(), "Set Trigger Mode Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
	//	return;
	//}
	//m_pBtn_SoftOnce->SetEnabled(false);
	//MessageBox(this->GetHWND(), "Set Trigger Mode Success", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
}

void DvpMainWidget::OnBtnStartGrabbingClick(TNotifyUI & msg)
{
	int ret = m_dvpCamera->StartGrabbing(m_curCamera);
	if (0 != ret)
	{
		MessageBox(this->GetHWND(), "StartGrabbing Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
		return;
	}
	//m_pOp_ContinueMode->SetEnabled(false);
	//m_pOp_SwTriggerMode->SetEnabled(false);
	//m_pOp_HwTriggerMode->SetEnabled(false);
	m_pBtn_DeviceStart->SetEnabled(false);
	m_pBtn_DeviceStop->SetEnabled(true);
	m_dvpCamera->SetSaveImagePath(m_curCamera, CALIBRATION_IMAGE_PATH_DEFAULT);
}

void DvpMainWidget::OnBtnStopGrabbingClick(TNotifyUI & msg)
{
	int ret = m_dvpCamera->StopGrabbing(m_curCamera);
	if (0 != ret)
	{
		MessageBox(this->GetHWND(), "StopGrabbing Fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
		return;
	}
	//m_pOp_ContinueMode->SetEnabled(true);
	//m_pOp_SwTriggerMode->SetEnabled(true);
	//m_pOp_HwTriggerMode->SetEnabled(true);
	m_pBtn_DeviceStart->SetEnabled(true);
	m_pBtn_DeviceStop->SetEnabled(false);
}

void DvpMainWidget::OnBtnSoftwareOnceClick(TNotifyUI & msg)
{
	std::string strErrorMsg, strPath;
	strPath = CALIBRATION_IMAGE_PATH_DEFAULT;
	if (m_pOp_ImageSaveBmp->IsSelected())
	{
		strPath += "SoftwareOnce_" + Jup::GetLocalTime(3) + ".bmp";
	}
	else
	{
		return;
	}
	//else if (m_pOp_ImageSaveJepg->IsSelected())
	//{
	//	strPath = "./SoftwareOnce.jpg";
	//}
	//else if (m_pOp_ImageSavePng->IsSelected())
	//{
	//	strPath = "./SoftwareOnce.png";
	//}
	//else if (m_pOp_ImageSaveTif->IsSelected())
	//{
	//	strPath = "./SoftwareOnce.tif";
	//}
	if (std::filesystem::exists(strPath))
	{
		std::filesystem::remove(strPath);
	}
	int ret = m_dvpCamera->TakePhoto(m_curCamera, strPath, strErrorMsg);
	if (0 != ret)
	{
		std::string str = "SoftwareOnce Fail, " + strErrorMsg;
		MessageBox(this->GetHWND(), str.c_str(), TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
		return;
	}
	//if (m_pOp_PnpCalibration->IsSelected())
	//{
	//	std::string testPath = "C:/Users/CTOS/Desktop/TEST0812/2024-08-10_10-41-04_314.bmp";
	//	jCore->PostEvent(ProjectEvent::g_MilWidget, new ProjectEvent::JMilEvent(testPath, 1));
	//}
	//else if (m_pOp_NozzleCalibration->IsSelected())
	//{
	//	std::string testPath = "C:/Users/CTOS/Desktop/TEST0812/2024-08-12_09-44-12_376.bmp";
	//	jCore->PostEvent(ProjectEvent::g_MilWidget, new ProjectEvent::JMilEvent(testPath, 2));
	//}

	//m_pLable_Image->SetBkImage(strPath.c_str());
}

void DvpMainWidget::OnBtnOpenParamsGUIClick(TNotifyUI & msg)
{
	if (!m_dvpCamera->OpenCameraProperty(m_curCamera))
	{
		MessageBox(this->GetHWND(), "open params GUI fail", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
		return;
	}
}

void DvpMainWidget::OnCheckPnpCalibrationSelectClick(TNotifyUI & msg)
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	if (m_pOp_PnpCalibration->IsSelected())
	{
		m_pOp_NozzleCalibration->Selected(false);
	}
}

void DvpMainWidget::OnCheckNozzleCalibrationSelectClick(TNotifyUI & msg)
{
	if (m_pOp_NozzleCalibration->IsSelected())
	{
		m_pOp_PnpCalibration->Selected(false);
	}
}

void DvpMainWidget::GetImagePointResult(std::string &file_name, bool wait_result)
{
	// MIL计算坐标
	std::string file_mmf;
	std::string file_out;
	std::string m_file_name = file_name;
	bool isRun = false;
	if (m_pOp_PnpCalibration->IsSelected())
	{
		file_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Top Cross.mmf";
		JMilFindModelPnpEvent milEvent(m_file_name, file_mmf, file_out);
		jCore->SendEvent(g_MilWidget, &milEvent);
		//在这里输出到界面上
		//通过milEvent去获得要输出的东西，也就是说milEvent里面包含了（XYR）标定板和（XYR）实际
		CDuiString strVal;

		strVal.Format("%.2f", milEvent.m_calibrationPointX);
		m_edit_normalX->SetText(strVal);
		strVal.Format("%.2f", milEvent.m_calibrationPointY);
		m_edit_normalY->SetText(strVal);
		strVal.Format("%.2f", milEvent.m_calibrationAngle);
		m_edit_normalR->SetText(strVal);

		strVal.Format("%.2f", milEvent.m_actualPointX);
		m_edit_actualX->SetText(strVal);
		strVal.Format("%.2f", milEvent.m_actualPointY);
		m_edit_actualY->SetText(strVal);
		strVal.Format("%.2f", milEvent.m_actualPointAngle);
		m_edit_actualR->SetText(strVal);

		strVal.Format("%.2f", milEvent.m_calibrationPointX - milEvent.m_actualPointX);
		m_edit_deltaX->SetText(strVal);
		strVal.Format("%.2f", milEvent.m_calibrationPointY - milEvent.m_actualPointY);
		m_edit_deltaY->SetText(strVal);
		strVal.Format("%.2f", milEvent.m_calibrationAngle - milEvent.m_actualPointAngle);
		m_edit_deltaR->SetText(strVal);

		//这里加个图片路径判断，若成功返回结果，就返回结果图片；若失败就返回原图
		if (!file_out.empty())
		{
			file_name = file_out;
		}
		//isRun = true;
	}
	else if (m_pOp_NozzleCalibration->IsSelected())
	{
		std::string file_cross_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Bottom Cross.mmf";
		std::string file_circle_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Bottom Circleli-1.mmf";

		JMilFindModelNozzleEvent milEvent(m_file_name, file_cross_mmf, file_circle_mmf, file_out);
		jCore->SendEvent(g_MilWidget, &milEvent);

		CDuiString strVal;

		strVal.Format("%.2f", milEvent.m_calibrationPointX);
		m_edit_normalX->SetText(strVal);
		strVal.Format("%.2f", milEvent.m_calibrationPointY);
		m_edit_normalY->SetText(strVal);
		strVal.Format("%.2f", milEvent.m_calibrationAngle);
		m_edit_normalR->SetText(strVal);

		strVal.Format("%.2f", milEvent.m_actualPointX);
		m_edit_actualX->SetText(strVal);
		strVal.Format("%.2f", milEvent.m_actualPointY);
		m_edit_actualY->SetText(strVal);
		strVal.Format("%.2f", milEvent.m_actualPointAngle);
		m_edit_actualR->SetText(strVal);

		strVal.Format("%.2f", milEvent.m_calibrationPointX - milEvent.m_actualPointX);
		m_edit_deltaX->SetText(strVal);
		strVal.Format("%.2f", milEvent.m_calibrationPointY - milEvent.m_actualPointY);
		m_edit_deltaY->SetText(strVal);
		strVal.Format("%.2f", milEvent.m_calibrationAngle - milEvent.m_actualPointAngle);
		m_edit_deltaR->SetText(strVal);

		//这里加个图片路径判断，若成功返回结果，就返回结果图片；若失败就返回原图
		if (!file_out.empty())
		{
			file_name = file_out;
		}
		//isRun = true;
	}
	else
	{
		//MessageBox(this->GetHWND(), "Please select calibration mode", TEXT("PROMPT"), MB_OK | MB_ICONWARNING);
		//isRun = false;
		// 计算结果
		//std::string file_mmf = "D:\\VISION\\FZ-TEST\\TEST0807\\ping.mmf";
		//std::string file_out;
		//JMilFindCenterEvent milEvent(file_name, file_mmf, file_out);
		//jCore->SendEvent(g_MilWidget, &milEvent);
		//double offset_centerY = -24.1141;
		//double offset_centerX = 3.6997;
		//double result_offsetX = -((-milEvent.m_event_deltaX) + offset_centerX) * 0.0139;
		//double result_offsetY = ((-milEvent.m_event_deltaY) + offset_centerY) * 0.0139;

		//std::string file_mmf = "D:\\VISION\\FZ-TEST\\TEST0807\\socket.mmf";
		//std::string file_out;
		//JMilFindSocketMarkCenterEvent milEvent(file_name, file_mmf, file_out);
		//jCore->SendEvent(g_MilWidget, &milEvent);
		//double offset_centerY = -1.616;
		//double offset_centerX = -194.021;
		//double result_offsetX = -((-milEvent.m_event_deltaX) + offset_centerX) * 0.0139;
		//double result_offsetY = ((-milEvent.m_event_deltaY) + offset_centerY) * 0.0139;


		//CDuiString strVal;
		//strVal.Format("%.3f", result_offsetY);
		//m_edit_deltaX->SetText(strVal);
		//strVal.Format("%.3f", result_offsetX);
		//m_edit_deltaY->SetText(strVal);

		std::string file_mmf = "D:\\VISION\\FZ-TEST\\TEST0807\\ping.mmf";
		std::string file_circle_mmf = "D:\\VISION\\FZ-TEST\\TEST0807\\socket.mmf";

		std::string file_out;
		JMilFindSocketMarkAndB2BDistanceEvent milEvent(file_name, file_mmf, file_circle_mmf, file_out);
		jCore->SendEvent(g_MilWidget, &milEvent);
	}
	
	//if (isRun)
	//{
	//	//file_name = file_out;
	//}
}
