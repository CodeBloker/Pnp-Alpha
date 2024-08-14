
#pragma once
#define MAX_SENSORLIST	256

typedef struct _SensorUnit
{
	char szSensorName[MAX_SENSORLIST];	
}SensorUnit, *pSensorUnit;

typedef struct _SENSOR_TEST
{
	SensorUnit	Sensor_Unit[MAX_SENSORLIST];
	LPSTR szName;
	int iSenCount;
}SENSOR_TEST,*pSENSOR_TEST;

extern "C" __declspec(dllexport) int SaveToJpeg(unsigned char* pImageBuffer, char* strFileName, int nWidth, int nHeight, int nQuality=80);
extern "C" __declspec(dllexport) int ChangeSplite(pSENSOR_TEST pSensor);
extern "C" __declspec(dllexport) int LoadJpegFromBuffer(unsigned char* pJpegBuffer, unsigned int nJpegBuffer, char* pBmpBuffer, int &nWidth, int &nHeight);
extern "C" __declspec(dllexport) int LoadJpegFromFile(char* strFileName, unsigned char* pBmpBuffer, int &nWidth, int &nHeight);
