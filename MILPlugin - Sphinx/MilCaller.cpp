#include "MilCaller.h"

#include "JError.h"
//#include <Windows.h>
#include "JupCore.h"
#include "CSVReader.h"
#include <filesystem>
#include <future>
#include "CameraDILManager.h"

#define Plugin_Method_Add(T, f) appendMethod(#f, transformMethod<T>(&T::f));
static JError s_error;

double preA1PointX_Tx = 0.0;
double preA1PointY_Tx = 0.0;
double preA1PointX_Ty = 0.0;
double preA1PointY_Ty = 0.0;
double preA2PointX_Tx = 0.0;
double preA2PointY_Tx = 0.0;
double preA2PointX_Ty = 0.0;
double preA2PointY_Ty = 0.0;
double preA3PointX_Tx = 0.0;
double preA3PointY_Tx = 0.0;
double preA3PointX_Ty = 0.0;
double preA3PointY_Ty = 0.0;
double preA4PointX_Tx = 0.0;
double preA4PointY_Tx = 0.0;
double preA4PointX_Ty = 0.0;
double preA4PointY_Ty = 0.0;
double preA5PointX_Tx = 0.0;
double preA5PointY_Tx = 0.0;
double preA5PointX_Ty = 0.0;
double preA5PointY_Ty = 0.0;
double preA6PointX_Tx = 0.0;
double preA6PointY_Tx = 0.0;
double preA6PointX_Ty = 0.0;
double preA6PointY_Ty = 0.0;
double preA7PointX_Tx = 0.0;
double preA7PointY_Tx = 0.0;
double preA7PointX_Ty = 0.0;
double preA7PointY_Ty = 0.0;

double preB1PointX_Tx = 0.0;
double preB1PointY_Tx = 0.0;
double preB1PointX_Ty = 0.0;
double preB1PointY_Ty = 0.0;
double preB2PointX_Tx = 0.0;
double preB2PointY_Tx = 0.0;
double preB2PointX_Ty = 0.0;
double preB2PointY_Ty = 0.0;
double preB3PointX_Tx = 0.0;
double preB3PointY_Tx = 0.0;
double preB3PointX_Ty = 0.0;
double preB3PointY_Ty = 0.0;
double preB4PointX_Tx = 0.0;
double preB4PointY_Tx = 0.0;
double preB4PointX_Ty = 0.0;
double preB4PointY_Ty = 0.0;
double preB5PointX_Tx = 0.0;
double preB5PointY_Tx = 0.0;
double preB5PointX_Ty = 0.0;
double preB5PointY_Ty = 0.0;
double preB6PointX_Tx = 0.0;
double preB6PointY_Tx = 0.0;
double preB6PointX_Ty = 0.0;
double preB6PointY_Ty = 0.0;
double preB7PointX_Tx = 0.0;
double preB7PointY_Tx = 0.0;
double preB7PointX_Ty = 0.0;
double preB7PointY_Ty = 0.0;

double preC1PointX_Tx = 0.0;
double preC1PointY_Tx = 0.0;
double preC1PointX_Ty = 0.0;
double preC1PointY_Ty = 0.0;
double preC2PointX_Tx = 0.0;
double preC2PointY_Tx = 0.0;
double preC2PointX_Ty = 0.0;
double preC2PointY_Ty = 0.0;
double preC3PointX_Tx = 0.0;
double preC3PointY_Tx = 0.0;
double preC3PointX_Ty = 0.0;
double preC3PointY_Ty = 0.0;
double preC4PointX_Tx = 0.0;
double preC4PointY_Tx = 0.0;
double preC4PointX_Ty = 0.0;
double preC4PointY_Ty = 0.0;
double preC5PointX_Tx = 0.0;
double preC5PointY_Tx = 0.0;
double preC5PointX_Ty = 0.0;
double preC5PointY_Ty = 0.0;
double preC6PointX_Tx = 0.0;
double preC6PointY_Tx = 0.0;
double preC6PointX_Ty = 0.0;
double preC6PointY_Ty = 0.0;
double preC7PointX_Tx = 0.0;
double preC7PointY_Tx = 0.0;
double preC7PointX_Ty = 0.0;
double preC7PointY_Ty = 0.0;

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
std::string csvFilePath;
std::string threshold_folder;

MilCaller::MilCaller()
{
	m_pMil = MilManager::GetInstance();
	m_dil_camera = CameraDILManager::GetInstance();
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
	Plugin_Method_Add(MilCaller, WriteTestResultToCSV);

	Plugin_Method_Add(MilCaller, OpenDILCamera);
	Plugin_Method_Add(MilCaller, SetDILCameraParas);
	Plugin_Method_Add(MilCaller, SetDotParas);
	Plugin_Method_Add(MilCaller, SetFloodParas);
	Plugin_Method_Add(MilCaller, WaitTriggerGetImage);

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
	csvFilePath.clear();
	threshold_folder.clear();
	preA1PointX_Tx = 0.0;
	preA1PointY_Tx = 0.0;
	preA1PointX_Ty = 0.0;
	preA1PointY_Ty = 0.0;
	preA2PointX_Tx = 0.0;
	preA2PointY_Tx = 0.0;
	preA2PointX_Ty = 0.0;
	preA2PointY_Ty = 0.0;
	preA3PointX_Tx = 0.0;
	preA3PointY_Tx = 0.0;
	preA3PointX_Ty = 0.0;
	preA3PointY_Ty = 0.0;
	preA4PointX_Tx = 0.0;
	preA4PointY_Tx = 0.0;
	preA4PointX_Ty = 0.0;
	preA4PointY_Ty = 0.0;
	preA5PointX_Tx = 0.0;
	preA5PointY_Tx = 0.0;
	preA5PointX_Ty = 0.0;
	preA5PointY_Ty = 0.0;
	preA6PointX_Tx = 0.0;
	preA6PointY_Tx = 0.0;
	preA6PointX_Ty = 0.0;
	preA6PointY_Ty = 0.0;
	preA7PointX_Tx = 0.0;
	preA7PointY_Tx = 0.0;
	preA7PointX_Ty = 0.0;
	preA7PointY_Ty = 0.0;

	preB1PointX_Tx = 0.0;
	preB1PointY_Tx = 0.0;
	preB1PointX_Ty = 0.0;
	preB1PointY_Ty = 0.0;
	preB2PointX_Tx = 0.0;
	preB2PointY_Tx = 0.0;
	preB2PointX_Ty = 0.0;
	preB2PointY_Ty = 0.0;
	preB3PointX_Tx = 0.0;
	preB3PointY_Tx = 0.0;
	preB3PointX_Ty = 0.0;
	preB3PointY_Ty = 0.0;
	preB4PointX_Tx = 0.0;
	preB4PointY_Tx = 0.0;
	preB4PointX_Ty = 0.0;
	preB4PointY_Ty = 0.0;
	preB5PointX_Tx = 0.0;
	preB5PointY_Tx = 0.0;
	preB5PointX_Ty = 0.0;
	preB5PointY_Ty = 0.0;
	preB6PointX_Tx = 0.0;
	preB6PointY_Tx = 0.0;
	preB6PointX_Ty = 0.0;
	preB6PointY_Ty = 0.0;
	preB7PointX_Tx = 0.0;
	preB7PointY_Tx = 0.0;
	preB7PointX_Ty = 0.0;
	preB7PointY_Ty = 0.0;

	preC1PointX_Tx = 0.0;
	preC1PointY_Tx = 0.0;
	preC1PointX_Ty = 0.0;
	preC1PointY_Ty = 0.0;
	preC2PointX_Tx = 0.0;
	preC2PointY_Tx = 0.0;
	preC2PointX_Ty = 0.0;
	preC2PointY_Ty = 0.0;
	preC3PointX_Tx = 0.0;
	preC3PointY_Tx = 0.0;
	preC3PointX_Ty = 0.0;
	preC3PointY_Ty = 0.0;
	preC4PointX_Tx = 0.0;
	preC4PointY_Tx = 0.0;
	preC4PointX_Ty = 0.0;
	preC4PointY_Ty = 0.0;
	preC5PointX_Tx = 0.0;
	preC5PointY_Tx = 0.0;
	preC5PointX_Ty = 0.0;
	preC5PointY_Ty = 0.0;
	preC6PointX_Tx = 0.0;
	preC6PointY_Tx = 0.0;
	preC6PointX_Ty = 0.0;
	preC6PointY_Ty = 0.0;
	preC7PointX_Tx = 0.0;
	preC7PointY_Tx = 0.0;
	preC7PointX_Ty = 0.0;
	preC7PointY_Ty = 0.0;
	return 0;
}

void MilCaller::DealImage(std::string imageFile, std::vector<PointXYA> result, std::string camera, std::string pos_name, bool isSave)
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
			//RecordPrePosValue(camera, pos_name, 0.0, 0.0);
		}
		else
		{
			SaveThresholdImage(imageFile, camera, pos_name, result[0].X, result[0].Y);
			//RecordPrePosValue(camera, pos_name, result[0].X, result[0].Y);
		}
	}
	if (result.empty())
		RecordPrePosValue(camera, pos_name, 0.0, 0.0);
	else
		RecordPrePosValue(camera, pos_name, result[0].X, result[0].Y);
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

void MilCaller::SaveThresholdImage(std::string image_file, std::string camera_name, std::string pos_name, double point_x, double point_y)
{
	// 比较偏差。大于阈值保存图片
	double preX = 0.0;
	double preY = 0.0;
	GetPrePosValue(camera_name, pos_name, preX, preY);
	if (preX != 0.0 && preY != 0.0)
	{
		double m_TxThreshold = jCore->GlobalSettings().ReadDouble("AlphaDoe", "TxThreshold");
		double m_TyThreshold = jCore->GlobalSettings().ReadDouble("AlphaDoe", "TyThreshold");
		if ((abs(preX - point_x) > m_TxThreshold) || (abs(preY - point_y) > m_TyThreshold))
		{
			std::vector<std::string> file_path = Jup::Split(image_file, "/");
			std::string file_name = file_path.back();
			file_path.pop_back();

			if (threshold_folder.empty())
			{
				threshold_folder = Jup::Join(file_path, "/") + "/OverThreshold";
				int flag = mkdir(threshold_folder.c_str());
				if (flag != 0)
				{
					// 创建失败
					char log[256] = "";
					sprintf(log, "Create folder: %s fail!", threshold_folder);
					PluginWriteLog(JLogLevel::Warn, __FUNCTION__, log);
				}
			}
			std::string newName = threshold_folder + "/" + file_name;
			if (std::filesystem::exists(image_file))
				std::filesystem::rename(image_file, newName);
		}
	}
	DeleteTempImage(image_file);
}

bool MilCaller::RecordPrePosValue(std::string camera_name, std::string pos_name, double point_x, double point_y)
{
	if (pos_name == "A1")
	{
		if (camera_name == "TX")
		{
			preA1PointX_Tx = point_x;
			preA1PointY_Tx = point_y;
		}
		else
		{
			preA1PointX_Ty = point_x;
			preA1PointY_Ty = point_y;
		}
	}
	else if (pos_name == "A2")
	{
		if (camera_name == "TX")
		{
			preA2PointX_Tx = point_x;
			preA2PointY_Tx = point_y;
		}
		else
		{
			preA2PointX_Ty = point_x;
			preA2PointY_Ty = point_y;
		}
	}
	else if (pos_name == "A3")
	{
		if (camera_name == "TX")
		{
			preA3PointX_Tx = point_x;
			preA3PointY_Tx = point_y;
		}
		else
		{
			preA3PointX_Ty = point_x;
			preA3PointY_Ty = point_y;
		}
	}
	else if (pos_name == "A4")
	{
		if (camera_name == "TX")
		{
			preA4PointX_Tx = point_x;
			preA4PointY_Tx = point_y;
		}
		else
		{
			preA4PointX_Ty = point_x;
			preA4PointY_Ty = point_y;
		}
	}
	else if (pos_name == "A4")
	{
		if (camera_name == "TX")
		{
			preA4PointX_Tx = point_x;
			preA4PointY_Tx = point_y;
		}
		else
		{
			preA4PointX_Ty = point_x;
			preA4PointY_Ty = point_y;
		}
	}
	else if (pos_name == "A5")
	{
		if (camera_name == "TX")
		{
			preA5PointX_Tx = point_x;
			preA5PointY_Tx = point_y;
		}
		else
		{
			preA5PointX_Ty = point_x;
			preA5PointY_Ty = point_y;
		}
	}
	else if (pos_name == "A6")
	{
		if (camera_name == "TX")
		{
			preA6PointX_Tx = point_x;
			preA6PointY_Tx = point_y;
		}
		else
		{
			preA6PointX_Ty = point_x;
			preA6PointY_Ty = point_y;
		}
	}
	else if (pos_name == "A7")
	{
		if (camera_name == "TX")
		{
			preA7PointX_Tx = point_x;
			preA7PointY_Tx = point_y;
		}
		else
		{
			preA7PointX_Ty = point_x;
			preA7PointY_Ty = point_y;
		}
	}
	else if (pos_name == "B1")
	{
		if (camera_name == "TX")
		{
			preB1PointX_Tx = point_x;
			preB1PointY_Tx = point_y;
		}
		else
		{
			preB1PointX_Ty = point_x;
			preB1PointY_Ty = point_y;
		}
	}
	else if (pos_name == "B2")
	{
		if (camera_name == "TX")
		{
			preB2PointX_Tx = point_x;
			preB2PointY_Tx = point_y;
		}
		else
		{
			preB2PointX_Ty = point_x;
			preB2PointY_Ty = point_y;
		}
	}
	else if (pos_name == "B3")
	{
		if (camera_name == "TX")
		{
			preB3PointX_Tx = point_x;
			preB3PointY_Tx = point_y;
		}
		else
		{
			preB3PointX_Ty = point_x;
			preB3PointY_Ty = point_y;
		}
	}
	else if (pos_name == "B4")
	{
		if (camera_name == "TX")
		{
			preB4PointX_Tx = point_x;
			preB4PointY_Tx = point_y;
		}
		else
		{
			preB4PointX_Ty = point_x;
			preB4PointY_Ty = point_y;
		}
	}
	else if (pos_name == "B4")
	{
		if (camera_name == "TX")
		{
			preB4PointX_Tx = point_x;
			preB4PointY_Tx = point_y;
		}
		else
		{
			preB4PointX_Ty = point_x;
			preB4PointY_Ty = point_y;
		}
	}
	else if (pos_name == "B5")
	{
		if (camera_name == "TX")
		{
			preB5PointX_Tx = point_x;
			preB5PointY_Tx = point_y;
		}
		else
		{
			preB5PointX_Ty = point_x;
			preB5PointY_Ty = point_y;
		}
	}
	else if (pos_name == "B6")
	{
		if (camera_name == "TX")
		{
			preB6PointX_Tx = point_x;
			preB6PointY_Tx = point_y;
		}
		else
		{
			preB6PointX_Ty = point_x;
			preB6PointY_Ty = point_y;
		}
	}
	else if (pos_name == "B7")
	{
		if (camera_name == "TX")
		{
			preB7PointX_Tx = point_x;
			preB7PointY_Tx = point_y;
		}
		else
		{
			preB7PointX_Ty = point_x;
			preB7PointY_Ty = point_y;
		}
	}
	else if (pos_name == "C1")
	{
		if (camera_name == "TX")
		{
			preC1PointX_Tx = point_x;
			preC1PointY_Tx = point_y;
		}
		else
		{
			preC1PointX_Ty = point_x;
			preC1PointY_Ty = point_y;
		}
	}
	else if (pos_name == "C2")
	{
		if (camera_name == "TX")
		{
			preC2PointX_Tx = point_x;
			preC2PointY_Tx = point_y;
		}
		else
		{
			preC2PointX_Ty = point_x;
			preC2PointY_Ty = point_y;
		}
	}
	else if (pos_name == "C3")
	{
		if (camera_name == "TX")
		{
			preC3PointX_Tx = point_x;
			preC3PointY_Tx = point_y;
		}
		else
		{
			preC3PointX_Ty = point_x;
			preC3PointY_Ty = point_y;
		}
	}
	else if (pos_name == "C4")
	{
		if (camera_name == "TX")
		{
			preC4PointX_Tx = point_x;
			preC4PointY_Tx = point_y;
		}
		else
		{
			preC4PointX_Ty = point_x;
			preC4PointY_Ty = point_y;
		}
	}
	else if (pos_name == "C4")
	{
		if (camera_name == "TX")
		{
			preC4PointX_Tx = point_x;
			preC4PointY_Tx = point_y;
		}
		else
		{
			preC4PointX_Ty = point_x;
			preC4PointY_Ty = point_y;
		}
	}
	else if (pos_name == "C5")
	{
		if (camera_name == "TX")
		{
			preC5PointX_Tx = point_x;
			preC5PointY_Tx = point_y;
		}
		else
		{
			preC5PointX_Ty = point_x;
			preC5PointY_Ty = point_y;
		}
	}
	else if (pos_name == "C6")
	{
		if (camera_name == "TX")
		{
			preC6PointX_Tx = point_x;
			preC6PointY_Tx = point_y;
		}
		else
		{
			preC6PointX_Ty = point_x;
			preC6PointY_Ty = point_y;
		}
	}
	else if (pos_name == "C7")
	{
		if (camera_name == "TX")
		{
			preC7PointX_Tx = point_x;
			preC7PointY_Tx = point_y;
		}
		else
		{
			preC7PointX_Ty = point_x;
			preC7PointY_Ty = point_y;
		}
	}
	return false;
}

bool MilCaller::GetPrePosValue(std::string camera_name, std::string pos_name, double & x, double & y)
{
	if (pos_name == "A1")
	{
		if (camera_name == "TX")
		{
			x = preA1PointX_Tx;
			y = preA1PointY_Tx;
		}
		else
		{
			x = preA1PointX_Ty;
			y = preA1PointY_Ty;
		}
	}
	else if (pos_name == "A2")
	{
		if (camera_name == "TX")
		{
			x = preA2PointX_Tx;
			y = preA2PointY_Tx;
		}
		else
		{
			x = preA2PointX_Ty;
			y = preA2PointY_Ty;
		}
	}
	else if (pos_name == "A3")
	{
		if (camera_name == "TX")
		{
			x = preA3PointX_Tx;
			y = preA3PointY_Tx;
		}
		else
		{
			x = preA3PointX_Ty;
			y = preA3PointY_Ty;
		}
	}
	else if (pos_name == "A4")
	{
		if (camera_name == "TX")
		{
			x = preA4PointX_Tx;
			y = preA4PointY_Tx;
		}
		else
		{
			x = preA4PointX_Ty;
			y = preA4PointY_Ty;
		}
	}
	else if (pos_name == "A5")
	{
		if (camera_name == "TX")
		{
			x = preA5PointX_Tx;
			y = preA5PointY_Tx;
		}
		else
		{
			x = preA5PointX_Ty;
			y = preA5PointY_Ty;
		}
	}
	else if (pos_name == "A6")
	{
		if (camera_name == "TX")
		{
			x = preA6PointX_Tx;
			y = preA6PointY_Tx;
		}
		else
		{
			x = preA6PointX_Ty;
			y = preA6PointY_Ty;
		}
	}
	else if (pos_name == "A7")
	{
		if (camera_name == "TX")
		{
			x = preA7PointX_Tx;
			y = preA7PointY_Tx;
		}
		else
		{
			x = preA7PointX_Ty;
			y = preA7PointY_Ty;
		}
	}
	else if (pos_name == "B1")
	{
		if (camera_name == "TX")
		{
			x = preB1PointX_Tx;
			y = preB1PointY_Tx;
		}
		else
		{
			x = preB1PointX_Ty;
			y = preB1PointY_Ty;
		}
	}
	else if (pos_name == "B2")
	{
		if (camera_name == "TX")
		{
			x = preB2PointX_Tx;
			y = preB2PointY_Tx;
		}
		else
		{
			x = preB2PointX_Ty;
			y = preB2PointY_Ty;
		}
	}
	else if (pos_name == "B3")
	{
		if (camera_name == "TX")
		{
			x = preB3PointX_Tx;
			y = preB3PointY_Tx;
		}
		else
		{
			x = preB3PointX_Ty;
			y = preB3PointY_Ty;
		}
	}
	else if (pos_name == "B4")
	{
		if (camera_name == "TX")
		{
			x = preB4PointX_Tx;
			y = preB4PointY_Tx;
		}
		else
		{
			x = preB4PointX_Ty;
			y = preB4PointY_Ty;
		}
	}
	else if (pos_name == "B5")
	{
		if (camera_name == "TX")
		{
			x = preB5PointX_Tx;
			y = preB5PointY_Tx;
		}
		else
		{
			x = preB5PointX_Ty;
			y = preB5PointY_Ty;
		}
	}
	else if (pos_name == "B6")
	{
		if (camera_name == "TX")
		{
			x = preB6PointX_Tx;
			y = preB6PointY_Tx;
		}
		else
		{
			x = preB6PointX_Ty;
			y = preB6PointY_Ty;
		}
	}
	else if (pos_name == "B7")
	{
		if (camera_name == "TX")
		{
			x = preB7PointX_Tx;
			y = preB7PointY_Tx;
		}
		else
		{
			x = preB7PointX_Ty;
			y = preB7PointY_Ty;
		}
	}
	else if (pos_name == "C1")
	{
		if (camera_name == "TX")
		{
			x = preC1PointX_Tx;
			y = preC1PointY_Tx;
		}
		else
		{
			x = preC1PointX_Ty;
			y = preC1PointY_Ty;
		}
	}
	else if (pos_name == "C2")
	{
		if (camera_name == "TX")
		{
			x = preC2PointX_Tx;
			y = preC2PointY_Tx;
		}
		else
		{
			x = preC2PointX_Ty;
			y = preC2PointY_Ty;
		}
	}
	else if (pos_name == "C3")
	{
		if (camera_name == "TX")
		{
			x = preC3PointX_Tx;
			y = preC3PointY_Tx;
		}
		else
		{
			x = preC3PointX_Ty;
			y = preC3PointY_Ty;
		}
	}
	else if (pos_name == "C4")
	{
		if (camera_name == "TX")
		{
			x = preC4PointX_Tx;
			y = preC4PointY_Tx;
		}
		else
		{
			x = preC4PointX_Ty;
			y = preC4PointY_Ty;
		}
	}
	else if (pos_name == "C5")
	{
		if (camera_name == "TX")
		{
			x = preC5PointX_Tx;
			y = preC5PointY_Tx;
		}
		else
		{
			x = preC5PointX_Ty;
			y = preC5PointY_Ty;
		}
	}
	else if (pos_name == "C6")
	{
		if (camera_name == "TX")
		{
			x = preC6PointX_Tx;
			y = preC6PointY_Tx;
		}
		else
		{
			x = preC6PointX_Ty;
			y = preC6PointY_Ty;
		}
	}
	else if (pos_name == "C7")
	{
		if (camera_name == "TX")
		{
			x = preC7PointX_Tx;
			y = preC7PointY_Tx;
		}
		else
		{
			x = preC7PointX_Ty;
			y = preC7PointY_Ty;
		}
	}
	return false;
}

std::vector<std::string> MilCaller::TransVector(std::vector<std::string> vec)
{
	std::vector<std::string> new_vec;
	std::vector<std::string>::reverse_iterator riter;
	for (riter = vec.rbegin(); riter != vec.rend(); riter++)
	{
		new_vec.push_back(*riter);
	}
	return new_vec;
}

void MilCaller::PluginWriteLog(JLogLevel level, std::string strFunc, const std::string str)
{
	jCore->Logger("MilPlugin.dll").Log(level, strFunc, str);
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
		// 结果乘以5.5
		pointX = result[0].X * 5.5;
		pointY = result[0].Y * 5.5;
	}
	std::string pos_name = data.GetValue("HikData", "PosName");
	AddResultToVector(pos_name.substr(0, 1), current_camera, pointX, pointY);
	// 临时图片文件删除/保存 (异步执行)
	auto future = std::async(std::launch::async, &MilCaller::DealImage, this, imageFile, result, current_camera, pos_name, isSave);
	return 0;
}

int MilCaller::WriteTestResultToCSV(JupData & data)
{
	int test_count = data.GetInt("HikData", "TestCount"); 
	std::string test_startTime = data.GetValue("HikData", "TestStartTime");
	std::string test_temp1 = data.GetValue("Serial", "CurrentTemp1");
	//std::string test_temp1 = "0.0";
	std::string test_temp2 = data.GetValue("Serial", "CurrentTemp2");	
	//std::string test_temp2 = "0.0";
	std::string omron_heigh1 = std::to_string(std::atof(data.GetValue("Serial", "OmronHeigh1").c_str())*1000.000);
	//std::string omron_heigh1 = "0.0";
	std::string omron_heigh2 = std::to_string(std::atof(data.GetValue("Serial", "OmronHeigh2").c_str())*1000.000);
	//std::string omron_heigh2 = "0.0";
	std::string confocal_heigh1 = std::to_string(std::atof(data.GetValue("ConfocalSensor", "Heigh1").c_str())*1000.000);
	//std::string confocal_heigh1 = "0.0";
	std::string confocal_heigh2 = std::to_string(std::atof(data.GetValue("ConfocalSensor", "Heigh2").c_str())*1000.000);
	//std::string confocal_heigh2 = "0.0";
	std::string omron_heigh3 = std::to_string(std::atof(data.GetValue("Serial", "OmronHeigh3").c_str())*1000.000);
	//std::string omron_heigh3 = "0.0";

	std::vector<std::string> TxResultB_X = TransVector(m_TxResultB_X);
	std::vector<std::string> TxResultB_Y = TransVector(m_TxResultB_Y);
	std::vector<std::string> TyResultB_X = TransVector(m_TyResultB_X);
	std::vector<std::string> TyResultB_Y = TransVector(m_TyResultB_Y);

	// 按格式拼接结果
	std::vector<std::string> resultDatas;
	resultDatas.push_back(std::to_string(test_count));
	resultDatas.push_back(test_startTime);
	resultDatas.push_back(test_temp1);
	resultDatas.push_back(test_temp2);
	resultDatas.push_back(omron_heigh1);
	resultDatas.push_back(omron_heigh2);
	resultDatas.push_back(confocal_heigh1);
	resultDatas.push_back(confocal_heigh2);
	resultDatas.push_back(omron_heigh3);
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TxResultA_X.begin()), std::make_move_iterator(m_TxResultA_X.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TxResultA_Y.begin()), std::make_move_iterator(m_TxResultA_Y.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(TxResultB_X.begin()), std::make_move_iterator(TxResultB_X.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(TxResultB_Y.begin()), std::make_move_iterator(TxResultB_Y.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TxResultC_X.begin()), std::make_move_iterator(m_TxResultC_X.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TxResultC_Y.begin()), std::make_move_iterator(m_TxResultC_Y.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TyResultA_X.begin()), std::make_move_iterator(m_TyResultA_X.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TyResultA_Y.begin()), std::make_move_iterator(m_TyResultA_Y.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(TyResultB_X.begin()), std::make_move_iterator(TyResultB_X.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(TyResultB_Y.begin()), std::make_move_iterator(TyResultB_Y.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TyResultC_X.begin()), std::make_move_iterator(m_TyResultC_X.end()));
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(m_TyResultC_Y.begin()), std::make_move_iterator(m_TyResultC_Y.end()));

	std::string AxisTxAngle = data.GetValue("PosAngle", "AxisTx");
	auto tx_angle = Jup::Split(AxisTxAngle, ",");
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(tx_angle.begin()), std::make_move_iterator(tx_angle.end()));
	std::string AxisTyAngle = data.GetValue("PosAngle", "AxisTy");
	auto ty_angle = Jup::Split(AxisTyAngle, ",");
	resultDatas.insert(resultDatas.end(), std::make_move_iterator(ty_angle.begin()), std::make_move_iterator(ty_angle.end()));

	// 写入文件
	std::string imageFile = data.GetValue("HikData", "ImageFile");
	if (!WriteDataToCSV(imageFile, resultDatas))
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

int MilCaller::OpenDILCamera(JupData & data)
{
	if (m_dil_camera->IsOpened())
	{
		return 0;
	}
	return m_dil_camera->Open() ? 0 : -1;
}

int MilCaller::SetDILCameraParas(JupData & data)
{
	// 设置外部触发
	m_dil_camera->SetRunMode(1);
	return 0;
}

int MilCaller::SetDotParas(JupData & data)
{
	// 设置曝光
	int ex_time = jCore->GlobalSettings().ReadInt("DILCamera", "DotExposureTime");
	m_dil_camera->SetExposure(ex_time);
	// 设置增益
	int gain = jCore->GlobalSettings().ReadInt("DILCamera", "DotGain");
	m_dil_camera->SetGain(gain);
	return 0;
}

int MilCaller::SetFloodParas(JupData & data)
{
	// 设置曝光
	int ex_time = jCore->GlobalSettings().ReadInt("DILCamera", "FloodExposureTime");
	m_dil_camera->SetExposure(ex_time);
	// 设置增益
	int gain = jCore->GlobalSettings().ReadInt("DILCamera", "FloodGain");
	m_dil_camera->SetGain(gain);
	return 0;
}

int MilCaller::WaitTriggerGetImage(JupData & data)
{
	// 开始采集等待触发获得图片
	//m_dil_camera->SetStartGrabing(false);
	std::thread t(&CameraDILManager::StartGrabing, m_dil_camera);
	t.detach();
	//std::async(std::launch::async, &CameraDILManager::StartGrabing, m_dil_camera);
	//unsigned char* image = m_future.get();
	//m_future.get();
	Sleep(100);
	return 0;
}

bool MilCaller::WriteDataToCSV(std::string imageInput, std::vector<std::string>& datas)
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
			m_reader.addRow(m_csv_head);
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

bool MilCaller::DeleteTempImage(std::string image)
{
	if (std::filesystem::exists(image)) {
		if (std::remove(image.c_str()) != 0) {
			return false;
		}
	}
	return true;
}