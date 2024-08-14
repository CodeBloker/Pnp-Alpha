#pragma once
#ifndef _JupLog_
#define _JupLog_

enum class JLogLevel
{
	Debug = 100,
	Info,
	Warn,
	Error
};

#include <string>

class JupLog
{
public:
	virtual void Log(JLogLevel level, const std::string& func, const std::string& str) = 0;
	virtual void LogDebug(const std::string& func, const std::string& str) = 0;
	virtual void LogInfo(const std::string& func, const std::string& str) = 0;
	virtual void LogWarn(const std::string& func, const std::string& str) = 0;
	virtual void LogError(const std::string& func, const std::string& str) = 0;
};

#endif /*_JupLog_*/