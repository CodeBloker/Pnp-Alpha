#pragma once
#ifndef _JINISETTINGS_
#define _JINISETTINGS_
#include "JupCore_export.h"
#include "Base/JupGlobal.h"

#include "PluginBase/JupTextData.h"

class JIniSettingsPrivate;

class JUPCORE_EXPORT JIniSettings : public JupTextData
{
	JUP_DECLARE_PRIVATE(JIniSettings)
public:
    JIniSettings(const std::string& path = "");
	JIniSettings(const JIniSettings &) = delete;
	JIniSettings &operator=(const JIniSettings &) = delete;
    ~JIniSettings();

    // 加载ini文件
    bool Loadfile(const std::string& path);
    // 保存ini文件
	bool SaveFile();
    bool SaveFile(const std::string& path);

	bool IsLoaded();
	bool IsQuickSave();
	void SetQuickSave(bool quick = true);

	bool IsThreadSafe();
	void SetThreadSafe(bool safe = true);

    // 设置INI数据的存储格式，参数为true时保存为UTF-8格式，否则为本地编码格式
    void SetUnicode(bool utf8 = true);
    // 是否允许一个关键字对应多个值，默认为允许；若不允许，则将最后一个值作为此关键字关联的值，其他删除
    void SetMultiKey(bool multiKey = false);

    // 获取ini文件字符串
    std::string GetIniStr();
	
	std::vector<std::string> GetAllSections();
	std::vector<std::string> GetSectionKeys(const std::string& section);
	int GetSectionKeyCount(const std::string& section);

	// 删除key，如果设置deleteSectionIfEmpty = true，最后一个key被删除则section也被删除
	bool DeleteKey(const std::string& section, const std::string& key, bool deleteSectionIfEmpty = false);
	// 删除section，整个section和其中的所有键值
	bool DeleteSection(const std::string& section);

	//通用接口
	bool ReadBool(const std::string& section, const std::string& key, bool defaultVal = false) override;
	bool WriteBool(const std::string& section, const std::string& key, bool value) override;

	int ReadInt(const std::string& section, const std::string& key, int defaultVal = 0) override;
	bool WriteInt(const std::string& section, const std::string& key, int value) override;

	double ReadDouble(const std::string& section, const std::string& key, double defaultVal = 0.0) override;
	bool WriteDouble(const std::string& section, const std::string& key, double value) override;

	std::string ReadString(const std::string& section, const std::string& key, const std::string& defaultVal = "") override;
	bool WriteString(const std::string& section, const std::string& key, const std::string& value) override;
	
	void ReadSection(const std::string& section, std::map<std::string, std::string>& configurations) override;
	int WriteSection(const std::string& section, const std::map<std::string, std::string>& configurations) override;

	void ReadSection(const std::string& section, std::vector<std::pair<std::string, std::string>>& configurations) override;
	int WriteSection(const std::string& section, const std::vector<std::pair<std::string, std::string>>& configurations) override;
};

#endif /* _JINISETTINGS_ */ 