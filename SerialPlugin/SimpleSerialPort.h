#pragma once

#include <iostream>
#include <string>
#include <windows.h>

class SimpleSerialPort
{
public:
	SimpleSerialPort();
	~SimpleSerialPort();

	bool open(const std::string& portName, int baudRate);
	bool close();
	bool read(char* buffer, int bufferSize, int& bytesRead);
	bool write(const char* buffer, int bufferSize, int& bytesWritten);

private:
	HANDLE hComm;  // 串口句柄
	DCB dcbSerialParams;  // 串口参数
	COMMTIMEOUTS timeouts;  // 超时参数
};

