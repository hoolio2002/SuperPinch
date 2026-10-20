
#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

class SuperPinch : public BakkesMod::Plugin::BakkesModPlugin,
                   public SettingsWindowBase
{
public:
    void onLoad() override;
    void RenderSettings() override;
};
