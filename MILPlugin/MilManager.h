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

	//����B2B����������
	std::string VisionBottomB2BCameraResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, std::vector<PointXYA>& ResultLists);

	//�������Ͽ���������������
	std::string VisionTopDownSocketCameraResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists);

	//��������ʮ������
	std::string VisionBottomCrossCamerResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, float &fdistance, float &fSocketAngle, float &deltaX, float &deltaY);

	//�����������ײ��Ӿ�����
	std::string VisionTopCrossCamerResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, float &fdistance, float &fSocketAngle, float &deltaX, float &deltaY);
	
	//�����ĸ�Բ����ĸ�ʮ��
	std::string VisionButtomCircleCamerResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, const std::string MMFFilename_Circle_Model, const std::vector<MilRect> RectROI_Cross, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, std::vector<PointXYA>& ResultCircleLists, float &fdistance, float &fSocketAngle, float &deltaX, float &deltaY);

	//��������ʱ B2B��������
	std::string VisionB2BTopCenterCamerResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, float &deltaX, float &deltaY);

	//��������ʱ Socket��Mark������
	std::string VisionSocketMarkCenterCamerResult(std::string strFilePathImage, std::string& strFileOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, float &deltaX, float &deltaY);

	//����Ž����Ͽں� B2B��Socket����Mark��ľ���
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

