#include "MilCaller.h"

#include "JError.h"
#include <Windows.h>
#include "JupCore.h"
#include "CSVReader.h"
#include <filesystem>
#include <future>
#include <thread>
#define Plugin_Method_Add(T, f) appendMethod(#f, transformMethod<T>(&T::f));
static JError s_error;

//#define TxThreshold 0.4
//#define TyThreshold 0.4

std::vector<std::string> m_TxResultA_X;
std::vector<std::string> m_TxResultA_Y;
std::vector<std::string> m_TxResultB_X;
std::vector<std::string> m_TxResultB_Y;
std::vector<std::string> m_TxResultC_X;
std::vector<std::string> m_TxResultC_Y;
std::vector<std::string> m_TyResultA_X;
std::vector<std::string> m_TyResultA_Y;
std::vector<std::string> m_TyResultB_X;
std::vector<std::string> m_TyResultB_Y;
std::vector<std::string> m_TyResultC_X;
std::vector<std::string> m_TyResultC_Y;
std::vector<std::string> m_TopresultDatas;
std::vector<std::string> m_ButtomresultDatas;
std::string csvFilePath;

MilCaller::MilCaller()
{
	m_pMil = MilManager::GetInstance();
}

MilCaller::~MilCaller()
{}

/*
	在该函数做特定的初始化操作，一般由平台调用该函数

	示例：默认调用父类接口的实现JupCaller::Initialize();
	根据当前插件的实际需要选择添加内容
*/
int MilCaller::Initialize()
{
	return JupCaller::Initialize();
}

/*
	统一在此注册所有测试项方法的函数

	示例：Plugin_Method_Add(MilCaller, Demo_msleep100);
	其中参数1：MilCaller为当前类的类名，参数2：Demo_msleep100为需要注册的函数名
*/
int MilCaller::RegisterMethod()
{
	Plugin_Method_Add(MilCaller, ResetData);
	Plugin_Method_Add(MilCaller, Demo_msleep100);
	Plugin_Method_Add(MilCaller, GetHikImageResult);
	Plugin_Method_Add(MilCaller, GetBottomImageResult);
	Plugin_Method_Add(MilCaller, GetBottomB2BImageResult);
	Plugin_Method_Add(MilCaller, GetTopImageResult);
	Plugin_Method_Add(MilCaller, GetTopImageDownDutResult);
	Plugin_Method_Add(MilCaller, GetHIKImageResult);
	Plugin_Method_Add(MilCaller, GetDVPImageResult);
	Plugin_Method_Add(MilCaller, SaveDOETestData);
	Plugin_Method_Add(MilCaller, SaveDOE2TestData);
	Plugin_Method_Add(MilCaller, SaveDOE3TestData);
	Plugin_Method_Add(MilCaller, WriteTestResultToCSV);
	Plugin_Method_Add(MilCaller, SaveCalibraData);
	return 0;
}

/*
	示例：
	如函数Demo_msleep100，内容自行添加；返回值为0表示没有错误，返回值非0表示有错误

	错误码的使用：
	1.在本cpp文件包含头文件：#include "ErrorCode.h"
	2.在函数中返回错误码：return ErrorCode::ERR_Init;

	如果想直接得到错误名以及错误提示（在函数Demo_msleep500Error中有范例）
	1.在本cpp文件定义静态变量：static ErrorCode s_error;
	2.在函数中使用下列方法
	获得错误名：			s_error.GetNameByCode(ErrorCode::ERR_Init);
	获得中文错误提示：	s_error.GetPromptByCode(ErrorCode::ERR_Init, JUP_ERROR_PROMPT_CN);
	获得英文错误提示：	s_error.GetPromptByCode(ErrorCode::ERR_Init, JUP_ERROR_PROMPT_EN);
*/
int MilCaller::Demo_msleep100(JupData & data)
{
	Sleep(10);
	return 0;
}

int MilCaller::ResetData(JupData & data)
{
	// 清空数据结构
	m_TxResultA_X.clear();
	m_TxResultA_Y.clear();
	m_TxResultB_X.clear();
	m_TxResultB_Y.clear();
	m_TxResultC_X.clear();
	m_TxResultC_Y.clear();
	m_TyResultA_X.clear();
	m_TyResultA_Y.clear();
	m_TyResultB_X.clear();
	m_TyResultB_Y.clear();
	m_TyResultC_X.clear();
	m_TyResultC_Y.clear();
	prePointX_Tx = 0.0;
	prePointY_Tx = 0.0;
	prePointX_Ty = 0.0;
	prePointY_Ty = 0.0;
	csvFilePath.clear();
	return 0;
}

void MilCaller::DealImage(std::string imageFile, std::vector<PointXYA> result, std::string camera, bool isSave)
{
	// 删除临时图片
	if (!isSave)
	{
		if (result.empty())
		{
			std::string newName = imageFile;
			Jup::Replace(newName, ".bmp", "Empty.bmp");
			if (std::filesystem::exists(imageFile))
				std::filesystem::rename(imageFile, newName);
			if (camera == "TX")
			{
				prePointX_Tx = 0.0;
				prePointY_Tx = 0.0;
			}
			else
			{
				prePointX_Ty = 0.0;
				prePointY_Ty = 0.0;
			}
		}
		else
		{
			SaveThresholdImage(imageFile, camera, result[0].X, result[0].Y);
			if (camera == "TX")
			{
				prePointX_Tx = result[0].X;
				prePointY_Tx = result[0].Y;
			}
			else
			{
				prePointX_Ty = result[0].X;
				prePointY_Ty = result[0].Y;
			}
		}
	}
}

std::string MilCaller::GetMMFName(std::string camera_name)
{
	std::string m_mmfPath;
	if (camera_name == "TX")
		m_mmfPath = m_mmfPathTx;
	else
		m_mmfPath = m_mmfPathTy;
	return m_mmfPath;
}

void MilCaller::AddResultToVector(std::string group, std::string camera_name, double point_x, double point_y)
{
	if (group == "A")
	{
		if (camera_name == "TX")
		{
			m_TxResultA_X.push_back(std::to_string(point_x));
			m_TxResultA_Y.push_back(std::to_string(point_y));
		}
		else
		{
			m_TyResultA_X.push_back(std::to_string(point_x));
			m_TyResultA_Y.push_back(std::to_string(point_y));
		}
	}
	else if (group == "B")
	{
		if (camera_name == "TX")
		{
			m_TxResultB_X.push_back(std::to_string(point_x));
			m_TxResultB_Y.push_back(std::to_string(point_y));
		}
		else
		{
			m_TyResultB_X.push_back(std::to_string(point_x));
			m_TyResultB_Y.push_back(std::to_string(point_y));
		}
	}
	else
	{
		if (camera_name == "TX")
		{
			m_TxResultC_X.push_back(std::to_string(point_x));
			m_TxResultC_Y.push_back(std::to_string(point_y));
		}
		else
		{
			m_TyResultC_X.push_back(std::to_string(point_x));
			m_TyResultC_Y.push_back(std::to_string(point_y));
		}
	}
}

void MilCaller::SaveThresholdImage(std::string image_file, std::string camera_name, double point_x, double point_y)
{
	// 比较偏差。大于阈值保存图片
	double preX;
	double preY;
	if (camera_name == "TX")
	{
		preX = prePointX_Tx;
		preY = prePointY_Tx;
	}
	else
	{
		preX = prePointX_Ty;
		preY = prePointY_Ty;
	}
	if (preX != 0.0 && preY != 0.0)
	{
		double m_TxThreshold = jCore->GlobalSettings().ReadDouble("AlphaDoe", "TxThreshold");
		double m_TyThreshold = jCore->GlobalSettings().ReadDouble("AlphaDoe", "TyThreshold");
		if ((abs(preX - point_x) > m_TxThreshold) || (abs(preY - point_y) > m_TyThreshold))
		{
			std::vector<std::string> file_path = Jup::Split(image_file, "/");
			std::string file_name = file_path.back();
			file_path.pop_back();

			static std::string folder;
			if (folder.empty())
			{
				folder = Jup::Join(file_path, "/") + "/OverThreshold";
				int flag = mkdir(folder.c_str());
				if (flag != 0)
				{
					// 创建失败
				}
			}
			std::string newName = folder + "/" + file_name;
			if (std::filesystem::exists(image_file))
				std::filesystem::rename(image_file, newName);
		}
	}
	DeleteTempImage(image_file);
}

int MilCaller::GetHikImageResult(JupData& data)
{
	bool isSave = data.GetInt("HikData", "SaveImage");
	std::vector<PointXYA> result;
	std::string imageFile = data.GetValue("HikData", "ImageFile");
	std::string imageResult;
	std::string current_camera = data.GetValue("HikData", "CurrentCamera");
	std::string m_mmfPath = GetMMFName(current_camera);
	// MIL计算结果
	std::string errStr = m_pMil->VisionModelFindGetResult(imageFile, imageResult, m_mmfPath, result, isSave);
	if (!errStr.empty())
	{
		// 报错
	}
	// 保存更新测试结果
	double pointX = 0.0;
	double pointY = 0.0;
	if (!result.empty())
	{
		pointX = result[0].X;
		pointY = result[0].Y;
	}
	std::string group = data.GetValue("HikData", "PosName").substr(0, 1);
	AddResultToVector(group, current_camera, pointX, pointY);
	// 临时图片文件删除/保存 (异步执行)
	auto future = std::async(std::launch::async, &MilCaller::DealImage, this, imageFile, result, current_camera, isSave);
	return 0;
}

int MilCaller::GetFindModeImageResult(JupData & data)
{
	std::string imageFile = data.GetValue("ImageData", "BottomImageFile");
	//std::string file_name = "C:\\Users\\CTOS\\Desktop\\TEST0802\\2024-08-05_10-45-09_991.bmp";
	std::string file_mmf = "C:\\Users\\CTOS\\Desktop\\TEST0802\\ping.mmf";
	std::vector<PointXYA> Result;
	std::string file_out, strStartTime_0;
	std::string errStr = m_pMil->VisionModelFindGetResult(imageFile, file_out, file_mmf, Result);

	strStartTime_0 = data.GetValue("MotionData", "StartTime_0");
	m_TopresultDatas.push_back(strStartTime_0);
	m_TopresultDatas.push_back("TOP");
	for (const auto value : Result)
	{
		m_TopresultDatas.push_back(std::to_string(value.X));
		m_TopresultDatas.push_back(std::to_string(value.Y));
		m_TopresultDatas.push_back(std::to_string(value.R));
	}
	m_TopresultDatas.push_back(file_out);
	return 0;
}

int MilCaller::WriteTestResultToCSV(JupData & data)
{
	int test_count = data.GetInt("HikData", "TestCount"); 
	std::string test_startTime = data.GetValue("HikData", "TestStartTime");
	std::string test_temp = data.GetValue("Serial", "CurrentTemp");
	// 按格式拼接结果
	std::vector<std::string> resultDatas;
	resultDatas.push_back(std::to_string(test_count));
	resultDatas.push_back(test_startTime);
	resultDatas.push_back(test_temp);
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TxResultA_X.begin()), std::make_move_iterator(m_TxResultA_X.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TxResultA_Y.begin()), std::make_move_iterator(m_TxResultA_Y.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TxResultB_X.begin()), std::make_move_iterator(m_TxResultB_X.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TxResultB_Y.begin()), std::make_move_iterator(m_TxResultB_Y.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TxResultC_X.begin()), std::make_move_iterator(m_TxResultC_X.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TxResultC_Y.begin()), std::make_move_iterator(m_TxResultC_Y.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TyResultA_X.begin()), std::make_move_iterator(m_TyResultA_X.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TyResultA_Y.begin()), std::make_move_iterator(m_TyResultA_Y.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TyResultB_X.begin()), std::make_move_iterator(m_TyResultB_X.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TyResultB_Y.begin()), std::make_move_iterator(m_TyResultB_Y.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TyResultC_X.begin()), std::make_move_iterator(m_TyResultC_X.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TyResultC_Y.begin()), std::make_move_iterator(m_TyResultC_Y.end()));
	// 写入文件
	std::string imageFile = data.GetValue("HikData", "ImageFile");
	if (!WriteDataToCSV(imageFile, m_csv_head, resultDatas))
	{
		// 报错
	}
	// 清空数据结构
	m_TxResultA_X.clear();
	m_TxResultA_Y.clear();
	m_TxResultB_X.clear();
	m_TxResultB_Y.clear();
	m_TxResultC_X.clear();
	m_TxResultC_Y.clear();
	m_TyResultA_X.clear();
	m_TyResultA_Y.clear();
	m_TyResultB_X.clear();
	m_TyResultB_Y.clear();
	m_TyResultC_X.clear();
	m_TyResultC_Y.clear();
	return 0;
}

int MilCaller::GetBottomImageResult(JupData& data)
{
	m_ButtomresultDatas.clear();
	data.SetValue("MILData", "BarCode", "");
	bool isSave = data.GetInt("HikData", "SaveImage");
	std::string imageFile = data.GetValue("HikData", "BottomImageFile");
	std::string m_mcoPathBarCode = "./Config/DataMatrix.mco";
	std::string m_mmfPathBottom = "./Config/BOTTOM.mmf";
	std::string m_metPathBottom = "./Config/BOTTOM.met";
	std::string m_mmfPathCircle = "./Config/Circle.mmf";
	std::vector<PointXYA> result;
	std::string strBarCode, strFileOut, strStartTime_0;
	std::vector<MilRect> ROIs;	
	ROIs.push_back(MilRect(2945, 798, 1230, 1230));		//图片左上销钉
	ROIs.push_back(MilRect(4025, 793, 1010, 1060));		//图片右上销钉
	ROIs.push_back(MilRect(4025, 3235, 1050, 1150));	//图片右下销钉
	ROIs.push_back(MilRect(3117, 3305, 1045, 1045));	//图片左下销钉
	MilMetIndex metIndex(0, 11, 11, 12);
	float fdistance = 0.0;
	std::string errStr = m_pMil->VisionBottomCameraResult(imageFile, strFileOut, m_mcoPathBarCode, m_mmfPathBottom, m_metPathBottom, m_mmfPathCircle
														, metIndex, ROIs, result, fdistance, strBarCode, isSave);
	
	data.SetValue("MILData", "BarCode", strBarCode);
	strStartTime_0 = data.GetValue("MotionData", "StartTime_0");
	m_ButtomresultDatas.push_back(strStartTime_0);
	m_ButtomresultDatas.push_back(strBarCode);
	m_ButtomresultDatas.push_back("Bottom");
	for (const auto value : result)
	{
		m_ButtomresultDatas.push_back(std::to_string(value.X));
		m_ButtomresultDatas.push_back(std::to_string(value.Y));
		m_ButtomresultDatas.push_back(std::to_string(value.R));
	}
	m_ButtomresultDatas.push_back(std::to_string(fdistance));
	if (!errStr.empty())
	{
		return 0;
		// 报错
		//return -1;
	}
	return 0;
}

int MilCaller::GetBottomB2BImageResult(JupData & data)
{
	//m_TopresultDatas.clear();
	std::string imageFile = "D:/SW/git_lrt/Sphinx-Alpha - Test/_OUT/2SoftwareOnce.bmp";
	std::string m_mmfPathButtomB2B = "C:/Users/CTOS/Desktop/TEST0807/B2B.mmf";
	std::vector<PointXYA> result;
	std::string strBarCode, strFileOut, strStartTime_0;

	std::string errStr = m_pMil->VisionBottomB2BCameraResult(imageFile,strFileOut, m_mmfPathButtomB2B,result);
	std::string strInfo;
	strInfo = "B2B Pos X: " + std::to_string(result[0].X);
	jCore->Logger("MilPlugin.dll").LogInfo(__FUNCTIONT__, strInfo);
	strInfo = "B2B Pos Y: " + std::to_string(result[0].Y);
	jCore->Logger("MilPlugin.dll").LogInfo(__FUNCTIONT__, strInfo);
	strInfo = "B2B Pos Angle: " + std::to_string(result[0].R);
	jCore->Logger("MilPlugin.dll").LogInfo(__FUNCTIONT__, strInfo);

	return 0;
}

int MilCaller::GetTopImageDownDutResult(JupData & data)
{
	//m_TopresultDatas.clear();
	std::string imageFile = data.GetValue("ImageData", "TopImageFile");
	std::string m_mmfPathTopDownDut = "C:\\Users\\CTOS\\Desktop\\TEST0807\\socket.mmf";
	std::vector<PointXYA> result;
	std::string strBarCode, strFileOut, strStartTime_0;
	std::vector<MilRect> ROIs;
	ROIs.push_back(MilRect(52, 238, 219, 209));		//图片上销钉
	ROIs.push_back(MilRect(56, 466, 203, 213));		//图片下销钉
	std::string errStr = m_pMil->VisionTopDownSocketCameraResult(imageFile, strFileOut, m_mmfPathTopDownDut, ROIs, result);

	//存图路径的设置在DvpCaller
	for (const auto value : result)
	{
		m_TopresultDatas.push_back(std::to_string(value.X));
		m_TopresultDatas.push_back(std::to_string(value.Y));
		m_TopresultDatas.push_back(std::to_string(value.R));
	}

	return 0;
}

int MilCaller::GetTopImageResult(JupData& data)
{
	m_TopresultDatas.clear();
	bool isSave = data.GetInt("HikData", "SaveImage");
	std::string imageFile = data.GetValue("ImageData", "TopImageFile");
	//std::string m_mmfPathTop = "./Config/B2B.mmf";
	std::string m_mmfPathTop = "C:/Users/CTOS/Desktop/TEST0807/ping.mmf";
	//std::string m_metPathTop = "./Config/B2B.met";
	std::string m_metPathTop = "";
	//std::string m_mmfPathCircle = "./Config/B2B_Circle.mmf";
	std::string m_mmfPathCircle = "C:\\Users\\CTOS\\Desktop\\TEST0807\\socket.mmf";
	std::vector<PointXYA> result;
	std::string strBarCode, strFileOut, strStartTime_0;
	std::vector<MilRect> ROIs;
	ROIs.push_back(MilRect(11, 286, 345, 360));		//图片上销钉
	ROIs.push_back(MilRect(11, 625, 410, 500));		//图片下销钉
	MilMetIndex metIndex(0, 11, 11, 12);
	float fdistance = 0.0, fSocketAngle = 0.0;
	//std::string imagepath = "";
	//if (!GetOpenFileFolderName(imagepath))
	//{
	//	return -1;
	//}
	//std::vector<std::string> vertor_Image;
	//vertor_Image.clear();
	//try
	//{
	//	if (std::filesystem::exists(imagepath) && std::filesystem::is_directory(imagepath))
	//	{
	//		for (const auto& entry : std::filesystem::directory_iterator(imagepath))
	//		{
	//			if (std::filesystem::is_regular_file(entry.status()))
	//			{
	//				vertor_Image.push_back(entry.path().string());
	//			}
	//		}
	//	}
	//	else
	//	{
	//		return -1;
	//	}
	//}
	//catch (const std::filesystem::filesystem_error& e)
	//{
	//	return -1;
	//}
	//for (const auto image : vertor_Image)
	//{
		std::string errStr = m_pMil->VisionTopCameraResult(imageFile, strFileOut, m_mmfPathTop, m_metPathTop, m_mmfPathCircle, metIndex, ROIs, result, fdistance, fSocketAngle, isSave);
		if (!errStr.empty())
		{
			// 报错
			return -1;
		}
	//}
	strBarCode = data.GetValue("MILData", "BarCode");
	strStartTime_0 = data.GetValue("MotionData", "StartTime_0");
	m_TopresultDatas.push_back(strStartTime_0);
	m_TopresultDatas.push_back(strBarCode);
	m_TopresultDatas.push_back("Top");
	for (const auto value : result)
	{
		m_TopresultDatas.push_back(std::to_string(value.X));
		m_TopresultDatas.push_back(std::to_string(value.Y));
		m_TopresultDatas.push_back(std::to_string(value.R));
	}
	m_TopresultDatas.push_back(std::to_string(fdistance));
	m_TopresultDatas.push_back(std::to_string(fSocketAngle));

	std::string strInfo;
	strInfo = "fdistance: " + std::to_string(fdistance);
	jCore->Logger("MilPlugin.dll").LogInfo(__FUNCTION__, strInfo);
	strInfo = "fSocketAngle: " + std::to_string(fSocketAngle);
	jCore->Logger("MilPlugin.dll").LogInfo(__FUNCTION__, strInfo);
	return 0;
}

int MilCaller::GetHIKImageResult(JupData& data)
{
	m_ButtomresultDatas.clear();
	std::string imageFile = data.GetValue("HikData", "TopImageFile");
	std::string m_metPathTop = "./Config/HIK.met";
	std::vector<PointXYA> result;
	std::string strFileOut, strStartTime_0;
	
	std::string errStr = m_pMil->VisionMETGetResult(imageFile, strFileOut, m_metPathTop, result, false);
	if (!errStr.empty())
	{
		// 报错
		return -1;
	}
	//}
	strStartTime_0 = data.GetValue("MotionData", "StartTime_0");
	m_ButtomresultDatas.push_back(strStartTime_0);
	for (const auto value : result)
	{
		m_ButtomresultDatas.push_back(std::to_string(value.X));
		m_ButtomresultDatas.push_back(std::to_string(value.Y));
	}
	return 0;
}

int MilCaller::GetDVPImageResult(JupData& data)
{
	m_TopresultDatas.clear();
	std::string imageFile = data.GetValue("ImageData", "TopImageFile");
	std::string m_metPathTop = "./Config/DVP.met";
	std::vector<PointXYA> result;
	std::string strFileOut, strStartTime_0;

	std::string errStr = m_pMil->VisionMETGetResult(imageFile, strFileOut, m_metPathTop, result, false);
	if (!errStr.empty())
	{
		// 报错
		return -1;
	}
	//}
	strStartTime_0 = data.GetValue("MotionData", "StartTime_0");
	m_TopresultDatas.push_back(strStartTime_0);
	for (const auto value : result)
	{
		m_TopresultDatas.push_back(std::to_string(value.X));
		m_TopresultDatas.push_back(std::to_string(value.Y));
	}
	return 0;
}

bool MilCaller::GetOpenFileFolderName(std::string &strImagePath)
{
	TCHAR szBuffer[MAX_PATH] = { 0 };
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = _T("从下面选文件夹目录:");
	bi.ulFlags = BIF_RETURNFSANCESTORS;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (NULL == idl)
	{
		return false;
	}
	SHGetPathFromIDList(idl, szBuffer);
	strImagePath = szBuffer;
	return true;
}

int MilCaller::SaveDOETestData(JupData& data)
{
	std::string imageFile = data.GetValue("HikData", "TopImageFile");
	std::string strBarCode = data.GetValue("MILData", "BarCode");
	std::string strStartTime_3 = data.GetValue("MotionData", "StartTime_3");
	std::string strStartTime_1 = data.GetValue("MotionData", "StartTime_1"); 
	std::string path_bottom_pcs = imageFile.substr(0, imageFile.find_last_of("/")) + "/bottom_result.csv";
	std::string path_top_pcs = imageFile.substr(0, imageFile.find_last_of("/")) + "/top_result.csv";

	std::vector<std::string> TopresultDatas;
	for (int i = 0; i < m_TopresultDatas.size(); i++)
	{
		if (i == 1)
		{
			TopresultDatas.push_back(strBarCode);
		}
		else
		{
			TopresultDatas.push_back(m_TopresultDatas.at(i));
		}
	}
	if (!WriteDoeTestDataToCSV(path_top_pcs, m_top_csv_head, TopresultDatas))
	{
		return -2;
	}
	if (!WriteDoeTestDataToCSV(path_bottom_pcs, m_bottom_csv_head, m_ButtomresultDatas))
	{
		return -3;
	}
	std::string path_top = "D:/AlphaDoeImage/" + strStartTime_1 + "/Top.csv";
	std::string path_bottom = "D:/AlphaDoeImage/" + strStartTime_1 + "/Bottom.csv";
	if (!WriteDoeTestDataToCSV(path_top, m_top_csv_head, TopresultDatas))
	{
		return -4;
	}
	if (!WriteDoeTestDataToCSV(path_bottom, m_bottom_csv_head, m_ButtomresultDatas))
	{
		return -5;
	}

	std::string path_old = imageFile.substr(0, imageFile.find_last_of("/"));
	std::string path_new = imageFile.substr(0, path_old.find_last_of("/"));
	path_new += "/";
	path_new += strBarCode;
	path_new += "_";
	path_new += strStartTime_3;
	if (!std::filesystem::exists(path_new))
	{
		std::filesystem::create_directory(path_new);
	}
	try 
	{
		int exposureTime = jCore->GlobalSettings().ReadInt("PnpDoe", "DelayTime_TestEnd");
		Sleep(exposureTime);
		//std::filesystem::rename(path_old, path_new);
		for (const auto& entry : std::filesystem::directory_iterator(path_old)) {
			const std::filesystem::path file_path = entry.path();
			if (std::filesystem::is_regular_file(file_path)) {
				std::filesystem::copy(file_path, path_new / file_path.filename(), std::filesystem::copy_options::update_existing);
				std::filesystem::remove(file_path);
			}
		}
	}
	catch (const std::filesystem::filesystem_error& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}
	return 0;
}

int MilCaller::SaveDOE2TestData(JupData& data)
{
	std::string imageFile = data.GetValue("HikData", "TopImageFile");
	std::string imageFile2 = data.GetValue("ImageData", "TopImageFile");
	std::string strBarCode = data.GetValue("MILData", "BarCode");
	std::string strStartTime_3 = data.GetValue("MotionData", "StartTime_3");
	std::string strStartTime_1 = data.GetValue("MotionData", "StartTime_1");
	std::string Temp = data.GetValue("Serial", "CurrentTemp1");
	std::string path = imageFile.substr(0, imageFile.find_last_of("/")) + "/result.csv";

	std::vector<std::string> resultDatas;	
	for (int i = 0; i < m_ButtomresultDatas.size(); i++)
	{
		resultDatas.push_back(m_ButtomresultDatas.at(i));
	}
	for (int i = 1; i < m_TopresultDatas.size(); i++)
	{
		resultDatas.push_back(m_TopresultDatas.at(i));
	}
	resultDatas.push_back(Temp);
	if (!WriteDoeTestDataToCSV(path, m_doe_csv_head, resultDatas))
	{
		return -2;
	}

	if (std::filesystem::exists(imageFile))
	{
		std::filesystem::remove(imageFile);
	}
	if (std::filesystem::exists(imageFile2))
	{
		std::filesystem::remove(imageFile2);
	}
	return 0;
}

int MilCaller::SaveDOE3TestData(JupData & data)
{
	std::string strStartTime_1 = data.GetValue("MotionData", "StartTime_1");
	std::string path_top = "D:/AlphaDoeImage/" + strStartTime_1 + "/Top.csv";
	std::string path_bottom = "D:/AlphaDoeImage/" + strStartTime_1 + "/Bottom.csv";
	if (!WriteDoeTestDataToCSV(path_top, m_top2_csv_head, m_TopresultDatas))
	{
		return -4;
	}
	//if (!WriteDoeTestDataToCSV(path_bottom, m_bottom_csv_head, m_ButtomresultDatas))
	//{
	//	return -5;
	//}
	return 0;
}

int MilCaller::SaveCalibraData(JupData & data)
{
	int test_count = data.GetInt("HikData", "TestCount");
	std::string test_startTime = data.GetValue("HikData", "TestStartTime");
	std::string test_PnpCFOV_X = std::to_string(data.GetDouble("JupMotion", "PnpAxisXPos_font"));
	std::string test_PnpCFOV_Y = std::to_string(data.GetDouble("JupMotion", "PnpAxisYPos_font"));

	//....其他的一些测试数据

	// 按格式拼接结果
	std::vector<std::string> resultDatas;
	resultDatas.push_back(std::to_string(test_count));
	resultDatas.push_back(test_startTime);
	resultDatas.push_back(test_PnpCFOV_X);
	resultDatas.push_back(test_PnpCFOV_Y);

	// 写入文件
	std::string strStartTime_1 = data.GetValue("MotionData", "StartTime_1");
	std::string path_Calibra = "D:/AlphaDoeImage/" + strStartTime_1 + "/TopVision.csv";
	if (!WriteDoeTestDataToCSV(path_Calibra, m_calibra_head, resultDatas))
	{
		return -1;
	}

	return 0;
}

bool MilCaller::WriteDataToCSV(std::string imageInput, std::vector<std::string> heads, std::vector<std::string> datas)
{
	if (csvFilePath.empty())
	{		
		std::string csvFileName = imageInput;
		std::vector<std::string> file_path = Jup::Split(csvFileName, "/");
		file_path.pop_back();
		file_path.pop_back();
		csvFileName = Jup::Join(file_path, "/") + "/" + "DoeResult_" + Jup::GetLocalTime(2) + ".csv";
		csvFilePath = csvFileName;

		struct stat buffer;
		if (stat(csvFileName.c_str(), &buffer) == 0)
		{
			return false;
		}
		else
		{
			CSVReader m_reader(csvFileName);
			m_reader.addRow(heads);
			m_reader.writeToFile();
		}
	}
	if (!csvFilePath.empty())
	{
		CSVReader m_reader(csvFilePath);
		m_reader.addRow(datas);
		m_reader.writeToFile();
	}
	return true;
}

bool MilCaller::WriteDoeTestDataToCSV(std::string path, std::vector<std::string> heads, std::vector<std::string> datas)
{
	if (!std::filesystem::exists(path))
	{
		CSVReader m_reader(path);
		m_reader.addRow(heads);
		m_reader.writeToFile();
	}

	CSVReader m_reader(path);
	m_reader.addRow(datas);
	m_reader.writeToFile();

	return true;
}

bool MilCaller::DeleteTempImage(std::string image)
{
	if (std::filesystem::exists(image)) {
		if (std::remove(image.c_str()) != 0) {
			return false;
		}
	}
	return true;
}