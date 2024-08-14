#include "CPluginDlg.h"
#include <filesystem>
#include "CommonFunction/CSVReader.h"
#include "CardConfigDlg.h"
#include "PositionConfigDlg.h"
#include "IOConfigDlg.h"
#include "Macro.h"

#include "JupCore.h"
#include "../_INCLUDE/ProjectEvent.h"
using namespace ProjectEvent;

AdlinkController* g_pMotion = NULL;

std::string UTF8StrToGBKString(std::string_view str_UTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, str_UTF8.data(), -1, NULL, 0);
	wchar_t* wsz_GBK = new wchar_t[len + 1];
	memset(wsz_GBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, str_UTF8.data(), -1, wsz_GBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wsz_GBK, -1, NULL, 0, NULL, NULL);
	char* sz_GBK = new char[len + 1];
	memset(sz_GBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wsz_GBK, -1, sz_GBK, len, NULL, NULL);
	std::string str_temp(sz_GBK);
	if (wsz_GBK) delete[] wsz_GBK;
	if (sz_GBK) delete[] sz_GBK;
	return str_temp;
}

void CPluginDlg::InitWindow()
{
	jCore->RegisterEventWindow(g_MotionWidget, this);

	// 初始化MotionControl类
	if (!m_Adlink)
	{
		m_Adlink = new AdlinkController();
		m_pMotionParameter = m_Adlink->GetMotionParameter();
		g_pMotion = m_Adlink;
	}

	// 从m_PaintManager获得控件对象
	m_pBtn_CardConnect = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_CardConnect));
	m_pBtn_CardClose = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_CardClose));
	m_pList_AxisList = static_cast<CListUI*>(m_PaintManager.FindControl(List_AxisList));
	m_pLable_CurAxis = static_cast<CLabelUI*>(m_PaintManager.FindControl(Lable_CurrentAxis));
	m_pList_AxisPos = static_cast<CListUI*>(m_PaintManager.FindControl(List_AxisPos));
	m_pBtn_AxisPosParasSave = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisPosParasSave));
	m_pBtn_AxisPosAdd = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisPosAdd));
	m_pBtn_AxisPosDel = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisPosDel));
	m_pBtn_nRelativeMove = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisNRelativeMove));
	m_pEdit_RelativeMove = static_cast<CEditUI*>(m_PaintManager.FindControl(Edit_AxisRelativeMove));
	m_pBtn_PositiveMove = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisPositiveMove));
	m_pBtn_AbsMove = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisAbsMove));
	m_pLable_CurPos = static_cast<CLabelUI*>(m_PaintManager.FindControl(Lable_AxisCurrentPos));
	m_pBtn_AxisParasDlgOpen = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisParasDlgOpen));
	m_pBtn_AxisAdd = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisAdd));
	m_pBtn_AxisDel = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisDel));
	m_pBtn_AxisEnable = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisEnable));
	m_pBtn_AxisDisable = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisDisable));
	m_pBtn_AxisHome = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisHome));
	m_pBtn_AxisStop = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisStop));
	m_pBtn_VmoveNegative = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisVmoveNegative));
	m_pBtn_VmovePositive = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisVmovePositive));
	m_pBtn_AxisClearError = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_AxisClearError));
	m_pBtn_CardReset = static_cast<CButtonUI*>(m_PaintManager.FindControl(Btn_CardReset));
	m_pLable_CardAlarm = static_cast<CLabelUI*>(m_PaintManager.FindControl(Lable_CardAlarm));
	m_pLable_CardServo = static_cast<CLabelUI*>(m_PaintManager.FindControl(Lable_CardServo));
	m_pLable_CardPEL = static_cast<CLabelUI*>(m_PaintManager.FindControl(Lable_CardPEL));
	m_pLable_CardORG = static_cast<CLabelUI*>(m_PaintManager.FindControl(Lable_CardORG));
	m_pLable_CardNEL = static_cast<CLabelUI*>(m_PaintManager.FindControl(Lable_CardNEL));
	m_pLable_CardConnectStatus = static_cast<CLabelUI*>(m_PaintManager.FindControl(Lable_CardConnectStatus));

	m_pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabTest")));

	m_pList_IO_Input = static_cast<CListUI*>(m_PaintManager.FindControl(_T("list_IO_Input")));
	m_pList_IO_Output = static_cast<CListUI*>(m_PaintManager.FindControl(_T("list_IO_Output")));
	m_pBtn_InputConfig = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_IO_InputConfig")));
	m_pBtn_InputAdd = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_IO_InputAdd")));
	m_pBtn_InputDel = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_IO_InputDel")));
	m_pBtn_OutputConfig = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_IO_OutputConfig")));
	m_pBtn_OutputAdd = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_IO_OutputAdd")));
	m_pBtn_OutputDel = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_IO_OutputDel")));

	// 更新轴列表显示
	ListInitUpdate();
	// 更新IO显示
	InitInputIOListUI();
	InitOutputIOListUI();
	// 连接板卡
	TNotifyUI msg;
	OnBtnCardConnectClick(msg);
}

LRESULT CPluginDlg::CustomEvent(JupCustomEvent * event)
{
	JupCustomEvent::eType type = event->Type();
	if (type == ProjectEvent::e_JMotionEvent)
	{
		auto e = dynamic_cast<JMotionEvent*>(event);
		bool ret = AxisMoveAndWaitting(e->m_axis, e->m_distance, e->m_speed_ratio);
	}

	return 0;
}

CPluginDlg::~CPluginDlg()
{
	if (m_Adlink)
	{
		m_Adlink->CloseAdlinkCard();
	}
}

LRESULT CPluginDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_TIPS_SEND_STOP)
	{
		OnRecvStopMessage(wParam, lParam);
	}
	if (uMsg == WM_CLOSE)
	{
		PostQuitMessage(0);
	}
	if (uMsg == WM_TIMER)
	{
		OnTimer(wParam, lParam);
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CPluginDlg::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("selectchanged"))
	{
		CDuiString strName = msg.pSender->GetName();
		if (strName == _T("Motion"))
			m_pControl->SelectItem(0);
		else if (strName == _T("IO"))
			m_pControl->SelectItem(1);
		else if (strName == "lable_input_checkbox")
			OnCheckInputUseClick(msg);
	}
	if (msg.sType == _T("itemselect"))
	{
		OnItemSelect(msg);
	}
	if (msg.sType == _T("click"))
	{
		OnMotionCtrlClick(msg);
	}
}

void CPluginDlg::OnMotionCtrlClick(TNotifyUI &msg)
{
	auto senderStr = msg.pSender->GetName();

	if (senderStr == Btn_AxisPosMove)
		OnBtnAxisPosMoveClick(msg);
	else if (senderStr == Btn_CardConnect)
		OnBtnCardConnectClick(msg);
	else if (senderStr == Btn_CardClose)
		OnBtnCardCloseClick(msg);
	else if (senderStr == Btn_AxisPosParasSave)
		OnBtnAxisPosParasSetClick(msg);
	else if (senderStr == Btn_AxisPosAdd)
		OnBtnAxisPosAddClick(msg);
	else if (senderStr == Btn_AxisPosDel)
		OnBtnAxisPosDelClick(msg);
	else if (senderStr == Btn_AxisNRelativeMove)
		OnBtnAxisNegativeRelativeMoveClick(msg);
	else if (senderStr == Btn_AxisPositiveMove)
		OnBtnAxisPositiveRelativeMoveClick(msg);
	else if (senderStr == Btn_AxisAbsMove)
		OnBtnAxisAbsMoveClick(msg);
	else if (senderStr == Btn_AxisParasDlgOpen)
		OnBtnAxisParasDlgOpenClick(msg);
	else if (senderStr == Btn_AxisAdd)
		OnBtnAxisAddClick(msg);
	else if (senderStr == Btn_AxisDel)
		OnBtnAxisDelClick(msg);
	else if (senderStr == Btn_AxisEnable)
		OnBtnAxisEnableClick(msg);
	else if (senderStr == Btn_AxisDisable)
		OnBtnAxisDisableClick(msg);
	else if (senderStr == Btn_AxisHome)
		OnBtnAxisHomeClick(msg);
	else if (senderStr == Btn_AxisStop)
		OnBtnAxisStopClick(msg);
	else if (senderStr == Btn_AxisVmoveNegative)
		OnBtnAxisVmoveNegativeClick(msg);
	else if (senderStr == Btn_AxisVmovePositive)
		OnBtnAxisVmovePositiveClick(msg);
	else if (senderStr == Btn_AxisClearError)
		OnBtnAxisClearErrorClick(msg);
	else if (senderStr == Btn_CardReset)
		OnBtnCardResetClick(msg);
	else if (senderStr == Btn_SocketCoveOpen)
		OnBtnSocketCoverOpenClick(msg);
	else if (senderStr == Btn_SocketCoveClose)
		OnBtnSocketCoverCloseClick(msg);
	else if (senderStr == Btn_SocketCoveUp)
		OnBtnSocketCoverUpClick(msg);
	else if (senderStr == Btn_SocketCoveDown)
		OnBtnSocketCoverDownClick(msg);
	else if (senderStr == Btn_SocketCoveCloseDown)
		OnBtnSocketCoverCloseDownClick(msg);
	else if (senderStr == Btn_SocketCoveUpOpen)
		OnBtnSocketCoverUpOpenClick(msg);
	else if (senderStr == Btn_CylHoldDut)
		OnBtnCylHoldDutClick(msg);
	else if (senderStr == Btn_CylPutDut)
		OnBtnCylPutDutClick(msg);
	else if (senderStr == "btn_output_status")
		OnBtnOutputIOClick(msg);
	else if (senderStr == "btn_IO_InputConfig")
		OnBtnInputParasDlgOpenClick(msg);
	else if (senderStr == "btn_IO_InputAdd")
		OnBtnInputAddClick(msg);
	else if (senderStr == "btn_IO_InputDel")
		OnBtnInputDelClick(msg);
	else if (senderStr == "btn_IO_OutputConfig")
		OnBtnOutputParasDlgOpenClick(msg);
	else if (senderStr == "btn_IO_OutputAdd")
		OnBtnOutputAddClick(msg);
	else if (senderStr == "btn_IO_OutputDel")
		OnBtnOutputDelClick(msg);
}

void CPluginDlg::OnItemSelect(TNotifyUI & msg)
{
	if (msg.pSender == m_pList_AxisList)
	{
		PosListUpdate();
	}
}

void CPluginDlg::InitInputIOListUI()
{
	m_pList_IO_Input->RemoveAll();
	auto input_list = m_pMotionParameter->GetInputIOList();
	for (auto input : input_list)
	{
		CListContainerElementUI* pList = new CListContainerElementUI();
		pList->SetManager(&m_PaintManager, m_pList_IO_Input, true);
		pList->m_pHeader = m_pList_IO_Input->GetHeader();
		pList->SetPadding({ 1,1,1,2 });
		pList->SetFixedHeight(28);
		// Item1
		CLabelUI* lable_name = new CLabelUI();
		lable_name->SetText(input.second->cnName.c_str());
		lable_name->SetAttribute("name", "lable_input_name");
		lable_name->SetAttribute("align", "center");
		lable_name->SetFont(0);
		lable_name->SetBorderSize({ 1,0,1,0 });
		lable_name->SetBorderColor(0XFFE0EEE8);
		pList->AddAt(lable_name, 0);
		// Item2
		CLabelUI* lable_type = new CLabelUI();
		lable_type->SetText(input.second->cardType.c_str());
		lable_type->SetAttribute("name", "lable_input_card_type");
		lable_type->SetAttribute("align", "center");
		lable_type->SetFont(0);
		lable_type->SetBorderSize({ 1,0,1,0 });
		lable_type->SetBorderColor(0XFFE0EEE8);
		pList->AddAt(lable_type, 1);
		// Item3
		CLabelUI* lable_card_num = new CLabelUI();
		CDuiString item_str;
		item_str.Format(_T("%d"), input.second->cardNum);
		lable_card_num->SetText(item_str);
		lable_card_num->SetAttribute("name", "lable_input_card_num");
		lable_card_num->SetAttribute("align", "center");
		lable_card_num->SetFont(0);
		lable_card_num->SetBorderSize({ 1,0,1,0 });
		lable_card_num->SetBorderColor(0XFFE0EEE8);
		pList->AddAt(lable_card_num, 2);
		// Item4
		CLabelUI* lable_bit_num = new CLabelUI();
		item_str.Format(_T("%d"), input.second->bitNum);
		lable_bit_num->SetText(item_str);
		lable_bit_num->SetAttribute("name", "lable_input_bit_num");
		lable_bit_num->SetAttribute("align", "center");
		lable_bit_num->SetFont(0);
		lable_bit_num->SetBorderSize({ 1,0,1,0 });
		lable_bit_num->SetBorderColor(0XFFE0EEE8);
		pList->AddAt(lable_bit_num, 3);
		// Item5
		CCheckBoxUI* checkBox = new CCheckBoxUI();
		checkBox->SetName(_T("lable_input_checkbox"));
		checkBox->SetFont(0);
		checkBox->SetSelectedImage("file='checkbox_p.png' dest='28,8,44,24'");
		checkBox->SetNormalImage("file='checkbox.png' dest='28,8,44,24'");
		checkBox->SetHotImage("file='checkbox_h.png' dest='28,8,44,24'");
		checkBox->Selected(input.second->isUsed);
		checkBox->SetTag(m_pList_IO_Input->GetCount());
		checkBox->SetBorderSize({ 1,0,1,0 });
		checkBox->SetBorderColor(0XFFE0EEE8);
		pList->AddAt(checkBox, 4);
		// Item6
		CLabelUI* lable_level = new CLabelUI();
		lable_level->SetText(input.second->electrical_level.c_str());
		lable_level->SetAttribute("name", "lable_input_level");
		lable_level->SetAttribute("align", "center");
		lable_level->SetFont(0);
		lable_level->SetBorderSize({ 1,0,1,0 });
		lable_level->SetBorderColor(0XFFE0EEE8);
		pList->AddAt(lable_level, 5);
		// Item7
		CLabelUI* lable_group = new CLabelUI();
		lable_group->SetText(input.second->group.c_str());
		lable_group->SetAttribute("name", "lable_input_group");
		lable_group->SetAttribute("align", "center");
		lable_group->SetFont(0);
		pList->AddAt(lable_group, 6);
		// Item8
		CLabelUI* lable_status = new CLabelUI();
		lable_status->SetAttribute("name", "lable_input_status");
		lable_status->SetBkColor(STATE_COLOR_GRAY);
		pList->AddAt(lable_status, 7);

		m_pList_IO_Input->Add(pList);
	}
}

void CPluginDlg::InitOutputIOListUI()
{
	m_pList_IO_Output->RemoveAll();

	m_pList_IO_Output->SetSelectedItemTextColor(0xFF048AE0);

	auto output_list = m_pMotionParameter->GetOutputIOList();
	for (auto output : output_list)
	{
		CListContainerElementUI* pList = new CListContainerElementUI();
		pList->SetManager(&m_PaintManager, m_pList_IO_Output, true);
		pList->m_pHeader = m_pList_IO_Output->GetHeader();
		pList->SetPadding({ 1,1,1,2 });
		pList->SetFixedHeight(25);
		// Item1
		CLabelUI* lable_name = new CLabelUI();
		lable_name->SetText(output.second->cnName.c_str());
		lable_name->SetAttribute("name", "lable_output_name");
		lable_name->SetAttribute("align", "center");
		lable_name->SetFont(0);
		lable_name->SetBorderSize({ 1,0,1,0 });
		lable_name->SetBorderColor(0XFFE0EEE8);
		pList->AddAt(lable_name, 0);
		// Item2
		CLabelUI* lable_type = new CLabelUI();
		lable_type->SetText(output.second->cardType.c_str());
		lable_type->SetAttribute("name", "lable_output_card_type");
		lable_type->SetAttribute("align", "center");
		lable_type->SetFont(0);
		lable_type->SetBorderSize({ 1,0,1,0 });
		lable_type->SetBorderColor(0XFFE0EEE8);
		pList->AddAt(lable_type, 1);
		// Item3
		CLabelUI* lable_card_num = new CLabelUI();
		CDuiString item_str;
		item_str.Format(_T("%d"), output.second->cardNum);
		lable_card_num->SetText(item_str);
		lable_card_num->SetAttribute("name", "lable_output_card_num");
		lable_card_num->SetAttribute("align", "center");
		lable_card_num->SetFont(0);
		lable_card_num->SetBorderSize({ 1,0,1,0 });
		lable_card_num->SetBorderColor(0XFFE0EEE8);
		pList->AddAt(lable_card_num, 2);
		// Item4
		CLabelUI* lable_bit_num = new CLabelUI();
		item_str.Format(_T("%d"), output.second->bitNum);
		lable_bit_num->SetText(item_str);
		lable_bit_num->SetAttribute("name", "lable_output_bit_num");
		lable_bit_num->SetAttribute("align", "center");
		lable_bit_num->SetFont(0);
		lable_bit_num->SetBorderSize({ 1,0,1,0 });
		lable_bit_num->SetBorderColor(0XFFE0EEE8);
		pList->AddAt(lable_bit_num, 3);
		// Item5
		CLabelUI* lable_level = new CLabelUI();
		lable_level->SetText(output.second->electrical_level.c_str());
		lable_level->SetAttribute("name", "lable_output_level");
		lable_level->SetAttribute("align", "center");
		lable_level->SetFont(0);
		lable_level->SetBorderSize({ 1,0,1,0 });
		lable_level->SetBorderColor(0XFFE0EEE8);
		pList->AddAt(lable_level, 4);
		// Item6
		CLabelUI* lable_group = new CLabelUI();
		lable_group->SetText(output.second->group.c_str());
		lable_group->SetAttribute("name", "lable_output_group");
		lable_group->SetAttribute("align", "center");
		lable_group->SetFont(0);
		pList->AddAt(lable_group, 5);
		// Item7
		CButtonUI* btn_status = new CButtonUI();
		btn_status->SetAttribute("name", "btn_output_status");
		btn_status->SetTag(m_pList_IO_Output->GetCount());
		btn_status->SetBkImage("file='switch.png' source='40,50,480,240'");
		//btn_status->SetBkImage("file='switch.png' source='40,280,480,460'");
		pList->AddAt(btn_status, 6);

		m_pList_IO_Output->Add(pList);
	}
}

void CPluginDlg::ListInitUpdate()
{
	auto axisList = m_pMotionParameter->GetAxisNameList();
	// 轴列表
	for (int i = 0; i < axisList.size(); i++)
	{
		std::string axisName = axisList[i];
		auto paras = m_pMotionParameter->GetAxisParam(axisName);

		CListTextElementUI *pListElement = new CListTextElementUI;
		m_pList_AxisList->Add(pListElement);
		// Item1
		CDuiString itemStr;
		itemStr.Format(_T("%d-%d"), paras->cardNum, paras->axisNum);
		pListElement->SetText(0, itemStr);
		// Item2
		pListElement->SetText(1, axisName.c_str());
		// Item3
		pListElement->SetText(2, paras->cardType.c_str());
		// Item4
		pListElement->SetText(3, paras->motorType.c_str());
	}
	// 默认选中第一行
	m_pList_AxisList->SelectItem(0);
}

void CPluginDlg::PosListUpdate()
{
	int nIndex = m_pList_AxisList->GetCurSel();   //获取选中行的索引
	CListTextElementUI *pLine = static_cast<CListTextElementUI*>(m_pList_AxisList->GetItemAt(nIndex));
	std::string axisName = pLine->GetText(AxisListItem::AxisName);
	// 更新位置列表
	m_pList_AxisPos->RemoveAll();
	auto posInfos = m_pMotionParameter->GetAxisPosListInfo(axisName);
	for (size_t i = 0; i < posInfos.size(); i++)
	{
		CListContainerElementUI* pList = new CListContainerElementUI();
		pList->SetManager(&m_PaintManager, m_pList_AxisPos, true);
		pList->m_pHeader = m_pList_AxisPos->GetHeader();
		pList->SetPadding({ 1,0,1,10 });
		// Item1
		CDuiString itemIndex;
		itemIndex.Format(_T("%d"), i);
		CLabelUI* lable_Index = new CLabelUI();
		lable_Index->SetText(itemIndex);
		lable_Index->SetFont(0);//0关联xml文件字体资源
		lable_Index->SetAttribute("align", "center");
		pList->AddAt(lable_Index, AxisPosItem::nId);
		// Item2
		CLabelUI* lable_PosName = new CLabelUI();
		lable_PosName->SetText(posInfos[i]->posName.c_str());
		lable_PosName->SetAttribute("name", "lable_PosName");
		lable_PosName->SetAttribute("align", "center");
		lable_PosName->SetFont(0);
		pList->AddAt(lable_PosName, AxisPosItem::AxisPosName);
		// Item3
		double axisPos = posInfos[i]->distance;
		CDuiString itemPos;
		itemPos.Format(_T("%.2f"), axisPos);
		CLabelUI* lable_Pos = new CLabelUI();
		lable_Pos->SetText(itemPos);
		lable_Pos->SetAttribute("name", "lable_PosValue");
		lable_Pos->SetAttribute("align", "center");
		lable_Pos->SetFont(0);
		pList->AddAt(lable_Pos, AxisPosItem::AxisPos);
		// Item4
		double axisPosStep = posInfos[i]->spacing;
		CDuiString itemPosStep;
		itemPosStep.Format(_T("%.2f"), axisPosStep);
		CLabelUI* lable_PosStep = new CLabelUI();
		lable_PosStep->SetText(itemPosStep);
		lable_PosStep->SetTextPadding({ 4,0,4,0 });
		lable_PosStep->SetAttribute("bkcolor", "#00FFFFFF");
		lable_PosStep->SetAttribute("name", "lable_PosStep");
		lable_PosStep->SetTag(m_pList_AxisPos->GetCount());
		lable_PosStep->SetFont(0);
		pList->AddAt(lable_PosStep, AxisPosItem::AxisPosStep);
		// Item5
		CButtonUI* btn_PosMove = new CButtonUI();
		btn_PosMove->SetText(_T("Move"));
		btn_PosMove->SetTextPadding({ 4,0,4,0 });
		//btn_PosMove->SetAttribute("bkcolor", "#0xff808000");
		btn_PosMove->SetAttribute("normalimage", "file='button_normal.png' corner='20,2,20,2'");
		btn_PosMove->SetAttribute("hotimage", "file='button_hover.png' corner='20,2,20,2'");
		btn_PosMove->SetAttribute("pushedimage", "file='button_pushed.png' corner='20,2,20,2'");
		btn_PosMove->SetAttribute("name", "btn_AxisPosMove");
		btn_PosMove->SetTag(m_pList_AxisPos->GetCount());
		btn_PosMove->SetEnabled(false);
		btn_PosMove->SetFont(0);
		pList->AddAt(btn_PosMove, AxisPosItem::AxisPosMove);
		// Item6
		CEditUI* edit_PosDebug = new CEditUI();
		edit_PosDebug->SetText(itemPos);
		edit_PosDebug->SetTextPadding({ 4,0,4,0 });
		edit_PosDebug->SetAttribute("bkcolor", "#00FFFFFF");
		edit_PosDebug->SetAttribute("name", "edit_PosValueDebug");
		edit_PosDebug->SetTag(m_pList_AxisPos->GetCount());
		edit_PosDebug->SetFont(0);
		pList->AddAt(edit_PosDebug, AxisPosItem::AxisPosDebug);
		pList->SetFixedHeight(25);
		m_pList_AxisPos->Add(pList);
	}
	// 更新当前轴显示
	m_pLable_CurAxis->SetText(axisName.c_str());
	if (m_Adlink->IsCardInit())
	{
		int nCount = m_pList_AxisPos->GetCount();
		for (size_t i = 0; i < nCount; i++)
		{
			CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_AxisPos->GetItemAt(i));
			CButtonUI* button = static_cast<CButtonUI*>(pLine->GetItemAt(AxisPosItem::AxisPosMove));
			button->SetEnabled(true);
		}
	}
}

void CPluginDlg::ButtonEnable(bool is_enable)
{
	m_pBtn_CardConnect->SetEnabled(!is_enable);
	m_pBtn_CardClose->SetEnabled(is_enable);
	m_pBtn_AxisPosParasSave->SetEnabled(is_enable);
	m_pBtn_AxisPosAdd->SetEnabled(is_enable);
	m_pBtn_AxisPosDel->SetEnabled(is_enable);
	m_pBtn_nRelativeMove->SetEnabled(is_enable);
	m_pBtn_PositiveMove->SetEnabled(is_enable);
	m_pBtn_AbsMove->SetEnabled(is_enable);
	m_pBtn_AxisParasDlgOpen->SetEnabled(is_enable);
	m_pBtn_AxisAdd->SetEnabled(is_enable);
	m_pBtn_AxisDel->SetEnabled(is_enable);
	m_pBtn_AxisEnable->SetEnabled(is_enable);
	m_pBtn_AxisDisable->SetEnabled(is_enable);
	m_pBtn_AxisHome->SetEnabled(is_enable);
	m_pBtn_AxisStop->SetEnabled(is_enable);
	m_pBtn_VmoveNegative->SetEnabled(is_enable);
	m_pBtn_VmovePositive->SetEnabled(is_enable);
	m_pBtn_AxisClearError->SetEnabled(is_enable);
	m_pBtn_CardReset->SetEnabled(is_enable);
	m_pBtn_InputConfig->SetEnabled(is_enable);
	m_pBtn_InputAdd->SetEnabled(is_enable);
	m_pBtn_InputDel->SetEnabled(is_enable);
	m_pBtn_OutputConfig->SetEnabled(is_enable);
	m_pBtn_OutputAdd->SetEnabled(is_enable);
	m_pBtn_OutputDel->SetEnabled(is_enable);

	// 位置列表移动按钮
	int nCount = m_pList_AxisPos->GetCount();
	for (size_t i = 0; i < nCount; i++)
	{
		CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_AxisPos->GetItemAt(i));
		CButtonUI* button = static_cast<CButtonUI*>(pLine->GetItemAt(AxisPosItem::AxisPosMove));
		button->SetEnabled(is_enable);
	}
}

bool CPluginDlg::AxisMoveAndWaitting(std::string axis_name, double distance, double speed_ratio)
{
	int nRet = m_Adlink->AxisAbsMove(axis_name, distance, 0.0, speed_ratio);
	if (nRet != 0)
	{
		return false;
	}
	m_Adlink->WaitAxisAbsMove(axis_name, distance);
	return true;
}

void CPluginDlg::OnBtnCardConnectClick(TNotifyUI & msg)
{
	//ButtonEnable(true);
	//return;
	CDuiString log;
	int nRet = m_Adlink->InitAdlinkCard();
	if (0 != nRet)
	{
		log.Format(_T("Init Card Failed = %d"), nRet);
		MessageBox(this->GetHWND(), log, _T("Error"), MB_OK);
		return;
	}

	ButtonEnable(true);
	SetTimer(this->GetHWND(), TIMER_CARD_STATUS, 1000, NULL);
	SetTimer(this->GetHWND(), TIMER_AXISPOS, 300, NULL);

	std::string str = UTF8StrToGBKString(std::string_view(_T("已连接")));
	m_pLable_CardConnectStatus->SetText(str.c_str());
	m_pLable_CardConnectStatus->SetBkColor(STATE_COLOR_GREEN);
	//MessageBox(this->GetHWND(), _T("Init Card Success!"), _T("Success"), MB_OK);
}

void CPluginDlg::OnBtnCardCloseClick(TNotifyUI & msg)
{
	int nRet1 = m_Adlink->CloseAdlinkCard();
	CDuiString log;
	if (!nRet1)
	{
		m_pBtn_CardConnect->SetEnabled(true);
		m_pBtn_CardClose->SetEnabled(false);
		MessageBox(this->GetHWND(), _T("Close All Card Success!"), _T("Success"), MB_OK);
	}
	else
	{
		log.Format(_T("Close Card Failed,error=%d"), nRet1);
		MessageBox(this->GetHWND(), log, _T("Error"), MB_OK);
	}
	ButtonEnable(false);

	KillTimer(this->GetHWND(), TIMER_CARD_STATUS);
	KillTimer(this->GetHWND(), TIMER_AXISPOS);
	std::string str = UTF8StrToGBKString(std::string_view(_T("未连接")));
	m_pLable_CardConnectStatus->SetText(str.c_str());
	m_pLable_CardConnectStatus->SetBkColor(STATE_COLOR_GRAY1);
	m_pLable_CardAlarm->SetBkColor(STATE_COLOR_GRAY1);
	m_pLable_CardServo->SetBkColor(STATE_COLOR_GRAY1);
	m_pLable_CardPEL->SetBkColor(STATE_COLOR_GRAY1);
	m_pLable_CardORG->SetBkColor(STATE_COLOR_GRAY1);
	m_pLable_CardNEL->SetBkColor(STATE_COLOR_GRAY1);
}

void CPluginDlg::OnBtnAxisPosParasSetClick(TNotifyUI & msg)
{
	int nIndex = m_pList_AxisPos->GetCurSel();
	if (nIndex < 0)
		return;
	std::string axisName = m_pLable_CurAxis->GetText().GetData();
	CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_AxisPos->GetItemAt(nIndex));
	std::string posName = pLine->GetItemAt(AxisPosItem::AxisPosName)->GetText().GetData();

	PositionConfigDlg dlg(this, m_pMotionParameter, axisName, posName);
	dlg.CenterWindow();
	dlg.ShowModal();

	// 更新轴列表显示
	PosListUpdate();
}

void CPluginDlg::OnBtnAxisPosAddClick(TNotifyUI & msg)
{
	std::string axisName = m_pLable_CurAxis->GetText().GetData();
	PositionConfigDlg dlg(this, m_pMotionParameter, axisName, "", true);
	dlg.CenterWindow();
	dlg.ShowModal();

	// 更新轴列表显示
	PosListUpdate();
}

void CPluginDlg::OnBtnAxisPosDelClick(TNotifyUI & msg)
{
	int nIndex = m_pList_AxisPos->GetCurSel();
	if (nIndex < 0)
		return;
	std::string axisName = m_pLable_CurAxis->GetText().GetData();
	CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_AxisPos->GetItemAt(nIndex));
	std::string posName = pLine->GetItemAt(AxisPosItem::AxisPosName)->GetText().GetData();
	CDuiString msgStr;
	msgStr.Format(_T("Are you sure to delete the position: %s"), posName);
	int nRet = MessageBox(this->GetHWND(), LPCTSTR(msgStr), _T("Prompt"), MB_YESNO);
	if (nRet == IDNO)
		return;
	// 删除轴配置
	m_pMotionParameter->DeletePosInfos(posName);
	// 更新轴列表显示
	PosListUpdate();
}

void CPluginDlg::OnBtnAxisNegativeRelativeMoveClick(TNotifyUI & msg)
{
	//if (!m_pMotion->isCardInit())
	//{
	//	MessageBox(this->GetHWND(), _T("Please Init Card First!"), _T("Error"), MB_OK);
	//	return;
	//}

	std::string axisName = m_pLable_CurAxis->GetText().GetData();
	std::string axisPos = m_pEdit_RelativeMove->GetText().GetData();
	double distance = atof(axisPos.c_str());

	CDuiString log;
	int nRet = m_Adlink->AxisMoveDistance(axisName, -distance);
	if (nRet != 0)
	{
		log.Format(_T("Move error = %d"), nRet);
		MessageBox(this->GetHWND(), log, _T("Error"), MB_OK);
		return;
	}

	int nAxisIndex = m_pMotionParameter->GetAxisParam(axisName)->axisNum;
	log.Format(_T("Wait [%s] moving..."), axisName);
	MyTipsDialog dlg(this, log, nAxisIndex);

	std::thread myThread([&] {
		m_Adlink->WaitAxisMoveDistance(axisName, -distance);
		::PostMessage(dlg.GetHWND(), WM_TIPS_RECV_MOVEDONE, 0, 0);
	});
	myThread.detach();

	dlg.CenterWindow();
	dlg.ShowModal();
}

void CPluginDlg::OnBtnAxisPositiveRelativeMoveClick(TNotifyUI & msg)
{
	//if (!m_pMotion->isCardInit())
	//{
	//	MessageBox(this->GetHWND(), _T("Please Init Card First!"), _T("Error"), MB_OK);
	//	return;
	//}

	std::string axisName = m_pLable_CurAxis->GetText().GetData();
	std::string axisPos = m_pEdit_RelativeMove->GetText().GetData();
	double distance = atof(axisPos.c_str());

	CDuiString log;
	int nRet = m_Adlink->AxisMoveDistance(axisName, distance);
	if (nRet != 0)
	{
		log.Format(_T("Move error = %d"), nRet);
		MessageBox(this->GetHWND(), log, _T("Error"), MB_OK);
		return;
	}

	int nAxisIndex = m_pMotionParameter->GetAxisParam(axisName)->axisNum;
	log.Format(_T("Wait [%s] moving..."), axisName);
	MyTipsDialog dlg(this, log, nAxisIndex);

	std::thread myThread([&] {
		m_Adlink->WaitAxisMoveDistance(axisName, distance);
		::PostMessage(dlg.GetHWND(), WM_TIPS_RECV_MOVEDONE, 0, 0);
	});
	myThread.detach();

	dlg.CenterWindow();
	dlg.ShowModal();
}

void CPluginDlg::OnBtnAxisAbsMoveClick(TNotifyUI & msg)
{
	//if (!m_pMotion->isCardInit())
	//{
	//	MessageBox(this->GetHWND(), _T("Please Init Card First!"), _T("Error"), MB_OK);
	//	return;
	//}
	CDuiString log;

	std::string axisName = m_pLable_CurAxis->GetText().GetData();
	std::string axisPos = m_pEdit_RelativeMove->GetText().GetData();

	int nRet = m_Adlink->AxisAbsMove(axisName, atof(axisPos.c_str()));
	if (nRet != 0)
	{
		log.Format(_T("Move error = %d"), nRet);
		MessageBox(this->GetHWND(), log, _T("Error"), MB_OK);
		return;
	}

	int nAxisIndex = m_pMotionParameter->GetAxisParam(axisName)->axisNum;
	log.Format(_T("Wait [%s] moving..."), axisName);
	MyTipsDialog dlg(this, log, nAxisIndex);

	std::thread myThread([&] {
		m_Adlink->WaitAxisAbsMove(axisName, atof(axisPos.c_str()));
		::PostMessage(dlg.GetHWND(), WM_TIPS_RECV_MOVEDONE, 0, 0);
	});
	myThread.detach();

	dlg.CenterWindow();
	dlg.ShowModal();
}

void CPluginDlg::OnBtnAxisParasDlgOpenClick(TNotifyUI & msg)
{
	std::string axisName = m_pLable_CurAxis->GetText().GetData();
	CardConfigDlg dlg(this, m_pMotionParameter, axisName);
	dlg.CenterWindow();
	dlg.ShowModal();
	// 更新轴列表显示
	m_pList_AxisList->RemoveAll();
	ListInitUpdate();
}

void CPluginDlg::OnBtnAxisAddClick(TNotifyUI & msg)
{
	std::string axisName = "";
	CardConfigDlg dlg(this, m_pMotionParameter, axisName, true);
	dlg.CenterWindow();
	dlg.ShowModal();
	// 更新轴列表显示
	m_pList_AxisList->RemoveAll();
	ListInitUpdate();
}

void CPluginDlg::OnBtnAxisDelClick(TNotifyUI & msg)
{
	std::string strAxis = m_pLable_CurAxis->GetText().GetData();
	CDuiString msgStr;
	msgStr.Format(_T("Are you sure to delete the axis: %s"), strAxis);
	int nRet = MessageBox(this->GetHWND(), LPCTSTR(msgStr), _T("Prompt"), MB_YESNO);
	if (nRet == IDNO)
		return;
	// 删除轴配置
	m_pMotionParameter->DeleteAxisInfos(strAxis);
	// 更新轴列表显示
	m_pList_AxisList->RemoveAll();
	ListInitUpdate();
}

void CPluginDlg::OnBtnAxisEnableClick(TNotifyUI & msg)
{
	std::string strAxis = m_pLable_CurAxis->GetText().GetData();
	if (m_Adlink->AxisServoOn(strAxis) != 0)
	{
		MessageBox(this->GetHWND(), _T("Servo on failed"), _T("Error"), MB_OK);
	}
}

void CPluginDlg::OnBtnAxisDisableClick(TNotifyUI & msg)
{
	std::string strAxis = m_pLable_CurAxis->GetText().GetData();
	if (m_Adlink->AxisServoOff(strAxis) != 0)
	{
		MessageBox(this->GetHWND(), _T("Servo off failed"), _T("Error"), MB_OK);
	}
}

void CPluginDlg::OnBtnAxisHomeClick(TNotifyUI & msg)
{
	//return;
	//if (!m_pMotion->isCardInit())
	//{
	//	MessageBox(this->GetHWND(), _T("Please Init Card First!"), _T("Error"), MB_OK);
	//	return;
	//}
	CDuiString log;
	std::string strAxis = m_pLable_CurAxis->GetText().GetData();

	int nRet = m_Adlink->AxisHome(strAxis);
	if (nRet != 0)
	{
		log.Format(_T("Home error = %d"), nRet);
		MessageBox(this->GetHWND(), log, _T("Error"), MB_OK);
		return;
	}

	int nAxisIndex = m_pMotionParameter->GetAxisParam(strAxis)->axisNum;
	log.Format(_T("Wait [%s] homing..."), strAxis);
	MyTipsDialog dlg(this, log, nAxisIndex);

	std::thread myThread([&] {
		std::string axisName = strAxis;
		m_Adlink->WaitAxisHome(axisName);
		::PostMessage(dlg.GetHWND(), WM_TIPS_RECV_MOVEDONE, 0, 0);
	});
	myThread.detach();

	dlg.CenterWindow();
	dlg.ShowModal();
}

void CPluginDlg::OnBtnAxisStopClick(TNotifyUI & msg)
{
	std::string axisName = m_pLable_CurAxis->GetText().GetData();
	m_Adlink->AxisStopWait();
	m_Adlink->StopAxisMove(axisName);
}

void CPluginDlg::OnBtnAxisVmoveNegativeClick(TNotifyUI & msg)
{
}

void CPluginDlg::OnBtnAxisVmovePositiveClick(TNotifyUI & msg)
{
}

void CPluginDlg::OnBtnAxisClearErrorClick(TNotifyUI & msg)
{
}

void CPluginDlg::OnBtnCardResetClick(TNotifyUI & msg)
{
}

void CPluginDlg::OnBtnAxisPosMoveClick(TNotifyUI & msg)
{
	//if (!m_pMotion->isCardInit())
	//{
	//	MessageBox(this->GetHWND(), _T("Please Init Card First!"), _T("Error"), MB_OK);
	//	return;
	//}
	CDuiString log;

	int nIndex = msg.pSender->GetTag();
	CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_AxisPos->GetItemAt(nIndex));
	std::string axisPos = pLine->GetItemAt(AxisPosItem::AxisPosDebug)->GetText().GetData();
	std::string axisName = m_pLable_CurAxis->GetText().GetData();

	int nRet = m_Adlink->AxisAbsMove(axisName, atof(axisPos.c_str()));
	if (nRet != 0)
	{
		log.Format(_T("Move error = %d"), nRet);
		MessageBox(this->GetHWND(), log, _T("Error"), MB_OK);
		return;
	}

	int nAxisIndex = m_pMotionParameter->GetAxisParam(axisName)->axisNum;
	log.Format(_T("Wait [%s] moving..."), axisName);
	MyTipsDialog dlg(this, log, nAxisIndex);

	std::thread myThread([&] {
		m_Adlink->WaitAxisAbsMove(axisName, atof(axisPos.c_str()));
		::PostMessage(dlg.GetHWND(), WM_TIPS_RECV_MOVEDONE, 0, 0);
	});
	myThread.detach();

	dlg.CenterWindow();
	dlg.ShowModal();
}

void CPluginDlg::OnBtnInputParasDlgOpenClick(TNotifyUI & msg)
{
	int nIndex = m_pList_IO_Input->GetCurSel();
	if (nIndex < 0)
		return;
	CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_IO_Input->GetItemAt(nIndex));
	std::string io_name = pLine->GetItemAt(0)->GetText().GetData();
	MotionIO* io_info = m_pMotionParameter->GetInputIOInfo(io_name, false);
	if (io_info)
	{
		IOConfigDlg dlg(this, m_pMotionParameter, io_info, true);
		dlg.CenterWindow();
		dlg.ShowModal();
		// 更新轴列表显示
		m_pList_IO_Input->RemoveAll();
		InitInputIOListUI();
	}
}

void CPluginDlg::OnBtnInputAddClick(TNotifyUI & msg)
{
	MotionIO* io_info = new MotionIO();
	IOConfigDlg dlg(this, m_pMotionParameter, io_info, true, true);
	dlg.CenterWindow();
	dlg.ShowModal();
	// 更新轴列表显示
	m_pList_IO_Input->RemoveAll();
	InitInputIOListUI();
}

void CPluginDlg::OnBtnInputDelClick(TNotifyUI & msg)
{
	int nIndex = m_pList_IO_Input->GetCurSel();
	if (nIndex < 0)
		return;
	CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_IO_Input->GetItemAt(nIndex));
	std::string io_name = pLine->GetItemAt(0)->GetText().GetData();
	CDuiString msgStr;
	msgStr.Format(_T("Are you sure to delete the io: %s"), io_name);
	int nRet = MessageBox(this->GetHWND(), LPCTSTR(msgStr), _T("Prompt"), MB_YESNO);
	if (nRet == IDNO)
		return;
	// 删除轴配置
	MotionIO* io_info = m_pMotionParameter->GetInputIOInfo(io_name, false);
	if (io_info)
	{
		m_pMotionParameter->DeleteIOInfos(io_info->name, true);
		// 更新轴列表显示
		m_pList_IO_Input->RemoveAll();
		InitInputIOListUI();
	}
}

void CPluginDlg::OnCheckInputUseClick(TNotifyUI & msg)
{
	int nIndex = msg.pSender->GetTag();
	CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_IO_Input->GetItemAt(nIndex));
	std::string io_name = pLine->GetItemAt(0)->GetText().GetData();
	MotionIO* io_info = m_pMotionParameter->GetInputIOInfo(io_name, false);
	CCheckBoxUI* checkBox = static_cast<CCheckBoxUI*>(pLine->GetItemAt(4));
	if (checkBox->IsSelected())
		m_pMotionParameter->UpdataInputIOUseStatus(io_info->name, true);
	else
		m_pMotionParameter->UpdataInputIOUseStatus(io_info->name, false);
}

void CPluginDlg::OnBtnOutputParasDlgOpenClick(TNotifyUI & msg)
{
	int nIndex = m_pList_IO_Output->GetCurSel();
	if (nIndex < 0)
		return;
	CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_IO_Output->GetItemAt(nIndex));
	std::string io_name = pLine->GetItemAt(0)->GetText().GetData();
	MotionIO* io_info = m_pMotionParameter->GetOutputIOInfo(io_name, false);
	if (io_info)
	{
		IOConfigDlg dlg(this, m_pMotionParameter, io_info, false);
		dlg.CenterWindow();
		dlg.ShowModal();
		// 更新轴列表显示
		m_pList_IO_Output->RemoveAll();
		InitOutputIOListUI();
	}
}

void CPluginDlg::OnBtnOutputAddClick(TNotifyUI & msg)
{
	MotionIO* io_info = new MotionIO();
	IOConfigDlg dlg(this, m_pMotionParameter, io_info, false, true);
	dlg.CenterWindow();
	dlg.ShowModal();
	// 更新轴列表显示
	m_pList_IO_Output->RemoveAll();
	InitOutputIOListUI();
}

void CPluginDlg::OnBtnOutputDelClick(TNotifyUI & msg)
{
	int nIndex = m_pList_IO_Output->GetCurSel();
	if (nIndex < 0)
		return;
	CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_IO_Output->GetItemAt(nIndex));
	std::string io_name = pLine->GetItemAt(0)->GetText().GetData();
	CDuiString msgStr;
	msgStr.Format(_T("Are you sure to delete the io: %s"), io_name);
	int nRet = MessageBox(this->GetHWND(), LPCTSTR(msgStr), _T("Prompt"), MB_YESNO);
	if (nRet == IDNO)
		return;
	// 删除轴配置
	MotionIO* io_info = m_pMotionParameter->GetOutputIOInfo(io_name, false);
	if (io_info)
	{
		m_pMotionParameter->DeleteIOInfos(io_info->name, false);
		// 更新轴列表显示
		m_pList_IO_Output->RemoveAll();
		InitOutputIOListUI();
	}
}

void CPluginDlg::OnBtnOutputIOClick(TNotifyUI & msg)
{
	int nIndex = msg.pSender->GetTag();
	CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_IO_Output->GetItemAt(nIndex));
	std::string io_name = pLine->GetItemAt(0)->GetText().GetData();
	MotionIO* io_info = m_pMotionParameter->GetOutputIOInfo(io_name, false);
	if (io_info)
	{
		int old_status = m_Adlink->IO_GetOutput(io_info->cardNum, IO_ModNo::No1, io_info->bitNum);
		int ret = -1;
		if (old_status == 0)
			ret = m_Adlink->IO_SetOutput(io_info->cardNum, IO_ModNo::No1, io_info->bitNum, IO_Status::ON);
		else
			ret = m_Adlink->IO_SetOutput(io_info->cardNum, IO_ModNo::No1, io_info->bitNum, IO_Status::OFF);
		if (ret == 0)
		{
			if (old_status == 0)
				pLine->GetItemAt(6)->SetBkImage("file='switch.png' source='40,280,480,460'");
			else
				pLine->GetItemAt(6)->SetBkImage("file='switch.png' source='40,50,480,240'");
		}
		else
		{
			CDuiString strMsg;
			strMsg.Format(_T("Set io: %s error = %d"), io_name, ret);
			MessageBox(this->GetHWND(), strMsg, _T("Error"), MB_OK);
		}
	}
}

void CPluginDlg::OnBtnSocketCoverOpenClick(TNotifyUI & msg)
{
	//m_Adlink->IO_SetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverOut, IO_Status::OFF);
	//m_Adlink->IO_SetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverIn, IO_Status::ON);

	//std::thread myThread([&] {
	//	while (true)
	//	{
	//		Sleep(50);
	//		bool ret1 = m_Adlink->IO_GetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverOut);
	//		bool ret2 = m_Adlink->IO_GetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverIn);
	//		if (!ret1 && ret2)
	//		{
	//			break;
	//		}
	//	}
	//});
	//myThread.join();
}

void CPluginDlg::OnBtnSocketCoverCloseClick(TNotifyUI & msg)
{
	//m_Adlink->IO_SetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverOut, IO_Status::ON);
	//m_Adlink->IO_SetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverIn, IO_Status::OFF);

	//std::thread myThread([&] {
	//	while (true)
	//	{
	//		Sleep(50);
	//		bool ret1 = m_Adlink->IO_GetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverOut);
	//		bool ret2 = m_Adlink->IO_GetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverIn);
	//		if (ret1 && !ret2)
	//		{
	//			break;
	//		}
	//	}
	//});
	//myThread.join();
}

void CPluginDlg::OnBtnSocketCoverUpClick(TNotifyUI & msg)
{
	//m_Adlink->IO_SetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverUp, IO_Status::OFF);
	//m_Adlink->IO_SetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverDown, IO_Status::ON);

	//std::thread myThread([&] {
	//	while (true)
	//	{
	//		Sleep(50);
	//		bool ret1 = m_Adlink->IO_GetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverUp);
	//		bool ret2 = m_Adlink->IO_GetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverDown);
	//		if (!ret1 && ret2)
	//		{
	//			break;
	//		}
	//	}
	//});
	//myThread.join();
}

void CPluginDlg::OnBtnSocketCoverDownClick(TNotifyUI & msg)
{
	//m_Adlink->IO_SetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverUp, IO_Status::ON);
	//m_Adlink->IO_SetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverDown, IO_Status::OFF);

	//std::thread myThread([&] {
	//	while (true)
	//	{
	//		Sleep(50);
	//		bool ret1 = m_Adlink->IO_GetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverUp);
	//		bool ret2 = m_Adlink->IO_GetOutput(IO_ModNo::No1, IO_Out_Channel::SocketCoverDown);
	//		if (ret1 && !ret2)
	//		{
	//			break;
	//		}
	//	}
	//});
	//myThread.join();
}

void CPluginDlg::OnBtnSocketCoverCloseDownClick(TNotifyUI & msg)
{
	OnBtnSocketCoverCloseClick(msg);
	Sleep(500);
	OnBtnSocketCoverDownClick(msg);
}

void CPluginDlg::OnBtnSocketCoverUpOpenClick(TNotifyUI & msg)
{
	OnBtnSocketCoverUpClick(msg);
	Sleep(500);
	OnBtnSocketCoverOpenClick(msg);
}

void CPluginDlg::OnBtnCylHoldDutClick(TNotifyUI & msg)
{
}

void CPluginDlg::OnBtnCylPutDutClick(TNotifyUI & msg)
{
}

void CPluginDlg::OnRecvStopMessage(WPARAM wParam, LPARAM lParam)
{
	//m_pMotion->StopWait();
	//m_pMotion->StopAllAxis();
}

void CPluginDlg::OnTimer(WPARAM wParam, LPARAM lParam)
{
	if (wParam == TIMER_IO)
	{
		// input io
		int input_count = m_pList_IO_Input->GetCount();
		for (size_t i = 0; i < input_count; i++)
		{
			CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_IO_Input->GetItemAt(i));
			CLabelUI* lable_status = static_cast<CLabelUI*>(pLine->GetItemAt(7));
			std::string io_name = pLine->GetItemAt(0)->GetText().GetData();
			MotionIO* io_info = m_pMotionParameter->GetInputIOInfo(io_name, false);
			int io_status = m_Adlink->IO_GetInput(io_info->cardNum, IO_ModNo::No1, io_info->bitNum);
			if (io_status == 0)
				lable_status->SetBkColor(STATE_COLOR_GREEN);
			else
				lable_status->SetBkColor(STATE_COLOR_GRAY);
		}
		// output io
		int output_count = m_pList_IO_Output->GetCount();
		for (size_t i = 0; i < input_count; i++)
		{
			CListContainerElementUI *pLine = static_cast<CListContainerElementUI*>(m_pList_IO_Output->GetItemAt(i));
			CButtonUI* btn_status = static_cast<CButtonUI*>(pLine->GetItemAt(6));
			std::string io_name = pLine->GetItemAt(0)->GetText().GetData();
			MotionIO* io_info = m_pMotionParameter->GetOutputIOInfo(io_name, false);
			int io_status = m_Adlink->IO_GetOutput(io_info->cardNum, IO_ModNo::No1, io_info->bitNum);
			if (io_status == 0)
				btn_status->SetBkImage("file='switch.png' source='40,280,480,460'");
			else
				btn_status->SetBkImage("file='switch.png' source='40,50,480,240'");
		}
	}
	if (wParam == TIMER_AXISPOS)
	{
		std::string strAxis = m_pLable_CurAxis->GetText().GetData();
		double currentPos_mm = m_Adlink->GetCurrentPos(strAxis);
		CDuiString editString;
		editString.Format(_T("%.4f"), currentPos_mm);
		m_pLable_CurPos->SetText(editString);
	}
	if (TIMER_CARD_STATUS == wParam)
	{
		std::string strAxis = m_pLable_CurAxis->GetText().GetData();
		m_Adlink->IsAlarm(strAxis) ? m_pLable_CardAlarm->SetBkColor(STATE_COLOR_RED) : m_pLable_CardAlarm->SetBkColor(STATE_COLOR_GRAY1);
		m_Adlink->IsSvon(strAxis) ? m_pLable_CardServo->SetBkColor(STATE_COLOR_RED) : m_pLable_CardServo->SetBkColor(STATE_COLOR_GRAY1);
		m_Adlink->IsPEL(strAxis) ? m_pLable_CardPEL->SetBkColor(STATE_COLOR_RED) : m_pLable_CardPEL->SetBkColor(STATE_COLOR_GRAY1);
		m_Adlink->IsORG(strAxis) ? m_pLable_CardORG->SetBkColor(STATE_COLOR_RED) : m_pLable_CardORG->SetBkColor(STATE_COLOR_GRAY1);
		m_Adlink->IsNEL(strAxis) ? m_pLable_CardNEL->SetBkColor(STATE_COLOR_RED) : m_pLable_CardNEL->SetBkColor(STATE_COLOR_GRAY1);
	}
}


