#pragma once
//#pragma execution_character_set("utf-8")

#include <map>

#define JUP_ERROR_PROMPT_CN true
#define JUP_ERROR_PROMPT_EN false

struct ErrorPrompt
{
	std::string _name;
	std::string _prompt_cn;
	std::string _prompt_en;
};

class JupError
{
public:
	JupError() {}
	virtual ~JupError() {}

	enum E_error
	{
		ERR_One = 1,
		ERR_Two,
		ERR_Three
	};

	virtual std::map<int, ErrorPrompt>& ErrorPrompts()
	{
		static std::map<int, ErrorPrompt> errorPrompts = {
			{ERR_One,	{"ERR_One", "错误一", "Error 1"}},
			{ERR_Two,	{"ERR_Two", "错误二", "Error 2"}},
			{ERR_Three,	{"ERR_Three","错误三", "Error 3"}},
		};
		return errorPrompts;
	}

	std::string GetNameByCode(int code) 
	{
		if (!ErrorPrompts().count(code))
			return "";
		return this->ErrorPrompts()[code]._name;
	}

	std::string GetPromptByCode(int code, bool isCn = JUP_ERROR_PROMPT_EN)
	{
		if (!ErrorPrompts().count(code))
			return "";
		return isCn ? this->ErrorPrompts()[code]._prompt_cn : this->ErrorPrompts()[code]._prompt_en;
	}
};
