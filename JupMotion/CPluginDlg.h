#pragma once

#include "StdAfx.h"
using namespace DuiLib;
#include "MotionCard/MotionParameter.h"
#include "MotionCard/AdlinkController.h"
#include "MyTipsDialog.h"

extern AdlinkController* g_pMotion;

// ���б����
enum AxisListItem
{
	CardAxisIndex = 0,
	AxisName,
	AxisType,
	AxisGroup
};
// λ���б����
enum AxisPosItem
{
	nId = 0,
	AxisPosName,
	AxisPos,
	AxisPosStep,
	AxisPosMove,
	AxisPosDebug
};

class CPluginDlg : public JupSubDialog
{
public:
	~CPluginDlg();

	virtual LPCTSTR GetWindowClassName() const	{ return _T("MotionMain"); }
	virtual CDuiString GetSkinFile()			{ return _T("JupMotion_Main.xml"); }
	virtual CDuiString GetSkinFolder()			{ return _T(""); }
	virtual UILIB_RESOURCETYPE GetResourceType() const { return UILIB_ZIP; }
	virtual CDuiString GetZIPFileName() const	{ return _T("PluginMotion.zip"); }

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void Notify(TNotifyUI& msg);
	virtual void InitWindow();

	// �Զ�����Ϣ
	LRESULT CustomEvent(JupCustomEvent* event) override;

private:
	void OnMotionCtrlClick(TNotifyUI & msg);
	void OnItemSelect(TNotifyUI & msg);

	// ��ʼ���忨IO��ʾ
	void InitInputIOListUI();
	void InitOutputIOListUI();
	// ��ʼ�����½������б��λ���б�(Ĭ����ʾ��һ��)
	void ListInitUpdate();
	void PosListUpdate();
	// ʹ��/ʧ�ܽ��水ť(���ݰ忨����״̬)
	void ButtonEnable(bool is_enable);

	// �Զ��궨Բ�ģ����ƶ���λ
	bool AxisMoveAndWaitting(std::string axis_name, double distance, double speed_ratio);

private:
	// ���水ť�����Ӧ
	void OnBtnCardConnectClick(TNotifyUI & msg);
	void OnBtnCardCloseClick(TNotifyUI & msg);
	void OnBtnAxisPosParasSetClick(TNotifyUI & msg);
	void OnBtnAxisPosAddClick(TNotifyUI & msg);
	void OnBtnAxisPosDelClick(TNotifyUI & msg);
	void OnBtnAxisNegativeRelativeMoveClick(TNotifyUI & msg);
	void OnBtnAxisPositiveRelativeMoveClick(TNotifyUI & msg);
	void OnBtnAxisAbsMoveClick(TNotifyUI & msg);
	void OnBtnAxisParasDlgOpenClick(TNotifyUI & msg);
	void OnBtnAxisAddClick(TNotifyUI & msg);
	void OnBtnAxisDelClick(TNotifyUI & msg);
	void OnBtnAxisEnableClick(TNotifyUI & msg);
	void OnBtnAxisDisableClick(TNotifyUI & msg);
	void OnBtnAxisHomeClick(TNotifyUI & msg);
	void OnBtnAxisStopClick(TNotifyUI & msg);
	void OnBtnAxisVmoveNegativeClick(TNotifyUI & msg);
	void OnBtnAxisVmovePositiveClick(TNotifyUI & msg);
	void OnBtnAxisClearErrorClick(TNotifyUI & msg);
	void OnBtnCardResetClick(TNotifyUI & msg);
	void OnBtnAxisPosMoveClick(TNotifyUI & msg);

	// io
	void OnBtnInputParasDlgOpenClick(TNotifyUI & msg);
	void OnBtnInputAddClick(TNotifyUI & msg);
	void OnBtnInputDelClick(TNotifyUI & msg);
	void OnCheckInputUseClick(TNotifyUI & msg);
	void OnBtnOutputParasDlgOpenClick(TNotifyUI & msg);
	void OnBtnOutputAddClick(TNotifyUI & msg);
	void OnBtnOutputDelClick(TNotifyUI & msg);
	void OnBtnOutputIOClick(TNotifyUI & msg);

	// ioһ������
	void OnBtnSocketCoverOpenClick(TNotifyUI & msg);
	void OnBtnSocketCoverCloseClick(TNotifyUI & msg);
	void OnBtnSocketCoverUpClick(TNotifyUI & msg);
	void OnBtnSocketCoverDownClick(TNotifyUI & msg);
	void OnBtnSocketCoverCloseDownClick(TNotifyUI & msg);
	void OnBtnSocketCoverUpOpenClick(TNotifyUI & msg);
	void OnBtnCylHoldDutClick(TNotifyUI & msg);
	void OnBtnCylPutDutClick(TNotifyUI & msg);

private:
	void OnRecvStopMessage(WPARAM wParam, LPARAM lParam);
	void OnTimer(WPARAM wParam, LPARAM lParam);

public:
	MotionParameter* m_pMotionParameter;
	AdlinkController* m_Adlink;
private:
	// ��������ؼ�����
	CButtonUI*	m_pBtn_CardConnect;
	CButtonUI*	m_pBtn_CardClose;
	CListUI*	m_pList_AxisList;
	CLabelUI*	m_pLable_CurAxis;
	CListUI*	m_pList_AxisPos;
	CButtonUI*	m_pBtn_AxisPosParasSave;
	CButtonUI*	m_pBtn_AxisPosAdd;
	CButtonUI*	m_pBtn_AxisPosDel;
	CButtonUI*	m_pBtn_nRelativeMove;
	CEditUI*	m_pEdit_RelativeMove;
	CButtonUI*	m_pBtn_PositiveMove;
	CButtonUI*	m_pBtn_AbsMove;
	CLabelUI*	m_pLable_CurPos;
	CButtonUI*	m_pBtn_AxisParasDlgOpen;
	CButtonUI*	m_pBtn_AxisAdd;
	CButtonUI*	m_pBtn_AxisDel;
	CButtonUI*	m_pBtn_AxisEnable;
	CButtonUI*	m_pBtn_AxisDisable;
	CButtonUI*	m_pBtn_AxisHome;
	CButtonUI*	m_pBtn_AxisStop;
	CButtonUI*	m_pBtn_VmoveNegative;
	CButtonUI*	m_pBtn_VmovePositive;
	CButtonUI*	m_pBtn_AxisClearError;
	CButtonUI*	m_pBtn_CardReset;
	CLabelUI*	m_pLable_CardAlarm;
	CLabelUI*	m_pLable_CardServo;
	CLabelUI*	m_pLable_CardPEL;
	CLabelUI*	m_pLable_CardORG;
	CLabelUI*	m_pLable_CardNEL;
	CLabelUI*	m_pLable_CardConnectStatus;

	CTabLayoutUI* m_pControl;

	// IO
	CListUI*	m_pList_IO_Input;
	CListUI*	m_pList_IO_Output;
	CButtonUI*	m_pBtn_InputConfig;
	CButtonUI*	m_pBtn_InputAdd;
	CButtonUI*	m_pBtn_InputDel;
	CButtonUI*	m_pBtn_OutputConfig;
	CButtonUI*	m_pBtn_OutputAdd;
	CButtonUI*	m_pBtn_OutputDel;
};
