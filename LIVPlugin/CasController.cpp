#include "CasController.h"
#include "JupCore.h"
#include "CAS4.h"
#include <Windows.h>

#define CAS_INI_FILE									"D:\\EVMS\\ENV\\Config\\1532121i1.ini"
#define CAS_CAL_FILE									"D:\\EVMS\\ENV\\Config\\1532121i1.isc"

CasController::CasController()
{
	this->ClearResult();

	m_nCASPixel = 0;
	m_nhCASHandle = 0;
}

CasController::~CasController()
{
}

void CasController::ClearResult()
{
	::ZeroMemory(&m_dTempX, sizeof(m_dTempX[0]) *_countof(m_dTempX));
	::ZeroMemory(&m_dTempY, sizeof(m_dTempY[0]) * _countof(m_dTempY));
	::ZeroMemory(&m_pdLamda, sizeof(m_pdLamda[0]) * _countof(m_pdLamda));
	::ZeroMemory(&m_pdIntVal, sizeof(m_pdIntVal[0]) * _countof(m_pdIntVal));

	m_dFirstWL = 0;
	m_dSecondWL = 0;
	m_dLAW = 0;
	m_dSPW = 0;
}

bool CasController::OpenDevice()
{
	char buf[260];
	int nRtn;
	for (int i = 0; i < CAS_DENSITY_FILTER_MAX_COUNT; i++)
		m_arrDensityFilterName[i] = "UNKNOWN";

	int USB = 1;
	if (USB)
	{	//USB Type
		casGetDeviceTypeOptionName(5, 0, buf, 30);
		nRtn = atoi(buf);
		m_nhCASHandle = casCreateDeviceEx(5, nRtn);
	}
	else
	{
		//PCI Type
		int option = casGetDeviceTypeOption(1, 0);
		m_nhCASHandle = casCreateDeviceEx(1, option);
	}

	memcpy(buf, CAS_INI_FILE, sizeof(CAS_INI_FILE));
	nRtn = casSetDeviceParameterString(m_nhCASHandle, dpidConfigFileName, buf);
	if (nRtn != 0)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Error Config File Check", 0);
		return false;
	}

	//Densiti Filter Table Read.
	const char* strSection = "DensityFilter";
	char szBuf[260];
	for (int i = 0; i < CAS_DENSITY_FILTER_MAX_COUNT; i++)
	{
		::ZeroMemory(szBuf, sizeof(szBuf));

		std::string strKey = std::to_string(i);
		::GetPrivateProfileStringA(strSection, strKey.c_str(), "UNKNOWN", szBuf, sizeof(szBuf), buf);

		std::string str(szBuf);
		//str.replace(",", ".");
		Jup::Replace(str, ",", ".");

		m_arrDensityFilterName[i] = str;
	}

	memcpy(buf, CAS_CAL_FILE, sizeof(CAS_CAL_FILE));
	nRtn = casSetDeviceParameterString(m_nhCASHandle, dpidCalibFileName, buf);
	if (nRtn != 0)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Error Calibration File Check", 0);
		return false;
	}

	nRtn = casInitialize(m_nhCASHandle, 0);
	if (nRtn != 0)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Error CAS Initial", 0);
		return false;
	}

	//CAS PARAMETER SET
	m_nCASPixel = casGetDeviceParameter(m_nhCASHandle, dpidPixels);
	int iDeadPixels = casGetDeviceParameter(m_nhCASHandle, dpidDeadPixels);
	int iVisiblePixel = casGetDeviceParameter(m_nhCASHandle, dpidVisiblePixels);
	casSetMeasurementParameter(m_nhCASHandle, mpidCheckStart, iDeadPixels);
	casSetMeasurementParameter(m_nhCASHandle, mpidCheckStop, iDeadPixels + iVisiblePixel);

	double CAS_COLOR_START = 920;// g_pINSP->m_LIVSetting.GetDouble("CAS_COLOR_START", 920.000000);
	nRtn = casSetMeasurementParameter(m_nhCASHandle, 7, CAS_COLOR_START);
	if (nRtn != 0)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Error Color Start Value Setting", 0);
		return false;
	}

	double CAS_COLOR_END = 960;// g_pINSP->m_LIVSetting.GetDouble("CAS_COLOR_END", 960.000000);
	nRtn = casSetMeasurementParameter(m_nhCASHandle, 8, CAS_COLOR_END);
	if (nRtn != 0)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Error Color End Value Setting", 0);
		return false;
	}

	casSetMeasurementParameter(m_nhCASHandle, mpidObserver, 0);  // observer 0 =  2degree; obsercer 1 = 10degree

	int CAS_INTEGRAL_TIME = 165;// g_pINSP->m_LIVSetting.GetInt("CAS_INTEGRAL_TIME", 10);
	nRtn = casSetMeasurementParameter(m_nhCASHandle, mpidIntegrationTime, CAS_INTEGRAL_TIME); // mpidColormetricStart //
	if (nRtn != 0)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Error Integration Time Setting", 0);
		return false;
	}

	bool bRtn;
	//double INSP_TEMPERATURE = g_pINSP->m_LIVSetting.GetDouble("INSP_TEMPERATURE", 25.000000);
	double INSP_TEMPERATURE = 25.000000;
	bRtn = this->CASSetDensityFilter(INSP_TEMPERATURE > 25 ? false : true);
	if (bRtn == false)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Error Filter Setting", 0);
		return false;
	}

	//int CAS_AVERAGE_COUNT = g_pINSP->m_LIVSetting.GetInt("CAS_AVERAGE_COUNT", 1);
	int CAS_AVERAGE_COUNT = 1;
	nRtn = casSetMeasurementParameter(m_nhCASHandle, mpidAverages, CAS_AVERAGE_COUNT);
	if (nRtn != 0)
	{
		//MessageBoxManage::Instance()->PostMessageBox(__FUNCTION__, "Error Average Count", 0);
		return false;
	}

	//int CAS_USE_HWTRIGGER = g_pINSP->m_LIVSetting.GetInt("CAS_USE_HWTRIGGER", 1);
	int CAS_USE_HWTRIGGER = 1;
	CASTriggerSet(CAS_USE_HWTRIGGER == 1 ? true : false);

	//CAS DarkCurrent
	CASDarkCurrent();

	return true;
}

int CasController::CloseDevice()
{
	if (casGetDeviceParameter(m_nhCASHandle, dpidInitialized))
	{
		casDoneDevice(m_nhCASHandle);
	}
	return 1;
}

void CasController::CASTriggerSet(bool bUseHWTrigger)
{	
	// Use trgflipflop mode with actual Kethley.
	// Trgsoftware mode must be used when CAS demo mode or there is no trigger cable test
	if (bUseHWTrigger == false)// trigger demo mode
	{
		casSetMeasurementParameter(m_nhCASHandle, mpidTriggerSource, trgSoftware);
	}
	else
	{
		casSetMeasurementParameter(m_nhCASHandle, mpidTriggerSource, trgFlipFlop);

		//mpidTriggerTimeout 20000ms when setting, output error after waiting time
		casSetMeasurementParameter(m_nhCASHandle, mpidTriggerTimeout, 10000);
		casSetDeviceParameter(m_nhCASHandle, dpidLine1FlipFlop, 0);
		casSetMeasurementParameter(m_nhCASHandle, mpidBusyStateLine, 2);
		//  CAS PIN 7 - Keithley 26 PIN 2
		casSetMeasurementParameter(m_nhCASHandle, mpidBusyStateLinePolarity, 0);
		casSetMeasurementParameter(m_nhCASHandle, mpidACQStateLine, 1);
		// CAS PIN 8 - Keithley 26 PIN 3
		casSetMeasurementParameter(m_nhCASHandle, mpidACQStateLinePolarity, 0);
		casSetMeasurementParameter(m_nhCASHandle, mpidTriggerOptions, 4);
		// toShowBusyState
		casSetMeasurementParameter(m_nhCASHandle, mpidTriggerOptions, 8);
		// toShowACQState // need in USB type
	}
}

void CasController::CASClearTrigger()
{
	CASTriggerSet(true);
}

bool CasController::CASSetDensityFilter(bool bCold)
{
	int nRtn = 0;
	//int CAS_FILTER_COLD = g_pINSP->m_LIVSetting.GetInt("CAS_FILTER_COLD", 2);
	int CAS_FILTER_COLD = 2;
	//int CAS_FILTER = g_pINSP->m_LIVSetting.GetInt("CAS_FILTER", 2);
	int CAS_FILTER = 2;
	nRtn = casSetMeasurementParameter(m_nhCASHandle, mpidNewDensityFilter, 3);

	if (nRtn != 0)
	{
		return false;
	}
	return true;
}

std::string CasController::GetCasDensityFilterName(int filterIdx)
{
	if (filterIdx < 0 || filterIdx >= CAS_DENSITY_FILTER_MAX_COUNT)
		return "INVALID_INDEX";

	return m_arrDensityFilterName[filterIdx];
}

int CasController::CASMeasure()
{
	int nRtn = 0;
	std::string strMsg;
	nRtn = casMeasure(m_nhCASHandle);
	if (nRtn == -16)
	{
		//g_pOP->LogError(-1, __FUNCTION__, "CAS Error:: Trigger is not acceptable");
		return -1;
	}
	else
	{
		if (nRtn != 0)
		{
			//strMsg = Format("CAS Error:: CAS Measure(Code = %1)", nRtn);
			//g_pOP->LogError(-1, __FUNCTION__, strMsg.c_str());
			return -2;
		}
	}

	nRtn = casColorMetric(m_nhCASHandle);
	if (nRtn != 0)
	{
		//g_pOP->LogError(-1, __FUNCTION__, "CAS Error:: CAS ColorMetric");
		return -3;
	}

	casGetCCT(m_nhCASHandle);
	m_nMaxAdcVal = casGetMaxAdcValue(m_nhCASHandle);

	//Spectrum Reading 
	this->CASReadSpectrum();

	double dCentroidWL = this->CASGetCentroidWL();
	double dWidth = m_dSecondWL - m_dFirstWL;	// Algorithm Apply Width Value
	m_dSPW = dWidth;

	//For cas120, after opening the program, read the CCD temperature memory and compare the CCD temperature in each measurement.When the temperature is + 3 ¡æ higher than the first measured value, dark current is required
	//Or there will be dark current during each measurement, so it is not necessary to measure the CCD temperature separately for comparison
	double dCCDTemp = casGetMeasurementParameter(m_nhCASHandle, mpidCurrentCCDTemperature);
	this->m_dCCDTemp = dCCDTemp;

	//g_pOP->LogInfo(-1, __FUNCTION__, "[CAS] CentroidWL:%f Width:%f LAW:%f CCD Temp:%f", dCentroidWL, dWidth, m_dLAW, dCCDTemp);

	return 1;
}

void CasController::CASDarkCurrent()
{
	int nRtn;
	casSetShutter(m_nhCASHandle, 0); //shutter close
	nRtn = casMeasureDarkCurrent(m_nhCASHandle);

	if (nRtn != 0)
	{
		//g_pOP->LogError(-1, __FUNCTION__, "Cas Error:: Error DarkCurrent.");
	}
	else
	{
		//g_pOP->LogInfo(-1, __FUNCTION__, "Cas DarkCurrent Complete.");
	}

	casSetShutter(m_nhCASHandle, 0); //shutter open
}

void CasController::CASReadSpectrum()
{
	if (m_nCASPixel < 2)
		return;

	for (int n = 0; n < m_nCASPixel; n++)
	{
		m_dTempX[n] = casGetXArray(m_nhCASHandle, n);
		m_dTempY[n] = casGetData(m_nhCASHandle, n);
	}

	for (int n = 0; n < m_nCASPixel; n++)
	{
		m_pdLamda[n] = m_dTempX[n];

		if (m_dTempY[n] <= 0)
		{
			m_pdIntVal[n] = -200;
		}
		else
		{
			m_pdIntVal[n] = 10 * log10(m_dTempY[n]); // dBm Transformation
		}
	}
}

double CasController::CASGetCentroidWL()
{
	double dPeakIntensity = m_pdIntVal[0];

	for (int i = 0; i < m_nCASPixel; i++)
	{
		if (m_pdIntVal[i] != 0)
		{
			dPeakIntensity = m_pdIntVal[i];
			break;
		}
	}

	int iPeakIndex = 0;
	for (int i = 0; i < m_nCASPixel; i++)
	{
		if (dPeakIntensity < m_pdIntVal[i] && m_pdIntVal[i])
		{
			dPeakIntensity = m_pdIntVal[i];
			iPeakIndex = i;
		}
	}

	double dDownTemp = 0.0f;
	double dUpTemp = 0.0f;

	m_dFirstWL = 0;
	m_dSecondWL = 0;

	int iIndex1st = 0;
	int iIndex2nd = 0;

	for (int i = 0; i < m_nCASPixel; i++)
	{
		// Centroid Seek Level == 8.5 dBm // Global variables need to be modified
		if (dPeakIntensity - m_pdIntVal[i] <= 8.5 && dPeakIntensity >= m_pdIntVal[i] && m_pdIntVal[i] != 0 && m_pdIntVal[i] != -200)
		{
			if (m_dFirstWL == 0)
			{
				m_dFirstWL = m_pdLamda[i];
				iIndex1st = i;
			}

			m_dSecondWL = m_pdLamda[i]; //  FWHM
			iIndex2nd = i;

			dUpTemp = dUpTemp + m_pdLamda[i] * m_pdIntVal[i];
			dDownTemp = dDownTemp + m_pdIntVal[i];
		}
	}

	CASCalc85dBWidth(dPeakIntensity, iIndex1st, iIndex2nd);

	m_dLAW = CASCalculateLAW(dPeakIntensity, iPeakIndex); // Algorithm Apply LAW Value

	double dCentroid = casGetCentroid(m_nhCASHandle);// CAS Calculation Centroid Value
	if (dDownTemp != 0)
	{
		dCentroid = dUpTemp / dDownTemp; // Algorithm Apply Centroid Value
	}
	return dCentroid;
}

void CasController::CASCalc85dBWidth(double dPeakIntensity, int iIndex1stWL, int iIndex2ndWL)
{
	double dWLFirst = m_pdLamda[iIndex1stWL];
	double dIntenFirt = m_pdIntVal[iIndex1stWL];

	double dWLSecond = m_pdLamda[iIndex2ndWL];
	double dIntenSecond = m_pdIntVal[iIndex2ndWL];

	double dTempWL = m_pdLamda[iIndex1stWL - 1];
	double dTempInten = m_pdIntVal[iIndex1stWL - 1];

	double dfX = 0.0000000000000;

	// Width Seek Level == 8.5 dBm // Global variable correct necessary
	double dfY = dPeakIntensity - 8.5000000000000;

	// Calc First Fitting Point
	dfX = dTempWL * ((dIntenFirt - dfY) / (dIntenFirt - dTempInten)) + dWLFirst *
		((dfY - dTempInten) / (dIntenFirt - dTempInten));
	m_dFirstWL = dfX;

	dTempWL = m_pdLamda[iIndex2ndWL + 1];
	dTempInten = m_pdIntVal[iIndex2ndWL + 1];

	// Calc Second Fitting Point
	dfX = dWLSecond * ((dTempInten - dfY) / (dTempInten - dIntenSecond)) + dTempWL *
		((dfY - dIntenSecond) / (dTempInten - dIntenSecond));
	m_dSecondWL = dfX;
}

double CasController::CASCalculateLAW(double dPeakIntensity, int iPeakIndex)
{
	double dLAW; // Left Angle Width]

	// LAW Seek Level == 10.0 dBm // Global variable correct necessary
	double dWidth10P = dPeakIntensity - 10.0;

	int iIndexFirstWidthOfLAW = 0; // first value under "dWidth10P"
	int iIndexSecondWidthOfLAW = 0; // first value upper "dWidth10P"

	for (int a = iPeakIndex; a > 0; a--)
	{
		if (m_pdIntVal[a] < dWidth10P) // value is under 0  dPeakIntensity < m_pdIntVal[i]
		{
			iIndexFirstWidthOfLAW = a;
			iIndexSecondWidthOfLAW = a + 1;
			break;
		}
	}

	// Linear interpolation
	double dX1, dY1, dX2, dY2;
	dX1 = m_pdLamda[iIndexFirstWidthOfLAW];
	dY1 = m_pdIntVal[iIndexFirstWidthOfLAW];
	dX2 = m_pdLamda[iIndexSecondWidthOfLAW];
	dY2 = m_pdIntVal[iIndexSecondWidthOfLAW];

	dLAW = (dWidth10P - dY1 + ((dY1 - dY2) / (dX1 - dX2)) * (dX1)) * ((dX1 - dX2) / (dY1 - dY2));

	return dLAW;
}
