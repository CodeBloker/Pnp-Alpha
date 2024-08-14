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

	void fnFindCircleCenter(double x1, double y1, double x2, double y2, double x3, double y3, double& CenterX, double& CenterY, double& CenterR);

	bool fnGetPictureDegree(int nSocIndex, std::string file, std::string & outPath, float & degree, float & midPointX, float & midPointY, bool bDebug = false);

	std::string VisionModelFindGetResult(std::string strFilePathImage, std::string& strFileOut, std::string strFilePathMMF, std::vector<PointXYA>& Results, bool save_result = true);

	std::string VisionMETGetResultSpecial(std::string strFilePathMMf, std::string strFilePathMET, std::vector<PointXYA>& Results);

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

