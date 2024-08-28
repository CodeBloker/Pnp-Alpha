#pragma once
#include <Mil.h>
#include <vector>
#include <string>
#include <stdexcept>

struct _Point {
	float X;
	float Y;
};

struct Line {
	double a;
	double b;
	double c;
};

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

struct MilMetIndex
{
	int SetPositionIndex;
	int Result_PositionXIndex;
	int Result_PositionYIndex;
	int Result_AngleIndex;
	MilMetIndex(int Index_1, int Index_2, int Index_3, int Index_4) : SetPositionIndex(Index_1), Result_PositionXIndex(Index_2), Result_PositionYIndex(Index_3), Result_AngleIndex(Index_4) {}
};

class VisionManager {


public:
	VisionManager();

	~VisionManager();

	float Calculate_Angle_Points(_Point point_A, _Point point_B)
	{
		float PI = 180;
		float xx, yy, angle;
		xx = point_B.X - point_A.X;
		yy = point_B.Y - point_A.Y;
		if (xx == 0.0)
		{
			angle = PI / 2.0;
		}
		else
		{
			angle = atan(fabs(yy / xx));
			angle = angle * 180 / 3.1415926535;
		}

		if ((xx < 0.0) && (yy > 0.0))
		{
			angle = PI - angle;
		}
		else if ((xx < 0.0) && (yy < 0.0))
		{
			angle = PI + angle;
		}
		else if ((xx >= 0.0) && (yy < 0.0))
		{
			angle = PI * 2.0 - angle;
		}
		return angle;
	}

	Line createLineFromPoints(_Point p1, _Point p2) 
	{
		Line line;

		// 计算直线方程的系数
		line.a = p2.Y - p1.Y;
		line.b = p1.X - p2.X;
		line.c = p2.X * p1.Y - p1.X * p2.Y;

		return line;
	}

	_Point findIntersection(Line line1, Line line2) 
	{
		_Point intersection;

		// 解直线方程组
		double determinant = line1.a * line2.b - line2.a * line1.b;

		if (determinant != 0) {
			intersection.X = abs((line2.b * line1.c - line1.b * line2.c) / determinant);
			intersection.Y = abs((line1.a * line2.c - line2.a * line1.c) / determinant);

			return intersection;
		} // namespace functions
	}

	std::string ExecuteBottomCameraResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, std::string strMCOFilePath, const std::string MMFFilename_Model
		, const std::string METFilename_Model, const std::string MMFFilename_Circle, const MilMetIndex MetIndex, const std::vector<MilRect> RectROI_Circle
		, std::vector<PointXYA>& ResultLists, float &fdistance, std::string &strBarCode);
	std::string ExecuteTopCameraResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string MMFFilename_Model, const std::string METFilename_Model
		, const std::string MMFFilename_Circle, const MilMetIndex MetIndex, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, float &fdistance, float &fSocketAngle);

	std::string ExecuteModelFindROIGetResult(MIL_ID MSystem, MIL_ID MImage, const std::string DutMMFFilename,
		const std::vector<MilRect>& RectDutROIlist, std::vector<PointXYA>& ResultLists,MIL_ID GraphicList = NULL);

	std::string ExecuteModelFindGetResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string DutMMFFilename,
		std::vector<PointXYA>& ResultLists, MIL_ID GraphicList = NULL);

	std::string ExecuteMMFandMETGetResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string DutMMFFilename, const std::string DutMETFilename,
		const MilMetIndex MetIndex, const MilRect RectDutROI, std::vector<PointXYA>& ResultLists);

	std::string ExecuteMETGetResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string DutMETFilename, std::vector<PointXYA>& ResultLists);

	std::string ReadCodeMatrix(MIL_ID MSystem, MIL_ID MImage, const std::vector<std::string>& McoList, const std::vector<MilRect>& trcList,
		bool IsBinarization, int BinarizationValue, std::vector<std::string>& ResultLists, MIL_ID GraphicList = NULL);

	std::string ExecuteMMFandMETGetResult_Special(MIL_ID MSystem, MIL_ID MImage, const std::string& DutMMFFilename, const std::string& DutMETFilename,
		const std::vector<int>& ResListIdx, std::vector<MilRect>& RectDutROIlist, const std::vector<int>& metListID, std::vector<PointXYA>& ResultLists,MIL_ID GraphicList = NULL);

	//计算B2B底面中心
	std::string ExecuteBottomCameraB2BResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string MMFFilename_Model, std::vector<PointXYA>& ResultLists);

	//计算下料口两个铆钉的中心
	std::string ExecuteTopCameraSocketDownResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists);

	//计算十字中心坐标
	std::string ExecuteBottomCameraCrossResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, float &fdistance, float &fSocketAngle, float &deltaX, float &deltaY);

	//计算上相机与底部视觉中心
	std::string ExecuteTopCamerCrossResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, float &fdistance, float &fSocketAngle, float &deltaX, float &deltaY);

	//计算底部四个圆中心校准
	std::string ExecuteButtomCamerCircle(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string MMFFilename_Model, const std::string MMFFilename_Circle_Model, const std::vector<MilRect> RectROI_Cross, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, std::vector<PointXYA>& ResultCircleLists, float &fdistance, float &fSocketAngle, float &deltaX, float &deltaY);

	//计算上料时 B2B正面中心
	std::string ExecuteTopCameraB2BCenterResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string MMFFilename_Model, float &deltaX, float &deltaY);

	//计算下料时 Socket两个Mark点
	std::string ExecuteTopCameraDownSocketMarkResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string MMFFilename_Model, std::vector<MilRect> RectROI_Circle, float &deltaX, float &deltaY);

	//计算放进下料口后 B2B跟Socket两个Mark点的距离
	std::string ExecuteTopCamerDownSocketMarkDistance(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string MMFFilename_Model
		,const std::string MMFFilename_Circle_Model, std::vector<MilRect> RectROI_Circle, float &fSocketAngle, float &fdistance);
};



