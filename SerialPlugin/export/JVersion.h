#pragma once

#include "PluginBase/JupVersion.h"

/*
	该类是平台加载版本信息的接口，若正确定义能显示在平台的系统设置窗口的版本页面上
*/
class JVersion : public JupVersion
{
public:
	JVersion() {}
	virtual ~JVersion() {}

	/*
		版本信息如下所示，规则如下：
		1.每条版本信息通过逗号分开
		2.最新的版本信息往头部插入
		3.分号的作用是在显示界面上换行
		4.每条版本信息的第一行添加版本号，后面的行添加更新内容
	*/
	std::vector<std::string>& GetVersions() override
	{
		static std::vector<std::string> ver = {
			"V1.0.3;"
			"1.增加DuiLib图形接口;"
			,
			"V1.0.2;"
			"1.增加版本控制接口;"
			"2.增加ErrorCode控制;"
			,
			"V1.0.1;"
			"1.创建插件;"
			"2.模板示例;"
		};
		return ver;
	}
};