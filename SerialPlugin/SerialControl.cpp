#include "SerialControl.h"
#include "JupCore.h"

SerialControl::SerialControl()
{
}

SerialControl::~SerialControl()
{
}

SerialControl *& SerialControl::GetInstance()
{
	if (m_SingleInstance == nullptr) {
		std::lock_guard<std::mutex> lock(m_Mutex);
		if (m_SingleInstance == nullptr) {
			m_SingleInstance = new (std::nothrow) SerialControl{};
		}
	}
	return m_SingleInstance;
}

bool SerialControl::openSerialPort(std::string port_name)
{ 
	if (port_name == "COM6")
		return OpenLightSource();
	else if (port_name == "\\\\.\\COM10")
		return OpenTempSensor();
	else if (port_name == "COM8")
		return OpenTempSensor2();
	else if (port_name == "COM9")
		return OpenHeighSensor1();
	return false;
}

bool SerialControl::CloseSerialPort(std::string port_name)
{
	if (port_name == "COM6")
		return CloseLightSource();
	else if (port_name == "\\\\.\\COM10")
		return CloseTempSensor();
	else if (port_name == "COM8")
		return CloseTempSensor2();
	else if (port_name == "COM9")
		return CloseHeighSensor1();
	return false;
}

bool SerialControl::OpenLightSource()
{
	LightComSetting Com;
	bool ret = mLightSerial.OpenDevice(Com.portName, Com.ulBaudRate, Com.ucByteSize, Com.ucParity, Com.ucStopBit, Com.ulHandshake);
	return ret;
}

bool SerialControl::CloseLightSource()
{
	bool ret = mLightSerial.CloseDevice();
	return ret;
}

bool SerialControl::IsLightSourceOpen()
{
	return mLightSerial.IsOpened();
}

bool SerialControl::OpenHikCamera1Light()
{
	char buf[20] = "SA0200#SB0000#";
	int ret = mLightSerial.Send(buf, sizeof(buf));
	return ret;
}

bool SerialControl::OpenHikCamera2Light()
{
	char buf[20] = "SA0000#SB0200#";
	int ret = mLightSerial.Send(buf, sizeof(buf));
	return ret;
}

bool SerialControl::OpenAllLight()
{
	char buf[20] = "SA0200#SB0200#";
	int ret = mLightSerial.Send(buf, sizeof(buf));
	if (ret == 0)
		return true;
	else
		return false;
}

bool SerialControl::CloseAllLight()
{
	char buf[20] = "SA0000#SB0000#";
	int ret = mLightSerial.Send(buf, sizeof(buf));
	if (ret == 0)
		return true;
	else
		return false;
}

bool SerialControl::OpenTempSensor()
{
	//TempComSetting Com;
	////bool ret = mTempSerial.OpenDevice(Com.portName, Com.ulBaudRate, Com.ucByteSize, Com.ucParity, Com.ucStopBit, Com.ulHandshake);
	//bool ret = mTempSerial.open(Com.portName, Com.ulBaudRate);
	//return ret;
	KeyenceHeighComSetting Com;
	bool ret = m_port.open(Com.portName.c_str(), Com.ulBaudRate, Com.ucParity, Com.ucByteSize, Com.ucStopBit);
	return ret;
}

bool SerialControl::CloseTempSensor()
{
	//bool ret = mTempSerial.CloseDevice();
	bool ret = mTempSerial.close();
	return ret;
}

bool SerialControl::IsTempSensorOpen()
{
	return true;
	//return mTempSerial.IsOpened();
}

std::string SerialControl::ReadTemp()
{
	//char buf[] = { 0x01, 0x04, 0x00, 0x00, 0x00, 0x02, 0x71, 0xCB };
	////int ret = mTempSerial.Send(buf, sizeof(buf));
	//int bytesWritten;
	//mTempSerial.write(buf, sizeof(buf), bytesWritten);
	//Sleep(50);
	//char bufResult[64] = { 0 };
	////ret = mTempSerial.Recv(bufResult, sizeof(bufResult));
	//int bytesRead;
	//mTempSerial.read(bufResult, sizeof(bufResult), bytesRead);
	////std::string strResult = ParseSerialRecv(bufResult, ret);
	//std::string strResult = ParseTempSerialRecv(bufResult, bytesRead);
	//return strResult;

	char buf[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B };
	m_port.send(buf, sizeof(buf));
	Sleep(50);
	char bufResult[64] = { 0 };
	int bytesRead;
	m_port.receive(bufResult, sizeof(bufResult));
	//std::string strResult = ParseTemp3SerialRecv(bufResult, bytesRead);

	return "";
}

bool SerialControl::OpenTempSensor2()
{
	Temp2ComSetting Com;
	bool ret = mTempSerial2.open(Com.portName, Com.ulBaudRate);
	return ret;
}

bool SerialControl::CloseTempSensor2()
{
	bool ret = mTempSerial2.close();
	return ret;
}

bool SerialControl::IsTempSensorOpen2()
{
	return true;
}

std::string SerialControl::ReadTemp2()
{
	char buf[] = { 0x01, 0x04, 0x00, 0x00, 0x00, 0x02, 0x71, 0xCB };
	int bytesWritten;
	mTempSerial2.write(buf, sizeof(buf), bytesWritten);
	Sleep(50);
	char bufResult[64] = { 0 };
	int bytesRead;
	mTempSerial2.read(bufResult, sizeof(bufResult), bytesRead);
	std::string strResult = ParseTemp2SerialRecv(bufResult, bytesRead);
	return strResult;
}

bool SerialControl::OpenHeighSensor1()
{
	HeighComSetting1 Com;
	bool ret = mHeighSerial1.open(Com.portName, Com.ulBaudRate);
	return ret;
}

bool SerialControl::CloseHeighSensor1()
{
	bool ret = mHeighSerial1.close();
	return ret;
}

bool SerialControl::IsHeighSensorOpen()
{
	return true;
	//return mHeighSerial.IsOpened();
}

std::string SerialControl::ReadHeigh1()
{
	char buf[] = "SR,01,519\r\n";
	int bytesWritten;
	mHeighSerial1.write(buf, sizeof(buf), bytesWritten);
	Sleep(50);
	char bufResult[64] = { 0 };
	int bytesRead;
	mHeighSerial1.read(bufResult, sizeof(bufResult), bytesRead);
	std::string strResult = ParseHeighSerialRecv(bufResult);
	return strResult;
}

bool SerialControl::OpenHeighSensor2()
{
	HeighComSetting2 Com;
	bool ret = mHeighSerial2.open(Com.portName, Com.ulBaudRate);
	return ret;
}

bool SerialControl::CloseHeighSensor2()
{
	bool ret = mHeighSerial2.close();
	return ret;
}

std::string SerialControl::ReadHeigh2()
{
	char buf[] = "SR,01,519\r\n";
	int bytesWritten;
	mHeighSerial2.write(buf, sizeof(buf), bytesWritten);
	Sleep(50);
	char bufResult[64] = { 0 };
	int bytesRead;
	mHeighSerial2.read(bufResult, sizeof(bufResult), bytesRead);
	std::string strResult = ParseHeighSerialRecv(bufResult);
	return strResult;
}

bool SerialControl::OpenHeighSensor3()
{
	HeighComSetting3 Com;
	bool ret = mHeighSerial3.open(Com.portName, Com.ulBaudRate);
	return ret;
}

bool SerialControl::CloseHeighSensor3()
{
	bool ret = mHeighSerial3.close();
	return ret;
}

std::string SerialControl::ReadHeigh3()
{
	char buf[] = "SR,01,519\r\n";
	int bytesWritten;
	mHeighSerial3.write(buf, sizeof(buf), bytesWritten);
	Sleep(50);
	char bufResult[64] = { 0 };
	int bytesRead;
	mHeighSerial3.read(bufResult, sizeof(bufResult), bytesRead);
	std::string strResult = ParseHeighSerialRecv(bufResult);
	return strResult;
}

bool SerialControl::OpenKeyenceHeighSensor()
{
	KeyenceHeighComSetting Com;
	bool ret = mKeyenceHeighSerial.open(Com.portName, Com.ulBaudRate);
	return ret;
}

bool SerialControl::CloseKeyenceHeighSensor()
{
	bool ret = mKeyenceHeighSerial.close();
	return ret;
}

std::string SerialControl::ReadKeyenceHeigh()
{
	char buf[] = "M1\r";
	int bytesWritten;
	mKeyenceHeighSerial.write(buf, sizeof(buf), bytesWritten);
	Sleep(50);
	char bufResult[64] = { 0 };
	int bytesRead;
	mKeyenceHeighSerial.read(bufResult, sizeof(bufResult), bytesRead);
	std::string strResult = ParseKeyenceHeighSerialRecv(bufResult);
	return strResult;
}

std::string SerialControl::ParseTempSerialRecv(char * buf, int len)
{
	if (len <= 0)
	{
		return std::string();
	}

	unsigned short tmp = 0;
	char* p = (char*)&tmp;
	*p = buf[4];
	*(++p) = buf[3];
	
	double decimalTemp = (tmp - 4000) / 100.0; // 温度转换公式
	std::string cur_temp = std::to_string(decimalTemp);
	
	return cur_temp;
}

std::string SerialControl::ParseTemp2SerialRecv(char * buf, int len)
{
	if (len <= 0)
	{
		return std::string();
	}

	unsigned short tmp = 0;
	char* p = (char*)&tmp;
	*p = buf[4];
	*(++p) = buf[3];

	double decimalTemp = tmp / 10.0; // 温度转换公式
	std::string cur_temp = std::to_string(decimalTemp);
	return cur_temp;
}

std::string SerialControl::ParseHeighSerialRecv(const std::string& buf)
{
	if (buf.empty())
	{
		return buf;
	}
	std::string heigh = buf.substr(10,7);
	return heigh;
}

std::string SerialControl::ParseKeyenceHeighSerialRecv(const std::string & buf)
{
	std::string str = buf;
	auto lst = Jup::Split(str, ",");
	if (lst.size() < 2)
	{
		return std::string();
	}
	std::string result = lst.at(1);
	Jup::Replace(result, "\r", "");
	return result;
}
