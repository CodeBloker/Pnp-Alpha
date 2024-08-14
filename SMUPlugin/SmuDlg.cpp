#include "SmuDlg.h"
#include <atltime.h>

SmuDlg::SmuDlg()
{
	m_smu = new SmuControl();
}

SmuDlg::~SmuDlg()
{	
}

UILIB_RESOURCETYPE SmuDlg::GetResourceType() const
{
	return UILIB_ZIP;
}

CDuiString SmuDlg::GetSkinFolder()
{
	return "";
}

CDuiString SmuDlg::GetSkinFile()
{
	return "main_frame.xml";
}

CDuiString SmuDlg::GetZIPFileName() const
{
	return _T("PluginSmu.zip");
}

LPCTSTR SmuDlg::GetWindowClassName() const
{
	return "SmuDlg";
}

LRESULT SmuDlg::ResponseDefaultKeyEvent(WPARAM wParam)
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

void SmuDlg::InitWindow()
{	
	m_pList_SmuOutput = static_cast<CListUI*>(m_PaintManager.FindControl(_T("smu_output")));
	m_pEdit_SmuCommand = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("smu_intput")));

}

void SmuDlg::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	PostQuitMessage(0);
}

void SmuDlg::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		OnBtnClick(msg);
	}
}

CControlUI * SmuDlg::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT SmuDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT SmuDlg::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT SmuDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	int ret = MessageBoxA(NULL, "是否退出程序？", "Quit", MB_YESNO);
	if (ret == IDYES)
		bHandled = FALSE;	//TRUE表示不处理
	else
		bHandled = TRUE;
	return 0;
}

void SmuDlg::OnExit(TNotifyUI & msg)
{
	this->Close();
}

void SmuDlg::ShowMsg(const char * str)
{
	CTime time = CTime::GetCurrentTime();
	char buf[64] = { 0 };
	sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d    ", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	std::string strText = buf + std::string(str);
	CLabelUI* label = new CLabelUI;
	label->SetFixedHeight(20);
	label->SetText(strText.c_str());
	m_pList_SmuOutput->Add(label);

	if (m_pList_SmuOutput->GetCount() >= 1000)
	{
		m_pList_SmuOutput->Remove(0);
	}
}

void SmuDlg::OnBtnClick(TNotifyUI & msg)
{
	if (msg.pSender->GetName() == _T("btn_SmuOpen"))
	{
		OnBtnSmuConnectClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_SmuClose"))
	{
		OnBtnSmuDisConnectClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_SmuCommandSend"))
	{
		OnBtnSmuCommandSendClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_SmuDisplayClear"))
	{
		OnBtnSmuClearUIClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_SmuDotLight"))
	{
		OnBtnSmuDotLightClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_SmuBufRead"))
	{
		OnBtnSmuBufReadClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_SmuGetVersion"))
	{
		OnBtnSmuVersionClick(msg);
	}
}

void SmuDlg::OnBtnSmuConnectClick(TNotifyUI & msg)
{
	bool ret = m_smu->fnSMUDevImpl();
	if (ret)
		ShowMsg("Smu connect success");
	else
		ShowMsg("Smu connect fail");
}

void SmuDlg::OnBtnSmuDisConnectClick(TNotifyUI & msg)
{
	bool ret = m_smu->fnSMUDevDestory();
	if (ret)
		ShowMsg("Smu disconnect success");
	else
		ShowMsg("Smu disconnect fail");
}

void SmuDlg::OnBtnSmuDotLightClick(TNotifyUI & msg)
{
	const char* strCommand = "TxDrive_Measure(1.3365,0.055,0.055,0,3.0,0.002,0.00325,0.005,1,1,2)";
	bool ret = m_smu->ExecuteCommand(false, "SMU1", strCommand);
	if (ret)
	{
		//char readedBuffer[VISA_BUFFER] = { 0L, };
		//ret = m_smu->ReadResult("SMU1", readedBuffer, _countof(readedBuffer));
		//if (ret)
		//{
		//	ShowMsg(readedBuffer);
		//}
		std::string str = strCommand + std::string(" success");
		ShowMsg(str.c_str());
	}
}

void SmuDlg::OnBtnSmuFloodLightClick(TNotifyUI & msg)
{
	const char* strCommand = "TxDrive_Measure(0,0,0,1.89,3.0,0.002,0.00285,0.0167,6,6,2)";
	bool ret = m_smu->ExecuteCommand(false, "SMU1", strCommand);
	if (ret)
	{
		//char readedBuffer[VISA_BUFFER] = { 0L, };
		//ret = m_smu->ReadResult("SMU1", readedBuffer, _countof(readedBuffer));
		//if (ret)
		//{
		//	ShowMsg(readedBuffer);
		//}
		std::string str = strCommand + std::string(" success");
		ShowMsg(str.c_str());
	}
}

void SmuDlg::OnBtnSmuDarkLightClick(TNotifyUI & msg)
{
	const char* strCommand = "TxDrive_Measure(0, 0, 0, 0, 4.5, 0.002, 0.00325, 0.005, 1, 1, 2)";
	bool ret = m_smu->ExecuteCommand(false, "SMU1", strCommand);
	if (ret)
	{
		//char readedBuffer[VISA_BUFFER] = { 0L, };
		//ret = m_smu->ReadResult("SMU1", readedBuffer, _countof(readedBuffer));
		//if (ret)
		//{
		//	ShowMsg(readedBuffer);
		//}
		std::string str = strCommand + std::string(" success");
		ShowMsg(str.c_str());
	}
}

void SmuDlg::OnBtnSmuBufReadClick(TNotifyUI & msg)
{
	const char* strCommand = "Buffer_Read()";
	bool ret = m_smu->ExecuteCommand(false, "SMU1", strCommand);
	if (ret)
	{
		char readedBuffer[VISA_BUFFER] = { 0L, };
		ret = m_smu->ReadResult("SMU1", readedBuffer, _countof(readedBuffer));
		if (ret)
		{
			ShowMsg(readedBuffer);
		}
	}
}

void SmuDlg::OnBtnSmuVersionClick(TNotifyUI & msg)
{
	const char* strCommand = "Script_Version()";
	bool ret = m_smu->ExecuteCommand(false, "SMU1", strCommand);
	if (ret)
	{
		char readedBuffer[VISA_BUFFER] = { 0L, };
		ret = m_smu->ReadResult("SMU1", readedBuffer, _countof(readedBuffer));
		if (ret)
		{
			ShowMsg(readedBuffer);
		}
	}
}

void SmuDlg::OnBtnSmuCommandSendClick(TNotifyUI & msg)
{
	const char* strCommand = m_pEdit_SmuCommand->GetText().GetData();
	bool ret = m_smu->ExecuteCommand(false, "SMU1", strCommand);
	if (ret)
	{
		char readedBuffer[VISA_BUFFER] = { 0L, };
		do
		{
			memset(readedBuffer, 0, VISA_BUFFER);
			ret = m_smu->ReadResult("SMU1", readedBuffer, _countof(readedBuffer));
			if (ret)
			{
				ShowMsg(readedBuffer);
			}
		} while (ret);

	}
}

void SmuDlg::OnBtnSmuClearUIClick(TNotifyUI & msg)
{
	m_pEdit_SmuCommand->SetText("");
	m_pList_SmuOutput->RemoveAll();
}
