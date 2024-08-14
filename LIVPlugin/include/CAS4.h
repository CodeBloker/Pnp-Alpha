
#ifndef __CAS4_included__
#define __CAS4_included__

#ifdef __MACH__
#define __callconv __cdecl
#else
#define __callconv __stdcall
typedef unsigned short ushort;
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* $Revision$ */

// error codes

#define ErrorNoError              0
#define ErrorUnknown              -1
#define ErrorTimeoutRWSNoData     -2
#define ErrorInvalidDeviceType    -3
#define ErrorAcquisition          -4
#define ErrorAccuDataStream       -5
#define ErrorPrivilege            -6
#define ErrorFIFOOverflow         -7
#define ErrorTimeoutEOSScan       -8
#define ErrorTimeoutEOSDummyScan  -9
#define ErrorFifoFull             -10
#define ErrorPixel1FinalCheck     -11
#define ErrorCCDTemperatureFail   -13
#define ErrorAdrControl           -14
#define ErrorFloat                -15
#define ErrorTriggerTimeout       -16
#define ErrorAbortWaitTrigger     -17
#define ErrorDarkArray            -18
#define ErrorNoCalibration        -19
#define ErrorInterfaceVersion     -20
#define ErrorCRI                  -21
#define ErrorNoMultiTrack         -25
#define ErrorInvalidTrack         -26
#define ErrorDetectPixel          -31
#define ErrorSelectParamSet       -32
#define ErrorI2CInit              -35
#define ErrorI2CBusy              -36
#define ErrorI2CNotAck            -37
#define ErrorI2CRelease           -38
#define ErrorI2CTimeOut           -39
#define ErrorI2CTransmission      -40
#define ErrorI2CController        -41
#define ErrorDataNotAck           -42
#define ErrorNoExternalADC        -52
#define ErrorShutterPos           -53
#define ErrorFilterPos            -54
#define ErrorConfigSerialMismatch -55
#define ErrorCalibSerialMismatch  -56
#define ErrorInvalidParameter     -57
#define ErrorGetFilterPos         -58
#define ErrorParamOutOfRange      -59
#define ErrorDeviceFileChecksum   -60
#define ErrorInvalidEEPromType    -61
#define ErrorDeviceFileTooLarge   -62
#define ErrorNoCommunication      -63
#define ErrorNoFilesOnIdentKey    -64
#define ErrorExtraCalibFileInvalid - 66
#define ErrorFeatureNotSupported  -68
#define ErrorConfigUpToDate       -70

#define errCASOK                 ErrorNoError

#define errCASError              -1000
#define errCasNoConfig           errCASError-3
#define errCASDriverMissing      errCASError-6 //driver problem
#define errCasDeviceNotFound     errCASError-10 //invalid ADevice param

/////////////////////
// Error handling  //
/////////////////////
extern int __callconv casGetError( int ADevice );
extern char* __callconv casGetErrorMessage( int AError, char* Dest, int AMaxLen );
extern char* __callconv casGetErrorMessageA( int AError, char* Dest, int AMaxLen );
extern ushort* __callconv casGetErrorMessageW( int AError, ushort* Dest, int AMaxLen );

///////////////////////////////////
// Device Handles and Interfaces //
///////////////////////////////////
#define InterfaceISA			0
#define InterfacePCI			1
#define InterfaceTest			3
#define InterfaceUSB			5

extern int __callconv casCreateDevice( void );
extern int __callconv casCreateDeviceEx( int AInterfaceType, int AInterfaceOption );
extern int __callconv casChangeDevice( int ADevice, int AInterfaceType, int AInterfaceOption );
extern int __callconv casDoneDevice( int ADevice );

#define aoAssignDevice     0
#define aoAssignParameters 1
#define aoAssignComplete   2

extern int __callconv casAssignDeviceEx( int ASourceDevice, int ADestDevice, int AOption );

extern int __callconv casGetDeviceTypes( void );
extern char* __callconv casGetDeviceTypeName( int AInterfaceType, char* Dest, int AMaxLen );
extern char* __callconv casGetDeviceTypeNameA( int AInterfaceType, char* Dest, int AMaxLen );
extern ushort* __callconv casGetDeviceTypeNameW( int AInterfaceType, ushort* Dest, int AMaxLen );
extern int __callconv casGetDeviceTypeOptions( int AInterfaceType );
extern int __callconv casGetDeviceTypeOption( int AInterfaceType, int AIndex );
extern char* __callconv casGetDeviceTypeOptionName( int AInterfaceType, int AInterfaceOptionIndex, char* Dest, int AMaxLen );
extern char* __callconv casGetDeviceTypeOptionNameA( int AInterfaceType, int AInterfaceOptionIndex, char* Dest, int AMaxLen );
extern ushort* __callconv casGetDeviceTypeOptionNameW( int AInterfaceType, int AInterfaceOptionIndex, ushort* Dest, int AMaxLen );

////////////////////
// Initialization //
////////////////////

#define InitOnce		0
#define InitForced		1
#define InitNoHardware	2

extern int __callconv casInitialize( int ADevice, int Perform );

///////////////////////////
// Instrument properties //
///////////////////////////

//AWhat parameter constants for DeviceParameter methods below
#define dpidIntTimeMin			101
#define dpidIntTimeMax			102
#define dpidDeadPixels			103
#define dpidVisiblePixels		104
#define dpidPixels			105
#define dpidParamSets			106
#define dpidCurrentParamSet		107
#define dpidADCRange			108
#define dpidADCBits			109
#define dpidSerialNo			110
#define dpidTOPSerial			111 //TOP200 only, use dpidTOPSerialEx and dpidTOPType for others
#define dpidTransmissionFileName	112
#define dpidConfigFileName		113
#define dpidCalibFileName		114
#define dpidCalibrationUnit		115
#define dpidAccessorySerial		116
#define dpidTriggerCapabilities		118
#define dpidAveragesMax			119
#define dpidFilterType			120
#define dpidRelSaturationMin		123
#define dpidRelSaturationMax		124
#define dpidInterfaceVersion		125
#define dpidTriggerDelayTimeMax		126
#define dpidSpectrometerName		127
#define dpidNeedDarkCurrent		130
#define dpidNeedDensityFilterChange	131
#define dpidSpectrometerModel		132
#define dpidLine1FlipFlop           	133
#define dpidTimer                   	134
#define dpidInterfaceType           	135
#define dpidInterfaceOption         	136
#define dpidInitialized             	137
#define dpidDCRemeasureReasons		138
#define dpidAbortWaitForTrigger		140
#define dpidGetFilesFromDevice		142
#define dpidTOPType			143
#define dpidTOPSerialEx			144
#define dpidAutoRangeFilterMin		145
#define dpidAutoRangeFilterMax		146
#define dpidMultiTrackMaxCount		147

#define dpidDebugLogFile			204
#define dpidDebugLogLevel			205
#define dpidDebugMaxLogSize			206

//TriggerCapabilities constants; see dpidTriggerCapabilities
#define tcoCanTrigger           0x0001
#define tcoTriggerDelay         0x0002
#define tcoTriggerOnlyWhenReady 0x0004
#define tcoAutoRangeTriggering  0x0008
#define tcoShowBusyState        0x0010
#define tcoShowACQState         0x0020
#define tcoFlashOutput          0x0040
#define tcoFlashHardware        0x0080
#define tcoFlashForEachAverage  0x0100
#define tcoFlashDelay           0x0200
#define tcoFlashDelayNegative   0x0400
#define tcoFlashSoftware		0x0800
#define tcoGetFlipFlopState		0x1000
#define tcoQueryHasData			0x2000

//DCRemeasureReasons constants; see dpidDCRemeasureReasons 
#define todcrrNeedDarkCurrent   0x0001
#define todcrrCCDTemperature    0x0002
    
//TOPType constants; see dpidTOPType
#define ttNone          0
#define ttTOP100        1
#define ttTOP200        2
#define ttTOP150        3

extern double __callconv casGetDeviceParameter( int ADevice, int AWhat );
extern int __callconv casSetDeviceParameter( int ADevice, int AWhat, double AValue );
extern int __callconv casGetDeviceParameterString( int ADevice, int AWhat, char* ADest, int AMaxLen );
extern int __callconv casGetDeviceParameterStringA( int ADevice, int AWhat, char* ADest, int AMaxLen );
extern int __callconv casGetDeviceParameterStringW( int ADevice, int AWhat, ushort* ADest, int AMaxLen );
extern int __callconv casSetDeviceParameterString( int ADevice, int AWhat, char* AValue );
extern int __callconv casSetDeviceParameterStringA( int ADevice, int AWhat, char* AValue );
extern int __callconv casSetDeviceParameterStringW( int ADevice, int AWhat, const ushort* AValue );

#define casSerialComplete	0
#define casSerialAccessory	1
#define casSerialExtInfo	2
#define casSerialDevice		3
#define casSerialTOP		4

extern int __callconv casGetSerialNumberEx( int ADevice, int AWhat, char* Dest, int AMaxLen );
extern int __callconv casGetSerialNumberExA( int ADevice, int AWhat, char* Dest, int AMaxLen );
extern int __callconv casGetSerialNumberExW( int ADevice, int AWhat, ushort* Dest, int AMaxLen );

#define coShutter		   0x00000001
#define coFilter                   0x00000002
#define coGetShutter               0x00000004
#define coGetFilter                0x00000008
#define coGetAccessories           0x00000010
#define coGetTemperature           0x00000020
#define coUseDarkcurrentArray      0x00000040
#define coUseTransmission          0x00000080
#define coAutorangeMeasurement     0x00000100
#define coAutorangeFilter          0x00000200
#define coCheckCalibConfigSerials  0x00000400
#define coTOPHasFieldOfViewConfig  0x00000800
#define coAutoRemeasureDC          0x00001000
#define coCanMultiTrack            0x00008000
#define coCanSwitchLEDOff          0x00010000
#define coLEDOffWhileMeasuring     0x00020000
#define coCheckConfigUpToDate      0x00040000


extern int __callconv casGetOptions( int ADevice );
extern void __callconv casSetOptionsOnOff( int ADevice, int AOptions, int AOnOff );
extern void __callconv casSetOptions( int ADevice, int AOptions );
extern void __callconv casSetAdvOptions( char * PChar, int AOnOff );

//////////////////////////
// Measurement Commands //
//////////////////////////
extern int __callconv casMeasure( int ADevice );

extern int __callconv casStart( int ADevice );
extern int __callconv casFIFOHasData( int ADevice );
extern int __callconv casGetFIFOData( int ADevice );

extern int __callconv casMeasureDarkCurrent( int ADevice );

#define paPrepareMeasurement        1
#define paLoadCalibration           3
#define paCheckAccessories          4
#define paMultiTrackStart           5
#define paAutoRangeFindParameter    7
#define paCheckConfigUpToDate       12
#define paSearchForDevices          13
#define paPrepareShutDown           14
#define paRecalcSpectrum            16
#define paUpdateSpectralCalibration 19
#define paUpdateCompleteCalibration 20

extern int __callconv casPerformAction( int ADevice, int AId );

///////////////////////////
// Measurement Parameter //
///////////////////////////

//AWhat parameter constants for MeasurementParameter methods below
#define mpidIntegrationTime        1
#define mpidAverages               2
#define mpidTriggerDelayTime       3
#define mpidTriggerTimeout         4
#define mpidCheckStart             5
#define mpidCheckStop              6
#define mpidColormetricStart       7
#define mpidColormetricStop        8
#define mpidACQTime                10
#define mpidMaxADCValue            11
#define mpidMaxADCPixel            12
#define mpidScanMode               13
#define mpidTriggerSource          14
#define mpidAmpOffset              15
#define mpidSkipLevel              16
#define mpidSkipLevelEnabled       17
#define mpidScanStartTime          18
#define mpidAutoRangeMaxIntTime    19
#define mpidAutoRangeLevel         20 //deprecated; use mpidAutoRangeMinLevel below
#define mpidAutoRangeMinLevel      20
#define mpidDensityFilter          21
#define mpidCurrentDensityFilter   22
#define mpidNewDensityFilter       23
#define mpidLastDCAge              24
#define mpidRelSaturation          25
#define mpidPulseWidth             27
#define mpidRemeasureDCInterval    28
#define mpidFlashDelayTime         29
#define mpidTOPAperture            30
#define mpidTOPDistance            31
#define mpidTOPSpotSize            32
#define mpidTriggerOptions         33
#define mpidForceFilter            34
#define mpidFlashType              35
#define mpidFlashOptions           36
#define mpidACQStateLine           37
#define mpidACQStateLinePolarity   38
#define mpidBusyStateLine          39
#define mpidBusyStateLinePolarity  40
#define mpidAutoFlowTime           41
#define mpidCRIMode                42
#define mpidObserver               43
#define mpidTOPFieldOfView         44
#define mpidCurrentCCDTemperature  46
#define mpidLastCCDTemperature     47
#define mpidDCCCDTemperature       48
#define mpidAutoRangeMaxLevel      49
#define mpidMultiTrackAcqTime      50
#define mpidTimeSinceScanStart     51
#define mpidCMTTrackStart          52
#define mpidColormetricWidthLevel  54

//mpidTriggerOptions constants
#define toAcceptOnlyWhenReady	0x0001
#define toForEachAutoRangeTrial	0x0002
#define toShowBusyState		0x0004
#define toShowACQState		0x0008

//mpidFlashType constants
#define ftNone      0
#define ftHardware  1
#define ftSoftware  2

//mpidFlashOptions constants
#define foEveryAverage  1

//mpidTriggerSource constants
#define trgSoftware  0
#define trgFlipFlop  3

//mpidCRIMode constants
#define criDIN6169     0
#define criCIE13_3_95  1

//mpidObserver constants
#define cieObserver1931  0
#define cieObserver1964  1

extern double __callconv casGetMeasurementParameter( int ADevice, int AWhat );
extern int __callconv casSetMeasurementParameter( int ADevice, int AWhat, double AValue );
extern int __callconv casClearDarkCurrent( int ADevice );

/////////////////////////////////              
// Filter and Shutter commands //
/////////////////////////////////
#define casShutterInvalid   -1
#define casShutterOpen	    0
#define casShutterClose	    1

extern int __callconv casGetShutter( int ADevice );
extern void __callconv casSetShutter( int ADevice, int OnOff );
extern char* __callconv casGetFilterName( int ADevice, int AFilter, char* Dest, int AMaxLen );
extern char* __callconv casGetFilterNameA( int ADevice, int AFilter, char* Dest, int AMaxLen );
extern ushort* __callconv casGetFilterNameW( int ADevice, int AFilter, ushort* Dest, int AMaxLen );
extern int __callconv casGetDigitalOut( int ADevice, int APort );
extern void __callconv casSetDigitalOut( int ADevice, int APort, int OnOff );
extern int __callconv casGetDigitalIn( int ADevice, int APort );

////////////////////////////
// Parameter Set Commands //
////////////////////////////
extern int __callconv casDeleteParamSet( int ADevice, int AParamSet );

////////////////////////////////////////////
// Calibration and Configuration Commands //
////////////////////////////////////////////
extern void __callconv casCalculateCorrectedData( int ADevice );
extern void __callconv casConvoluteTransmission( int ADevice );

#define gcfDensityFunction        0
#define gcfSensitivityFunction    1
#define gcfTransmissionFunction   2
#define gcfDensityFactor          3
#define gcfTOPApertureFactor      4
#define gcfTOPDistanceFactor      5
	#define gcfTDCount         -1
	#define gcfTDExtraDistance  1
	#define gcfTDExtraFactor    2
#define gcfWLCalibrationChannel   6
	#define gcfWLExtraFirstCoefficient     -6
	#define gcfWLExtraLastCoefficient      -2
	#define gcfWLCalibPointCount           -1
	#define gcfWLExtraCalibrationDelete     1
	#define gcfWLExtraCalibrationDeleteAll  2
#define gcfWLCalibrationAlias     7
#define gcfWLCalibrationSave      8
#define gcfDarkArrayValues        9
	#define gcfDarkArrayDepth    -1  //Extra
	#define gcfDarkArrayIntTime  -2  //Extra
#define gcfTOPParameter          11
	#define gcfTOPApertureSize          0 //Extra
	#define gcfTOPSpotSizeDenominator   1
	#define gcfTOPSpotSizeOffset        2
#define gcfLinearityFunction     12
	#define gcfLinearityCounts  0
	#define gcfLinearityFactor  1
#define gcfRawData               14
		
//obsolete (03/2010); backward compatibility after renaming
#define gcfTop100Factor           4 //-> gcfTOPApertureFactor
#define gcfTop100DistanceFactor   5 //-> gcfTOPDistanceFactor

extern double __callconv casGetCalibrationFactors( int ADevice, int What, int Index, int Extra );
extern void __callconv casSetCalibrationFactors( int ADevice, int What, int Index, int Extra, double Value );
extern void __callconv casUpdateCalibrations( int ADevice );
extern void __callconv casSaveCalibration( int ADevice, char* AFileName );
extern void __callconv casSaveCalibrationA( int ADevice, char* AFileName );
extern void __callconv casSaveCalibrationW( int ADevice, ushort* AFileName );
extern void __callconv casClearCalibration( int ADevice, int What );

/////////////////////////
// Measurement Results //
/////////////////////////
extern double __callconv casGetData( int ADevice, int AIndex );
extern double __callconv casGetXArray( int ADevice, int AIndex );
extern double __callconv casGetDarkCurrent( int ADevice, int AIndex );
extern void __callconv casGetPhotInt( int ADevice, double* APhotInt, char* AUnit, int AUnitMaxLen );
extern void __callconv casGetPhotIntA( int ADevice, double* APhotInt, char* AUnit, int AUnitMaxLen );
extern void __callconv casGetPhotIntW( int ADevice, double* APhotInt, ushort* AUnit, int AUnitMaxLen );
extern void __callconv casGetRadInt( int ADevice, double* ARadInt, char* AUnit, int AUnitMaxLen );
extern void __callconv casGetRadIntA( int ADevice, double* ARadInt, char* AUnit, int AUnitMaxLen );
extern void __callconv casGetRadIntW( int ADevice, double* ARadInt, ushort* AUnit, int AUnitMaxLen );
extern double __callconv casGetCentroid( int ADevice );
extern void __callconv casGetPeak( int ADevice, double* x, double* y );
extern double __callconv casGetWidth( int ADevice );

#define	cLambdaWidth		0
#define	cLambdaLow		1
#define	cLambdaMiddle		2
#define	cLambdaHigh		3
#define	cLambdaOuterWidth	4
#define	cLambdaOuterLow		5
#define	cLambdaOuterMiddle	6
#define	cLambdaOuterHigh	7

extern double __callconv casGetWidthEx( int ADevice, int What ); // call only after casGetWidth
extern void __callconv casGetColorCoordinates( int ADevice, double* x, double* y, double* z, double* u, double* v1976, double* v1960 );
extern double __callconv casGetCCT( int ADevice );
extern double __callconv casGetCRI( int ADevice, int Index );
extern void __callconv casGetTriStimulus( int ADevice, double* X, double* Y, double* Z );

#define	ecvVisualEffect		 2
#define	ecvUVA			 3
#define	ecvUVB			 4
#define	ecvUVC			 5
#define	ecvVIS			 6
#define	ecvCRICCT		 7
#define	ecvCDI			 8
#define	ecvDistance		 9
#define	ecvCalibMin		10
#define	ecvCalibMax		11
#define ecvScotopicInt		12

#define ecvCRIFirst           100
#define ecvCRILast            116
#define ecvCRITriKXFirst      120
#define ecvCRITriKXLast       136
#define ecvCRITriKYFirst      140
#define ecvCRITriKYLast       156
#define ecvCRITriKZFirst      160
#define ecvCRITriKZLast       176
#define ecvCRITriRXordUFirst  180
#define ecvCRITriRXordULast   196
#define ecvCRITriRYordVFirst  200
#define ecvCRITriRYordVLast   216
#define ecvCRITriRZordWFirst  220
#define ecvCRITriRZordWLast   236

extern double __callconv casGetExtendedColorValues( int ADevice, int What );

/////////////////////////////
// Colormetric Calculation //
/////////////////////////////
extern int __callconv casColorMetric( int ADevice );
extern int __callconv casCalculateCRI( int ADevice );
extern int __callconv cmXYToDominantWavelength( double x, double y, double IllX, double IllY, double* LambdaDom, double* Purity );

///////////////
// Utilities //
///////////////
extern char* __callconv casGetDLLFileName( char* Dest, int AMaxLen );
extern char* __callconv casGetDLLFileNameA( char* Dest, int AMaxLen );
extern ushort* __callconv casGetDLLFileNameW( ushort* Dest, int AMaxLen );
extern char* __callconv casGetDLLVersionNumber( char* Dest, int AMaxLen );
extern char* __callconv casGetDLLVersionNumberA( char* Dest, int AMaxLen );
extern ushort* __callconv casGetDLLVersionNumberW( ushort* Dest, int AMaxLen );
extern int __callconv casSaveSpectrum( int ADevice, char* AFileName );
extern int __callconv casSaveSpectrumA( int ADevice, char* AFileName );
extern int __callconv casSaveSpectrumW( int ADevice, ushort* AFileName );
extern double __callconv casGetExternalADCValue( int ADevice, int AIndex ); //obsolete; use mpidCurrentCCDTemperature

#define extNoError		0
#define extExternalError	1
#define extFilterBlink		2
#define extShutterBlink		4

extern void __callconv casSetStatusLED( int ADevice, int AWhat );
extern int __callconv casNmToPixel( int ADevice, double nm );
extern double __callconv casPixelToNm( int ADevice, int APixel );
extern int __callconv casCalculateTOPParameter( int ADevice, int AAperture, double ADistance, double* ASpotSize, double* AFieldOfView);

////////////////
// MultiTrack //
////////////////
extern int __callconv casMultiTrackInit( int ADevice, int ATracks );
extern int __callconv casMultiTrackDone( int ADevice );
extern int __callconv casMultiTrackCount( int ADevice );
extern int __callconv casMultiTrackCopyData( int ADevice, int ATrack );
extern int __callconv casMultiTrackSaveData( int ADevice, char* AFileName );
extern int __callconv casMultiTrackSaveDataA( int ADevice, char* AFileName );
extern int __callconv casMultiTrackSaveDataW( int ADevice, ushort* AFileName );
extern int __callconv casMultiTrackLoadData( int ADevice, char* AFileName );
extern int __callconv casMultiTrackLoadDataA( int ADevice, char* AFileName );
extern int __callconv casMultiTrackLoadDataW( int ADevice, ushort* AFileName );

///////////////////////////
// Spectrum Manipulation //
///////////////////////////
extern void __callconv casSetData( int ADevice, int AIndex, double Value );
extern void __callconv casSetXArray( int ADevice, int AIndex, double Value );
extern void __callconv casSetDarkCurrent( int ADevice, int AIndex, double Value );
extern float* __callconv casGetDataPtr( int ADevice );
extern float* __callconv casGetXPtr( int ADevice );
extern void __callconv casLoadTestData( int ADevice, char* AFileName );
extern void __callconv casLoadTestDataA( int ADevice, char* AFileName );
extern void __callconv casLoadTestDataW( int ADevice, ushort* AFileName );

//////////////////////////
// Deprecated methods!! //
//////////////////////////
extern int __callconv casGetInitialized(int ADevice);
extern int __callconv casGetDeviceType( int ADevice );
extern int __callconv casGetDeviceOption( int ADevice );
extern int __callconv casGetAdcBits( int ADevice );
extern int __callconv casGetAdcRange( int ADevice );
extern char* __callconv casGetSerialNumber( int ADevice, char* Dest, int AMaxLen );
extern int __callconv casGetDeadPixels(int ADevice);
extern int __callconv casGetVisiblePixels(int ADevice);
extern int __callconv casGetPixels(int ADevice);
extern int __callconv casGetModel(int ADevice);
extern double __callconv casGetAmpOffset(int ADevice);
extern int __callconv casGetIntTimeMin( int ADevice );
extern int __callconv casGetIntTimeMax( int ADevice );
extern int __callconv casBackgroundMeasure( int ADevice );
extern int __callconv casGetIntegrationTime( int ADevice );
extern void __callconv casSetIntegrationTime( int ADevice, int Value );
extern int __callconv casGetAccumulations( int ADevice );
extern void __callconv casSetAccumulations( int ADevice, int Value );
extern double __callconv casGetAutoIntegrationLevel( int ADevice );
extern void __callconv casSetAutoIntegrationLevel( int ADevice, double ALevel );
extern int __callconv casGetAutoIntegrationTimeMax( int ADevice );
extern void __callconv casSetAutoIntegrationTimeMax( int ADevice, int AMaxTime );
extern int __callconv casClearBackground( int ADevice );
extern int __callconv casGetNeedBackground( int ADevice );
extern void __callconv casSetNeedBackground( int ADevice, int Value );
extern int __callconv casGetTop100( int ADevice );
extern void __callconv casSetTop100( int ADevice, int AIndex );
extern double __callconv casGetTop100Distance( int ADevice );
extern void __callconv casSetTop100Distance( int ADevice, double ADistance );
extern int __callconv casGetFilter( int ADevice );
extern void __callconv casSetFilter( int ADevice, int AFilter );
extern int __callconv casGetActualFilter( int ADevice );
extern int __callconv casGetNewDensityFilter( int ADevice );
extern void __callconv casSetNewDensityFilter( int ADevice, int AFilter );
extern int __callconv casGetForceFilter( int ADevice );
extern void __callconv casSetForceFilter( int ADevice, int AForce );
extern int __callconv casGetParamSets( int ADevice );
extern void __callconv casSetParamSets( int ADevice, int Value );
extern int __callconv casGetParamSet( int ADevice );
extern void __callconv casSetParamSet( int ADevice, int Value );
extern char* __callconv casGetCalibrationFileName( int ADevice, char* Dest, int AMaxLen );
extern void __callconv casSetCalibrationFileName( int ADevice, char* Value );
extern char* __callconv casGetConfigFileName( int ADevice, char* Dest, int AMaxLen );
extern void __callconv casSetConfigFileName( int ADevice, char* Value );
extern char* __callconv casGetTransmissionFileName( int ADevice, char* Dest, int AMaxLen );
extern void __callconv casSetTransmissionFileName( int ADevice, char* Value );
extern int __callconv casValidateConfigAndCalibFile( int ADevice );
extern char* __callconv casGetCalibrationUnit( int ADevice, char* Dest, int AMaxLen );
extern void __callconv casSetCalibrationUnit( int ADevice, char* Value );
extern double __callconv casGetBackground( int ADevice, int AIndex );
extern void __callconv casSetBackground( int ADevice, int AIndex, double Value );
extern int __callconv casGetMaxAdcValue( int ADevice );
extern int __callconv casGetCheckStart( int ADevice );
extern void __callconv casSetCheckStart( int ADevice, int Value );
extern int __callconv casGetCheckStop( int ADevice );
extern void __callconv casSetCheckStop( int ADevice, int Value );
extern double __callconv casGetColormetricStart( int ADevice );
extern void __callconv casSetColormetricStart( int ADevice, double Value );
extern double __callconv casGetColormetricStop( int ADevice );
extern void __callconv casSetColormetricStop( int ADevice, double Value );
extern int __callconv casGetObserver( void );
extern void __callconv casSetObserver( int ADevice );
extern double __callconv casGetSkipLevel( int ADevice );
extern void __callconv casSetSkipLevel( int ADevice, double ASkipLevel );
extern int __callconv casGetSkipLevelEnabled( int ADevice );
extern void __callconv casSetSkipLevelEnabled( int ADevice, int ASkipLevel );
extern int __callconv casGetTriggerSource( int ADevice );
extern void __callconv casSetTriggerSource( int ADevice, int Value );
extern int __callconv casGetLine1FlipFlop( int ADevice );
extern void __callconv casSetLine1FlipFlop( int ADevice, int Value );
extern int __callconv casGetTimeout( int ADevice );
extern void __callconv casSetTimeout( int ADevice, int Value );
extern int __callconv casGetFlash( int ADevice );
extern void __callconv casSetFlash( int ADevice, int Value );
extern int __callconv casGetFlashDelayTime( int ADevice );
extern void __callconv casSetFlashDelayTime( int ADevice, int Value );
extern int __callconv casGetFlashOptions( int ADevice );
extern void __callconv casSetFlashOptions( int ADevice, int Value );
extern int __callconv casGetDelayTime( int ADevice );
extern void __callconv casSetDelayTime( int ADevice, int Value );
extern int __callconv casGetStartTime( int ADevice );
extern int __callconv casGetACQTime( int ADevice );
extern int __callconv casReadWatch( int ADevice );
extern int __callconv casStopTime( int ADevice, int ARefTime );
extern void __callconv casMultiTrackCopySet( int ADevice );
extern int __callconv casMultiTrackReadData( int ADevice, int ATrack );

#ifdef __cplusplus
};
#endif /* __cplusplus */


#endif // __CAS4_included__

