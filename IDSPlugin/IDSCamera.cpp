#include "IDSCamera.h"
#include <process.h>
#include "JupCore.h"
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include "../_INCLUDE/ProjectEvent.h"
using namespace ProjectEvent;

#define IS_SET_EVENT_THREAD_STOP    IS_SET_EVENT_USER_DEFINED_BEGIN

IDSCamera::IDSCamera()
{
	m_pcImageMemory = NULL;
	m_lMemoryId = 0;
	m_hCam = 0;   //初始化相机句柄为0
	m_nRenderMode = IS_RENDER_FIT_TO_WINDOW;  //设置显示模式为适应窗口大小
	m_nPosX = 0;
	m_nPosY = 0;
	m_nFlipHor = 0;
	m_nFlipVert = 0;
}

IDSCamera::~IDSCamera()
{
	m_bStartGrabbing = false;
}

IDSCamera *& IDSCamera::GetInstance()
{
	if (m_SingleInstance == nullptr) {
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (m_SingleInstance == nullptr) {
			m_SingleInstance = new (std::nothrow) IDSCamera{};
		}
	}
	return m_SingleInstance;
}

INT IDSCamera::InitCamera(HIDS * hCam, HWND hWnd)
{
	INT nRet = is_InitCamera(hCam, hWnd);
	if (nRet == IS_STARTER_FW_UPLOAD_NEEDED)//相机的启动程序固件和驱动不兼容,需要更新固件版本 
	{

		INT nUploadTime = 25000; //默认更新时间为25S
		is_GetDuration(*hCam, IS_STARTER_FW_UPLOAD, &nUploadTime);

		//printf("This camera requires a new firmware !\n");
		//printf("The upload will take about %f seconds. Please wait ...\n", nUploadTime / 1000);

		//再次打开相机并自动更新固件
		*hCam = (HIDS)(((INT)*hCam) | IS_ALLOW_STARTER_FW_UPLOAD);
		nRet = is_InitCamera(hCam, NULL);
	}
	//printf("初始化相机成功 !\n");
	return nRet;
}

bool IDSCamera::OpenCamera()
{
	INT nRet = IS_NO_SUCCESS;
	ExitCamera();

	m_hCam = (HIDS)0;
	//nRet = InitCamera(&m_hCam, m_hWndDisplay);  //  1.初始化相机
	nRet = InitCamera(&m_hCam, NULL);  //  1.初始化相机

	if (nRet == IS_SUCCESS) {   //  打开相机成功
			// 查询相机所用传感器的类型
		is_GetSensorInfo(m_hCam, &m_sInfo);     //2.查询信息
		GetMaxImageSize(&m_nSizeX, &m_nSizeY);
		nRet = InitDisplayMode();             //3.选择显示模式（位图）

		if (nRet == IS_SUCCESS)
		{
			// 允许接受消息
			is_EnableMessage(m_hCam, IS_DEVICE_REMOVED, NULL);
			is_EnableMessage(m_hCam, IS_DEVICE_RECONNECTED, NULL);
			is_EnableMessage(m_hCam, IS_FRAME, NULL);
			is_EnableMessage(m_hCam, IS_TRIGGER, NULL);
			//is_CaptureVideo(m_hCam, IS_WAIT);   //4.设定捕捉模式：自由运行模式下的实时模式
			//EvInitAll();
			IS_INIT_EVENT init_events[] = { {IS_SET_EVENT_FRAME, TRUE, FALSE}, {IS_SET_EVENT_THREAD_STOP, TRUE, FALSE} };
			INT ret = is_Event(m_hCam, IS_EVENT_CMD_INIT, init_events, sizeof(init_events));
			if (IS_SUCCESS == ret)
			{
				UINT events[] = { IS_SET_EVENT_FRAME, IS_SET_EVENT_THREAD_STOP };
				ret = is_Event(m_hCam, IS_EVENT_CMD_ENABLE, events, sizeof(events));
			}
			// load parameter from file
			LoadParameterFromFile("./Config/ids.ini");
			return true;
		}
		else {
			//printf("初始化显示模式失败!");
			return false;
		}
	}
	else {
		//printf("没有发现uEye相机!");
		return false;
	}
}

void IDSCamera::ExitCamera()
{
	if (m_hCam != 0)
	{
		// 调用 hWnd = NULL函数禁用Windows消息
		is_EnableMessage(m_hCam, IS_FRAME, NULL);
		// 在曝光未开始时停止实时模式或取消硬件触发的图像捕捉
		is_StopLiveVideo(m_hCam, IS_WAIT);
		// 释放分配的图像内存
		if (m_pcImageMemory != NULL)
			is_FreeImageMem(m_hCam, m_pcImageMemory, m_lMemoryId);
		m_pcImageMemory = NULL;
		// 关闭相机
		is_ExitCamera(m_hCam);
		m_hCam = NULL;
	}
}

int IDSCamera::InitDisplayMode()
{
	INT nRet = IS_NO_SUCCESS;

	if (m_hCam == NULL)
		return IS_NO_SUCCESS;

	if (m_pcImageMemory != NULL) //释放通过 is_AllocImageMem() 函数分配的图像内存
	{
		is_FreeImageMem(m_hCam, m_pcImageMemory, m_lMemoryId);
		//如果图像内存不是通过SDK分配，则需调用 is_FreeImageMem() 函数。否则驱动会继续尝试访问该内存。
	   //但是这并不能释放内存。因此，必须确保可再次释放内存。
	}
	m_pcImageMemory = NULL;

	// 设置位图模式
	nRet = is_SetDisplayMode(m_hCam, IS_SET_DM_DIB);

	if (m_sInfo.nColorMode == IS_COLORMODE_BAYER)
	{
		// 如果是拜耳色 则设置位深为当前窗口的设置,linux 下不可以这么设置
		// 用于检索当前Windows桌面的颜色设置并返回每像素位深及相匹配的uEye色彩模式
		is_GetColorDepth(m_hCam, &m_nBitsPerPixel, &m_nColorMode);
	}
	else if (m_sInfo.nColorMode == IS_COLORMODE_CBYCRY)
	{
		m_nColorMode = IS_CM_BGRA8_PACKED;
		m_nBitsPerPixel = 32;
	}
	else
	{
		m_nColorMode = IS_CM_MONO8;
		m_nBitsPerPixel = 8;
	}

	// 分配图像内存，图像尺寸有 m_nSizeX和m_nSizeY确定，色彩位深由m_nBitsPerPixel确定，m_pcImageMemory返回起始地址，m_lMemoryId 返回已分配内存的ID
	if (is_AllocImageMem(m_hCam, m_nSizeX, m_nSizeY, m_nBitsPerPixel, &m_pcImageMemory, &m_lMemoryId) != IS_SUCCESS)
	{
		//printf("相机内存分配出错!");
	}
	else
		is_SetImageMem(m_hCam, m_pcImageMemory, m_lMemoryId);
	/*    INT is_SetImageMem (HIDS hCam, char* pcImgMem, INT id)用于将指定的图像内存变为活动内存。
			只有活动图像内存可以接收图像数据。
		在调用 is_FreezeVideo() 时，捕捉的图像会存储在 pcImgMem 和 id 指定的图像缓冲区中。
		捕捉的图像会存储在 pcImgMem 和 id 指定的图像缓冲区中。对于 pcImgMem，
		您必须传递 is_AllocImageMem() 创建的指针，传递任何其他指针均会发出错误信息。
		您可以多次传递同样的指针。     */

	if (nRet == IS_SUCCESS)
	{
		// 设置显卡在保存或显示图像数据时所使用的色彩模
		is_SetColorMode(m_hCam, m_nColorMode);

		// set the image size to capture
		IS_SIZE_2D imageSize;
		imageSize.s32Width = m_nSizeX;
		imageSize.s32Height = m_nSizeY;
		//设置图像感兴趣区域（AOI）的大小和位置
		is_AOI(m_hCam, IS_AOI_IMAGE_SET_SIZE, (void*)&imageSize, sizeof(imageSize));
	}

	return nRet;
}

int IDSCamera::StartGrabbingImage(bool is_calibration)
{
	if ( NULL == m_hCam)
	{
		return -1;
	}

	// 开启线程
	std::thread capture_thread(&IDSCamera::GetCaptureImage, this, is_calibration);
	capture_thread.detach();

	BOOL bWasLive = (BOOL)(is_CaptureVideo(m_hCam, IS_GET_LIVE));
	if (!bWasLive)
		is_CaptureVideo(m_hCam, IS_DONT_WAIT);
	return 0;
}

int IDSCamera::StopGrabbingImage()
{
	if (NULL == m_hCam)
	{
		return -1;
	}
	// ... signal 'stop thread' ...
	UINT events[] = { IS_SET_EVENT_FRAME, IS_SET_EVENT_THREAD_STOP };
	is_Event(m_hCam, IS_EVENT_CMD_SET, &events[1], sizeof(UINT));
	is_Event(m_hCam, IS_EVENT_CMD_DISABLE, events, sizeof(events));
	is_Event(m_hCam, IS_EVENT_CMD_EXIT, events, sizeof(events));
	is_StopLiveVideo(m_hCam, IS_WAIT);
	return 0;
}

void IDSCamera::GetMaxImageSize(INT * pnSizeX, INT * pnSizeY)
{
	INT nAOISupported = 0;
	BOOL bAOISupported = TRUE;
	if (is_ImageFormat(m_hCam,
		IMGFRMT_CMD_GET_ARBITRARY_AOI_SUPPORTED,
		(void*)&nAOISupported,
		sizeof(nAOISupported)) == IS_SUCCESS)
	{
		bAOISupported = (nAOISupported != 0);
	}

	if (bAOISupported)
	{
		// All other sensors
		// Get maximum image size
		SENSORINFO sInfo;
		is_GetSensorInfo(m_hCam, &sInfo);
		*pnSizeX = sInfo.nMaxWidth;
		*pnSizeY = sInfo.nMaxHeight;
	}
	else
	{
		// Only ueye xs
		// Get image size of the current format
		IS_SIZE_2D imageSize;
		is_AOI(m_hCam, IS_AOI_IMAGE_GET_SIZE, (void*)&imageSize, sizeof(imageSize));

		*pnSizeX = imageSize.s32Width;
		*pnSizeY = imageSize.s32Height;
	}
}

bool IDSCamera::SaveImage(const char* fileName)
{
	IMAGE_FILE_PARAMS ImageFileParams;
	memset(&ImageFileParams, 0, sizeof(ImageFileParams));

	//ImageFileParams.pwchFileName = NULL;
	//ImageFileParams.pnImageID = NULL;
	//ImageFileParams.ppcImageMem = NULL;
	//ImageFileParams.nQuality = 0;

	//ImageFileParams.nFileType = IS_IMG_BMP;
	//INT nRet = is_ImageFile(m_hCam, IS_IMAGE_FILE_CMD_SAVE, (void*)&ImageFileParams,
	//	sizeof(ImageFileParams));

	//保存活动内存中的jpeg图像，图像画质为100
	//ImageFileParams.pwchFileName = L"CamIds.jpg";
	ImageFileParams.pwchFileName = charToWchat(fileName);
	ImageFileParams.nFileType = IS_IMG_BMP; //待保存文件的类型
	ImageFileParams.nQuality = 100;  //100为最佳图像画质（无压缩)
	if (ImageFileParams.ppcImageMem == NULL)
	{
		// 出现ppcImageMem内存图片为空的情况
		ImageFileParams.ppcImageMem = &m_pLastBuffer;
	}
	INT nRet = is_ImageFile(m_hCam, IS_IMAGE_FILE_CMD_SAVE, (void*)&ImageFileParams, sizeof(ImageFileParams));
	if (0 != nRet)
	{
		return false;
	}
	return true;
}

bool IDSCamera::SetGamma(int nGamma)
{
	INT nRet = is_Gamma(m_hCam, IS_GAMMA_CMD_SET, (void*)&nGamma, sizeof(nGamma));
	if (nRet != IS_SUCCESS)
	{
		return false;
	}
	return true;
}

int IDSCamera::ReadGamma()
{
	/* read gamma value to nGamma */
	INT nGamma;
	INT nRet = is_Gamma(m_hCam, IS_GAMMA_CMD_GET, (void*)&nGamma, sizeof(nGamma));
	return nGamma;
}

bool IDSCamera::SetGain(int nGain)
{
	return false;
}

int IDSCamera::ReadGain()
{
	return 0;
}

bool IDSCamera::SetExposure(double nExposure)
{
	double newExposure = nExposure;
	INT nRet = is_Exposure(m_hCam, IS_EXPOSURE_CMD_SET_EXPOSURE, (void*)&newExposure, sizeof(newExposure));
	if (nRet != IS_SUCCESS)
	{
		return false;
	}
	return true;
}

double IDSCamera::ReadExposure()
{
	double nExposure;
	INT nRet = is_Exposure(m_hCam, IS_EXPOSURE_CMD_GET_EXPOSURE, (void*)&nExposure, sizeof(nExposure));
	return nExposure;
}

bool IDSCamera::SetFrameRate(double nFrameRate)
{
	double newFrameRate;
	INT nRet = is_SetFrameRate(m_hCam, nFrameRate, &newFrameRate);
	if (nRet != IS_SUCCESS)
	{
		return false;
	}
	return true;
}

double IDSCamera::ReadFrameRate()
{
	double nFrameRate;
	//INT nRet = is_GetFramesPerSecond(m_hCam, &dblFPS);
	INT nRet = is_SetFrameRate(m_hCam, IS_GET_FRAMERATE, &nFrameRate);
	return nFrameRate;
}

bool IDSCamera::SetSharpness(double Sharpness)
{
	return false;
}

int IDSCamera::ReadSharpness()
{
	INT nSharpness;
	INT nRet = is_Sharpness(m_hCam, SHARPNESS_CMD_GET_VALUE, (void*)&nSharpness, sizeof(nSharpness));
	return nSharpness;
}

int IDSCamera::SetTrigger(int m_nTimeout, int mode)
{
	INT m_Ret = is_SetTimeout(m_hCam, IS_TRIGGER_TIMEOUT, m_nTimeout);
	m_Ret = is_SetExternalTrigger(m_hCam, mode);
	return m_Ret;
}

int IDSCamera::LoadParameterFromFile(const char * file)
{
	// Load parameters from specified file using an absolute path
	auto file_name = charToWchat(file);
	int nRet = is_ParameterSet(m_hCam, IS_PARAMETERSET_CMD_LOAD_FILE, (void*)file_name, sizeof(file_name));
	return nRet;
}

int IDSCamera::getWidth()
{
	return m_nSizeX;
}

int IDSCamera::getHeight()
{
	return m_nSizeY;
}

void IDSCamera::GetCaptureImage(bool is_calibration)
{
	UINT events[] = { IS_SET_EVENT_FRAME, IS_SET_EVENT_THREAD_STOP };
	IS_WAIT_EVENTS wait_events = { events, 2, FALSE, 1000, 0, 0 };
	do
	{
		INT ret = is_Event(m_hCam, IS_EVENT_CMD_WAIT, &wait_events, sizeof(wait_events));
		if ((IS_SUCCESS == ret) && (IS_SET_EVENT_FRAME == wait_events.nSignaled))
		{
			// find the latest image buffer and display the buffer
			INT nNum = 0;
			char *pcMem = NULL;
			char *pcMemLast = NULL;

			INT nRet = is_GetActSeqBuf(m_hCam, &nNum, &pcMem, &pcMemLast);

			if ((IS_SUCCESS == nRet) && (NULL != pcMemLast))
			{
				nRet = is_LockSeqBuf(m_hCam, IS_IGNORE_PARAMETER, pcMemLast);

				if (IS_SUCCESS == nRet)
				{
					//is_RenderBitmap(m_hCam, m_lSeqMemId[j], m_hWndDisplay, IS_RENDER_FIT_TO_WINDOW);
					// send to display
					if (is_calibration)
					{
						m_pLastBuffer = pcMemLast;
						jCore->SendEvent(g_CalibrationWidget, &JCalibrationEvent("DisplayOnceFrame", "IDS", (unsigned char*)pcMemLast, m_nSizeX, m_nSizeY));
						Sleep(500);
					}
					else
						jCore->SendEvent(g_IdsWidget, &JIdsEvent("DisplayOnceFrame", pcMemLast));
					is_UnlockSeqBuf(m_hCam, IS_IGNORE_PARAMETER, pcMemLast);
				}
			}
			// ... reset event, because 'bManualReset = TRUE'
			is_Event(m_hCam, IS_EVENT_CMD_RESET, &events[0], sizeof(UINT));
		}
		else if (IS_TIMED_OUT == ret)
		{
			// do something ...
			Sleep(1);
		}
	} while (IS_SET_EVENT_THREAD_STOP != wait_events.nSignaled);
}

wchar_t* IDSCamera::charToWchat(const char * str)
{
	int bufSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	wchar_t* wp = new wchar_t[bufSize];
	MultiByteToWideChar(CP_ACP, 0, str, -1, wp, bufSize);
	return wp;
}
