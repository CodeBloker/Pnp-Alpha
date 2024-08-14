#pragma once

#include "Base/JupGlobal.h"
#include "PluginBase/JupPluginBase.h"

class IDSPlugin : public JupPluginBase
{
	JUP_DISABLE_MOVE(IDSPlugin)
	JUP_STATIC(IDSPlugin)
	JUP_STATIC_HELPER(IDSPlugin)
};

extern "C" {
	__declspec(dllexport) JupPluginBase* JupGetPlugin();
}
