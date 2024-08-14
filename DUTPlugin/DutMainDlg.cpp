#include "DutMainDlg.h"
#include "ParasDefine.h"
#include "Common/JupCommon.h"
#include <atltime.h>

#include "JupCore.h"
#include "../_INCLUDE/ProjectEvent.h"
using namespace ProjectEvent;

DutMainDlg::DutMainDlg()
{
	m_dut = DutController::GetInstance();
}

DutMainDlg::~DutMainDlg()
{	
}

UILIB_RESOURCETYPE DutMainDlg::GetResourceType() const
{
	return UILIB_ZIP;
}

CDuiString DutMainDlg::GetSkinFolder()
{
	return "";
}

CDuiString DutMainDlg::GetSkinFile()
{
	return "main_frame.xml";
}

CDuiString DutMainDlg::GetZIPFileName() const
{
	return _T("PluginDUT.zip");
}

LPCTSTR DutMainDlg::GetWindowClassName() const
{
	return "DutMainDlg";
}

LRESULT DutMainDlg::ResponseDefaultKeyEvent(WPARAM wParam)
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

void DutMainDlg::InitWindow()
{	
	m_pEdit_I2CInput = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("dut_intput")));
	m_pList_I2COutput = static_cast<CListUI*>(m_PaintManager.FindControl(_T("dut_output")));
	m_pEdit_I2CAddr = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_DutAddr")));
	m_pEdit_I2CData = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_DutData")));
}

void DutMainDlg::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	PostQuitMessage(0);
}

void DutMainDlg::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		OnBtnClick(msg);
	}
}

CControlUI * DutMainDlg::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT DutMainDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT DutMainDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	int ret = MessageBoxA(NULL, "是否退出程序？", "Quit", MB_YESNO);
	if (ret == IDYES)
		bHandled = FALSE;	//TRUE表示不处理
	else
		bHandled = TRUE;
	return 0;
}

void DutMainDlg::OnExit(TNotifyUI & msg)
{
	this->Close();
}

LRESULT DutMainDlg::CustomEvent(JupCustomEvent * event)
{
	JupCustomEvent::eType type = event->Type();
	if (type == ProjectEvent::e_JHikEvent)
	{
		auto e = dynamic_cast<JHikEvent*>(event);
		//DisplayOneFrameImage((MV_DISPLAY_FRAME_INFO*)e->m_ptr);
		//ShowMsg((const char*)e->m_ptr);
	}

	return 0;
}

void DutMainDlg::OnBtnClick(TNotifyUI & msg)
{
	if (msg.pSender->GetName() == _T("btn_DutOpen"))
	{
		OnBtnDutPowerOnClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_DutClose"))
	{
		OnBtnDutPowerOffClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_DutInit"))
	{
		OnBtnDutInitClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_Read"))
	{
		OnBtnDutReadTxClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_ReadDutAddr"))
	{
		OnBtnI2CAddrReadClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_ReadDutData"))
	{
		OnBtnI2CAddrWriteClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_SwitchDot"))
	{
		OnBtnSwitchToDotClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_SwitchFlood"))
	{
		OnBtnSwitchToFloodClick(msg);
	}
}

void DutMainDlg::OnBtnDutPowerOnClick(TNotifyUI & msg)
{
	bool ret = m_dut->fnCanyouPowerOnTriggerMode(socketIndex, TXRegFile_INI, RXRegFile_INI);
	if (ret)
	{
		ShowMsg("Canyou PowerOn Success");
	}
	else
	{
		ShowMsg("Canyou PowerOn Fail");
	}
}

void DutMainDlg::OnBtnDutPowerOffClick(TNotifyUI & msg)
{
	bool ret = m_dut->fnCanyouPowerOff(socketIndex, "ManuelPowerOff");
	if (ret)
	{
		ShowMsg("Canyou PowerOff Success");
		m_pEdit_I2CAddr->SetText("");
		m_pEdit_I2CData->SetText("");
	}
	else
	{
		ShowMsg("Canyou PowerOff Fail");
	}
}

void DutMainDlg::OnBtnDutInitClick(TNotifyUI & msg)
{
	bool ret = m_dut->fnCanyouInit(socketIndex);
	if (ret)
	{
		ShowMsg("CanyouInit success");
	}
	else
	{
		ShowMsg("CanyouInit fail");
	}
}

void DutMainDlg::OnBtnDutReadTxClick(TNotifyUI & msg)
{
	//bool ret = m_dut.ReadTxASIC_Temper();
	//if (ret)
	//{

	//}
	//else
	//{

	//}
}

void DutMainDlg::OnBtnI2CAddrReadClick(TNotifyUI & msg)
{
	m_pEdit_I2CData->SetText("");
	const char* strAddr = m_pEdit_I2CAddr->GetText().GetData();
	unsigned short uAddr = static_cast<unsigned short>(std::strtoul(strAddr, NULL, 16));
	unsigned char pData;
	bool ret = m_dut->fnReadI2CData(socketIndex, BANFF_TX_SLAVE_ADDRESS, uAddr, 1, &pData);
	if (ret)
	{
		char hex_str[32];
		sprintf(hex_str, "0x%02X", pData);
		m_pEdit_I2CData->SetText(hex_str);
	}
}

void DutMainDlg::OnBtnI2CAddrWriteClick(TNotifyUI & msg)
{
	const char* strAddr = m_pEdit_I2CAddr->GetText().GetData();
	const char* strData = m_pEdit_I2CData->GetText().GetData();

	unsigned char uAddr = static_cast<unsigned short>(std::strtoul(strAddr, NULL, 16));
	unsigned char uData = static_cast<unsigned short>(std::strtoul(strData, NULL, 16));
	bool ret = m_dut->fnWriteI2CData(socketIndex, BANFF_TX_SLAVE_ADDRESS, uAddr, 1, &uData);
	if (ret)
	{
		//MessageBox(NULL, TEXT("Set success!"), NULL, MB_ICONERROR);
		ShowMsg("Write success!");
	}
}

void DutMainDlg::OnBtnSwitchToDotClick(TNotifyUI & msg)
{
	m_dut->switchTriggerLight(socketIndex, "DOT");
}

void DutMainDlg::OnBtnSwitchToFloodClick(TNotifyUI & msg)
{
	m_dut->switchTriggerLight(socketIndex, "FLOOD");
}

std::string DutMainDlg::getOpenFileName()
{
	OPENFILENAME ofn = { 0 };
	TCHAR strFileName[1024] = { 0 };	//用于接收文件名
	ofn.lStructSize = sizeof(OPENFILENAME);	//结构体大小
	ofn.hwndOwner = NULL;					//拥有着窗口句柄
	ofn.lpstrFilter = TEXT("All\0*.*\0jpg\0*.jpg\0bmp\0*.bmp\0\0");	//设置过滤
	ofn.nFilterIndex = 1;	//过滤器索引
	ofn.lpstrFile = strFileName;	//接收返回的文件名，注意第一个字符需要为NULL
	ofn.nMaxFile = sizeof(strFileName);	//缓冲区长度
	ofn.lpstrInitialDir = NULL;			//初始目录为默认
	ofn.lpstrTitle = TEXT("请选择一个文件"); //窗口标题
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY; //文件、目录必须存在，隐藏只读选项
	//打开文件对话框
	if (GetOpenFileName(&ofn)) {
		return strFileName; // 文件路径
	}
	else {
		MessageBox(NULL, TEXT("请选择一文件"), NULL, MB_ICONERROR);
	}
}

std::string DutMainDlg::openPathSaveFileDir()
{
	
}

void DutMainDlg::ShowMsg(const char * msg)
{
	//std::string strText = m_pList_I2COutput->GetText().GetData();
	CTime time = CTime::GetCurrentTime();
	char buf[64] = { 0 };
	sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d    ", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	std::string strText = buf + std::string(msg);
	CLabelUI* label = new CLabelUI;
	label->SetFixedHeight(20);
	label->SetText(strText.c_str());
	m_pList_I2COutput->Add(label);

	if (m_pList_I2COutput->GetCount() >= 1000)
	{
		m_pList_I2COutput->Remove(0);
	}
}
