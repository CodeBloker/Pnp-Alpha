#pragma once

#include "Base/JupGlobal.h"
#include "PluginBase/JupPluginBase.h"

class JupMotionPlugin : public JupPluginBase
{
	JUP_DISABLE_MOVE(JupMotionPlugin)
	JUP_STATIC(JupMotionPlugin)
	JUP_STATIC_HELPER(JupMotionPlugin)
};

extern "C" {
	__declspec(dllexport) JupPluginBase* JupGetPlugin();
}
