#pragma once

#include "PluginBase/JupCaller.h"
#include "MilManager.h"
#include <ShlObj.h>
class CSVReader;

/*
	该类是平台调用测试项的接口，若正确定义能在平台的测试流程编辑器上被使用，并加载到测试项中
*/
class MilCaller : public JupCaller
{
public:
	MilCaller();
	~MilCaller();

	/*
		在该函数做特定的初始化操作，由平台调用该函数

		示例：默认调用父类接口的实现JupCaller::Initialize();
		根据当前插件的实际需要选择添加内容
	*/
	int Initialize() override;

	/*
		统一在该函数内注册所有测试项方法的函数

		示例：Plugin_Method_Add(SmuCaller, Demo_msleep100);
		其中DemoTestCaller为当前类的类名，Demo_msleep100为需要注册的函数名
	*/
	int RegisterMethod() override;

private:
	/*
		在此添加需要测试项方法的函数，函数类型必须为int (T::*)(JupData&)
		下列函数需要在RegisterMethod()中注册才能在平台上使用
	*/
	int Demo_msleep100(JupData& data);

	int ResetData(JupData& data);

	// 计算图片（Hik）
	int GetHikImageResult(JupData& data);

	// 调用Find接口计算图片
	int GetFindModeImageResult(JupData& data);

	// 写入测试数据到CSV
	int WriteTestResultToCSV(JupData& data);

	// 计算下相机图片
	int GetBottomImageResult(JupData& data);

	// 计算下相机B2B图片
	int GetBottomB2BImageResult(JupData& data);

	// 上相机计算下料口图片
	int GetTopImageDownDutResult(JupData& data);

	// 计算上相机图片
	int GetTopImageResult(JupData& data);

	// 计算下相机图片
	int GetHIKImageResult(JupData& data);

	// 计算上相机图片
	int GetDVPImageResult(JupData& data);

	// 保存数据
	int SaveDOETestData(JupData& data);

	int SaveDOE2TestData(JupData& data);

	int SaveDOE3TestData(JupData& data);

	// 校准数据写入csv
	int SaveCalibraData(JupData& data);

private:
	bool WriteDataToCSV(std::string imageInput, std::vector<std::string> heads, std::vector<std::string> datas);
	bool WriteDoeTestDataToCSV(std::string path, std::vector<std::string> heads, std::vector<std::string> datas);
	bool DeleteTempImage(std::string image);
	void DealImage(std::string imageFile, std::vector<PointXYA> result, std::string camera, bool isSave);
	std::string GetMMFName(std::string camera_name);
	void AddResultToVector(std::string group, std::string camera_name, double point_x, double point_y);
	void SaveThresholdImage(std::string image_file, std::string camera_name, double point_x, double point_y);

	bool GetOpenFileFolderName(std::string &strImagePath);
private:
	MilManager* m_pMil;
	//CSVReader* m_pCsv;

	std::string m_mmfPathTx = "./Config/TX.mmf";
	std::string m_mmfPathTy = "./Config/TY.mmf";

	double prePointX_Tx = 0.0;
	double prePointY_Tx = 0.0;
	double prePointX_Ty = 0.0;
	double prePointY_Ty = 0.0;
	std::vector<std::string> m_bottom_csv_head = {"Time", "BarCode", "Camera", "Position_X", "Position_Y", "Position_Angle"
												, "UpperLeft_Circle_X", "UpperLeft_Circle_Y", "UpperLeft_Circle_radius"												
												, "UpperRight_Circle_X", "UpperRight_Circle_Y", "UpperRight_Circle_radius" 												
												, "DownRight_Circle_X", "DownRight_Circle_Y", "DownRight_Circle_radius"
												, "DownLeft_Circle_X", "DownLeft_Circle_Y", "DownLeft_Circle_radius"
												, "Center_X", "Center_Y", "Center_Angle", "Distance"};

	std::vector<std::string> m_top_csv_head = {"Time", "BarCode", "Camera", "B2B_X", "B2B_Y", "B2B_Angle"
											  , "Upper_Circle_X", "Upper_Circle_Y", "Upper_Circle_radius"
										      , "Down_Circle_X", "Down_Circle_Y", "Down_Circle_radius"
											  , "Center_X", "Center_Y", "Center_Angle", "Distance", "Socket_Angle" };

	std::vector<std::string> m_top2_csv_head = { "Time", "BarCode", "Camera", "B2B_X", "B2B_Y", "B2B_Angle"
											  , "Upper_Circle_X", "Upper_Circle_Y", "Upper_Circle_radius"
											  , "Down_Circle_X", "Down_Circle_Y", "Down_Circle_radius"
											  , "Center_X", "Center_Y", "Center_Angle", "Distance", "Socket_Angle"
											  , "Down_Socket_Upper_Circle_X", "Down_Socket_Upper_Circle_Y", "Down_Socket_Upper_Circle_radius"
											  , "Down_Socket_Down_Circle_X", "Down_Socket_Down_Circle_Y", "Down_Socket_Down_Circle_radius"
											  ,	"Down_Socket_Center_X","Down_Socket_Center_Y", "Down_Socket_Center_Angle" };

	std::vector<std::string> m_doe_csv_head = { "Time", "HIK_X", "HIK_Y", "DVP_X", "DVP_Y", "Temperature"};

	std::vector<std::string> m_csv_head = { "Item", "Time", "Temperature"
	, "TxCamera_A1_PointX", "TxCamera_A2_PointX", "TxCamera_A3_PointX", "TxCamera_A4_PointX", "TxCamera_A5_PointX", "TxCamera_A6_PointX", "TxCamera_A7_PointX"
	, "TxCamera_A1_PointY", "TxCamera_A2_PointY", "TxCamera_A3_PointY", "TxCamera_A4_PointY", "TxCamera_A5_PointY", "TxCamera_A6_PointY", "TxCamera_A7_PointY"
	, "TxCamera_B1_PointX", "TxCamera_B2_PointX", "TxCamera_B3_PointX", "TxCamera_B4_PointX", "TxCamera_B5_PointX", "TxCamera_B6_PointX", "TxCamera_B7_PointX"
	, "TxCamera_B1_PointY", "TxCamera_B2_PointY", "TxCamera_B3_PointY", "TxCamera_B4_PointY", "TxCamera_B5_PointY", "TxCamera_B6_PointY", "TxCamera_B7_PointY"
	, "TxCamera_C1_PointX", "TxCamera_C2_PointX", "TxCamera_C3_PointX", "TxCamera_C4_PointX", "TxCamera_C5_PointX", "TxCamera_C6_PointX", "TxCamera_C7_PointX"
	, "TxCamera_C1_PointY", "TxCamera_C2_PointY", "TxCamera_C3_PointY", "TxCamera_C4_PointY", "TxCamera_C5_PointY", "TxCamera_C6_PointY", "TxCamera_C7_PointY"
	, "TyCamera_A1_PointX", "TyCamera_A2_PointX", "TyCamera_A3_PointX", "TyCamera_A4_PointX", "TyCamera_A5_PointX", "TyCamera_A6_PointX", "TyCamera_A7_PointX"
	, "TyCamera_A1_PointY", "TyCamera_A2_PointY", "TyCamera_A3_PointY", "TyCamera_A4_PointY", "TyCamera_A5_PointY", "TyCamera_A6_PointY", "TyCamera_A7_PointY"
	, "TyCamera_B1_PointX", "TyCamera_B2_PointX", "TyCamera_B3_PointX", "TyCamera_B4_PointX", "TyCamera_B5_PointX", "TyCamera_B6_PointX", "TyCamera_B7_PointX"
	, "TyCamera_B1_PointY", "TyCamera_B2_PointY", "TyCamera_B3_PointY", "TyCamera_B4_PointY", "TyCamera_B5_PointY", "TyCamera_B6_PointY", "TyCamera_B7_PointY"
	, "TyCamera_C1_PointX", "TyCamera_C2_PointX", "TyCamera_C3_PointX", "TyCamera_C4_PointX", "TyCamera_C5_PointX", "TyCamera_C6_PointX", "TyCamera_C7_PointX"
	, "TyCamera_C1_PointY", "TyCamera_C2_PointY", "TyCamera_C3_PointY", "TyCamera_C4_PointY", "TyCamera_C5_PointY", "TyCamera_C6_PointY", "TyCamera_C7_PointY" };

	std::vector<std::string> m_calibra_head = { "Item","Time","PnpCFOV_X","PnpCFOV_Y","NozzleCFOV_X","NozzleCFOV_Y","PnpPos_X","PnpPos_Y","CalPnpDelta_X","CalPnpDelta_Y" };

};
