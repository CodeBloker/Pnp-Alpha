#include "VisionManager.h"

// Constructor
VisionManager::VisionManager() {
	// Initialization code.
}

// Destructor
VisionManager::~VisionManager() {
	// Cleanup code, if any.
}

void VisionManager::FindCircleCenter(double x1, double y1, double x2, double y2, double x3, double y3, double & CenterX, double & CenterY, double & CenterR)
{
	double midX1 = (x1 + x2) / 2.0;
	double midY1 = (y1 + y2) / 2.0;
	double midX2 = (x2 + x3) / 2.0;
	double midY2 = (y2 + y3) / 2.0;

	// 避免值一样的情况
	if (x1 == x2 || x2 == x3)
	{
		CenterX = -999.0;
		CenterY = -999.0;
		CenterR = -999.0;
		return;
	}

	double slope1 = (y2 - y1) / (x2 - x1);
	double slope2 = (y3 - y2) / (x3 - x2);

	double perpSlope1 = -1 / slope1;
	double perpSlope2 = -1 / slope2;

	double b1 = midY1 - perpSlope1 * midX1;
	double b2 = midY2 - perpSlope2 * midX2;

	CenterX = (b2 - b1) / (perpSlope1 - perpSlope2);
	CenterY = perpSlope1 * CenterX + b1;

	double radius1 = sqrtf((CenterX - x1)*(CenterX - x1) + (CenterY - y1)*(CenterY - y1));
	double radius2 = sqrtf((CenterX - x2)*(CenterX - x2) + (CenterY - y2)*(CenterY - y2));
	double radius3 = sqrtf((CenterX - x3)*(CenterX - x3) + (CenterY - y3)*(CenterY - y3));
	CenterR = (radius1 + radius2 + radius3) / 3.0;
}

// More methods can be added as per requirements.
std::string VisionManager::ExecuteModelFindROIGetResult(MIL_ID MSystem, MIL_ID MImage, const std::string DutMMFFilename,
	const std::vector<MilRect>& RectDutROIlist, std::vector<PointXYA>& ResultLists, MIL_ID GraphicList) {
	std::string sErr;
	MIL_ID ModelContextID = M_NULL;
	MIL_ID ResultContextID = M_NULL;
	MIL_ID ClonedImage = M_NULL;
	MIL_ID ROIImage = M_NULL;

	try {
		MIL_INT  ResultCount = 0;
		ResultLists.clear();
		if (GraphicList != NULL)
			MgraClear(M_DEFAULT, GraphicList);
		if (MImage == M_NULL) {
			throw std::runtime_error("Invalid image or null");
		}
		
		// Find DUT Coordinate
		MmodRestore(MIL_CONST_TEXT_PTR(DutMMFFilename.c_str()), MSystem, M_DEFAULT, &ModelContextID);
		MmodPreprocess(ModelContextID, M_DEFAULT);
		MmodAllocResult(MSystem, M_DEFAULT, &ResultContextID);
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);

		for (size_t i = 0; i < RectDutROIlist.size(); i++) {
			if (ROIImage != M_NULL) MbufFree(ROIImage);
			MbufChild2d(ClonedImage, RectDutROIlist[i].X, RectDutROIlist[i].Y,
				RectDutROIlist[i].W, RectDutROIlist[i].H, &ROIImage);
			MmodFind(ModelContextID, ROIImage, ResultContextID);
			MmodGetResult(ResultContextID, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);
			if (GraphicList != NULL)
			{
				MgraControl(GraphicList, M_DRAW_OFFSET_X, -RectDutROIlist[i].X);
				MgraControl(GraphicList, M_DRAW_OFFSET_Y, -RectDutROIlist[i].Y);
				MmodDraw(M_DEFAULT, ResultContextID, GraphicList,
					M_DRAW_EDGES + M_DRAW_POSITION, M_DEFAULT, M_DEFAULT);
				MgraControl(GraphicList, M_DRAW_OFFSET_X, 0);
				MgraControl(GraphicList, M_DRAW_OFFSET_Y, 0);
			}
			double temX = 0.0;
			double temY = 0.0;
			double temAngle = 0.0;
			if (ResultCount == 1) {
				MmodGetResult(ResultContextID, 0, M_POSITION_X, &temX);
				MmodGetResult(ResultContextID, 0, M_POSITION_Y, &temY);
				MmodGetResult(ResultContextID, 0, M_ANGLE, &temAngle);

				temX += RectDutROIlist[i].X;
				temY += RectDutROIlist[i].Y;

				ResultLists.emplace_back(static_cast<float>(temX), static_cast<float>(temY), static_cast<float>(temAngle));
			}
			else {
				ResultLists.emplace_back(-9999.0f, -9999.0f, 0.0f);
				sErr += "Failed to find MMF[" + std::to_string(i) + "]";
			}
		}
	}
	catch (const std::exception& ex) {
		sErr += ex.what();
	}
	if (ROIImage != M_NULL) MbufFree(ROIImage);
	if (ClonedImage != M_NULL) MbufFree(ClonedImage);
	if (ModelContextID != M_NULL) MmodFree(ModelContextID);
	if (ResultContextID != M_NULL) MmodFree(ResultContextID);

	return sErr;
}

std::string VisionManager::ExecuteModelFindGetResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string DutMMFFilename,
	std::vector<PointXYA>& ResultLists, MIL_ID GraphicList) {
	std::string sErr;
	MIL_ID ModelContextID = M_NULL;
	MIL_ID ResultContextID = M_NULL;
	MIL_ID ClonedImage = M_NULL;
	MIL_ID ROIImage = M_NULL;

	try {
		MIL_INT  ResultCount = 0;
		ResultLists.clear();
		if (GraphicList != NULL)
			MgraClear(M_DEFAULT, GraphicList);
		if (MImage == M_NULL) {
			throw std::runtime_error("Invalid image or null");
		}
		
		// Find DUT Coordinate
		MmodRestoreA((DutMMFFilename.data()), MSystem, M_DEFAULT, &ModelContextID);
		MmodPreprocess(ModelContextID, M_DEFAULT);
		MmodAllocResult(MSystem, M_DEFAULT, &ResultContextID);
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);

		MmodFind(ModelContextID, ClonedImage, ResultContextID);
		MmodGetResult(ResultContextID, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);
		if(ResultCount == 0)
			throw std::runtime_error("Invalid image or null");
		if (GraphicList != NULL)
		{
			MmodDraw(M_DEFAULT, ResultContextID, GraphicList,
				M_DRAW_EDGES + M_DRAW_POSITION, M_DEFAULT, M_DEFAULT);
		}

		MIL_INT img_W;
		MIL_INT img_H;
		MbufInquire(MImage, M_SIZE_X, &img_W);
		MbufInquire(MImage, M_SIZE_Y, &img_H);
		MbufAllocColor(MSystem, 3, img_W, img_H, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_DISP, &ImageOut);
		MimConvert(MImage, ImageOut, M_L_TO_RGB);
		MIL_UNIQUE_GRA_ID GraphicsContext = MgraAlloc(MSystem, M_UNIQUE_ID);

		for (int i = 0; i < ResultCount; i++)
		{
			double temX = 0.0;
			double temY = 0.0;
			double temAngle = 0.0;
			MmodGetResult(ResultContextID, i, M_POSITION_X, &temX);
			MmodGetResult(ResultContextID, i, M_POSITION_Y, &temY);
			MmodGetResult(ResultContextID, i, M_ANGLE, &temAngle);

			ResultLists.emplace_back(static_cast<float>(temX), static_cast<float>(temY), static_cast<float>(temAngle));

			MgraColor(GraphicsContext, M_COLOR_GREEN);
			MmodDraw(GraphicsContext, ResultContextID, ImageOut, M_DRAW_POSITION, i, M_DEFAULT);
			MgraColor(GraphicsContext, M_COLOR_GREEN);
			MmodDraw(GraphicsContext, ResultContextID, ImageOut, M_DRAW_BOX, i, M_DEFAULT);
			MgraColor(GraphicsContext, M_COLOR_RED);
			MmodDraw(GraphicsContext, ResultContextID, ImageOut, M_DRAW_EDGES, i, M_DEFAULT);
		}
		if (img_W != M_NULL) MbufFree(img_W);
		if (img_H != M_NULL) MbufFree(img_H);
	}
	catch (const std::exception& ex) {
		sErr += ex.what();
	}
	if (ROIImage != M_NULL) MbufFree(ROIImage);
	if (ClonedImage != M_NULL) MbufFree(ClonedImage);
	if (ModelContextID != M_NULL) MmodFree(ModelContextID);
	if (ResultContextID != M_NULL) MmodFree(ResultContextID);

	return sErr;
}

std::string VisionManager::ExecuteMMFandMETGetResult(MIL_ID MSystem,MIL_ID MImage,const std::string& DutMMFFilename,const std::string& DutMETFilename,
	const std::vector<int>& ResListIdx,const MilRect& RectDutROI,std::vector<PointXYA>& ResultLists, MIL_ID GraphicList)
{
	ResultLists.clear();
	std::string sErr;
	bool MmfFind = false;
	MIL_ID MmfContextD = M_NULL;
	MIL_ID ResultContextD = M_NULL;
	MIL_ID ClonedImage = M_NULL;
	MIL_ID ROIImage = M_NULL;
	MIL_ID MetContextD = M_NULL;
	MIL_ID MetRusult = M_NULL;

	try {
		if (MImage == M_NULL) {
			throw std::invalid_argument("Invalid image or null");
		}
		if (GraphicList != NULL)
			MgraClear(M_DEFAULT, GraphicList);
		// 模板匹配找中心
		MmodRestoreA((DutMMFFilename.data()), MSystem, M_DEFAULT, &MmfContextD);
		MmodPreprocess(MmfContextD, M_DEFAULT);
		MmodAllocResult(MSystem, M_DEFAULT, &ResultContextD);
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);

		MIL_INT ResultCount = 0;
		if (ROIImage != M_NULL) {
			MbufFree(ROIImage);
		}
		MbufChild2d(ClonedImage, RectDutROI.X, RectDutROI.Y, RectDutROI.W, RectDutROI.H, &ROIImage);
		MmodFind(MmfContextD, ROIImage, ResultContextD);
		MmodGetResult(ResultContextD, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);

		double mmfX = 0.0;
		double mmfY = 0.0;
		double mmfAngle = 0.0;
		if (ResultCount == 1) {
			MmodGetResult(ResultContextD, 0, M_POSITION_X, &mmfX);
			MmodGetResult(ResultContextD, 0, M_POSITION_Y, &mmfY);
			MmodGetResult(ResultContextD, 0, M_ANGLE, &mmfAngle);

			mmfX += RectDutROI.X;
			mmfY += RectDutROI.Y;

			MmfFind = true;
		}
		else {
			sErr += "Failed to find MMF";
			MmfFind = false;
		}

		if (MmfFind) {
			// 载入MET 设置MET中心，计算
			MmetRestoreA(DutMETFilename.data(), MSystem, M_DEFAULT, &MetContextD);
			MmetAllocResult(MSystem, M_DEFAULT, &MetRusult);

			// 将模板结果设置到met 根据序号来确定设置的位置
			int index = 0;
			MmetSetPosition(MetContextD, M_FEATURE_INDEX(index), M_POSITION, mmfX, mmfY, mmfAngle, M_DEFAULT, M_DEFAULT);
			// 计算
			MmetCalculate(MetContextD, MImage, MetRusult, M_DEFAULT);
			// 设置以图片坐标为原点输出
			MmetControl(MetRusult, M_GENERAL, M_OUTPUT_FRAME, M_IMAGE_FRAME);
			if (GraphicList != NULL)
			{
				MmetDraw(M_DEFAULT, MetRusult, GraphicList,
					M_DEFAULT, M_DEFAULT, M_DEFAULT);
			}
			// 获取结果
			for (int idx : ResListIdx) {
				double tempx = -100;
				double tempy = -100;
				MmetGetResult(MetRusult, M_FEATURE_LABEL(idx), M_POSITION_X, &tempx);
				MmetGetResult(MetRusult, M_FEATURE_LABEL(idx), M_POSITION_Y, &tempy);
				ResultLists.emplace_back(static_cast<float>(tempx), static_cast<float>(tempy), 0);
			}
		}
	}
	catch (const std::exception& ex) {
		sErr += ex.what();
	}

	if (ROIImage != M_NULL) {
		MbufFree(ROIImage);
	}
	if (ClonedImage != M_NULL) {
		MbufFree(ClonedImage);
	}
	if (MmfContextD != M_NULL) {
		MmodFree(MmfContextD);
	}
	if (ResultContextD != M_NULL) {
		MmodFree(ResultContextD);
	}
	if (MetContextD != M_NULL) {
		MmetFree(MetContextD);
	}
	if (MetRusult != M_NULL) {
		MmetFree(MetRusult);
	}
	return sErr;
}

std::string VisionManager::ExecuteMMFandMETGetResult_Special(MIL_ID MSystem, MIL_ID MImage, const std::string& DutMMFFilename, const std::string& DutMETFilename,
	const std::vector<int>& ResListIdx, std::vector<MilRect>& RectDutROIlist, const std::vector<int>& MetSetIndexs, std::vector<PointXYA>& ResultLists, MIL_ID GraphicList)
{
	ResultLists.clear();
	std::string sErr;

	MIL_ID MmfContextD = M_NULL;
	MIL_ID ResultContextD = M_NULL;
	MIL_ID ClonedImage = M_NULL;
	MIL_ID ROIImage = M_NULL;
	MIL_ID MetContextD = M_NULL;
	MIL_ID MetRusult = M_NULL;
	bool MmfFind = false;
	std::vector<PointXYA> ModelResults;
	try {
		if (MImage == M_NULL) {
			throw std::invalid_argument("Invalid image or null");
		}
		if (GraphicList != NULL)
			MgraClear(M_DEFAULT, GraphicList);
		// 模板匹配找中心
		MmodRestoreA((DutMMFFilename.data()), MSystem, M_DEFAULT, &MmfContextD);
		MmodPreprocess(MmfContextD, M_DEFAULT);
		MmodAllocResult(MSystem, M_DEFAULT, &ResultContextD);
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);

		MIL_INT ResultCount = 0;

		for (size_t i = 0; i < RectDutROIlist.size(); i++) {
			if (ROIImage != M_NULL) MbufFree(ROIImage);
			MbufChild2d(ClonedImage, RectDutROIlist[i].X, RectDutROIlist[i].Y,
				RectDutROIlist[i].W, RectDutROIlist[i].H, &ROIImage);
			MmodFind(MmfContextD, ROIImage, ResultContextD);
			MmodGetResult(ResultContextD, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);
			if (GraphicList != NULL)
			{
				MgraControl(M_DEFAULT, M_DRAW_OFFSET_X, -RectDutROIlist[i].X);
				MgraControl(M_DEFAULT, M_DRAW_OFFSET_Y, -RectDutROIlist[i].Y);
				MmodDraw(M_DEFAULT, ResultContextD, GraphicList,
					M_DRAW_EDGES + M_DRAW_POSITION, M_DEFAULT, M_DEFAULT);
				MgraControl(M_DEFAULT, M_DRAW_OFFSET_X, 0);
				MgraControl(M_DEFAULT, M_DRAW_OFFSET_Y, 0);
			}

			if (ResultCount > 0) {
				double temX = 0.0;
				double temY = 0.0;
				double temAngle = 0.0;
				MmodGetResult(ResultContextD, 0, M_POSITION_X, &temX);
				MmodGetResult(ResultContextD, 0, M_POSITION_Y, &temY);
				MmodGetResult(ResultContextD, 0, M_ANGLE, &temAngle);

				temX += RectDutROIlist[i].X;
				temY += RectDutROIlist[i].Y;

				MmfFind = true;

				ModelResults.emplace_back(static_cast<float>(temX), static_cast<float>(temY), static_cast<float>(temAngle));
			}
			else {
				MmfFind = false;
				sErr += "Failed to find MMF[" + std::to_string(i) + "]";
			}
		}
		int temp1 = MetSetIndexs.size();
		int temp2 = ModelResults.size();
		if (MetSetIndexs.size() != ModelResults.size()) {
			throw std::invalid_argument("模板结果数量与设置Met参数不匹配");
		}
		if (MmfFind) {
			// 载入MET 设置MET中心，计算
			MmetRestoreA(DutMETFilename.data(), MSystem, M_DEFAULT, &MetContextD);
			MmetAllocResult(MSystem, M_DEFAULT, &MetRusult);

			// 将模板结果设置到met 根据序号来确定设置的位置
			for (size_t i = 0; i < MetSetIndexs.size(); i++)
			{
				MmetControl(MetContextD, M_FEATURE_INDEX(MetSetIndexs[i]), M_POSITION_X, ModelResults[i].X);
				MmetControl(MetContextD, M_FEATURE_INDEX(MetSetIndexs[i]), M_POSITION_Y, ModelResults[i].Y);
				//MmetSetPosition(MetContextD, M_FEATURE_INDEX(MetSetIndexs[i]), M_POSITION, ModelResults[i].X, ModelResults[i].Y, ModelResults[i].R, M_DEFAULT, M_DEFAULT);
			}
			// 计算
			MmetCalculate(MetContextD, MImage, MetRusult, M_DEFAULT);
			// 设置以图片坐标为原点输出
			MmetControl(MetRusult, M_GENERAL, M_OUTPUT_FRAME, M_IMAGE_FRAME);
			if (GraphicList != NULL)
			{
				MmetDraw(M_DEFAULT, MetRusult, GraphicList,
					M_DRAW_FEATURE, M_DEFAULT, M_DEFAULT);
			}
			// 获取结果
			for (int idx : ResListIdx) {
				double tempx = -100;
				double tempy = -100;
				MmetGetResult(MetRusult, M_FEATURE_LABEL(idx), M_POSITION_X, &tempx);
				MmetGetResult(MetRusult, M_FEATURE_LABEL(idx), M_POSITION_Y, &tempy);
				ResultLists.emplace_back(static_cast<float>(tempx), static_cast<float>(tempy), 0);
			}
		}
	}
	catch (const std::exception& ex) {
		sErr += ex.what();
	}

	if (ROIImage != M_NULL) {
		MbufFree(ROIImage);
	}
	if (ClonedImage != M_NULL) {
		MbufFree(ClonedImage);
	}
	if (MmfContextD != M_NULL) {
		MmodFree(MmfContextD);
	}
	if (ResultContextD != M_NULL) {
		MmodFree(ResultContextD);
	}
	if (MetContextD != M_NULL) {
		MmetFree(MetContextD);
	}
	if (MetRusult != M_NULL) {
		MmetFree(MetRusult);
	}
	return sErr;
}
/// <summary>
/// 读取二维码
/// </summary>
/// <param name="MSystem"></param>
/// <param name="MImage"></param>
/// <param name="McoList"></param>
/// <param name="trcList"></param>
/// <param name="IsBinarization"></param>
/// <param name="BinarizationValue"></param>
/// <param name="ResultLists"></param>
/// <returns></returns>
std::string VisionManager::ReadCodeMatrix(MIL_ID MSystem,MIL_ID MImage,const std::vector<std::string>& McoList,const std::vector<MilRect>& RoiList,
	bool IsBinarization,int BinarizationValue,	std::vector<std::string>& ResultLists, MIL_ID GraphicList)
{
	std::string sErr;

	MIL_ID McoContext = M_NULL;
	MIL_ID ResultContext = M_NULL;
	MIL_ID ClonedImage = M_NULL;
	MIL_ID ROIImage = M_NULL;
	MIL_ID BinImage = M_NULL;

	try {
		if (MImage == M_NULL) {
			throw std::invalid_argument("Invalid image or null");
		}
		if (GraphicList != NULL)
			MgraClear(M_DEFAULT, GraphicList);
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);
		McodeAllocResult(MSystem, M_DEFAULT, &ResultContext);

		for (size_t i = 0; i < McoList.size(); i++) {
			if (McoContext != M_NULL) {
				McodeFree(McoContext);
			}

			McodeRestoreA(McoList[i].data(), MSystem, M_DEFAULT, &McoContext);

			if (i > 0) MbufFree(ROIImage);
			MbufChild2d(ClonedImage, RoiList[i].X, RoiList[i].Y, RoiList[i].W, RoiList[i].H, &ROIImage);

			if (IsBinarization) {
				MbufClone(ROIImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, &BinImage);
				MimBinarize(ROIImage, BinImage, M_FIXED + M_GREATER, BinarizationValue, M_NULL);
				McodeRead(McoContext, BinImage, ResultContext);
			}
			else {
				McodeRead(McoContext, ROIImage, ResultContext);
			}

			MIL_INT BarcodeStatus = M_NULL;
			char BarcodeString[64] = { 0 };

			McodeGetResult(ResultContext, M_DEFAULT, M_DEFAULT, M_STATUS + M_TYPE_MIL_INT, &BarcodeStatus);

			if (BarcodeStatus == M_STATUS_READ_OK) {
				MIL_INT ResultCount = 0;
				McodeGetResult(ResultContext, M_DEFAULT, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);

				if (ResultCount > 0) {
					for (MIL_INT ii = 0; ii < ResultCount; ii++) {
						double x = 0, y = 0;

						McodeGetResult(ResultContext, ii, M_GENERAL, M_STRING, BarcodeString);
						McodeGetResult(ResultContext, ii, M_GENERAL, M_POSITION_X, &x);
						McodeGetResult(ResultContext, ii, M_GENERAL, M_POSITION_Y, &y);

						x += RoiList[i].X;
						y += RoiList[i].Y;

						ResultLists.push_back(std::string(BarcodeString));
					}
				}
				else {
					throw std::runtime_error("Code no result" + std::to_string(i));
				}
			}
			else {
				throw std::runtime_error("Code status - cannot read" + std::to_string(i));
			}
		}

	}
	catch (const std::exception& ex) {
		sErr = ex.what();
	}

	if (BinImage != M_NULL) {
		MbufFree(BinImage);
	}
	if (ROIImage != M_NULL) {
		MbufFree(ROIImage);
	}
	if (ClonedImage != M_NULL) {
		MbufFree(ClonedImage);
	}
	if (McoContext != M_NULL) {
		McodeFree(McoContext);
	}
	if (ResultContext != M_NULL) {
		McodeFree(ResultContext);
	}
	

	return sErr;
}





