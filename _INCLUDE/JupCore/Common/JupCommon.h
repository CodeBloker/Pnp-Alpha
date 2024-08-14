#pragma once
#ifndef _JUPCOMMON_
#define _JUPCOMMON_

#include "JupCore_export.h"

#include <vector>
#include <map>
#include <ctime>
#include <sstream>

enum class UserLevel
{
	Operator,
	Engineer,
	Administrator
};

class JUPCORE_EXPORT Jup 
{
public:
/*字符处理*/
	//StringList按char分割
	static std::vector<std::string> Split(const std::string& str, const char& delim, bool skipEmpty = false);
	
	//StringList按字符串分割
	static std::vector<std::string> Split(std::string_view str, std::string_view sep = "\n");

	//StringList拼接
	static std::string Join(const std::vector<std::string>& strList, const std::string& join);

	//替换
	static void Replace(std::string& str, const std::string& from, const std::string& to);

	//GBK编码转换为UTF-8编码，使用前要确保不带UTF-8字符
	static std::string ToUTF8String(std::string_view gbkStr);

	//UTF-8编码转换为GBK编码，使用前要确保不带GBK字符
	static std::string ToGBKString(std::string_view utf8Str);

	//格式化字符串
	template<typename... Args>
	static std::string Format(const char* format, Args... args);

	//Stream格式化字符串
	template<typename ... Args>
	static std::string FormatStream(Args&& ... args);

/*文件与目录*/
	// 计算文件大小
	static uintmax_t ComputeFileSize(const std::string& filePath);

	// 遍历文件夹找出所有文件(非递归)
	static std::vector<std::string> FindAllFile(const std::string& filePath, bool absName = true);

	// 遍历文件夹找出所有文件(递归)
	static std::vector<std::string> FindAllFileRecursive(const std::string& filePath, bool absName = true);

/*时间函数*/
	/*
	获得当前时间的时间戳
		type		时间格式
		default:	2024-05-23 16:58:02.123
		0:			2024-05-23 16:58:02
		1:			20240523
		2:			202405231658
		3:			20240523165802
		4:			2024/05/23 16.58.02
	*/
	static std::string GetLocalTime(int type = -1);
	/*
	获得输入时间的时间戳
		方法1:
		timespec ts;
		timespec_get(&ts, TIME_UTC);
		Jup::GetLocalTime(ts.tv_sec, ts.tv_nsec);
		方法2:
		time_t tv_sec = time(nullptr);
		Jup::GetLocalTime(tv_sec, 0, 1);
	*/
	static std::string GetTimeBuffer(time_t time_secs, long time_nsecs, int type = -1);
	static inline int TimeElapsedMs(timespec& start, timespec& end);
	static inline int TimeElapsed(time_t& time_start, time_t& time_end);
};

#define _GBK_(x)	((sizeof("我") == 3) ? x : Jup::ToGBKString(x))
#define _UTF8_(x)	((sizeof("我") == 4) ? x : Jup::ToUTF8String(x))

template<typename... Args>
std::string Jup::Format(const char* format, Args... args)
{
	const auto size = std::snprintf(nullptr, 0, format, args...) + 1;
	const auto buffer = std::make_unique<char[]>(size);
	std::snprintf(buffer.get(), size, format, args...);
	return std::string(buffer.get(), buffer.get() + size - 1);
}

template<typename ... Args>
std::string Jup::FormatStream(Args&& ... args)
{
	std::stringstream stream;
	char buffer[] = { (stream << args, '\0') ... };
	(void)buffer;
	return stream.str();
}

inline int Jup::TimeElapsedMs(timespec& start, timespec& end) 
{
	return static_cast<int>((end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000);
}

inline int Jup::TimeElapsed(time_t& time_start, time_t& time_end)
{
	return static_cast<int>(time_end - time_start);
}

#endif /*_JUPCOMMON_*/