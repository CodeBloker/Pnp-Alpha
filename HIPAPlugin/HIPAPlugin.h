#pragma once

#include "Base/JupGlobal.h"
#include "PluginBase/JupPluginBase.h"

class HIPAPlugin : public JupPluginBase
{
	JUP_DISABLE_MOVE(HIPAPlugin)
	JUP_STATIC(HIPAPlugin)
	JUP_STATIC_HELPER(HIPAPlugin)
};

extern "C" {
	__declspec(dllexport) JupPluginBase* JupGetPlugin();
}
