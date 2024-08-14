#include "MilManager.h"
#include "Common/JupCommon.h"
#include "publicDLL/publicDLL.h"
#include <atltime.h>
#include <future>

MilManager::MilManager()
{
	loadParasFromFile(INSPECTORINFOR_INI);
	MappAllocA("M_DEFAULT", M_DEFAULT, &(m_mil.milApplication));
	MappControl(m_mil.milApplication, M_ERROR, M_PRINT_DISABLE);
	MsysAllocA(m_mil.milApplication, "M_SYSTEM_HOST", M_DEV1, M_COMPLETE, &(m_mil.milSystem));
	testMilInitCopy(m_mil.milApplication, m_mil.milSystem, m_mil.milDisplay);
}

MilManager::~MilManager()
{
}

MilManager *& MilManager::GetInstance()
{
	if (m_SingleInstance == nullptr) {
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (m_SingleInstance == nullptr) {
			m_SingleInstance = new (std::nothrow) MilManager{};
		}
	}
	return m_SingleInstance;
}

void MilManager::fnFindCircleCenter(double x1, double y1, double x2, double y2, double x3, double y3, double & CenterX, double & CenterY, double& CenterR)
{
	visionManager.FindCircleCenter(x1, y1, x2, y2, x3, y3, CenterX, CenterY, CenterR);
}

bool MilManager::fnGetPictureDegree(int nSocIndex, std::string file, std::string & outPath, float & degree, float & midPointX, float & midPointY, bool bDebug)
{
	std::string copyFile = file;

	cv::Mat imgGray = imread(copyFile, 0);
	if (imgGray.empty())
	{
		//g_pOP->LogError(nSocIndex, __FUNCTION__, "Image is empty, path = %s", copyFile.toStdString().c_str());
		return false;
	}

	cv::Mat imgRGB;
	cv::cvtColor(imgGray, imgRGB, cv::COLOR_GRAY2RGB);

	ImageProcessPara imgProcPara;
	imgProcPara.Init();
	imgProcPara.AdaptiveModel = 5;
	imgProcPara.DiffValue = -10;
	imgProcPara.ErosionFlag = 0;
	imgProcPara.MinMarkNum2 = 5;
	imgProcPara.MaxMarkNum2 = 150;
	imgProcPara.HeightWidthRatio2 = 0.5;
	imgProcPara.ROIStartX = stoi(m_VisionSetting["ROIStartX"]);
	imgProcPara.ROIStartY = stoi(m_VisionSetting["ROIStartY"]);
	imgProcPara.ROIEndX = stoi(m_VisionSetting["ROIEndX"]);
	imgProcPara.ROIEndY = stoi(m_VisionSetting["ROIEndY"]);
	//imgProcPara.ROIStartX = 310;
	//imgProcPara.ROIStartY = 1160;
	//imgProcPara.ROIEndX = 870;
	//imgProcPara.ROIEndY = 1640;

	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "ROI Value: StartX:%d, EndX:%d, StartY:%d, EndY:%d",
	///	imgProcPara.ROIStartX, imgProcPara.ROIEndX, imgProcPara.ROIStartY, imgProcPara.ROIEndY);

	float _degree = 0;
	cv::Point2f midPoint;
	MilDetecDegree(imgGray, imgRGB, imgProcPara, _degree, midPoint);

	midPointX = midPoint.x;
	midPointY = midPoint.y;

	//double offset = g_pINSP->m_StationVisionSetting.GetDouble("OFFSET_SOCKET" + QString::number(nSocIndex + 1), 0);
	double offset = stof(m_VisionSetting["OFFSET_SOCKET" + std::to_string(nSocIndex + 1)]);
	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Degree: %f, Offset:%f", _degree, offset);

	float tz = _degree - 90.0 + offset;
	degree = tz;
	if (_degree == -999)
	{
		if (bDebug)
		{
			std::string NewFile1 = copyFile;
			//NewFile1.replace("TZ0", "TZ" + std::to_string(-999));
			Jup::Replace(NewFile1, "TZ0", "TZ" + std::to_string(-999));
			//QFile::rename(copyFile, NewFile1);
			rename(copyFile.c_str(), NewFile1.c_str());
			std::string NewFile2 = NewFile1;
			//NewFile2.replace("Image1", "Image2");
			Jup::Replace(NewFile2, "Image1", "Image2");
			std::string bmpFilePath = NewFile2;
			imwrite(bmpFilePath.c_str(), imgRGB);
			outPath = NewFile2;
			degree = 0.0001;

			//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Debug Detec NG!!!, out path = %s", NewFile2.toStdString().c_str());
		}
		else
		{
			outPath.clear();
			degree = 0.0001;
			//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Detec NG!!!");
		}
		return false;
	}

	std::string NewFile1 = copyFile;
	//NewFile1.replace("TZ0", "TZ" + std::to_string(degree));
	Jup::Replace(NewFile1, "TZ0", "TZ" + std::to_string(degree));
	//QFile::rename(copyFile, NewFile1);
	rename(copyFile.c_str(), NewFile1.c_str());
	std::string NewFile2 = NewFile1;
	//NewFile2.replace("Image1", "Image2");
	//Jup::Replace(NewFile2, "Image1", "Image2");

	CTime time = CTime::GetCurrentTime();
	char buf[64];
	sprintf(buf, "%02d%02d%02d-%02d%02d%02d", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	std::string sreTime = buf;
	Jup::Replace(NewFile2, ".bmp", "_" + sreTime + "_OUTImage.bmp");

	imwrite(NewFile2.c_str(), imgRGB);
	outPath = NewFile2;
	return true;
}

std::string MilManager::VisionModelFindGetResult(std::string strFilePathImage, std::string& strFileOut, std::string strFilePathMMF, std::vector<PointXYA>& Results, bool save_result)
{
	MIL_ID GraphicList = 0;
	//生成GraID
	MgraAllocList(m_mil.milSystem, M_DEFAULT, &GraphicList);
	//绑定Gra
	MdispControl(m_mil.milDisplay, M_ASSOCIATED_GRAPHIC_LIST_ID, GraphicList);
	//设置颜色
	MgraColor(M_DEFAULT, M_COLOR_GREEN);
	//读取图片
	MIL_ID MilImage;
	MbufRestoreA(strFilePathImage, m_mil.milSystem, &MilImage);
	//计算结果
	MIL_ID MilImageOut;
	string sErr = "";
	sErr = visionManager.ExecuteModelFindGetResult(m_mil.milSystem, MilImage, MilImageOut, strFilePathMMF, Results, GraphicList);
	// 存图
	if (save_result)
	{
		std::string file = strFilePathImage;
		Jup::Replace(file, ".bmp", "_Result.jpg");
		strFileOut = file;
		MbufExport(file, M_JPEG_LOSSY, MilImageOut);
		// 异步保存图片
		//auto future = std::async(std::launch::async, &MilManager::saveMilImage, this, file, MilImageOut);
	}
	//释放资源
	MbufFree(MilImage);
	MbufFree(MilImageOut);
	MgraFree(GraphicList);
	return sErr;
}

std::string MilManager::VisionMETGetResultSpecial(std::string strFilePathMMf, std::string strFilePathMET, std::vector<PointXYA>& Results)
{
	//MIL_ID MilApplication,     /* Application identifier. */
	//	MilSystem,          /* System identifier.      */
	//	MilDisplay,        /* Display identifier.     */
	//	MilImage,
	//	MilModContext;
	////分配系统ID
	//MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem, &MilDisplay, M_NULL, M_NULL);

	MIL_ID GraphicList = 0;
	//生成GraID
	MgraAllocList(m_mil.milSystem, M_DEFAULT, &GraphicList);
	//绑定Gra
	MdispControl(m_mil.milDisplay, M_ASSOCIATED_GRAPHIC_LIST_ID, GraphicList);
	//设置颜色
	MgraColor(M_DEFAULT, M_COLOR_GREEN);
	string sImagePath1;
	//读取图片
	MIL_ID MilImage;
	MbufRestoreA(sImagePath1.data(), m_mil.milSystem, &MilImage);
	string strFilePath1;
	string strFilePath2;
	//获取Met结果序号
	vector<int> ResListIdx;
	ResListIdx.push_back(1);
	ResListIdx.push_back(2);
	//输入设置参数序号
	vector<int> MetSetIndexs;
	MetSetIndexs.push_back(1);
	MetSetIndexs.push_back(2);
	//ROI区域设置
	vector<MilRect> ROIs;
	ROIs.push_back(MilRect(1362, 612, 155, 97));
	ROIs.push_back(MilRect(1342, 1064, 220, 129));

	string sErr = "";
	sErr = visionManager.ExecuteMMFandMETGetResult_Special(m_mil.milSystem, MilImage, strFilePath1, strFilePath2, ResListIdx, ROIs, MetSetIndexs, Results, GraphicList);
	//MdispSelect(m_mil.milDisplay, MilImage);

	//MosGetch();
	return sErr;
}

void MilManager::loadParasFromFile(const char * file_name)
{
	m_IniParas = new JIniSettings(file_name);
	m_IniParas->ReadSection("STATION_VISION", m_VisionSetting);
}

void MilManager::saveMilImage(std::string strFilePath, MIL_ID MilImageOut)
{
	MbufExport(strFilePath, M_JPEG_LOSSY, MilImageOut);
	MbufFree(MilImageOut);
}
