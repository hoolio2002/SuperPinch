#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

class SuperPinch : public BakkesMod::Plugin::BakkesModPlugin
{
public:
    void onLoad() override;
    void RenderSettings() override;
    void RenderWindow() override;
    std::string GetPluginName() override;
    void SetImGuiContext(uintptr_t ctx) override;
};
