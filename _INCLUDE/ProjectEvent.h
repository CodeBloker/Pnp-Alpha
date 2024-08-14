#pragma once

#include "JupExpand/JupCustomEvent.h"
#include <string>
#include <tuple>

namespace ProjectEvent {

static const char* g_HikWidget = "hikWidget";
static const char* g_DutWidget = "dutWidget";
static const char* g_IdsWidget = "IdsWidget";
static const char* g_MilWidget = "MilWidget";
static const char* g_MotionWidget = "MotionWidget";
static const char* g_CalibrationWidget = "CalibrationWidget";
static const char* g_DvpWidget = "DvpWidget";

enum E_CustomEventId {
	e_JHikEvent = JupCustomEvent::Begin + 1,
	e_JDutEvent,
	e_JIdsEvent,
	e_JMilEvent,
	e_JMilFindModelEvent,
	e_JMilFindCenterEvent,
	e_JMotionEvent,
	e_JCalibrationEvent,
	e_JDvpEvent
};

class JDvpEvent : public JupCustomEvent
{
public:
	JDvpEvent(void* ptr, int width, int height)
		: m_ptr(ptr), m_width(width), m_height(height) {}
	~JDvpEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JDvpEvent);
	}

public:
	void* m_ptr;
	int m_width;
	int m_height;
};

class JHikEvent : public JupCustomEvent
{
public:
	JHikEvent(const char* command, void* ptr)
		: m_command(command), m_ptr(ptr) {}
	~JHikEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JHikEvent);
	}

public:
	const char* m_command;
	void* m_ptr;
};

class JDutEvent : public JupCustomEvent
{
public:
	JDutEvent(const char* ptr)
		: m_ptr(ptr) {}
	~JDutEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JDutEvent);
	}

public:
	const char* m_ptr;
};

class JIdsEvent : public JupCustomEvent
{
public:
	JIdsEvent(const char* command, const char* ptr)
		: m_command(command), m_ptr(ptr) {}
	~JIdsEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JIdsEvent);
	}

public:
	const char* m_command;
	const char* m_ptr;
};

class JMilEvent : public JupCustomEvent
{
public:
	JMilEvent(std::string ptr, std::string& file_out, std::string file_mmf)
		: m_ptr(ptr), m_file_out(file_out), m_file_mmf(file_mmf) {}
	~JMilEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JMilEvent);
	}

public:
	std::string m_ptr;
	std::string& m_file_out;
	std::string m_file_mmf;
	double m_pointX = 0.0;
	double m_pointY = 0.0;
	double m_angle = 0.0;
	//const char* m_ptr;
};

class JMilFindModelEvent : public JupCustomEvent
{
public:
	JMilFindModelEvent(std::string ptr, std::string file_mmf, bool is_wait)
		: m_file(ptr), m_file_mmf(file_mmf), m_is_wait(is_wait) {}
	~JMilFindModelEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JMilFindModelEvent);
	}

public:
	std::string m_file;
	std::string m_file_out;
	std::string m_file_mmf;
	double m_pointX = 0.0;
	double m_pointY = 0.0;
	double m_angle = 0.0;
	bool m_is_wait;
};

class JMilFindCenterEvent : public JupCustomEvent
{
public:
	JMilFindCenterEvent(double x1, double y1, double x2, double y2, double x3, double y3)
		: m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_x3(x3), m_y3(y3) {}
	~JMilFindCenterEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JMilFindCenterEvent);
	}

public:
	double m_x1;
	double m_y1;
	double m_x2;
	double m_y2;
	double m_x3;
	double m_y3;
	double m_pointX = 0.0;
	double m_pointY = 0.0;
	double m_pointR = 0.0;
};

class JMotionEvent : public JupCustomEvent
{
public:
	JMotionEvent(const char* axis, double distance, double speed_ratio)
		: m_axis(axis), m_distance(distance), m_speed_ratio(speed_ratio) {}
	~JMotionEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JMotionEvent);
	}

public:
	const char* m_axis;
	double m_distance;
	double m_speed_ratio;
};

class JCalibrationEvent : public JupCustomEvent
{
public:
	JCalibrationEvent(std::string command, std::string camera, unsigned char* pData, unsigned short nWidth, unsigned short nHeight)
		: m_command(command), m_camera(camera), m_pData(pData), m_nWidth(nWidth), m_nHeight(nHeight){}
	JCalibrationEvent(std::string command, std::string camera, double point_x, double point_y)
		: m_command(command), m_camera(camera), m_point_x(point_x), m_point_y(point_y) {}
	~JCalibrationEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JCalibrationEvent);
	}

public:
	std::string m_command;
	std::string m_camera;
	unsigned char* m_pData;
	unsigned short m_nWidth;
	unsigned short m_nHeight;

	double m_point_x;
	double m_point_y;
};

}
