#pragma once
//#pragma execution_character_set("utf-8")

#include <vector>

class JupVersion
{
public:
	JupVersion() {}
	virtual ~JupVersion() {}

	virtual std::vector<std::string>& GetVersions()
	{
		static std::vector<std::string> ver = {
			"V1.0.2;"
			"1....;"
			"2....;"
			,
			"V1.0.1;"
			"1....;"
			"2....;"
		};
		return ver;
	}
};
