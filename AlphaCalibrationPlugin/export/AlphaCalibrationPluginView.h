#pragma once
#include "StdAfx.h"
using namespace DuiLib;
#include <mutex>
#include <future>
#include "opencv2/opencv.hpp"

// 记录最后一张图片信息（用于修改相机实时状态）
struct LastImageInfo
{
	unsigned char* pLastMem = NULL;
	int nWidth;
	int nHeight;
};

class AlphaCalibrationPluginView : public JupSubDialog
{
public:
	AlphaCalibrationPluginView();
	virtual ~AlphaCalibrationPluginView();

public:
	UILIB_RESOURCETYPE GetResourceType() const override;

	CDuiString GetSkinFolder() override;
	CDuiString GetSkinFile() override;
	CDuiString GetZIPFileName() const override;

	LPCTSTR GetWindowClassName() const override;

protected:
	LRESULT ResponseDefaultKeyEvent(WPARAM wParam) override;
	void InitWindow() override;
	void OnFinalMessage(HWND hWnd) override;
	void Notify(TNotifyUI& msg) override;

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

	// 框架自定义事件
	LRESULT CustomEvent(JupCustomEvent* event) override;

private:
	// 相机控制
	void OnBtnTxExposureSetClick(TNotifyUI & msg);
	void OnBtnTyExposureSetClick(TNotifyUI & msg);
	void OnBtnIdsExposureSetClick(TNotifyUI & msg);
	void OnBtnTxGainSetClick(TNotifyUI & msg);
	void OnBtnTyGainSetClick(TNotifyUI & msg);
	void OnBtnIdsGainSetClick(TNotifyUI & msg);
	void OnBtnTxParasGetClick(TNotifyUI & msg);
	void OnBtnTyParasGetClick(TNotifyUI & msg);
	void OnBtnIdsParasGetClick(TNotifyUI & msg);
	void OnBtnDeviceOpenClick(TNotifyUI & msg);
	void OnBtnDeviceCloseClick(TNotifyUI & msg);
	void OnBtnStartGrabClick(TNotifyUI & msg);
	void OnBtnStopGrabClick(TNotifyUI & msg);
	void OnCheckTxSelectClick(TNotifyUI & msg);
	void OnCheckTySelectClick(TNotifyUI & msg);
	void OnCheckIdsSelectClick(TNotifyUI & msg);
	void OnCheckTxContinueClick(TNotifyUI & msg);
	void OnCheckTyContinueClick(TNotifyUI & msg);
	void OnCheckIdsContinueClick(TNotifyUI & msg);

	// OQC
	void OnCheckOqcModeClick(TNotifyUI & msg);
	void OnOqcStartTestClick(TNotifyUI & msg);
	void OnRadioOqcTxClick(TNotifyUI & msg);
	void OnRadioOqcTyClick(TNotifyUI & msg);

	// 自动标定圆心
	void OnBtnCalibrationConfirmClick(TNotifyUI & msg);
	void OnBtnStartAutoCalibrationClick(TNotifyUI & msg);
	void OnBtnSelectOfflineImageClick(TNotifyUI & msg);
	void OnCheckOfflineClick(TNotifyUI & msg);
	void OnRadioTxClick(TNotifyUI & msg);
	void OnRadioTyClick(TNotifyUI & msg);

private:
	// 显示一帧图片(分开写，避免图片资源冲突)
	void DisplayTxOneFrameImage(unsigned char* pData, unsigned short nWidth, unsigned short nHeight, bool is_online = true);
	void DisplayTyOneFrameImage(unsigned char* pData, unsigned short nWidth, unsigned short nHeight, bool is_online = true);
	void DisplayIdsOneFrameImage(unsigned char* pData, unsigned short nWidth, unsigned short nHeight, bool is_online = true);
	// 内存图片转换成HBITMAP
	HBITMAP ConvertCharToHBITMAP(std::string camera_name, char* imageData, int width, int height, bool is_online);

	// 自动标定圆心获取像素值结果
	bool GetCirclePixelResult(std::string camera_name, std::string file_name, double& point_x, double& point_y, bool wait_result = false);
	bool GetCircleCenterResult(std::string camera_name, CEditUI* result_edit, double val1, double val2, double val3, bool wait_result = false);
	// 自动标定获取拟合圆结果
	std::string ScalarCircle(std::string camera_name, double x1, double y1, double x2, double y2, double x3, double y3, double center_x, double center_y, double center_r);
	// 获取像素值结果
	void GetTxCameraPixelResult(bool is_continues = false);
	void GetTyCameraPixelResult(bool is_continues = false);
	void GetIdsCameraPixelResult(bool is_continues = false);

	// 离线验证（选择离线图片）
	std::vector<std::string> chooseFiles();

	// 自动标定异步执行线程
	void StartAutoCalibrationAsync();

	// 使能/失能按钮
	void EnableBtn(bool is_enable);
	// 清除界面显示
	void ClearAutoCalibrationDisplay();
	// 获取自动标定点位位置
	void GetAutoCalibrationPosInfos(std::string& cur_cam, double& pos1, double& pos2, double& pos3);

	// 计算图片清晰度(用于相机调焦距)
	double GetImgQualityScore(cv::Mat src, int flag = 0);
	void GetCameraImgQualityScore(std::string camera_name, bool is_continues = false);

	// 获得点位图片结果
	void GetPosImagePointResult(std::string current_cam, double distance, double& point_x, double& point_y);


private:
	// 关联界面控件事件对象
	// 相机参数设置
	// TX相机
	COptionUI* m_pOp_CameraTxSelect;
	CLabelUI*  m_pLable_TxStatus;
	COptionUI* m_pOp_TxContinueCapture;
	COptionUI* m_pOp_TxCameraFocal;
	CLabelUI*  m_pLable_TxCameraFocal;
	CLabelUI*  m_pLable_TxFocalThreshold;
	CEditUI*   m_pEdit_TxExposure;
	CButtonUI* m_pBtn_TxExposureSet;
	CEditUI*   m_pEdit_TxGain;
	CButtonUI* m_pBtn_TxGainSet;
	CButtonUI* m_pBtn_TxParasGet;
	// TY相机
	COptionUI* m_pOp_CameraTySelect;
	CLabelUI*  m_pLable_TyStatus;
	COptionUI* m_pOp_TyContinueCapture;
	COptionUI* m_pOp_TyCameraFocal;
	CLabelUI*  m_pLable_TyCameraFocal;
	CLabelUI*  m_pLable_TyFocalThreshold;
	CEditUI*   m_pEdit_TyExposure;
	CButtonUI* m_pBtn_TyExposureSet;
	CEditUI*   m_pEdit_TyGain;
	CButtonUI* m_pBtn_TyGainSet;
	CButtonUI* m_pBtn_TyParasGet;
	// Alpha相机（IDS相机）
	COptionUI* m_pOp_CameraIdsSelect;
	CLabelUI*  m_pLable_IdsStatus;
	COptionUI* m_pOp_IdsContinueCapture;
	COptionUI* m_pOp_AlphaCameraFocal;
	CLabelUI*  m_pLable_AlphaCameraFocal;
	CLabelUI*  m_pLable_AlphaFocalThreshold;
	CButtonUI* m_pBtn_AlphaAutoFocal;
	CEditUI*   m_pEdit_IdsExposure;
	CButtonUI* m_pBtn_IdsExposureSet;
	CEditUI*   m_pEdit_IdsGain;
	CButtonUI* m_pBtn_IdsGainSet;
	CButtonUI* m_pBtn_IdsParasGet;

	CButtonUI* m_pBtn_DeviceOpen;
	CButtonUI* m_pBtn_DeviceClose;
	CButtonUI* m_pBtn_StartGrab;
	CButtonUI* m_pBtn_StopGrab;

	// Calibration
	CEditUI*   m_pEdit_TxDertaX;
	CLabelUI*  m_pLable_TxDertaXThreshold;
	CLabelUI*  m_pLable_Axis1Advice;
	CEditUI*   m_pEdit_TxDertaY;
	CLabelUI*  m_pLable_TxDertaYThreshold;
	CLabelUI*  m_pLable_Axis2Advice;
	CEditUI*   m_pEdit_AlphaDertaX;
	CLabelUI*  m_pLable_AlphaDertaXThreshold;
	CLabelUI*  m_pLable_Axis3Advice;
	CEditUI*   m_pEdit_AlphaDertaY;
	CLabelUI*  m_pLable_AlphaDertaYThreshold;
	CLabelUI*  m_pLable_Axis4Advice;
	CEditUI*   m_pEdit_TyDertaX;
	CLabelUI*  m_pLable_TyDertaXThreshold;
	CLabelUI*  m_pLable_Axis5Advice;
	CEditUI*   m_pEdit_TyDertaY;
	CLabelUI*  m_pLable_TyDertaYThreshold;
	CLabelUI*  m_pLable_Axis6Advice;
	CEditUI*   m_pEdit_TxResultX;
	CEditUI*   m_pEdit_TxResultY;
	CLabelUI*  m_pLable_TxThreshold;
	CEditUI*   m_pEdit_TyResultX;
	CEditUI*   m_pEdit_TyResultY;
	CLabelUI*  m_pLable_TyThreshold;
	COptionUI* m_pOp_TxCalibration;
	COptionUI* m_pOp_TyCalibration;

	// Motion
	CEditUI*   m_pEdit_TxPos1;
	CEditUI*   m_pEdit_TxPos2;
	CEditUI*   m_pEdit_TxPos3;
	CEditUI*   m_pEdit_TyPos1;
	CEditUI*   m_pEdit_TyPos2;
	CEditUI*   m_pEdit_TyPos3;

	// Analysis
	CEditUI*   m_pEdit_TxPixel_x;
	CEditUI*   m_pEdit_TxPixel_y;
	CEditUI*   m_pEdit_TyPixel_x;
	CEditUI*   m_pEdit_TyPixel_y;
	CEditUI*   m_pEdit_IdsPixel_x;
	CEditUI*   m_pEdit_IdsPixel_y;
	COptionUI* m_pOp_OfflineMode;
	CEditUI*   m_pEdit_Pos1PointX;
	CEditUI*   m_pEdit_Pos2PointX;
	CEditUI*   m_pEdit_Pos3PointX;
	CEditUI*   m_pEdit_Pos1PointY;
	CEditUI*   m_pEdit_Pos2PointY;
	CEditUI*   m_pEdit_Pos3PointY;
	CEditUI*   m_pEdit_PointX;
	CEditUI*   m_pEdit_PointY;
	CEditUI*   m_pEdit_PointR;

	// OQC
	COptionUI* m_pOp_OqcMode;
	CEditUI*   m_pEdit_OqcTy_x;
	CEditUI*   m_pEdit_OqcTy_y;
	CEditUI*   m_pEdit_OqcAlpha_x;
	CEditUI*   m_pEdit_OqcAlpha_y;
	CEditUI*   m_pEdit_OqcTyDertaX;
	CEditUI*   m_pEdit_OqcTyDertaY;
	CLabelUI*  m_pLable_OqcTyDertaXThreshold;
	CLabelUI*  m_pLable_OqcTyDertaYThreshold;
	CLabelUI*  m_pLable_OqcAxis5Advice;
	CLabelUI*  m_pLable_OqcAxis6Advice;
	CEditUI*   m_pEdit_OqcAlphaDertaX;
	CEditUI*   m_pEdit_OqcAlphaDertaY;
	CLabelUI*  m_pLable_OqcAlphaDertaXThreshold;
	CLabelUI*  m_pLable_OqcAlphaDertaYThreshold;
	CLabelUI*  m_pLable_OqcAxis3Advice;
	CLabelUI*  m_pLable_OqcAxis4Advice;
	CEditUI*   m_pEdit_OqcTxResultX;
	CEditUI*   m_pEdit_OqcTxResultY;
	CLabelUI*  m_pLable_OqcTxThreshold;
	CEditUI*   m_pEdit_OqcTyResultX;
	CEditUI*   m_pEdit_OqcTyResultY;
	CLabelUI*  m_pLable_OqcTyThreshold;
	CButtonUI* m_pBtn_OqcStartTest;
	COptionUI* m_pOp_OqcTxCalibration;
	COptionUI* m_pOp_OqcTyCalibration;

	// 图像输出
	CLabelUI*  m_pLable_Image1;
	CLabelUI*  m_pLable_Image2;
	CLabelUI*  m_pLable_Image3;
	CLabelUI*  m_pLable_Image4;
	CLabelUI*  m_pLable_Image5;
	CLabelUI*  m_pLable_Image6;

	// Tab
	CTabLayoutUI* m_pControl;

private:
	// 容器，保存离线选中图片
	std::vector<std::string> m_offline_image;
	// 判断TX相机是否选用
	bool m_tx_select = false;
	// 判断TY相机是否选用
	bool m_ty_select = false;
	// 判断IDS相机是否选用
	bool m_ids_select = false;
	// 判断TX相机是否连续计算Pixel
	bool m_tx_continue = false;
	// 判断TY相机是否连续计算Pixel
	bool m_ty_continue = false;
	// 判断IDS相机是否连续计算Pixel
	bool m_ids_continue = false;
	// 判断相机调焦距是否连续计算清晰度
	bool m_focal_continue = false;
	// 判断是否使用离线计算功能
	bool m_offline = false;
	// 判断自动标定前是否已经打开相机
	bool start_camera = false;
	// 判断自动标定线程是否已启用，避免连续进入
	bool is_thread_start = false;
	// 判断是否使用OQC功能
	bool m_oqc_enable = false;
	// 判断选择TX还是TY标定
	bool m_is_tx_calibration = true;

	// 读写锁
	std::mutex m_Mutex;

	// 计算线程（异步执行）
	std::future<void> m_tx_thread;
	std::future<void> m_ty_thread;
	std::future<void> m_ids_thread;

	// 拟合圆中心坐标
	double m_circle_point_x = -1.0;
	double m_circle_point_y = -1.0;
	double m_alpha_center_x = 1280;// 图片宽度1280，后面移到配置中
	double m_alpha_center_y = 1024;// 图片高度1024，后面移到配置中

	// 相机最后一张图片信息
	LastImageInfo m_last_tx;
	LastImageInfo m_last_ty;
	LastImageInfo m_last_ids;

	// 标定结果
	bool m_tx_result = false;
	bool m_ty_result = false;
};
