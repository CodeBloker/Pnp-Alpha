#include "SimpleSerialPort.h"

SimpleSerialPort::SimpleSerialPort()
{
	hComm = INVALID_HANDLE_VALUE;
	SecureZeroMemory(&dcbSerialParams, sizeof(DCB));
	SecureZeroMemory(&timeouts, sizeof(COMMTIMEOUTS));
}

SimpleSerialPort::~SimpleSerialPort()
{
	close();
}

bool SimpleSerialPort::open(const std::string & portName, int baudRate)
{
	hComm = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hComm == INVALID_HANDLE_VALUE) {
		std::cout << "无法打开串口!" << std::endl;
		return false;
	}

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hComm, &dcbSerialParams)) {
		std::cout << "获取串口状态失败!" << std::endl;
		close();
		return false;
	}

	dcbSerialParams.BaudRate = baudRate;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (!SetCommState(hComm, &dcbSerialParams)) {
		std::cout << "设置串口状态失败!" << std::endl;
		close();
		return false;
	}

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (!SetCommTimeouts(hComm, &timeouts)) {
		std::cout << "设置串口超时失败!" << std::endl;
		close();
		return false;
	}

	return true;
}

bool SimpleSerialPort::close()
{
	if (hComm != INVALID_HANDLE_VALUE) {
		CloseHandle(hComm);
		hComm = INVALID_HANDLE_VALUE;
	}
	return true;
}

bool SimpleSerialPort::read(char * buffer, int bufferSize, int & bytesRead)
{
	return ReadFile(hComm, buffer, bufferSize, (LPDWORD)&bytesRead, NULL);
}

bool SimpleSerialPort::write(const char * buffer, int bufferSize, int & bytesWritten)
{
	return WriteFile(hComm, buffer, bufferSize, (LPDWORD)&bytesWritten, NULL);
}
