#pragma once
#include <string>
#include "json/json.h"
#include "CardGlobal.h"

class MotionIO
{
public:
	std::string name;
	std::string cardType;
	int id;
	int cardNum;
	int bitNum;
	bool isUsed;
	std::string electrical_level;
	std::string cnName;
	std::string group;

	//inline Json::Value toJSonObject()
	//{
	//	Json::Value ob;
	//	ob[DataID] = id;
	//	ob[IO_Name] = name;
	//	ob[IO_CardType] = cardType;
	//	ob[IO_CardNum] = cardNum;
	//	ob[IO_BitNum] = bitNum;
	//	ob[IO_State] = state;
	//	ob[IO_IsUsed] = isUsed;
	//	ob[IO_HighName] = highName;
	//	ob[IO_CnName] = cnName;
	//	ob[IO_Group] = groupName;
	//	return ob;
	//}
};
