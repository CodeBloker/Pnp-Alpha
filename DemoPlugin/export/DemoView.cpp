#include "DemoView.h"

#include "JupCore.h"

DemoView::DemoView()
{
}

DemoView::~DemoView()
{	
}

UILIB_RESOURCETYPE DemoView::GetResourceType() const
{
	return UILIB_ZIP;
}

CDuiString DemoView::GetSkinFolder()
{
	return "";
}

CDuiString DemoView::GetSkinFile()
{
	return "DemoView.xml";
}

CDuiString DemoView::GetZIPFileName() const
{
	return "DemoPlugin.zip";
}

LPCTSTR DemoView::GetWindowClassName() const
{
	return "DemoView";
}

LRESULT DemoView::ResponseDefaultKeyEvent(WPARAM wParam)
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

void DemoView::InitWindow()
{	
}

void DemoView::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
}

void DemoView::Notify(TNotifyUI & msg)
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

LRESULT DemoView::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT res = 0;

	if (uMsg == WM_CREATE)
	{
	}

	res = __super::HandleMessage(uMsg, wParam, lParam);
	return res;
}

LRESULT DemoView::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT DemoView::CustomEvent(JupCustomEvent * event)
{
	JupCustomEvent::eType type = event->Type();

	return 0;
}
