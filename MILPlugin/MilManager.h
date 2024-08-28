#pragma once
#include "Common/JIniSettings.h"
#include <string>
#include "VisionManager.h"

#define INSPECTORINFOR_INI	"D:\\EVMS\\ENV\\Config\\InspectInfor.ini"

typedef struct _tagMILInstance
{
	MIL_ID milApplication;		// Application identifier.
	MIL_ID milSystem;			// System Identifier.
	MIL_ID milDisplay;			// Display identifier.
} MILInstance, *PMILInstance;

class MilManager
{
public:
	MilManager();
	~MilManager();

	static MilManager*& GetInstance();
	MILInstance getMilInstance() { return m_mil; }

	bool fnGetPictureDegree(int nSocIndex, std::string file, std::string & outPath, float & degree, float & midPointX, float & midPointY, bool bDebug = false);

	std::string VisionModelFindGetResult(std::string strFilePathImage, std::string& strFileOut, std::string strFilePathMMF, std::vector<PointXYA>& Results, bool save_result = true);

	std::string VisionMETGetResultSpecial(std::string strFilePathMMf, std::string strFilePathMET, std::vector<PointXYA>& Results);

	std::string VisionMMFandMETGetResult(std::string strFilePathImage, std::string& strFileOut, std::string strFilePathMMF, std::string strFilePathMET,
		const MilMetIndex MetIndex, const MilRect RectDutROI, std::vector<PointXYA>& Results, bool save_result = true);

	std::string VisionMETGetResult(std::string strFilePathImage, std::string& strFileOut, std::string strFilePathMET, std::vector<PointXYA>& Results, bool save_result = true);

	std::string VisionBottomCameraResult(std::string strFilePathImage, std::string& strFileOut, std::string strMCOFilePath, const std::string MMFFilename_Model
		, const std::string METFilename_Model, const std::string MMFFilename_Circle, const MilMetIndex MetIndex, const std::vector<MilRect> RectROI_Circle
		, std::vector<PointXYA>& ResultLists, float &fdistance, std::string &strBarCode, bool save_result = true);
	std::string VisionTopCameraResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, const std::string METFilename_Model
		, const std::string MMFFilename_Circle, const MilMetIndex MetIndex, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, float &fdistance, float &fSocketAngle, bool save_result = true);

	//计算B2B的中心坐标
	std::string VisionBottomB2BCameraResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, std::vector<PointXYA>& ResultLists);

	//计算下料口两个钉中心坐标
	std::string VisionTopDownSocketCameraResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists);

	//计算中心十字坐标
	std::string VisionBottomCrossCamerResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, float &fdistance, float &fSocketAngle, float &deltaX, float &deltaY);

	//计算上相机与底部视觉中心
	std::string VisionTopCrossCamerResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, float &fdistance, float &fSocketAngle, float &deltaX, float &deltaY);
	
	//计算四个圆点和四个十字
	std::string VisionButtomCircleCamerResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, const std::string MMFFilename_Circle_Model, const std::vector<MilRect> RectROI_Cross, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, std::vector<PointXYA>& ResultCircleLists, float &fdistance, float &fSocketAngle, float &deltaX, float &deltaY);

	//计算上料时 B2B正面中心
	std::string VisionB2BTopCenterCamerResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, float &deltaX, float &deltaY);

	//计算下料时 Socket俩Mark点中心
	std::string VisionSocketMarkCenterCamerResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, float &deltaX, float &deltaY);

	//计算放进下料口后 B2B跟Socket两个Mark点的距离
	std::string VisionSocketMarkAndB2BDistanceResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model
		, const std::string MMFFilename_Circle_Model, const std::vector<MilRect> RectROI_Circle, float &SocketAngle, float &distance);
private:
	void loadParasFromFile(const char* file_name);
	void saveMilImage(std::string strFilePath, MIL_ID MilImageOut);

private:
	MILInstance m_mil;
	VisionManager visionManager;

	JIniSettings *m_IniParas;
	std::map<std::string, std::string> m_VisionSetting;

	inline static MilManager* m_SingleInstance = nullptr;
	inline static std::mutex m_Mutex;
};

