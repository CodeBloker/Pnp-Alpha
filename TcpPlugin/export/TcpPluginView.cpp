#include "TcpPluginView.h"
#include "TcpController.h"
#include <atltime.h>
#include "JupCore.h"

TcpPluginView::TcpPluginView()
{
	m_tcp = TcpController::GetInstance();
}

TcpPluginView::~TcpPluginView()
{	
}

UILIB_RESOURCETYPE TcpPluginView::GetResourceType() const
{
	return UILIB_ZIP;
}

CDuiString TcpPluginView::GetSkinFolder()
{
	return "";
}

CDuiString TcpPluginView::GetSkinFile()
{
	return "main_frame.xml";
}

CDuiString TcpPluginView::GetZIPFileName() const
{
	return "PluginTcp.zip";
}

LPCTSTR TcpPluginView::GetWindowClassName() const
{
	return "TcpPluginView";
}

LRESULT TcpPluginView::ResponseDefaultKeyEvent(WPARAM wParam)
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

void TcpPluginView::InitWindow()
{
	m_pList_TcpOutput = static_cast<CListUI*>(m_PaintManager.FindControl(_T("tcp_output")));
}

void TcpPluginView::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
}

void TcpPluginView::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		OnBtnClick(msg);
	}
}

LRESULT TcpPluginView::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT res = 0;

	if (uMsg == WM_CREATE)
	{
	}

	res = __super::HandleMessage(uMsg, wParam, lParam);
	return res;
}

LRESULT TcpPluginView::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT TcpPluginView::CustomEvent(JupCustomEvent * event)
{
	JupCustomEvent::eType type = event->Type();

	return 0;
}

void TcpPluginView::ShowMsg(const char * msg)
{
	CTime time = CTime::GetCurrentTime();
	char buf[128] = { 0 };
	sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d    ", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	std::string strText = buf + std::string(msg);
	CLabelUI* label = new CLabelUI;
	label->SetFixedHeight(20);
	label->SetText(strText.c_str());
	m_pList_TcpOutput->Add(label);
	// 超过500行删除最前
	if (m_pList_TcpOutput->GetCount() >= 500)
	{
		m_pList_TcpOutput->Remove(0);
	}
}

void TcpPluginView::OnBtnClick(TNotifyUI & msg)
{
	CDuiString senderName = msg.pSender->GetName();

	if (senderName == _T("btn_clearList"))
		OnClearListClick(msg);
	else if (senderName == _T("btn_getACLVal"))
		OnGetACLValuesClick(msg);
	else if (senderName == _T("btn_ConfocalGetValue1"))
		OnConfocalGetValue1Click(msg);
	else if (senderName == _T("btn_ConfocalGetValue2"))
		OnConfocalGetValue2Click(msg);
}

void TcpPluginView::OnClearListClick(TNotifyUI & msg)
{
	m_pList_TcpOutput->RemoveAll();
}

void TcpPluginView::OnGetACLValuesClick(TNotifyUI & msg)
{
	double Tx;
	double Ty;
	if (m_tcp->ConnectTcpGetACLValue(Tx, Ty))
	{
		char buf[256] = { 0 };
		sprintf_s(buf, "ACL Value: Tx = %f, Ty = %f", Tx, Ty);
		ShowMsg(buf);
		return;
	}
	ShowMsg("Get ACL values failed!");
}

void TcpPluginView::OnConfocalGetValue1Click(TNotifyUI & msg)
{
	std::string ip = jCore->GlobalSettings().ReadString("TcpPlugin", "ConfocalSensor1_IP");
	unsigned short port = jCore->GlobalSettings().ReadInt("TcpPlugin", "ConfocalSensor1_PORT");
	std::string command = "MS,0,1\r";
	double value;
	if (m_tcp->ConnectAndGetConfocalValue(ip, port, command, value))
	{
		char buf[256] = { 0 };
		sprintf_s(buf, "Confocal sensor1 value: %f", value);
		ShowMsg(buf);
		return;
	}
	ShowMsg("GetConfocalValue1 failed!");
}

void TcpPluginView::OnConfocalGetValue2Click(TNotifyUI & msg)
{
	std::string ip = jCore->GlobalSettings().ReadString("TcpPlugin", "ConfocalSensor2_IP");
	unsigned short port = jCore->GlobalSettings().ReadInt("TcpPlugin", "ConfocalSensor2_PORT");
	std::string command = "MS,0,1\r";
	double value;
	if (m_tcp->ConnectAndGetConfocalValue(ip, port, command, value))
	{
		char buf[256] = { 0 };
		sprintf_s(buf, "Confocal sensor2 value: %f", value);
		ShowMsg(buf);
		return;
	}
	ShowMsg("GetConfocalValue2 failed!");
}
