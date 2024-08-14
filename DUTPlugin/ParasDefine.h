#pragma once
#include "Common/JupCommon.h"
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <fstream>
#include <list>
#include <shared_mutex>
#include <sstream>
#include <stdarg.h>
#include <direct.h>
#include <io.h>

typedef unsigned long ulong;

using JVariant = std::variant<int, double, std::string>;
using JVariantMap = std::map<std::string, std::variant<int, double, std::string>>;

#define SN_HEX_LENGTH 22
#define NVMSIZE 1024

// ÒÆ³ý×Ö·û´®Á½¶Ë¿Õ°×
inline std::string& trim(std::string &s)
{
	if (!s.empty())
	{
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}
	return s;
}

inline std::string Format(const char * format, ...)
{
	char buf[1024] = { 0, };
	va_list args;
	va_start(args, format);
	vsnprintf_s(buf, _countof(buf) - 1, format, args);
	va_end(args);

	return buf;
}

static std::mutex csv_mutex;
inline bool append_csv_fileold(std::string csv_path, std::string buf)
{
	if (buf.empty())
	{
		return false;
	}
	std::unique_lock<std::mutex> lock(csv_mutex);
	std::fstream out;
	int retry = 0;
	bool ret = false;
	while (ret == false && retry < 3) {
		out.open(csv_path, std::ios::app);
		ret = out.is_open();
		if (ret) {
			break;
		}
		//::MessageBox(0, "please close execl and copy data", "warn", MB_OK);
		retry++;
		if (retry == 3)
			return false;
	}
	out.write(buf.c_str(), buf.length());
	out.close();
	return true;
}

inline bool add_csv_file_context(std::string csv_pah, std::list<std::string> context_v)
{
	std::error_code error;
	std::stringstream csv_buf;
	for (auto s : context_v)
	{
		csv_buf << s << ",";
	}
	csv_buf << "\n";
	return append_csv_fileold(csv_pah, csv_buf.str());
}

inline std::list<std::string> vec_to_list(std::vector<std::string> m_vec)
{
	std::list<std::string> m_list;
	m_list.assign(m_vec.begin(), m_vec.end());
	return m_list;
}

inline bool exists_file(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

//INI 
#define FILE_VISASCRIPT_PATH							"D:\\EVMS\\ENV\\Lua\\"
#define DUT_CONFIG_FOLDER							    "D:\\EVMS\\ENV\\Ref\\"
#define STATION_INFO_INI								"D:\\EVMS\\ENV\\Station.ini"
#define CMBU_INI										"D:\\EVMS\\ENV\\Config\\CMBU_Config.ini"
#define INSPECTORINFOR_INI								"D:\\EVMS\\ENV\\Config\\InspectInfor.ini"
#define TXRegFile_INI									"D:\\EVMS\\ENV\\Config\\BA_SCREEN_INI_Tx.ini"
#define RXRegFile_INI									"D:\\EVMS\\ENV\\Ref\\Register.ini"
#define FFBLRegFile_INI									"D:\\EVMS\\ENV\\Ref\\Register_FFBL.ini"
#define SCREEN_INI										"D:\\EVMS\\ENV\\Config\\BA_EOL_INI_Tx.ini"
#define CAS_INI_FILE									"D:\\EVMS\\ENV\\Config\\1532121i1.ini"
#define CAS_CAL_FILE									"D:\\EVMS\\ENV\\Config\\1532121i1.isc"
#define ERRORCODE_INI									"D:\\EVMS\\ENV\\Config\\Error_Code.ini"  //"\\Config\\Error_Code.ini"
#define PROGRAME_README									"./Document/README.txt" //"./Document/README.txt"

#define IOCONFIG_INI									"D:\\EVMS\\ENV\\Config\\IOConfig.ini"
#define AXISCONFIG_INI									"D:\\EVMS\\ENV\\Config\\AxisConfig.ini"
#define AXISPOS_INI										"D:\\EVMS\\ENV\\Config\\AxisPos.ini"
#define LENSCALCSV_FILE									("D:\\EVMS\\ENV\\Config\\CAL file EOS66002\\CAL File-EOS66002.csv")
#define LENSCALRATIOCSV_FILE						    ("D:\\EVMS\\ENV\\Config\\CAL file EOS66002\\CAL_TS6001_ratiofile_half.csv")