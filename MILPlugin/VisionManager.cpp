#include "VisionManager.h"

// Constructor
VisionManager::VisionManager() {
	// Initialization code.
}

// Destructor
VisionManager::~VisionManager() {
	// Cleanup code, if any.
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
		//if (img_W != M_NULL) MbufFree(img_W);
		//if (img_H != M_NULL) MbufFree(img_H);
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

std::string VisionManager::ExecuteMMFandMETGetResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, 
	const std::string DutMMFFilename, const std::string DutMETFilename, const MilMetIndex MetIndex, 
	const MilRect RectDutROI,std::vector<PointXYA>& ResultLists)
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
		// 模板匹配找中心
		MmodRestoreA((DutMMFFilename.data()), MSystem, M_DEFAULT, &MmfContextD);
		MmodPreprocess(MmfContextD, M_DEFAULT);
		MmodAllocResult(MSystem, M_DEFAULT, &ResultContextD);
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);

		MIL_INT img_W;
		MIL_INT img_H;
		MbufInquire(MImage, M_SIZE_X, &img_W);
		MbufInquire(MImage, M_SIZE_Y, &img_H);
		MbufAllocColor(MSystem, 3, img_W, img_H, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_DISP, &ImageOut);
		MimConvert(MImage, ImageOut, M_L_TO_RGB);
		MIL_UNIQUE_GRA_ID GraphicsContext = MgraAlloc(MSystem, M_UNIQUE_ID);

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

			//画结果图
			MgraControl(GraphicsContext, M_DRAW_OFFSET_X, -RectDutROI.X);
			MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, -RectDutROI.Y);
			MgraColor(GraphicsContext, M_COLOR_BLUE);
			MmodDraw(GraphicsContext, ResultContextD, ImageOut, M_DRAW_POSITION, 0, M_DEFAULT);
			MgraColor(GraphicsContext, M_COLOR_RED);
			MmodDraw(GraphicsContext, ResultContextD, ImageOut, M_DRAW_EDGES, 0, M_DEFAULT);
			MgraControl(GraphicsContext, M_DRAW_OFFSET_X, 0);
			MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, 0);
		}
		else {
			sErr += "Failed to find MMF";
			MmfFind = false;
		}
		//if (img_W != M_NULL) MbufFree(img_W);
		//if (img_H != M_NULL) MbufFree(img_H);

		if (MmfFind) {
			// 载入MET 设置MET中心，计算
			MmetRestoreA(DutMETFilename.data(), MSystem, M_DEFAULT, &MetContextD);
			MmetAllocResult(MSystem, M_DEFAULT, &MetRusult);

			// 将模板结果设置到met 根据序号来确定设置的位置
			MmetSetPosition(MetContextD, M_FEATURE_INDEX(MetIndex.SetPositionIndex), M_POSITION, mmfX, mmfY, mmfAngle, M_DEFAULT, M_DEFAULT);
			// 计算
			MmetCalculate(MetContextD, MImage, MetRusult, M_DEFAULT);
			// 设置以图片坐标为原点输出
			MmetControl(MetRusult, M_GENERAL, M_OUTPUT_FRAME, M_IMAGE_FRAME);
			//画结果图
			MgraColor(GraphicsContext, M_COLOR_GREEN);
			MmetDraw(GraphicsContext, MetRusult, ImageOut, M_DRAW_FEATURE, M_DEFAULT, M_DEFAULT);
			// 获取结果
			double tempx = -100;
			double tempy = -100;
			double tempA = 0;
			MmetGetResult(MetRusult, M_FEATURE_LABEL(MetIndex.Result_PositionXIndex), M_POSITION_X, &tempx);
			MmetGetResult(MetRusult, M_FEATURE_LABEL(MetIndex.Result_PositionYIndex), M_POSITION_Y, &tempy);
			MmetGetResult(MetRusult, M_FEATURE_LABEL(MetIndex.Result_AngleIndex), M_ANGLE, &tempA);
			ResultLists.emplace_back(static_cast<float>(tempx), static_cast<float>(tempy), static_cast<float>(tempA));
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

std::string VisionManager::ExecuteMETGetResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string DutMETFilename, std::vector<PointXYA>& ResultLists)
{
	ResultLists.clear();
	std::string sErr;
	MIL_ID ClonedImage = M_NULL;
	MIL_ID ROIImage = M_NULL;
	MIL_ID MetContextD = M_NULL;
	MIL_ID MetRusult = M_NULL;

	try {
		if (MImage == M_NULL) {
			throw std::invalid_argument("Invalid image or null");
		}
		
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);

		MIL_INT img_W;
		MIL_INT img_H;
		MbufInquire(MImage, M_SIZE_X, &img_W);
		MbufInquire(MImage, M_SIZE_Y, &img_H);
		MbufAllocColor(MSystem, 3, img_W, img_H, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_DISP, &ImageOut);
		MimConvert(MImage, ImageOut, M_L_TO_RGB);
		MIL_UNIQUE_GRA_ID GraphicsContext = MgraAlloc(MSystem, M_UNIQUE_ID);

		// 载入MET 设置MET中心，计算
		MmetRestoreA(DutMETFilename.data(), MSystem, M_DEFAULT, &MetContextD);
		MmetAllocResult(MSystem, M_DEFAULT, &MetRusult);

		// 将模板结果设置到met 根据序号来确定设置的位置
		MmetSetPosition(MetContextD, M_FEATURE_INDEX(0), M_POSITION, 0, 0, 0, M_DEFAULT, M_DEFAULT);
		// 计算
		MmetCalculate(MetContextD, ClonedImage, MetRusult, M_DEFAULT);
		// 设置以图片坐标为原点输出
		MmetControl(MetRusult, M_GENERAL, M_OUTPUT_FRAME, M_IMAGE_FRAME);
		//画结果图
		MgraColor(GraphicsContext, M_COLOR_GREEN);
		MmetDraw(GraphicsContext, MetRusult, ImageOut, M_DRAW_FEATURE, M_DEFAULT, M_DEFAULT);
		// 获取结果
		double tempx = -100;
		double tempy = -100;
		double tempA = 0;
		MmetGetResult(MetRusult, M_FEATURE_LABEL(1), M_POSITION_X, &tempx);
		MmetGetResult(MetRusult, M_FEATURE_LABEL(1), M_POSITION_Y, &tempy);
		ResultLists.emplace_back(static_cast<float>(tempx), static_cast<float>(tempy), static_cast<float>(tempA));		
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
std::string VisionManager::ExecuteBottomCameraB2BResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID & ImageOut, const std::string MMFFilename_Model, std::vector<PointXYA>& ResultLists)
{
	std::string sErr = "";
	bool ModelFind = false;
	bool CircleFind = false;
	ResultLists.clear();
	MIL_ID ClonedImage = M_NULL;
	MIL_ID MmfContext_Model = M_NULL;
	MIL_ID MmfContext_Circle = M_NULL;
	MIL_ID ResultContext_Model = M_NULL;
	MIL_ID ResultContext_Circle = M_NULL;
	MIL_ID ROIImage = M_NULL;
	MIL_ID MetContextD = M_NULL;
	MIL_ID MetRusult = M_NULL;
	MIL_ID GraphicsContext = M_NULL;

	try
	{
		if (MImage == M_NULL)
		{
			throw std::runtime_error("Invalid image or null");
		}
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);
		MIL_INT img_W;
		MIL_INT img_H;
		MbufInquire(ClonedImage, M_SIZE_X, &img_W);
		MbufInquire(ClonedImage, M_SIZE_Y, &img_H);
		MbufAllocColor(MSystem, 3, img_W, img_H, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_DISP, &ImageOut);
		MimConvert(ClonedImage, ImageOut, M_L_TO_RGB);
		MgraAlloc(MSystem, &GraphicsContext);

		// 模板匹配找中心
		double mmfX = 0.0;
		double mmfY = 0.0;
		double mmfAngle = 0.0;
		MIL_INT ResultCount = 0;
		MmodRestoreA((MMFFilename_Model.data()), MSystem, M_DEFAULT, &MmfContext_Model);
		MmodPreprocess(MmfContext_Model, M_DEFAULT);
		MmodAllocResult(MSystem, M_DEFAULT, &ResultContext_Model);
		MmodFind(MmfContext_Model, ClonedImage, ResultContext_Model);
		MmodGetResult(ResultContext_Model, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);

		if (ResultCount == 1)
		{
			ModelFind = true;
			MmodGetResult(ResultContext_Model, 0, M_POSITION_X, &mmfX);
			MmodGetResult(ResultContext_Model, 0, M_POSITION_Y, &mmfY);
			MmodGetResult(ResultContext_Model, 0, M_ANGLE, &mmfAngle);

			//画结果图
			MgraColor(GraphicsContext, M_COLOR_BLUE);
			MmodDraw(GraphicsContext, ResultContext_Model, ImageOut, M_DRAW_POSITION, 0, M_DEFAULT);
			MgraColor(GraphicsContext, M_COLOR_RED);
			MmodDraw(GraphicsContext, ResultContext_Model, ImageOut, M_DRAW_EDGES, 0, M_DEFAULT);

			//将结果存入Point XYA动态数组中
			ResultLists.emplace_back(static_cast<float>(mmfX), static_cast<float>(mmfY), static_cast<float>(mmfAngle));
		}
		else
		{
			sErr += "Failed to find Model";
			ModelFind = false;
		}


	}
	catch (const std::exception& ex) {
		sErr += ex.what();
	}
	if (GraphicsContext != M_NULL)
	{
		MgraFree(GraphicsContext);
	}
	if (ROIImage != M_NULL) {
		MbufFree(ROIImage);
	}
	if (ClonedImage != M_NULL) {
		MbufFree(ClonedImage);
	}
	if (MmfContext_Model != M_NULL) {
		MmodFree(MmfContext_Model);
	}
	if (MetContextD != M_NULL) {
		MmetFree(MetContextD);
	}
	if (MmfContext_Circle != M_NULL) {
		MmodFree(MmfContext_Circle);
	}
	if (ResultContext_Model != M_NULL) {
		MmodFree(ResultContext_Model);
	}
	if (MetRusult != M_NULL) {
		MmetFree(MetRusult);
	}
	if (ResultContext_Circle != M_NULL) {
		MmodFree(ResultContext_Circle);
	}
	return sErr;
}
std::string VisionManager::ExecuteTopCameraSocketDownResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID & ImageOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists)
{
	std::string sErr = "";
	bool ModelFind = false;
	bool CircleFind = false;
	ResultLists.clear();
	MIL_ID ClonedImage = M_NULL;
	MIL_ID MmfContext_Model = M_NULL;
	MIL_ID MmfContext_Circle = M_NULL;
	MIL_ID ResultContext_Model = M_NULL;
	MIL_ID ResultContext_Circle = M_NULL;
	MIL_ID ROIImage = M_NULL;
	MIL_ID MetContextD = M_NULL;
	MIL_ID MetRusult = M_NULL;
	MIL_ID GraphicsContext = M_NULL;

	try
	{
		if (MImage == M_NULL)
		{
			throw std::runtime_error("Invalid image or null");
		}
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);
		MIL_INT img_W;
		MIL_INT img_H;
		MbufInquire(ClonedImage, M_SIZE_X, &img_W);
		MbufInquire(ClonedImage, M_SIZE_Y, &img_H);
		MbufAllocColor(MSystem, 3, img_W, img_H, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_DISP, &ImageOut);
		MimConvert(ClonedImage, ImageOut, M_L_TO_RGB);
		MgraAlloc(MSystem, &GraphicsContext);

		// Find circle
		MmodRestoreA((MMFFilename_Model.data()), MSystem, M_DEFAULT, &MmfContext_Circle);
		MmodPreprocess(MmfContext_Circle, M_DEFAULT);
		MmodAllocResult(MSystem, M_DEFAULT, &ResultContext_Circle);
		for (int i = 0; i < RectROI_Circle.size(); i++)
		{
			if (ROIImage != M_NULL)
			{
				MbufFree(ROIImage);
			}
			MIL_INT  ResultCount = 0;
			MbufChild2d(ClonedImage, RectROI_Circle.at(i).X, RectROI_Circle.at(i).Y, RectROI_Circle.at(i).W, RectROI_Circle.at(i).H, &ROIImage);
			MmodFind(MmfContext_Circle, ROIImage, ResultContext_Circle);
			MmodGetResult(ResultContext_Circle, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);
			if (ResultCount == 1)
			{
				CircleFind = true;
				double temX = 0.0;
				double temY = 0.0;
				double temRadius = 0.0;
				MmodGetResult(ResultContext_Circle, 0, M_POSITION_X, &temX);
				MmodGetResult(ResultContext_Circle, 0, M_POSITION_Y, &temY);
				MmodGetResult(ResultContext_Circle, 0, M_RADIUS, &temRadius);

				temX += RectROI_Circle.at(i).X;
				temY += RectROI_Circle.at(i).Y;

				ResultLists.emplace_back(static_cast<float>(temX), static_cast<float>(temY), static_cast<float>(temRadius));

				MgraControl(GraphicsContext, M_DRAW_OFFSET_X, -RectROI_Circle.at(i).X);
				MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, -RectROI_Circle.at(i).Y);
				MgraColor(GraphicsContext, M_COLOR_GREEN);
				MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_POSITION, 0, M_DEFAULT);
				MgraColor(GraphicsContext, M_COLOR_GREEN);
				MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_BOX, 0, M_DEFAULT);
				MgraColor(GraphicsContext, M_COLOR_RED);
				MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_EDGES, 0, M_DEFAULT);
				MgraControl(GraphicsContext, M_DRAW_OFFSET_X, 0);
				MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, 0);
			}
			else
			{
				CircleFind = false;
				sErr += "Failed to find circle, No :" + std::to_string(i);
			}
		}

		if (CircleFind)
		{
			_Point point_B;
			point_B.X = (ResultLists.at(0).X + ResultLists.at(1).X) / 2.0;
			point_B.Y = (ResultLists.at(0).Y + ResultLists.at(1).Y) / 2.0;
			ResultLists.emplace_back(static_cast<float>(point_B.X), static_cast<float>(point_B.Y), static_cast<float>(0));
			//画结果图
			MIL_INT XStart[2], YStart[2], XEnd[2], YEnd[2];
			int crossWidth = 50;
			int brushSize = 5; // must be odd value: 1,3,5,7
			XStart[0] = point_B.X - crossWidth;
			YStart[0] = point_B.Y;
			XEnd[0] = point_B.X + crossWidth;
			YEnd[0] = point_B.Y;

			XStart[1] = point_B.X;
			YStart[1] = point_B.Y - crossWidth;
			XEnd[1] = point_B.X;
			YEnd[1] = point_B.Y + crossWidth;
			MgraColor(GraphicsContext, M_COLOR_BLUE);
			MgraControl(GraphicsContext, M_LINE_THICKNESS, brushSize);
			MgraLines(GraphicsContext, ImageOut, 2, XStart, YStart, XEnd, YEnd, M_DEFAULT);
		}

	}
	catch (const std::exception& ex) {
		sErr += ex.what();
	}
	if (GraphicsContext != M_NULL)
	{
		MgraFree(GraphicsContext);
	}
	if (ROIImage != M_NULL) {
		MbufFree(ROIImage);
	}
	if (ClonedImage != M_NULL) {
		MbufFree(ClonedImage);
	}
	if (MmfContext_Model != M_NULL) {
		MmodFree(MmfContext_Model);
	}
	if (MetContextD != M_NULL) {
		MmetFree(MetContextD);
	}
	if (MmfContext_Circle != M_NULL) {
		MmodFree(MmfContext_Circle);
	}
	if (ResultContext_Model != M_NULL) {
		MmodFree(ResultContext_Model);
	}
	if (MetRusult != M_NULL) {
		MmetFree(MetRusult);
	}
	if (ResultContext_Circle != M_NULL) {
		MmodFree(ResultContext_Circle);
	}
	return sErr;
}
std::string VisionManager::ExecuteBottomCameraCrossResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID & ImageOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, float &fdistance, float &fSocketAngle, float &deltaX, float &deltaY)
{
	std::string sErr = "";
	bool ModelFind = false;
	bool CircleFind = false;
	bool ImageCenterFind = false;
	ResultLists.clear();
	MIL_ID ClonedImage = M_NULL;
	MIL_ID MmfContext_Model = M_NULL;
	MIL_ID MmfContext_Circle = M_NULL;
	MIL_ID ResultContext_Model = M_NULL;
	MIL_ID ResultContext_Circle = M_NULL;
	MIL_ID ROIImage = M_NULL;
	MIL_ID MetContextD = M_NULL;
	MIL_ID MetRusult = M_NULL;
	MIL_ID GraphicsContext = M_NULL;

	try
	{
		if (MImage == M_NULL)
		{
			throw std::runtime_error("Invalid image or null");
		}
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);
		MIL_INT img_W;
		MIL_INT img_H;
		MbufInquire(ClonedImage, M_SIZE_X, &img_W);
		MbufInquire(ClonedImage, M_SIZE_Y, &img_H);
		MbufAllocColor(MSystem, 3, img_W, img_H, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_DISP, &ImageOut);
		MimConvert(ClonedImage, ImageOut, M_L_TO_RGB);
		MgraAlloc(MSystem, &GraphicsContext);

		MmodRestoreA((MMFFilename_Model.data()), MSystem, M_DEFAULT, &MmfContext_Circle);
		MmodPreprocess(MmfContext_Circle, M_DEFAULT);
		MmodAllocResult(MSystem, M_DEFAULT, &ResultContext_Circle);
		for (int i = 0; i < RectROI_Circle.size(); i++)
		{
			if (ROIImage != M_NULL)
			{
				MbufFree(ROIImage);
			}
			MIL_INT  ResultCount = 0;
			MbufChild2d(ClonedImage, RectROI_Circle.at(i).X, RectROI_Circle.at(i).Y, RectROI_Circle.at(i).W, RectROI_Circle.at(i).H, &ROIImage);
			MmodFind(MmfContext_Circle, ROIImage, ResultContext_Circle);
			MmodGetResult(ResultContext_Circle, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);
			if (ResultCount == 1)
			{
				CircleFind = true;
				double temX = 0.0;
				double temY = 0.0;
				double temRadius = 0.0;
				MmodGetResult(ResultContext_Circle, 0, M_POSITION_X, &temX);
				MmodGetResult(ResultContext_Circle, 0, M_POSITION_Y, &temY);
				MmodGetResult(ResultContext_Circle, 0, M_RADIUS, &temRadius);

				temX += RectROI_Circle.at(i).X;
				temY += RectROI_Circle.at(i).Y;

				ResultLists.emplace_back(static_cast<float>(temX), static_cast<float>(temY), static_cast<float>(temRadius));

				MgraControl(GraphicsContext, M_DRAW_OFFSET_X, -RectROI_Circle.at(i).X);
				MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, -RectROI_Circle.at(i).Y);
				MgraColor(GraphicsContext, M_COLOR_GREEN);
				MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_POSITION, 0, M_DEFAULT);
				MgraColor(GraphicsContext, M_COLOR_GREEN);
				MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_BOX, 0, M_DEFAULT);
				MgraColor(GraphicsContext, M_COLOR_RED);
				MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_EDGES, 0, M_DEFAULT);
				MgraControl(GraphicsContext, M_DRAW_OFFSET_X, 0);
				MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, 0);
			}
			else
			{
				CircleFind = false;
				sErr += "Failed to find circle, No :" + std::to_string(i);
			}
		}

		if (CircleFind)
		{
			_Point point_Center;
			point_Center.X = (ResultLists.at(0).X + ResultLists.at(1).X + ResultLists.at(2).X + ResultLists.at(3).X) / 4.0;
			point_Center.Y = (ResultLists.at(0).Y + ResultLists.at(1).Y + ResultLists.at(2).Y + ResultLists.at(3).Y) / 4.0;
			ResultLists.emplace_back(static_cast<float>(point_Center.X), static_cast<float>(point_Center.Y), static_cast<float>(0));
			//画结果图
			MIL_INT XStart[2], YStart[2], XEnd[2], YEnd[2];
			int crossWidth = 50;
			int brushSize = 47; // must be odd value: 1,3,5,7
			XStart[0] = point_Center.X - crossWidth;
			YStart[0] = point_Center.Y;
			XEnd[0] = point_Center.X + crossWidth;
			YEnd[0] = point_Center.Y;

			XStart[1] = point_Center.X;
			YStart[1] = point_Center.Y - crossWidth;
			XEnd[1] = point_Center.X;
			YEnd[1] = point_Center.Y + crossWidth;
			MgraColor(GraphicsContext, M_COLOR_GREEN);
			MgraControl(GraphicsContext, M_LINE_THICKNESS, brushSize);
			MgraLines(GraphicsContext, ImageOut, 2, XStart, YStart, XEnd, YEnd, M_DEFAULT);

			ImageCenterFind = true;
		}

		if (ImageCenterFind)
		{
			float angle, distance;
			_Point point_img_Center;
			_Point point_A, point_B, point_C, point_D;
			point_A.X = ResultLists.at(0).X;
			point_A.Y = ResultLists.at(0).Y;
			point_B.X = ResultLists.at(2).X;
			point_B.Y = ResultLists.at(2).Y;
			point_C.X = ResultLists.back().X;
			point_C.Y = ResultLists.back().Y;
			point_img_Center.X = 5120 / 2.0;
			point_img_Center.Y = 5120 / 2.0;

			fSocketAngle = Calculate_Angle_Points(point_A, point_B);
			fdistance = sqrt(pow(point_C.X - point_img_Center.X, 2) + pow(point_C.Y - point_img_Center.Y, 2));
			deltaX = point_C.X - point_img_Center.X;
			deltaY = point_C.Y - point_img_Center.Y;
			//画结果图
			MIL_INT XStart[2], YStart[2], XEnd[2], YEnd[2];
			int crossWidth = 100;
			int brushSize = 47; // must be odd value: 1,3,5,7
			XStart[0] = point_img_Center.X - crossWidth;
			YStart[0] = point_img_Center.Y;
			XEnd[0] = point_img_Center.X + crossWidth;
			YEnd[0] = point_img_Center.Y;

			XStart[1] = point_img_Center.X;
			YStart[1] = point_img_Center.Y - crossWidth;
			XEnd[1] = point_img_Center.X;
			YEnd[1] = point_img_Center.Y + crossWidth;
			MgraColor(GraphicsContext, M_COLOR_BLUE);
			MgraControl(GraphicsContext, M_LINE_THICKNESS, brushSize);
			MgraLines(GraphicsContext, ImageOut, 2, XStart, YStart, XEnd, YEnd, M_DEFAULT);
		}

	}
	catch (const std::exception& ex) {
		sErr += ex.what();
	}
	if (GraphicsContext != M_NULL)
	{
		MgraFree(GraphicsContext);
	}
	if (ROIImage != M_NULL) {
		MbufFree(ROIImage);
	}
	if (ClonedImage != M_NULL) {
		MbufFree(ClonedImage);
	}
	if (MmfContext_Model != M_NULL) {
		MmodFree(MmfContext_Model);
	}
	if (MetContextD != M_NULL) {
		MmetFree(MetContextD);
	}
	if (MmfContext_Circle != M_NULL) {
		MmodFree(MmfContext_Circle);
	}
	if (ResultContext_Model != M_NULL) {
		MmodFree(ResultContext_Model);
	}
	if (MetRusult != M_NULL) {
		MmetFree(MetRusult);
	}
	if (ResultContext_Circle != M_NULL) {
		MmodFree(ResultContext_Circle);
	}
	return sErr;
}
std::string VisionManager::ExecuteTopCamerCrossResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID & ImageOut, const std::string MMFFilename_Model, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, float & fdistance, float & fSocketAngle, float & deltaX, float & deltaY)
{
	std::string sErr = "";
	bool ModelFind = false;
	bool CircleFind = false;
	bool ImageCenterFind = false;
	ResultLists.clear();
	MIL_ID ClonedImage = M_NULL;
	MIL_ID MmfContext_Model = M_NULL;
	MIL_ID MmfContext_Circle = M_NULL;
	MIL_ID ResultContext_Model = M_NULL;
	MIL_ID ResultContext_Circle = M_NULL;
	MIL_ID ROIImage = M_NULL;
	MIL_ID MetContextD = M_NULL;
	MIL_ID MetRusult = M_NULL;
	MIL_ID GraphicsContext = M_NULL;

	try
	{
		if (MImage == M_NULL)
		{
			throw std::runtime_error("Invalid image or null");
		}
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);
		MIL_INT img_W;
		MIL_INT img_H;
		MbufInquire(ClonedImage, M_SIZE_X, &img_W);
		MbufInquire(ClonedImage, M_SIZE_Y, &img_H);
		MbufAllocColor(MSystem, 3, img_W, img_H, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_DISP, &ImageOut);
		MimConvert(ClonedImage, ImageOut, M_L_TO_RGB);
		MgraAlloc(MSystem, &GraphicsContext);

		MmodRestoreA((MMFFilename_Model.data()), MSystem, M_DEFAULT, &MmfContext_Circle);
		MmodPreprocess(MmfContext_Circle, M_DEFAULT);
		MmodAllocResult(MSystem, M_DEFAULT, &ResultContext_Circle);
		for (int i = 0; i < RectROI_Circle.size(); i++)
		{
			if (ROIImage != M_NULL)
			{
				MbufFree(ROIImage);
			}
			MIL_INT  ResultCount = 0;
			MbufChild2d(ClonedImage, RectROI_Circle.at(i).X, RectROI_Circle.at(i).Y, RectROI_Circle.at(i).W, RectROI_Circle.at(i).H, &ROIImage);
			MmodFind(MmfContext_Circle, ROIImage, ResultContext_Circle);
			MmodGetResult(ResultContext_Circle, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);
			if (ResultCount == 1)
			{
				CircleFind = true;
				double temX = 0.0;
				double temY = 0.0;
				double temRadius = 0.0;
				MmodGetResult(ResultContext_Circle, 0, M_POSITION_X, &temX);
				MmodGetResult(ResultContext_Circle, 0, M_POSITION_Y, &temY);
				MmodGetResult(ResultContext_Circle, 0, M_RADIUS, &temRadius);

				temX += RectROI_Circle.at(i).X;
				temY += RectROI_Circle.at(i).Y;

				ResultLists.emplace_back(static_cast<float>(temX), static_cast<float>(temY), static_cast<float>(temRadius));

				MgraControl(GraphicsContext, M_DRAW_OFFSET_X, -RectROI_Circle.at(i).X);
				MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, -RectROI_Circle.at(i).Y);
				MgraColor(GraphicsContext, M_COLOR_GREEN);
				MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_POSITION, 0, M_DEFAULT);
				MgraColor(GraphicsContext, M_COLOR_GREEN);
				MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_BOX, 0, M_DEFAULT);
				MgraColor(GraphicsContext, M_COLOR_RED);
				MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_EDGES, 0, M_DEFAULT);
				MgraControl(GraphicsContext, M_DRAW_OFFSET_X, 0);
				MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, 0);
			}
			else
			{
				CircleFind = false;
				sErr += "Failed to find circle, No :" + std::to_string(i);
			}
		}

		if (CircleFind)
		{
			_Point point_Center;
			point_Center.X = (ResultLists.at(0).X + ResultLists.at(1).X + ResultLists.at(2).X + ResultLists.at(3).X) / 4.0;
			point_Center.Y = (ResultLists.at(0).Y + ResultLists.at(1).Y + ResultLists.at(2).Y + ResultLists.at(3).Y) / 4.0;
			ResultLists.emplace_back(static_cast<float>(point_Center.X), static_cast<float>(point_Center.Y), static_cast<float>(0));
			//画结果图
			MIL_INT XStart[2], YStart[2], XEnd[2], YEnd[2];
			int crossWidth = 50;
			int brushSize = 47; // must be odd value: 1,3,5,7
			XStart[0] = point_Center.X - crossWidth;
			YStart[0] = point_Center.Y;
			XEnd[0] = point_Center.X + crossWidth;
			YEnd[0] = point_Center.Y;

			XStart[1] = point_Center.X;
			YStart[1] = point_Center.Y - crossWidth;
			XEnd[1] = point_Center.X;
			YEnd[1] = point_Center.Y + crossWidth;
			MgraColor(GraphicsContext, M_COLOR_GREEN);
			MgraControl(GraphicsContext, M_LINE_THICKNESS, brushSize);
			MgraLines(GraphicsContext, ImageOut, 2, XStart, YStart, XEnd, YEnd, M_DEFAULT);

			ImageCenterFind = true;
		}

		if (ImageCenterFind)
		{
			float angle, distance;
			_Point point_img_Center;
			_Point point_A, point_B, point_C, point_D;
			point_A.X = ResultLists.at(0).X;
			point_A.Y = ResultLists.at(0).Y;
			point_B.X = ResultLists.at(2).X;
			point_B.Y = ResultLists.at(2).Y;
			point_C.X = ResultLists.back().X;
			point_C.Y = ResultLists.back().Y;
			point_img_Center.X = 2448 / 2.0;
			point_img_Center.Y = 2048 / 2.0;

			fSocketAngle = Calculate_Angle_Points(point_A, point_B);
			fdistance = sqrt(pow(point_C.X - point_img_Center.X, 2) + pow(point_C.Y - point_img_Center.Y, 2));
			deltaX = point_C.X - point_img_Center.X;
			deltaY = point_C.Y - point_img_Center.Y;
			//画结果图
			MIL_INT XStart[2], YStart[2], XEnd[2], YEnd[2];
			int crossWidth = 100;
			int brushSize = 47; // must be odd value: 1,3,5,7
			XStart[0] = point_img_Center.X - crossWidth;
			YStart[0] = point_img_Center.Y;
			XEnd[0] = point_img_Center.X + crossWidth;
			YEnd[0] = point_img_Center.Y;

			XStart[1] = point_img_Center.X;
			YStart[1] = point_img_Center.Y - crossWidth;
			XEnd[1] = point_img_Center.X;
			YEnd[1] = point_img_Center.Y + crossWidth;
			MgraColor(GraphicsContext, M_COLOR_BLUE);
			MgraControl(GraphicsContext, M_LINE_THICKNESS, brushSize);
			MgraLines(GraphicsContext, ImageOut, 2, XStart, YStart, XEnd, YEnd, M_DEFAULT);
		}

	}
	catch (const std::exception& ex) {
		sErr += ex.what();
	}
	if (GraphicsContext != M_NULL)
	{
		MgraFree(GraphicsContext);
	}
	if (ROIImage != M_NULL) {
		MbufFree(ROIImage);
	}
	if (ClonedImage != M_NULL) {
		MbufFree(ClonedImage);
	}
	if (MmfContext_Model != M_NULL) {
		MmodFree(MmfContext_Model);
	}
	if (MetContextD != M_NULL) {
		MmetFree(MetContextD);
	}
	if (MmfContext_Circle != M_NULL) {
		MmodFree(MmfContext_Circle);
	}
	if (ResultContext_Model != M_NULL) {
		MmodFree(ResultContext_Model);
	}
	if (MetRusult != M_NULL) {
		MmetFree(MetRusult);
	}
	if (ResultContext_Circle != M_NULL) {
		MmodFree(ResultContext_Circle);
	}
	return sErr;
}
std::string VisionManager::ExecuteButtomCamerCircle(MIL_ID MSystem, MIL_ID MImage, MIL_ID & ImageOut, const std::string MMFFilename_Model, const std::string MMFFilename_Circle_Model, const std::vector<MilRect> RectROI_Cross, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, std::vector<PointXYA>& ResultCircleLists, float & fdistance, float & fSocketAngle, float & deltaX, float & deltaY)
{
	std::string sErr = "";
	bool ModelFind = false;
	bool CircleFind = false;
	bool CrossFind = false;
	bool ImageCenterFind = false;
	ResultLists.clear();
	ResultCircleLists.clear();
	MIL_ID ClonedImage = M_NULL;
	MIL_ID MmfContext_Model = M_NULL;
	MIL_ID MmfContext_Circle = M_NULL;
	MIL_ID ResultContext_Model = M_NULL;
	MIL_ID ResultContext_Circle = M_NULL;
	MIL_ID ROIImage = M_NULL;
	MIL_ID MetContextD = M_NULL;
	MIL_ID MetRusult = M_NULL;
	MIL_ID GraphicsContext = M_NULL;

	try
	{
		if (MImage == M_NULL)
		{
			throw std::runtime_error("Invalid image or null");
		}
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);
		MIL_INT img_W;
		MIL_INT img_H;
		MbufInquire(ClonedImage, M_SIZE_X, &img_W);
		MbufInquire(ClonedImage, M_SIZE_Y, &img_H);
		MbufAllocColor(MSystem, 3, img_W, img_H, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_DISP, &ImageOut);
		MimConvert(ClonedImage, ImageOut, M_L_TO_RGB);
		MgraAlloc(MSystem, &GraphicsContext);

		//计算十字
		if (true)
		{
			MmodRestoreA((MMFFilename_Model.data()), MSystem, M_DEFAULT, &MmfContext_Circle);
			MmodPreprocess(MmfContext_Circle, M_DEFAULT);
			MmodAllocResult(MSystem, M_DEFAULT, &ResultContext_Circle);
			for (int i = 0; i < RectROI_Cross.size(); i++)
			{
				if (ROIImage != M_NULL)
				{
					MbufFree(ROIImage);
				}
				MIL_INT  ResultCount = 0;
				MbufChild2d(ClonedImage, RectROI_Cross.at(i).X, RectROI_Cross.at(i).Y, RectROI_Cross.at(i).W, RectROI_Cross.at(i).H, &ROIImage);
				MmodFind(MmfContext_Circle, ROIImage, ResultContext_Circle);
				MmodGetResult(ResultContext_Circle, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);
				if (ResultCount == 1)
				{
					CrossFind = true;
					double temX = 0.0;
					double temY = 0.0;
					double temRadius = 0.0;
					MmodGetResult(ResultContext_Circle, 0, M_POSITION_X, &temX);
					MmodGetResult(ResultContext_Circle, 0, M_POSITION_Y, &temY);
					MmodGetResult(ResultContext_Circle, 0, M_RADIUS, &temRadius);

					temX += RectROI_Cross.at(i).X;
					temY += RectROI_Cross.at(i).Y;

					ResultLists.emplace_back(static_cast<float>(temX), static_cast<float>(temY), static_cast<float>(temRadius));

					MgraControl(GraphicsContext, M_DRAW_OFFSET_X, -RectROI_Cross.at(i).X);
					MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, -RectROI_Cross.at(i).Y);
					MgraColor(GraphicsContext, M_COLOR_GREEN);
					MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_POSITION, 0, M_DEFAULT);
					MgraColor(GraphicsContext, M_COLOR_GREEN);
					MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_BOX, 0, M_DEFAULT);
					MgraColor(GraphicsContext, M_COLOR_RED);
					MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_EDGES, 0, M_DEFAULT);
					MgraControl(GraphicsContext, M_DRAW_OFFSET_X, 0);
					MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, 0);
				}
				else
				{
					CrossFind = false;
					sErr += "Failed to find circle, No :" + std::to_string(i);
				}
			}
		}

		if (CrossFind)
		{
			_Point point_Center;
			point_Center.X = (ResultLists.at(0).X + ResultLists.at(1).X + ResultLists.at(2).X + ResultLists.at(3).X) / 4.0;
			point_Center.Y = (ResultLists.at(0).Y + ResultLists.at(1).Y + ResultLists.at(2).Y + ResultLists.at(3).Y) / 4.0;
			ResultLists.emplace_back(static_cast<float>(point_Center.X), static_cast<float>(point_Center.Y), static_cast<float>(0));
			//画结果图
			MIL_INT XStart[2], YStart[2], XEnd[2], YEnd[2];
			int crossWidth = 50;
			int brushSize = 47; // must be odd value: 1,3,5,7
			XStart[0] = point_Center.X - crossWidth;
			YStart[0] = point_Center.Y;
			XEnd[0] = point_Center.X + crossWidth;
			YEnd[0] = point_Center.Y;

			XStart[1] = point_Center.X;
			YStart[1] = point_Center.Y - crossWidth;
			XEnd[1] = point_Center.X;
			YEnd[1] = point_Center.Y + crossWidth;
			MgraColor(GraphicsContext, M_COLOR_GREEN);
			MgraControl(GraphicsContext, M_LINE_THICKNESS, brushSize);
			MgraLines(GraphicsContext, ImageOut, 2, XStart, YStart, XEnd, YEnd, M_DEFAULT);

			ImageCenterFind = true;
		}

		//计算四个圆点
		if (true)
		{
			MmodRestoreA((MMFFilename_Circle_Model.data()), MSystem, M_DEFAULT, &MmfContext_Circle);
			MmodPreprocess(MmfContext_Circle, M_DEFAULT);
			MmodAllocResult(MSystem, M_DEFAULT, &ResultContext_Circle);
			for (int i = 0; i < RectROI_Circle.size(); i++)
			{
				if (ROIImage != M_NULL)
				{
					MbufFree(ROIImage);
				}
				MIL_INT  ResultCount = 0;
				MbufChild2d(ClonedImage, RectROI_Circle.at(i).X, RectROI_Circle.at(i).Y, RectROI_Circle.at(i).W, RectROI_Circle.at(i).H, &ROIImage);
				MmodFind(MmfContext_Circle, ROIImage, ResultContext_Circle);
				MmodGetResult(ResultContext_Circle, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);
				if (ResultCount == 1)
				{
					CircleFind = true;
					double temX = 0.0;
					double temY = 0.0;
					double temRadius = 0.0;
					MmodGetResult(ResultContext_Circle, 0, M_POSITION_X, &temX);
					MmodGetResult(ResultContext_Circle, 0, M_POSITION_Y, &temY);
					MmodGetResult(ResultContext_Circle, 0, M_RADIUS, &temRadius);

					temX += RectROI_Circle.at(i).X;
					temY += RectROI_Circle.at(i).Y;

					ResultCircleLists.emplace_back(static_cast<float>(temX), static_cast<float>(temY), static_cast<float>(temRadius));

					MgraControl(GraphicsContext, M_DRAW_OFFSET_X, -RectROI_Circle.at(i).X);
					MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, -RectROI_Circle.at(i).Y);
					MgraColor(GraphicsContext, M_COLOR_BLUE);
					MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_POSITION, 0, M_DEFAULT);
					MgraColor(GraphicsContext, M_COLOR_BLUE);
					MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_BOX, 0, M_DEFAULT);
					MgraColor(GraphicsContext, M_COLOR_RED);
					MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_EDGES, 0, M_DEFAULT);
					MgraControl(GraphicsContext, M_DRAW_OFFSET_X, 0);
					MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, 0);
				}
				else
				{
					CircleFind = false;
					sErr += "Failed to find circle, No :" + std::to_string(i);
				}
			}
		}
		
		if (CircleFind)
		{
			_Point point_Center;
			point_Center.X = (ResultCircleLists.at(0).X + ResultCircleLists.at(1).X + ResultCircleLists.at(2).X + ResultCircleLists.at(3).X) / 4.0;
			point_Center.Y = (ResultCircleLists.at(0).Y + ResultCircleLists.at(1).Y + ResultCircleLists.at(2).Y + ResultCircleLists.at(3).Y) / 4.0;
			ResultCircleLists.emplace_back(static_cast<float>(point_Center.X), static_cast<float>(point_Center.Y), static_cast<float>(0));
			//画结果图
			MIL_INT XStart[2], YStart[2], XEnd[2], YEnd[2];
			int crossWidth = 50;
			int brushSize = 47; // must be odd value: 1,3,5,7
			XStart[0] = point_Center.X - crossWidth;
			YStart[0] = point_Center.Y;
			XEnd[0] = point_Center.X + crossWidth;
			YEnd[0] = point_Center.Y;

			XStart[1] = point_Center.X;
			YStart[1] = point_Center.Y - crossWidth;
			XEnd[1] = point_Center.X;
			YEnd[1] = point_Center.Y + crossWidth;
			MgraColor(GraphicsContext, M_COLOR_BLUE);
			MgraControl(GraphicsContext, M_LINE_THICKNESS, brushSize);
			MgraLines(GraphicsContext, ImageOut, 2, XStart, YStart, XEnd, YEnd, M_DEFAULT);

			ImageCenterFind = true;
		}

		if (ImageCenterFind)
		{
			float angle, distance;
			_Point point_img_Center;
			_Point point_A, point_B, point_C, point_D;
			point_A.X = ResultLists.back().X;
			point_A.Y = ResultLists.back().Y;
			point_B.X = ResultCircleLists.back().X;
			point_B.Y = ResultCircleLists.back().Y;
			point_C.X = ResultCircleLists.at(0).X;
			point_C.Y = ResultCircleLists.at(0).Y;
			point_D.X = ResultCircleLists.at(2).X;
			point_D.Y = ResultCircleLists.at(2).Y;
			//point_img_Center.X = 2448 / 2.0;
			//point_img_Center.Y = 2048 / 2.0;

			fSocketAngle = Calculate_Angle_Points(point_C, point_D);
			fdistance = sqrt(pow(point_B.X - point_A.X, 2) + pow(point_B.Y - point_A.Y, 2));
			deltaX = point_B.X - point_A.X;
			deltaY = point_B.Y - point_A.Y;
			//画结果图
			//MIL_INT XStart[2], YStart[2], XEnd[2], YEnd[2];
			//int crossWidth = 100;
			//int brushSize = 47; // must be odd value: 1,3,5,7
			//XStart[0] = point_img_Center.X - crossWidth;
			//YStart[0] = point_img_Center.Y;
			//XEnd[0] = point_img_Center.X + crossWidth;
			//YEnd[0] = point_img_Center.Y;

			//XStart[1] = point_img_Center.X;
			//YStart[1] = point_img_Center.Y - crossWidth;
			//XEnd[1] = point_img_Center.X;
			//YEnd[1] = point_img_Center.Y + crossWidth;
			//MgraColor(GraphicsContext, M_COLOR_BLUE);
			//MgraControl(GraphicsContext, M_LINE_THICKNESS, brushSize);
			//MgraLines(GraphicsContext, ImageOut, 2, XStart, YStart, XEnd, YEnd, M_DEFAULT);
		}

	}
	catch (const std::exception& ex) {
		sErr += ex.what();
	}
	if (GraphicsContext != M_NULL)
	{
		MgraFree(GraphicsContext);
	}
	if (ROIImage != M_NULL) {
		MbufFree(ROIImage);
	}
	if (ClonedImage != M_NULL) {
		MbufFree(ClonedImage);
	}
	if (MmfContext_Model != M_NULL) {
		MmodFree(MmfContext_Model);
	}
	if (MetContextD != M_NULL) {
		MmetFree(MetContextD);
	}
	if (MmfContext_Circle != M_NULL) {
		MmodFree(MmfContext_Circle);
	}
	if (ResultContext_Model != M_NULL) {
		MmodFree(ResultContext_Model);
	}
	if (MetRusult != M_NULL) {
		MmetFree(MetRusult);
	}
	if (ResultContext_Circle != M_NULL) {
		MmodFree(ResultContext_Circle);
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

std::string VisionManager::ExecuteBottomCameraResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, std::string strMCOFilePath, const std::string MMFFilename_Model
	, const std::string METFilename_Model, const std::string MMFFilename_Circle, const MilMetIndex MetIndex, const std::vector<MilRect> RectROI_Circle
	, std::vector<PointXYA>& ResultLists, float &fdistance, std::string &strBarCode)
{
	std::string sErr = "";
	bool BarcodeFind = false;
	bool ModelFind = false;
	bool CircleFind = false;
	ResultLists.clear();
	MIL_ID ClonedImage = M_NULL;
	MIL_ID ResultContext_BarCode = M_NULL;
	MIL_ID McoContext = M_NULL;
	MIL_ID MmfContext_Model = M_NULL;
	MIL_ID MmfContext_Circle = M_NULL;
	MIL_ID ResultContext_Model = M_NULL;
	MIL_ID ResultContext_Circle = M_NULL;
	MIL_ID ROIImage = M_NULL;
	MIL_ID MetContextD = M_NULL;
	MIL_ID MetRusult = M_NULL;
	MIL_ID GraphicsContext = M_NULL;
	try 
	{	
		if (MImage == M_NULL) 
		{
			throw std::runtime_error("Invalid image or null");
		}
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);
		MIL_INT img_W;
		MIL_INT img_H;
		MbufInquire(ClonedImage, M_SIZE_X, &img_W);
		MbufInquire(ClonedImage, M_SIZE_Y, &img_H);
		MbufAllocColor(MSystem, 3, img_W, img_H, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_DISP, &ImageOut);
		MimConvert(ClonedImage, ImageOut, M_L_TO_RGB);
		MgraAlloc(MSystem, &GraphicsContext);

		// Find DUT BarCode
		if (true)
		{
			MIL_STRING String0;
			MIL_INT BarcodeStatus = 0;
			McodeAllocResult(MSystem, M_DEFAULT, &ResultContext_BarCode);
			McodeRestoreA(strMCOFilePath, MSystem, M_DEFAULT, &McoContext);
			McodeRead(McoContext, ClonedImage, ResultContext_BarCode);
			McodeGetResult(ResultContext_BarCode, M_GENERAL, M_GENERAL, M_STATUS + M_TYPE_MIL_INT, &BarcodeStatus);
			if (BarcodeStatus == M_STATUS_READ_OK)
			{
				BarcodeFind = true;
				/* Get decoded string. */
				McodeGetResult(ResultContext_BarCode, 0, M_DEFAULT, M_STRING, String0);
				strBarCode = String0.c_str();

				MgraColor(GraphicsContext, M_COLOR_GREEN);
				McodeDraw(GraphicsContext, ResultContext_BarCode, ImageOut, M_DRAW_BOX, M_DEFAULT, M_GENERAL, M_DEFAULT);
				MgraColor(GraphicsContext, M_COLOR_RED);
				McodeDraw(GraphicsContext, ResultContext_BarCode, ImageOut, M_DRAW_CODE, M_DEFAULT, M_GENERAL, M_DEFAULT);
			}
			else
			{
				BarcodeFind = false;
				sErr = "not find barcode";
			}
		}	

		//定位长方形中心
		if (BarcodeFind)
		{
			// 模板匹配找中心
			double mmfX = 0.0;
			double mmfY = 0.0;
			double mmfAngle = 0.0;
			MIL_INT ResultCount = 0;
			MmodRestoreA((MMFFilename_Model.data()), MSystem, M_DEFAULT, &MmfContext_Model);
			MmodPreprocess(MmfContext_Model, M_DEFAULT);
			MmodAllocResult(MSystem, M_DEFAULT, &ResultContext_Model);
			MmodFind(MmfContext_Model, ClonedImage, ResultContext_Model);
			MmodGetResult(ResultContext_Model, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);
			if (ResultCount == 1) 
			{
				ModelFind = true;
				MmodGetResult(ResultContext_Model, 0, M_POSITION_X, &mmfX);
				MmodGetResult(ResultContext_Model, 0, M_POSITION_Y, &mmfY);
				MmodGetResult(ResultContext_Model, 0, M_ANGLE, &mmfAngle);

				//画结果图
				MgraColor(GraphicsContext, M_COLOR_BLUE);
				MmodDraw(GraphicsContext, ResultContext_Model, ImageOut, M_DRAW_POSITION, 0, M_DEFAULT);
				MgraColor(GraphicsContext, M_COLOR_RED);
				MmodDraw(GraphicsContext, ResultContext_Model, ImageOut, M_DRAW_EDGES, 0, M_DEFAULT);
			}
			else 
			{
				sErr += "Failed to find Model";
				ModelFind = false;
			}
			if (ModelFind) 
			{
				// 载入MET 设置MET中心，计算
				MmetRestoreA(METFilename_Model.data(), MSystem, M_DEFAULT, &MetContextD);
				MmetAllocResult(MSystem, M_DEFAULT, &MetRusult);

				// 将模板结果设置到met 根据序号来确定设置的位置
				MmetSetPosition(MetContextD, M_FEATURE_INDEX(MetIndex.SetPositionIndex), M_POSITION, mmfX, mmfY, mmfAngle, M_DEFAULT, M_DEFAULT);
				// 计算
				MmetCalculate(MetContextD, MImage, MetRusult, M_DEFAULT);
				// 设置以图片坐标为原点输出
				MmetControl(MetRusult, M_GENERAL, M_OUTPUT_FRAME, M_IMAGE_FRAME);
				//画结果图
				MgraColor(GraphicsContext, M_COLOR_GREEN);
				MmetDraw(GraphicsContext, MetRusult, ImageOut, M_DRAW_FEATURE, M_DEFAULT, M_DEFAULT);
				// 获取结果
				double tempx = -100;
				double tempy = -100;
				double tempA = 0;
				MmetGetResult(MetRusult, M_FEATURE_LABEL(MetIndex.Result_PositionXIndex), M_POSITION_X, &tempx);
				MmetGetResult(MetRusult, M_FEATURE_LABEL(MetIndex.Result_PositionYIndex), M_POSITION_Y, &tempy);
				MmetGetResult(MetRusult, M_FEATURE_LABEL(MetIndex.Result_AngleIndex), M_ANGLE, &tempA);
				ResultLists.emplace_back(static_cast<float>(tempx), static_cast<float>(tempy), static_cast<float>(tempA));
			}
		}

		//识别4个销钉圆
		if (ModelFind)
		{
			// Find circle
			MmodRestoreA((MMFFilename_Circle.data()), MSystem, M_DEFAULT, &MmfContext_Circle);
			MmodPreprocess(MmfContext_Circle, M_DEFAULT);
			MmodAllocResult(MSystem, M_DEFAULT, &ResultContext_Circle);
			for (int i = 0; i < RectROI_Circle.size(); i++)
			{
				if (ROIImage != M_NULL)
				{
					MbufFree(ROIImage);					
				}
				MIL_INT  ResultCount = 0;
				MbufChild2d(ClonedImage, RectROI_Circle.at(i).X, RectROI_Circle.at(i).Y, RectROI_Circle.at(i).W, RectROI_Circle.at(i).H, &ROIImage);
				MmodFind(MmfContext_Circle, ROIImage, ResultContext_Circle);
				MmodGetResult(ResultContext_Circle, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);
				if (ResultCount == 1)
				{
					CircleFind = true;
					double temX = 0.0;
					double temY = 0.0;
					double temRadius = 0.0;
					MmodGetResult(ResultContext_Circle, 0, M_POSITION_X, &temX);
					MmodGetResult(ResultContext_Circle, 0, M_POSITION_Y, &temY);
					MmodGetResult(ResultContext_Circle, 0, M_RADIUS, &temRadius);

					temX += RectROI_Circle.at(i).X;
					temY += RectROI_Circle.at(i).Y;

					ResultLists.emplace_back(static_cast<float>(temX), static_cast<float>(temY), static_cast<float>(temRadius));

					MgraControl(GraphicsContext, M_DRAW_OFFSET_X, -RectROI_Circle.at(i).X);
					MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, -RectROI_Circle.at(i).Y);
					MgraColor(GraphicsContext, M_COLOR_GREEN);
					MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_POSITION, 0, M_DEFAULT);
					MgraColor(GraphicsContext, M_COLOR_GREEN);
					MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_BOX, 0, M_DEFAULT);
					MgraColor(GraphicsContext, M_COLOR_RED);
					MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_EDGES, 0, M_DEFAULT);
					MgraControl(GraphicsContext, M_DRAW_OFFSET_X, 0);
					MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, 0);
				}
				else
				{
					CircleFind = false;
					sErr += "Failed to find circle, No :" + std::to_string(i);
				}
			}
		}

		//计算4个销钉圆的中心点
		if (CircleFind)
		{
			if (ResultLists.size() >= 5)
			{
				float angle;
				_Point point_A, point_B, point_C;
				_Point p1, p2;
				p1.X = ResultLists.at(1).X;
				p1.Y = ResultLists.at(1).Y;
				p2.X = ResultLists.at(3).X;
				p2.Y = ResultLists.at(3).Y;
				Line line1 = createLineFromPoints(p1, p2);
				p1.X = ResultLists.at(2).X;
				p1.Y = ResultLists.at(2).Y;
				p2.X = ResultLists.at(4).X;
				p2.Y = ResultLists.at(4).Y;
				Line line2 = createLineFromPoints(p1, p2);
				point_C = findIntersection(line1, line2);

				point_A.X = (ResultLists.at(1).X + ResultLists.at(2).X) / 2.0;
				point_A.Y = (ResultLists.at(1).Y + ResultLists.at(2).Y) / 2.0;
				point_B.X = (ResultLists.at(3).X + ResultLists.at(4).X) / 2.0;
				point_B.Y = (ResultLists.at(3).Y + ResultLists.at(4).Y) / 2.0;
				angle = Calculate_Angle_Points(point_A, point_B);
				ResultLists.emplace_back(static_cast<float>(point_C.X), static_cast<float>(point_C.Y), static_cast<float>(angle));
				fdistance = sqrt(pow(point_C.X - ResultLists.at(0).X, 2) + pow(point_C.Y - ResultLists.at(0).Y, 2));
				//画结果图
				MIL_INT XStart[2], YStart[2], XEnd[2], YEnd[2];
				int crossWidth = 200;
				int brushSize = 5; // must be odd value: 1,3,5,7
				XStart[0] = point_C.X - crossWidth;
				YStart[0] = point_C.Y;
				XEnd[0] = point_C.X + crossWidth;
				YEnd[0] = point_C.Y;

				XStart[1] = point_C.X;
				YStart[1] = point_C.Y - crossWidth;
				XEnd[1] = point_C.X;
				YEnd[1] = point_C.Y + crossWidth;
				MgraColor(GraphicsContext, M_COLOR_BLUE);
				MgraControl(GraphicsContext, M_LINE_THICKNESS, brushSize);				
				MgraLines(GraphicsContext, ImageOut, 2, XStart, YStart, XEnd, YEnd, M_DEFAULT);
				MIL_DOUBLE X_Start, Y_Start, X_End, Y_End;
				X_Start = ResultLists.at(0).X;
				Y_Start = ResultLists.at(0).Y;
				X_End = point_C.X;
				Y_End = point_C.Y;
				MgraColor(GraphicsContext, M_COLOR_GREEN);
				MgraLine(GraphicsContext, ImageOut, X_Start, Y_Start, X_End, Y_End);
				X_Start = point_A.X;
				Y_Start = point_A.Y;
				X_End = point_B.X;
				Y_End = point_B.Y;
				MgraLine(GraphicsContext, ImageOut, X_Start, Y_Start, X_End, Y_End);
			}
			else
			{
				sErr += "Failed to find Model or Circle";
			}
		}	
	}
	catch (const std::exception& ex) {
		sErr += ex.what();
	}
	if (GraphicsContext != M_NULL)
	{
		MgraFree(GraphicsContext);
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
	if (MmfContext_Model != M_NULL) {
		MmodFree(MmfContext_Model);
	}
	if (MetContextD != M_NULL) {
		MmetFree(MetContextD);
	}
	if (MmfContext_Circle != M_NULL) {
		MmodFree(MmfContext_Circle);
	}
	if (ResultContext_BarCode != M_NULL) {
		McodeFree(ResultContext_BarCode);
	}	
	if (ResultContext_Model != M_NULL) {
		MmodFree(ResultContext_Model);
	}	
	if (MetRusult != M_NULL) {
		MmetFree(MetRusult);
	}
	if (ResultContext_Circle != M_NULL) {
		MmodFree(ResultContext_Circle);
	}
	return sErr;
}

std::string VisionManager::ExecuteTopCameraResult(MIL_ID MSystem, MIL_ID MImage, MIL_ID& ImageOut, const std::string MMFFilename_Model, const std::string METFilename_Model
	, const std::string MMFFilename_Circle, const MilMetIndex MetIndex, const std::vector<MilRect> RectROI_Circle, std::vector<PointXYA>& ResultLists, float &fdistance, float &fSocketAngle)
{
	std::string sErr = "";
	bool ModelFind = false;
	bool CircleFind = false;
	ResultLists.clear();
	MIL_ID ClonedImage = M_NULL;
	MIL_ID MmfContext_Model = M_NULL;
	MIL_ID MmfContext_Circle = M_NULL;
	MIL_ID ResultContext_Model = M_NULL;
	MIL_ID ResultContext_Circle = M_NULL;
	MIL_ID ROIImage = M_NULL;
	MIL_ID MetContextD = M_NULL;
	MIL_ID MetRusult = M_NULL;
	MIL_ID GraphicsContext = M_NULL;
	try
	{
		if (MImage == M_NULL)
		{
			throw std::runtime_error("Invalid image or null");
		}
		MbufClone(MImage, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_DEFAULT, M_COPY_SOURCE_DATA, &ClonedImage);
		MIL_INT img_W;
		MIL_INT img_H;
		MbufInquire(ClonedImage, M_SIZE_X, &img_W);
		MbufInquire(ClonedImage, M_SIZE_Y, &img_H);
		MbufAllocColor(MSystem, 3, img_W, img_H, 8 + M_UNSIGNED, M_IMAGE + M_PROC + M_DISP, &ImageOut);
		MimConvert(ClonedImage, ImageOut, M_L_TO_RGB);
		MgraAlloc(MSystem, &GraphicsContext);
	
		//定位B2B中心
		if (true)
		{
			// 模板匹配找中心
			double mmfX = 0.0;
			double mmfY = 0.0;
			double mmfAngle = 0.0;
			MIL_INT ResultCount = 0;
			MmodRestoreA((MMFFilename_Model.data()), MSystem, M_DEFAULT, &MmfContext_Model);
			MmodPreprocess(MmfContext_Model, M_DEFAULT);
			MmodAllocResult(MSystem, M_DEFAULT, &ResultContext_Model);
			MmodFind(MmfContext_Model, ClonedImage, ResultContext_Model);
			MmodGetResult(ResultContext_Model, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);
			if (ResultCount == 1)
			{
				ModelFind = true;
				MmodGetResult(ResultContext_Model, 0, M_POSITION_X, &mmfX);
				MmodGetResult(ResultContext_Model, 0, M_POSITION_Y, &mmfY);
				MmodGetResult(ResultContext_Model, 0, M_ANGLE, &mmfAngle);

				//画结果图
				MgraColor(GraphicsContext, M_COLOR_BLUE);
				MmodDraw(GraphicsContext, ResultContext_Model, ImageOut, M_DRAW_POSITION, 0, M_DEFAULT);
				MgraColor(GraphicsContext, M_COLOR_RED);
				MmodDraw(GraphicsContext, ResultContext_Model, ImageOut, M_DRAW_EDGES, 0, M_DEFAULT);

				//将结果存入Point XYA动态数组中
				ResultLists.emplace_back(static_cast<float>(mmfX), static_cast<float>(mmfY), static_cast<float>(mmfAngle));
			}
			else
			{
				sErr += "Failed to find Model";
				ModelFind = false;
			}
			//if (ModelFind)//新版本不执行这一段
			//{
			//	// 载入MET 设置MET中心，计算
			//	MmetRestoreA(METFilename_Model.data(), MSystem, M_DEFAULT, &MetContextD);
			//	MmetAllocResult(MSystem, M_DEFAULT, &MetRusult);

			//	// 将模板结果设置到met 根据序号来确定设置的位置
			//	MmetSetPosition(MetContextD, M_FEATURE_INDEX(MetIndex.SetPositionIndex), M_POSITION, mmfX, mmfY, mmfAngle, M_DEFAULT, M_DEFAULT);
			//	// 计算
			//	MmetCalculate(MetContextD, MImage, MetRusult, M_DEFAULT);
			//	// 设置以图片坐标为原点输出
			//	MmetControl(MetRusult, M_GENERAL, M_OUTPUT_FRAME, M_IMAGE_FRAME);
			//	//画结果图
			//	MgraColor(GraphicsContext, M_COLOR_GREEN);
			//	MmetDraw(GraphicsContext, MetRusult, ImageOut, M_DRAW_FEATURE, M_DEFAULT, M_DEFAULT);
			//	// 获取结果
			//	double tempx = -100;
			//	double tempy = -100;
			//	double tempA = 0;
			//	MmetGetResult(MetRusult, M_FEATURE_LABEL(MetIndex.Result_PositionXIndex), M_POSITION_X, &tempx);
			//	MmetGetResult(MetRusult, M_FEATURE_LABEL(MetIndex.Result_PositionYIndex), M_POSITION_Y, &tempy);
			//	MmetGetResult(MetRusult, M_FEATURE_LABEL(MetIndex.Result_AngleIndex), M_ANGLE, &tempA);
			//	ResultLists.emplace_back(static_cast<float>(tempx), static_cast<float>(tempy), static_cast<float>(tempA));
			//}
		}

		//识别2个销钉圆
		if (ModelFind)
		{
			// Find circle
			MmodRestoreA((MMFFilename_Circle.data()), MSystem, M_DEFAULT, &MmfContext_Circle);
			MmodPreprocess(MmfContext_Circle, M_DEFAULT);
			MmodAllocResult(MSystem, M_DEFAULT, &ResultContext_Circle);
			for (int i = 0; i < RectROI_Circle.size(); i++)
			{
				if (ROIImage != M_NULL)
				{
					MbufFree(ROIImage);
				}
				MIL_INT  ResultCount = 0;
				MbufChild2d(ClonedImage, RectROI_Circle.at(i).X, RectROI_Circle.at(i).Y, RectROI_Circle.at(i).W, RectROI_Circle.at(i).H, &ROIImage);
				MmodFind(MmfContext_Circle, ROIImage, ResultContext_Circle);
				MmodGetResult(ResultContext_Circle, M_DEFAULT, M_NUMBER + M_TYPE_MIL_INT, &ResultCount);
				if (ResultCount == 1)
				{
					CircleFind = true;
					double temX = 0.0;
					double temY = 0.0;
					double temRadius = 0.0;
					MmodGetResult(ResultContext_Circle, 0, M_POSITION_X, &temX);
					MmodGetResult(ResultContext_Circle, 0, M_POSITION_Y, &temY);
					MmodGetResult(ResultContext_Circle, 0, M_RADIUS, &temRadius);

					temX += RectROI_Circle.at(i).X;
					temY += RectROI_Circle.at(i).Y;

					ResultLists.emplace_back(static_cast<float>(temX), static_cast<float>(temY), static_cast<float>(temRadius));

					MgraControl(GraphicsContext, M_DRAW_OFFSET_X, -RectROI_Circle.at(i).X);
					MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, -RectROI_Circle.at(i).Y);
					MgraColor(GraphicsContext, M_COLOR_GREEN);
					MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_POSITION, 0, M_DEFAULT);
					MgraColor(GraphicsContext, M_COLOR_GREEN);
					MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_BOX, 0, M_DEFAULT);
					MgraColor(GraphicsContext, M_COLOR_RED);
					MmodDraw(GraphicsContext, ResultContext_Circle, ImageOut, M_DRAW_EDGES, 0, M_DEFAULT);
					MgraControl(GraphicsContext, M_DRAW_OFFSET_X, 0);
					MgraControl(GraphicsContext, M_DRAW_OFFSET_Y, 0);
				}
				else
				{
					CircleFind = false;
					sErr += "Failed to find circle, No :" + std::to_string(i);
				}
			}
		}

		//计算4个销钉圆的中心点
		if (CircleFind)
		{
			if (ResultLists.size() >= 3)
			{
				float angle;
				_Point point_A, point_B, point_C, point_D;
				point_A.X = ResultLists.at(0).X;
				point_A.Y = ResultLists.at(0).Y;
				point_B.X = (ResultLists.at(1).X + ResultLists.at(2).X) / 2.0;
				point_B.Y = (ResultLists.at(1).Y + ResultLists.at(2).Y) / 2.0;
				point_C.X = ResultLists.at(1).X;
				point_C.Y = ResultLists.at(1).Y;
				point_D.X = ResultLists.at(2).X;
				point_D.Y = ResultLists.at(2).Y;

				angle = Calculate_Angle_Points(point_C, point_D);
				fSocketAngle = Calculate_Angle_Points(point_A, point_B);
				ResultLists.emplace_back(static_cast<float>(point_B.X), static_cast<float>(point_B.Y), static_cast<float>(angle));
				fdistance = sqrt(pow(point_B.X - point_A.X, 2) + pow(point_B.Y - point_A.Y, 2));
				//画结果图
				MIL_INT XStart[2], YStart[2], XEnd[2], YEnd[2];
				int crossWidth = 50;
				int brushSize = 5; // must be odd value: 1,3,5,7
				XStart[0] = point_B.X - crossWidth;
				YStart[0] = point_B.Y;
				XEnd[0] = point_B.X + crossWidth;
				YEnd[0] = point_B.Y;

				XStart[1] = point_B.X;
				YStart[1] = point_B.Y - crossWidth;
				XEnd[1] = point_B.X;
				YEnd[1] = point_B.Y + crossWidth;
				MgraColor(GraphicsContext, M_COLOR_BLUE);
				MgraControl(GraphicsContext, M_LINE_THICKNESS, brushSize);
				MgraLines(GraphicsContext, ImageOut, 2, XStart, YStart, XEnd, YEnd, M_DEFAULT);
				MIL_DOUBLE X_Start, Y_Start, X_End, Y_End;
				X_Start = point_C.X;
				Y_Start = point_C.Y;
				X_End = point_D.X;
				Y_End = point_D.Y;
				MgraColor(GraphicsContext, M_COLOR_GREEN);
				MgraLine(GraphicsContext, ImageOut, X_Start, Y_Start, X_End, Y_End);
				X_Start = point_A.X;
				Y_Start = point_A.Y;
				X_End = point_B.X;
				Y_End = point_B.Y;
				MgraColor(GraphicsContext, M_COLOR_GREEN);
				MgraLine(GraphicsContext, ImageOut, X_Start, Y_Start, X_End, Y_End);
			}
			else
			{
				sErr += "Failed to find Model or Circle";
			}
		}
	}
	catch (const std::exception& ex) {
		sErr += ex.what();
	}
	if (GraphicsContext != M_NULL)
	{
		MgraFree(GraphicsContext);
	}
	if (ROIImage != M_NULL) {
		MbufFree(ROIImage);
	}
	if (ClonedImage != M_NULL) {
		MbufFree(ClonedImage);
	}
	if (MmfContext_Model != M_NULL) {
		MmodFree(MmfContext_Model);
	}
	if (MetContextD != M_NULL) {
		MmetFree(MetContextD);
	}
	if (MmfContext_Circle != M_NULL) {
		MmodFree(MmfContext_Circle);
	}
	if (ResultContext_Model != M_NULL) {
		MmodFree(ResultContext_Model);
	}
	if (MetRusult != M_NULL) {
		MmetFree(MetRusult);
	}
	if (ResultContext_Circle != M_NULL) {
		MmodFree(ResultContext_Circle);
	}
	return sErr;
}




