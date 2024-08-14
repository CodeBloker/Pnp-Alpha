//宏定义文件---定义公用的宏
#ifndef _TRAINITEM_STRUCR_H_
#define _TRAINITEM_STRUCR_H_

#include <LibSVM/SVMStruct.h>

#define MAXOCRNUM     32       //最多字符数目
#define MAXTRAINNUM   10
#define MAXTRAINIMAGENUM  6     

#define MAXCONFIGNUM  100        

 
#define MAXCONFIGTRAINNUM  200        

#define MAXTHREADNUM  20

#define MAXMSGLENGTH  1024*10

#define COLOR_ALL      0
#define COLOR_RED      1
#define COLOR_GREEN    2
#define COLOR_BLUE     3
#define COLOR_GRAY     4

#define MAXIMAGENUM   500     
#define MAXFILEPATH   1024

#define INITPROCESS   0      //任务初始处理
#define PROCESSING    20     //任务处理过程中
#define COMPLETETASK  25     //任务结束处理

typedef struct tagTrainNumPara   
{
	int    trainNum;
	char   trainResult[MAXOCRNUM];
	CvRect trainRect[MAXOCRNUM];

	void Init()
	{
		trainNum = 0;
		memset(trainResult, '\0', MAXOCRNUM*sizeof(char));
		memset(trainRect, 0, MAXOCRNUM*sizeof(CvRect));
	}
}TrainNumPara;

typedef struct tagTrainColorPara     
{
	TrainNumPara  allTrainNum;
	TrainNumPara  otherTrainNum; 

	void Init()
	{
		allTrainNum.Init(); otherTrainNum.Init(); 
	}
}TrainColorPara;

typedef struct tagConfigTrainPara
{	
	int    configTrainFirst;           
	char   configTrainTypeResult[20];	

	void Init()
	{
		configTrainFirst = 0;
		memset(configTrainTypeResult, '\0', 20*sizeof(char));
	}
}ConfigTrainPara;

typedef struct tagConfigTrainNumPara
{           
	//1---用字符AB表示  2 ---用I II表示 3---表示无端位
	char   configTrainType[10];	
	char   configTrainNum[10];	

	void Init()
	{
		memset(configTrainType, '\0', 10*sizeof(char));
		memset(configTrainNum, '\0', 10*sizeof(char));
	}
}ConfigTrainNumPara;


typedef struct tagTrainResultPara
{
	int    allTrainNumFirst;         
	int    allTrainNumMark;          

	int    configTrainFirst;         

	char   allTrainNumResult[20];    
	char   allTrainTypeResult[20];   

	int    trainNumFrontStartIndex;       
	int    trainNumFrontEndIndex;
	int    trainNumAfterStartIndex;       
	int    trainNumAfterEndIndex;

	void Init()
	{
		allTrainNumFirst = 0;  allTrainNumMark = 0;  configTrainFirst = 0;

		memset(allTrainNumResult, '\0', 20*sizeof(char));
		memset(allTrainTypeResult, '\0', 20*sizeof(char));

		trainNumFrontStartIndex = trainNumFrontEndIndex = 0;
		trainNumAfterStartIndex = trainNumAfterEndIndex = 0;
	}
}TrainResultPara;

typedef struct tagTrainParaIn
{
	int startIndex;                 //表示当前列车的起始图像序号
	int endIndex;                   //表示当前列车的终止图像序号

	int  trainBI;                    
	char trainBH[32];

	char currTrainID;               
	
	void Init()
	{
		trainBI = 0;
		memset(trainBH, '\0', 32*sizeof(char));
		currTrainID = 0; startIndex = endIndex = 0;
	}
}TrainParaIn;

typedef struct tagTrainParaOut
{
	//用于记录当前图像单张的高度和宽度
	int imageMark;     //用于标示当前任务是否识别完成

	TrainColorPara allTrainPara;

	void Init()
	{
		imageMark = 0;

		allTrainPara.Init();
	}
}TrainParaOut;

typedef struct tagAnalyDataTask       //表示分析任务单元
{
	char m_AnalyImagePath[MAXFILEPATH];   //图像路径---采集生成图像

	int  m_analyImageIndex;

	TrainParaIn    m_analyParaIn;          //记录当前标准信息	
	TrainParaOut   m_analyParaOut;

	void Init()
	{
		memset(m_AnalyImagePath, '\0', MAXFILEPATH*sizeof(char));

		m_analyImageIndex = 0;

		m_analyParaIn.Init();	m_analyParaOut.Init();
	}
}AnalyDataTask;

typedef struct tagGlobalPara
{
	int    ParaAll_ImageHeight;
	int    ParaAll_ImageWidth;       //针对配准图像的切割等分
	
	int    ParaAll_NormHeight;       //用于设置背景差值灰度值
	int    ParaAll_NormWidth;

	int    ParaAll_BlockHeight;
	int    ParaAll_BlockWidth;

	int    ParaAll_MaxOCRHeight;    //字符最大高度

	int    ParaAll_IsWhiteImage;
	int    ParaAll_IsMorphImage;
	int    ParaAll_IsMorphBigImage;
	int    ParaAll_IsWhiteMorphImage;

	int    ParaAll_DeltaValue;
	int    ParaAll_GrayValue;       
	int    ParaAll_SS8GrayValue;    

	int    ParaAll_MorphHeight;     //针对图像的腐蚀与膨胀
	int    ParaAll_MorphWidth;

	int    ParaAll_MorphBigHeight;   //针对图像断字较大间隔的腐蚀与膨胀参数
	int    ParaAll_MorphBigWidth;


	int    ParaAll_MaxSVMNum;

	int    ParaAll_BaoGuang;
	int    ParaAll_BackImage;
	int    ParaAll_MaxNumImage;      //处理的最多图片数量

	int   ParaAll_21ChannelFlag;    

	int   ParaAll_21ChannelAddFlag; 

	int   ParaAll_CharacterPick;    //用于对字符进行截取

	float  ParaAll_ChangeRatio;      //用于设置变化率

	int    ParaAll_ImgRotate;

	int    ParaAll_SavePara;

	int    ParaSVM_svmtype;
	int    ParaSVM_kerneltype;
	double ParaSVM_degree;
	double ParaSVM_gramma;
	double ParaSVM_coef0;

	void Init()
	{
		ParaAll_ImageHeight = 250;
		ParaAll_ImageWidth = 250;

		ParaAll_NormHeight = 60;
		ParaAll_NormWidth = 40;

		ParaAll_BlockHeight = 12;
		ParaAll_BlockWidth = 8;

		ParaAll_MaxOCRHeight = 0;

		ParaAll_DeltaValue = 5;
		ParaAll_MaxSVMNum = 50;

		ParaAll_BaoGuang = 1;
		ParaAll_BackImage = 2;
		ParaAll_MaxNumImage = 1<<30;

		ParaAll_21ChannelFlag = 0;
		ParaAll_21ChannelAddFlag = 0;
		ParaAll_CharacterPick = 0;

		ParaAll_ChangeRatio = 0.1;

		ParaAll_ImgRotate = 0;

		ParaSVM_svmtype = C_SVC;
		ParaSVM_kerneltype = RBF;
		ParaSVM_degree = 3;
		ParaSVM_gramma = 0;
		ParaSVM_coef0 = 0;
	}
}GlobalPara;

#endif//_TEDSITEM_STRUCR_H_