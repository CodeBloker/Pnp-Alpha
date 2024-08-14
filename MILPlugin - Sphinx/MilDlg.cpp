#include "MilDlg.h"
#include "Common/JupCommon.h"

MilDlg::MilDlg()
{
	m_milManager = MilManager::GetInstance();
	m_camera = CameraDILManager::GetInstance();
}

MilDlg::~MilDlg()
{	
	m_camera->Close();
}

UILIB_RESOURCETYPE MilDlg::GetResourceType() const
{
	return UILIB_ZIP;
}

CDuiString MilDlg::GetSkinFolder()
{
	return "";
}

CDuiString MilDlg::GetSkinFile()
{
	return "main_frame.xml";
}

CDuiString MilDlg::GetZIPFileName() const
{
	return _T("PluginMil.zip");
}

LPCTSTR MilDlg::GetWindowClassName() const
{
	return "MilDlg";
}

LRESULT MilDlg::ResponseDefaultKeyEvent(WPARAM wParam)
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

void MilDlg::InitWindow()
{	
	jCore->RegisterEventWindow(g_MilWidget, this);

	m_pEdit_ExposureTime = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_exposureTime")));
	m_pEdit_FrameRate = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_frameRate")));
	m_pEdit_Gain = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_gain")));
	m_pEdit_BlackLevel = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_blackLevel")));
	m_pEdit_Timeout = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Timeout")));
	m_pEdit_Temperature = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Temperature")));
	m_pEdit_runMode = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_runMode")));
	m_pLable_MilImage = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("mil_image")));
}

void MilDlg::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	PostQuitMessage(0);
}

void MilDlg::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		OnBtnClick(msg);
	}
}

CControlUI * MilDlg::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT MilDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT MilDlg::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT MilDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	int ret = MessageBoxA(NULL, "是否退出程序？", "Quit", MB_YESNO);
	if (ret == IDYES)
		bHandled = FALSE;	//TRUE表示不处理
	else
		bHandled = TRUE;
	return 0;
}

void MilDlg::OnExit(TNotifyUI & msg)
{
	this->Close();
}

LRESULT MilDlg::CustomEvent(JupCustomEvent * event)
{
	JupCustomEvent::eType type = event->Type();
	if (type == ProjectEvent::e_JMilEvent)
	{
		auto e = dynamic_cast<JMilEvent*>(event);
		int width = m_camera->GetWidth();
		int height = m_camera->GetHeight();
		DisplayOneFrameImage((const char*)e->m_ptr, width, height);
	}
	else if (type == ProjectEvent::e_JMilFindModelEvent)
	{
		auto e = dynamic_cast<JMilFindModelEvent*>(event);
		std::string camera_name;
		if (e->m_file_mmf.find("TX") != std::string::npos)
			camera_name = "TX";
		else if (e->m_file_mmf.find("TY") != std::string::npos)
			camera_name = "TY";
		else
			camera_name = "IDS";
		// 放到不同线程执行
		if (camera_name == "TX" && !m_tx_thread.valid() || m_tx_thread._Is_ready())
		{	
			if (e->m_is_wait)
				GetPixelResult(camera_name, e, true);
			else
				m_tx_thread = std::async(std::launch::async, &MilDlg::GetPixelResult, this, camera_name, e, false);
		}
		else if (camera_name == "TY" && !m_ty_thread.valid() || m_ty_thread._Is_ready())
		{		
			if (e->m_is_wait)
				GetPixelResult(camera_name, e, true);
			else
				m_ty_thread = std::async(std::launch::async, &MilDlg::GetPixelResult, this, camera_name, e, false);
		}
		else if (camera_name == "IDS" && !m_ids_thread.valid() || m_ids_thread._Is_ready())
		{	
			if (e->m_is_wait)
				GetPixelResult(camera_name, e, true);
			else
				m_ids_thread = std::async(std::launch::async, &MilDlg::GetPixelResult, this, camera_name, e, false);
		}
	}
	else if (type == ProjectEvent::e_JMilFindCenterEvent)
	{
		auto e = dynamic_cast<JMilFindCenterEvent*>(event);
		double point_x = 0.0;
		double point_y = 0.0;
		double point_r = 0.0;
		m_milManager->fnFindCircleCenter(e->m_x1, e->m_y1, e->m_x2, e->m_y2, e->m_x3, e->m_y3, point_x, point_y, point_r);
		e->m_pointX = point_x;
		e->m_pointY = point_y;
		e->m_pointR = point_r;
	}
	return 0;
}

void MilDlg::OnBtnClick(TNotifyUI & msg)
{
	CDuiString senderName = msg.pSender->GetName();
	if (senderName == _T("btn_openCamera"))
		OnBtnMilCameraOpenClick(msg);
	else if (senderName == _T("btn_closeCamera"))
		OnBtnMilCameraCloseClick(msg);
	else if (senderName == _T("btn_Continue"))
		OnRadioContinueModeClick(msg);
	else if (senderName == _T("btn_TriggerHw"))
		OnRadioHwTrigerModeClick(msg);
	else if (senderName == _T("btn_startGrabbing"))
		OnBtnStartGrabbingClick(msg);
	else if (senderName == _T("btn_stopGrabbing"))
		OnBtnStopGrabbingClick(msg);
	else if (senderName == _T("btn_LoadParasFromFile"))
		OnBtnLoadParasFromFileClick(msg);
	else if (senderName == _T("btn_exposureTimeGet"))
		OnBtnExposureTimeGetClick(msg);
	else if (senderName == _T("btn_exposureTimeSet"))
		OnBtnExposureTimeSetClick(msg);
	else if (senderName == _T("btn_frameRateGet"))
		OnBtnFrameRateGetClick(msg);
	else if (senderName == _T("btn_frameRateSet"))
		OnBtnFrameRateSetClick(msg);
	else if (senderName == _T("btn_gainGet"))
		OnBtnGainGetClick(msg);
	else if (senderName == _T("btn_gainSet"))
		OnBtnGainSetClick(msg);
	else if (senderName == _T("btn_blackLevelGet"))
		OnBtnBlackLevelGetClick(msg);
	else if (senderName == _T("btn_blackLevelSet"))
		OnBtnBlackLevelSetClick(msg);
	else if (senderName == _T("btn_TimeoutSet"))
		OnBtnTriggerModeTimeoutSetClick(msg);
	else if (senderName == _T("btn_Temperature"))
		OnBtnTemperatureClick(msg);
	else if (senderName == _T("btn_runModeGet"))
		OnBtnRunModeGetClick(msg);
	else if (senderName == _T("btn_runModeSet"))
		OnBtnRunModeSetClick(msg);
	else if (senderName == _T("btn_DotConfig"))
		OnBtnDotConfigClick(msg);
	else if (senderName == _T("btn_FloodConfig"))
		OnBtnFloodConfigClick(msg);
}

void MilDlg::OnBtnMilCameraOpenClick(TNotifyUI & msg)
{
	bool nRet = m_camera->Open();
	if (nRet)
		MessageBox(this->GetHWND(), "Open Mil Camera success", _T("Success"), MB_OK);
	else
		MessageBox(this->GetHWND(), "Open Mil Camera error", _T("Error"), MB_OK);
}

void MilDlg::OnBtnMilCameraCloseClick(TNotifyUI & msg)
{
	m_camera->Close();
}

void MilDlg::OnRadioContinueModeClick(TNotifyUI & msg)
{
	m_camera->SetRunMode(0);
}

void MilDlg::OnRadioHwTrigerModeClick(TNotifyUI & msg)
{
	m_camera->SetRunMode(1);
}

void MilDlg::OnBtnStartGrabbingClick(TNotifyUI & msg)
{
	// 连续模式一直采集
	int run_mode = m_camera->GetRunMode();
	if (run_mode == 0)
	{
		m_camera->SetStartGrabing(true);
		std::thread t(&CameraDILManager::StartGrabing, m_camera);
		t.detach();
	}
	else
	{
		//m_future = std::async(std::launch::async, &CameraDILManager::GetGrabImage, m_camera);
		std::thread t(&CameraDILManager::StartGrabing, m_camera);
		t.detach();
	}
}

void MilDlg::OnBtnStopGrabbingClick(TNotifyUI & msg)
{
	m_camera->SetStartGrabing(false);
}

void MilDlg::OnBtnLoadParasFromFileClick(TNotifyUI & msg)
{
}

void MilDlg::OnBtnExposureTimeGetClick(TNotifyUI & msg)
{
	int nRet = m_camera->GetExposure();
	m_pEdit_ExposureTime->SetText(Jup::Format("%d", nRet).c_str());
}

void MilDlg::OnBtnExposureTimeSetClick(TNotifyUI & msg)
{
	auto ex_time = m_pEdit_ExposureTime->GetText();
	m_camera->SetExposure(atoi(ex_time));
}

void MilDlg::OnBtnFrameRateGetClick(TNotifyUI & msg)
{
	int nRet = m_camera->GetFramePeriod();
	m_pEdit_FrameRate->SetText(Jup::Format("%d", nRet).c_str());
}

void MilDlg::OnBtnFrameRateSetClick(TNotifyUI & msg)
{
	auto period = m_pEdit_FrameRate->GetText();
	m_camera->SetFramePeriod(atoi(period));
}

void MilDlg::OnBtnGainGetClick(TNotifyUI & msg)
{
	int nRet = m_camera->GetGain();
	m_pEdit_Gain->SetText(Jup::Format("%d", nRet).c_str());
}

void MilDlg::OnBtnGainSetClick(TNotifyUI & msg)
{
	auto gain = m_pEdit_Gain->GetText();
	m_camera->SetGain(atoi(gain));
}

void MilDlg::OnBtnBlackLevelGetClick(TNotifyUI & msg)
{
	int nRet = m_camera->GetBlackLevel();
	m_pEdit_BlackLevel->SetText(Jup::Format("%d", nRet).c_str());
}

void MilDlg::OnBtnBlackLevelSetClick(TNotifyUI & msg)
{
	auto black_level = m_pEdit_BlackLevel->GetText();
	m_camera->SetBlackLevel(atoi(black_level));
}

void MilDlg::OnBtnTriggerModeTimeoutSetClick(TNotifyUI & msg)
{
	auto timeout = m_pEdit_Timeout->GetText();
	m_camera->SetRetryGrabCount(atoi(timeout));
}

void MilDlg::OnBtnTemperatureClick(TNotifyUI & msg)
{
	double nRet = m_camera->GetTemperature();
	m_pEdit_Temperature->SetText(Jup::Format("%d", nRet).c_str());
}

void MilDlg::OnBtnRunModeGetClick(TNotifyUI & msg)
{
	int nRet = m_camera->GetRunMode();
	m_pEdit_runMode->SetText(Jup::Format("%d", nRet).c_str());
}

void MilDlg::OnBtnRunModeSetClick(TNotifyUI & msg)
{
	auto run_mode = m_pEdit_runMode->GetText();
	m_camera->SetRunMode(atoi(run_mode));
}

void MilDlg::OnBtnDotConfigClick(TNotifyUI & msg)
{
	// 设置曝光
	int ex_time = jCore->GlobalSettings().ReadInt("DILCamera", "DotExposureTime");
	m_camera->SetExposure(ex_time);
	// 设置增益
	int gain = jCore->GlobalSettings().ReadInt("DILCamera", "DotGain");
	m_camera->SetGain(gain);
}

void MilDlg::OnBtnFloodConfigClick(TNotifyUI & msg)
{
	// 设置曝光
	int ex_time = jCore->GlobalSettings().ReadInt("DILCamera", "FloodExposureTime");
	m_camera->SetExposure(ex_time);
	// 设置增益
	int gain = jCore->GlobalSettings().ReadInt("DILCamera", "FloodGain");
	m_camera->SetGain(gain);
}

HBITMAP MilDlg::ConvertCharToHBITMAP(char * imageData, int width, int height)
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

void MilDlg::DisplayOneFrameImage(const char * image, int width, int height)
{
	m_pLable_MilImage->SetBkImage("");
	unsigned char* pData = (unsigned char*)image;
	unsigned short nWidth = width;
	unsigned short nHeight = height;

	HBITMAP hBmp = ConvertCharToHBITMAP((char*)pData, nWidth, nHeight);

	CDuiString sCtrlKey = "Image";
	m_PaintManager.RemoveImage(sCtrlKey, true);
	m_PaintManager.AddImage(sCtrlKey, hBmp, nWidth, nHeight, false, true);
	m_PaintManager.ReloadSharedImages();
	m_pLable_MilImage->SetBkImage(sCtrlKey);
}

void MilDlg::GetPixelResult(std::string camera_name, JMilFindModelEvent* e, bool is_wait)
{
	std::vector<PointXYA> Result;
	std::string file_out;
	m_milManager->VisionModelFindGetResult(e->m_file, file_out, e->m_file_mmf, Result);
	if (!Result.empty())
	{
		if (is_wait)
		{
			e->m_pointX = Result[0].X;
			e->m_pointY = Result[0].Y;
		}
		else
		{
			jCore->SendEvent(g_CalibrationWidget, &JCalibrationEvent("DisplayPixel", camera_name, Result[0].X, Result[0].Y));
		}
	}
}
