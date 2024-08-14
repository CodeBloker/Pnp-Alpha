#pragma once

#include "PluginBase/JupPluginBase.h"

class SerialPlugin : public JupPluginBase
{
	JUP_DISABLE_MOVE(SerialPlugin)
	JUP_STATIC(SerialPlugin)
	JUP_STATIC_HELPER(SerialPlugin)
};

extern "C" {
	__declspec(dllexport) JupPluginBase* JupGetPlugin();
}
