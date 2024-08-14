#pragma once
#ifdef PUBLICDLL_EXPORTS
#define PUBLICDLL_API __declspec(dllexport) 
#else
#define PUBLICDLL_API __declspec(dllimport) 
#endif
//#include "stdafx.h"
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "ImagePre/ImagePre.h"
#include "ListArrayLib/ListArrayLib.h"
#include "GeometryLib/GeometryLib.h"
#include "ImagePre/ImagePre.h"
#include "ObjectLib/ObjectLib.h"
#include "FeatureLib/FeatureLib.h"

//#include "vld/vld.h"

#include <mil.h>
#include <MILDyn/milim.h>

using namespace std;
using namespace cv;

typedef struct tagImageProcessPara
{
	//用于记录当前图像单张的高度和宽度
	volatile int    AdaptiveModel;
	volatile int    DiffValue;
	volatile int    Objectgray;
	volatile int    MinMarkNum;
	volatile int    MaxMarkNum;
	volatile float  HeightWidthRatio;
	volatile float  Compactness;
	volatile int    ErosionFlag;
	volatile int    ErosionModel;
	volatile int    ErosionObjectgray;
	volatile int    DilationModel;
	volatile int    DilationObjectgray;

	volatile int    Objectgray2;
	volatile int    MinMarkNum2;
	volatile int    MaxMarkNum2;
	volatile float  HeightWidthRatio2;

	volatile int    ROIStartX;
	volatile int    ROIStartY;
	volatile int    ROIEndX;
	volatile int    ROIEndY;

	volatile float  StandardAngle;
	volatile float  AngleRange;
	void Init()
	{
		AdaptiveModel = 5;
		DiffValue = 0;
		Objectgray = 255;
		MinMarkNum = 70000;
		MaxMarkNum = 90000;
		HeightWidthRatio = 3;
		Compactness = 0.5;
		ErosionFlag = 0;
		ErosionModel = 1;
		ErosionObjectgray = 0;
		DilationModel = 8;
		DilationObjectgray = 0;
		Objectgray2 = 255;
		MinMarkNum2 = 5;
		MaxMarkNum2 = 150;
		HeightWidthRatio2 = 0.8;

		ROIStartX = ROIStartY = 0;
		ROIEndX = 2447;
		ROIEndY = 2047;
		StandardAngle = 90.0;
		AngleRange = 1.0;
	}
	void InitDot()
	{
		AdaptiveModel = 17;
		DiffValue = 180;
		Objectgray = 255;
		MinMarkNum = 11;
		MaxMarkNum = 150;
		HeightWidthRatio = 3;
		Compactness = 0.5;
		ErosionFlag = 0;
		ErosionModel = 1;
		ErosionObjectgray = 0;
		DilationModel = 8;
		DilationObjectgray = 0;
		Objectgray2 = 255;
		MinMarkNum2 = 30;
		MaxMarkNum2 = 200;
		HeightWidthRatio2 = 0.8;
		ROIStartX = ROIStartY = 0;
		ROIEndX = 2447;
		ROIEndY = 2047;
		StandardAngle = 90.0;
		AngleRange = 1.0;
	}
}ImageProcessPara;

//int PUBLICDLL_API traditionDetecOrg(Mat image, Mat &imgColor, ImageProcessPara imgProcPara, float &degree, cv::Point2f &midPoint);
int PUBLICDLL_API traditionDetec(Mat image, Mat &imgColor, ImageProcessPara imgProcPara, float &degree, cv::Point2f &midPoint);

void PUBLICDLL_API testMilInit();
void PUBLICDLL_API testMilDestruct();
void PUBLICDLL_API testMilInitCopy(MIL_ID MilApplicationT, MIL_ID MilSystemT, MIL_ID MilDisplayT);

int PUBLICDLL_API MilDetec(Mat image, Mat &imgColor, ImageProcessPara imgProcPara, float &degree, cv::Point2f &midPoint);
int PUBLICDLL_API MilDetecDegree(Mat image, Mat &imgColor, ImageProcessPara imgProcPara, float &degree, cv::Point2f &midPoint);


int PUBLICDLL_API dotArrayDetectRaw8(std::string strFilename, int nWidth, int nHeight, ImageProcessPara imgProcPara, float &degree);

//int PUBLICDLL_API dotArrayDetectRaw8Rect(std::string strFilename, int nWidth, int nHeight, ImageProcessPara imgProcPara, cv::RotatedRect &rotated_rect, float &degree);