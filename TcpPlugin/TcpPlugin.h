#pragma once

#include "PluginBase/JupPluginBase.h"

class TcpPlugin : public JupPluginBase
{
	JUP_DISABLE_MOVE(TcpPlugin)
	JUP_STATIC(TcpPlugin)
	JUP_STATIC_HELPER(TcpPlugin)
};

extern "C" {
	__declspec(dllexport) JupPluginBase* JupGetPlugin();
}
