#include "SerialView.h"

#include "JupCore.h"
#include <atltime.h>

SerialView::SerialView()
{
	m_pSerial = SerialControl::GetInstance();
}

SerialView::~SerialView()
{	
	if (m_pSerial)
	{
		m_pSerial->CloseAllLight();
		m_pSerial->CloseTempSensor();
	}
}

UILIB_RESOURCETYPE SerialView::GetResourceType() const
{
	return UILIB_ZIP;
}

CDuiString SerialView::GetSkinFolder()
{
	return "";
}

CDuiString SerialView::GetSkinFile()
{
	return "main_frame.xml";
}

CDuiString SerialView::GetZIPFileName() const
{
	return "PluginSerial.zip";
}

LPCTSTR SerialView::GetWindowClassName() const
{
	return "SerialView";
}

LRESULT SerialView::ResponseDefaultKeyEvent(WPARAM wParam)
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

void SerialView::InitWindow()
{	
	m_pList_Output = static_cast<CListUI*>(m_PaintManager.FindControl(_T("list_output")));
	m_pEdit_Input = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_intput")));

	m_pSerial->OpenLightSource();
	m_pSerial->OpenAllLight();
	m_pSerial->OpenTempSensor();
	m_pSerial->OpenTempSensor2();
	m_pSerial->OpenHeighSensor1();
	m_pSerial->OpenHeighSensor2();
	m_pSerial->OpenHeighSensor3();
	m_pSerial->OpenKeyenceHeighSensor();
}

void SerialView::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
}

void SerialView::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		OnBtnClick(msg);
	}
	else if (msg.sType == DUI_MSGTYPE_ITEMCLICK)
	{

	}
}

LRESULT SerialView::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT res = 0;

	if (uMsg == WM_CREATE)
	{
	}

	res = __super::HandleMessage(uMsg, wParam, lParam);
	return res;
}

LRESULT SerialView::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT SerialView::CustomEvent(JupCustomEvent * event)
{
	JupCustomEvent::eType type = event->Type();

	return 0;
}

void SerialView::ShowMsg(const char * str)
{
	CTime time = CTime::GetCurrentTime();
	char buf[64] = { 0 };
	sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d    ", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	std::string strText = buf + std::string(str);
	CLabelUI* label = new CLabelUI;
	label->SetFixedHeight(20);
	label->SetText(strText.c_str());
	m_pList_Output->Add(label);

	if (m_pList_Output->GetCount() >= 1000)
	{
		m_pList_Output->Remove(0);
	}
}

void SerialView::OnBtnClick(TNotifyUI & msg)
{
	auto senderName = msg.pSender->GetName();

	if (senderName == _T("btn_OpenAlphaLight1"))
		OnBtnAlphaLight1OpenClick(msg);
	else if (senderName == _T("btn_OpenAlphaLight2"))
		OnBtnAlphaLight2OpenClick(msg);
	else if (senderName == _T("btn_AlphaOpenAllLight"))
		OnBtnAlphaOpenAllLightClick(msg);
	else if (senderName == _T("btn_AlphaCloseAllLight"))
		OnBtnAlphaCloseAllLightClick(msg);
	else if (senderName == _T("btn_CommandSend"))
		OnBtnCommandSendClick(msg);
	else if (senderName == _T("btn_DisplayClear"))
		OnBtnClearUIClick(msg);
	else if (senderName == _T("btn_Temp1Get"))
		OnBtnTemp1GetClick(msg);
	else if (senderName == _T("btn_Temp2Get"))
		OnBtnTemp2GetClick(msg);
	else if (senderName == _T("btn_Heigh1Get"))
		OnBtnHeigh1GetClick(msg);
	else if (senderName == _T("btn_Heigh2Get"))
		OnBtnHeigh2GetClick(msg);
	else if (senderName == _T("btn_Heigh3Get"))
		OnBtnHeigh3GetClick(msg);
}

void SerialView::OnBtnAlphaLight1OpenClick(TNotifyUI & msg)
{
	bool ret = m_pSerial->OpenHikCamera1Light();
	if (ret)
		ShowMsg("Open Light1 success");
	else
		ShowMsg("Open Light1 fail");
}

void SerialView::OnBtnAlphaLight2OpenClick(TNotifyUI & msg)
{
	bool ret = m_pSerial->OpenHikCamera2Light();
	if (ret)
		ShowMsg("Open Light2 success");
	else
		ShowMsg("Open Light2 fail");
}

void SerialView::OnBtnAlphaOpenAllLightClick(TNotifyUI & msg)
{
	bool ret = m_pSerial->OpenAllLight();
	if (ret)
		ShowMsg("OpenAllLight success");
	else
	{
		std::string msg = "OpenAllLight fail";
		MessageBox(this->GetHWND(), msg.c_str(), _T("Error"), MB_OK);
		ShowMsg("OpenAllLight fail");
	}
}

void SerialView::OnBtnAlphaCloseAllLightClick(TNotifyUI & msg)
{
	bool ret = m_pSerial->CloseAllLight();
	if (ret)
		ShowMsg("CloseAllLight success");
	else
		ShowMsg("CloseAllLight fail");
}

void SerialView::OnBtnTemp1GetClick(TNotifyUI & msg)
{
	std::string temp = m_pSerial->ReadTemp();
	if (!temp.empty())
	{
		temp = "ReadTemp1 = " + temp;
		ShowMsg(temp.c_str());
	}
	else
		ShowMsg("ReadTemp1 fail");
}

void SerialView::OnBtnTemp2GetClick(TNotifyUI & msg)
{
	std::string temp = m_pSerial->ReadTemp2();
	if (!temp.empty())
	{
		temp = "ReadTemp2 = " + temp;
		ShowMsg(temp.c_str());
	}
	else
		ShowMsg("ReadTemp2 fail");
}

void SerialView::OnBtnHeigh1GetClick(TNotifyUI & msg)
{
	std::string heigh = m_pSerial->ReadHeigh1();
	if (!heigh.empty())
	{
		heigh = "ReadOmronHeigh1 = " + heigh;
		ShowMsg(heigh.c_str());
	}
	else
		ShowMsg("ReadOmronHeigh1 fail");
}

void SerialView::OnBtnHeigh2GetClick(TNotifyUI & msg)
{
	std::string heigh = m_pSerial->ReadHeigh2();
	if (!heigh.empty())
	{
		heigh = "ReadOmronHeigh2 = " + heigh;
		ShowMsg(heigh.c_str());
	}
	else
		ShowMsg("ReadOmronHeigh2 fail");
}

void SerialView::OnBtnHeigh3GetClick(TNotifyUI & msg)
{
	std::string heigh = m_pSerial->ReadHeigh3();
	if (!heigh.empty())
	{
		heigh = "ReadOmronHeigh3 = " + heigh;
		ShowMsg(heigh.c_str());
	}
	else
		ShowMsg("ReadOmronHeigh3 fail");
}

void SerialView::OnBtnCommandSendClick(TNotifyUI & msg)
{
	//std::string temp = m_pSerial->ReadTemp2();
	////std::string temp = m_pSerial->ReadHeigh();
	//if (!temp.empty())
	//	ShowMsg("CloseAllLight success");
	//else
	//	ShowMsg("CloseAllLight fail");
}

void SerialView::OnBtnClearUIClick(TNotifyUI & msg)
{
	m_pEdit_Input->SetText("");
	m_pList_Output->RemoveAll();
}
