#pragma once
#ifndef _JupTextData_
#define _JupTextData_

#include <string>
#include <vector>
#include <map>

class JupTextData
{
public:
	virtual bool ReadBool(const std::string& section, const std::string& key, bool defaultVal = false) = 0;
	virtual bool WriteBool(const std::string& section, const std::string& key, bool value) = 0;

	virtual int ReadInt(const std::string& section, const std::string& key, int defaultVal = 0) = 0;
	virtual bool WriteInt(const std::string& section, const std::string& key, int value) = 0;

	virtual double ReadDouble(const std::string& section, const std::string& key, double defaultVal = 0.0f) = 0;
	virtual bool WriteDouble(const std::string& section, const std::string& key, double value) = 0;

	virtual std::string ReadString(const std::string& section, const std::string& key, const std::string& defaultVal = "") = 0;
	virtual bool WriteString(const std::string& section, const std::string& key, const std::string& value) = 0;

	virtual void ReadSection(const std::string& section, std::map<std::string, std::string>& configurations) = 0;
	virtual int WriteSection(const std::string& section, const std::map<std::string, std::string>& configurations) = 0;

	virtual void ReadSection(const std::string& section, std::vector<std::pair<std::string, std::string>>& configurations) = 0;
	virtual int WriteSection(const std::string& section, const std::vector<std::pair<std::string, std::string>>& configurations) = 0;
};

#endif /*_JupTextData_*/