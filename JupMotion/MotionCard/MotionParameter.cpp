#include "MotionParameter.h"

#pragma execution_character_set("utf-8")

#include <comutil.h>  
#pragma comment(lib, "comsuppw.lib")

std::string ws2s(const std::wstring& ws)
{
	_bstr_t t = ws.c_str();
	char* pchar = (char*)t;
	std::string result = pchar;
	return result;
}

std::wstring s2ws(const std::string& s)
{
	_bstr_t t = s.c_str();
	wchar_t* pwchar = (wchar_t*)t;
	std::wstring result = pwchar;
	return result;
}

wchar_t* s2wchar(const std::string& s)
{
	_bstr_t t = s.c_str();
	wchar_t* pwchar = (wchar_t*)t;
	return pwchar;
}

std::string CoverToChineseStr(std::string_view str_UTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, str_UTF8.data(), -1, NULL, 0);
	wchar_t* wsz_GBK = new wchar_t[len + 1];
	memset(wsz_GBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, str_UTF8.data(), -1, wsz_GBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wsz_GBK, -1, NULL, 0, NULL, NULL);
	char* sz_GBK = new char[len + 1];
	memset(sz_GBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wsz_GBK, -1, sz_GBK, len, NULL, NULL);
	std::string str_temp(sz_GBK);
	if (wsz_GBK) delete[] wsz_GBK;
	if (sz_GBK) delete[] sz_GBK;
	return str_temp;
}

char* UnicodeToUtf8(const wchar_t* unicode)
{
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = (char*)malloc(len + 1);
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
	return szUtf8;
}

std::string string_To_UTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

MotionParameter::MotionParameter()
{
	int result = sqlite3_open("./Motion/motioncard.db", &m_db);
	if (result == SQLITE_OK)
	{
		result = LoadParameterFromDB();
	}
	else
	{
	}
}

MotionParameter::~MotionParameter()
{
	// 清空数据结构
	std::map<std::string, MotionAxis*>::iterator iter_axis = m_axises.begin();
	while (iter_axis != m_axises.end())
	{
		delete iter_axis->second;
		iter_axis++;
	}
	m_axises.clear();
	m_axisList.clear();

	std::map<std::string, std::map<std::string, AxisPosition*>>::iterator iter_pos = m_poses.begin();
	while (iter_pos != m_poses.end())
	{
		auto data = iter_pos->second;
		std::map<std::string, AxisPosition*>::iterator iter_datas = data.begin();
		while (iter_datas != data.end())
		{
			delete iter_datas->second;
			iter_datas++;
		}
		iter_pos++;
	}
	m_poses.clear();

	std::map<std::string, MotionIO*>::iterator iter_out = m_outputs.begin();
	while (iter_out != m_outputs.end())
	{
		delete iter_out->second;
		iter_out++;
	}
	m_outputs.clear();

	std::map<std::string, MotionIO*>::iterator iter_in = m_inputs.begin();
	while (iter_in != m_inputs.end())
	{
		delete iter_in->second;
		iter_in++;
	}
	m_inputs.clear();
}

bool MotionParameter::LoadParameterFromDB()
{
	bool ret1 = LoadAxisInfos();
	bool ret2 = LoadPositionInfos();
	bool ret3 = LoadOutputInfos();
	bool ret4 = LoadInputInfos();
	if (ret1 && ret2 && ret3 && ret4)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MotionParameter::LoadAxisInfos()
{
	// 清空数据结构
	std::map<std::string, MotionAxis*>::iterator iter = m_axises.begin();
	while (iter != m_axises.end())
	{
		delete iter->second;
		iter++;
	}
	m_axises.clear();
	m_axisList.clear();
	// 查询数据
	std::string cmd = "select AxisID,axisName,axisNameCn,motorType,cardType,cardNum,axisNum,minVel,maxVel,accVel,decVel,stopVel,sPara,allowErrorPos,equiv,lead,homeMode,homeDir,homeMinVel,homeMaxVel,homeAccVel,homeDecVel,homeOffsetPos,homeCurve,homeEZA,msTimeout,useDelay,useLimit,positiveLimit,negativeLimit from TblAxis order by AxisID";
	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(m_db, cmd.c_str(), -1, &statement, nullptr) == SQLITE_OK) 
	{
		MotionAxis *axis;
		// 遍历结果集
		while (sqlite3_step(statement) == SQLITE_ROW) 
		{
			axis = new MotionAxis();
			axis->axisID = sqlite3_column_int(statement, 0);
			std::string axisName = CoverToChineseStr(std::string_view(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1))));
			axis->axisName = axisName;
			axis->axisNameCn = CoverToChineseStr(std::string_view(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2))));
			axis->motorType = CoverToChineseStr(std::string_view(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3))));
			axis->cardType = CoverToChineseStr(std::string_view(reinterpret_cast<const char*>(sqlite3_column_text(statement, 4))));
			axis->cardNum = sqlite3_column_int(statement, 5);
			axis->axisNum = sqlite3_column_int(statement, 6);
			axis->minVel = sqlite3_column_double(statement, 7);
			axis->maxVel = sqlite3_column_double(statement, 8);
			axis->accVel = sqlite3_column_double(statement, 9);
			axis->decVel = sqlite3_column_double(statement, 10);
			axis->stopVel = sqlite3_column_double(statement, 11);
			axis->sPara = sqlite3_column_double(statement, 12);
			axis->allowErrorPos = sqlite3_column_double(statement, 13);
			axis->equiv = sqlite3_column_double(statement, 14);
			axis->lead = sqlite3_column_double(statement, 15);
			axis->homeMode = sqlite3_column_int(statement, 16);
			axis->homeDir = sqlite3_column_int(statement, 17);
			axis->homeMinVel = sqlite3_column_int(statement, 18);
			axis->homeMaxVel = sqlite3_column_int(statement, 19);
			axis->homeAccVel = sqlite3_column_int(statement, 20);
			axis->homeDecVel = sqlite3_column_double(statement, 21);
			axis->homeOffsetPos = sqlite3_column_double(statement, 22);
			axis->homeCurve = sqlite3_column_double(statement, 23);
			axis->homeEZA = sqlite3_column_double(statement, 24);
			axis->msTimeout = sqlite3_column_int(statement, 25);
			axis->useDelay = sqlite3_column_int(statement, 26);
			axis->useLimit = sqlite3_column_int(statement, 27);
			axis->positiveLimit = sqlite3_column_int(statement, 28);
			axis->negativeLimit = sqlite3_column_int(statement, 29);
			m_axises[axisName] = axis;
			m_axisList.push_back(axisName);
		}
		// 释放资源
		sqlite3_finalize(statement);
		return true;
	}
	return false;
}

bool MotionParameter::LoadPositionInfos()
{
	// 清空数据结构
	std::map<std::string, std::map<std::string, AxisPosition*>>::iterator iter = m_poses.begin();
	while (iter != m_poses.end())
	{
		auto data = iter->second;
		std::map<std::string, AxisPosition*>::iterator iter_datas = data.begin();
		while (iter_datas != data.end())
		{
			delete iter_datas->second;
			iter_datas++;
		}
		iter++;
	}
	m_poses.clear();
	m_posesList.clear();
	// 查询数据
	std::string cmd = "select PositionID,AxisName,AxisID,PositionName,Distance,Spacing,Notes from TblPosition";
	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(m_db, cmd.c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		AxisPosition *posInfo;
		// 遍历结果集
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			posInfo = new AxisPosition();
			posInfo->posID = sqlite3_column_int(statement, 0);
			std::string axisName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
			posInfo->axisName = axisName;
			posInfo->axisID = sqlite3_column_int(statement, 2);
			std::string posName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
			posInfo->posName = posName;
			posInfo->distance = sqlite3_column_double(statement, 4);
			posInfo->spacing = sqlite3_column_double(statement, 5);
			posInfo->notes = CoverToChineseStr(std::string_view(reinterpret_cast<const char*>(sqlite3_column_text(statement, 6))));
			if (m_poses.find(axisName) != m_poses.end())
			{
				auto data = m_poses[axisName];
				data[posName] = posInfo;
				m_poses[axisName] = data;
			}
			else
			{
				std::map<std::string, AxisPosition*> posMap;
				posMap[posName] = posInfo;
				m_poses[axisName] = posMap;
			}
			m_posesList[axisName].push_back(posInfo);
		}
		// 释放资源
		sqlite3_finalize(statement);
		return true;
	}
	return false;
}

bool MotionParameter::LoadOutputInfos()
{
	// 清空数据结构
	std::map<std::string, MotionIO*>::iterator iter = m_outputs.begin();
	while (iter != m_outputs.end())
	{
		delete iter->second;
		iter++;
	}
	m_outputs.clear();
	// 查询数据
	std::string cmd = "select OutputID,name,cardType,cardNum,bitNum,electricalLevel,chinaName,groupName from TblOutputInfo order by cardNum,bitNum";
	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(m_db, cmd.c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		MotionIO *outputInfo;
		// 遍历结果集
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			outputInfo = new MotionIO();
			outputInfo->id = sqlite3_column_int(statement, 0);
			std::string outputName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
			outputInfo->name = outputName;
			outputInfo->cardType = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
			outputInfo->cardNum = sqlite3_column_int(statement, 3);
			outputInfo->bitNum = sqlite3_column_int(statement, 4);
			outputInfo->electrical_level = CoverToChineseStr(std::string_view(reinterpret_cast<const char*>(sqlite3_column_text(statement, 5))));
			outputInfo->cnName = CoverToChineseStr(std::string_view(reinterpret_cast<const char*>(sqlite3_column_text(statement, 6))));
			outputInfo->group = CoverToChineseStr(std::string_view(reinterpret_cast<const char*>(sqlite3_column_text(statement, 7))));
			m_outputs[outputName] = outputInfo;
		}
		// 释放资源
		sqlite3_finalize(statement);
		return true;
	}
	return false;
}

bool MotionParameter::LoadInputInfos()
{
	// 清空数据结构
	std::map<std::string, MotionIO*>::iterator iter = m_inputs.begin();
	while (iter != m_inputs.end())
	{
		delete iter->second;
		iter++;
	}
	m_inputs.clear();
	// 查询数据
	std::string cmd = "select InputID,name,cardType,cardNum,bitNum,isUsed,electricalLevel,chinaName,groupName from TblInputInfo order by cardNum,bitNum";
	sqlite3_stmt* statement;
	if (sqlite3_prepare_v2(m_db, cmd.c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		MotionIO *inputInfo;
		// 遍历结果集
		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			inputInfo = new MotionIO();
			inputInfo->id = sqlite3_column_int(statement, 0);
			std::string inputName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
			inputInfo->name = inputName;
			inputInfo->cardType = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
			inputInfo->cardNum = sqlite3_column_int(statement, 3);
			inputInfo->bitNum = sqlite3_column_int(statement, 4);
			inputInfo->isUsed = sqlite3_column_int(statement, 5);
			inputInfo->electrical_level = CoverToChineseStr(std::string_view(reinterpret_cast<const char*>(sqlite3_column_text(statement, 6))));
			inputInfo->cnName = CoverToChineseStr(std::string_view(reinterpret_cast<const char*>(sqlite3_column_text(statement, 7))));
			inputInfo->group = CoverToChineseStr(std::string_view(reinterpret_cast<const char*>(sqlite3_column_text(statement, 8))));
			m_inputs[inputName] = inputInfo;
		}
		// 释放资源
		sqlite3_finalize(statement);
		return true;
	}
	return false;
}

bool MotionParameter::UpdateAxisInfos(MotionAxis* axis_update_info)
{
	MotionAxis* axis_info = axis_update_info;

	std::stringstream data_stream;
	data_stream << "replace into TblAxis values(";
	data_stream << axis_info->axisID << ",";
	data_stream << "'" << axis_info->axisName << "'" << ",";
	data_stream << "'" << axis_info->axisNameCn << "'" << ",";
	data_stream << "'" << axis_info->motorType << "'" << ",";
	data_stream << "'" << axis_info->cardType << "'" << ",";
	data_stream << axis_info->cardNum << ",";
	data_stream << axis_info->axisNum << ",";
	data_stream << axis_info->minVel << ",";
	data_stream << axis_info->maxVel << ",";
	data_stream << axis_info->accVel << ",";
	data_stream << axis_info->decVel << ",";
	data_stream << axis_info->stopVel << ",";
	data_stream << axis_info->sPara << ",";
	data_stream << axis_info->allowErrorPos << ",";
	data_stream << axis_info->equiv << ",";
	data_stream << axis_info->lead << ",";
	data_stream << axis_info->homeMode << ",";
	data_stream << axis_info->homeDir << ",";
	data_stream << axis_info->homeMinVel << ",";
	data_stream << axis_info->homeMaxVel << ",";
	data_stream << axis_info->homeAccVel << ",";
	data_stream << axis_info->homeDecVel << ",";
	data_stream << axis_info->homeOffsetPos << ",";
	data_stream << axis_info->homeCurve << ",";
	data_stream << axis_info->homeEZA << ",";
	data_stream << axis_info->msTimeout << ",";
	data_stream << axis_info->useDelay << ",";
	data_stream << axis_info->useLimit << ",";
	data_stream << axis_info->positiveLimit << ",";
	data_stream << axis_info->negativeLimit;
	data_stream << ")";

	// string转成utf-8格式的，不然会中文乱码
	const char* cmd = UnicodeToUtf8(s2wchar(data_stream.str()));

	sqlite3_stmt* statement;
	// 执行SQL语句
	if (sqlite3_prepare_v2(m_db, cmd, -1, &statement, nullptr) == SQLITE_OK)
	{
		if (sqlite3_step(statement) == SQLITE_DONE)
		{
			// 释放资源
			sqlite3_finalize(statement);
			// 重新加载数据
			LoadAxisInfos();
			return true;
		}
	}	
	sqlite3_finalize(statement);
	return false;
}

bool MotionParameter::DeleteAxisInfos(const std::string & axis_name)
{
	std::stringstream cmd;
	cmd << "delete from TblAxis where axisName = '" << axis_name << "'";
	sqlite3_stmt* statement;
	// 执行SQL语句
	if (sqlite3_prepare_v2(m_db, cmd.str().c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		if (sqlite3_step(statement) == SQLITE_DONE)
		{
			// 释放资源
			sqlite3_finalize(statement);
			// 删除轴已配置的点位数据
			auto pos_list = GetAxisPosListInfo(axis_name);
			for (auto pos : pos_list)
			{
				DeletePosInfos(pos->posName, false);
			}
			// 重新加载数据
			LoadPositionInfos();
			LoadAxisInfos();
			return true;
		}
	}
	sqlite3_finalize(statement);
	return false;
}

bool MotionParameter::UpdatePosInfos(AxisPosition * pos_update_info)
{
	AxisPosition* pos_info = pos_update_info;

	std::stringstream data_stream;
	//data_stream << "replace into TblPosition values(";
	data_stream << "replace into TblPosition (PositionID,AxisName,AxisID,PositionName,Distance,Spacing,Notes) values (";
	data_stream << pos_info->posID << ",";
	data_stream << "'" << pos_info->axisName << "'" << ",";
	data_stream << pos_info->axisID << ",";
	data_stream << "'" << pos_info->posName << "'" << ",";
	data_stream << pos_info->distance << ",";
	data_stream << pos_info->spacing << ",";
	data_stream << "'" << pos_info->notes << "'";
	data_stream << ")";

	// string转成utf-8格式的，不然会中文乱码
	const char* cmd = UnicodeToUtf8(s2wchar(data_stream.str()));

	sqlite3_stmt* statement;
	// 执行SQL语句
	if (sqlite3_prepare_v2(m_db, cmd, -1, &statement, nullptr) == SQLITE_OK)
	{
		if (sqlite3_step(statement) == SQLITE_DONE)
		{
			// 释放资源
			sqlite3_finalize(statement);
			// 重新加载数据
			LoadPositionInfos();
			return true;
		}
	}
	sqlite3_finalize(statement);
	return false;
}

bool MotionParameter::DeletePosInfos(const std::string & pos_name, bool update_pos_infos)
{
	std::stringstream cmd;
	cmd << "delete from TblPosition where PositionName = '" << pos_name << "'";
	sqlite3_stmt* statement;
	// 执行SQL语句
	if (sqlite3_prepare_v2(m_db, cmd.str().c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		if (sqlite3_step(statement) == SQLITE_DONE)
		{
			// 释放资源
			sqlite3_finalize(statement);
			// 重新加载数据
			if (update_pos_infos)
				LoadPositionInfos();
			return true;
		}
	}
	sqlite3_finalize(statement);
	return false;
}

bool MotionParameter::UpdateIOInfos(MotionIO * io_update_info, bool is_input_io)
{
	std::stringstream data_stream;
	if (is_input_io)
		data_stream << "replace into TblInputInfo (InputID,name,cardType,cardNum,bitNum,isUsed,electricalLevel,chinaName,groupName) values (";
	else
		data_stream << "replace into TblOutputInfo (OutputID,name,cardType,cardNum,bitNum,electricalLevel,chinaName,groupName) values (";
	data_stream << io_update_info->id << ",";
	data_stream << "'" << io_update_info->name << "'" << ",";
	data_stream << "'" << io_update_info->cardType << "'" << ",";
	data_stream << io_update_info->cardNum << ",";
	data_stream << io_update_info->bitNum << ",";
	if (is_input_io)
		data_stream << io_update_info->isUsed << ",";
	data_stream << "'" << io_update_info->electrical_level << "'" << ",";
	data_stream << "'" << io_update_info->cnName << "'" << ",";
	data_stream << "'" << io_update_info->group << "'";
	data_stream << ")";

	// string转成utf-8格式的，不然会中文乱码
	const char* cmd = UnicodeToUtf8(s2wchar(data_stream.str()));

	sqlite3_stmt* statement;
	// 执行SQL语句
	if (sqlite3_prepare_v2(m_db, cmd, -1, &statement, nullptr) == SQLITE_OK)
	{
		if (sqlite3_step(statement) == SQLITE_DONE)
		{
			// 释放资源
			sqlite3_finalize(statement);
			// 重新加载数据
			if (is_input_io)
				LoadInputInfos();
			else
				LoadOutputInfos();
			return true;
		}
	}
	sqlite3_finalize(statement);
	return false;
}

bool MotionParameter::DeleteIOInfos(const std::string & io_name, bool is_input_io)
{
	std::stringstream cmd;
	if (is_input_io)
		cmd << "delete from TblInputInfo where name = '" << io_name << "'";
	else
		cmd << "delete from TblOutputInfo where name = '" << io_name << "'";
	sqlite3_stmt* statement;
	// 执行SQL语句
	if (sqlite3_prepare_v2(m_db, cmd.str().c_str(), -1, &statement, nullptr) == SQLITE_OK)
	{
		if (sqlite3_step(statement) == SQLITE_DONE)
		{
			// 释放资源
			sqlite3_finalize(statement);
			// 重新加载数据
			if (is_input_io)
				LoadInputInfos();
			else
				LoadOutputInfos();
			return true;
		}
	}
	sqlite3_finalize(statement);
	return false;
}

bool MotionParameter::IsContainAxis(const std::string & axis_name)
{
	return std::find(m_axisList.begin(), m_axisList.end(), axis_name) != m_axisList.end();
}

AxisPosition* MotionParameter::GetAxisPosInfo(const std::string & axis_name, const std::string & pos_name)
{
	if (!IsContainAxis(axis_name))
	{
		return nullptr;
	}
	return m_poses[axis_name][pos_name];
}

std::vector<AxisPosition*> MotionParameter::GetAxisPosListInfo(const std::string & axis_name)
{
	if (!IsContainAxis(axis_name))
	{
		return std::vector<AxisPosition*>();
	}
	return m_posesList[axis_name];
}

MotionAxis * MotionParameter::GetAxisParam(const std::string & axis_name)
{
	if (!IsContainAxis(axis_name))
	{
		return nullptr;
	}
	return m_axises[axis_name];
}

std::vector<std::string> MotionParameter::GetAxisNameList()
{
	return m_axisList;
}

IOHash MotionParameter::GetInputIOList()
{
	return m_inputs;
}

IOHash MotionParameter::GetOutputIOList()
{
	return m_outputs;
}

MotionIO * MotionParameter::GetInputIOInfo(const std::string & io_name, bool is_en)
{
	if (is_en)
		return m_inputs[io_name];
	else
	{
		IOHash::iterator iter = m_inputs.begin();
		while (iter != m_inputs.end())
		{
			MotionIO* io_info = iter->second;
			if (io_name == io_info->cnName)
			{
				return m_inputs[io_info->name];
			}
			iter++;
		}
	}
}

void MotionParameter::UpdataInputIOUseStatus(const std::string & io_name, bool is_use)
{
	m_inputs[io_name]->isUsed = is_use;
}

MotionIO * MotionParameter::GetOutputIOInfo(const std::string & io_name, bool is_en)
{
	if (is_en)
		return m_outputs[io_name];
	else
	{
		IOHash::iterator iter = m_outputs.begin();
		while (iter != m_outputs.end())
		{
			MotionIO* io_info = iter->second;
			if (io_name == io_info->cnName)
			{
				return m_outputs[io_info->name];
			}
			iter++;
		}
	}
}