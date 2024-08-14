#pragma once
#include <Mil.h>
#include <vector>
#include <string>
#include <stdexcept>

struct PointXYA {
	float X;
	float Y;
	float R;
	PointXYA(float x, float y, float r) : X(x), Y(y), R(r) {}
};
struct MilRect {
	int X;
	int Y;
	int W;
	int H;
	MilRect(int x, int y, int w, int h) : X(x), Y(y), W(w), H(h) {}
};


class VisionManager {


public:
	VisionManager();

	~VisionManager();

	// 计算拟合圆心坐标
	void FindCircleCenter(double x1, double y1, double x2, double y2, double x3, double y3, double& CenterX, double& CenterY, double & CenterR);

	std::string InitDisplay(MIL_ID MSystem, MIL_ID MImage, const std::string DutMMFFilename,
		const std::vector<MilRect>& RectDutROIlist, std::vector<PointXYA>& ResultLists, MIL_ID GraphicList = NULL);

	std::string ExecuteModelFindROIGetResult(MIL_ID MSystem, MIL_ID MImage, const std::string DutMMFFilename,
		const std::vector<MilRect>& RectDutROIlist, std::vector<PointXYA>& ResultLists,MIL_ID GraphicList = NULL);

	std::string ExecuteModelFindGetResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string DutMMFFilename,
		std::vector<PointXYA>& ResultLists, MIL_ID GraphicList = NULL);

	std::string ExecuteMMFandMETGetResult(MIL_ID MSystem, MIL_ID MImage, const std::string& DutMMFFilename, const std::string& DutMETFilename,
		const std::vector<int>& ResListIdx, const MilRect& RectDutROI, std::vector<PointXYA>& ResultLists, MIL_ID GraphicList = NULL);

	std::string ReadCodeMatrix(MIL_ID MSystem, MIL_ID MImage, const std::vector<std::string>& McoList, const std::vector<MilRect>& trcList,
		bool IsBinarization, int BinarizationValue, std::vector<std::string>& ResultLists, MIL_ID GraphicList = NULL);

	std::string ExecuteMMFandMETGetResult_Special(MIL_ID MSystem, MIL_ID MImage, const std::string& DutMMFFilename, const std::string& DutMETFilename,
		const std::vector<int>& ResListIdx, std::vector<MilRect>& RectDutROIlist, const std::vector<int>& metListID, std::vector<PointXYA>& ResultLists,MIL_ID GraphicList = NULL);
};



