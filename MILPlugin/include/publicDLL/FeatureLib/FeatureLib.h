#ifndef _FEATURELIB_H
#define _FEATURELIB_H

#include "Public.h"

//DLLAPI void STDCALL NormalOCRImage(IplImage* srcImage, IplImage* dstImage);

//字符水平方向上的投影特征
DLLAPI void STDCALL ProjectedHoriHistogram(IplImage* img, int ObjectGray, float* histArray);

//字符垂直方向上的投影特征
DLLAPI void STDCALL ProjectedVertHistogram(IplImage* img, int ObjectGray, float* histArray);

//字符分块LBP统计特征
DLLAPI void STDCALL StatLBPDistribute(IplImage* img, int ObjectGray, int nHeight, int nWidth, float* histArray);

#ifdef UPPROCESS
#ifndef FEATURELIB_IMPLEMENT
#pragma comment(lib, "FeatureLib.lib")
#endif
#endif

#endif  //_FEATURELIB_H
