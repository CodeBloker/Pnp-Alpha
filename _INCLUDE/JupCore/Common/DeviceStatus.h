#pragma once
#ifndef _DEVICESTATUS_
#define _DEVICESTATUS_

#include "Base/JupGlobal.h"
#include "JupCore_export.h"
#include <Windows.h>

#define MSG_ControlCommand	50050
#define MSG_ControlStatus	50051

class JUPCORE_EXPORT DeviceStatus
{
public:
	enum ControlCommand
	{
		Stop,
		Reset,
		Start,
		Pause
	};

	enum ControlStatus
	{
		Stopping,
		Resetting,
		Idling,
		Running,
		Pausing
	};

	enum WorkStatus
	{
		DEVICE_STOP = 0,
		DEVICE_RESETTING,
		DEVICE_IDLE,
		DEVICE_RUNNING,
		DEVICE_PAUSE
	};

public:
	DeviceStatus();
	~DeviceStatus();

	WorkStatus GetWorkStatus();
	bool SetWorkStatus(WorkStatus status);

	std::string GetDescription(int status);

	static void SetControlCommandSlot(HWND hwnd);
	static HWND GetControlCommandSlot();
	static void SetControlStatusSlot(HWND hwnd);
	static HWND GetControlStatusSlot();

private:
	static WorkStatus m_workStatus;
};

#endif /* _DEVICESTATUS_ */ 