#include "MilDlg.h"
#include "Common/JupCommon.h"

int number = 1;

double getRandomDouble(double min, double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

MilDlg::MilDlg()
{
	m_milManager = MilManager::GetInstance();
}

MilDlg::~MilDlg()
{	
}

UILIB_RESOURCETYPE MilDlg::GetResourceType() const
{
	return UILIB_ZIP;
}

CDuiString MilDlg::GetSkinFolder()
{
	return "";
}

CDuiString MilDlg::GetSkinFile()
{
	return "main_frame.xml";
}

CDuiString MilDlg::GetZIPFileName() const
{
	return _T("PluginMil.zip");
}

LPCTSTR MilDlg::GetWindowClassName() const
{
	return "MilDlg";
}

LRESULT MilDlg::ResponseDefaultKeyEvent(WPARAM wParam)
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

void MilDlg::InitWindow()
{	
	jCore->RegisterEventWindow(g_MilWidget, this);

	m_pEdit_ImageFile = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_image_path")));
	//m_pCom_Index = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("socket_id")));
	m_pEdit_Degree = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Degree")));
	m_pEdit_Distance = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_Distance")));
	m_pEdit_midPointX = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("midPointX")));
	m_pEdit_midPointY = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("midPointY")));
	m_pLable_OutputResult = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("mil_output")));

	m_pOp_BottomCross = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_ImageSaveBmp")));
	m_pOp_PNPCross = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_ImageSaveJpeg")));
	m_pOp_PNPCrossAndCircle = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_ImageSavePng")));
}

void MilDlg::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	PostQuitMessage(0);
}

void MilDlg::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		OnBtnClick(msg);
	}
}

CControlUI * MilDlg::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT MilDlg::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT MilDlg::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT MilDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	int ret = MessageBoxA(NULL, "是否退出程序？", "Quit", MB_YESNO);
	if (ret == IDYES)
		bHandled = FALSE;	//TRUE表示不处理
	else
		bHandled = TRUE;
	return 0;
}

void MilDlg::OnExit(TNotifyUI & msg)
{
	this->Close();
}

LRESULT MilDlg::CustomEvent(JupCustomEvent * event)
{
	JupCustomEvent::eType type = event->Type();
	if (type == ProjectEvent::e_JMilEvent)
	{
		auto e = dynamic_cast<JMilEvent*>(event);
	}
	else if (type == ProjectEvent::e_JMilFindModelPnpEvent) {
		auto e = dynamic_cast<JMilFindModelPnpEvent*>(event);
		MilTestVisualGetResult(e->m_file, e->m_file_mmf, e, e->m_file_out);
	}
	else if (type == ProjectEvent::e_JMilFindModelNozzleEvent)
	{
		auto e = dynamic_cast<JMilFindModelNozzleEvent*>(event);
		MILTestNozzleVisualGetResult(e->m_file, e->m_file_mmf, e->m_file2_mmf, e, e->m_file_out);
	}
	else if (type == ProjectEvent::e_JMilFindCenterEvent)
	{
		auto e = dynamic_cast<JMilFindCenterEvent*>(event);
		MilTestB2BTopVisualGetResult(e->m_file, e->m_file_mmf, e);
		//MilTestDownSocketMarkVisualGetResult(e->m_file, e->m_file_mmf, e);
	}
	else if (type == ProjectEvent::e_JMilFindSocketMarkCenterEvent)
	{
		auto e = dynamic_cast<JMilFindSocketMarkCenterEvent*>(event);
		MilTestDownSocketMarkVisualGetResult(e->m_file, e->m_file_mmf, e);
	}
	else if (type == ProjectEvent::e_JMilFindSocketMarkAndB2BDistanceEvent)
	{
		auto e = dynamic_cast<JMilFindSocketMarkAndB2BDistanceEvent*>(event);
		MilTestDownSocketMarkAndB2BDistanceVisualGetResult(e->m_file, e->m_file_mmf, e->m_file_circle_mmf, e);
	}
	return 0;
}

void MilDlg::OnBtnClick(TNotifyUI & msg)
{
	if (msg.pSender->GetName() == _T("btn_image_open"))
	{
		OnBtnImagePathClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_Mil_Calr"))
	{
		OnBtnImageCalculateClick(msg);
	}
	else if (msg.pSender->GetName() == _T("btn_Mil_Clear"))
	{
		OnBtnClearUIClick(msg);
	}
}
#include "CSVReader.h"
void MilDlg::OnBtnImagePathClick(TNotifyUI & msg)
{
	//std::string imageFile = "E:\\AlphaDoeImage\\20240531\\202405311717\\Circle_0_20240531171719\\A2_00D33111644_20240531171720.bmp";
	//static std::string csvFilePath;
	//if (csvFilePath.empty())
	//{
	//	std::string csvFileName = imageFile;
	//	std::vector<std::string> file_path = Jup::Split(csvFileName, "\\");
	//	file_path.pop_back();
	//	file_path.pop_back();
	//	csvFileName = Jup::Join(file_path, "\\") + "\\" + "DoeResult.csv";
	//	struct stat buffer;
	//	if (!stat(csvFileName.c_str(), &buffer) == 0)
	//	{

	//	}
	//	CSVReader m_csv(csvFileName);
	//	std::vector<std::string> head;
	//	head.push_back("ImagePath");
	//	head.push_back("ResultImagePath");
	//	head.push_back("PointX");
	//	head.push_back("PointY");
	//	head.push_back("Angle");
	//	m_csv.addRow(head);
	//	m_csv.writeToFile();
	//}

	OPENFILENAME ofn;
	TCHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile) / sizeof(TCHAR);
	ofn.lpstrFilter = _T("位图文件\0*.bmp");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	CDuiString strSelectedFilePath;
	if (GetOpenFileName(&ofn) == TRUE)
	{
		strSelectedFilePath = ofn.lpstrFile;
		MessageBox(m_hWnd, strSelectedFilePath, _T("选定的 BMP 文件"), MB_OK);
	}

	if (m_pOp_BottomCross->IsSelected())
	{
		//底部视觉校准
		std::string file_name = std::string(strSelectedFilePath);
		std::string file_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Bottom Cross.mmf";
		std::vector<PointXYA> Result;
		std::vector<MilRect> ROIs;
		ROIs.push_back(MilRect(520, 520, 753, 817));	//左上
		ROIs.push_back(MilRect(496, 3936, 737, 769));	//左下
		ROIs.push_back(MilRect(3896, 624, 705, 745));	//右上
		ROIs.push_back(MilRect(3848, 3976, 729, 761));	//右下
		std::string file_out;
		if (!file_name.empty())
		{
			float fSocketAngle;
			float fdistance;
			float deltaX, deltaY;
			std::string str = m_milManager->VisionBottomCrossCamerResult(file_name, file_out, file_mmf, ROIs, Result, fdistance, fSocketAngle, deltaX, deltaY);
			if (str.rfind(".jpg") == str.size() - 4)
			{
				m_pEdit_Degree->SetText(std::to_string(fSocketAngle).c_str());
				m_pEdit_Distance->SetText(std::to_string(fdistance).c_str());
				m_pEdit_midPointX->SetText(std::to_string(deltaX).c_str());
				m_pEdit_midPointY->SetText(std::to_string(deltaY).c_str());
				m_pLable_OutputResult->SetBkImage(str.c_str());
			}
		}
	}
	else if (m_pOp_PNPCross->IsSelected())
	{
		//PNP视觉与十字校准板校准
		std::string file_name = std::string(strSelectedFilePath);
		std::string file_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Top Cross.mmf";
		std::vector<PointXYA> Result;
		std::vector<MilRect> ROIs;
		ROIs.push_back(MilRect(400, 228, 573, 529));	//左上
		ROIs.push_back(MilRect(420, 1260, 513, 505));	//左下
		ROIs.push_back(MilRect(1412, 220, 593, 525));	//右上
		ROIs.push_back(MilRect(1452, 1248, 509, 533));	//右下
		std::string file_out;
		if (!file_name.empty())
		{
			float fSocketAngle;
			float fdistance;
			float deltaX, deltaY;
			std::string str = m_milManager->VisionTopCrossCamerResult(file_name, file_out, file_mmf, ROIs, Result, fdistance, fSocketAngle, deltaX, deltaY);
			if (str.rfind(".jpg") == str.size() - 4)
			{
				m_pEdit_Degree->SetText(std::to_string(fSocketAngle).c_str());
				m_pEdit_Distance->SetText(std::to_string(fdistance).c_str());
				m_pEdit_midPointX->SetText(std::to_string(deltaX).c_str());
				m_pEdit_midPointY->SetText(std::to_string(deltaY).c_str());
				m_pLable_OutputResult->SetBkImage(str.c_str());
			}
		}
	}
	else if (m_pOp_PNPCrossAndCircle->IsSelected())
	{
		std::string file_name = std::string(strSelectedFilePath);
		std::string file_cross_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Bottom Cross.mmf";
		std::string file_circle_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Bottom Circleli-1.mmf";

		//十字
		std::vector<PointXYA> Result;
		std::vector<MilRect> ROIs;
		ROIs.push_back(MilRect(552, 584, 689, 697));	//左上
		ROIs.push_back(MilRect(440, 3944, 825, 745));	//左下
		ROIs.push_back(MilRect(3864, 616, 793, 769));	//右上
		ROIs.push_back(MilRect(3808, 3944, 809, 825));	//右下

		//圆点
		std::vector<PointXYA> Circle_Result;
		std::vector<MilRect> Circle_ROIs;
		Circle_ROIs.push_back(MilRect(1728, 928, 809, 873));	//左上
		Circle_ROIs.push_back(MilRect(1760, 3384, 753, 777));	//左下
		Circle_ROIs.push_back(MilRect(2488, 936, 801, 849));	//右上
		Circle_ROIs.push_back(MilRect(2408, 3376, 857, 921));	//右下

		std::string file_out;
		if (!file_name.empty())
		{
			float fSocketAngle;
			float fdistance;
			float deltaX, deltaY;
			std::string str = m_milManager->VisionButtomCircleCamerResult(file_name, file_out, file_cross_mmf, file_circle_mmf, ROIs, Circle_ROIs, Result, Circle_Result, fdistance, fSocketAngle, deltaX, deltaY);
			if (str.rfind(".jpg") == str.size() - 4)
			{
				m_pEdit_Degree->SetText(std::to_string(fSocketAngle).c_str());
				m_pEdit_Distance->SetText(std::to_string(fdistance).c_str());
				m_pEdit_midPointX->SetText(std::to_string(deltaX).c_str());
				m_pEdit_midPointY->SetText(std::to_string(deltaY).c_str());
				m_pLable_OutputResult->SetBkImage(str.c_str());
			}
		}

	}

	//底部视觉校准
	//std::string file_name = std::string(strSelectedFilePath);
	//std::string file_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Bottom Cross.mmf";
	//std::vector<PointXYA> Result;
	//std::vector<MilRect> ROIs;
	//ROIs.push_back(MilRect(520, 520, 753, 817));	//左上
	//ROIs.push_back(MilRect(496, 3936, 737, 769));	//左下
	//ROIs.push_back(MilRect(3896, 624, 705, 745));	//右上
	//ROIs.push_back(MilRect(3848, 3976, 729, 761));	//右下
	//std::string file_out;
	//if (!file_name.empty())
	//{
	//	float fSocketAngle;
	//	float fdistance;
	//	float deltaX, deltaY;
	//	std::string str = m_milManager->VisionBottomCrossCamerResult(file_name, file_out, file_mmf, ROIs, Result, fdistance, fSocketAngle, deltaX, deltaY);
	//	if (str.rfind(".jpg") == str.size() - 4)
	//	{
	//		m_pEdit_Degree->SetText(std::to_string(fSocketAngle).c_str());
	//		m_pEdit_Distance->SetText(std::to_string(fdistance).c_str());
	//		m_pEdit_midPointX->SetText(std::to_string(deltaX).c_str());
	//		m_pEdit_midPointY->SetText(std::to_string(deltaY).c_str());
	//		m_pLable_OutputResult->SetBkImage(str.c_str());
	//	}
	//}

	//PNP视觉与十字校准板校准
	//std::string file_name = std::string(strSelectedFilePath);
	//std::string file_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Top Cross.mmf";
	//std::vector<PointXYA> Result;
	//std::vector<MilRect> ROIs;
	//ROIs.push_back(MilRect(572, 448, 229, 233));	//左上
	//ROIs.push_back(MilRect(576, 1444, 253, 273));	//左下
	//ROIs.push_back(MilRect(1568, 408, 261, 273));	//右上
	//ROIs.push_back(MilRect(1568, 1416, 289, 289));	//右下
	//std::string file_out;
	//if (!file_name.empty())
	//{
	//	float fSocketAngle;
	//	float fdistance;
	//	float deltaX, deltaY;
	//	std::string str = m_milManager->VisionTopCrossCamerResult(file_name, file_out, file_mmf, ROIs, Result, fdistance, fSocketAngle, deltaX, deltaY);
	//	if (str.rfind(".jpg") == str.size() - 4)
	//	{
	//		m_pEdit_Degree->SetText(std::to_string(fSocketAngle).c_str());
	//		m_pEdit_Distance->SetText(std::to_string(fdistance).c_str());
	//		m_pEdit_midPointX->SetText(std::to_string(deltaX).c_str());
	//		m_pEdit_midPointY->SetText(std::to_string(deltaY).c_str());
	//		m_pLable_OutputResult->SetBkImage(str.c_str());
	//	}
	//}
}

void MilDlg::OnBtnImageCalculateClick(TNotifyUI & msg)
{
	//std::string fileFloder = m_pEdit_ImageFile->GetText().GetData();
	//auto fileList = Jup::FindAllFile(fileFloder);
	//for (auto& file : fileList)
	//{
	//	if (file.find("_OUTImage") != std::string::npos)
	//	{
	//		continue;
	//	}
	//	//int nSocIndex = (int)m_pCom_Index->GetText().GetData();
	//	std::string outputPath;
	//	float degree;
	//	float midPointX;
	//	float midPointY;

	//	bool ret = m_milManager->fnGetPictureDegree(socketIndex, file, outputPath, degree, midPointX, midPointY);
	//	if (ret)
	//	{
	//		std::string strVal = m_pLable_OutputResult->GetText().GetData();
	//		CDuiString valDegree;
	//		valDegree.Format(_T("%.5f"), degree);
	//		CDuiString strMidPointX;
	//		strMidPointX.Format(_T("%.5f"), midPointX);
	//		CDuiString strMidPointY;
	//		strMidPointY.Format(_T("%.5f"), midPointY);
	//		strVal += file + "\t degree:" + std::string(valDegree) + "\t midPointX:" + std::string(strMidPointX) + "\t midPointY:" + std::string(strMidPointY) + "\r\n";
	//		m_pLable_OutputResult->SetText(strVal.c_str());
	//	}
	//}
	//jCore->PostEvent(ProjectEvent::g_DvpWidget, new ProjectEvent::JDvpPnpCalibrationEvent(10, 20, 30, 40));
	//std::string path1 = "C:\\Users\\106866\\Desktop\\newImage\\__20240731151111.bmp";
	//std::string path2 = "C:\\Users\\106866\\Desktop\\22222.png";
	//
	////jCore->SendEvent(ProjectEvent::g_DvpWidget, &ProjectEvent::JDvpPnpCalibrationEvent(33.232, 42.433, 12.323, 40.3232, path2));
	//while (true)
	//{
	//	if(number%2 == 0)
	//		jCore->SendEvent(ProjectEvent::g_DvpWidget, &ProjectEvent::JDvpPnpCalibrationEvent(10.322, 20.543, 30.314, 54.342, path1));
	//	else
	//		jCore->SendEvent(ProjectEvent::g_DvpWidget, &ProjectEvent::JDvpPnpCalibrationEvent(33.232, 42.433, 12.323, 40.3232, path2));
	//	number++;
	//	Sleep(500);
	//}
	//do
	//{
	//	Sleep(1000);
	//	switch (number)
	//	{
	//	case 1:
	//		//m_pLable_OutputResult->SetBkImage(path1.c_str());
	//		jCore->SendEvent(ProjectEvent::g_DvpWidget, &ProjectEvent::JDvpPnpCalibrationEvent(10.322, 20.543, 30.314, 54.342, path1));
	//		break;
	//	case 2:
	//		//m_pLable_OutputResult->SetBkImage(path2.c_str());
	//		jCore->PostEvent(ProjectEvent::g_DvpWidget, new ProjectEvent::JDvpPnpCalibrationEvent(33.232, 42.433, 12.323, 40.3232, path2));
	//		break;
	//	default:
	//		break;
	//	}
	//	number++;
	//	if (number > 2)
	//	{
	//		number = 1;
	//	}
	//} while (true);
	std::thread t(&MilDlg::funcTest, this);
	t.detach();
}

void MilDlg::OnBtnClearUIClick(TNotifyUI & msg)
{
	m_pEdit_Degree->SetText("");
	m_pEdit_midPointX->SetText("");
	m_pEdit_midPointY->SetText("");
}

void MilDlg::MilDigPnpVisualCalibrationGetResult(std::string m_image_ptr)
{
	std::string file_cross_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Top Cross.mmf";
	std::vector<PointXYA> Result;
	std::vector<MilRect> ROIs;
	ROIs.push_back(MilRect(416, 284, 573, 549));	//左上
	ROIs.push_back(MilRect(436, 1332, 521, 501));	//左下
	ROIs.push_back(MilRect(1460, 276, 489, 509));	//右上
	ROIs.push_back(MilRect(1464, 1300, 525, 553));	//右下
	std::string m_file_out;
	if (!m_image_ptr.empty())
	{
		float fSocketAngle;
		float fdistance;
		float deltaX, deltaY;
		std::string str = m_milManager->VisionTopCrossCamerResult(m_image_ptr, m_file_out, file_cross_mmf, ROIs, Result, fdistance, fSocketAngle, deltaX, deltaY);
		//若执行成功则返回图片路径，然后使用sentEvent传给Dvp模块界面上
		const std::string imageSuffix = "_Result.jpg";
		//if (str.find(imageSuffix) != std::string::npos)
		//	jCore->PostEvent(ProjectEvent::g_DvpWidget, new ProjectEvent::JDvpPnpCalibrationEvent(Result.back().X, Result.back().Y, 2448 / 2.0, 2048 / 2.0, str));
		//else
		//	return;
	}
}

void MilDlg::MilDigNozzleVisualCalibrationGetResult(std::string m_image_ptr)
{
	std::string file_cross_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Bottom Cross.mmf";
	std::string file_circle_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Bottom Circleli-1.mmf";
	//十字
	std::vector<PointXYA> Result;
	std::vector<MilRect> ROIs;
	ROIs.push_back(MilRect(352, 432, 1121, 993));	//左上
	ROIs.push_back(MilRect(328, 3376, 1057, 1025));	//左下
	ROIs.push_back(MilRect(3720, 400, 1097, 1097));	//右上
	ROIs.push_back(MilRect(3632, 3720, 1177, 1177));//右下

	//圆点
	std::vector<PointXYA> Circle_Result;
	std::vector<MilRect> Circle_ROIs;
	Circle_ROIs.push_back(MilRect(1800, 920, 825, 849));	//左上
	Circle_ROIs.push_back(MilRect(1752, 3120, 985, 1129));	//左下
	Circle_ROIs.push_back(MilRect(2504, 872, 849, 897));	//右上
	Circle_ROIs.push_back(MilRect(2544, 3208, 889, 913));	//右下
	std::string m_file_out;
	if (!m_image_ptr.empty())
	{
		float fSocketAngle;
		float fdistance;
		float deltaX, deltaY;
		std::string str = m_milManager->VisionButtomCircleCamerResult(m_image_ptr, m_file_out, file_cross_mmf, file_circle_mmf, ROIs, Circle_ROIs, Result, Circle_Result, fdistance, fSocketAngle, deltaX, deltaY);
		//若执行成功则返回图片路径，然后使用sentEvent传给Dvp模块界面上
		const std::string imageSuffix = "_Result.jpg";
		//if (str.find(imageSuffix) != std::string::npos)
		//	jCore->PostEvent(ProjectEvent::g_DvpWidget, new ProjectEvent::JDvpNozzleCalibrationEvent(Circle_Result.back().X, Circle_Result.back().Y, Circle_Result.back().R, Result.back().X, Result.back().Y, Result.back().R, str));
		//else
		//	return;
	}
}

void MilDlg::MilTestVisualGetResult(std::string image_file, std::string mmf_file, JMilFindModelPnpEvent* e, std::string & file_out)
{
	//std::string file_cross_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Top Cross.mmf";
	std::vector<PointXYA> Result;
	std::vector<MilRect> ROIs;
	ROIs.push_back(MilRect(416, 284, 573, 549));	//左上
	ROIs.push_back(MilRect(436, 1332, 521, 501));	//左下
	ROIs.push_back(MilRect(1336, 324, 489, 509));	//右上
	ROIs.push_back(MilRect(1304, 1320, 525, 553));	//右下
	std::string m_file_out;
	if (!image_file.empty())
	{
		float fSocketAngle;
		float fdistance;
		float deltaX, deltaY;
		std::string str = m_milManager->VisionTopCrossCamerResult(image_file, m_file_out, mmf_file, ROIs, Result, fdistance, fSocketAngle, deltaX, deltaY);
		//若执行成功则返回图片路径，然后使用sentEvent传给Dvp模块界面上
		const std::string imageSuffix = "_Result.jpg";
		if (str.find(imageSuffix) != std::string::npos)
		{
			file_out = str;
			e->m_calibrationPointX = Result.at(0).X;
			e->m_calibrationPointY = Result.at(0).Y;
			e->m_calibrationAngle = Result.at(0).R;
			e->m_actualPointX = Result.at(1).X;
			e->m_actualPointY = Result.at(1).Y;
			e->m_actualPointAngle = Result.at(1).R;
		}
		else
			file_out = "";
	}



	//file_out = "Test...";
}

void MilDlg::MILTestNozzleVisualGetResult(std::string image_file, std::string mmf_file, std::string mmf_file2, JMilFindModelNozzleEvent *e, std::string & file_out)
{
	//std::string file_cross_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Bottom Cross.mmf";
	//std::string file_circle_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0812\\Bottom Circleli-1.mmf";
	//十字
	std::vector<PointXYA> Result;
	std::vector<MilRect> ROIs;
	ROIs.push_back(MilRect(544, 480, 1025, 1089));	//左上
	ROIs.push_back(MilRect(512, 3840, 1073, 1057));	//左下
	ROIs.push_back(MilRect(3848, 432, 1105, 1089));	//右上
	ROIs.push_back(MilRect(3880, 3768, 1137, 1153));//右下

	//圆点
	std::vector<PointXYA> Circle_Result;
	std::vector<MilRect> Circle_ROIs;
	Circle_ROIs.push_back(MilRect(1600, 792, 1049, 1169));	//左上
	Circle_ROIs.push_back(MilRect(1680, 3264, 849, 1057));	//左下
	Circle_ROIs.push_back(MilRect(2528, 864, 849, 1041));	//右上
	Circle_ROIs.push_back(MilRect(2432, 3280, 993, 1137));	//右下
	std::string m_file_out;

	if (!image_file.empty())
	{
		float fSocketAngle;
		float fdistance;
		float deltaX, deltaY;
		std::string str = m_milManager->VisionButtomCircleCamerResult(image_file, m_file_out, mmf_file, mmf_file2, ROIs, Circle_ROIs, Result, Circle_Result, fdistance, fSocketAngle, deltaX, deltaY);
		//若执行成功则返回图片路径，然后使用sentEvent传给Dvp模块界面上
		const std::string imageSuffix = "_Result.jpg";
		if (str.find(imageSuffix) != std::string::npos)
		{
			file_out = str;
			e->m_calibrationPointX = Result.at(0).X;
			e->m_calibrationPointY = Result.at(0).Y;
			e->m_calibrationAngle = Result.at(0).R;
			e->m_actualPointX = Circle_Result.at(0).X;
			e->m_actualPointY = Circle_Result.at(0).Y;
			e->m_actualPointAngle = Circle_Result.at(0).R;
		}
		else
			file_out = "";
	}


}

void MilDlg::MilTestB2BTopVisualGetResult(std::string image_file, std::string mmf_file, JMilFindCenterEvent* e)
{
	//std::string file_name = "D:\\AlphaDoeImage\\temp\\SoftwareOnce_20240822141024.bmp";
	//std::string file_mmf = "D:\\VISION\\FZ-TEST\\TEST0807\\ping.mmf";
	std::string m_file_out;
	float deltaX = 0.0, deltaY = 0.0;
	if (!image_file.empty())
	{
		std::string str = m_milManager->VisionB2BTopCenterCamerResult(image_file, m_file_out, mmf_file, deltaX, deltaY);
		//若执行成功则返回图片路径，然后使用sentEvent传给Dvp模块界面上
		const std::string imageSuffix = "_Result.jpg";
		if (str.find(imageSuffix) != std::string::npos)
		{
			e->m_event_deltaX = deltaX;
			e->m_event_deltaY = deltaY;
		}
	}

}

void MilDlg::MilTestDownSocketMarkVisualGetResult(std::string image_file, std::string mmf_file, JMilFindSocketMarkCenterEvent * e)
{
	std::string m_file_out;
	float deltaX = 0.0, deltaY = 0.0;
	std::vector<MilRect> Circle_ROIs;
	Circle_ROIs.push_back(MilRect(0, 0, 2448, 2048));	//整张图
	//Circle_ROIs.push_back(MilRect(0, 960, 2440, 1085));	//下
	if (!image_file.empty())
	{
		std::string str = m_milManager->VisionSocketMarkCenterCamerResult(image_file, m_file_out, mmf_file, Circle_ROIs, deltaX, deltaY);
		//若执行成功则返回图片路径，然后使用sentEvent传给Dvp模块界面上
		const std::string imageSuffix = "_Result.jpg";
		if (str.find(imageSuffix) != std::string::npos)
		{
			e->m_event_deltaX = deltaX;
			e->m_event_deltaY = deltaY;
		}
	}
}

void MilDlg::MilTestDownSocketMarkAndB2BDistanceVisualGetResult(std::string image_file, std::string mmf_file, std::string mmf_circle_file, JMilFindSocketMarkAndB2BDistanceEvent * e)
{
	std::string m_file_out;
	float distance = 0.0;
	float SocketAngle = 0.0;
	std::vector<MilRect> Circle_ROIs;
	Circle_ROIs.push_back(MilRect(0, 0, 2448, 2048));	//整张图
	//Circle_ROIs.push_back(MilRect(0, 960, 2440, 1085));	//下
	if (!image_file.empty())
	{
		std::string str = m_milManager->VisionSocketMarkAndB2BDistanceResult(image_file, m_file_out, mmf_file, mmf_circle_file, Circle_ROIs, SocketAngle, distance);
		//若执行成功则返回图片路径，然后使用sentEvent传给Dvp模块界面上
		const std::string imageSuffix = "_Result.jpg";
		if (str.find(imageSuffix) != std::string::npos)
		{
			e->m_SocketAngle = SocketAngle;
			e->m_distance = distance;
		}
		else
		{
			e->m_SocketAngle = 0.0;
			e->m_distance = 0.0;
		}
	}
}

void MilDlg::funcTest()
{
	std::string path1 = "C:\\Users\\106866\\Desktop\\newImage\\__20240731151111.bmp";
	std::string path2 = "C:\\Users\\106866\\Desktop\\22222.png";

	//jCore->SendEvent(ProjectEvent::g_DvpWidget, &ProjectEvent::JDvpPnpCalibrationEvent(33.232, 42.433, 12.323, 40.3232, path2));
	while (true)
	{
		//if (number % 2 == 0)
		//	jCore->SendEvent(ProjectEvent::g_DvpWidget, &ProjectEvent::JDvpPnpCalibrationEvent(10.322, 20.543, 30.314, 54.342, path1));
		//else
		//	jCore->SendEvent(ProjectEvent::g_DvpWidget, &ProjectEvent::JDvpPnpCalibrationEvent(33.232, 42.433, 12.323, 40.3232, path2));
		//number++;
		Sleep(500);
	}
}
