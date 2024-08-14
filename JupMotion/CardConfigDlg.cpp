#include "CardConfigDlg.h"
#include "Macro.h"

LRESULT CardConfigDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CardConfigDlg::Notify(TNotifyUI & msg)
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

void CardConfigDlg::InitWindow()
{
	m_pEdit_CurrentAxis = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_CurrentAxis"));
	m_pEdit_CurrentAxisCn = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_CurrentAxisCn"));
	m_pEdit_MotorType = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_MotorType"));
	m_pEdit_CardType = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_CardType"));
	m_pEdit_CardNum = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_CardNum"));
	m_pEdit_AxisNum = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_AxisNum"));
	m_pEdit_AxisMinSpeed = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_AxisMinSpeed"));
	m_pEdit_AxisMaxSpeed = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_AxisMaxSpeed"));
	m_pEdit_AxisAcc = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_AxisAcc"));
	m_pEdit_AxisDec = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_AxisDec"));
	m_pEdit_AxisStopSpeed = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_AxisStopSpeed"));
	m_pEdit_AxisCurve = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_AxisCurve"));
	m_pEdit_AllowErrorPos = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_AllowErrorPos"));
	m_pEdit_Scale = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_Scale"));
	m_pEdit_Lead = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_Lead"));
	m_pEdit_HomeMode = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_HomeMode"));
	m_pEdit_HomeDir = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_HomeDir"));
	m_pEdit_HomeMinSpeed = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_HomeMinSpeed"));
	m_pEdit_HomeMaxSpeed = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_HomeMaxSpeed"));
	m_pEdit_HomeAcc = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_HomeAcc"));
	m_pEdit_HomeDec = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_HomeDec"));
	m_pEdit_HomeOffset = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_HomeOffset"));
	m_pEdit_HomeCurve = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_HomeCurve"));
	m_pEdit_HomeEZA = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_HomeEZA"));
	m_pEdit_UseDelay = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_useDelay"));
	m_pEdit_DelayTime = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_DelayTime"));
	m_pEdit_UseLimit = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_useLimit"));
	m_pEdit_PositiveLimit = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_PositiveLimit"));
	m_pEdit_NegativeLimit = static_cast<CEditUI*>(m_PaintManager.FindControl("edit_NegativeLimit"));

	// 显示数据
	updateConfigDisplay(m_is_new_axis);
}

void CardConfigDlg::OnBtnSaveClick(TNotifyUI & msg)
{
	MotionAxis* axis_info = NULL;
	if (m_is_new_axis)
	{
		axis_info = new MotionAxis();
		int axis_count = m_pMotionParameter->GetAxisNameList().size();
		// ID计数+1
		axis_info->axisID = axis_count + 1;
	}
	else
		axis_info = m_pMotionParameter->GetAxisParam(m_axis);

	axis_info->axisName = m_pEdit_CurrentAxis->GetText().GetData();;
	axis_info->axisNameCn = m_pEdit_CurrentAxisCn->GetText().GetData();
	axis_info->motorType = m_pEdit_MotorType->GetText().GetData();
	axis_info->cardType = m_pEdit_CardType->GetText().GetData();
	axis_info->cardNum = atoi(m_pEdit_CardNum->GetText().GetData());
	axis_info->axisNum = atoi(m_pEdit_AxisNum->GetText().GetData());
	axis_info->minVel = atof(m_pEdit_AxisMinSpeed->GetText().GetData());
	axis_info->maxVel = atof(m_pEdit_AxisMaxSpeed->GetText().GetData());
	axis_info->accVel = atof(m_pEdit_AxisAcc->GetText().GetData());
	axis_info->decVel = atof(m_pEdit_AxisDec->GetText().GetData());
	axis_info->stopVel = atof(m_pEdit_AxisStopSpeed->GetText().GetData());
	axis_info->sPara = atof(m_pEdit_AxisCurve->GetText().GetData());
	axis_info->allowErrorPos = atof(m_pEdit_AllowErrorPos->GetText().GetData());
	axis_info->equiv = atof(m_pEdit_Scale->GetText().GetData());
	axis_info->lead = atof(m_pEdit_Lead->GetText().GetData());
	axis_info->homeMode = atoi(m_pEdit_HomeMode->GetText().GetData());
	axis_info->homeDir = atoi(m_pEdit_HomeDir->GetText().GetData());
	axis_info->homeMinVel = atof(m_pEdit_HomeMinSpeed->GetText().GetData());
	axis_info->homeMaxVel = atof(m_pEdit_HomeMaxSpeed->GetText().GetData());
	axis_info->homeAccVel = atof(m_pEdit_HomeAcc->GetText().GetData());
	axis_info->homeDecVel = atof(m_pEdit_HomeDec->GetText().GetData());
	axis_info->homeOffsetPos = atof(m_pEdit_HomeOffset->GetText().GetData());
	axis_info->homeCurve = atof(m_pEdit_HomeCurve->GetText().GetData());
	axis_info->homeEZA = atoi(m_pEdit_HomeEZA->GetText().GetData());
	axis_info->useDelay = atoi(m_pEdit_UseDelay->GetText().GetData());
	axis_info->msTimeout = atoi(m_pEdit_DelayTime->GetText().GetData());
	axis_info->useLimit = atoi(m_pEdit_UseLimit->GetText().GetData());
	axis_info->positiveLimit = atof(m_pEdit_PositiveLimit->GetText().GetData());
	axis_info->negativeLimit = atof(m_pEdit_NegativeLimit->GetText().GetData());
	// 更新到数据库并更新轴数据结构
	bool ret = m_pMotionParameter->UpdateAxisInfos(axis_info);
	if (ret)
		MessageBox(this->GetHWND(), std::string("Update data success!").c_str(), _T("Prompt"), MB_OK);
	else
		MessageBox(this->GetHWND(), std::string("Update data fail!").c_str(), _T("Error"), MB_OK);

	if (m_is_new_axis && axis_info != NULL)
	{
		delete axis_info;
		axis_info = NULL;
	}
}

void CardConfigDlg::updateConfigDisplay(bool is_new)
{
	MotionAxis* paras = NULL;
	if (is_new)
		paras = new MotionAxis();
	else
		paras = m_pMotionParameter->GetAxisParam(m_axis);

	m_pEdit_CurrentAxis->SetText(m_axis.c_str());

	CDuiString editStr;
	m_pEdit_CurrentAxisCn->SetText(paras->axisNameCn.c_str());

	m_pEdit_MotorType->SetText(paras->motorType.c_str());

	m_pEdit_CardType->SetText(paras->cardType.c_str());

	editStr.Format("%d", paras->cardNum);
	m_pEdit_CardNum->SetText(editStr);

	editStr.Format("%d", paras->axisNum);
	m_pEdit_AxisNum->SetText(editStr);

	editStr.Format("%f", paras->minVel);
	m_pEdit_AxisMinSpeed->SetText(editStr);

	editStr.Format("%f", paras->maxVel);
	m_pEdit_AxisMaxSpeed->SetText(editStr);

	editStr.Format("%f", paras->accVel);
	m_pEdit_AxisAcc->SetText(editStr);

	editStr.Format("%f", paras->decVel);
	m_pEdit_AxisDec->SetText(editStr);

	editStr.Format("%f", paras->stopVel);
	m_pEdit_AxisStopSpeed->SetText(editStr);

	editStr.Format("%f", paras->sPara);
	m_pEdit_AxisCurve->SetText(editStr);

	editStr.Format("%f", paras->allowErrorPos);
	m_pEdit_AllowErrorPos->SetText(editStr);

	editStr.Format("%f", paras->equiv);
	m_pEdit_Scale->SetText(editStr);

	editStr.Format("%f", paras->lead);
	m_pEdit_Lead->SetText(editStr);

	editStr.Format("%d", paras->homeMode);
	m_pEdit_HomeMode->SetText(editStr);

	editStr.Format("%d", paras->homeDir);
	m_pEdit_HomeDir->SetText(editStr);

	editStr.Format("%f", paras->homeMinVel);
	m_pEdit_HomeMinSpeed->SetText(editStr);

	editStr.Format("%f", paras->homeMaxVel);
	m_pEdit_HomeMaxSpeed->SetText(editStr);	
	
	editStr.Format("%f", paras->homeAccVel);
	m_pEdit_HomeAcc->SetText(editStr);

	editStr.Format("%f", paras->homeDecVel);
	m_pEdit_HomeDec->SetText(editStr);

	editStr.Format("%f", paras->homeOffsetPos);
	m_pEdit_HomeOffset->SetText(editStr);

	editStr.Format("%f", paras->homeCurve);
	m_pEdit_HomeCurve->SetText(editStr);

	editStr.Format("%d", paras->homeEZA);
	m_pEdit_HomeEZA->SetText(editStr);

	editStr.Format("%d", paras->useDelay);
	m_pEdit_UseDelay->SetText(editStr);

	editStr.Format("%d", paras->msTimeout);
	m_pEdit_DelayTime->SetText(editStr);

	editStr.Format("%d", paras->useLimit);
	m_pEdit_UseLimit->SetText(editStr);

	editStr.Format("%f", paras->positiveLimit);
	m_pEdit_PositiveLimit->SetText(editStr);

	editStr.Format("%f", paras->negativeLimit);
	m_pEdit_NegativeLimit->SetText(editStr);

	if (m_is_new_axis && paras != NULL)
	{
		delete paras;
		paras = NULL;
	}
}
