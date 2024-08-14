#pragma once

#include "Base/JupMethodCaller.h"
#include "Common/MtcpPacket.h"
#include "JupCore_export.h"

using JupData = MtcpPacket;

class JUPCORE_EXPORT JupCaller : public JupMethodCaller<JupData>
{
public:
	void* This() override final;
	int Initialize() override;
	int RegisterMethod() override;

protected:
	friend class JupPluginBase;
};
