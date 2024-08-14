#pragma once

#include "PluginBase/JupPluginBase.h"

class LIVPlugin : public JupPluginBase
{
	JUP_DISABLE_MOVE(LIVPlugin)
	JUP_STATIC(LIVPlugin)
	JUP_STATIC_HELPER(LIVPlugin)
};

extern "C" {
	__declspec(dllexport) JupPluginBase* JupGetPlugin();
}
