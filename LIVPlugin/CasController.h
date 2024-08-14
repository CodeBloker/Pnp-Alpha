#pragma once
#include <string>

#define CAS_DENSITY_FILTER_MAX_COUNT (8)

class CasController
{
public:
	CasController();
	~CasController();

	void ClearResult();

	bool OpenDevice();
	int CloseDevice();

	void CASTriggerSet(bool bUseHWTrigger);
	void CASClearTrigger();
	bool CASSetDensityFilter(bool bCold);
	std::string GetCasDensityFilterName(int filterIdx);
	int CASMeasure();
	void CASDarkCurrent();
	void CASReadSpectrum();
	double CASGetCentroidWL();
	void CASCalc85dBWidth(double dPeakIntensity, int iIndex1stWL, int iIndex2ndWL);
	double CASCalculateLAW(double dPeakIntensity, int iPeakIndex);

public:
	static const int m_nMaxSize = 2500;
	double m_dTempX[m_nMaxSize];
	double m_dTempY[m_nMaxSize];
	double m_pdLamda[m_nMaxSize];
	double m_pdIntVal[m_nMaxSize];

	double m_dFirstWL;
	double m_dSecondWL;
	double m_dLAW;
	double m_dSPW;
	int m_nCASPixel;

	double m_dCCDTemp;
	int m_nMaxAdcVal;

protected:
	int m_nhCASHandle;
	std::string m_arrDensityFilterName[CAS_DENSITY_FILTER_MAX_COUNT];
};

