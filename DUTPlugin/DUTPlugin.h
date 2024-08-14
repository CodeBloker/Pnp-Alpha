#pragma once

#include "Base/JupGlobal.h"
#include "PluginBase/JupPluginBase.h"

class DUTPlugin : public JupPluginBase
{
	JUP_DISABLE_MOVE(DUTPlugin)
	JUP_STATIC(DUTPlugin)
	JUP_STATIC_HELPER(DUTPlugin)
};

extern "C" {
	__declspec(dllexport) JupPluginBase* JupGetPlugin();
}
