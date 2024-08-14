#pragma once

#include "Base/JupGlobal.h"
#include "PluginBase/JupPluginBase.h"

class HIKPlugin : public JupPluginBase
{
	JUP_DISABLE_MOVE(HIKPlugin)
	JUP_STATIC(HIKPlugin)
	JUP_STATIC_HELPER(HIKPlugin)
};

extern "C" {
	__declspec(dllexport) JupPluginBase* JupGetPlugin();
}
