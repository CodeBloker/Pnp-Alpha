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
	e_JMilFindModelPnpEvent,
	e_JMilFindModelNozzleEvent,
	e_JMilFindCenterEvent,
	e_JMilFindSocketMarkCenterEvent,
	e_JMilFindSocketMarkAndB2BDistanceEvent,
	e_JMotionEvent,
	e_JCalibrationEvent,
	e_JDvpEvent,
	e_JDvpPnpCalibrationEvent,
	e_JMotionIsHomeEvent
};

class JMotionIsHomeEvent :public JupCustomEvent
{
public:
	JMotionIsHomeEvent(bool isHome)
		:isAxisHome(isHome){}
	~JMotionIsHomeEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JMotionIsHomeEvent);
	}
public:
	bool isAxisHome;
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

class JDvpPnpCalibrationEvent : public JupCustomEvent
{
public:
	JDvpPnpCalibrationEvent(std::string result_img)
		: resultImagePath(result_img) {}
	~JDvpPnpCalibrationEvent() {}
	JupCustomEvent::eType Type() const override
	{
		return static_cast<eType>(e_JDvpPnpCalibrationEvent);
	}

public:
	void* m_ptr;
	int m_width;
	int m_height;
	std::string resultImagePath;
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
	JMilEvent(std::string ptr, int options)
		: m_image_ptr(ptr), mil_options(options) {}
	~JMilEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JMilEvent);
	}

public:
	std::string m_image_ptr;
	int mil_options;
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

class JMilFindModelPnpEvent : public JupCustomEvent
{
public:
	JMilFindModelPnpEvent(std::string ptr, std::string file_mmf, std::string &file_out)
		: m_file(ptr), m_file_mmf(file_mmf), m_file_out(file_out) {}
	~JMilFindModelPnpEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JMilFindModelPnpEvent);
	}

public:
	std::string m_file;//需要传参
	std::string &m_file_out;//需要传参
	std::string m_file_mmf;//需要传参
	double m_calibrationPointX = 0.0;
	double m_calibrationPointY = 0.0;
	double m_calibrationAngle = 0.0;
	double m_actualPointX = 0.0;
	double m_actualPointY = 0.0;
	double m_actualPointAngle = 0.0;
	//bool m_is_wait;//需要传参
};

class JMilFindModelNozzleEvent : public JupCustomEvent
{
public:
	JMilFindModelNozzleEvent(std::string ptr, std::string file_mmf, std::string file2_mmf, std::string &file_out)
		: m_file(ptr), m_file_mmf(file_mmf), m_file2_mmf(file2_mmf), m_file_out(file_out) {}
	~JMilFindModelNozzleEvent(){}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JMilFindModelNozzleEvent);
	}

public:
	std::string m_file;//需要传参
	std::string &m_file_out;//需要传参
	std::string m_file_mmf,m_file2_mmf;//需要传参
	double m_calibrationPointX = 0.0;
	double m_calibrationPointY = 0.0;
	double m_calibrationAngle = 0.0;
	double m_actualPointX = 0.0;
	double m_actualPointY = 0.0;
	double m_actualPointAngle = 0.0;
};

class JMilFindCenterEvent : public JupCustomEvent
{
public:
	JMilFindCenterEvent(std::string ptr, std::string file_mmf, std::string &file_out)
		: m_file(ptr), m_file_mmf(file_mmf), m_file_out(file_out) {}
	~JMilFindCenterEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JMilFindCenterEvent);
	}

public:
	std::string m_file;
	std::string &m_file_out;
	std::string m_file_mmf;
	double m_event_deltaX, m_event_deltaY;
};

class JMilFindSocketMarkCenterEvent : public JupCustomEvent
{
public:
	JMilFindSocketMarkCenterEvent(std::string ptr, std::string file_mmf, std::string &file_out)
		: m_file(ptr), m_file_mmf(file_mmf), m_file_out(file_out) {}
	~JMilFindSocketMarkCenterEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JMilFindSocketMarkCenterEvent);
	}

public:
	std::string m_file;
	std::string &m_file_out;
	std::string m_file_mmf;
	float m_event_deltaX, m_event_deltaY;

};

class JMilFindSocketMarkAndB2BDistanceEvent : public JupCustomEvent
{
public:
	JMilFindSocketMarkAndB2BDistanceEvent(std::string ptr, std::string file_mmf, std::string file_circle_mmf, std::string &file_out)
	: m_file(ptr), m_file_mmf(file_mmf), m_file_circle_mmf(file_circle_mmf), m_file_out(file_out) {}
	~JMilFindSocketMarkAndB2BDistanceEvent() {}
	JupCustomEvent::eType Type() const override {
		return static_cast<eType>(e_JMilFindSocketMarkAndB2BDistanceEvent);
	}
public:
	std::string m_file;
	std::string &m_file_out;
	std::string m_file_mmf,m_file_circle_mmf;
	float m_SocketAngle,m_distance;
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
