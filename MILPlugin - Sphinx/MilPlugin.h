#pragma once

#include "Base/JupGlobal.h"
#include "PluginBase/JupPluginBase.h"

class MilPlugin : public JupPluginBase
{
	JUP_DISABLE_MOVE(MilPlugin)
	JUP_STATIC(MilPlugin)
	JUP_STATIC_HELPER(MilPlugin)
};

extern "C" {
	__declspec(dllexport) JupPluginBase* JupGetPlugin();
}
