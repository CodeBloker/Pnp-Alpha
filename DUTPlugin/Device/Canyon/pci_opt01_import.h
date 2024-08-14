///////////////////////////////////////////////////////////////////////////////////////
//	DLL import header file for Hyvision system boards
///////////////////////////////////////////////////////////////////////////////////////
#define MAX_DEVICE	4						// Maximum number of board to find

											// Board level API functions
extern "C" __declspec(dllimport) int  OpenDAQDevice(void);
extern "C" __declspec(dllimport) BOOL ResetBoard(int nBoard);
extern "C" __declspec(dllimport) BOOL CloseDAQDevice(void);
extern "C" __declspec(dllimport) int  GetBoardNum(void);

//****************************************************************************************
//	Get DLL Version 2015. 01. 19 add
//****************************************************************************************
extern "C" __declspec(dllimport) char* GetDllVersion(void);
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_Init(int nBoard, int nCh);
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_Start(int nBoard, int nCh);
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_GetFrame(int nBoard, int nCh, DWORD* nCnt, unsigned char* buf);
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_Close(int nBoard, int nCh);

extern "C" __declspec(dllimport) BOOL  PCI_LVDS_SetResolution(int nBoard, int nCh, DWORD xRes, DWORD yRes);
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_GetResolution(int nBoard, int nCh, DWORD *xRes, DWORD *yRes);
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_Stop(int nBoard, int nCh);

//****************************************************************************************
//	LVDS Set Datamode
//  nMode
//		1 : 8bit, 1 : 16bit mode, 2 : 24bit, 3 : 32bit, 4 : 16bit YUV
//****************************************************************************************
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_SetDataMode(int nBoard, int nCh, int nMode);
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_GetVersion(int nBoard, int nCh, int *nFpgaVer, int *nFirmVer);

//****************************************************************************************
//	LVDS Select Input
//	0 : MIPI, 1 : Parallel
//****************************************************************************************
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_SelectInput(int nBoard, int nCh, int nInput);
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_BufferFlush(int nBoard, int nCh);				//2012.09.07
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_FrameMerge(int nBoard, int nCh, int nNum); //2013.01.16 add

//****************************************************************************************
//	LVDS Set Polarity  (2013. 03. 06)
//  dwSignal  0:clock, 1: vsync
//	dwPolarity  0:normal, 1: inverse
//****************************************************************************************
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_SetPolarity(int nBoard, int nCh, DWORD dwSignal, DWORD dwPolarity);
//****************************************************************************************
//	LVDS Set Vsync Polarity  (2013. 03. 06)
//  bPol  FALSE:normal, TRUE: inverse
//****************************************************************************************
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_VsyncPol(int nBoard, int nCh, BOOL bPol);
//****************************************************************************************
//	LVDS Set Pclk Polarity  (2013. 03. 06)
//  bPol  FALSE:normal, TRUE: inverse
//****************************************************************************************
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_PclkPol(int nBoard, int nCh, BOOL bPol);

//****************************************************************************************
//	LVDS CheckSum  (2013. 04. 19)
//  bOn  TRUE: add 2byte checksum,  FALSE: do not add checksum
//****************************************************************************************
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_CheckSum(int nBoard, int nCh, BOOL bOn);

//****************************************************************************************
//	Set Rolling mode (2013. 04. 25)
//	if rolling mode is true, update frame data regardless of getframe function
//****************************************************************************************
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_SetRolling(int nBoard, int nCh, BOOL bRolling);

// Fiber Tx Board Reset 2014. 04. 10
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_TxBoardReset(int nBoard, int nCh, BOOL bHwReset);
// DDR USE add 2014. 06. 09
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_DdrUse(int nBoard, int nCh, BOOL bUse);

//****************************************************************************************
// DMA Buffer API (2014. 08. 28)
//****************************************************************************************
extern "C" __declspec(dllimport) BOOL PCI_LVDS_GetDmaBufferSize(DWORD *pdwBytes);
extern "C" __declspec(dllimport) BOOL PCI_LVDS_SetDmaBufferSize(DWORD dwBytes);

//*********************************************************************************************
// Fiber Tx Board Check 2015. 01. 18
// return TRUE: no Error, FALSE: Error
// nError code 0 : no error, 1 : parameter error, 2: no device
// nError code -1 : no connection
//*********************************************************************************************
extern "C" __declspec(dllimport) BOOL  PCI_LVDS_TxBoardCheck(int nBoard, int nCh, int *pError);

//****************************************************************************************
//  From here it starts to define Clock API
//****************************************************************************************
extern "C" __declspec(dllimport)  BOOL PCI_CLK_Init(int nBoard, int nCh);
extern "C" __declspec(dllimport)  BOOL PCI_CLK_Close(int nBoard, int nCh);
//****************************************************************************************
// nSelect == 0 : fixed clock
// nSelect == others : Program clock
//****************************************************************************************
extern "C" __declspec(dllimport)  BOOL  PCI_CLK_Select(int nBoard, int nCh, int nSelect);
extern "C" __declspec(dllimport)  DWORD PCI_CLK_Get(int nBoard, int nCh);
//****************************************************************************************
////   1039Hz to 68Mhz
//****************************************************************************************
extern "C" __declspec(dllimport)  BOOL PCI_CLK_Set(int nBoard, int nCh, DWORD val);
extern "C" __declspec(dllimport)  BOOL PCI_CLK_Off(int nBoard, int nCh, BOOL bOff);		// bOff TRUE : clock off, FALSE : clock on


//**************************************************************************************
//  From here it starts to define SYSTEM I2C function
//**************************************************************************************
extern "C" __declspec(dllimport) BOOL  PCI_I2C_SYS_Reset(int nBoard, int nCh);
extern "C" __declspec(dllimport) BOOL  PCI_I2C_SYS_Set_Clock(int nBoard, int nCh, int nClock);
extern "C" __declspec(dllimport) BOOL  PCI_I2C_SYS_Read(int nBoard, int nCh, BYTE slAddr, DWORD nAddrLen, DWORD nAddr, DWORD nCnt, unsigned char* buf);
extern "C" __declspec(dllimport) BOOL  PCI_I2C_SYS_Read2(int nBoard, int nCh, BYTE slAddr, DWORD nAddrLen, DWORD nAddr, DWORD nCnt, unsigned char* buf);
extern "C" __declspec(dllimport) BOOL  PCI_I2C_SYS_Write(int nBoard, int nCh, BYTE slAddr, DWORD nAddrLen, DWORD nAddr, DWORD nCnt, unsigned char* buf);

extern "C" __declspec(dllimport) BOOL  PCI_SEN_Reset(int nBoard, int nCh, BOOL bReset);		// default high
extern "C" __declspec(dllimport) BOOL  PCI_SEN_Enable(int nBoard, int nCh, BOOL bEnble);		// default high

//**************************************************************************************
//  From here it starts to OIS function
//**************************************************************************************
extern "C" __declspec(dllimport) BOOL  PCI_OIS_Reset(int nBoard, int nCh);
extern "C" __declspec(dllimport) BOOL  PCI_OIS_SetClock(int nBoard, int nCh, DWORD dwKHz);						// 1-10 = 1x100Khz, others : 100Khz
extern "C" __declspec(dllimport) BOOL  PCI_OIS_SetDelay(int nBoard, int nCh, DWORD dwWrDelay, DWORD dwRdDelay);	// Delay in nano second (Max 1310700) = 1.3mSEC
extern "C" __declspec(dllimport) BOOL  PCI_OIS_SetBytesRead(int nBoard, int nCh, DWORD dwBytesRead);				// Default 3 (Max 255)
extern "C" __declspec(dllimport) BOOL  PCI_OIS_GetData(int nBoard, int nCh, 	BYTE  byID,			// Slave ID (must 0x1e)
													int	  nData,		// # of dac Data  (range 1 to 255)
													BYTE* dacBuf,		// Dac Data buffer
													int   nRead,		// # of Hall data reads (range 0 to 1023)
																		// hall buffer size in FPGA is 4096 bytes
													int   nBytesPerRead,
													BYTE* hallBuf,		// Hall data buffer, minimum buffer size is nRead x dwBytesRead
													int   nPos,			// # of Position Data (range 0 to 7)
													BYTE* posBuf);		// Position Data buffer
														
