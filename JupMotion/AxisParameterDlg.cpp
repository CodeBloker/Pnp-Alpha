#include "AxisParameterDlg.h"

LRESULT AxisParameterDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CLOSE)
	{
		PostQuitMessage(0);
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void AxisParameterDlg::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == _T("btn_AxisParasSave"))
		{
			OnBtnAxisParasSaveClick(msg);
		}
		else if (msg.pSender->GetName() == _T("btn_AxisParasSave"))
		{
			PostQuitMessage(0);
		}
	}
	//__super::Notify(msg);
}

void AxisParameterDlg::OnBtnAxisParasSaveClick(TNotifyUI & msg)
{
}
