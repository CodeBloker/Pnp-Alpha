#pragma once

#include "StdAfx.h"
using namespace DuiLib;
#include "MilManager.h"
#include <random>
#include "JupCore.h"
#include "../_INCLUDE/ProjectEvent.h"
using namespace ProjectEvent;

class MilDlg : public JupSubDialog
{
public:
	MilDlg();
	virtual ~MilDlg();

public:
	UILIB_RESOURCETYPE GetResourceType() const override;
	CDuiString GetSkinFolder() override;
	CDuiString GetSkinFile() override;
	CDuiString GetZIPFileName() const override;
	LPCTSTR GetWindowClassName() const override;

protected:
	LRESULT ResponseDefaultKeyEvent(WPARAM wParam) override;
	void InitWindow() override;
	void OnFinalMessage(HWND hWnd) override;
	void Notify(TNotifyUI& msg) override;

	CControlUI* CreateControl(LPCTSTR pstrClass) override;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;	
	void OnExit(TNotifyUI& msg);	

	LRESULT CustomEvent(JupCustomEvent* event) override;

private:
	// 界面按钮事件响应
	void OnBtnClick(TNotifyUI & msg);
	void OnBtnImagePathClick(TNotifyUI & msg);
	void OnBtnImageCalculateClick(TNotifyUI & msg);
	void OnBtnClearUIClick(TNotifyUI & msg);

private:
	CEditUI* m_pEdit_ImageFile;
	CComboUI* m_pCom_Index;
	CEditUI* m_pEdit_Degree;
	CEditUI* m_pEdit_Distance;
	CEditUI* m_pEdit_midPointX;
	CEditUI* m_pEdit_midPointY;
	CLabelUI* m_pLable_OutputResult;

	COptionUI* m_pOp_BottomCross;
	COptionUI* m_pOp_PNPCross;
	COptionUI* m_pOp_PNPCrossAndCircle;

private:
	MilManager* m_milManager;
	int socketIndex = 0;

public:
	//PNP视觉与底部视觉的校准
	void MilDigPnpVisualCalibrationGetResult(std::string m_image_ptr);
	//PNP吸嘴校准
	void MilDigNozzleVisualCalibrationGetResult(std::string m_image_ptr);

	//模拟MIL算法调用
	void MilTestVisualGetResult(std::string image_file, std::string mmf_file, JMilFindModelPnpEvent* e, std::string &file_out);
	void MILTestNozzleVisualGetResult(std::string image_file, std::string mmf_file, std::string mmf_file2, JMilFindModelNozzleEvent* e, std::string &file_out);

	//计算上料时 B2B正面中心
	void MilTestB2BTopVisualGetResult(std::string image_file, std::string mmf_file, JMilFindCenterEvent* e);

	//计算下料时 DownSocket俩Mark点
	void MilTestDownSocketMarkVisualGetResult(std::string image_file, std::string mmf_file, JMilFindSocketMarkCenterEvent* e);

	//计算放进下料口后 B2B跟Socket两个Mark点的距离
	void MilTestDownSocketMarkAndB2BDistanceVisualGetResult(std::string image_file, std::string mmf_file, std::string mmf_circle_file, JMilFindSocketMarkAndB2BDistanceEvent* e);

//用来测试
public:
	void funcTest();
};