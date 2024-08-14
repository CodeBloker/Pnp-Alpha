#pragma once

#include "PluginBase/JupError.h"

/*
	该类是平台加载错误码信息的接口，若正确定义能显示在平台系统设置的ErrorHanding页面上
*/
class JError : public JupError
{
public:
	explicit JError() {}
	~JError() {}

	/*
		枚举的变量名表示错误名，枚举的变量值表示错误码
	*/
	enum E_error
	{
		ERR_Init = 1001,
		ERR_Free = 1002,
		ERR_Run,
	};

	/*
		返回错误提示，下列是默认数据，需结合枚举E_error自定义修改并删除默认数据
		格式为<错误码, <中文提示, 英文提示>>
	*/
	std::map<int, ErrorPrompt>& ErrorPrompts() override
	{
		static std::map<int, ErrorPrompt> errorPrompts = {
			{ERR_Init,	{"ERR_Init", "初始化失败", "Initialization failed"}},
			{ERR_Free,	{"ERR_Free", "释放失败", "Free failed"}},
			{ERR_Run,	{"ERR_Run", "运行错误", "Run error"}},
		};
		return errorPrompts;
	}
};
