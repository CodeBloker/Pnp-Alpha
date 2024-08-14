
#ifndef _IMAGEPRE_FILE_H_
#define _IMAGEPRE_FILE_H_

#include "Public.h"

DLLAPI void STDCALL AdaptiveStretchImage(IplImage* srcImage, CvRect rect, float lowValue, float highValue, IplImage* dstImage);

DLLAPI void STDCALL MarkEdgeIplImageForRectBorder(IplImage* srcImage, CvRect rect, int ObjectGray, IplImage* EdgeImage);


DLLAPI void STDCALL TraceEdgeForIplImageModel(IplImage* srcImage, IplImage* MarkImage, int MarkValue, 
											  int hIndex, int wIndex, ListPoint* EdgePoint);

//提取所有边缘中像素点最多的目标边缘，添加到像素点集合中
DLLAPI int STDCALL ExtractMaxEdgePointNumForItem(IplImage* EdgeImage, IplImage* MarkImage, CvRect rect,
												 int ObjectGray, ListPoint* PointList);

//提取所有边缘点，添加到像素点集合中
DLLAPI int STDCALL ExtractAllEdgePointNumForItem(IplImage* EdgeImage, IplImage* MarkImage, CvRect rect,
												 int ObjectGray, ListPoint* PointList);

DLLAPI int STDCALL ExtractAllEdgePointNumForItemVector(IplImage* EdgeImage, IplImage* MarkImage, CvRect rect,int ObjectGray, ListPointVector* PointListVector);

DLLAPI void STDCALL cvAdaptiveDevision(IplImage* srcImage, int hModel, int wModel, int DiffValue, IplImage* dstImage);

DLLAPI void STDCALL cvFixThreshold(IplImage* srcImage, int threshold, IplImage* dstImage);
DLLAPI void STDCALL cvFixThreshold_Inverse(IplImage* srcImage, int threshold, IplImage* dstImage);

DLLAPI void STDCALL OstuThreshold(IplImage* srcImage, IplImage* dstImage);
DLLAPI void STDCALL PathContrastForRectImage(IplImage* srcImage, CvRect rect, int PathValue, IplImage* dstImage);
DLLAPI void STDCALL PathContrastForMarkImage(IplImage* srcImage, IplImage* markImage, int ObjectGray, int PathValue, IplImage* dstImage);

/*********************************************************
              所有滤波类的接口函数
**********************************************************/
//滤除在设置面积范围之外的所有目标物
DLLAPI void STDCALL FilterBlobNoiseForRect(IplImage* srcImage, IplImage* MarkImage, CvRect rect, int Objectgray,
										   int MinMarkNum, int MaxMarkNum, IplImage* dstImage);


DLLAPI void STDCALL FilterBlobNoiseForRectDirection(IplImage* srcImage, IplImage* MarkImage, CvRect rect, int Objectgray,
											int direction, int MinMarkNum, int MaxMarkNum, IplImage* dstImage);

DLLAPI void STDCALL FilterBlobNoiseForRectX(IplImage* srcImage, IplImage* MarkImage, CvRect rect, int Objectgray,
											int MinMarkNum, int MaxMarkNum, IplImage* dstImage);

DLLAPI void STDCALL FilterMaxRegionForRectImage(IplImage* srcImage, IplImage* MarkImage, CvRect rect, 
											int Objectgray, IplImage* dstImage);

DLLAPI void STDCALL FilterEdgeRegionRectList(IplImage* srcImage, IplImage* MarkImage,int Objectgray, CvRect rect, 
											 int MinMarkNum, int MaxMarkNum, IplImage* dstImage, ListRect* rectList, 
											 ListInt* intList);

DLLAPI void STDCALL FilterRegionRectList_Ratio(IplImage* srcImage, IplImage* MarkImage,int Objectgray, int MinMarkNum,
											   int MaxMarkNum, float HeightWidthRatio, IplImage* dstImage, 
											   ListRect* rectList, ListInt* intList);

DLLAPI void STDCALL FilterRegionRectList_Ratio_Line(IplImage* srcImage, IplImage* MarkImage, int Objectgray, int MinMarkNum,
											int MaxMarkNum, float HeightWidthRatio, IplImage* dstImage,
											ListRect* rectList, ListInt* intList);

DLLAPI void STDCALL FilterRegionRectList_Ratio_LinePro(IplImage* srcImage, IplImage* MarkImage, int Objectgray, int MinMarkNum,
											int MaxMarkNum, float HeightWidthRatioMax, float HeightWidthRatioMin, IplImage* dstImage,
											ListRect* rectList, ListInt* intList);

DLLAPI void STDCALL FilterEdgeRegionRectList_Ratio(IplImage* srcImage, IplImage* MarkImage,int Objectgray, int MinMarkNum,
												   int MaxMarkNum, float HeightWidthRatio, IplImage* dstImage, 
												   ListRect* rectList, ListInt* intList);

DLLAPI void STDCALL cvDilationImage(IplImage* srcImage, int hModel, int wModel, int Objectgray, IplImage* dstImage);
DLLAPI void STDCALL cvErosionImage(IplImage* srcImage, int hModel, int wModel, int Objectgray, IplImage* dstImage);

DLLAPI void STDCALL MorphDilationImage(IplImage* srcImage, int Objectgray, IplImage* dstImage);
DLLAPI void STDCALL MorphErosionImage(IplImage* srcImage, int Objectgray, IplImage* dstImage);

DLLAPI bool STDCALL findCircle(string filePath, Rect Postion, CvPointF& CenterPoint, float& radior, string resultFilePath);


#ifdef UPPROCESS
#ifndef IMAGEPRE_IMPLEMENT
#pragma comment(lib, "ImagePre.lib")
#endif
#endif

#endif  //_IMAGEPRE_FILE_H_
