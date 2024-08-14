#include "IOConfigDlg.h"

LRESULT IOConfigDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void IOConfigDlg::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == "btn_IOParasSave")
		{
			OnBtnSaveClick(msg);
		}
		else if (msg.pSender->GetName() == "btn_ExitIOSetDlg")
		{
			this->Close();
		}
	}
}

void IOConfigDlg::InitWindow()
{
	m_pEdit_IONameEn = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_IONameEn"));
	m_pEdit_IONameCn = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_IONameCn"));
	m_pEdit_GroupName = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_GroupName"));
	m_pEdit_CardType = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_CardType"));
	m_pEdit_CardNum = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_CardNum"));
	m_pEdit_BitNum = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_BitNum"));
	m_pEdit_IsUse = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_IsUse"));
	m_pEdit_ElectricalLevel = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_ElectricalLevel"));

	if (!m_is_input)
	{
		CLabelUI* lable = static_cast<CLabelUI*>(m_PaintManager.FindControl("lable_IsUse"));
		lable->SetVisible(false);
		m_pEdit_IsUse->SetVisible(false);
	}
	// 显示数据
	updateConfigDisplay();
}

void IOConfigDlg::OnBtnSaveClick(TNotifyUI & msg)
{
	MotionIO* io_info = new MotionIO();

	io_info->name = m_pEdit_IONameEn->GetText().GetData();
	io_info->cnName = m_pEdit_IONameCn->GetText().GetData();
	io_info->group = m_pEdit_GroupName->GetText().GetData();
	io_info->cardType = m_pEdit_CardType->GetText().GetData();
	io_info->cardNum = atoi(m_pEdit_CardNum->GetText().GetData());
	io_info->bitNum = atoi(m_pEdit_BitNum->GetText().GetData());
	IOHash io_list;
	if (m_is_input)
	{
		io_info->isUsed = atoi(m_pEdit_IsUse->GetText().GetData());
		io_list = m_pMotionParameter->GetInputIOList();
	}
	else
	{
		io_list = m_pMotionParameter->GetOutputIOList();
	}
	if (m_is_new)
	{
		int max_id = 0;
		IOHash::iterator iter = io_list.begin();
		while (iter != io_list.end())
		{
			MotionIO* io_info = iter->second;
			if (max_id < io_info->id)
				max_id = io_info->id;
			iter++;
		}
		io_info->id = max_id + 1; // ID计数+1
	}
	else
		io_info->id = m_io->id;

	io_info->electrical_level = m_pEdit_ElectricalLevel->GetText().GetData();

	// 更新到数据库并更新IO数据结构
	bool ret = m_pMotionParameter->UpdateIOInfos(io_info, m_is_input);
	if (ret)
		MessageBox(this->GetHWND(), std::string("Update data success!").c_str(), _T("Prompt"), MB_OK);
	else
		MessageBox(this->GetHWND(), std::string("Update data fail!").c_str(), _T("Error"), MB_OK);

	if (io_info != NULL)
	{
		delete io_info;
		io_info = NULL;
	}
}

void IOConfigDlg::updateConfigDisplay()
{
	CDuiString editStr;
	m_pEdit_IONameEn->SetText(m_io->name.c_str());

	m_pEdit_IONameCn->SetText(m_io->cnName.c_str());

	m_pEdit_GroupName->SetText(m_io->group.c_str());

	m_pEdit_CardType->SetText(m_io->cardType.c_str());

	editStr.Format("%d", m_io->cardNum);
	m_pEdit_CardNum->SetText(editStr);

	editStr.Format("%d", m_io->bitNum);
	m_pEdit_BitNum->SetText(editStr);

	if (m_is_input)
	{
		editStr.Format("%d", m_io->isUsed);
		m_pEdit_IsUse->SetText(editStr);
	}

	m_pEdit_ElectricalLevel->SetText(m_io->electrical_level.c_str());
}
