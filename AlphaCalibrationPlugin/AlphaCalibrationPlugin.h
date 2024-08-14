#pragma once

#include "PluginBase/JupPluginBase.h"

class AlphaCalibrationPlugin : public JupPluginBase
{
	JUP_DISABLE_MOVE(AlphaCalibrationPlugin)
	JUP_STATIC(AlphaCalibrationPlugin)
	JUP_STATIC_HELPER(AlphaCalibrationPlugin)
};

extern "C" {
	__declspec(dllexport) JupPluginBase* JupGetPlugin();
}
