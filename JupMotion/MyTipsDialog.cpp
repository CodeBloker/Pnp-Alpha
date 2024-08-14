#include "MyTipsDialog.h"
#include "CPluginDlg.h"
LRESULT MyTipsDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_TIPS_RECV_MOVEDONE)
	{
		OnMoveDone(wParam, lParam);
	}

	if (uMsg == WM_TIPS_SEND_STOP)
	{
		int i = 0;
		i++;
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void MyTipsDialog::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == _T("Tip_Btn_Stop"))
		{
			//CPluginDlg* pdlg = dynamic_cast<CPluginDlg*>(m_pParentWnd);
			//MotionController* pMotion = dynamic_cast<MotionController*>(pdlg->m_pMotion);
			//HWND parentHwnd = pdlg->GetHWND();
			g_pMotion->AxisStopWait();
			g_pMotion->StopAxis(m_cur_axis, 0);
			//::PostMessage(parentHwnd, WM_TIPS_SEND_STOP, 0, 0);
			//Sleep(200);
			//::PostMessage(this->GetHWND(), WM_CLOSE, 0, 0);
		}
	}

	__super::Notify(msg);
}

void MyTipsDialog::SetText(CDuiString log)
{
	CLabelUI* pText = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("Tip_Text")));
	pText->SetText(log);
}

void MyTipsDialog::OnMoveDone(WPARAM wParam, LPARAM lParam)
{
	::PostMessage(this->GetHWND(), WM_CLOSE, 0, 0);
}
