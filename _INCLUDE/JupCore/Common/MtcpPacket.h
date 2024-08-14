#pragma once

#include <map>
#include <string>
#include <variant>
#include <shared_mutex>
#include "JupCore_export.h"

//MtcpTime ts; timespec_get(&ts, TIME_UTC);
using MtcpTime = timespec;

static std::string GetMtcpTimeBuffer(MtcpTime & time)
{
	tm tm_ptr;
	localtime_s(&tm_ptr, &time.tv_sec);
	char timebuff[20]{ 0 };
	strftime(timebuff, sizeof(timebuff), "%Y-%m-%d %H:%M:%S", &tm_ptr);
	return timebuff;
}

static inline int MtcpTimeElapsed(MtcpTime & start, MtcpTime & end)
{
	return static_cast<int>((end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000);
}

using REQValue = std::variant<std::string, int, double>;

class JUPCORE_EXPORT REQValueHelper
{
public:
	int toInt(const REQValue& value);
	double toDouble(const REQValue& value);
	std::string toString(const REQValue& value);
};

struct REQLine
{
	std::string index;
	std::string group;
	std::string groupinfo;
	std::string item;
	std::string starttime;
	std::string endtime;
	std::string testtime;
	std::string low;
	std::string high;
	std::string unit;
	REQValue value;
	std::string result;

	REQLine() {}
	REQLine(const std::string& group, const std::string& item, const REQValue& value = "")
		: group(group), item(item), value(value) {}

	REQLine(const std::string& group, const std::string& item, MtcpTime& start, MtcpTime& end, const REQValue& value = "")
		: group(group), item(item), value(value)
	{
		this->starttime = GetMtcpTimeBuffer(start);
		this->endtime = GetMtcpTimeBuffer(end);
		this->testtime = std::to_string(MtcpTimeElapsed(start, end));
	}
};

using REQList = std::vector<REQLine>;

class JUPCORE_EXPORT MtcpPacket
{
public:
	MtcpPacket();
	MtcpPacket(const REQList& newList);
	~MtcpPacket();

	static std::string ListToWriteStr(const REQList& list);
	static REQList GetListFromWriteStr(const std::string &str);

	int GetInt(const std::string& group, const std::string& item);
	double GetDouble(const std::string& group, const std::string& item);
	std::string GetValue(const std::string& group, const std::string& item);
	bool SetValue(const std::string& group, const std::string& item, const REQValue& value);

	void Lock();
	void Unlock();
	//在多线程中使用时，为保证线程安全，需要在适当位置使用Lock()和Unlock()
	REQLine& LineAt(const std::string& group, const std::string& item);

	//获取对应group下的所有项
	REQList GetListByOneGroup(const std::string& group);
	//根据groups的顺序获取对应group下的所有项，默认参数则按map的排序获取全部项
	REQList GetListByGroups(std::vector<std::string> groups = std::vector<std::string>());

	void Clear();

	void AddLine(const REQLine & newLine);
	void AddList(const REQList & newList);

	//获得group的个数
	int GetGroupCount();
	//获得group的数组
	std::vector<std::string> GetGroupList();

private:
	REQValue value(const std::string& group, const std::string& item);

private:
	std::shared_mutex m_mutex;
	std::map<std::string, REQList> m_reqListMap;	
};


