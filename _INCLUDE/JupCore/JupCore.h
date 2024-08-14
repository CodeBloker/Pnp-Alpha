#pragma once

#include "JupCore_export.h"
#include "StdAfx.h"
#include "Base/JupGlobal.h"
#include "Common/JupCommon.h"
#include "Common/MtcpPacket.h"
#include "PluginBase/JupLog.h"
#include "PluginBase/JupTextData.h"

#define jCore JupCore::GetInstance()

class JUPCORE_EXPORT JupCore
{
	JUP_STATIC(JupCore)
	JUP_STATIC_HELPER(JupCore)

public:
	bool RegisterEventWindow(std::string key, JupSubDialog* window);
	//������ʽ�źţ�����new event�����һ��Զ��ͷ�
	__int64 PostEvent(std::string key, JupCustomEvent* event);
	//����ʽ�źţ������Զ��ͷ�
	__int64 SendEvent(std::string key, JupCustomEvent* event);

	MtcpPacket& GetPreMtcpPacket();
	JupTextData& GlobalSettings();
	JupLog& Logger(const std::string& name);
};
