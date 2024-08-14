#include "DeviceModuleGuadalupeCanyon.h"
#include "Canyon/pci_opt01_import.h"
#include "Canyon/PCIeInterface.h"
//#include "strutil.h"
//#include "sysinfoapi.h"
#include "HVS_CheckSum.h"
#include <experimental/filesystem>
#include <fstream>
#include <numeric>
#include <atltime.h>
#include "ParasDefine.h"


#include "../_INCLUDE/ProjectEvent.h"
using namespace ProjectEvent;



#pragma comment(lib, "version.lib")

const long RW_MAX_TRY = 1; //2

#define max(a,b)            (((a) > (b)) ? (a) : (b))
//#define NVM_TX_SLAVE_ID		(BANFF_TX_SLAVE_ADDRESS)	// C5.0

DeviceModuleGuadalupeCanyon::DeviceModuleGuadalupeCanyon()
{
	m_INI = new DutParameterINI();
}

DeviceModuleGuadalupeCanyon::~DeviceModuleGuadalupeCanyon()
{
	if (m_INI != NULL)
	{
		delete m_INI;
	}
}

void DeviceModuleGuadalupeCanyon::fnGetDllVersionFile(DWORD & v1, DWORD & v2)
{
#ifndef _M_X64 
	const char* strFilePath = "pci_opt01.dll";
#else
	const char* strFilePath = "pci_opt01_x64.dll";
#endif
	struct VS_VERSIONINFO {
		WORD  wLength;
		WORD  wValueLength;
		WORD  wType;
		WCHAR szKey[1];
		WORD  Padding1[1];
		VS_FIXEDFILEINFO Value;
		WORD  Padding2[1];
		WORD  Children[1];
	};
	DWORD dummy;
	DWORD dwSize = GetFileVersionInfoSize((LPCTSTR)strFilePath, &dummy);
	if (dwSize == 0)	return;
	BYTE*	pData = new BYTE[dwSize];
	if (GetFileVersionInfo((LPCTSTR)strFilePath, NULL, dwSize, pData))
	{
		VS_VERSIONINFO* fixedfileinfo = (VS_VERSIONINFO*)pData;
		byte* pVt = (byte*)&fixedfileinfo->szKey[wcslen(fixedfileinfo->szKey) + 1];
		VS_FIXEDFILEINFO* pValue = (VS_FIXEDFILEINFO*)(((byte*)fixedfileinfo) + (((byte*)pVt - (byte*)fixedfileinfo + 3) & ~3));
		v1 = pValue->dwFileVersionMS;
		v2 = pValue->dwFileVersionLS;
	}
	else
	{
		v1 = 0;
		v2 = 0;
	}
	delete []pData;
}

bool DeviceModuleGuadalupeCanyon::fnCanyonDLLInitialize(int nBoardindex)
{
	int nSocIndex = nBoardindex % 4;

	DWORD v1, v2;
	fnGetDllVersionFile(v1, v2);

	int nDeviceCount = OpenDAQDevice(); //114ms
	if (nDeviceCount <= 0)
	{
		//m_CHVSBase.ListOut(ghwndDlg, "PCIe open fail!!!");
		return false;
	}
	else 
	{
		//gDeviceIndex = 0;/*m_CHVSBase.INIReadInt(L"BOARD_SET", L"INDEX_NUM", 0);*/
		//bUSBOpen = ResetBoard(nBoardindex); //打开DAQ之后，重置一次

		if (PCI_LVDS_Init(nSocIndex, CH0))//553ms
		{
			PCI_LVDS_DdrUse(nSocIndex, CH0, FALSE);
			int nRxCardVer, nTxBoardVer;
			PCI_LVDS_GetVersion(nSocIndex, CH0, &nRxCardVer, &nTxBoardVer);
		}
		else 
		{
			//open fail. log print here.
			return false;
		}
	}

	int bChecksum = 1;
	bChecksum ? gnHeaderCnt = 4 : gnHeaderCnt = 0;
	gbChecksum_OnlyHWmode = 0;
	gbSaveChecksumFailRAW = 0;
	gbListOutOnlyCrcFail = 0;

	return true;
}

void DeviceModuleGuadalupeCanyon::BoardControl(int nBoardindex)
{
	int nSocIndex = nBoardindex % 4;
	//Vsync/VCLK effect only for parallel sensor
	//Vsync - 0: bypass , 1: inverse.
	if (m_bVSYNC == 0)
	{
		VSYNC_ByPass(nSocIndex);
	}
	else
	{
		VSYNC_Inv(nSocIndex);
	}

	//VCLK - 0: bypass , 1 : inverse
	if (m_bVCLK == 0)
	{
		VCLK_ByPass(nSocIndex);
	}
	else
	{
		VCLK_Inv(nSocIndex);
	}

	//ENB low/high
	if (m_bENB == 1)
	{
		ENB_High(nSocIndex); //enb high  
		Sleep(3);
		ENB_Low(nSocIndex);  //enb low              ΜΟ    ΞΜ
		Sleep(3);	//                                  ΡΜΜΠ
		ENB_High(nSocIndex); //enb high
		Sleep(3);
	}
	else
	{
		ENB_High(nSocIndex); //enb high  
		Sleep(3);
		ENB_Low(nSocIndex);  //enb low                 ΜΟ    
		Sleep(3);	//					                   ΡΜΜ
	}

	//RESET low/high
	if (m_bRESET == 1)
	{
		Reset_High(nSocIndex); //reset high
		Sleep(3);
		Reset_Low(nSocIndex);  //reset low         ΜΟ    ΞΜ
		Sleep(3);	  //	                           ΡΜΜΠ
		Reset_High(nSocIndex); //reset high
		Sleep(3);
	}
	else
	{
		Reset_Low(nSocIndex);  //reset low  
		Sleep(3);
		Reset_High(nSocIndex); //reset high			ΞΜΜΟ   
		Sleep(3);	  //				              ΜΠ    ΡΜ
		Reset_Low(nSocIndex);  //reset low
		Sleep(3);
	}
}

bool DeviceModuleGuadalupeCanyon::Oscillator_Set(int nBoardindex)
{
	int nSocIndex = nBoardindex % 4;
	int		tmpvalue;
	float	freq;
	DWORD   freqVal;

	freq = 12.0;
	freq *= 1000000.0; //MHz unit

	tmpvalue = 1;/*m_CHVSBase.INIReadIntSensor(L"HVS_HW", L"HW_OSC_TYPE", 0);*/
	if (tmpvalue == 0) bPGMOSC = false;
	else bPGMOSC = true;

	if (bPGMOSC == true)
	{
		//PGM MCLK 
		freqVal = (DWORD)freq;
		bool ret1 = PCI_CLK_Off(nSocIndex, CH0, FALSE);   //clock generation on
		bool ret2 = PCI_CLK_Set(nSocIndex, CH0, freqVal);
		bool ret3 = PCI_CLK_Select(nSocIndex, CH0, 1);
		return (ret1 && ret2 && ret3);
	}
	else
	{
		bool ret1 = PCI_CLK_Off(nSocIndex, CH0, FALSE);  //clock generation on
		bool ret2 = PCI_CLK_Select(nSocIndex, CH0, 0);
		//m_CHVSBase.ListOut(ghwndDlg, "Fix OSC select");
		return (ret1 && ret2);
	}
}

void DeviceModuleGuadalupeCanyon::Reset_High(int nBoardindex)
{
	int nSocIndex = nBoardindex % 4;
	PCI_SEN_Reset(nSocIndex, CH0, TRUE);
}

void DeviceModuleGuadalupeCanyon::Reset_Low(int nBoardindex)
{
	int nSocIndex = nBoardindex % 4;
	PCI_SEN_Reset(nSocIndex, CH0, FALSE);
}

void DeviceModuleGuadalupeCanyon::ENB_High(int nBoardindex)
{
	int nSocIndex = nBoardindex % 4;
	PCI_SEN_Enable(nSocIndex, CH0, TRUE);
}

void DeviceModuleGuadalupeCanyon::ENB_Low(int nBoardindex)
{
	int nSocIndex = nBoardindex % 4;
	PCI_SEN_Enable(nSocIndex, CH0, FALSE);
}

void DeviceModuleGuadalupeCanyon::VCLK_ByPass(int nBoardindex)
{
	int nSocIndex = nBoardindex % 4;
	PCI_LVDS_PclkPol(nSocIndex, CH0, 0);
	SetVCLKMode(0);
}

void DeviceModuleGuadalupeCanyon::VCLK_Inv(int nBoardindex)
{
	int nSocIndex = nBoardindex % 4;
	PCI_LVDS_PclkPol(nSocIndex, CH0, 1);
	SetVCLKMode(1); //parameter feedback for read function	
}

void DeviceModuleGuadalupeCanyon::VSYNC_ByPass(int nBoardindex)
{
	int nSocIndex = nBoardindex % 4;
	PCI_LVDS_VsyncPol(nSocIndex, CH0, 0);
	SetVSYNCMode(0);
}

void DeviceModuleGuadalupeCanyon::VSYNC_Inv(int nBoardindex)
{
	int nSocIndex = nBoardindex % 4;
	PCI_LVDS_VsyncPol(nSocIndex, CH0, 1);
	SetVSYNCMode(1);
}

void DeviceModuleGuadalupeCanyon::MCLK_Off(int nBoardindex)
{
	int nSocIndex = nBoardindex % 4;
	PCI_CLK_Off(nSocIndex, CH0, TRUE);						//PGM clock off
}

void DeviceModuleGuadalupeCanyon::SetVCLKMode(bool bVCLK)
{
	m_bVCLK = bVCLK;
}

bool DeviceModuleGuadalupeCanyon::GetVCLKMode(void)
{
	return m_bVCLK;
}

void DeviceModuleGuadalupeCanyon::SetVSYNCMode(bool bVSYNC)
{
	m_bVSYNC = bVSYNC;
}

bool DeviceModuleGuadalupeCanyon::GetVSYNCMode(void)
{
	return m_bVSYNC;
}

int DeviceModuleGuadalupeCanyon::GetMipiMode(void)
{
	return m_iMipiMode;
}

bool DeviceModuleGuadalupeCanyon::ReadI2CData(int nBoardindex, unsigned short nSlave, unsigned short nAddr, unsigned short nDataLen, unsigned char * pBuf, bool bAddr16)
{
	int nSocIndex = nBoardindex % 4;
	std::string strSlave, strAddr, strData;
	/*unsigned short nAddrLen = 1;
	unsigned short slave = BANFF_TX_SLAVE_ADDRESS;
	if (bAddr16)
	{
		nAddrLen = 2;
		slave = BANFF_RX_SLAVE_ADDRESS;
	}*/
	unsigned short nAddrLen = 2;
	unsigned short slave = BANFF_RX_SLAVE_ADDRESS;
	if (!bAddr16)
	{
		nAddrLen = 1;
		slave = BANFF_TX_SLAVE_ADDRESS;
	}
	//if (PCI_I2C_SYS_Read(nSocIndex, CH0, 0x64 << 1, nAddrLen, nAddr, nDataLen, pBuf))
	if (PCI_I2C_SYS_Read(nSocIndex, CH0, slave << 1, nAddrLen, nAddr, nDataLen, pBuf))
	{
		//for (int i = 0; i < nDataLen; i++)
		//	strData.append(Format("%02X", pBuf[i]));
		return true;
	}
	else
	{
		return false;
	}
}

bool DeviceModuleGuadalupeCanyon::WriteI2CData(int nBoardindex, unsigned short nSlave, unsigned short nAddr, unsigned short nDataLen, const unsigned char * pBuf, bool bAddr16)
{
	int nSocIndex = nBoardindex % 4;
	unsigned short nAddrLen = 1;
	unsigned short slave = BANFF_TX_SLAVE_ADDRESS;
	if (bAddr16)
	{
		nAddrLen = 2;
		slave = BANFF_RX_SLAVE_ADDRESS;
	}
	bool ret = false;
	ret = PCI_I2C_SYS_Write(nSocIndex, CH0, slave << 1, nAddrLen, nAddr, nDataLen, (unsigned char *)pBuf);
	if (!ret)
	{
		Sleep(5);
		ret = PCI_I2C_SYS_Write(nSocIndex, CH0, slave << 1, nAddrLen, nAddr, nDataLen, (unsigned char *)pBuf);
	}

	return ret;
}

std::string DeviceModuleGuadalupeCanyon::I2cReadByte(int nBoardindex, bool bAddr16, unsigned short addr, int nDataLen)
{
	BYTE uData[4] = { 0, };
	std::string strData = "0x";

	unsigned short slave = BANFF_TX_SLAVE_ADDRESS;
	if (bAddr16)
	{
		slave = BANFF_RX_SLAVE_ADDRESS;
	}

	if (ReadI2CData(nBoardindex % 4, slave, addr, nDataLen, uData, bAddr16))
	{
		for (int i = 0; i < nDataLen; i++)
		{
			char buf[50];
			sprintf(buf, "%02X", uData[i]);
			//strData.append(Format("%02X", uData[i]));
			strData.append(buf);
		}
		//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Read OK, Slave:[0x%X], Addr:[0x%02X], Data:[%s]", slave, addr, strData.c_str());
	}
	else
	{
		//g_pOP->LogError(nBoardindex, __FUNCTION__, "Read NG, Slave:[0x%X], Addr:[0x%02X]", slave, addr);
	}

	return strData;
}

bool DeviceModuleGuadalupeCanyon::I2cWrite16BitByte(int nBoardindex, bool bAddr16, unsigned short addr, unsigned short Data) 
{
	bool bOK = false;
	unsigned short nDataLen = 2;
	unsigned short slave = BANFF_TX_SLAVE_ADDRESS;
	if (bAddr16)
	{
		slave = BANFF_RX_SLAVE_ADDRESS;
	}

	unsigned short _data = ((Data & 0xff00) >> 8) | ((Data & 0x00ff) << 8);

	if (WriteI2CData(nBoardindex % 4, slave, addr, nDataLen, (unsigned char *)&_data, bAddr16))
	{
		//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Write OK, Slave:[0x%X], Addr:[0x%02X], Len:[%d], Vaule:[0x%02X]", slave, addr, nDataLen, _data);
	}
	else
	{
		//g_pOP->LogError(nBoardindex, __FUNCTION__, "Write NG, Slave:[0x%X], Addr:[0x%02X]", slave, addr);
	}
	return bOK;
}

bool DeviceModuleGuadalupeCanyon::WriteByte(int nBoardindex, bool bAddr16, unsigned short addr, unsigned char value, bool bVerify)
{
	unsigned char readVal = value;
	bool bOK = false;
	unsigned short nDataLen = 1;
	/*unsigned short slave = BANFF_TX_SLAVE_ADDRESS;
	if (bAddr16)
	{
		slave = BANFF_RX_SLAVE_ADDRESS;
	}*/
	unsigned short slave = BANFF_RX_SLAVE_ADDRESS;
	if (bAddr16)
	{
		slave = BANFF_TX_SLAVE_ADDRESS;
	}

	for (long writeTry = 0; writeTry < RW_MAX_TRY; writeTry++)
	{
		if (WriteI2CData(nBoardindex % 4, slave, addr, nDataLen, &readVal, bAddr16))
		{
			bOK = true;
			//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Write OK, RetryCnt:[%d], Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", writeTry, slave, addr, readVal);			
			break;
		}
	}
	if (!bOK)
	{
		//g_pOP->LogError(nBoardindex, __FUNCTION__, "Write NG, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", slave, addr, readVal);
		return false;
	}

	if (bVerify)
	{
		readVal = 0;
		bOK = false;
		for (long readTry = 0; readTry < RW_MAX_TRY; readTry++)
		{
			if (ReadI2CData(nBoardindex % 4, slave, addr, nDataLen, &readVal, bAddr16))
			{
				//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Read OK, RetryCnt:[%d], Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", readTry, slave, addr, readVal);
				if (readVal == value)
				{
					//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Verify OK, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X], Verify:[0x%02X]", slave, addr, readVal, value);
					bOK = true;
					break;
				}
				else
				{
					//g_pOP->LogError(nBoardindex, __FUNCTION__, "Verify NG, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X], Verify:[0x%02X]", slave, addr, readVal, value);
				}
			}
		}
		if (!bOK)
		{
			//g_pOP->LogError(nBoardindex, __FUNCTION__, "Read NG, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", slave, addr, readVal);
		}
	}
	return bOK;
}

bool DeviceModuleGuadalupeCanyon::WriteBit(int nBoardindex, bool bAddr16, unsigned short addr, int msb, int lsb, unsigned char value, bool bVerify)
{
	unsigned char bitModifyVal = 0;
	unsigned char bitMask = 0;
	unsigned char bitValue = 0;
	bitMask = 0xFF;
	// lsb
	bitMask = (bitMask >> lsb);
	bitMask = (bitMask << lsb);
	// msb
	bitMask = bitMask << (8 - msb - 1);
	bitMask = bitMask >> (8 - msb - 1);

	unsigned char readVal = 0;
	bool bOK = false;
	unsigned short nDataLen = 1;
	unsigned short slave = BANFF_TX_SLAVE_ADDRESS;
	if (bAddr16)
	{
		slave = BANFF_RX_SLAVE_ADDRESS;
	}

	for (long readTry = 0; readTry < RW_MAX_TRY; readTry++)
	{
		if (ReadI2CData(nBoardindex % 4, slave, addr, nDataLen, &readVal, bAddr16))
		{
			bOK = true;
			//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Read OK, RetryCnt:[%d], Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", readTry, slave, addr, readVal);		
			break;
		}
	}
	if (!bOK)
	{
		//g_pOP->LogError(nBoardindex, __FUNCTION__, "Read NG, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", slave, addr, readVal);
		return false;
	}

	bitValue = bitMask & readVal;
	bitModifyVal = (readVal ^ bitValue) | value;

	bOK = false;
	for (long writeTry = 0; writeTry < RW_MAX_TRY; writeTry++)
	{
		if (WriteI2CData(nBoardindex % 4, slave, addr, nDataLen, &bitModifyVal, bAddr16))
		{
			//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Write OK, RetryCnt:[%d], Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X]", writeTry, slave, addr, msb, lsb, bitModifyVal);
			bOK = true;
			break;
		}
	}
	if (!bOK)
	{
		//g_pOP->LogError(nBoardindex, __FUNCTION__, "Write NG, Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X]", slave, addr, msb, lsb, bitModifyVal);
		return false;
	}

	if (bVerify)
	{
		readVal = 0;
		bOK = false;
		for (long readTry = 0; readTry < RW_MAX_TRY; readTry++)
		{
			if (ReadI2CData(nBoardindex % 4, slave, addr, nDataLen, &readVal, bAddr16))
			{
				//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Read OK, RetryCnt:[%d], Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X]", readTry, slave, addr, msb, lsb, readVal);
				if (readVal == bitModifyVal)
				{
					//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Verify OK, Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X], Verify:[0x%02X]", slave, addr, msb, lsb, readVal, bitModifyVal);
					bOK = true;
					break;
				}
				else
				{
					//g_pOP->LogError(nBoardindex, __FUNCTION__, "Verify NG, Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X], Verify:[0x%02X]", slave, addr, msb, lsb, readVal, bitModifyVal);
				}
			}
		}
		if (!bOK)
		{
			//g_pOP->LogError(nBoardindex, __FUNCTION__, "Read NG, Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X]", slave, addr, msb, lsb, readVal);
		}
	}
	return bOK;
}

bool DeviceModuleGuadalupeCanyon::ReadByteVerify(int nBoardindex, bool bAddr16, unsigned short addr, unsigned char value)
{
	unsigned char readVal = 0;
	bool bOK = false;
	bAddr16 = false;
	unsigned short nDataLen = 1;
	unsigned short slave = BANFF_TX_SLAVE_ADDRESS;
	for (long readTry = 0; readTry < RW_MAX_TRY; readTry++)
	{
		if (ReadI2CData(nBoardindex % 4, slave, addr, nDataLen, &readVal, bAddr16))
		{
			//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Read OK, RetryCnt:[%d], Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", readTry, slave, addr, readVal);
			if (readVal == value)
			{
				bOK = true;
				//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Verify OK, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X], Verify:[0x%02X]", slave, addr, readVal, value);
				char buf[128];
				sprintf(buf, "Verify OK, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X], Verify:[0x%02X]", slave, addr, readVal, value);
				jCore->Logger("DUTPlugin.dll").LogDebug(__FUNCTION__, buf);
				break;
			}
			else
			{
				//g_pOP->LogError(nBoardindex, __FUNCTION__, "Verify NG, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X], Verify:[0x%02X]", slave, addr, readVal, value);
				char buf[128];
				sprintf(buf, "Verify NG, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X], Verify:[0x%02X]", slave, addr, readVal, value);
				jCore->Logger("DUTPlugin.dll").LogDebug(__FUNCTION__, buf);
			}
		}
	}
	if (!bOK)
	{
		//g_pOP->LogError(nBoardindex, __FUNCTION__, "Read NG, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", slave, addr, readVal);
		char buf[128];
		sprintf(buf, "Read NG, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", slave, addr, readVal);
		jCore->Logger("DUTPlugin.dll").LogDebug(__FUNCTION__, buf);
	}

	return bOK;
}

bool DeviceModuleGuadalupeCanyon::ReadBitVerify(int nBoardindex, bool bAddr16, unsigned short addr, int msb, int lsb, unsigned char value)
{
	unsigned char bitMask = 0;
	unsigned char bitValue = 0;
	bitMask = 0xFF;
	// lsb
	bitMask = (bitMask >> lsb);
	bitMask = (bitMask << lsb);
	// msb
	bitMask = bitMask << (8 - msb - 1);
	bitMask = bitMask >> (8 - msb - 1);

	unsigned char readVal = 0;
	bool bOK = false;
	bAddr16 = false;
	unsigned short nDataLen = 1;
	unsigned short slave = BANFF_TX_SLAVE_ADDRESS;
	for (long readTry = 0; readTry < RW_MAX_TRY; readTry++)
	{
		if (ReadI2CData(nBoardindex % 4, slave, addr, nDataLen, &readVal, bAddr16))
		{
			//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Read OK, RetryCnt:[%d], Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X]", readTry, slave, addr, msb, lsb, readVal);
			char buf[128];
			sprintf(buf, "Read OK, RetryCnt:[%d], Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X]", readTry, slave, addr, msb, lsb, readVal);
			jCore->Logger("DUTPlugin.dll").LogDebug(__FUNCTION__, buf);
			//jCore->SendEvent(g_DutWidget, &JDutEvent((const char*)&buf));

			bitValue = bitMask & readVal;		
			if (bitValue == value)
			{
				bOK = true;
				//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Verify OK, Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X], Verify:[0x%02X]", slave, addr, msb, lsb, bitValue, value);				
				sprintf(buf, "Verify OK, Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X], Verify:[0x%02X]", slave, addr, msb, lsb, bitValue, value);
				jCore->Logger("DUTPlugin.dll").LogDebug(__FUNCTION__, buf);
				break;
			}
			else
			{
				//g_pOP->LogError(nBoardindex, __FUNCTION__, "Verify NG, Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X], Verify:[0x%02X]", slave, addr, bitValue, value);
				sprintf(buf, "Verify NG, Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X], Verify:[0x%02X]", slave, addr, bitValue, value);
				jCore->Logger("DUTPlugin.dll").LogDebug(__FUNCTION__, buf);
				jCore->SendEvent(g_DutWidget, &JDutEvent((const char*)&buf));
			}
		}
	}
	if (!bOK)
	{
		//g_pOP->LogError(nBoardindex, __FUNCTION__, "Read NG, Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X]", slave, addr, msb, lsb, readVal);
		char buf[128];
		sprintf(buf, "Read NG, Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X]", slave, addr, msb, lsb, readVal);
		jCore->Logger("DUTPlugin.dll").LogDebug(__FUNCTION__, buf);
		jCore->SendEvent(g_DutWidget, &JDutEvent((const char*)&buf));
	}

	return bOK;
}

bool DeviceModuleGuadalupeCanyon::ReadByte(int nBoardindex, bool bAddr16, unsigned short addr, unsigned char * value)
{
	unsigned char readVal = 0;
	bool bOK = false;
	unsigned short nDataLen = 1;
	unsigned short slave = BANFF_TX_SLAVE_ADDRESS;
	if (bAddr16)
	{
		slave = BANFF_RX_SLAVE_ADDRESS;
	}

	for (long readTry = 0; readTry < RW_MAX_TRY; readTry++)
	{
		if (ReadI2CData(nBoardindex % 4, slave, addr, nDataLen, &readVal, bAddr16))
		{
			bOK = true;
			//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Read OK, RetryCnt:[%d], Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", readTry, slave, addr, readVal);
			char buf[128];
			sprintf(buf, "Read OK, RetryCnt:[%d], Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", readTry, slave, addr, readVal);
			jCore->Logger("DUTPlugin.dll").LogDebug(__FUNCTION__, buf);
			break;
		}
	}
	if (!bOK)
	{
		//g_pOP->LogError(nBoardindex, __FUNCTION__, "Read NG, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", slave, addr, readVal);
		char buf[128];
		sprintf(buf, "Read NG, Slave:[0x%X], Addr:[0x%02X], Vaule:[0x%02X]", slave, addr, readVal);
		jCore->Logger("DUTPlugin.dll").LogDebug(__FUNCTION__, buf);
		jCore->SendEvent(g_DutWidget, &JDutEvent((const char*)&buf));
	}
	*value = readVal;

	return bOK;
}

bool DeviceModuleGuadalupeCanyon::ReadBit(int nBoardindex, bool bAddr16, unsigned short addr, int msb, int lsb, unsigned char * value)
{
	unsigned char bitMask = 0;
	unsigned char bitValue = 0;
	bitMask = 0xFF;
	// lsb
	bitMask = (bitMask >> lsb);
	bitMask = (bitMask << lsb);
	// msb
	bitMask = bitMask << (8 - msb - 1);
	bitMask = bitMask >> (8 - msb - 1);

	unsigned char readVal = 0;
	bool bOK = false;
	unsigned short nDataLen = 1;
	unsigned short slave = BANFF_TX_SLAVE_ADDRESS;
	if (bAddr16)
	{
		slave = BANFF_RX_SLAVE_ADDRESS;
	}

	for (long readTry = 0; readTry < RW_MAX_TRY; readTry++)
	{
		if (ReadI2CData(nBoardindex % 4, slave, addr, nDataLen, &readVal, bAddr16))
		{
			bOK = true;
			bitValue = bitMask & readVal;
			//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Read OK, RetryCnt:[%d], Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X]", readTry, slave, addr, msb, lsb, bitValue);
			break;
		}
	}
	if (!bOK)
	{
		//g_pOP->LogError(nBoardindex, __FUNCTION__, "Read NG, Slave:[0x%X], Addr:[0x%02X %d|%d], Vaule:[0x%02X]", slave, addr, msb, lsb, readVal);
	}
	*value = bitValue;

	return bOK;
}

bool DeviceModuleGuadalupeCanyon::ReadBuffer(int nBoardindex, bool bAddr16, unsigned short addr, std::vector<unsigned char> & value)
{
	bool bOK = false;
	bAddr16 = false;
	unsigned short nDataLen = 1;
	unsigned short slave = BANFF_TX_SLAVE_ADDRESS;

	ulong ulAddr = (ulong)(addr + value.size());
	if (ulAddr > 0xFF)
	{
		return false;
	}

	for (long readTry = 0; readTry < RW_MAX_TRY; readTry++)
	{
		if (ReadI2CData(nBoardindex % 4, slave, addr, value.size(), value.data(), bAddr16))
		{
			bOK = true;
			break;
		}
	}
	if (!bOK)
	{
		//g_pOP->LogError(nBoardindex, __FUNCTION__, "Read NG, Slave:[0x%X], Addr:[0x%02X]", slave, addr);
	}
	return bOK;
}


char DeviceModuleGuadalupeCanyon::toAscii(unsigned char ch)
{
	char TEST_CHARS[] = { '`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '~', '!', '@', '#', '$', '^', '&', '*', '(', ')', '_', '+', '{', '}', '|', '[', ']', ':', '\"', ';', '\'', '<', '>', '?', ',', '.', '/', ' ' };
	if ((ch >= 'A' && ch <= 'Z') ||
		(ch >= 'a' && ch <= 'z') ||
		(ch >= '0' && ch <= '9'))
	{
		return (char)ch;
	}

	for (auto & c : TEST_CHARS)
	{
		if (c == ch)
		{
			return (char)ch;
		}
	}

	return '.';
}

bool DeviceModuleGuadalupeCanyon::fnOSTest(int nSocIndex, std::vector<float> &reading)
{
	//int ret = 0;
	//float foceValue = 0.0;
	////QList<int> retArry;
	//float readingVal = 0.0;

	//auto varMap = g_pINSP->m_BanffOSTESTOffset.GetValues();

	////g_pOP->LogInfo(nSocIndex,__FUNCTION__, "OS TEST Start");

	//ret = OSTest_StartM(nSocIndex%4, -1, TRUE, FALSE);

	//Sleep(100);

	//for (size_t i = 0; i < 36; i++) //40
	//{
	//	if (i==0 || i == 4 || i == 5 || i == 6 || i == 11 || i == 12 || i == 13 || i == 17 || i == 18 || i == 20 || i == 33 || (i > 21 && i < 32) )
	//	{
	//		reading.push_back(0.0);
	//		continue;
	//	}

	//	foceValue = std::get<float>(varMap[std::string("Force_Value_Offset_%1") + std::to_string(i)]);
	//	//ret = OSTest_UnitPinM(i, foceValue, 1, &reading[i], TRUE, FALSE, nSocIndex % 4);
	//	ret = OSTest_UnitPinM(i, foceValue, 1, &readingVal, TRUE, FALSE, nSocIndex % 4);
	//	reading.push_back(readingVal);
	//	//retArry.append(ret);

	//	//g_pOP->LogDebug(nSocIndex,__FUNCTION__, "PIN:%d - Reading:%f - Ret：%d", i, readingVal, ret);

	//}
	//ret = OSTest_End(nSocIndex%4);

	////g_pOP->LogInfo(nSocIndex, __FUNCTION__, "OS TEST End");

	return true;
}

bool DeviceModuleGuadalupeCanyon::fnDynamicReading(int nSocIndex, std::vector<float> &reading)
{
	float	measure_result;
	float	fDynamic_Sum[6] = { 0.0 };
	float	fDynamic_Avg[6] = { 0.0 };
	int		iLoopCnt = 1;
	char	szMes[80];
	char	szMode[80] = { 0 };
	WORD	woffset_value;
	int		istart, ion, idata;

	PCI_LVDS_Start(nSocIndex % 4, CH0); //2000ms
	for (int cnt = 0; cnt < iLoopCnt; cnt++)
	{
		for (istart = 0; istart < 3; istart++)
		{
			sprintf(szMes, "Current_Dynamic_Measure_offset_%d_%d", istart, nSocIndex);

			//woffset_value = IniParameter::instance()->m_BanffDynamicOffset.GetInt(szMes, 270);
			woffset_value = stoi(m_INI->m_BanffDynamicOffset[szMes]);

			if (1 != DynamicMeasureM(istart, woffset_value, &measure_result, 5, nSocIndex % 4))
			{
				//g_pOP->LogError(nSocIndex, __FUNCTION__, "Current_Dynamic_Measure Read FAIED!!! PIN:%d", istart);

				return false;
			}

			fDynamic_Sum[istart] = fDynamic_Sum[istart] + measure_result;

			char tmp_buf[100] = { 0 };
			sprintf(tmp_buf, "%.3f ", measure_result);
			//g_pOP->LogDebug(nSocIndex, __FUNCTION__, "Current_Dynamic_Measure:PIN:%d - Reading:%s", istart, tmp_buf);
		}
	}


	for (size_t ch = 0; ch < 6; ch++)
	{

		fDynamic_Avg[ch] = fDynamic_Sum[ch] / (float)(iLoopCnt);
	}

	reading.push_back(fDynamic_Avg[0]);
	reading.push_back(fDynamic_Avg[1]);
	reading.push_back(fDynamic_Avg[2]);

	//g_pOP->LogDebug(nSocIndex, __FUNCTION__, "Current_Dynamic_Measure:PIN:%d - Reading:%d", 0, fDynamic_Avg[0]);
	//g_pOP->LogDebug(nSocIndex, __FUNCTION__, "Current_Dynamic_Measure:PIN:%d - Reading:%d", 1, fDynamic_Avg[1]);
	//g_pOP->LogDebug(nSocIndex, __FUNCTION__, "Current_Dynamic_Measure:PIN:%d - Reading:%d", 2, fDynamic_Avg[2]);

	return true;
}

bool DeviceModuleGuadalupeCanyon::fnStandbyReading(int nSocIndex, std::vector<float> &reading)
{
	float	measure_result;
	float	fCurrent_Sum[6] = {0.0};
	float	fCurrent_Avg[6] = {0.0};
	int		iLoopCnt = 1;
	char	szMes[80];
	WORD	woffset_value;
	int		istart, ion, idata;

	////todo
	//for (size_t i = 0; i < 6; i++)
	//{
	//	GPIOWrite_High(i, nSocIndex % 4);
	//}


	for (int i = 0; i < iLoopCnt; i++)
	{
		for (istart = 0; istart < 3; istart++)
		{ 
			StandbyMeasureMode(0, nSocIndex % 4);//500uA
			Sleep(50);
			sprintf(szMes, "Current_Standby_Measure_offset_%d_%d", istart, nSocIndex);

			//woffset_value = g_pINSP->m_BanffStandbyOffset_500uA.GetInt(szMes, 270);
			woffset_value = stoi(m_INI->m_BanffStandbyOffset_500uA[szMes]);

			if (1 != StandbyMeasureM(istart, woffset_value, &measure_result, 5, nSocIndex % 4))
			{
				//g_pOP->LogDebug(nSocIndex, __FUNCTION__, "Current_Standby_Measure Read FAIED!!! PIN:%d", istart);

				return false;
			}
			
			fCurrent_Sum[istart] = fCurrent_Sum[istart] + measure_result;

			char tmp_buf[100] = { 0 };
			sprintf(tmp_buf, "%.3f ", measure_result);
			//g_pOP->LogDebug(nSocIndex, __FUNCTION__, "Current_Standby_Measure:PIN:%d - Reading:%s", istart, tmp_buf);
		}
	}

	for (size_t ch = 0; ch < 6; ch++)
	{

		fCurrent_Avg[ch] = fCurrent_Sum[ch] / (float)(iLoopCnt);
	}

	reading.push_back(fCurrent_Avg[0]);
	reading.push_back(fCurrent_Avg[1]);
	reading.push_back(fCurrent_Avg[2]);

	//g_pOP->LogDebug(nSocIndex, __FUNCTION__, "Current_Standby_Measure:PIN:%d - Reading:%d", 0, fCurrent_Avg[0]);
	//g_pOP->LogDebug(nSocIndex, __FUNCTION__, "Current_Standby_Measure:PIN:%d - Reading:%d", 1, fCurrent_Avg[1]);
	//g_pOP->LogDebug(nSocIndex, __FUNCTION__, "Current_Standby_Measure:PIN:%d - Reading:%d", 2, fCurrent_Avg[2]);


	return true;
}

bool DeviceModuleGuadalupeCanyon::fnDynamicOffset(int nSocIndex)
{
	//char		szMode[80] = { 0 };
	//char		szMes[80];
	//char		tmp_buf[7][20] = { 0 };
	//char		szOffser_return[2][30];
	//bool		power_on[7];
	//float		power_volt[7];

	//int			offset_result[6];
	//int			inum;
	//int			setResult = 0;
	//int			offser_return;

	//power_volt[0] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin1_Volt", 2.85);
	//power_volt[1] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin2_Volt", 1.2);
	//power_volt[2] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin3_Volt", 1.8);
	//power_volt[3] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin4_Volt", 3.5);
	//power_volt[4] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin35_Volt", 5.0);
	//power_volt[5] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin36_Volt", 5.0);
	//power_volt[6] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPinIO_Volt", 1.8); //io power.

	//sprintf(szMode, "Current_Dynamic_Measure_offset");
	//offser_return = DynamicOffset_EachPowerM(offset_result, power_volt[0], power_volt[1], power_volt[2], power_volt[3], power_volt[4], TRUE, power_volt[6], nSocIndex%4);

	//if (1 != offser_return)
	//{
	//	sprintf(szOffser_return[0], "Error code:%d", offser_return); //default sensor IO volt.
	//	//g_pOP->LogInfo(nSocIndex % 4, __FUNCTION__, "Something wrong, Check Hardware!!");
	//}
	//else
	//{
	//	//g_pOP->LogInfo(nSocIndex % 4, __FUNCTION__, "Dynamic offset ok!!");
	//}

	//for (int i = 0; i < 5; i++)
	//{
	//	sprintf(szMes, "%s_%d_%d", szMode, i, nSocIndex);
	//	g_pINSP->m_BanffDynamicOffset.SetInt(szMes, offset_result[i]);
	//	g_pINSP->m_TesterResourceInfor->fnSaveSectionMaps("CURRENT_TEST", g_pINSP->m_BanffDynamicOffset);
	//	//g_pOP->LogInfo(nSocIndex % 4, __FUNCTION__, "D.Offset_5mA[%d]:%d", i, offset_result[i]);
	//}

	return true;
}

bool DeviceModuleGuadalupeCanyon::fnStandbyOffset(int nSocIndex)
{
	//int			offset_result[6];
	//int			offser_return;
	//int			iCH = 5;
	//int			setResult = 0;

	//char		szOffser_return[2][30];
	//char		tmp_buf[7][20] = { 0 };
	//char		szMode[80] = { 0 };
	//char		szMes[80];

	//bool		power_on[7];
	//float		power_volt[7];

	//power_volt[0] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin1_Volt", 2.85);
	//power_volt[1] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin2_Volt", 1.2);
	//power_volt[2] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin3_Volt", 1.8);
	//power_volt[3] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin4_Volt", 3.5);
	//power_volt[4] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin35_Volt", 5.0);
	//power_volt[5] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin36_Volt", 5.0);
	//power_volt[6] = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPinIO_Volt", 1.8); //io power.


	//for (int i = 0; i < iCH; i++)
	//{
	//	offset_result[i] = 0;//坷橇悸 Result 府悸
	//}

	//// 500uA mode
	//StandbyMeasureMode(PWR_StandbyCurrentMeasureStep_500uA, nSocIndex%4); // 500uA 螟沥 mode
	//sprintf(szMode, "Current_Standby_Measure_offset");
	//offser_return = StandbyOffset_EachPowerM(offset_result, power_volt[0], power_volt[1], power_volt[2], power_volt[3], power_volt[4], TRUE, power_volt[6], nSocIndex%4);

	//if (1 != offser_return)
	//{
	//	sprintf(szOffser_return[0], "Error code:%d", offser_return); //default sensor IO volt.
	//	return false;
	//}

	//for (int i = 0; i < iCH; i++)
	//{
	//	sprintf(szMes, "%s_%d_%d", szMode, i, nSocIndex);
	//	g_pINSP->m_BanffStandbyOffset_500uA.SetInt(szMes, offset_result[i]);
	//	g_pINSP->m_TesterResourceInfor->fnSaveSectionMaps("CURRENT_TEST_STANDBY_500uA", g_pINSP->m_BanffStandbyOffset_500uA);
	//	//g_pOP->LogInfo(nSocIndex % 4, __FUNCTION__, "S.Offset_500uA[%d]:%d", i, offset_result[i]);
	//}


	//// 5mA mode
	//StandbyMeasureMode(PWR_StandbyCurrentMeasureStep_5mA, nSocIndex%4); // 5mA 螟沥 mode
	//sprintf(szMode, "Current_Standby_Measure_offset");
	//offser_return = StandbyOffset_EachPowerM(offset_result, power_volt[0], power_volt[1], power_volt[2], power_volt[3], power_volt[4], TRUE, power_volt[6], nSocIndex%4);

	//if (1 != offser_return)
	//{
	//	sprintf(szOffser_return[0], "Error code:%d", offser_return); //default sensor IO volt.
	//	//g_pOP->LogInfo(nSocIndex % 4, __FUNCTION__, "Something wrong, Check Hardware!!");
	//}
	//else
	//{
	//	//g_pOP->LogInfo(nSocIndex % 4, __FUNCTION__, "Standby offset ok!!");
	//}

	//for (int i = 0; i < 5; i++)
	//{
	//	sprintf(szMes, "%s_%d_%d", szMode, i, nSocIndex);
	//	g_pINSP->m_BanffStandbyOffset_5mA.SetInt(szMes, offset_result[i]);
	//	g_pINSP->m_TesterResourceInfor->fnSaveSectionMaps("CURRENT_TEST_STANDBY_5mA", g_pINSP->m_BanffStandbyOffset_5mA);
	//	//g_pOP->LogInfo(nSocIndex % 4, __FUNCTION__, "S.Offset_5mA[%d]:%d", i, offset_result[i]);
	//}

	return true;
}

bool DeviceModuleGuadalupeCanyon::CheckDeviceIsActive(int nBoardindex)
{
	unsigned char byteVal = 0;
	if (!ReadBit(nBoardindex % 4, false, 0xB4, 2, 0, &byteVal))
	{
		return false;
	}

	//Verify FSM is Idle,
	//RegAddr 0xB4[2:0] = 0x2
	return (byteVal == 0x03);
}

#define	Finish_Valid_Script(x)	\
		if (x) {				\
			bSkipContinue = true; break;}

bool DeviceModuleGuadalupeCanyon::RegisterScriptParse(int nBoardindex, std::string scriptName, bool bParseOnly, const std::vector<CommandPair> & script)
{
	bool bSkipContinue = false;
	bool bValidValue = true;
	//QStringList paramsList;
	std::vector<std::string> paramsList;

	//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Begin script:%s", scriptName.toLatin1().data());

	for (auto & item : script)
	{
		//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "CMD:%s, Data:%s", item.first.toLatin1().data(), item.second.toLatin1().data());

		if (item.first == "I2C_W" && ( scriptName.find("REGISTER") != std::string::npos || scriptName.find("[LightDPC") != std::string::npos))
		{
			//item.first.startsWith("0x") && item.first.length() == 6
			// REGISTER  eg: 0x0303	0x02
			//WRTBYTE [HEX_ADDR] [HEX_VAL]

			unsigned short addr = 0;
			unsigned char value = 0;

			paramsList = Jup::Split(item.second, ' ');
			Finish_Valid_Script(paramsList.size() < 2)

			//Get addr
			if (!paramsList.empty())
			{
				//addr = paramsList.takeFirst().tounsigned short(&bValidValue, 16);
				addr = static_cast<unsigned short>(std::strtoul(paramsList.front().c_str(), NULL, 16));
				paramsList.erase(paramsList.begin());
				Finish_Valid_Script(!bValidValue)
			}

			//Get value
			if (!paramsList.empty())
			{
				//value = paramsList.takeFirst().tounsigned short(&bValidValue, 16);
				value = static_cast<unsigned short>(std::strtoul(paramsList.front().c_str(), NULL, 16));
				paramsList.erase(paramsList.begin());
				Finish_Valid_Script(!bValidValue)
			}

			if (!bParseOnly && addr > 0x0000 && value >= 0x00)
			{
				bool ret = WriteByte(nBoardindex % 4, true, addr, value, false);
				if (!ret == true)
				{
					bSkipContinue = true;
				}
			}
		}
		
		else if (item.first == "RDBYTE")
		{
			unsigned char addr = 0;
			bool bVerify = false;
			unsigned char verify = 0;
			int count = 1;
			
			paramsList = Jup::Split(item.second, ' '); 
			Finish_Valid_Script(paramsList.size() < 1)

			//Get addr
			if (!paramsList.empty())
			{
				//addr = paramsList.takeFirst().tounsigned short(&bValidValue, 16);
				addr = static_cast<unsigned short>(std::strtoul(paramsList.front().c_str(), NULL, 16));
				paramsList.erase(paramsList.begin());
				Finish_Valid_Script(!bValidValue)
			}

			//Get verify
			if (!paramsList.empty())
			{
				//verify = paramsList.takeFirst().tounsigned short(&bValidValue, 16);
				verify = static_cast<unsigned short>(std::strtoul(paramsList.front().c_str(), NULL, 16));
				paramsList.erase(paramsList.begin());
				if (bValidValue)
					bVerify = true;
			}

			//Get count
			if (!paramsList.empty())
			{
				//count = paramsList.takeFirst().tounsigned short(&bValidValue, 10);
				count = static_cast<unsigned short>(std::strtoul(paramsList.front().c_str(), NULL, 10));
				paramsList.erase(paramsList.begin());
				count = max(1, count);
			}

			if (!bParseOnly)
			{
				for (long retry = 0; retry < count; retry++)
				{
					unsigned char data = 0;
					bool ret = bVerify ?
						ReadByteVerify(nBoardindex % 4, false, addr, verify) :
						ReadByte(nBoardindex % 4, false, addr, &data);
					if (ret)
					{
						bSkipContinue = false;
						break;
					}
					else
					{
						bSkipContinue = true;
					}
				}
			}
		}
		else if (item.first == "RDBIT")
		{
			//RDBIT [HEX_ADDR] [MSB:LSB] [HEX_VAL] [COUNTS]
			//RDBIT [HEX_ADDR] [MSB:LSB] [COUNTS]

			unsigned char addr = 0;
			int msb = 0;
			int lsb = 0;
			//QStringList msb_lsb_split;
			std::vector<std::string> msb_lsb_split;
			bool bVerify = false;
			unsigned char verify = 0;
			int count = 1;

			std::string str = item.second;
			Jup::Replace(str, "[", " [");
			paramsList = Jup::Split(str, ' ', true);
			if (paramsList.size() == 1 && paramsList[0].find("[0:0]") != std::string::npos)
			{
				bSkipContinue = false;
				continue;
			}
			Finish_Valid_Script(paramsList.size() < 2)

			//Get addr
			if (!paramsList.empty())
			{
				//addr = paramsList.takeFirst().tounsigned short(&bValidValue, 16);
				addr = static_cast<unsigned short>(std::strtoul(paramsList.front().c_str(), NULL, 16));
				paramsList.erase(paramsList.begin());
				Finish_Valid_Script(!bValidValue)
			}

			//Get msb,lsb
			if (!paramsList.empty())
			{
				str = paramsList.front();
				paramsList.erase(paramsList.begin());
				//str.remove('[');
				std::remove(str.begin(), str.end(), '[');
				//str.remove(']');
				std::remove(str.begin(), str.end(), ']');
				//msb_lsb_split = str.split(':');
				msb_lsb_split = Jup::Split(str, ':');
				Finish_Valid_Script(msb_lsb_split.size() != 2)

				//msb = msb_lsb_split.at(0).tounsigned short(&bValidValue, 10);
				msb = static_cast<unsigned short>(std::strtoul(msb_lsb_split.at(0).c_str(), NULL, 10));
				Finish_Valid_Script(!bValidValue)

				//lsb = msb_lsb_split.at(1).tounsigned short(&bValidValue, 10);
				lsb = static_cast<unsigned short>(std::strtoul(msb_lsb_split.at(1).c_str(), NULL, 10));
				Finish_Valid_Script(!bValidValue)
			}

			//Get verify
			if (!paramsList.empty())
			{
				//verify = paramsList.takeFirst().tounsigned short(&bValidValue, 16);				
				verify = static_cast<unsigned short>(std::strtoul(paramsList.front().c_str(), NULL, 16));
				paramsList.erase(paramsList.begin());
				if (bValidValue)
					bVerify = true;
				Finish_Valid_Script(!bValidValue && !(msb == 0 && lsb == 0))
			}

			//Get count 16
			if (!paramsList.empty())
			{
				//count = paramsList.takeFirst().tounsigned short(&bValidValue, 16);
				count = static_cast<unsigned short>(std::strtoul(paramsList.front().c_str(), NULL, 16));
				paramsList.erase(paramsList.begin());
				count = max(1, count);
			}

			if (!bParseOnly)
			{
				for (int retry = 0; retry < count; retry++)
				{
					unsigned char data = 0;
					bool ret = bVerify ?
						ReadBitVerify(nBoardindex % 4, false, addr, msb, lsb, verify) :
						ReadBit(nBoardindex % 4, false, addr, msb, lsb, &data);
					if (ret)
					{
						bSkipContinue = false;
						break;
					}
					else
					{
						bSkipContinue = true;
					}
				}
			}
		}
		else if (item.first == "WRTBYTE")
		{
			//WRTBYTE [HEX_ADDR] [HEX_VAL]

			unsigned char addr = 0;
			unsigned char value = 0;

			paramsList = Jup::Split(item.second, ' ');
			Finish_Valid_Script(paramsList.size() < 2)

			//Get addr
			if (!paramsList.empty())
			{
				//addr = paramsList.takeFirst().tounsigned short(&bValidValue, 16);
				addr = static_cast<unsigned short>(std::strtoul(paramsList.front().c_str(), NULL, 16));
				paramsList.erase(paramsList.begin());
				Finish_Valid_Script(!bValidValue)
			}

			//Get value
			if (!paramsList.empty())
			{
				//value = paramsList.takeFirst().tounsigned short(&bValidValue, 16);
				value = static_cast<unsigned short>(std::strtoul(paramsList.front().c_str(), NULL, 16));
				paramsList.erase(paramsList.begin());
				Finish_Valid_Script(!bValidValue)
			}

			if (!bParseOnly)
			{
				bool ret = WriteByte(nBoardindex % 4, false, addr, value, false);
				if (!ret)
				{
					bSkipContinue = true;
				}
			}
		}
		else if (item.first == "WRTBIT")
		{
			unsigned char addr = 0;
			int msb = 0;
			int lsb = 0;
			//QStringList msb_lsb_split;
			std::vector<std::string> msb_lsb_split;
			bool bVerify = false;
			unsigned char verify = 0;
			unsigned char value = 0;

			std::string str = item.second;
			paramsList = Jup::Split(str, ' ');
			Finish_Valid_Script(paramsList.size() < 3)

			//Get addr
			if (!paramsList.empty())
			{
				//addr = paramsList.takeFirst().tounsigned short(&bValidValue, 16);
				addr = static_cast<unsigned short>(std::strtoul(paramsList.front().c_str(), NULL, 16));
				paramsList.erase(paramsList.begin());
				Finish_Valid_Script(!bValidValue)
			}

			//Get msb,lsb
			if (!paramsList.empty())
			{
				str = paramsList.front();
				//str.remove('[');
				std::remove(str.begin(), str.end(), '[');
				//str.remove(']');
				std::remove(str.begin(), str.end(), ']');
				//msb_lsb_split = str.split(':');
				msb_lsb_split = Jup::Split(str, ':');
				Finish_Valid_Script(msb_lsb_split.size() != 2)

				//msb = msb_lsb_split.at(0).tounsigned short(&bValidValue, 10);
				msb = static_cast<unsigned short>(std::strtoul(msb_lsb_split.at(0).c_str(), NULL, 10));
				Finish_Valid_Script(!bValidValue)

				//lsb = msb_lsb_split.at(1).tounsigned short(&bValidValue, 10);
				lsb = static_cast<unsigned short>(std::strtoul(msb_lsb_split.at(1).c_str(), NULL, 10));
				Finish_Valid_Script(!bValidValue)
			}

			//Get value
			if (!paramsList.empty())
			{
				//value = paramsList.takeFirst().tounsigned short(&bValidValue, 16);
				value = static_cast<unsigned short>(std::strtoul(paramsList.front().c_str(), NULL, 16));
				paramsList.erase(paramsList.begin());
				Finish_Valid_Script(!bValidValue)
			}

			if (!bParseOnly)
			{
				bool ret = WriteBit(nBoardindex % 4, false, addr, msb, lsb, value, false);
				if (!ret)
				{
					bSkipContinue = true;
				}
			}
		}
		
		else if (item.first == "SLEEP")
		{
		int ms = stoi(item.second);
		if (ms == 0)
		{
			break;
		}
		//QThread::msleep(ms);
		}

		else if (item.first == "ENB")
		{
			if (item.second == "0")
				ENB_Low(nBoardindex);
			else
				ENB_High(nBoardindex);
		}
		else if (item.first == "RESET")
		{
			if (item.second == "0")
				Reset_Low(nBoardindex);
			else
				Reset_High(nBoardindex);
		}
		else if (item.first == "MCLK")
		{
			if (item.second == "0")
				MCLK_Off(nBoardindex);
		}
		else if (item.first == "POWER" ||
		item.first == "ECHO" ||
		item.first == "SLAVE")
		{
		}

		if (bSkipContinue)
		{
			break;
		}
	}

	//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Finish script:%s, result:%d", scriptName.toLatin1().data(), !bSkipContinue);

	return !bSkipContinue;
}

int DeviceModuleGuadalupeCanyon::fnPowerOnCanyouPinVoltSet(int nSocIndex, const char* sTX_RegisterFile, const char* sRX_RegisterFile)
{
	bool status = 0;
	int nCheckTxBoard = 0;
	PCI_LVDS_TxBoardCheck(nSocIndex %4, CH0, &nCheckTxBoard);
	if (nCheckTxBoard != 0)
	{
		//g_pOP->LogError(nSocIndex,__FUNCTION__, "TxBoard check Error!!");
		//MessageBoxManage::Instance()->PostMessageBox("TxBoard!", QString("TxBoard check Error! No TxBoard OR No Power,socket:%1").arg(nSocIndex+1), 0);
		//return m_ErrorCodeSetting.GetInt("EC_TXBoardCheckFail",-8888);
		//return stoi(m_INI->m_ErrorCodeSetting["EC_TXBoardCheckFail"]);
		return -8888;
	}
	//g_pOP->LogDebug(nSocIndex,__FUNCTION__, "TxBoard OK!!");

	int bSetResult = 0;
	char	tmp_buf[7][20] = { 0 };
	int		inum;
	int		setResult = 0;

	//read from INI 
	//float v1 = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin1_Volt", 2.85);
	float v1 = stof(m_INI->m_BanffPinPowerSetting["HW_PowerPin1_Volt"]);
	//float v2 = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin2_Volt", 1.2);
	float v2 = stof(m_INI->m_BanffPinPowerSetting["HW_PowerPin2_Volt"]);
	//float v3 = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin3_Volt", 1.8);
	float v3 = stof(m_INI->m_BanffPinPowerSetting["HW_PowerPin3_Volt"]);
	//float v4 = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin4_Volt", 3.5);
	float v4 = stof(m_INI->m_BanffPinPowerSetting["HW_PowerPin4_Volt"]);
	//float v5 = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPin35_Volt", 5.0);
	float v5 = stof(m_INI->m_BanffPinPowerSetting["HW_PowerPin35_Volt"]);
	//float vIO = g_pINSP->m_BanffPinPowerSetting.GetDouble("HW_PowerPinIO_Volt", 1.8); //io power.
	float vIO = stof(m_INI->m_BanffPinPowerSetting["HW_PowerPinIO_Volt"]);

	int bSetResult1 = Program_PowerSetM(0, v1, nSocIndex%4);
	Sleep(10);
	int bSetResult2 = Program_PowerSetM(1, v2, nSocIndex%4);
	Sleep(10);
	int bSetResult3 = Program_PowerSetM(2, v3, nSocIndex%4);
	Sleep(10);
	int bSetResult4 = Program_PowerSetM(3, v4, nSocIndex%4);
	Sleep(10);
	int bSetResult5 = Program_PowerSetM(4, v5, nSocIndex%4);
	Sleep(10);
	int bSetResult6 = Program_PowerOnOff_Fix36M(TRUE, nSocIndex%4);
	Sleep(5);
	int bSetResult7 = IOlevel_SetM(/*g_pINSP->m_BanffPinPowerSetting["HW_PowerPinIO_Volt"]*/vIO, nSocIndex%4);
	////GPIOWrite_High(0, nSocIndex%4);	//1: High
	if (!bSetResult1 || !bSetResult2 || !bSetResult3 || !bSetResult4 || !bSetResult5 || !bSetResult6 || !bSetResult7 )
	{
		//g_pOP->LogError(nSocIndex, __FUNCTION__, "Socket Pin voltage set Failed");
	}

	int				iPowerSet;

	bool ret2 = PCI_I2C_SYS_Reset(nSocIndex % 4, CH0);

	bool ret1 = Oscillator_Set(nSocIndex%4);
	Sleep(10);
	BoardControl(nSocIndex%4);

	if (!ret1 || !ret2)
	{
		//g_pOP->LogError(nSocIndex,__FUNCTION__, "Socket Pin voltage set Failed");
		//return g_pINSP->m_ErrorCodeSetting.GetInt("EC_PowerOnSetVoltFail", -8888);
		return stoi(m_INI->m_ErrorCodeSetting["EC_PowerOnSetVoltFail"]);
	}

	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Power on-- Socket Pin voltage set.Socket:%d",nSocIndex);
	return true;
}

int DeviceModuleGuadalupeCanyon::fnPowerOnCanyouPinVoltSetForOSTest(int nSocIndex)
{

	bool status = 0;
	int nCheckTxBoard = 0;
	PCI_LVDS_TxBoardCheck(nSocIndex % 4, CH0, &nCheckTxBoard);
	if (nCheckTxBoard != 0)
	{
		//g_pOP->LogError(nSocIndex,__FUNCTION__, "TxBoard check Error!!");

		//return g_pINSP->m_ErrorCodeSetting.GetInt("EC_TXBoardCheckFail", -8888);
		return stoi(m_INI->m_ErrorCodeSetting["EC_TXBoardCheckFail"]);
	}
	//g_pOP->LogDebug(nSocIndex,__FUNCTION__, "TxBoard OK!!");

	int bSetResult = 0;
	char	tmp_buf[7][20] = { 0 };
	int		inum;
	int		setResult = 0;

	bSetResult = Program_PowerSetM(0, 0.0, nSocIndex % 4);
	Sleep(10);
	bSetResult = Program_PowerSetM(1, 0.0, nSocIndex % 4);
	Sleep(10);
	bSetResult = Program_PowerSetM(2, 0.0, nSocIndex % 4);
	Sleep(10);
	bSetResult = Program_PowerSetM(3, 0.0, nSocIndex % 4);
	Sleep(10);
	bSetResult = Program_PowerSetM(4, 0.0, nSocIndex % 4);
	Sleep(10);
	bSetResult = Program_PowerOnOff_Fix36M(TRUE, nSocIndex % 4);
	Sleep(5);


	return true;
}

bool DeviceModuleGuadalupeCanyon::fnPowerOnCanyouAfterRegister(int nSocIndex) {

	bool ret1 = PCI_LVDS_SelectInput(nSocIndex%4, CH0, 0); //0:MIPI(default), 1:Parallel

	bool ret2 = PCI_LVDS_SetDataMode(nSocIndex%4, CH0, 1);  //0:8bit->1Lane, 1:16bit->2Lane, 3:32bit->4Lane

	//bool ret3 = PCI_LVDS_CheckSum(nSocIndex%4, CH0, TRUE);
	bool ret3 = fnSetModuleCheckSum(nSocIndex % 4, false);

	return (ret1&&ret2&&ret3);
}

bool DeviceModuleGuadalupeCanyon::fnSetModuleCheckSum(int nSocIndex,bool set) 
{
	bool ret3 = PCI_LVDS_CheckSum(nSocIndex % 4, CH0, set);

	return ret3;
}


bool DeviceModuleGuadalupeCanyon::fnPowerOFF(int nSocIndex)
{
	int ret = false;
	int deviceCount = 0;
	int nCheckTxBoard = 0;

	//m_BanffControl.fnSaveAllTXDumpToCsv(nSocIndex % 4, "Before_PowerOFF", sDumpFilePrefix); ,在devcontrol执行

	PCI_LVDS_TxBoardCheck(nSocIndex%4, CH0, &nCheckTxBoard);
	if (nCheckTxBoard != 0)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "TxBoard Check Error!!"); //开机的时候调用，log还没初始化
		deviceCount = OpenDAQDevice();
	}

	if (deviceCount == 1)
	{
		//log print

	}

	ret = PCI_LVDS_Stop(nSocIndex%4, CH0);
	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "PCI_LVDS_Stop,Socket:%d", nSocIndex);
	PCI_SEN_Reset(nSocIndex%4, CH0, FALSE);
	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "PCI_SEN_Reset,Socket:%d", nSocIndex);
	PCI_SEN_Enable(nSocIndex%4, CH0, FALSE);
	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "PCI_SEN_Enable,Socket:%d", nSocIndex);
	PCI_CLK_Off(nSocIndex%4, CH0, TRUE);	    //MCLK off
	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "PCI_CLK_Off,Socket:%d", nSocIndex);
	

	ret = Program_PowerSetM(0, 0, nSocIndex%4);
	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Shutdown PIN:0,Socket:%d", nSocIndex);
	ret = Program_PowerSetM(1, 0, nSocIndex%4);
	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Shutdown PIN:1,Socket:%d", nSocIndex);
	ret = Program_PowerSetM(2, 0, nSocIndex%4);
	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Shutdown PIN:2,Socket:%d", nSocIndex);
	ret = Program_PowerSetM(3, 0, nSocIndex%4);
	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Shutdown PIN:3,Socket:%d", nSocIndex);
	ret = Program_PowerSetM(4, 0, nSocIndex%4);
	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Shutdown PIN:4,Socket:%d", nSocIndex);

	ret = Program_PowerOffAllM(nSocIndex % 4);
		    //Power off
	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Shutdown All,Socket:%d", nSocIndex);

	//g_pOP->LogInfo(nSocIndex, __FUNCTION__, "Power off Complete.Socket:%d", nSocIndex);
	return ret;
}


void Calc_CheckSum(LPBYTE pDataBuffer, int nWidthSize, int nHeight, int nMode)
{
	int gnHeaderCnt = 4;
	bool gbListOutOnlyCrcFail = 0;
	int i, dummyadd = 0, nErrorLines = 0;
	unsigned short	crcresult;
	BYTE			crc1, crc2, crc3, crc4, crcLS, crcMS, ECC = 0 /*GetChecksum_ECC()*/;
	LPBYTE dwAddress;
	if (nWidthSize % 4) dummyadd = 2;

	if (nMode) //Only Checking the hw result!!
	{
		for (i = 0; i < nHeight; i++)
		{
			dwAddress = (pDataBuffer + ((nWidthSize + gnHeaderCnt + dummyadd)*i));
			crc4 = *(dwAddress + (nWidthSize + 3));		//Logic result
			if (0x00 != crc4)
			{
				if (!gbListOutOnlyCrcFail)
				{
					crc1 = *(dwAddress + (nWidthSize));		//ECC
					crc2 = *(dwAddress + (nWidthSize + 1));		//CRC_LS
					crc3 = *(dwAddress + (nWidthSize + 2));		//CRC_MS
					//m_CHVSBase.ListOut(ghwndDlg, "%dL %02X,%02X,%02X,%02X", i + 1, crc1, crc2, crc3, crc4);
				}
				nErrorLines--;
			}
		}
	}
	else	//Check software calculation
	{
		for (i = 0; i < nHeight; i++)
		{
			dwAddress = (pDataBuffer + ((nWidthSize + gnHeaderCnt + dummyadd)*i));
			crcresult = crc16_fast(dwAddress, nWidthSize);
			crc1 = *(dwAddress + (nWidthSize));		//ECC
			crc2 = *(dwAddress + (nWidthSize + 1));		//CRC_LS
			crc3 = *(dwAddress + (nWidthSize + 2));		//CRC_MS
			crc4 = *(dwAddress + (nWidthSize + 3));		//Logic result
			crcLS = crcresult & 0x00FF;				//LOBYTE(crcresult);
			crcMS = (crcresult & 0xFF00) >> 8;		//HIBYTE(crcresult);
			if (crcLS != crc2 || crcMS != crc3 || ECC != crc1 || 0x00 != crc4)
			{
				if (!gbListOutOnlyCrcFail)
				{
					//m_CHVSBase.ListOut(ghwndDlg, "%dL %02X,%02X,%02X,-- vs --%02X,%02X,%02X,%02X", i + 1, ECC, crcLS, crcMS, crc1, crc2, crc3, crc4);
				}
				nErrorLines--;
			}
		}
	}
	if (nErrorLines != 0)
	{
		//m_CHVSBase.ListOut(ghwndDlg, "CheckSum:%dLnEr", nErrorLines);
		bool gbSaveChecksumFailRAW = 0;
		if (gbSaveChecksumFailRAW)
		{
			/*char filename[260];
			static int nIndex = 0;
			sprintf(filename, "%s\\Bin\\CheckSumErrImg_%04d.raw", gRootDir, nIndex++);*/
			//SaveToRawImg(pDataBuffer, (nWidthSize + gnHeaderCnt + dummyadd) * nHeight, filename);
		}
	}
}

void Shift10BitMode(unsigned char* pImage, unsigned char* pDest, unsigned int nWidth, unsigned int nHeight)
{
	int gnHeaderCnt = 4;
	unsigned int i, j;
	unsigned int nByteWidth = ALIGNED_SIZE(((nWidth * 5) >> 2) + gnHeaderCnt, 3);
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j += 4)
		{
			memcpy(&pDest[i*nWidth + j], &pImage[i*nByteWidth + ((j * 5) >> 2)], 4);
		}
	}
}

void RawToBmp(int iMode, BYTE *pRawBuffer, BYTE *pBmpBuffer, int size_x, int size_y)
{
	LPBYTE		pImageData, pImageTemp, pImageTemp1;
	BYTE		r, g, b;
	int			i, j;
	BOOL		bInterpolation = TRUE; //FALSE;

	pImageData = pRawBuffer + size_x * (size_y - 1);

	switch (iMode) {
	case 5:  //BlackWhite		//kcshin 2016.01.04;; 捞傈波啊 救登绰 版快啊 惯积窍咯 荐沥...
		for (j = 0; j < size_y; j++)
		{
			pImageData = pRawBuffer + size_x * (size_y - 1 - j);
			for (i = 0; i < size_x; i++)
			{
				*pBmpBuffer++ = pImageData[i];
				*pBmpBuffer++ = pImageData[i];
				*pBmpBuffer++ = pImageData[i];
			}
		}
		break;
	case 4:	//GRBG			//GRGR
							//BGBG
							//GRGR
							//BGBG
		for (i = 0; i < size_y - 2; i += 2) {
			pImageTemp = pImageData;
			pImageTemp1 = pImageData - size_x;
			for (j = 0; j < size_x - 2; j += 2) {
				r = pImageTemp1[1];
				b = pImageTemp[0];
				g = (pImageTemp[1] + pImageTemp1[0]) >> 1;
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;

				r = pImageTemp1[0];
				b = pImageTemp[1];
				g = (pImageTemp[0] + pImageTemp1[1]) >> 1;
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;
			}
			memcpy(pBmpBuffer, pBmpBuffer - 3, 3);
			memcpy(pBmpBuffer + 3, pBmpBuffer, 3);
			pBmpBuffer += 6;

			pImageData -= size_x;
			pImageTemp = pImageData;
			pImageTemp1 = pImageData - size_x;

			for (j = 0; j < size_x - 2; j += 2) {
				b = pImageTemp1[0];
				g = (pImageTemp[0] + pImageTemp1[1]) >> 1;
				r = pImageTemp[1];
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;

				r = pImageTemp[0];
				g = (pImageTemp[1] + pImageTemp1[0]) >> 1;
				b = pImageTemp1[1];
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;

			}
			memcpy(pBmpBuffer, pBmpBuffer - 3, 3);
			memcpy(pBmpBuffer + 3, pBmpBuffer, 3);
			pBmpBuffer += 6;
			pImageData -= size_x;
		}
		memcpy(pBmpBuffer, pBmpBuffer - size_x * 3, size_x * 3);
		memcpy(pBmpBuffer + (size_x * 3), pBmpBuffer - size_x * 3, size_x * 3);
		break;
	case 2:	//RGGB				//RGRG
								//GBGB
								//RGRG
								//GBGB
		for (i = 0; i < size_y - 2; i += 2) {
			pImageTemp = pImageData;
			pImageTemp1 = pImageData - size_x;
			for (j = 0; j < size_x - 2; j += 2) {
				r = pImageTemp1[0];
				b = pImageTemp[1];
				g = (pImageTemp[0] + pImageTemp1[1]) >> 1;
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;

				r = pImageTemp1[1];
				b = pImageTemp[0];
				g = (pImageTemp[1] + pImageTemp1[0]) >> 1;
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;
			}
			memcpy(pBmpBuffer, pBmpBuffer - 3, 3);
			memcpy(pBmpBuffer + 3, pBmpBuffer, 3);
			pBmpBuffer += 6;

			pImageData -= size_x;
			pImageTemp = pImageData;
			pImageTemp1 = pImageData - size_x;

			for (j = 0; j < size_x - 2; j += 2) {
				b = pImageTemp1[1];
				g = (pImageTemp[1] + pImageTemp1[0]) >> 1;
				r = pImageTemp[0];
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;

				r = pImageTemp[1];
				g = (pImageTemp[0] + pImageTemp1[1]) >> 1;
				b = pImageTemp1[0];
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;
			}
			memcpy(pBmpBuffer, pBmpBuffer - 3, 3);
			memcpy(pBmpBuffer + 3, pBmpBuffer, 3);
			pBmpBuffer += 6;
			pImageData -= size_x;
		}
		memcpy(pBmpBuffer, pBmpBuffer - size_x * 3, size_x * 3);
		memcpy(pBmpBuffer + (size_x * 3), pBmpBuffer - size_x * 3, size_x * 3);
		break;
	case 1:	//BGGR				//BGBG
								//GRGR
								//BGBG
								//GRGR
		for (i = 0; i < size_y - 2; i += 2) {
			pImageTemp = pImageData;
			pImageTemp1 = pImageData - size_x;
			for (j = 0; j < size_x - 2; j += 2) {
				r = pImageTemp[1];
				b = pImageTemp1[0];
				g = (pImageTemp[0] + pImageTemp1[1]) >> 1;
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;

				r = pImageTemp[0];
				b = pImageTemp1[1];
				g = (pImageTemp[1] + pImageTemp1[0]) >> 1;
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;
			}
			memcpy(pBmpBuffer, pBmpBuffer - 3, 3);
			memcpy(pBmpBuffer + 3, pBmpBuffer, 3);
			pBmpBuffer += 6;
			pImageData -= size_x;
			pImageTemp = pImageData;
			pImageTemp1 = pImageData - size_x;

			for (j = 0; j < size_x - 2; j += 2) {
				b = pImageTemp[0];
				g = (pImageTemp[1] + pImageTemp1[0]) >> 1;
				r = pImageTemp1[1];
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;

				r = pImageTemp1[0];
				g = (pImageTemp[0] + pImageTemp1[1]) >> 1;
				b = pImageTemp[1];
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;
			}
			memcpy(pBmpBuffer, pBmpBuffer - 3, 3);
			memcpy(pBmpBuffer + 3, pBmpBuffer, 3);
			pBmpBuffer += 6;
			pImageData -= size_x;
		}
		memcpy(pBmpBuffer, pBmpBuffer - size_x * 3, size_x * 3);
		memcpy(pBmpBuffer + (size_x * 3), pBmpBuffer - size_x * 3, size_x * 3);
		break;
	case 3:	//GBRG				//GBGB
								//RGRG
								//GBGB
								//RGRG
		for (i = 0; i < size_y - 2; i += 2) {
			pImageTemp = pImageData;
			pImageTemp1 = pImageData - size_x;
			for (j = 0; j < size_x - 2; j += 2) {
				r = pImageTemp[0];
				b = pImageTemp1[1];
				g = (pImageTemp[1] + pImageTemp1[0]) >> 1;
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;

				r = pImageTemp[1];
				b = pImageTemp1[0];
				g = (pImageTemp[0] + pImageTemp1[1]) >> 1;
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;
			}
			memcpy(pBmpBuffer, pBmpBuffer - 3, 3);
			memcpy(pBmpBuffer + 3, pBmpBuffer, 3);
			pBmpBuffer += 6;
			pImageData -= size_x;
			pImageTemp = pImageData;
			pImageTemp1 = pImageData - size_x;

			for (j = 0; j < size_x - 2; j += 2) {
				b = pImageTemp[1];
				g = (pImageTemp[0] + pImageTemp1[1]) >> 1;
				r = pImageTemp1[0];
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;

				r = pImageTemp1[1];
				g = (pImageTemp[1] + pImageTemp1[0]) >> 1;
				b = pImageTemp[0];
				*pBmpBuffer++ = b;
				*pBmpBuffer++ = g;
				*pBmpBuffer++ = r;
				pImageTemp += 1;
				pImageTemp1 += 1;
			}
			memcpy(pBmpBuffer, pBmpBuffer - 3, 3);
			memcpy(pBmpBuffer + 3, pBmpBuffer, 3);
			pBmpBuffer += 6;
			pImageData -= size_x;
		}
		memcpy(pBmpBuffer, pBmpBuffer - size_x * 3, size_x * 3);
		memcpy(pBmpBuffer + (size_x * 3), pBmpBuffer - size_x * 3, size_x * 3);
		break;
	}
}

bool DeviceModuleGuadalupeCanyon::SaveToRaw16BitImg(const char* strFilename, unsigned char* pBuffer, int nWidth, int nHeight)
{
	int gnHeaderCnt = 4;
	FILE* pf = fopen(strFilename, "wb");
	if (pf == NULL)
		return FALSE;

	unsigned short * pDest = new unsigned short[nWidth * nHeight]();
	unsigned int nByteWidth = ALIGNED_SIZE(((nWidth * 5) >> 2) + gnHeaderCnt, 3);
	unsigned int nDst, nSrc;
	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j += 4)
		{
			//LSB bit swap, so fix this bug - 2013. 10/01 OHSK
			nDst = i * nWidth + j;
			nSrc = i * nByteWidth + ((j * 5) >> 2);
			pDest[nDst + 0] = (pBuffer[nSrc + 0]) + (((WORD)(pBuffer[nSrc + 4] & 0x03)) << 14);
			pDest[nDst + 1] = (pBuffer[nSrc + 1]) + (((WORD)(pBuffer[nSrc + 4] & 0x0C)) << 12);
			pDest[nDst + 2] = (pBuffer[nSrc + 2]) + (((WORD)(pBuffer[nSrc + 4] & 0x30)) << 10);
			pDest[nDst + 3] = (pBuffer[nSrc + 3]) + (((WORD)(pBuffer[nSrc + 4] & 0xC0)) << 8);
		}
	}

	fwrite(pDest, sizeof(unsigned short), nWidth * nHeight, pf);
	fclose(pf);

	if (!(NULL == pDest))
	{
		delete pDest;
		pDest = NULL;
	}
	return TRUE;
}


bool fWrite_uint16_b(const char* strFilename, uint16_t H, uint16_t V, unsigned short* data)
{
	int gnHeaderCnt = 4;
	FILE* pf = fopen(strFilename, "wb");
	if (pf == NULL)
		return FALSE;

	unsigned char *ByteBuf = new unsigned char[H * V];
	//将图片存成16bit,为了能以后再拿出来分析。
	int i, j = 0;
	for (j = 0; j < H; j++)
	{
		for (i = 0; i < V; i++)
		{
			ByteBuf[j * V * 2 + i * 2 + 0] = data[j * V + i] >> 2;
			ByteBuf[j * V * 2 + i * 2 + 1] = data[j * V + i] << 6;
		}
	}
	fwrite(ByteBuf, sizeof(unsigned short), V * H, pf);
	delete[] ByteBuf;
	fclose(pf);

	if (!(NULL == ByteBuf))
	{
		delete ByteBuf;
		ByteBuf = NULL;
	}

	return true;
}





bool SaveImageToBmpFile(const char* desFileName, BYTE *pBmpBuffer, int sizeX, int sizeY)
{
	//OPENFILENAME	 SFN;
	char			 lpstrFile[MAX_PATH];
	char			 SaveFileMessage[MAX_PATH] = { 0 };

	int				 OffBits;
	HFILE			 bmpFile;
	BITMAPFILEHEADER bmpHeader; // Header for Bitmap file
	BITMAPINFO		 bmpInfo;

	OffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	DWORD dwSizeImage = sizeX * sizeY * 3;

	bmpHeader.bfType = ((WORD)('M' << 8) | 'B');
	bmpHeader.bfSize = OffBits + dwSizeImage;
	bmpHeader.bfReserved1 = 0;
	bmpHeader.bfReserved2 = 0;
	bmpHeader.bfOffBits = OffBits;

	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = sizeX;
	bmpInfo.bmiHeader.biHeight = sizeY;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biSizeImage = 0;
	bmpInfo.bmiHeader.biXPelsPerMeter = 0;
	bmpInfo.bmiHeader.biYPelsPerMeter = 0;
	bmpInfo.bmiHeader.biClrUsed = 0;
	bmpInfo.bmiHeader.biClrImportant = 0;

	bmpFile = _lcreat(desFileName, 0);
	if (bmpFile < 0) {
		return FALSE;
	}

	UINT len;
	len = _lwrite(bmpFile, (LPSTR)&bmpHeader, sizeof(BITMAPFILEHEADER));
	len = _lwrite(bmpFile, (LPSTR)&bmpInfo, sizeof(BITMAPINFOHEADER));
	len = _lwrite(bmpFile, (LPSTR)pBmpBuffer, bmpHeader.bfSize - sizeof(bmpHeader) - sizeof(bmpInfo) + 4);  //+4 is for exact filesize

	_lclose(bmpFile);

	return TRUE;
}


bool DeviceModuleGuadalupeCanyon::fnGetFFBLDummyFrame(int nBoardindex)
{
	int gnHeaderCnt = 0;
	int m_iDisplayX = 1104;
	int m_iDisplayY = 1314;
	int m_iDataFormat = 2;
	int m_iMipiMode = 1;		//Mipi mode 0:1L, 1:2L, 3:3L, 7:4L
	int m_iOutMode = 2;

	BOOL status = TRUE;
	DWORD			exitcode;
	int				nCnt = 0;
	DWORD			dwCount, nXsize;
	int				pixelalign = 0;

	if (m_iDataFormat/*GetDataFormat()*/ == 0) {		//YUV
		pixelalign = 16;
	}
	else if (m_iDataFormat == 1) { //8bit bayer
		pixelalign = 8;
	}
	else if (m_iDataFormat == 2) { //10bit bayer
		if (m_iMipiMode/*GetMipiMode()*/ == 9) { //parallel
			pixelalign = 16;
		}
		else {
			pixelalign = 10;//this 0x0a
		}
	}
	else if (m_iDataFormat == 3) { //12bit MIPI bayer
		pixelalign = 12;
	}
	int ret = 0;

	//GPIOWrite_High(1, nBoardindex % 4);
	//Sleep(10);
	//GPIOWrite_Low(1, nBoardindex % 4);

	BYTE *gpRaw8Buffer;
	gpRaw8Buffer = new BYTE[DATA_MAX_X *DATA_MAX_Y];
	memset(gpRaw8Buffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y);

	BYTE *gpDataBuffer;
	gpDataBuffer = new BYTE[DATA_MAX_X *DATA_MAX_Y * 2];
	memset(gpDataBuffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y * 2);

	BYTE *gpBmpBuffer;
	gpBmpBuffer = new BYTE[DATA_MAX_X *DATA_MAX_Y * 3];
	memset(gpBmpBuffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y * 3);



	//if (nBoardindex == 0 || nBoardindex == 4)
	//{
	//	if (PCI_LVDS_BufferFlush(nBoardindex % 4, CH0) == FALSE)
	//	{
	//		g_pOP->LogError(nBoardindex, __FUNCTION__, "BufferFlush error!!!");
	//		status = FALSE;
	//		return FALSE;
	//	}
	//}

	//ret = PCI_LVDS_Start(nBoardindex % 4, CH0);
	int nRetryCnt = 0;
	int nLoopCnt = 100;
	bool ret1 = false;
	
	while (nRetryCnt < nLoopCnt)
	{
		Sleep(30);
		nXsize = ((m_iDisplayX*pixelalign) >> 3);//0x0564
		dwCount = ALIGNED_SIZE(nXsize + gnHeaderCnt, 3) * m_iDisplayY;  //size define based on image size 0x01bbfd0
		ret1 = PCI_LVDS_GetFrame(nBoardindex % 4, CH0, &dwCount, gpDataBuffer);
		if (ret1) {
			bool gbChecksum_OnlyHWmode = 0;
			if (gnHeaderCnt) { Calc_CheckSum(gpDataBuffer, nXsize, m_iDisplayY, gbChecksum_OnlyHWmode); }
			//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Capture Dummy frame data");
			//if (PCI_LVDS_BufferFlush(nBoardindex % 4, CH0) == FALSE)
			//{
			//	//mData->mLogEvent->fnWriteLogAndShowui((LOG_STATION)nBoardindex % 4, ERRORS, __FUNCTION__, "BufferFlush  after capture error !");
			//	g_pOP->LogError(nBoardindex, __FUNCTION__, "BufferFlush  after capture error !");
			//	status = FALSE;
			//	return FALSE;
			//}
			break;
		}
		else {
			//mData->mLogEvent->fnWriteLogAndShowui((LOG_STATION)nBoardindex % 4, ERRORS, __FUNCTION__, "No Data:%d" + to_string(dwCount));
			//g_pOP->LogError(nBoardindex, __FUNCTION__, "No frame data");
			nRetryCnt++;
		}

		//if (nRetryCnt == 5)
		//{
		//	//ret1 = g_pDEV->m_BanffControl.WriteByte(nBoardindex % 4, true, 0x0102, 0x01);
		//	//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Write 0x01 to 0x0102 results:[%d]", ret1);
		//	//Sleep(10);
		//	ret1 = g_pDEV->m_BanffControl.WriteByte(nBoardindex % 4, true, 0x0102, 0x02);
		//	//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Write 0x01 to 0x0102 results:[%d]", ret1);
		//	Sleep(10);
		//	nRetryCnt++;
		//}

	}
	//if (ret1 == false)
	//{
	//	//g_pOP->LogError(nBoardindex, __FUNCTION__, "No frame data after retry:[%d]", nRetryCnt);

	//	std::string value146;
	//	std::string value147;

	//	value146 = g_pDEV->m_BanffControl.I2cReadByte(nBoardindex % 4, true, 0x0146, 2);

	//	value147 = g_pDEV->m_BanffControl.I2cReadByte(nBoardindex % 4, true, 0x0147, 2);

	//}
	

	delete[]gpBmpBuffer;
	delete[]gpDataBuffer;
	delete[]gpRaw8Buffer;

	return ret1;
}


bool DeviceModuleGuadalupeCanyon::fnGetFFBLOneFrame(int nBoardindex, bool isSave, std::string station, std::string barcode, std::string FilePath, std::string fileName, BYTE* RawBuffer, bool is16Bit)
{
	//int gnHeaderCnt = 0;
	//int m_iDisplayX = 1104;
	//int m_iDisplayY = 1314;
	//int m_iDataFormat = 2;
	//int m_iMipiMode = 1;		//Mipi mode 0:1L, 1:2L, 3:3L, 7:4L
	//int m_iOutMode = 2;

	//BOOL status = TRUE;
	//DWORD			exitcode;
	//int				nCnt = 0;
	//DWORD			dwCount, nXsize;
	//int				pixelalign = 0;
	//std::string fileNameWithPath;
	//fileNameWithPath = FilePath + "\\" + fileName;

	//if (m_iDataFormat/*GetDataFormat()*/ == 0) {		//YUV
	//	pixelalign = 16;
	//}
	//else if (m_iDataFormat == 1) { //8bit bayer
	//	pixelalign = 8;
	//}
	//else if (m_iDataFormat == 2) { //10bit bayer
	//	if (m_iMipiMode/*GetMipiMode()*/ == 9) { //parallel
	//		pixelalign = 16;
	//	}
	//	else {
	//		pixelalign = 10;//this 0x0a
	//	}
	//}
	//else if (m_iDataFormat == 3) { //12bit MIPI bayer
	//	pixelalign = 12;
	//}
	//bool ret = 0;

	////GPIOWrite_High(1, nBoardindex % 4);
	////Sleep(10);
	////GPIOWrite_Low(1, nBoardindex % 4);

	//BYTE *gpRaw8Buffer;
	//gpRaw8Buffer = new BYTE[DATA_MAX_X *DATA_MAX_Y];
	//memset(gpRaw8Buffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y);

	//BYTE *gpDataBuffer;
	//gpDataBuffer = new BYTE[DATA_MAX_X *DATA_MAX_Y * 2];
	//memset(gpDataBuffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y * 2);

	//BYTE *gpBmpBuffer;
	//gpBmpBuffer = new BYTE[DATA_MAX_X *DATA_MAX_Y * 3];
	//memset(gpBmpBuffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y * 3);

	//unsigned short *gpRaw10bitBuffer;
	//gpRaw10bitBuffer = new unsigned short[DATA_MAX_X *DATA_MAX_Y];
	//memset(gpRaw10bitBuffer, 0, sizeof(unsigned short)*DATA_MAX_X *DATA_MAX_Y);

	//memset(RawBuffer, 0, sizeof(short)*DATA_MAX_X *DATA_MAX_Y);

	//
	////if (nBoardindex == 0 || nBoardindex == 4)
	////{
	////	if (PCI_LVDS_BufferFlush(nBoardindex % 4, CH0) == FALSE)
	////	{
	////		g_pOP->LogError(nBoardindex, __FUNCTION__, "BufferFlush error!!!");
	////		status = FALSE;
	////		return FALSE;
	////	}
	////}
	////ret = PCI_LVDS_Start(nBoardindex % 4, CH0);
	////Sleep(30);//Dut out put frame need 20ms minimun delay.

	//int nRetryCnt = 0;
	//int nLoopCnt = 100;
	//bool ret1 = false;
	//
	//while (nRetryCnt < nLoopCnt)
	//{
	//	Sleep(30);
	//	nXsize = ((m_iDisplayX*pixelalign) >> 3);//0x0564
	//	dwCount = ALIGNED_SIZE(nXsize + gnHeaderCnt, 3) * m_iDisplayY;  //size define based on image size 0x01bbfd0
	//	ret1 = PCI_LVDS_GetFrame(nBoardindex % 4, CH0, &dwCount, gpDataBuffer);
	//	if (ret1) {
	//		bool gbChecksum_OnlyHWmode = 0;
	//		if (gnHeaderCnt) { Calc_CheckSum(gpDataBuffer, nXsize, m_iDisplayY, gbChecksum_OnlyHWmode); }

	//		memcpy(RawBuffer, gpDataBuffer, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y * 2);

	//		Shift10BitMode(gpDataBuffer, gpRaw8Buffer, m_iDisplayX, m_iDisplayY);
	//		RawToBmp(m_iOutMode/*GetOutOrder()*/, gpRaw8Buffer, gpBmpBuffer, m_iDisplayX, m_iDisplayY);

	//		if (/*fileName.size() > 0 && g_pINSP->m_iSaveBMPImage == true*/ isSave)
	//		{
	//			if (fileName.size() > 0 && g_pINSP->m_iSaveBMPImage == true /*isSave*/)
	//			{
	//				std::string bmpFile = fileNameWithPath + ".bmp";
	//				SaveImageToBmpFile(bmpFile.c_str(), gpBmpBuffer, m_iDisplayX, m_iDisplayY);
	//			}

	//			if (is16Bit)//FFBL algorithnm
	//			{
	//				Make10BitMode(gpDataBuffer, gpRaw10bitBuffer, 1104, 1314);

	//				//cv::Mat mat;
	//				//CvMat mCVmat = cvMat(1104, 1314, CV_8UC1, gpDataBuffer);

	//				////save 16bit bit picture
	//				//FILE	*fp;
	//				//char strTmp[1024];
	//				//sprintf(strTmp, "%s", fileNameWithPath.c_str());
	//				//if (!(fp = fopen(strTmp, "wb")))
	//				//{
	//				//	g_pOP->LogError(nBoardindex, __FUNCTION__, "Image save fail");
	//				//}
	//				//fwrite(gpRaw10bitBuffer, sizeof(unsigned short), 1104 * 1314, fp);
	//				//fclose(fp);

	//				//SaveToRawImg(Format("%s\\%s_%s", FilePath.c_str(), "MiPi_Raw", fileName.c_str()).c_str(), gpDataBuffer, 1104, 1314 * 1.25); //Save MiniRaw
	//			}
	//			else
	//			{//AE process
	//				//string RawFile = Format("%s", fileNameWithPath.c_str());
	//				//SaveToRawImg(RawFile.c_str(), gpDataBuffer, m_iDisplayX, m_iDisplayY * 1.25);
	//			}
	//		}

	//		//Show8BitImg(pWnd, gpRaw8Buffer, m_iDisplayX, m_iDisplayY);
	//		//SaveToRaw16BitImg(/*fnMakeImgFileName(FALSE).c_str()*/fileNameWithPath.c_str(), gpDataBuffer, m_iDisplayX, m_iDisplayY);
	//		//qDebug() << "SaveRawImage:" << fileNameWithPath.c_str();

	//		QImage img(gpBmpBuffer, m_iDisplayX, m_iDisplayY, m_iDisplayX * 3, QImage::Format_RGB888);
	//		img = img.convertToFormat(QImage::Format_Grayscale8, Qt::AutoColor);
	//		jupMsgSender->emit_showTestStationImage(nBoardindex, station, barcode, img, QString::fromStdString(fileName));

	//		//if (PCI_LVDS_BufferFlush(nBoardindex % 4, CH0) == FALSE)
	//		//{
	//		//	//mData->mLogEvent->fnWriteLogAndShowui((LOG_STATION)nBoardindex % 4, ERRORS, __FUNCTION__, "BufferFlush  after capture error !");
	//		//	g_pOP->LogError(nBoardindex, __FUNCTION__, "BufferFlush  after capture error !");
	//		//	status = FALSE;
	//		//	return FALSE;
	//		//}
	//		break;
	//	}
	//	else {
	//		//mData->mLogEvent->fnWriteLogAndShowui((LOG_STATION)nBoardindex % 4, ERRORS, __FUNCTION__, "No Data:%d" + to_string(dwCount));
	//		//g_pOP->LogError(nBoardindex, __FUNCTION__, "No data capture one frame");
	//		/*Sleep(50);*/
	//		nRetryCnt++;
	//	}

	//	if (nRetryCnt == 5)
	//	{
	//		//ret1 = g_pDEV->m_BanffControl.WriteByte(nBoardindex % 4, true, 0x0102, 0x01);
	//		//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Write 0x01 to 0x0102 results:[%d]", ret1);
	//		//Sleep(10);
	//		ret1 = g_pDEV->m_BanffControl.WriteByte(nBoardindex % 4, true, 0x0102, 0x02);
	//		//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Write 0x01 to 0x0102 results:[%d]", ret1);
	//		Sleep(10);
	//		nRetryCnt++;
	//	}
	//}

	//if (ret1 == false)
	//{
	//	//g_pOP->LogError(nBoardindex, __FUNCTION__, "No frame data after retry:[%d]", nRetryCnt);
	//}

	//delete[]gpBmpBuffer;
	//delete[]gpDataBuffer;
	//delete[]gpRaw8Buffer;
	//delete[]gpRaw10bitBuffer;

	//return status;
	return true;
}


bool DeviceModuleGuadalupeCanyon::fnGetFFBLExposureImg(int nBoardindex, bool isSave, std::string station, std::string barcode, std::string FilePath, std::string fileName, unsigned short* RawBufferDest, bool is16Bit)
{
	//int gnHeaderCnt = 0;
	//int m_iDisplayX = 1104;
	//int m_iDisplayY = 1314;
	//int m_iDataFormat = 2;
	//int m_iMipiMode = 1;		//Mipi mode 0:1L, 1:2L, 3:3L, 7:4L
	//int m_iOutMode = 2;

	//BOOL status = TRUE;
	//DWORD			exitcode;
	//int				nCnt = 0;
	//DWORD			dwCount, nXsize;
	//int				pixelalign = 0;
	//std::string fileNameWithPath;
	//fileNameWithPath = Format("%s\\%s", FilePath.c_str(), fileName.c_str());

	//if (m_iDataFormat/*GetDataFormat()*/ == 0) {		//YUV
	//	pixelalign = 16;
	//}
	//else if (m_iDataFormat == 1) { //8bit bayer
	//	pixelalign = 8;
	//}
	//else if (m_iDataFormat == 2) { //10bit bayer
	//	if (m_iMipiMode/*GetMipiMode()*/ == 9) { //parallel
	//		pixelalign = 16;
	//	}
	//	else {
	//		pixelalign = 10;//this 0x0a
	//	}
	//}
	//else if (m_iDataFormat == 3) { //12bit MIPI bayer
	//	pixelalign = 12;
	//}
	//bool ret = 0;

	//BYTE *gpRaw8Buffer;
	//gpRaw8Buffer = new BYTE[DATA_MAX_X *DATA_MAX_Y];
	//memset(gpRaw8Buffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y);

	//BYTE *gpDataBuffer;
	//gpDataBuffer = new BYTE[DATA_MAX_X *DATA_MAX_Y * 2];
	//memset(gpDataBuffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y * 2);

	//BYTE *gpBmpBuffer;
	//gpBmpBuffer = new BYTE[DATA_MAX_X *DATA_MAX_Y * 3];
	//memset(gpBmpBuffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y * 3);

	//unsigned short *gpRaw10bitBuffer;
	//gpRaw10bitBuffer = new unsigned short[DATA_MAX_X *DATA_MAX_Y];
	//memset(gpRaw10bitBuffer, 0, sizeof(unsigned short)*DATA_MAX_X *DATA_MAX_Y);

	//memset(RawBufferDest, 0, sizeof(short)*DATA_MAX_X *DATA_MAX_Y);

	//int nRetryCnt = 0;
	//int nLoopCnt = 100;
	//bool ret1 = false;

	//while (nRetryCnt < nLoopCnt)
	//{
	//	Sleep(30);
	//	nXsize = ((m_iDisplayX*pixelalign) >> 3);//0x0564
	//	dwCount = ALIGNED_SIZE(nXsize + gnHeaderCnt, 3) * m_iDisplayY;  //size define based on image size 0x01bbfd0
	//	ret1 = PCI_LVDS_GetFrame(nBoardindex % 4, CH0, &dwCount, gpDataBuffer);
	//	if (ret1) {
	//		bool gbChecksum_OnlyHWmode = 0;
	//		if (gnHeaderCnt) { Calc_CheckSum(gpDataBuffer, nXsize, m_iDisplayY, gbChecksum_OnlyHWmode); }

	//		Shift10BitMode(gpDataBuffer, gpRaw8Buffer, m_iDisplayX, m_iDisplayY);
	//		RawToBmp(m_iOutMode/*GetOutOrder()*/, gpRaw8Buffer, gpBmpBuffer, m_iDisplayX, m_iDisplayY);

	//		if (/*fileName.size() > 0 && g_pINSP->m_iSaveBMPImage == true*/ isSave)
	//		{
	//			if (fileName.size() > 0 && g_pINSP->m_iSaveBMPImage == true /*isSave*/)
	//			{
	//				std::string bmpFile = Format("%s.bmp", fileNameWithPath.c_str());
	//				SaveImageToBmpFile(bmpFile.c_str(), gpBmpBuffer, m_iDisplayX, m_iDisplayY);
	//			}

	//			if (is16Bit)//FFBL AE Process
	//			{
	//				Make10BitMode(gpDataBuffer, RawBufferDest, 1104, 1314);

	//				//cv::Mat mat;
	//				//CvMat mCVmat = cvMat(1104, 1314, CV_8UC1, gpDataBuffer);

	//				////save 16bit bit picture
	//				//FILE	*fp;
	//				//char strTmp[1024];
	//				//sprintf(strTmp, "%s", fileNameWithPath.c_str());
	//				//if (!(fp = fopen(strTmp, "wb")))
	//				//{
	//				//	g_pOP->LogError(nBoardindex, __FUNCTION__, "Image save fail");
	//				//}
	//				//fwrite(RawBufferDest, sizeof(unsigned short), 1104 * 1314, fp);
	//				//fclose(fp);

	//				//SaveToRawImg(Format("%s\\%s_%s", FilePath.c_str(), "MiPi_Raw-", fileName.c_str()).c_str(), gpDataBuffer, 1104, 1314 * 1.25); //Save MiPi Raw
	//			}
	//			else
	//			{//AE process
	//				//string RawFile = Format("%s", fileNameWithPath.c_str());
	//				//SaveToRawImg(RawFile.c_str(), gpDataBuffer, m_iDisplayX, m_iDisplayY * 1.25);
	//			}
	//		}
	//		//qDebug() << "SaveRawImage:" << fileNameWithPath.c_str();

	//		QImage img(gpBmpBuffer, m_iDisplayX, m_iDisplayY, m_iDisplayX * 3, QImage::Format_RGB888);
	//		img = img.convertToFormat(QImage::Format_Grayscale8, Qt::AutoColor);
	//		jupMsgSender->emit_showTestStationImage(nBoardindex, station, barcode, img, QString::fromStdString(fileName));
	//		break;
	//	}
	//	else {
	//		g_pOP->LogError(nBoardindex, __FUNCTION__, "No data capture one frame");
	//		/*Sleep(50);*/
	//		nRetryCnt++;
	//	}

	//	if (nRetryCnt == 5)
	//	{
	//		ret1 = g_pDEV->m_BanffControl.WriteByte(nBoardindex % 4, true, 0x0102, 0x02);
	//		//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Write 0x01 to 0x0102 results:[%d]", ret1);
	//		Sleep(10);
	//		nRetryCnt++;
	//	}
	//}

	//if (ret1 == false)
	//{
	//	//g_pOP->LogError(nBoardindex, __FUNCTION__, "No frame data after retry:[%d]", nRetryCnt);
	//}

	//delete[]gpBmpBuffer;
	//delete[]gpDataBuffer;
	//delete[]gpRaw8Buffer;
	//delete[]gpRaw10bitBuffer;

	//return status;
	return true;	
}

double DeviceModuleGuadalupeCanyon::fnGetImgMean(PUSHORT pRawBuffer, int nWidth, int nHeight, int nROIWidth)
{
	int    i = 0, j = 0;
	int    nNum = 0;
	RECT   _AEROI = { 0 };
	double dMean = 0;

	_AEROI.left = nWidth / 2 - nROIWidth / 2 - 1;
	_AEROI.right = _AEROI.left + nROIWidth + 1;
	_AEROI.top = nHeight / 2 - nROIWidth / 2 - 1 + 2;   //+2 for embedded line
	_AEROI.bottom = _AEROI.top + nROIWidth + 1;

	double *pGrBuffer = new double[(_AEROI.bottom - _AEROI.top) * (_AEROI.right - _AEROI.left)];

	for (j = _AEROI.top; j < _AEROI.bottom; j++)
	{
		for (i = _AEROI.left; i < _AEROI.right; i++)
		{
			pGrBuffer[nNum] = pRawBuffer[j * nWidth + i];
			nNum++;
		}
	}

	for (i = 0; i < nNum; i++) dMean = dMean + pGrBuffer[i];

	dMean /= nNum;

	delete[] pGrBuffer;

	return dMean;
}

bool DeviceModuleGuadalupeCanyon::fnGetFFBLOneFrame(int nBoardindex, bool isSave, std::string station, std::string barcode, std::string FilePath, std::string fileName, unsigned short * RawBuffer, bool is16Bit)
{
	return fnGetFFBLOneFrame(nBoardindex, isSave, station, barcode, FilePath, fileName, (BYTE*)RawBuffer, is16Bit);
}

void DeviceModuleGuadalupeCanyon::fnFireSync(int nBoardindex)
{
	GPIOWrite_High(1, nBoardindex % 4);
	Sleep(10);
	GPIOWrite_Low(1, nBoardindex % 4);
}

bool DeviceModuleGuadalupeCanyon::fnGetOneFrame(int nBoardindex, std::string station, std::string barcode, std::string FilePath, std::string fileName, bool iShowImg)
{
	//int gnHeaderCnt = 4;
	//int m_iDisplayX = 1104;
	//int m_iDisplayY = 1314;
	////int m_iDataFormat = 2;
	////int m_iMipiMode = 1;		//Mipi mode 0:1L, 1:2L, 3:3L, 7:4L
	//int m_iOutMode = 2;

	//BOOL status = TRUE;
	//DWORD			exitcode;
	//int				nCnt = 0;
	//DWORD			dwCount, nXsize;
	//int				pixelalign = 0;
	//std::string fileNameWithPath;
	//fileNameWithPath = Format("%s\\%s", FilePath.c_str(), fileName.c_str());

	////if (m_iDataFormat/*GetDataFormat()*/ == 0) {		//YUV
	////	pixelalign = 16;
	////}
	////else if (m_iDataFormat == 1) { //8bit bayer
	////	pixelalign = 8;
	////}
	////else if (m_iDataFormat == 2) { //10bit bayer
	////	if (m_iMipiMode/*GetMipiMode()*/ == 9) { //parallel
	////		pixelalign = 16;
	////	}
	////	else {
	////		pixelalign = 10;//this 0x0a
	////	}
	////}
	////else if (m_iDataFormat == 3) { //12bit MIPI bayer
	////	pixelalign = 12;
	////}
	//pixelalign = 10;//this 0x0a
	//int ret = 0;

	//BYTE *gpRaw8Buffer;
	//gpRaw8Buffer = new BYTE[DATA_MAX_X *DATA_MAX_Y];
	//memset(gpRaw8Buffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y);

	//BYTE *gpDataBuffer;
	//gpDataBuffer = new BYTE[DATA_MAX_X *DATA_MAX_Y * 2];
	//memset(gpDataBuffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y * 2);

	//BYTE *gpBmpBuffer;
	//gpBmpBuffer = new BYTE[DATA_MAX_X *DATA_MAX_Y * 3];
	//memset(gpBmpBuffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y * 3);
	//
	//nXsize = ((m_iDisplayX*pixelalign) >> 3);//0x0564
	//dwCount = ALIGNED_SIZE(nXsize + gnHeaderCnt, 3) * m_iDisplayY;  //size define based on image size 0x01bbfd0


	//GPIOWrite_High(1, nBoardindex % 4);
	//Sleep(10);
	//GPIOWrite_Low(1, nBoardindex % 4);
	//

	////if (PCI_LVDS_BufferFlush(nBoardindex % 4, CH0) == FALSE)
	////{
	////	//m_CHVSBase.ListOut("BufferFlush error !");
	////	status = FALSE;
	////	return FALSE;
	////}
	//ret = PCI_LVDS_Start(nBoardindex % 4, CH0);

	//bool ret1 = PCI_LVDS_GetFrame(nBoardindex % 4, CH0, &dwCount, gpDataBuffer);
	//if (ret1) {
	//	bool gbChecksum_OnlyHWmode = 0;
	//	if (gnHeaderCnt) { Calc_CheckSum(gpDataBuffer, nXsize, m_iDisplayY, gbChecksum_OnlyHWmode); }

	//	//Shift10BitMode(gpDataBuffer, gpRaw8Buffer, m_iDisplayX, m_iDisplayY);
	//	//RawToBmp(m_iOutMode/*GetOutOrder()*/, gpRaw8Buffer, gpBmpBuffer, m_iDisplayX, m_iDisplayY);

	//	if (fileName.size() > 0 && g_pINSP->m_iSaveBMPImage == true)
	//	{
	//		Shift10BitMode(gpDataBuffer, gpRaw8Buffer, m_iDisplayX, m_iDisplayY);
	//		RawToBmp(m_iOutMode/*GetOutOrder()*/, gpRaw8Buffer, gpBmpBuffer, m_iDisplayX, m_iDisplayY);

	//		std::string bmpFile = Format("%s.bmp", fileNameWithPath.c_str());
	//		SaveImageToBmpFile(bmpFile.c_str(), gpBmpBuffer, m_iDisplayX, m_iDisplayY);
	//	}

	//	SaveToRaw16BitImg(/*fnMakeImgFileName(FALSE).c_str()*/fileNameWithPath.c_str(), gpDataBuffer, m_iDisplayX, m_iDisplayY);

	//	if (fileName.size() > 0 && iShowImg==true)
	//	{
	//		if (g_pINSP->m_iSaveBMPImage == false) //这种情况下，以下的代码在上面并未执行
	//		{
	//			Shift10BitMode(gpDataBuffer, gpRaw8Buffer, m_iDisplayX, m_iDisplayY);
	//			RawToBmp(m_iOutMode/*GetOutOrder()*/, gpRaw8Buffer, gpBmpBuffer, m_iDisplayX, m_iDisplayY);
	//		}

	//		QImage img(gpBmpBuffer, m_iDisplayX, m_iDisplayY, m_iDisplayX * 3, QImage::Format_RGB888);
	//		img = img.convertToFormat(QImage::Format_Grayscale8, Qt::AutoColor);
	//		jupMsgSender->emit_showTestStationImage(nBoardindex, station, barcode, img, QString::fromStdString(fileName));

	//	}

	//	//if (PCI_LVDS_BufferFlush(nBoardindex % 4, CH0) == FALSE)
	//	//{
	//	//	//mData->mLogEvent->fnWriteLogAndShowui((LOG_STATION)nBoardindex % 4, ERRORS, __FUNCTION__, "BufferFlush  after capture error !");
	//	//	g_pOP->LogError(nBoardindex,__FUNCTION__, "BufferFlush  after capture error !");
	//	//	status = FALSE;
	//	//	return FALSE;
	//	//}
	//}
	//else {
	//	//mData->mLogEvent->fnWriteLogAndShowui((LOG_STATION)nBoardindex % 4, ERRORS, __FUNCTION__, "No Data:%d" + to_string(dwCount));
	//	//g_pOP->LogError(nBoardindex,__FUNCTION__, "No data capture one frame");
	//	status = FALSE;
	//	Sleep(1);
	//}

	//delete []gpBmpBuffer;
	//delete []gpDataBuffer;
	//delete []gpRaw8Buffer;

	//return status;
	return true;
}

bool DeviceModuleGuadalupeCanyon::fnGetOneFrameWithoutTrigger(int nBoardindex, std::string station, std::string barcode, std::string FilePath, std::string fileName, bool iShowImg)
{
	//int gnHeaderCnt = 4;
	//int m_iDisplayX = 1104;
	//int m_iDisplayY = 1314;
	//int m_iOutMode = 2;

	//BOOL status = TRUE;
	//DWORD			exitcode;
	//int				nCnt = 0;
	//DWORD			dwCount, nXsize;
	//int				pixelalign = 0;
	//std::string fileNameWithPath;
	//fileNameWithPath = Format("%s\\%s", FilePath.c_str(), fileName.c_str());

	//pixelalign = 10;//this 0x0a
	//int ret = 0;

	//BYTE *gpRaw8Buffer;
	//gpRaw8Buffer = new BYTE[DATA_MAX_X *DATA_MAX_Y];
	//memset(gpRaw8Buffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y);

	//BYTE *gpDataBuffer;
	//gpDataBuffer = new BYTE[DATA_MAX_X *DATA_MAX_Y * 2];
	//memset(gpDataBuffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y * 2);

	//BYTE *gpBmpBuffer;
	//gpBmpBuffer = new BYTE[DATA_MAX_X *DATA_MAX_Y * 3];
	//memset(gpBmpBuffer, 0, sizeof(BYTE)*DATA_MAX_X *DATA_MAX_Y * 3);

	//nXsize = ((m_iDisplayX*pixelalign) >> 3);//0x0564
	//dwCount = ALIGNED_SIZE(nXsize + gnHeaderCnt, 3) * m_iDisplayY;  //size define based on image size 0x01bbfd0

	////if (PCI_LVDS_BufferFlush(nBoardindex % 4, CH0) == FALSE)
	////{
	////	//m_CHVSBase.ListOut("BufferFlush error !");
	////	status = FALSE;
	////	return FALSE;
	////}
	//ret = PCI_LVDS_Start(nBoardindex % 4, CH0);

	//bool ret1 = PCI_LVDS_GetFrame(nBoardindex % 4, CH0, &dwCount, gpDataBuffer);
	//if (ret1) {
	//	bool gbChecksum_OnlyHWmode = 0;
	//	if (gnHeaderCnt) { Calc_CheckSum(gpDataBuffer, nXsize, m_iDisplayY, gbChecksum_OnlyHWmode); }

	//	//Shift10BitMode(gpDataBuffer, gpRaw8Buffer, m_iDisplayX, m_iDisplayY);
	//	//RawToBmp(m_iOutMode/*GetOutOrder()*/, gpRaw8Buffer, gpBmpBuffer, m_iDisplayX, m_iDisplayY);

	//	if (fileName.size() > 0 && g_pINSP->m_iSaveBMPImage == true)
	//	{
	//		Shift10BitMode(gpDataBuffer, gpRaw8Buffer, m_iDisplayX, m_iDisplayY);
	//		RawToBmp(m_iOutMode/*GetOutOrder()*/, gpRaw8Buffer, gpBmpBuffer, m_iDisplayX, m_iDisplayY);

	//		std::string bmpFile = Format("%s.bmp", fileNameWithPath.c_str());
	//		SaveImageToBmpFile(bmpFile.c_str(), gpBmpBuffer, m_iDisplayX, m_iDisplayY);
	//	}

	//	SaveToRaw16BitImg(/*fnMakeImgFileName(FALSE).c_str()*/fileNameWithPath.c_str(), gpDataBuffer, m_iDisplayX, m_iDisplayY);


	//	if (fileName.size() > 0 && iShowImg == true)
	//	{
	//		if (g_pINSP->m_iSaveBMPImage == false) //这种情况下，以下的代码在上面并未执行
	//		{
	//			Shift10BitMode(gpDataBuffer, gpRaw8Buffer, m_iDisplayX, m_iDisplayY);
	//			RawToBmp(m_iOutMode/*GetOutOrder()*/, gpRaw8Buffer, gpBmpBuffer, m_iDisplayX, m_iDisplayY);
	//		}

	//		QImage img(gpBmpBuffer, m_iDisplayX, m_iDisplayY, m_iDisplayX * 3, QImage::Format_RGB888);
	//		img = img.convertToFormat(QImage::Format_Grayscale8, Qt::AutoColor);
	//		jupMsgSender->emit_showTestStationImage(nBoardindex, station, barcode, img, QString::fromStdString(fileName));

	//	}

	//	//if (PCI_LVDS_BufferFlush(nBoardindex % 4, CH0) == FALSE)
	//	//{
	//	//	//mData->mLogEvent->fnWriteLogAndShowui((LOG_STATION)nBoardindex % 4, ERRORS, __FUNCTION__, "BufferFlush  after capture error !");
	//	//	g_pOP->LogError(nBoardindex,__FUNCTION__, "BufferFlush  after capture error !");
	//	//	status = FALSE;
	//	//	return FALSE;
	//	//}
	//}
	//else {
	//	//mData->mLogEvent->fnWriteLogAndShowui((LOG_STATION)nBoardindex % 4, ERRORS, __FUNCTION__, "No Data:%d" + to_string(dwCount));
	//	//g_pOP->LogError(nBoardindex, __FUNCTION__, "No data capture one frame");
	//	status = FALSE;
	//	Sleep(1);
	//}

	//delete[]gpBmpBuffer;
	//delete[]gpDataBuffer;
	//delete[]gpRaw8Buffer;

	//return status;
	return true;
}

bool DeviceModuleGuadalupeCanyon::fnSetLVDS_Start(int nBoardindex)
{
	bool ret = false;
	//ret = PCI_LVDS_Start(nBoardindex % 4, CH0);
	//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "fnSetLVDS_Start Results:[%d]", ret);
 //   ret = PCI_LVDS_Stop(nBoardindex % 4, CH0);
	//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "PCI_LVDS_Stop Results:[%d]", ret);
 //   ret = PCI_LVDS_BufferFlush(nBoardindex % 4, CH0);
	//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "PCI_LVDS_BufferFlush Results:[%d]", ret);
	ret = PCI_LVDS_Start(nBoardindex % 4, CH0);
	//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "fnSetLVDS_Start Results:[%d]",ret);

	return ret;
}

bool DeviceModuleGuadalupeCanyon::fnSetLVDS_Stop(int nBoardindex)
{
	bool ret = false;
	ret = PCI_LVDS_Stop(nBoardindex % 4, CH0);
	//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "fnSetLVDS_Start Results:[%d]", ret);

	return ret;
}

bool DeviceModuleGuadalupeCanyon::Read_Tx_ASIC_ID(int nBoardindex, std::vector<unsigned char> & readBuffer)
{
	bool OK = false;
	std::vector<unsigned char> buffer;
	buffer.resize(4);

	unsigned char addr = 0x0B;
	OK = ReadBuffer(nBoardindex % 4, false, addr, buffer);

	readBuffer.resize(4);
	readBuffer[0] = buffer[3];
	readBuffer[1] = buffer[2];
	readBuffer[2] = buffer[1];
	readBuffer[3] = buffer[0];

	if (OK)
	{
		//g_pOP->LogDebug(nBoardindex, __FUNCTION__, "Read Tx ASIC ID OK, Addr:[0x%X], Value:[%02X %02X %02X %02X][%c%c%c%c]", addr, readBuffer[0], readBuffer[1], readBuffer[2], readBuffer[3], toAscii(readBuffer[0]), toAscii(readBuffer[1]), toAscii(readBuffer[2]), toAscii(readBuffer[3]));
	}
	else
	{
		//g_pOP->LogError(nBoardindex, __FUNCTION__, "Read Tx ASIC ID FAIL, Addr:[0x%X]");
	}

	return OK;
}

bool DeviceModuleGuadalupeCanyon::Read_Tx_ASIC_Trim(int nBoardindex, std::vector<unsigned char> & readBuffer)
{
	bool OK = false;
	readBuffer.resize(1);
	unsigned char addr = 0x70;

	OK = ReadByte(nBoardindex % 4, false, addr, &readBuffer[0]);
	if (OK)
	{
		//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Read Tx ASIC Trim OK, Addr:[0x%X], Value:[%02X][%c]", addr, readBuffer[0], toAscii(readBuffer[0]));
	}
	else
	{
		//g_pOP->LogError(nBoardindex, __FUNCTION__, "Read Tx ASIC Trim FAIL, Addr:[0x%X]");
	}

	return OK;
}

bool DeviceModuleGuadalupeCanyon::fnReadTx_ASIC_Trim(int nBoardindex, std::string &TrimSN)
{
	//USES_CONVERSION;
	BYTE bySlave = BANFF_TX_SLAVE_ADDRESS;
	uint8_t uData[25] = { '\0' };
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x00, 1, &uData[0]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR,[CCanyon_Banff:fnReadTx_ASIC_Trim], Read Error RDBYTE: 0x%02x", 0x00);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x01, 1, &uData[1]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR,[CCanyon_Banff:fnReadTx_ASIC_Trim], Read Error RDBYTE: 0x%02x", 0x01);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x02, 1, &uData[2]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR,[CCanyon_Banff:fnReadTx_ASIC_Trim], Read Error RDBYTE: 0x%02x", 0x02);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x03, 1, &uData[3]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR,[CCanyon_Banff:fnReadTx_ASIC_Trim], Read Error RDBYTE: 0x%02x", 0x03);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x04, 1, &uData[4]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR,[CCanyon_Banff:fnReadTx_ASIC_Trim], Read Error RDBYTE: 0x%02x", 0x04);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x05, 1, &uData[5]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR,[CCanyon_Banff:fnReadTx_ASIC_Trim], Read Error RDBYTE: 0x%02x", 0x05);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x06, 1, &uData[6]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR,[CCanyon_Banff:fnReadTx_ASIC_Trim], Read Error RDBYTE: 0x%02x", 0x06);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x07, 1, &uData[7]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR,[CCanyon_Banff:fnReadTx_ASIC_Trim], Read Error RDBYTE: 0x%02x", 0x07);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x08, 1, &uData[8]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR,[CCanyon_Banff:fnReadTx_ASIC_Trim], Read Error RDBYTE: 0x%02x", 0x08);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x09, 1, &uData[9]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR,[CCanyon_Banff:fnReadTx_ASIC_Trim], Read Error RDBYTE: 0x%02x", 0x09);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x0A, 1, &uData[10]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR,[CCanyon_Banff:fnReadTx_ASIC_Trim], Read Error RDBYTE: 0x%02x", 0x0A);
		return FALSE;
	}

	try
	{
		char SN5[20] = { '\0' };
		sprintf(SN5, "%02X%02X%02X%02X%02X", uData[10], uData[9], uData[8], uData[7], uData[6]);
		std::string TrimSN1 = SN5;
		char SN6[20] = { '\0' };
		sprintf(SN6, "%02X%02X%02X%02X%02X%02X", uData[5], uData[4], uData[3], uData[2], uData[1], uData[0]);
		std::string TrimSN2 = SN6;
		char SNL[23] = { '\0' };
		sprintf(SNL, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", uData[10], uData[9], uData[8], uData[7], uData[6], uData[5], uData[4], uData[3], uData[2], uData[1], uData[0]);
		TrimSN = SNL;
	}
	catch (const std::exception&ex)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR,[CCanyon_Banff:fnReadTx_ASIC_Trim], unexpected issue occur here! %s", ex.what());
	}

	return TRUE;
}


bool DeviceModuleGuadalupeCanyon::fnReadRx_ASIC_ID(int nBoardindex, std::string &RxID)
{
	//USES_CONVERSION;
	BYTE bySlave = BANFF_RX_SLAVE_ADDRESS;
	uint8_t uData[12] = { '\0' };
	char SN[20];
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 2, 0x05, 1, &uData[0]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR, Read Error RDBYTE: 0x%02x", 0x00);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 2, 0x06, 1, &uData[1]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR, Read Error RDBYTE: 0x%02x", 0x01);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 2, 0x07, 1, &uData[2]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR, Read Error RDBYTE: 0x%02x", 0x02);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 2, 0x09, 1, &uData[3]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR, Read Error RDBYTE: 0x%02x", 0x03);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 2, 0x0B, 1, &uData[4]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR, Read Error RDBYTE: 0x%02x", 0x04);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 2, 0x0C, 1, &uData[5]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR, Read Error RDBYTE: 0x%02x", 0x05);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 2, 0x00, 1, &uData[6]) == FALSE)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR, Read Error RDBYTE: 0x%02x", 0x06);
		return FALSE;
	}

	try
	{
		sprintf(SN, "%02X%02X%02X%02X%02X%02X%02X%02X", uData[0], uData[1], uData[2], uData[3], uData[4], uData[5], uData[6], uData[7]);
		RxID = SN;
	}
	catch (const std::exception&ex)
	{
		//ListOut((LOG_STATION)nBoardindex % 4, "ERROR, unexpected issue occur here! %s", ex.what());
	}

	return TRUE;
}

bool DeviceModuleGuadalupeCanyon::ReadTxASIC_Temper(int nBoardindex, double* pResult)
{
	bool bActivateState = false;
	unsigned char value = 0;

	bActivateState = CheckDeviceIsActive(nBoardindex % 4);
	std::vector<unsigned char> readBuffer;
	readBuffer.resize(2);

	if (bActivateState)
	{
		if (!ReadByte(nBoardindex % 4, false, 0x7A, &readBuffer[0]))
		{
			return false;
		}

		if (!ReadByte(nBoardindex % 4, false, 0x7B, &readBuffer[1]))
		{
			return false;
		}
	}
	else
	{
		// 1. Select channel for manual read.
		if (!WriteBit(nBoardindex % 4, false, 0x61, 2, 1, 0x01))
		{
			return false;
		}

		// 2. start adc conversion.
		if (!WriteBit(nBoardindex % 4, false, 0x61, 0, 0, 0))
		{
			return false;
		}

		if (!WriteBit(nBoardindex % 4, false, 0x61, 0, 0, 1))
		{
			return false;
		}

		//3. Read MAN_ADC_EOC
		int retryCount = 10;
		while (true)
		{
			if (!ReadBit(nBoardindex % 4, false, 0x71, 1, 1, &value))
			{
				return false;
			}

			if (value || retryCount <= 0)
			{
				break;
			}
			retryCount--;
		}

		readBuffer.resize(2);
		// 4. Read Manual ADC results, 
		if (!ReadByte(nBoardindex % 4, false, 0x8E, &readBuffer[0]))
		{
			return false;
		}

		if (!ReadByte(nBoardindex % 4, false, 0x8F, &readBuffer[1]))
		{
			return false;
		}

		if (!ReadBitVerify(nBoardindex % 4, false, 0x8F, 7, 4, 0x01))
		{

		}
	}

	unsigned short ADC_READOUT = (((unsigned short)readBuffer[0]) << 4) | (readBuffer[1] & 0x0F);
	double ADC_V = 1500. / 4095 * ADC_READOUT;
	double dTemperature = (ADC_V - 978.5) / 3.612;

	//g_pOP->LogInfo(nBoardindex, __FUNCTION__, "Read Tx ASIC Temperature OK, ADC_READOUT:[%d], ADC_V:[%f], Temp:[%f]", ADC_READOUT, ADC_V, dTemperature);

	*pResult = dTemperature;
	return true;
}

int getIndexOfSigns(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return ch - '0';
	}
	if (ch >= 'A' && ch <= 'F')
	{
		return ch - 'A' + 10;
	}
	if (ch >= 'a' && ch <= 'f')
	{
		return ch - 'a' + 10;
	}
	return -1;
}
long hexToDec(char *source)
{
	long sum = 0;
	long t = 1;
	int i, len;
	len = strlen(source);
	for (i = len - 1; i >= 0; i--)
	{
		sum += t * getIndexOfSigns(*(source + i));
		t *= 16;
	}
	return sum;
}

bool  DeviceModuleGuadalupeCanyon::fnCheckRegValue(int nBoardindex, unsigned short &tempV1, unsigned short &tempV2)
{
	BYTE bySlave = BANFF_TX_SLAVE_ADDRESS;
	unsigned char uData[10] = { 0 };
	unsigned short addr1 = 0x72;
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x72, 1, &uData[0]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x72);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x73, 1, &uData[1]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x73);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x74, 1, &uData[2]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x74);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x75, 1, &uData[4]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x75);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x76, 1, &uData[5]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x76);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x77, 1, &uData[6]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x77);
		return FALSE;
	}
	tempV1 = 0;
	for (int i = 0; i < 7; i++)
	{
		char tempChar = uData[i];
		tempV1 += hexToDec(&tempChar);
		uData[i] = 0;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x54, 1, &uData[0]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x54);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x55, 1, &uData[1]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x55);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x56, 1, &uData[2]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x56);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x57, 1, &uData[4]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x57);
		return FALSE;
	}
	tempV2 = 0;
	for (int i = 0; i < 5; i++)
	{
		char tempChar = uData[i];
		tempV2 += hexToDec(&tempChar);
	}
	return TRUE;
}

int NVM2SN(std::string input_hex, std::string& output_sn) {
	int err_value = 0;
	// Create base-34 dictionary
	std::string base34digits("0123456789ABCDEFGHJKLMNPQRSTUVWXYZ");

	do {
		std::stringstream SN;

		// Check that input_hex is required length;
		if (input_hex.length() != SN_HEX_LENGTH) {
			err_value = 1;
			//std::cout << "Hex is not 22 characters" << std::endl;
			break;
		}

		// convert PPPPYWW
		try {
			int decPPPPYWW;
			std::stringstream ssPPPPYWW;
			ssPPPPYWW << std::hex << input_hex.substr(0, 8);
			ssPPPPYWW >> decPPPPYWW;
			for (int i = 6; i >= 1; i--) {
				int char_idx = (int)floor(decPPPPYWW / (int)pow(34, i - 1));
				decPPPPYWW -= (char_idx * (int)pow(34, i - 1));
				SN << base34digits.at(char_idx);
				//std::cout << "char_idx : " << char_idx << " Char : " << base34digits.at(char_idx) << std::endl;
			}
		}
		catch (...) {
			err_value = 2;
			break;
		}

		// convert DSSSS
		try {
			int decDSSSS;
			std::stringstream ssDSSSS;
			ssDSSSS << std::hex << input_hex.substr(8, 6);
			ssDSSSS >> decDSSSS;
			for (int i = 5; i >= 1; i--) {
				int char_idx = (int)floor(decDSSSS / (int)pow(34, i - 1));
				decDSSSS -= (char_idx * (int)pow(34, i - 1));
				SN << base34digits.at(char_idx);
				//std::cout << "char_idx : " << char_idx << " Char : " << base34digits.at(char_idx) << std::endl;
			}
		}
		catch (...) {
			err_value = 3;
			break;
		}

		// convert EEEERX
		try {
			int decEEEERX;
			std::stringstream ssEEEERX;
			ssEEEERX << std::hex << input_hex.substr(14, 8);
			ssEEEERX >> decEEEERX;
			for (int i = 6; i >= 1; i--) {
				int char_idx = (int)floor(decEEEERX / (int)pow(34, i - 1));
				decEEEERX -= (char_idx * (int)pow(34, i - 1));
				SN << base34digits.at(char_idx);
				//std::cout << "char_idx : " << char_idx << " Char : " << base34digits.at(char_idx) << std::endl;
			}
		}
		catch (...) {
			err_value = 4;
			break;
		}

		//std::cout << SN.str() << std::endl;
		// Make SN a normal string for shorter code in the checksum calc
		std::string SN_str = SN.str();

		// Copy converted serial number over
		output_sn = SN.str();
	} while (false);
	return err_value;
}

bool DeviceModuleGuadalupeCanyon::fnReadingBarCodeSN(int nBoardindex, std::string& output_sn)
{
	bool status = TRUE;
	unsigned short barcode_start = 0x1AF;
	unsigned short barcode_end = 0x1B9;
	unsigned short plusOne = 0x001;
	char strSlave[] = { "BANFF_RX_SLAVE_ADDRESS" };
	std::string input_hex;
	unsigned short Nvm_Start = 0x310;

	for (size_t i = 0; i < barcode_end + 1 - barcode_start; i++)
	{
		unsigned short yy = Nvm_Start + barcode_start + i;
		//string data = mCanyonBanff.I2cRead_8bit(nBoardindex % 4, BANFF_RX_SLAVE_ADDRESS, yy);
		unsigned char readVal = 0;
		ReadByte(nBoardindex % 4, true, yy, &readVal);
		std::string value;
		//value = Format("%02X", readVal);
		char buf[64];
		sprintf(buf, "%02X", readVal);
		value = buf;
		input_hex = input_hex + value;

	}
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read NVM Dump :%s", input_hex.c_str());
	NVM2SN(input_hex, output_sn);
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read NVM Dump for Barcode:%s", output_sn.c_str());

	return status;
}

bool DeviceModuleGuadalupeCanyon::fnReadTxNVM(int nBoardindex, unsigned char* TxNVMData, const unsigned short  TxNVMSize)
{
	//Need to write read NVM function to this.
	unsigned short gID_PAGE_SIZE = 255;;
	unsigned short gID_PAGE_ADDRESS = 0;
	DWORD RxRegAddr = BANFF_TX_SLAVE_ADDRESS << 1;
	BYTE Tx_PAGE_DATA[256];
	memset(Tx_PAGE_DATA, 0, sizeof(Tx_PAGE_DATA));
	for (uint16_t current_page = 0; current_page < 1; current_page++)
	{
		//	Sleep(100);
		gID_PAGE_ADDRESS = 00;
		if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, RxRegAddr, 1, gID_PAGE_ADDRESS, gID_PAGE_SIZE, Tx_PAGE_DATA) == FALSE)
		{
			//g_pOP->LogError(nBoardindex,__FUNCTION__, "Read Error RDBYTE: 0x%02x .socket:%d", 0xB4,nBoardindex);
			return FALSE;
		}

		// Copy the whole block to the point 
		uint16_t startAddress = current_page * gID_PAGE_SIZE;
		uint16_t last_byte = (startAddress + gID_PAGE_SIZE);
		if (last_byte > TxNVMSize)
		{
			//g_pOP->LogError(nBoardindex,__FUNCTION__, "Read Size Error %d.socket:%d", last_byte,nBoardindex);
			return FALSE;
		}
		memcpy(TxNVMData + startAddress, Tx_PAGE_DATA, (gID_PAGE_SIZE));
	}

	return TRUE;
}

bool DeviceModuleGuadalupeCanyon::fnReadRxNVM(int nBoardindex, unsigned char* RxVMData, const unsigned short  RxNVMSize)
{
	unsigned short gID_EEPROM_PAGE_SIZE = 64;
	unsigned short gID_PAGE_ADDRESS = 0;
	DWORD wNVMRegAddr = BANFF_RX_SLAVE_ADDRESS << 1;
	BYTE EEPROM_PAGE_DATA[255];

	uint8_t NUM_EEPROM_PAGES = 16;


	for (uint16_t current_page = 0; current_page <= NUM_EEPROM_PAGES; current_page++)
	{
		gID_PAGE_ADDRESS = current_page * gID_EEPROM_PAGE_SIZE;
		if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, wNVMRegAddr, 2, (0x310 + gID_PAGE_ADDRESS), gID_EEPROM_PAGE_SIZE, EEPROM_PAGE_DATA) == FALSE)
		{
			//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadRxNVM], Read Error RDBYTE: 0x%02x", gID_EEPROM_PAGE_SIZE);
			return FALSE;
		}

		uint16_t startAddress = current_page + gID_EEPROM_PAGE_SIZE;
		uint16_t last_byte = startAddress + gID_EEPROM_PAGE_SIZE;
		if (last_byte > RxNVMSize)
		{
			//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadRxNVM], Read Size Error %d", last_byte);
			return FALSE;
		}
		memcpy((RxVMData + startAddress), EEPROM_PAGE_DATA, gID_EEPROM_PAGE_SIZE);
	}

	return TRUE;
}

int DeviceModuleGuadalupeCanyon::Read_NVM_DATA(int nBoardindex, unsigned char OTPData[], int nReadLength, int nStartAddr, int ECC, int iMode)
{
	if (nReadLength + nStartAddr > 1024 || nReadLength == 0) return FALSE;

	int i = 0, j = 0;
	int nStandbyChk = 0, nChkCounts = 0;
	int nStartWord = nStartAddr / 4;
	int nEndWord = (nStartAddr + nReadLength - 1) / 4;
	int nWords = nEndWord - nStartWord + 1;
	unsigned char szTemp[8] = { 0 };
	unsigned char szReadTmp[100] = { 0 };
	unsigned char ucTmpValue = 0;
	DWORD wNVMRegAddr = BANFF_RX_SLAVE_ADDRESS << 1;

	int nBulkLength = 0;
	int nEtcLength = 0;

	nBulkLength = nReadLength / 64;
	nEtcLength = nReadLength % 64;
	//m_pPfMemory->SetLog(nSite, "nBulk : %d / %d", nBulkLength, nEtcLength);
	//ListOut((LOG_STATION)nBoardindex % 4, "INFO,[CCanyon_Banff:Read_NVM_DATA], nBulk : %d / %d", nBulkLength, nEtcLength);

	for (i = nStartAddr; i < nStartAddr + nBulkLength * 64; i = i + 64)
	{
		memset(szReadTmp, 0, 100 * sizeof(unsigned char));
		PCI_I2C_SYS_Read(nBoardindex % 4, CH0, wNVMRegAddr, 2, 0x0310 + i, 64, szReadTmp);

		//		Sleep(10);
		for (j = 0; j < 64; j++)
		{
			OTPData[i + j] = szReadTmp[j];
			if (OTPData[i + j] != szReadTmp[j])
			{
				;
			}
			//ListOut((LOG_STATION)nBoardindex % 4, "INFO,[CCanyon_Banff:Read_NVM_DATA], Read  RDBYTE: [%d] 0x%02X != 0x%02X", +j, OTPData[i + j], szReadTmp[j]);
		}
	}

	memset(szReadTmp, 0, 100 * sizeof(unsigned char));
	for (i = nStartAddr + (nBulkLength * 64); i < (nStartAddr + (nBulkLength * 64)) + nEtcLength; i++)
	{
		PCI_I2C_SYS_Read(nBoardindex % 4, CH0, wNVMRegAddr, 2, 0x0310 + i, 1, szReadTmp);
		// 		Sleep(1);
		OTPData[i] = szReadTmp[0];
		if (OTPData[i] != szReadTmp[0])
		{
			;
		}
		//ListOut((LOG_STATION)nBoardindex % 4, "INFO,[CCanyon_Banff:Read_NVM_DATA], Read  RDBYTE: [%d] 0x%02X = 0x%02X", i, OTPData[i], szReadTmp[0]);
	}
	return TRUE;
}

void DeviceModuleGuadalupeCanyon::WriteBin_NVM(std::string filename, unsigned char DATA[], unsigned short DataSize)
{
	std::string filePath = filename + ".bin";

	std::ifstream inf;
	inf.open(filePath, std::ios::in);
	if (!inf)
	{
		// not create yet
		std::ofstream out;
		out.open(filePath.c_str(), std::ios::out | std::ios::app | std::ios::binary);

		out.write(reinterpret_cast<char*>(DATA), DataSize);

		out.flush();
		out.close();
	}

	inf.close();

}

bool DeviceModuleGuadalupeCanyon::NVMArrayToString(bool flag, std::string startAddr, unsigned char DATA[], unsigned short DataSize, std::string& address_list, std::string& data_list)
{
	try
	{
		std::stringstream address_stream;
		std::stringstream data_stream;
		// loop through the datasize, and convert each address location to fixed length 
		char temp_address[7];
		char temp_data[7];
		int mStartAddr = strtol(startAddr.c_str(), NULL, 16);
		int iStartBit = 0;
		if (flag) //默认16bit地址&值存储
		{
			for (int current_address = mStartAddr; current_address <= DataSize; current_address++)
			{
				sprintf(temp_address, "0x%04X", current_address);
				sprintf(temp_data, "0x%02X", DATA[iStartBit]);
				address_stream << temp_address << ";";
				data_stream << temp_data << ";";
				iStartBit++;
			}
		}
		else//8bit地址&值存储
		{
			for (int current_address = mStartAddr; current_address <= DataSize; current_address++)
			{
				sprintf(temp_address, "0x%02X", current_address);
				sprintf(temp_data, "0x%02X", DATA[iStartBit]);
				address_stream << temp_address << ";";
				data_stream << temp_data << ";";
				iStartBit++;
			}
		}

		address_list = address_stream.str();
		data_list = data_stream.str();
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

void _split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
}
std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	_split(s, delim, elems);
	return elems;
}

void DeviceModuleGuadalupeCanyon::WriteCSV_NVM(std::string filename, std::string NVMAddr, std::string NVMData)
{

	std::string dir = "";/*rawdatapath + "\\" + BarcodeSN + "\\" + TimeStamp + "\\" + "DUT" + "\\";*/
	if (0 != _access(dir.c_str(), 0))
	{
		//MakeDirectory(dir);
		_mkdir(dir.c_str());
	}
	std::string filePath = filename + ".csv";

	std::ifstream inf;
	inf.open(filePath, std::ios::in);
	if (!inf)
	{
		// not create yet
		std::ofstream out;
		out.open(filePath.c_str(), std::ios::out | std::ios::app);

		std::vector<std::string> NVMAddrList = split(NVMAddr, ';');
		std::vector<std::string> NVMDataList = split(NVMData, ';');
		std::string info;

		std::string tmpHeader = "Index,Address(Hex),Data(Hex),";

		out << tmpHeader + "\n";

		for (int i = 0; i < NVMAddrList.size(); ++i)
		{
			if (NVMDataList.at(i).length() != 0)
			{
				std::string info = Format("%d,%s,%s",(i) , NVMAddrList.at(i).c_str(), NVMDataList.at(i).c_str());
				out << info + "\n";
			}
		}
		out.flush();
		out.close();
	}

	inf.close();
}

bool DeviceModuleGuadalupeCanyon::fnReadTxREGNVM(int nBoardindex, std::string filename)
{
	std::string fileName =  filename;
	bool status;
	bool is16Bit = false;
	std::string TxNVMStringAddress;
	std::string TxNVMStringData;
	uint8_t	TxRegNVMData[TxRegSize];

	memset(TxRegNVMData, 0, sizeof(TxRegNVMData[0])*TxRegSize);
	status = fnReadTxNVM(nBoardindex % 4, TxRegNVMData, TxRegSize);
	WriteBin_NVM(fileName, TxRegNVMData, TxRegSize);
	NVMArrayToString(is16Bit, "0x00", TxRegNVMData, TxRegSize, TxNVMStringAddress, TxNVMStringData);
	WriteCSV_NVM(fileName, TxNVMStringAddress, TxNVMStringData);

	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "ReadTxREGNVM:%i FilePath:%s", status,filename.c_str());
	return status;
}
bool DeviceModuleGuadalupeCanyon::fnReadRxREGNVM(int nBoardindex, std::string filename)
{
	std::string fileName = /*filePath + "\\" +*/ filename;

	bool status = FALSE;
	bool is16Bit = TRUE;
	std::string TxNVMStringAddress;
	std::string TxNVMStringData;

	std::string RxNVMStringAddress;
	std::string RxNVMStringData;

	static const int RxNVMEndAddr = 0x70F;

	PUCHAR NVMMap_Read = new unsigned char[RxNVMSize];
	memset(NVMMap_Read, 0, RxNVMSize * sizeof(unsigned char));

	status = Read_NVM_DATA(nBoardindex % 4, NVMMap_Read, RxNVMSize, 0, 1, 1);
	WriteBin_NVM(fileName, NVMMap_Read, RxNVMSize);
	NVMArrayToString(is16Bit, "0x0310", NVMMap_Read, RxNVMEndAddr, RxNVMStringAddress, RxNVMStringData);
	WriteCSV_NVM(fileName, RxNVMStringAddress, RxNVMStringData);

	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "ReadRxREGNVM:%i FilePath:%s", status, filename.c_str());
	return status;
}

bool DeviceModuleGuadalupeCanyon::fnReadRTraceValue(int nBoardIndex, unsigned short &RTraceValue)
{
	bool status = TRUE;
	unsigned short temp = 0.0000;
	unsigned char address0 = 0x78;
	unsigned char address1 = 0x79;

	//status = GetRTRACEValue(nBoardindex % 4, address0, address1, RTraceValue);
	BYTE bySlave = BANFF_TX_SLAVE_ADDRESS;
	unsigned char address0_temp = 0x78;
	unsigned char address1_temp = 0x79;
	if (address0_temp != address0)
		address0 = address0_temp;
	if (address1_temp != address1)
		address1 = address1_temp;
	int ret = -1;
	int		naddrLen, ndataLen;
	naddrLen = 1;
	ndataLen = 1;
	BYTE	buf;
	uint8_t uData[4] = { 0, };
	//if (PCI_I2C_SYS_Read(nBoardIndex, CH0, bySlave << 1, 1, 0xB4, 1, &uData[0]) == FALSE)
	//{
	//	ListOut((LOG_STATION)nBoardIndex, "ERROR,[CCanyon_Banff:GetRTRACEValue], Read Error RDBYTE: 0x%02x", 0xB4);
	//	return FALSE;
	//}
	uint8_t statuTemp = 0x00;
	statuTemp = uData[0] & 0x07;
	volatile int statueValue = 0;   //0--default 1--idl 2 -- active
	if (statuTemp == 0x02)
	{
		statueValue = 1;
		if (PCI_I2C_SYS_Read(nBoardIndex%4, CH0, bySlave << 1, 1, 0x60, 1, &uData[1]) == FALSE)
		{
			//g_pOP->LogError(nBoardIndex,__FUNCTION__, "ERROR,[CCanyon_Banff:GetRTRACEValue], Read Error RDBYTE: 0x%02x", 0x60);
			return FALSE;
		}
		uint8_t utemp = 0x00;
		utemp = uData[1] | 0x02;
		if (PCI_I2C_SYS_Write(nBoardIndex%4, CH0, bySlave << 1, 1, 0x60, 1, &utemp) == FALSE)
		{
			//g_pOP->LogError(nBoardIndex,__FUNCTION__, "ERROR,[CCanyon_Banff:GetRTRACEValue], Write Error RDBYTE: 0x%02x", 0x60);
			return FALSE;
		}
		Sleep(1);
		uData[2] = 0x00;
		if (PCI_I2C_SYS_Read(nBoardIndex%4, CH0, bySlave << 1, 1, 0xB5, 1, &uData[2]) == FALSE)
		{
			//g_pOP->LogError(nBoardIndex,__FUNCTION__, "ERROR,[CCanyon_Banff:GetRTRACEValue], Read Error RDBYTE: 0x%02x", 0xB5);
			return FALSE;
		}
		utemp = 0x00;
		utemp = uData[2] | 0x20;
		if (PCI_I2C_SYS_Write(nBoardIndex%4, CH0, bySlave << 1, 1, 0xB5, 1, &utemp) == FALSE)
		{
			//g_pOP->LogError(nBoardIndex,__FUNCTION__, "ERROR,[CCanyon_Banff:GetRTRACEValue], Write Error RDBYTE: 0x%02x", 0xB5);
			return FALSE;
		}
		uData[2] = 0x00;
		if (PCI_I2C_SYS_Read(nBoardIndex%4, CH0, bySlave << 1, 1, 0xB4, 1, &uData[2]) == FALSE)
		{
			//g_pOP->LogError(nBoardIndex,__FUNCTION__, "ERROR,[CCanyon_Banff:GetRTRACEValue], Read Error RDBYTE: 0x%02x", 0xB4);
			return FALSE;
		}
		utemp = 0x00;
		utemp = uData[2] & 0x03;
		if (utemp < 1)
		{
			utemp = uData[2] & 0xF8;
			utemp = uData[2] | 0x03;
			if (PCI_I2C_SYS_Write(nBoardIndex%4, CH0, bySlave << 1, 1, 0xB4, 1, &utemp) == FALSE)
			{
				//g_pOP->LogError(nBoardIndex,__FUNCTION__, "ERROR,[CCanyon_Banff:GetRTRACEValue], Write Error RDBYTE: 0x%02x", 0xB4);
				return FALSE;
			}
		}
	}
	else
	{
		;
	}
	Sleep(10);
	if (PCI_I2C_SYS_Read(nBoardIndex%4, CH0, bySlave << 1, 1, address0, ndataLen, &buf) == FALSE)
	{
		Sleep(30); //100
		if (PCI_I2C_SYS_Read(nBoardIndex%4, CH0, bySlave << 1, 1, address0, ndataLen, &buf) == FALSE)
		{
			//g_pOP->LogError(nBoardIndex,__FUNCTION__, "ERROR,[CCanyon_Banff:GetRTRACEValue], Read Error RDBYTE: 0x%02x", address0);
			return FALSE;
		}
	}

	//ListOut((LOG_STATION)nBoardIndex%4, "INFO,[CCanyon_Banff:GetRTRACEValue], Read RDBYTE: [0x%02x], VALUE:[0x%02x]", address0, buf);
	unsigned char result0 = buf;
	if (PCI_I2C_SYS_Read(nBoardIndex%4, CH0, bySlave << 1, 1, address1, ndataLen, &buf) == FALSE)
	{
		Sleep(30); //100
		if (PCI_I2C_SYS_Read(nBoardIndex%4, CH0, bySlave << 1, 1, address1, ndataLen, &buf) == FALSE)
		{
			//g_pOP->LogError(nBoardIndex,__FUNCTION__, "ERROR,[CCanyon_Banff:GetRTRACEValue], Read Error RDBYTE: 0x%02x", address1);
			return FALSE;
		}
	}
	//g_pOP->LogDebug(nBoardIndex,__FUNCTION__, "INFO,[CCanyon_Banff:GetRTRACEValue], Read RDBYTE: [0x%02x], VALUE:[0x%02x]", address1, buf);

	unsigned char result1 = buf;
	RTraceValue = ((unsigned short)result0) << 4;
	RTraceValue += (unsigned short)result1 & 0x0F;

	return status;
}

bool DeviceModuleGuadalupeCanyon::fnReadRtraceTSMC(int nBoardindex, float &RtraceRaw)
{
	BYTE bySlave = BANFF_TX_SLAVE_ADDRESS;
	uint8_t uData[4] = { 0, };
	char SN[20] = { '\0' };
	uData[0] = 0x1;
	volatile int B8Flag = 0;
	volatile int B8FlagCount = 30;
	int retry1 = 10;
	while (B8Flag == 0 && retry1 != 0)
	{
		if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB8, 1, &uData[0]) == FALSE)
		{
			uint8_t tempValue = 0;
			tempValue = uData[0] | 0x1;
			PCI_I2C_SYS_Write(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB8, 1, &tempValue);
			Sleep(0.001);
			retry1--;
			continue;
		}
		if ((uData[0] & 0x01) == 1)
		{
			B8Flag = 1;
			break;
		}
		Sleep(1);
		if (B8FlagCount <= 0)
			break;
		else
			B8FlagCount--;
	}
	uData[1] = 0x2E;
	if (PCI_I2C_SYS_Write(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB9, 1, &uData[1]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Write Error RDBYTE: 0x%02x", 0xB9);
		return FALSE;
	}
	uData[1] = 0x20;
	if (PCI_I2C_SYS_Write(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB6, 1, &uData[1]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Write Error RDBYTE: 0x%02x", 0xB6);
		return FALSE;
	}
	Sleep(1);
	B8Flag = 0;
	uData[0] = 0x00;
	B8FlagCount = 30;
	int retry2 = 10;
	while (B8Flag == 0 && retry2 != 0)
	{
		if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB8, 1, &uData[0]) == FALSE)
		{
			Sleep(0.001);
			retry2--;
			continue;
		}
		if ((uData[0] & 0x01) == 1)
		{
			B8Flag = 1;
			break;
		}
		Sleep(1);
		if (B8FlagCount <= 0)
			break;
		else
			B8FlagCount--;
	}
	uData[0] = 0x00; uData[1] = 0x00; uData[2] = 0x00; uData[3] = 0x00;
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xC2, 1, &uData[0]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Read Error RDBYTE: 0x%02x", 0xC2);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xC3, 1, &uData[1]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Read Error RDBYTE: 0x%02x", 0xC3);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xC4, 1, &uData[2]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Read Error RDBYTE: 0x%02x", 0xC4);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xC5, 1, &uData[3]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Read Error RDBYTE: 0x%02x", 0xC5);
		return FALSE;
	}
	uint8_t clearValue = 0x00;
	if (PCI_I2C_SYS_Write(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB6, 1, &clearValue) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Write Error RDBYTE: 0x%02x", 0xB6);
		return FALSE;
	}
	sprintf(SN, "%02X%02X%02X%02X", uData[3], uData[2], uData[1], uData[0]);
	float AddressData = (((DWORD)uData[0]) << 8) + (DWORD)uData[1];

	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "INFO,[CCanyon_Banff:fnReadRtraceTSMC],  RDBYTE: %s - [0x%02x]", "0x2E[0]", uData[0]);
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "INFO,[CCanyon_Banff:fnReadRtraceTSMC],  RDBYTE: %s - [0x%02x]", "0x2E[1]", uData[1]);

	RtraceRaw = AddressData * 16.0 / 1000;
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "INFO,[CCanyon_Banff:fnReadRtraceTSMC],RtraceRaw:  %f", RtraceRaw);

	return TRUE;
}

bool DeviceModuleGuadalupeCanyon::fnGetRtrace_ADC(int nBoardindex, RTraceData & rTraceData)
{
	bool status = TRUE;
	double RPU;
	std::vector<std::string> tempVec;
	unsigned short ADC_READOUT;
	std::vector<double> vADCReadOut;
	std::vector<double> vRtraceRaw;
	std::vector<double> vADCRaw;
	double dRtrace_Mean_ADC = 0.0;
	double dRtrace_Mean = 0.0;
	double dRtrace_Max = 0.0;
	double dRtrace_Min = 0.0;
	double dRtrace_Range = 0.0;
	double dRtrace_Stdev = 0.0;
	double dRtrace_TSMC = 0.0;
	double dRtrace_Delta = dRtrace_Mean - dRtrace_TSMC;
	RPU = 332000;//

	//读取10次的ADC原始值
	for (size_t i = 0; i < 10; i++)
	{
		status = fnReadRTraceValue(nBoardindex % 4, ADC_READOUT);
		vADCReadOut.push_back(ADC_READOUT);
		Sleep(2.5);//2.5
	}
	if (vADCReadOut.empty())
	{
		return false;
	}

	std::string sADC = "Read Rtrace Value List Rtrace_ADC:";
	std::string sRTrace = "Read Rtrace Value List Rtrace:";
	//将对应的readout都保存成对应次数的数组
	for (size_t i = 0; i < vADCReadOut.size(); i++)
	{
		double ADC_V = (double)(1.5 / 4095) * vADCReadOut.at(i);
		double dRTraceTemp = ADC_V * RPU / (1.5 - ADC_V);
		double dRTrace = (dRTraceTemp / 1000.0);
		vRtraceRaw.push_back(dRTrace);
		vADCRaw.push_back(ADC_V);
		char buf[64];
		sprintf(buf, "%f", ADC_V);
		sRTrace = sADC + buf;
		//sRTrace = Format("%s %f", sRTrace.c_str(),(ADC_V));
	}

	//算出 ADC Mean
	double sum = std::accumulate(std::begin(vADCRaw), std::end(vADCRaw), 0.0);
	dRtrace_Mean_ADC = sum / vADCRaw.size(); //均值  

	//算出 Rtrace Mean
	double Rtrace_sum = std::accumulate(std::begin(vRtraceRaw), std::end(vRtraceRaw), 0.0);
	dRtrace_Mean = Rtrace_sum / vRtraceRaw.size(); //均值  

	//计算出Rtrace stdev
	double Rtrace_accum = 0.0;
	std::for_each(std::begin(vRtraceRaw), std::end(vRtraceRaw), [&](const double d) {
		Rtrace_accum += (d - dRtrace_Mean)*(d - dRtrace_Mean);
	});

	dRtrace_Stdev = sqrt(Rtrace_accum / (vRtraceRaw.size() - 1)); //方差  

	//求Rtrace最大值和最小值
	dRtrace_Max = vRtraceRaw[0]; //let, first element is the smallest one
	dRtrace_Min = vRtraceRaw[0]; //also let, first element is the biggest one

	for (int i = 1; i < vRtraceRaw.size(); i++)  //start iterating from the second element
	{
		if (vRtraceRaw[i] < dRtrace_Min)
		{
			dRtrace_Min = vRtraceRaw[i];
		}
		if (vRtraceRaw[i] > dRtrace_Max)
		{
			dRtrace_Max = vRtraceRaw[i];
		}
	}

	//计算出Rtrace range
	dRtrace_Range = dRtrace_Max - dRtrace_Min;

	float fRtraceRawTSMC = 0.0;
	fnReadRtraceTSMC(nBoardindex % 4, fRtraceRawTSMC);

	dRtrace_TSMC = fRtraceRawTSMC;
	dRtrace_Delta = dRtrace_Mean - dRtrace_TSMC;

	rTraceData.dRtrace_Mean_ADC = dRtrace_Mean_ADC;
	rTraceData.dRtrace_Mean = dRtrace_Mean;
	rTraceData.dRtrace_Max = dRtrace_Max;
	rTraceData.dRtrace_Min = dRtrace_Min;
	rTraceData.dRtrace_Range = dRtrace_Range;
	rTraceData.dRtrace_Stdev = dRtrace_Stdev;
	rTraceData.dRtrace_TSMC = fRtraceRawTSMC;
	rTraceData.dRtrace_Delta = dRtrace_Mean - dRtrace_TSMC;

	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "ADC:%s",sADC.c_str());
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Rtrace:%s" , sRTrace.c_str());
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read Rtrace Value Rtrace_Mean_ADC:%f", dRtrace_Mean_ADC);
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read Rtrace Value Rtrace_Mean:%f",dRtrace_Mean);
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read Rtrace Value Rtrace_Max:%f" ,dRtrace_Max);
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read Rtrace Value Rtrace_Min:%f", dRtrace_Min);
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read Rtrace Value Rtrace_Range:%f" , dRtrace_Range);
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read Rtrace Value Rtrace_Stdev:%f", dRtrace_Stdev);
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read Rtrace Value dRtrace_TSMC:%f",dRtrace_TSMC);
	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read Rtrace Value dRtrace_Delta:%f",dRtrace_Delta);

	return status;
}

bool DeviceModuleGuadalupeCanyon::fnReadUserModeNTCNew(int nBoardindex, uint8_t *AddressGroup, int AddressGroupSize, DWORD *AddressData)
{
	//USES_CONVERSION;
	bool ret = false;
	BYTE bySlave = BANFF_TX_SLAVE_ADDRESS;
	uint8_t uData[4] = { 0, };
	char SN[20] = { '\0' };
	for (int i = 0; i < AddressGroupSize; i++)
	{
		uint8_t AddressTemp = AddressGroup[i];
		ret = fnReadUserModeNTCNewGetOne(nBoardindex % 4, AddressTemp, AddressData[i]);
		if (ret == false)
		{
			break;
		}
	}
	std::string TraceID = SN;

	return ret;
}
bool DeviceModuleGuadalupeCanyon::fnReadUserModeNTCNewBak(int nBoardindex, uint8_t *AddressGroup, int AddressGroupSize, DWORD *AddressData)
{
	//USES_CONVERSION;
	BYTE bySlave = BANFF_TX_SLAVE_ADDRESS;
	uint8_t uData[4] = { 0, };
	char SN[20] = { '\0' };
	for (int i = 0; i < AddressGroupSize; i++)
	{
		uint8_t AddressTemp = AddressGroup[i];
		fnReadUserModeNTCNewGetOne(nBoardindex % 4, AddressTemp, AddressData[i]);
	}
	uData[0] = 0x1;
	volatile int B8Flag = 0;
	while (B8Flag == 0)
	{
		if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB8, 1, &uData[0]) == FALSE)
		{
			uint8_t tempValue = 0;
			tempValue = uData[0] | 0x1;
			PCI_I2C_SYS_Write(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB8, 1, &tempValue);
			Sleep(0.001);
			continue;
		}
		if ((uData[0] & 0x01) == 1)
		{
			B8Flag = 1;
			break;
		}
		Sleep(0.001);
	}
	uData[1] = 0x00;
	if (PCI_I2C_SYS_Write(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB9, 1, &uData[1]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewBak], Write Error RDBYTE: 0x%02x", 0xB9);
		return FALSE;
	}
	uData[1] = 0x20;
	if (PCI_I2C_SYS_Write(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB6, 1, &uData[1]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewBak], Write Error RDBYTE: 0x%02x", 0xB6);
		return FALSE;
	}
	B8Flag = 0;
	uData[0] = 0x00;
	while (B8Flag == 0)
	{
		if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB8, 1, &uData[0]) == FALSE)
		{
			Sleep(0.001);
			continue;
		}
		if ((uData[0] & 0x01) == 1)
		{
			B8Flag = 1;
			break;
		}
		Sleep(0.001);
	}
	uData[0] = 0x00; uData[1] = 0x00; uData[2] = 0x00; uData[3] = 0x00;
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xC2, 1, &uData[0]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewBak], Read Error RDBYTE: 0x%02x", 0xC2);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xC3, 1, &uData[1]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewBak], Read Error RDBYTE: 0x%02x", 0xC3);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xC4, 1, &uData[2]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewBak], Read Error RDBYTE: 0x%02x", 0xC4);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xC5, 1, &uData[3]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewBak], Read Error RDBYTE: 0x%02x", 0xC5);
		return FALSE;
	}
	sprintf(SN, "%02X%02X%02X%02X", uData[3], uData[2], uData[1], uData[0]);
	std::string TraceID = SN;
	return TRUE;
}

bool DeviceModuleGuadalupeCanyon::fnReadUserModeNTCNewGetOne(int nBoardindex, uint8_t AddressGroup, DWORD &AddressData)
{
	bool ret = true;
	BYTE bySlave = BANFF_TX_SLAVE_ADDRESS;
	uint8_t uData[4] = { 0, };
	char SN[20] = { '\0' };
	uData[0] = 0x1;
	volatile int B8Flag = 0;
	volatile int B8FlagCount = 2; //30
	int retry1 = 2; //10
	while (B8Flag == 0 && retry1 != 0)
	{
		if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB8, 1, &uData[0]) == FALSE)
		{
			uint8_t tempValue = 0;
			tempValue = uData[0] | 0x1;
			PCI_I2C_SYS_Write(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB8, 1, &tempValue);
			Sleep(0.001);
			retry1--;
			continue;
		}
		if ((uData[0] & 0x01) == 1)
		{
			B8Flag = 1;
			break;
		}
		Sleep(1);
		if (B8FlagCount <= 0)
			break;
		else
			B8FlagCount--;
	}
	uData[1] = AddressGroup;
	if (PCI_I2C_SYS_Write(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB9, 1, &uData[1]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Write Error RDBYTE: 0x%02x", 0xB9);
		return FALSE;
	}
	uData[1] = 0x20;
	if (PCI_I2C_SYS_Write(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB6, 1, &uData[1]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Write Error RDBYTE: 0x%02x", 0xB6);
		return FALSE;
	}
	Sleep(0.01);
	B8Flag = 0;
	uData[0] = 0x00;
	B8FlagCount = 2;//30
	int retry2 = 2; //10s
	while (B8Flag == 0 && retry2 != 0)
	{
		if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB8, 1, &uData[0]) == FALSE)
		{
			Sleep(0.001);
			retry2--;
			continue;
		}
		if ((uData[0] & 0x01) == 1)
		{
			B8Flag = 1;
			break;
		}
		Sleep(1);
		if (B8FlagCount <= 0)
			break;
		else
			B8FlagCount--;
	}
	uData[0] = 0x00; uData[1] = 0x00; uData[2] = 0x00; uData[3] = 0x00;
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xC2, 1, &uData[0]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Read Error RDBYTE: 0x%02x", 0xC2);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xC3, 1, &uData[1]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Read Error RDBYTE: 0x%02x", 0xC3);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xC4, 1, &uData[2]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Read Error RDBYTE: 0x%02x", 0xC4);
		return FALSE;
	}
	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xC5, 1, &uData[3]) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Read Error RDBYTE: 0x%02x", 0xC5);
		return FALSE;
	}
	uint8_t clearValue = 0x00;
	if (PCI_I2C_SYS_Write(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB6, 1, &clearValue) == FALSE)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadUserModeNTCNewGetOne], Write Error RDBYTE: 0x%02x", 0xB6);
		return FALSE;
	}
	sprintf(SN, "%02X%02X%02X%02X", uData[3], uData[2], uData[1], uData[0]);
	AddressData = (((DWORD)uData[3]) << 24) + (((DWORD)uData[2]) << 16) + (((DWORD)uData[1]) << 8) + (DWORD)uData[0];
	return TRUE;
}

int Hex2String(char tempChar, std::string & hexstr)
{
	hexstr = "";
	unsigned short value = tempChar;
	value = value & 0x00FF;
	int v1 = value / 16;
	int v2 = value % 16;
	char hex1;
	char hex2;

	if (v1 >= 0 && v1 <= 9)
		hex1 = (char)(48 + v1);
	else
		hex1 = (char)(55 + v1);

	if (v2 >= 0 && v2 <= 9)
		hex2 = (char)(48 + v2);
	else
		hex2 = (char)(55 + v2);

	if (hex1 >= 'A' && hex1 <= 'F')
		hex1 += 32;

	if (hex2 >= 'A' && hex2 <= 'F')
		hex2 += 32;

	hexstr = hexstr + hex1 + hex2;

	return 0;
}

//只是为了TX_NVM 0x16-0x49 DWORD suzu
void WriteCSV_NVM3(std::string filename, std::string NVMAddr, DWORD *NVMData, std::string strNVMData)
{
	//std::string dir = "";
	//if (!IsExistFile(dir))
	//{
	//	MakeDirectory(dir);
	//}
	//std::string filePath = Format("%s.csv", filename.c_str() );

	//std::ifstream inf;
	//inf.open(filePath, std::ios::in);
	//if (!inf)
	//{
	//	// not create yet
	//	std::ofstream out;
	//	out.open(filePath.c_str(), std::ios::out | std::ios::app);

	//	std::vector<std::string> NVMAddrList = split(NVMAddr, ';');

	//	std::string info;

	//	char uData[4] = { 0, };
	//	DWORD tempValue = 0x0;
	//	std::string IndexLine = "Index,Address(Hex),Data(Hex)";
	//	out << IndexLine + "\n";

	//	for (int i = 0; i < NVMAddrList.size(); ++i)
	//	{
	//		//if (NVMDataList.at(i).length() != 0)
	//		//{
	//		//	std::string info = NVMAddrList.at(i) + "," + NVMDataList.at(i);
	//		//	out << info + "\n";
	//		//}		
	//		tempValue = 0x0;
	//		tempValue = NVMData[i];
	//		uData[0] = uData[1] = uData[2] = uData[3] = 0x0;
	//		uData[0] = tempValue;
	//		uData[1] = tempValue >> 8;
	//		uData[2] = tempValue >> 16;
	//		uData[3] = tempValue >> 24;

	//		std::string u1 = ""; Hex2String(uData[0], u1);
	//		std::string u2 = ""; Hex2String(uData[1], u2);
	//		std::string u3 = ""; Hex2String(uData[2], u3);
	//		std::string u4 = ""; Hex2String(uData[3], u4);

	//		{
	//			std::string info0 = "";
	//			info0 = Format("%d,%s[0],0x%s", (i) , NVMAddrList.at(i).c_str(), u1);//7 8
	//			out << info0 + "\n";
	//			std::string info1 = "";
	//			info1 = Format("%d,%s[1],0x%s", (i) ,NVMAddrList.at(i).c_str(), u2);//5 6
	//			out << info1 + "\n";
	//			std::string info2 = "";
	//			info2 = Format("%d,%s[2],0x%s", (i), NVMAddrList.at(i).c_str(), u3);//3 4
	//			out << info2 + "\n";
	//			std::string info3 = "";
	//			info3 = Format("%d,%s[3],0x%s", (i), NVMAddrList.at(i).c_str(), u4);//1 2
	//			out << info3 + "\n";
	//		}
	//	}
	//	out.flush();
	//	out.close();
	//}

	//inf.close();
}

bool DeviceModuleGuadalupeCanyon::fnReadTX_NVM(int nBoardindex, std::string FileName)
{
	//return false;//TODO xbh

	std::string TxRegStringAddress;
	std::string TxRegStringData;

	std::string fileName = FileName;

	BOOL status;
	BOOL is16Bit = FALSE;
	const int  lengthAddress = /*52;*/ 75; //0x4B
	uint8_t AddresStart = 0x16;
	uint8_t AddressGroup[lengthAddress];
	
	for (int i = 0; i < lengthAddress; i++)
	{
		AddressGroup[i] = AddresStart;
		AddresStart = AddresStart + 0x01;
	}
	DWORD AddressData[lengthAddress + 1] = { '\0' };
	std::string SN = "N/A";
	status = fnReadUserModeNTCNew(nBoardindex % 4, AddressGroup, lengthAddress, AddressData);
	WriteBin_NVM(fileName, AddressGroup, lengthAddress);
	NVMArrayToString(is16Bit, "0x16", AddressGroup, lengthAddress, TxRegStringAddress, TxRegStringData);
	WriteCSV_NVM3(fileName, TxRegStringAddress, AddressData, TxRegStringData);
	
	//g_pOP->LogInfo(nBoardindex,__FUNCTION__, "MODULE_READ_TXNVM OK");
	return status;
}


bool DeviceModuleGuadalupeCanyon::fnReadRx_reg(int nBoardindex, std::vector<std::string> &dataVecotrOut)
{
	std::string dataValue_1;
	std::string dataValue_2;
	std::string dataValue_3;
	std::string dataValue_4;
	std::string dataValue_5;
	std::string dataValue_6;
	std::string dataValue_7;
	std::string dataValue_8;
	//unsigned char udataValue_1;
	//unsigned char udataValue_2;
	//unsigned char udataValue_3;
	//unsigned char udataValue_4;
	//unsigned char udataValue_5;
	//unsigned char udataValue_6;
	//unsigned char udataValue_7;
	//unsigned char udataValue_8;
	int tmpfloat = 0;
	double Temperature = 0.0;
	char strSlave[] = { "BANFF_RX_SLAVE_ADDRESS" };
	unsigned short strAddrRead_1 = 0x120;
	unsigned short strAddrRead_2 = 0x121;
	unsigned short strAddrRead_3 = 0x146;
	unsigned short strAddrRead_4 = 0x147;
	unsigned short strAddrRead_5 = 0x14A;
	unsigned short strAddrRead_6 = 0x15E;
	unsigned short strAddrRead_7 = 0x15F;
	//	char strAddrRead_8[] = { "0x14B" };
	int nAddrLen = 2;
	int nDataLen = 2;// 1;//
	//ReadByte(nBoardindex % 4, true, strAddrRead_1, &udataValue_1);
	//ReadByte(nBoardindex % 4, true, strAddrRead_2, &udataValue_2);
	//ReadByte(nBoardindex % 4, true, strAddrRead_3, &udataValue_3);
	//ReadByte(nBoardindex % 4, true, strAddrRead_4, &udataValue_4);
	//ReadByte(nBoardindex % 4, true, strAddrRead_5, &udataValue_5);
	//ReadByte(nBoardindex % 4, true, strAddrRead_6, &udataValue_6);
	//ReadByte(nBoardindex % 4, true, strAddrRead_7, &udataValue_7);
	//ReadByte(nBoardIndex%4, true, strAddrRead_8, &udataValue_8);
	dataValue_1 = I2cReadByte(nBoardindex % 4, true, strAddrRead_1, nDataLen);
	dataValue_2 = I2cReadByte(nBoardindex % 4, true, strAddrRead_2, nDataLen);
	dataValue_3 = I2cReadByte(nBoardindex % 4, true, strAddrRead_3, nDataLen);
	dataValue_4 = I2cReadByte(nBoardindex % 4, true, strAddrRead_4, nDataLen);
	dataValue_5 = I2cReadByte(nBoardindex % 4, true, strAddrRead_5, nDataLen);
	dataValue_6 = I2cReadByte(nBoardindex % 4, true, strAddrRead_6, nDataLen);
	dataValue_7 = I2cReadByte(nBoardindex % 4, true, strAddrRead_7, nDataLen);

	//dataValue_1 = Format("0x%04X", udataValue_1);
	//dataValue_2 = Format("0x%04X", udataValue_2);
	//dataValue_3 = Format("0x%04X", udataValue_3);
	//dataValue_4 = Format("0x%04X", udataValue_4);
	//dataValue_5 = Format("0x%04X", udataValue_5);
	//dataValue_6 = Format("0x%04X", udataValue_6);
	//dataValue_7 = Format("0x%04X", udataValue_7);
	//dataValue_8 = Format("0x%04X", udataValue_8);

	dataVecotrOut.push_back(dataValue_1);
	dataVecotrOut.push_back(dataValue_2);
	dataVecotrOut.push_back(dataValue_3);
	dataVecotrOut.push_back(dataValue_4);
	dataVecotrOut.push_back(dataValue_5);
	dataVecotrOut.push_back(dataValue_6);
	dataVecotrOut.push_back(dataValue_7);

	return true;
}

std::vector<std::string> fnGetRx_regAddr()
{
	std::vector<std::string> addrVecotrOut = { "0x120","0x121","0x146" ,"0x147" ,"0x14A" ,"0x15E" ,"0x15F" ,"0x14B" };

	return addrVecotrOut;
}

std::string vecToString(std::vector<std::string> m_vec, std::string elems)
{
	std::string mstream;
	for (auto s : m_vec)
	{
		mstream = mstream + s + elems;
	}
	return mstream;
}

bool DeviceModuleGuadalupeCanyon::fnReadRxTemperature(int nBoardindex, double& temperature)
{
	BOOL status;
	char strAddrWrite[] = { "0x0101" }; //swtich standby mode
	unsigned short strAddrRead = 0x00B0;
	int nAddrLen = 2;
	int nDataLen = 2;
	float tmpfloat = 0;
	BYTE bySlave = BANFF_RX_SLAVE_ADDRESS;

	try
	{
		unsigned char * pBuf = NULL;
		//unsigned char *uData = { 0 };
		//unsigned char readValue = 0;
		std::string sReadValue = "";
		BYTE uData[4] = { 0 };
		status = PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, nAddrLen, strAddrRead, nDataLen, uData);
		//string dataValue = Format("%X", readValue);
		for (int i = 0; i < nDataLen; i++) {
			//readValue.AppendFormat(_T("%02X"), uData[i]);
			char buf[64];
			sprintf(buf, "%X", uData[i]);
			sReadValue += buf;
		}
		tmpfloat = strtol(sReadValue.c_str(), NULL, 16);
		temperature = tmpfloat ? tmpfloat / 2 : 0.00;

	}
	catch (const std::exception&ex)
	{
		//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnReadRxTemperature], unexpected issue occur here! %s", ex.what());
	}

	return status;
}

bool DeviceModuleGuadalupeCanyon::fnCheckHardBrick(int nBoardindex, std::string& b4Value)
{
	////BANFF_TX_SLAVE_ADDRESS
	//bool status = false;
	//int isBit16 = false;
	//unsigned short uAdd = 0xB4;
	//unsigned char readVal = 0;
	//bool ret = g_pDEV->m_BanffControl.ReadByte(nBoardindex % 4, isBit16, uAdd, &readVal);
	//std::string value;
	//value = Format("0x%02X", readVal);
	////g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read 0xB4:%s", value.c_str());
	//if (ret)
	//{
	//	if (value == "0x04" || value == "0x05")
	//	{
	//		status = true;
	//	}
	//}
	//else
	//{
	//	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read 0xB4 Fail.");
	//}
	//b4Value = value;
	//return status;
	return true;
}

void replace(std::string & s, std::string now, std::string rep)
{
	size_t s_begin = 0;
	s_begin = s.find(now, s_begin);
	while (s_begin != -1)
	{
		s.replace(s_begin, now.length(), rep);
		s_begin = s.find(now, s_begin);
	}
}

bool NVMArrayToStringComa(BOOL flag, std::string startAddr, uint8_t DATA[], uint16_t DataSize, std::string& address_list, std::string& data_list)
{
	try
	{
		std::stringstream address_stream;
		std::stringstream data_stream;
		// loop through the datasize, and convert each address location to fixed length 
		char temp_address[7];
		char temp_data[7];
		int mStartAddr = strtol(startAddr.c_str(), NULL, 16);
		if (flag) //默认16bit地址&值存储
		{
			for (int current_address = mStartAddr; current_address < DataSize; current_address++)
			{
				sprintf(temp_address, "0x%04x", current_address);
				sprintf(temp_data, "0x%02x", DATA[current_address]);
				address_stream << temp_address << ",";
				data_stream << temp_data << ",";
			}
		}
		else//8bit地址&值存储
		{
			for (int current_address = mStartAddr; current_address < DataSize; current_address++)
			{
				sprintf(temp_address, "0x%02x", current_address);
				sprintf(temp_data, "0x%02x", DATA[current_address]);
				address_stream << temp_address << ",";
				data_stream << temp_data << ",";
			}
		}

		address_list = address_stream.str();
		data_list = data_stream.str();
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}


bool DeviceModuleGuadalupeCanyon::fnSaveAllTXDumpToCsv(int nBoardindex, std::string sInfo, std::string sFilePrefix)  //for save all Tx memory during power on
{
	//	Sleep(200);  //为了验证是不是太快了导致B4 的值读取不正确

	BOOL status = TRUE;
	BOOL is16Bit = FALSE;
	static const int TxRegSize = (0xFF + 1);         //0x00~0xFF
	uint8_t	TxRegNVMData[TxRegSize];
	std::string TxNVMStringAddress;
	std::string TxNVMStringData;
	replace(sInfo, "_", " ");
	replace(sInfo, ".raw", "");

	std::vector<std::string> m_header, m_context;

	memset(TxRegNVMData, 0, sizeof(TxRegNVMData[0])*TxRegSize);
	fnReadTxNVM(nBoardindex % 4, TxRegNVMData, TxRegSize);
	NVMArrayToStringComa(is16Bit, "0x00", TxRegNVMData, TxRegSize, TxNVMStringAddress, TxNVMStringData);

	//getTx ID;
	char SN[9] = { 0 };
	if (TxRegNVMData[11] != NULL)
	{
		sprintf(SN, "0x%02X%02X%02X%02X", TxRegNVMData[14], TxRegNVMData[13], TxRegNVMData[12], TxRegNVMData[11]);
	}
	std::string tempSN = SN;

	//1231
	char strB4[9] = { 0 };
	if (TxRegNVMData[180] != NULL)
	{
		sprintf(strB4, "0x%02X", TxRegNVMData[180]);
	}
	std::string tempstrB4 = strB4;
	if (tempstrB4 == "0x05" || tempstrB4 == "0x04")
	{
		status = FALSE;

		//CString str;
		//str.Format(_T("DUT Failed:%s Socket:%d ", tempstrB4.c_str(), (nBoardIndex%4+1) ) );
		/*CDlgPopResult::fnDomodalResult(str, PopResultStatusFail);*/
	}

	// get SN
	std::string output_sn;
	uint16_t barcode_start = 0x1AF;
	uint16_t barcode_end = 0x1B9;
	uint16_t plusOne = 0x001;
	char strSlave[] = { "BANFF_RX_SLAVE_ADDRESS" };
	std::string input_hex;
	uint16_t Nvm_Start = 0x310;
	for (size_t i = 0; i < barcode_end + 1 - barcode_start; i++) //已经poweroff 470ms
	{
		uint16_t yy = Nvm_Start + barcode_start + i;
		//string data = I2cRead_8bit(nBoardIndex%4, BANFF_RX_SLAVE_ADDRESS, yy);
		unsigned char readVal = 0;
		bool ret = ReadByte(nBoardindex % 4, true, yy, &readVal);
		//if (ret == false)
		//{
		//	break;
		//}
		std::string value;
		value = Format("%02X", readVal);
		input_hex = input_hex + value;
		//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read NVM Dump for Barcode:%s", input_hex.c_str());
	}
	NVM2SN(input_hex, output_sn);

	//std::string csvPath = Format("%s\\%s_TxNVM_Dump.csv", g_pOP->getLogPath().toLatin1().data(), sFilePrefix.c_str());
	std::string csvPath = Format("D:\\%s_TxNVM_Dump.csv", sFilePrefix.c_str());
	//if (g_pOP->fnSaveAllTXDumpToCsvHeader == false)
	//if (!IsExistFile(csvPath))
	if (!exists_file(csvPath))
	{
		//g_pOP->fnSaveAllTXDumpToCsvHeader = true;

		m_header.push_back("SocketIndex");
		m_header.push_back("Time");
		m_header.push_back("Position");
		m_header.push_back("TxASCID");
		m_header.push_back("DUTSN");
		m_header.push_back(TxNVMStringAddress);

		add_csv_file_context(csvPath, vec_to_list(m_header));
	}

	m_context.push_back(std::to_string(nBoardindex + 1));
	CTime time = CTime::GetCurrentTime();
	//QString timestamp = dateTime.toString("yyyyMMdd_hh-mm-ss");
	char buf[64];
	sprintf(buf,"yyyyMMdd_hh-mm-ss.zzz",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
	//m_context.push_back(CFormatTime::fnGetCurrentDateTime().toStdString());
	m_context.push_back(buf);
	m_context.push_back(sInfo);
	m_context.push_back(tempSN);
	m_context.push_back(output_sn);
	m_context.push_back(TxNVMStringData);

	//EnterCriticalSection(&m_fnSaveAllTXDumpToCsvSync);
	add_csv_file_context(csvPath, vec_to_list(m_context));
	//LeaveCriticalSection(&m_fnSaveAllTXDumpToCsvSync);

	//WriteCSV_NVM(PrefixName, TxNVMStringAddress, TxNVMStringData);

	return status;
}

int DeviceModuleGuadalupeCanyon::fnSaveSimpleTXDumpToCsv(int nBoardindex, std::string sInfo, std::string sFilePrefix)  //for save all Tx memory during power on
{
	////	Sleep(200);  //为了验证是不是太快了导致B4 的值读取不正确

	//int status = 1;
	////BOOL is16Bit = FALSE;
	////static const int TxRegSize = (0xFF + 1);         //0x00~0xFF
	////uint8_t	TxRegNVMData[TxRegSize];
	////string TxNVMStringAddress;
	////string TxNVMStringData;
	//replace(sInfo, "_", " ");
	//replace(sInfo, ".raw", "");

	//std::vector<std::string> m_header, m_context;

	///*memset(TxRegNVMData, 0, sizeof(TxRegNVMData[0])*TxRegSize);
	//fnReadTxNVM(nBoardindex % 4, TxRegNVMData, TxRegSize);
	//NVMArrayToStringComa(is16Bit, "0x00", TxRegNVMData, TxRegSize, TxNVMStringAddress, TxNVMStringData);
	//
	////getTx ID;
	//char SN[9] = { 0 };
	//if (TxRegNVMData[11] != NULL)
	//{
	//	sprintf(SN, "0x%02X%02X%02X%02X", TxRegNVMData[14], TxRegNVMData[13], TxRegNVMData[12], TxRegNVMData[11]);
	//}
	//string tempSN = SN;

	////1231
	//char strB4[9] = { 0 };
	//if (TxRegNVMData[180] != NULL)
	//{
	//	sprintf(strB4, "0x%02X", TxRegNVMData[180]);
	//}
	//string tempstrB4 = strB4;
	//if (tempstrB4 == "0x05" || tempstrB4 == "0x04")
	//{
	//	status = FALSE;

	//	//CString str;
	//	//str.Format(_T("DUT Failed:%s Socket:%d ", tempstrB4.c_str(), (nBoardIndex%4+1) ) );
	//	
	//}

	//// get SN
	//string output_sn;
	//uint16_t barcode_start = 0x1AF;
	//uint16_t barcode_end = 0x1B9;
	//uint16_t plusOne = 0x001;
	//char strSlave[] = { "BANFF_RX_SLAVE_ADDRESS" };
	//string input_hex;
	//uint16_t Nvm_Start = 0x310;
	//for (size_t i = 0; i < barcode_end + 1 - barcode_start; i++)
	//{
	//	uint16_t yy = Nvm_Start + barcode_start + i;
	//	//string data = I2cRead_8bit(nBoardIndex%4, BANFF_RX_SLAVE_ADDRESS, yy);
	//	unsigned char readVal = 0;
	//	ReadByte(nBoardindex % 4, true, yy, &readVal);
	//	string value;
	//	value = Format("%02X", readVal);
	//	input_hex = input_hex + value;
	//	//g_pOP->LogDebug(nBoardindex,__FUNCTION__, "Read NVM Dump for Barcode:%s", input_hex.c_str());
	//}
	//NVM2SN(input_hex, output_sn);*/

	////barcode
	//std::string sBarcode;
	//fnReadingBarCodeSN(nBoardindex, sBarcode);

	////TxASIC ID
	//std::string txValue = "0x";
	//std::vector<unsigned char> readBuffer;
	//bool ret = Read_Tx_ASIC_ID(nBoardindex, readBuffer);
	//int size = readBuffer.size();
	//if (size > 0)
	//{
	//	for (size_t i = 0; i < size; i++)
	//	{
	//		unsigned char buf = readBuffer.at(i);
	//		txValue = Format("%s%02X", txValue.c_str(), buf);
	//	}
	//}

	//BYTE bySlave = BANFF_TX_SLAVE_ADDRESS;
	//unsigned char uData[10] = { 0 };
	//unsigned short addr1 = 0x72;
	//if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x72, 1, &uData[0]) == FALSE)
	//{
	//	//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x72);
	//	return FALSE;
	//}
	//if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x73, 1, &uData[1]) == FALSE)
	//{
	//	//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x73);
	//	return FALSE;
	//}
	//if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x74, 1, &uData[2]) == FALSE)
	//{
	//	//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x74);
	//	return FALSE;
	//}
	//if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x75, 1, &uData[4]) == FALSE)
	//{
	//	//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x75);
	//	return FALSE;
	//}
	//if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x76, 1, &uData[5]) == FALSE)
	//{
	//	//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x76);
	//	return FALSE;
	//}
	//if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x77, 1, &uData[6]) == FALSE)
	//{
	//	//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x77);
	//	return FALSE;
	//}
	//std::string value7;
	//for (int i = 0; i < 6; i++)
	//{
	//	char tempChar = uData[i];
	//	if (i == 0)
	//	{
	//		value7 = Format("0x%02X", tempChar);
	//	}
	//	else
	//	{
	//		value7 = Format("%s,0x%02X", value7.c_str(), tempChar);
	//	}
	//	uData[i] = 0;
	//}

	//if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x54, 1, &uData[0]) == FALSE)
	//{
	//	//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x54);
	//	return FALSE;
	//}
	//if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x55, 1, &uData[1]) == FALSE)
	//{
	//	//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x55);
	//	return FALSE;
	//}
	//if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x56, 1, &uData[2]) == FALSE)
	//{
	//	//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x56);
	//	return FALSE;
	//}
	//if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0x57, 1, &uData[4]) == FALSE)
	//{
	//	//g_pOP->LogError(nBoardindex,__FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0x57);
	//	return FALSE;
	//}
	//std::string value5;
	//for (int i = 0; i < 4; i++)
	//{
	//	char tempChar = uData[i];
	//	if (i == 0)
	//	{
	//		value5 = Format("0x%02X", tempChar);
	//	}
	//	else
	//	{
	//		value5 = Format("%s,0x%02X", value5.c_str(), tempChar);
	//	}
	//	uData[i] = 0;
	//}

	//std::string sB4Value;
	//for (size_t i = 0; i < 10; i++)
	//{
	//	unsigned char uDataB4[4] = { 0 };
	//	if (PCI_I2C_SYS_Read(nBoardindex % 4, CH0, bySlave << 1, 1, 0xB4, 1, uDataB4) == FALSE)
	//	{
	//		//g_pOP->LogError(nBoardindex, __FUNCTION__, "ERROR,[CCanyon_Banff:fnCheckRegValue], Read Error RDBYTE: 0x%02x", 0xB4);
	//		return FALSE;
	//	}
	//	sB4Value = Format("0x%02X", uDataB4[0]);
	//	if (uDataB4[0] == 3)
	//	{
	//		break;
	//	}
	//	Sleep(5);
	//}
	//

	//if (sB4Value == "0x04" || sB4Value == "0x05" || sB4Value == "0x02" )
	//{
	//	status = -1;
	//	//g_pOP->LogError(nBoardindex, __FUNCTION__, "DUT failed, value of 0xB4:%s", sB4Value.c_str());
	//	//MessageBoxManage::Instance()->PostMessageBox("", QString("DUT FAILED! ,Socket:%1 .Value of 0xB4:%2").arg(nBoardindex + 1).arg(sB4Value.c_str()), 0);
	//}

	//std::string sAddr5 = "0x54,0x55,0x56,0x57";
	//std::string sAddr7 = "0x72,0x73,0x74,0x75,0x76,0x77";

	//std::string csvPath = Format("%s\\%s_TxNVM_Dump_Simple.csv", g_pOP->getLogPath().toLatin1().data(), sFilePrefix.c_str());
	////if (g_pOP->fnSaveAllTXDumpToCsvHeader == false)
	//if (!IsExistFile(csvPath))
	//{
	//	g_pOP->fnSaveAllTXDumpToCsvHeader = true;

	//	m_header.push_back("SocketIndex");
	//	m_header.push_back("Time");
	//	m_header.push_back("Position");
	//	m_header.push_back("TxASCID");
	//	m_header.push_back("DUTSN");
	//	m_header.push_back(sAddr5);
	//	m_header.push_back(sAddr7);
	//	m_header.push_back("0xB4");

	//	add_csv_file_context(csvPath, vec_to_list(m_header));
	//}

	//m_context.push_back(to_string(nBoardindex + 1));
	//m_context.push_back(CFormatTime::fnGetCurrentDateTime().toStdString());
	//m_context.push_back(sInfo);
	//m_context.push_back(txValue);
	//m_context.push_back(sBarcode);
	//m_context.push_back(value5);
	//m_context.push_back(value7);
	//m_context.push_back(sB4Value);

	////EnterCriticalSection(&m_fnSaveAllTXDumpToCsvSync);
	//add_csv_file_context(csvPath, vec_to_list(m_context));
	////LeaveCriticalSection(&m_fnSaveAllTXDumpToCsvSync);

	////WriteCSV_NVM(PrefixName, TxNVMStringAddress, TxNVMStringData);

	//return status;
}

BOOL DeviceModuleGuadalupeCanyon::SaveToRawImg(const char* strFilename, unsigned char* pBuffer, int sizeX, int sizeY)
{
	FILE* pf = fopen(strFilename, "wb");
	if (pf == NULL)		return FALSE;

	fwrite(pBuffer, sizeof(unsigned char), sizeX*sizeY, pf);
	fclose(pf);
	return TRUE;
}

BOOL DeviceModuleGuadalupeCanyon::SaveToRawImg(const char* strFilename, unsigned short* pBuffer, int sizeX, int sizeY)
{
	FILE* pf = fopen(strFilename, "wb");
	if (pf == NULL)		return FALSE;

	fwrite(pBuffer, sizeof(unsigned short), sizeX*sizeY, pf);
	fclose(pf);
	return TRUE;
}

void	DeviceModuleGuadalupeCanyon::Make10BitMode(unsigned char* pImage, WORD* pDest, unsigned int nWidth, unsigned int nHeight)
{
	unsigned int i, j;
	unsigned int nByteWidth = ALIGNED_SIZE(((nWidth * 5) >> 2), 3);
	unsigned int nDst, nSrc;
	for (i = 0; i < nHeight; i++) {
		for (j = 0; j < nWidth; j += 4) {
			//LSB bit swap, so fix this bug - 2013. 10/01 OHSK
			nDst = i * nWidth + j;
			nSrc = i * nByteWidth + ((j * 5) >> 2);
			pDest[nDst + 0] = (WORD)((pImage[nSrc + 0] << 2) + (pImage[nSrc + 4] & 0x03));
			pDest[nDst + 1] = (WORD)((pImage[nSrc + 1] << 2) + ((pImage[nSrc + 4] & 0x0C) >> 2));
			pDest[nDst + 2] = (WORD)((pImage[nSrc + 2] << 2) + ((pImage[nSrc + 4] & 0x30) >> 4));
			pDest[nDst + 3] = (WORD)((pImage[nSrc + 3] << 2) + ((pImage[nSrc + 4] & 0xC0) >> 6));

			//pDest[i*nWidth + j + 0] = (WORD)((pImage[i*nByteWidth + j * 5 / 4 + 0] << 2) + (pImage[i*nByteWidth + j * 5 / 4 + 4] & 0x03));
			//pDest[i*nWidth + j + 1] = (WORD)((pImage[i*nByteWidth + j * 5 / 4 + 1] << 2) + ((pImage[i*nByteWidth + j * 5 / 4 + 4] & 0x0C) >> 2));
			//pDest[i*nWidth + j + 2] = (WORD)((pImage[i*nByteWidth + j * 5 / 4 + 2] << 2) + ((pImage[i*nByteWidth + j * 5 / 4 + 4] & 0x30) >> 4));
			//pDest[i*nWidth + j + 3] = (WORD)((pImage[i*nByteWidth + j * 5 / 4 + 3] << 2) + ((pImage[i*nByteWidth + j * 5 / 4 + 4] & 0xC0) >> 6));
		}
	}
}