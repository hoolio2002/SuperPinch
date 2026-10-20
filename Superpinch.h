#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

class SuperPinch : public BakkesMod::Plugin::BakkesModPlugin
{
public:
    void onLoad() override;
    void RenderSettings();
};
