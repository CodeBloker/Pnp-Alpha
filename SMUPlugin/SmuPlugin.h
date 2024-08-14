#pragma once

#include "Base/JupGlobal.h"
#include "PluginBase/JupPluginBase.h"

class SmuPlugin : public JupPluginBase
{
	JUP_DISABLE_MOVE(SmuPlugin)
	JUP_STATIC(SmuPlugin)
	JUP_STATIC_HELPER(SmuPlugin)
};

extern "C" {
	__declspec(dllexport) JupPluginBase* JupGetPlugin();
}
