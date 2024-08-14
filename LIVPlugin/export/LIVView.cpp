#include "LIVView.h"

#include "JupCore.h"

LIVView::LIVView()
{
}

LIVView::~LIVView()
{	
}

UILIB_RESOURCETYPE LIVView::GetResourceType() const
{
	return UILIB_ZIP;
}

CDuiString LIVView::GetSkinFolder()
{
	return "";
}

CDuiString LIVView::GetSkinFile()
{
	return "main_frame.xml";
}

CDuiString LIVView::GetZIPFileName() const
{
	return "PluginLIV.zip";
}

LPCTSTR LIVView::GetWindowClassName() const
{
	return "LIVView";
}

LRESULT LIVView::ResponseDefaultKeyEvent(WPARAM wParam)
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

void LIVView::InitWindow()
{	
}

void LIVView::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
}

void LIVView::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (msg.pSender->GetName() == "")
		{

		}
	}
	else if (msg.sType == DUI_MSGTYPE_ITEMCLICK)
	{

	}
}

CControlUI * LIVView::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT LIVView::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT res = 0;

	if (uMsg == WM_CREATE)
	{
	}

	res = __super::HandleMessage(uMsg, wParam, lParam);
	return res;
}

LRESULT LIVView::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT LIVView::CustomEvent(JupCustomEvent * event)
{
	JupCustomEvent::eType type = event->Type();

	return 0;
}
