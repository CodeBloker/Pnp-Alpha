#pragma once

#include "PluginBase/JupPluginBase.h"

class DemoPlugin : public JupPluginBase
{
	JUP_DISABLE_MOVE(DemoPlugin)
	JUP_STATIC(DemoPlugin)
	JUP_STATIC_HELPER(DemoPlugin)
};

extern "C" {
	__declspec(dllexport) JupPluginBase* JupGetPlugin();
}
