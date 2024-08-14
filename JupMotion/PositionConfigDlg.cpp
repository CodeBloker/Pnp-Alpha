#include "PositionConfigDlg.h"
#include "Macro.h"

LRESULT PositionConfigDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void PositionConfigDlg::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == "btn_AxisParasSave")
		{
			OnBtnSaveClick(msg);
		}
		else if (msg.pSender->GetName() == "btn_CloseDlg")
		{
			this->Close();
		}
	}
}

void PositionConfigDlg::InitWindow()
{
	m_pLable_CurrentAxis = static_cast<CLabelUI*>(m_PaintManager.FindControl("lable_CurrentAxis"));
	m_pLable_AxisId = static_cast<CLabelUI*>(m_PaintManager.FindControl("lable_AxisId"));
	m_pEdit_PosName = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_PosName"));
	m_pEdit_Distance = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_Distance"));
	m_pEdit_Spacing = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_Spacing"));
	m_pEdit_PosMarkCn = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_PosMarkCn"));

	// 显示数据
	updateConfigDisplay(m_is_new_pos);
}

void PositionConfigDlg::OnBtnSaveClick(TNotifyUI & msg)
{
	AxisPosition* pos_info = NULL;
	if (m_is_new_pos)
	{
		pos_info = new AxisPosition();
		int max_id = 0;
		auto axis_list = m_pMotionParameter->GetAxisNameList();
		for (auto axis_name : axis_list)
		{
			auto pos_list = m_pMotionParameter->GetAxisPosListInfo(axis_name);
			for (auto posPtr : pos_list)
			{
				if (max_id < posPtr->posID)
					max_id = posPtr->posID;
			}
		}
		// ID计数+1
		pos_info->posID = max_id + 1;
	}
	else
		pos_info = m_pMotionParameter->GetAxisPosInfo(m_axis, m_pos);

	pos_info->axisName = m_pLable_CurrentAxis->GetText().GetData();
	pos_info->axisID = atoi(m_pLable_AxisId->GetText().GetData());
	pos_info->posName = m_pEdit_PosName->GetText().GetData();
	pos_info->distance = atof(m_pEdit_Distance->GetText().GetData());
	pos_info->spacing = atof(m_pEdit_Spacing->GetText().GetData());
	pos_info->notes = m_pEdit_PosMarkCn->GetText().GetData();

	// 更新到数据库并更新轴数据结构
	bool ret = m_pMotionParameter->UpdatePosInfos(pos_info);
	if (ret)
		MessageBox(this->GetHWND(), std::string("Update data success!").c_str(), _T("Prompt"), MB_OK);
	else
		MessageBox(this->GetHWND(), std::string("Update data fail!").c_str(), _T("Error"), MB_OK);

	if (m_is_new_pos && pos_info != NULL)
	{
		delete pos_info;
		pos_info = NULL;
	}
}

void PositionConfigDlg::updateConfigDisplay(bool is_new)
{
	AxisPosition* pos_paras = NULL;
	if (is_new)
		pos_paras = new AxisPosition();
	else
		pos_paras = m_pMotionParameter->GetAxisPosInfo(m_axis, m_pos);

	auto axis_paras = m_pMotionParameter->GetAxisParam(m_axis);

	m_pLable_CurrentAxis->SetText(m_axis.c_str());

	CDuiString editStr;
	editStr.Format("%d", axis_paras->axisID);
	m_pLable_AxisId->SetText(editStr);

	m_pEdit_PosName->SetText(pos_paras->posName.c_str());

	editStr.Format("%f", pos_paras->distance);
	m_pEdit_Distance->SetText(editStr);

	editStr.Format("%f", pos_paras->spacing);
	m_pEdit_Spacing->SetText(editStr);

	m_pEdit_PosMarkCn->SetText(pos_paras->notes.c_str());
}
