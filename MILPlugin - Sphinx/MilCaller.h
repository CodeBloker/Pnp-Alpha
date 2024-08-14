#pragma once

#include "PluginBase/JupCaller.h"
#include "MilManager.h"
#include "JupCore.h"

class CSVReader;
class CameraDILManager;

class JupDefine
{
public:
	enum LogLevel
	{
		Error = 0,
		Info,
		Warn,
		Debug,
	};
};

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

	// 写入测试数据到CSV
	int WriteTestResultToCSV(JupData& data);

	//*****************DIL相机*******************//
	// 打开DIL相机
	int OpenDILCamera(JupData& data);
	// 设置DIL相机参数
	int SetDILCameraParas(JupData& data);
	// 设置Dot参数
	int SetDotParas(JupData& data);
	// 设置Flood参数
	int SetFloodParas(JupData& data);
	// 开启采集
	int WaitTriggerGetImage(JupData& data);


private:
	bool WriteDataToCSV(std::string imageInput, std::vector<std::string>& datas);
	bool DeleteTempImage(std::string image);
	void DealImage(std::string imageFile, std::vector<PointXYA> result, std::string camera, std::string pos_name, bool isSave);
	std::string GetMMFName(std::string camera_name);
	void AddResultToVector(std::string group, std::string camera_name, double point_x, double point_y);
	void SaveThresholdImage(std::string image_file, std::string camera_name, std::string pos_name, double point_x, double point_y);
	bool RecordPrePosValue(std::string camera_name, std::string pos_name, double point_x, double point_y);
	bool GetPrePosValue(std::string camera_name, std::string pos_name, double& x, double& y);

	std::vector<std::string> TransVector(std::vector<std::string> vec);

private:
	// log
	void PluginWriteLog(JLogLevel level, std::string strFunc, const std::string str);

private:
	MilManager* m_pMil;
	CameraDILManager* m_dil_camera;

	std::string m_mmfPathTx = "./Config/TX.mmf";
	std::string m_mmfPathTy = "./Config/TY.mmf";

	//std::vector<std::string> m_csv_head = { "Item", "Time", "Temperature1", "Temperature2", "YSensor_Heigh1", "XSensor_Heigh1", "XSensor_Heigh2", "ZSensor_Heigh"
	//, "YZCamera_A1_Y", "YZCamera_A2_Y", "YZCamera_A3_Y", "YZCamera_A4_Y", "YZCamera_A5_Y", "YZCamera_A6_Y", "YZCamera_A7_Y"
	//, "YZCamera_A1_Z", "YZCamera_A2_Z", "YZCamera_A3_Z", "YZCamera_A4_Z", "YZCamera_A5_Z", "YZCamera_A6_Z", "YZCamera_A7_Z"
	//, "YZCamera_B1_Y", "YZCamera_B2_Y", "YZCamera_B3_Y", "YZCamera_B4_Y", "YZCamera_B5_Y", "YZCamera_B6_Y", "YZCamera_B7_Y"
	//, "YZCamera_B1_Z", "YZCamera_B2_Z", "YZCamera_B3_Z", "YZCamera_B4_Z", "YZCamera_B5_Z", "YZCamera_B6_Z", "YZCamera_B7_Z"
	//, "YZCamera_C1_Y", "YZCamera_C2_Y", "YZCamera_C3_Y", "YZCamera_C4_Y", "YZCamera_C5_Y", "YZCamera_C6_Y", "YZCamera_C7_Y"
	//, "YZCamera_C1_Z", "YZCamera_C2_Z", "YZCamera_C3_Z", "YZCamera_C4_Z", "YZCamera_C5_Z", "YZCamera_C6_Z", "YZCamera_C7_Z"
	//, "XZCamera_A1_X", "XZCamera_A2_X", "XZCamera_A3_X", "XZCamera_A4_X", "XZCamera_A5_X", "XZCamera_A6_X", "XZCamera_A7_X"
	//, "XZCamera_A1_Z", "XZCamera_A2_Z", "XZCamera_A3_Z", "XZCamera_A4_Z", "XZCamera_A5_Z", "XZCamera_A6_Z", "XZCamera_A7_Z"
	//, "XZCamera_B1_X", "XZCamera_B2_X", "XZCamera_B3_X", "XZCamera_B4_X", "XZCamera_B5_X", "XZCamera_B6_X", "XZCamera_B7_X"
	//, "XZCamera_B1_Z", "XZCamera_B2_Z", "XZCamera_B3_Z", "XZCamera_B4_Z", "XZCamera_B5_Z", "XZCamera_B6_Z", "XZCamera_B7_Z"
	//, "XZCamera_C1_X", "XZCamera_C2_X", "XZCamera_C3_X", "XZCamera_C4_X", "XZCamera_C5_X", "XZCamera_C6_X", "XZCamera_C7_X"
	//, "XZCamera_C1_Z", "XZCamera_C2_Z", "XZCamera_C3_Z", "XZCamera_C4_Z", "XZCamera_C5_Z", "XZCamera_C6_Z", "XZCamera_C7_Z"
	//, "YZAngle_A1", "YZAngle_A2" , "YZAngle_A3" , "YZAngle_A4" , "YZAngle_A5" , "YZAngle_A6" , "YZAngle_A7" 
	//, "YZAngle_B7", "YZAngle_B6" , "YZAngle_B5" , "YZAngle_B4" , "YZAngle_B3" , "YZAngle_B2" , "YZAngle_B1" 
	//, "YZAngle_C1", "YZAngle_C2" , "YZAngle_C3" , "YZAngle_C4" , "YZAngle_C5" , "YZAngle_C6" , "YZAngle_C7"
	//, "XZAngle_A1", "XZAngle_A2" , "XZAngle_A3" , "XZAngle_A4" , "XZAngle_A5" , "XZAngle_A6" , "XZAngle_A7"
	//, "XZAngle_B7", "XZAngle_B6" , "XZAngle_B5" , "XZAngle_B4" , "XZAngle_B3" , "XZAngle_B2" , "XZAngle_B1"
	//, "XZAngle_C1", "XZAngle_C2" , "XZAngle_C3" , "XZAngle_C4" , "XZAngle_C5" , "XZAngle_C6" , "XZAngle_C7" 
	//};

	std::vector<std::string> m_csv_head = { "Item", "Time", "Temperature1", "Temperature2", "YSensor_Heigh1", "XSensor_Heigh1", "XSensor_Heigh2", "ZSensor_Heigh1", "ZSensor_Heigh2"
	, "YZCamera_A1_Y"
	, "YZCamera_A1_Z"
	, "YZCamera_B4_Y"
	, "YZCamera_B4_Z"
	, "YZCamera_C7_Y"
	, "YZCamera_C7_Z"
	, "XZCamera_A1_X"
	, "XZCamera_A1_Z"
	, "XZCamera_B4_X"
	, "XZCamera_B4_Z"
	, "XZCamera_C7_X"
	, "XZCamera_C7_Z"
	, "YZAngle_A1"
	, "YZAngle_B4"
	, "YZAngle_C7"
	, "XZAngle_A1"
	, "XZAngle_B4"
	, "XZAngle_C7"
	};
};
