#pragma once
// LIV calculation DLL Ver. 11

/* Error code (int error_code)
	0 : No error
	1001 : Spectrum acquire fail (only noise signal) [BA_LIV function]
	1002 : Dark correction fail (too high noise level > 50uW) [BA_LIV function]
	1003 : Spectrum saturation (MaxCCDCounts > 65,000) [BA_LIV function]
	1004 : Pulse firing & reading error [BA_LIV function]
	2001 : NTC calibration error [NTC_Cal function]
	2002 : NVM conversion error on NTC calibration parameters [NTC_Cal function]
*/
// Error code
typedef enum
{
	DLL_ErrorNoError = 0,
	DLL_ErrorSpectrumCount = -1,
	DLL_ErrorInvalidInput = -2,
} eError;


// Function to output LIV DLL version
extern "C" __declspec(dllexport) double LIV_SW_Ver();


// LVI calculation function
// Output data structure for spectral calculation
typedef struct
{
	double NTC_ON_degC;		// Average NTC_ON temperature (degC)
	double NTC_ON_R_Ohm;	// Average NTC_ON resistance (Ohm)
	double V_Dot_V;			// Average forward voltage of Dot array (V)
	double V_A_V;			// Average forward voltage of A array (V)
	double V_B_V;			// Average forward voltage of B array (V)
	double V_Flood_V;		// Average forward voltage of Flood array (V)
	double V_STD_V;			// Stdev of forward voltages for Dot/A/B arrays (V)
	double I_Dot_A;			// Average forward current of Dot array (A)
	double I_A_A;			// Average forward current of A array (A)
	double I_B_A;			// Average forward current of B array (A)
	double I_Flood_A;		// Average forward current of Flood array (A)
	double Ptot_W;			// Total optical power (W)
	double WPE_percent;		// Wall-plug efficiency (%)
	double AE_Skin_W;		// AE_Skin power (mW)
	double PWL_nm;			// Peak wavelength (nm)
	double PWL2nd_nm;		// 2nd peak wavelength of sub peak (nm)
	double SMSR_percent;	// Side mode suppression ration of sub peak (%)
	double CWL_8p5dB_nm;	// Centroid wavelength, -8.5dB (nm)
	double CWL_05p95p_nm;	// Centroid wavelength, 5%-95% (nm)
	double CWL_10p90p_nm;	// Centroid wavelength, 10%-90% (nm)
	double LAW_8p5dB_nm;	// Left ankle wavelength, -8.5dB (nm)
	double LAW_05p95p_nm;	// Left ankle wavelength, 5%-95% (nm)
	double LAW_10p90p_nm;	// Left ankle wavelength, 10%-90% (nm)
	double RAW_8p5dB_nm;	// Right ankle wavelength, -8.5dB (nm)
	double RAW_05p95p_nm;	// Right ankle wavelength, 5%-95% (nm)
	double RAW_10p90p_nm;	// Right ankle wavelength, 10%-90% (nm)
	double FWHM_nm;			// Full width half maximum (nm)
	double SpW_8p5dB_nm;	// Spectral width, -8.5dB (nm)
	double SpW_05p95p_nm;	// Spectral width, 5%-95% (nm)
	double SpW_10p90p_nm;	// Spectral width, 10%-90% (nm)
	double PD_Responsivity_mAW;	// Photo detector responsivity calculated from LIV DLL (mA/W)
	double sp_SNR;			// Signal to noise ratio of spectrum data (ppm)
	double Left_Noise;		// Noise signal level of left side of the spectrum (uW/nm)
	double Right_Noise;		// Noise signal level of right side of the spectrum (uW/nm)
	int error_code;			// Error code
	double LIV_DLL_Ver;		// LIV DLL version
} LIVOutput;

/* Definition of LIV calculation fuction
	Sp_WL_nm[]				: Wavelength data from CAS spectrometer (nm)
	Sp_Power_W[]			: Spectral power data from CAS spectrometer (W/nm, not in dB unit)
	Sp_ArrSize				: 1D array size of Sp_WL_nm[] and Sp_Power_W[] (e.g. 1800 for CAS120)
	PDCalWL_nm[]			: Wavelength array of PD calibration data from Instrument Systems (nm)
	PDCalResp_AW[]			: Responsivity array of PD calibration data from Instrument Systems (A/W)
	PDCal_ArrSize			: 1D size of PD calibration data, PDCalWL_nm[] and PDCalResp_AW[]
	VCSEL_Array				: VCSEL array code [Dot = 1, Flood = 2]
	V_Dot_input_V[]			: Forward voltage of Dot array measured from SMU for every single pulse (V)
	V_A_input_V[]			: Forward voltage of A array measured from SMU for every single pulse (V)
	V_B_input_V[]			: Forward voltage of B array measured from SMU for every single pulse (V)
	V_Flood_input_V[]		: Forward voltage of Flood array measured from SMU for every single pulse (V)
	I_Dot_input_A[]			: Forward current of Dot array measured from SMU for every single pulse (V)
	I_A_input_A[]			: Forward current of A array measured from SMU for every single pulse (V)
	I_B_input_A[]			: Forward current of B array measured from SMU for every single pulse (V)
	I_Flood_input_A[]		: Forward current of Flood array measured from SMU for every single pulse (V)
	NTC_ON_R_input_Ohm[]	: NTC_ON resistance measured from DMM or SMU for every single pulse (Ohm)
	Ipd_mA[]				: PD current array measured from DMM for every single pulse (mA)
	tPeriod_ms				: Pulse period (ms)
	N_Total					: Total number of pulses in LIV sequence
	N_Meas					: Number of pulse counts for averaging of LIV items
	N_Skin					: Number of pulse counts for AE_Skin power calculation
	tSkin_ms				: Exposure time for AE_Skin power calculation (ms)
	Ptot_Factor				: Power correlation facotr (slope)
	WL_Offset				: Wavelength correlation offset (intercept)
	MaxCCDCounts			: Max CCD counts from CAS spectrometer
*/
extern "C" __declspec(dllexport) void BA_LIV(double Sp_WL_nm[], double Sp_Power_W[], int Sp_ArrSize,
	double PDCalWL_nm[], double PDCalResp_AW[], int PDCal_ArrSize, int VCSEL_Array,
	double V_Dot_input_V[], double V_A_input_V[], double V_B_input_V[], double V_Flood_input_V[],
	double I_Dot_input_A[], double I_A_input_A[], double I_B_input_A[], double I_Flood_input_A[],
	double NTC_ON_R_input_Ohm[], double Ipd_mA[], double tPeriod_ms, double tPulse_ms, int N_Total, int N_Meas, int N_Skin, double tSkin_ms,
	double Ptot_Factor, double WL_Offset, int MaxCCDCounts,
	LIVOutput* LIV_Output);


// NTC temperature calculation function (resistance to temperature conversion)
/* Definition of NTC_Temp function
	NTC_R_Ohm				: NTC resistance to convert it to temperature (Ohm)
*/
extern "C" __declspec(dllexport) double NTC_Temp(double NTC_R_Ohm);


// NTC resistance calculation function (temperature to resistance conversion)
/* Definition of NTC_Resist function
	NTC_Temp_degC			: NTC temperature to convert it to resistance (degC)
*/
extern "C" __declspec(dllexport) double NTC_Resist(double NTC_Temp_degC);


// Rth/Tj calculation function
// Output data structure for Rth calculation
typedef struct
{
	double Rth_KW;		// Thermal resistance (K/W)
	double Tj_LO;		// Junction temperature at low current condition (L*D, L*F) (degC)
	double Tj_HI;		// Junction temperature at high current condition (H*D, H*F) (degC)
} RthOutput;

/* Definition of Rth calculation function
	CWL_LO	: CWL_05p95p_L*D or CWL_05p95p_L*F (nm)
	CWL_HI	: CWL_05p95p_H*D or CWL_05p95p_H*F (nm)
	Ptot_LO	: Ptot_L*D or Ptot_L*F (W)
	Ptot_HI	: Ptot_H*D or Ptot_H*F (W)
	WPE_LO	: WPE_L*D or WPE_H*F (%)
	WPE_HI	: WPE_H*D or WPE_H*F (%)
	NTC_OFF	: NTC_OFF_LIV* (degC)
*/
extern "C" __declspec(dllexport) void LIV_Rth(double CWL_LO, double CWL_HI, double Ptot_LO, double Ptot_HI, double WPE_LO, double WPE_HI, double NTC_OFF,
	RthOutput* Rth_Output);


// NTC calibration parameter calculation function
// Output data structure for NTC cal.
typedef struct
{
	double NTC_Cal_a;		// NTC calibration parameter a
	double NTC_Cal_b;		// NTC calibration parameter b
	double NTC_Cal_c;		// NTC calibration parameter c (c=0)
	int NTC_Cal_a1_NVM;		// NVM value for a1 (decimal)
	int NTC_Cal_a2_NVM;		// NVM value for a2 (decimal)
	int NTC_Cal_b1_NVM;		// NVM value for b1 (decimal)
	int NTC_Cal_b2_NVM;		// NVM value for b2 (decimal)
	int NTC_Cal_c1_NVM;		// NVM value for c1 (decimal)
	int NTC_Cal_c2_NVM;		// NVM value for c2 (decimal)
	int NTC_Cal_a3b3_NVM;	// NVM value for a3b3 (decimal)
	int NTC_Cal_c3_NVM;		// NVM value for b3 (decimal)
	int error_code;			// Error code
} NTCCalOutput;

/* Definition of NTC calibration function
	NTC_OFF_R_C	: NTC_OFF resistance at cold 15'C temperature (Ohm)
	NTC_OFF_R_H	: NTC_OFF resistance at hot 50'C temperature (Ohm)
*/
extern "C" __declspec(dllexport) void NTC_Cal(double NTC_OFF_R_C, double NTC_OFF_R_H, NTCCalOutput* NTCCal_Output);


// NTC temperature calculating using NTC cal. parameters from NVM
/* Definition of NTC_Temp_Cal function
	NTC_R_Ohm	: NTC resistance measured at tester (Ohm)
	a1			: NTC cal. a1 value read from NVM
	a2			: NTC cal. a2 value read from NVM
	b1			: NTC cal. b1 value read from NVM
	b2			: NTC cal. b2 value read from NVM
	a3b3		: NTC cal. a3b3 value read from NVM
*/
extern "C" __declspec(dllexport) double NTC_Temp_Cal(double NTC_R_Ohm, int a1, int a2, int b1, int b2, int a3b3);


// Temperature coefficients (tempCo) calculation function
// Output data structure for tempCo
typedef struct
{
	double tempCo_Vf;	// tempCo of forward voltage (mV/degC)
	double tempCo_Ptot;	// tempCo of optical power (%/degC)
	double tempCo_WL;	// tempCo of wavelength (nm/degC)
} tempCoOutput;

/* Definition of Rth calculation function
	NTC_ON_C	: NTC_ON temperature at HH*_LowDC condition (degC)
				  FOM names : NTC_ON_HHD_LowDC, NTC_ON_HHF_LowDC
	NTC_ON_H	: NTC_ON temperature at HH* condition (degC)
				  FOM names : NTC_ON_HHD, NTC_ON
	Vf_C		: Forward voltage at HH*_LowDC condition (V)
				  FOM names : V_Dot_HHD_LowDC, V_F_HHF_LowDC
	Vf_H		: Forward voltage at HH* condition (V)
				  FOM names : V_Dot_HHD, V_F_HHF
	Ptot_C		: Optical power at HH*_LowDC condition (W)
				  FOM names : Ptot_HHD_LowDC or Ptot_HHF_LowDC
	Ptot_H		: Optical power at HH* condition (W)
				  FOM names : Ptot_HHD or Ptot_HHF
	CWL_C		: Wavelength at HH*_LowDC condition (nm)
				  FOM names : CWL_8p5db_HHD_LowDC, CWL_8p5db_HHF_LowDC
	CWL_H		: Wavelength at HH* condition (nm)
				  FOM names : CWL_8p5db_HHD, CWL_8p5db_HHF
*/
extern "C" __declspec(dllexport) void tempCo(double NTC_ON_C, double NTC_ON_H, double Vf_C, double Vf_H, double Ptot_C, double Ptot_H, double CWL_C, double CWL_H,
	tempCoOutput* tempCo_Output);

// Post-Arm Firing sanity check function
// Output : binary flag on sanity check [1:Pass, 0:Fail]
/*
	V_Dot_input_V[]			: Forward voltage of Dot array measured from SMU for every single pulse (V)
	V_A_input_V[]			: Forward voltage of A array measured from SMU for every single pulse (V)
	V_B_input_V[]			: Forward voltage of B array measured from SMU for every single pulse (V)
	V_Flood_input_V[]		: Forward voltage of Flood array measured from SMU for every single pulse (V)
	VreadingCount			: Array size of input parameters. Should be same as 12 because we fire totally 12 pulses at Post-Arm Check procedure.
*/
extern "C" __declspec(dllexport) int PostArmCheck(double V_Dot_input_V[], double V_A_input_V[], double V_B_input_V[], double V_Flood_input_V[], int VreadingCount);