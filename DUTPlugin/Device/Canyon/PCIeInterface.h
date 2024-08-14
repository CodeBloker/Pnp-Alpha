#ifndef _PCIEINTERFACE_H_
#define _PCIEINTERFACE_H_
#define		CH0		0
extern "C" __declspec(dllexport) int	Program_PowerOffAllM(int index);
extern "C" __declspec(dllexport) int	Program_PowerOffM(int ch_index, int index);
extern "C" __declspec(dllexport) int	Program_PowerIOSetAllM(float fch0volt, float fch1volt, float fch2volt, float fch3volt, float fch4volt, BOOL bch5on, float fIOvolt, int index);		  //Power: 1.2~3.0V, IO:1.6~3.0V
extern "C" __declspec(dllexport) int	Program_PowerSetM(int ch_index, float fvolt, int index);
extern "C" __declspec(dllexport) int	Program_PowerOnOff_Fix36M(BOOL bPowerOn, int index);
extern "C" __declspec(dllexport) int	IOlevel_SetM(float fvolt, int index); //1.6 ~ 3.5 range ¹× table ¼öÁ¤. (2006. 3/13)

extern "C" __declspec(dllexport) int	DynamicMeasureM(int ch_index, int offset_value, float *measure_value, int iMeasureConut=1, int index=0);
extern "C" __declspec(dllexport) int	StandbyMeasureM(int ch_index, int offset_value, float *measure_value, int iMeasureConut=1, int index=0);
extern "C" __declspec(dllexport) int	DynamicOffset_EachPowerM(int *offsetvalue, float ch1, float ch2, float ch3, float ch4, float ch5, BOOL bch6on, float ch_io, int index);
extern "C" __declspec(dllexport) int	StandbyOffset_EachPowerM(int *offsetvalue, float ch1, float ch2, float ch3, float ch4, float ch5, BOOL bch6on, float ch_io, int index);

#define PWR_StandbyCurrentMeasureStep_500uA	0
#define PWR_StandbyCurrentMeasureStep_5mA	1
extern "C" __declspec(dllexport) int	StandbyMeasureMode(int nMode, int index);


extern "C" __declspec(dllexport) int 	GPIOWrite_Low(int ionum, int index);   //GPIO 0 ~ 3, ionum must be 0 ~ 3.
extern "C" __declspec(dllexport) int 	GPIOWrite_High(int ionum, int index);
extern "C" __declspec(dllexport) int 	GPIO_Read(int ionum, int index);
extern "C" __declspec(dllexport) int 	RearOutput_Low(int ionum, int index);  //Rear Output 0 ~ 1, ionum must be 0 ~ 1.
extern "C" __declspec(dllexport) int 	RearOutput_High(int ionum, int index);
extern "C" __declspec(dllexport) int 	RearInput_Read(int ionum, int index);  //Rear Input 0 ~ 5,  ionum must be 0 ~ 5.

extern "C" __declspec(dllexport) int	LEDLight_SetM(int value, int index);
extern "C" __declspec(dllexport) void	LEDLight_OffM(int index);


//V5P Board's OS ...
extern "C" __declspec(dllexport) void 	Parallel_OS_Enable(BOOL benable);
extern "C" __declspec(dllexport) int 	OSTest_StartM(int index, int openShort_PlusMinus, BOOL SourceSelect, BOOL bFloating);	//int openShort_PlusMinus => +1: Plus, -1: Minus 
extern "C" __declspec(dllexport) int 	LeakageTest_StartM(int index);
extern "C" __declspec(dllexport) int	OSTest_End(int index);
extern "C" __declspec(dllexport) int	LeakageTest_End(int index);
extern "C" __declspec(dllexport) int	OSTest_UnitPinM(int  pinNo, float  Iforcevalue, int count, float  *measurevalue,BOOL SourceSelect, BOOL bFloating, int index);  //unit is micro ampere(uA) & Voltage(V)  
extern "C" __declspec(dllexport) int	LeakageTest_UnitPinM(int  pinNo, float  Vforcevalue, int count, float  *measurevalue, int index); //unit is Voltage(V) & micro ampere(uA) 

#endif /* _PCIEINTERFACE_H_ */