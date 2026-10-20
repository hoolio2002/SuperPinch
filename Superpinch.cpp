#include "pch.h"
#include "SuperPinch.h"
#include <algorithm>

BAKKESMOD_PLUGIN(
    SuperPinch,
    "SuperPinch",
    plugin_version,
    PLUGINTYPE_FREEPLAY
)

void SuperPinch::onLoad()
{
    cvarManager->registerCvar(
        "superpinch_target_kph",
        "100",
        "Target speed in KPH",
        true,
        true,
        1.0f,
        true,
        500.0f,
        true
    );
}

void SuperPinch::RenderSettings()
{
    auto cvar = cvarManager->getCvar("superpinch_target_kph");

    if (!cvar)
        return;

    float speed = cvar.getFloatValue();

    ImGui::Text("SuperPinch");
    ImGui::Separator();
    ImGui::Text("Target pinch speed (KPH)");

    if (ImGui::InputFloat("##TargetKPH", &speed, 1.0f, 10.0f, "%.1f"))
    {
        speed = std::clamp(speed, 1.0f, 500.0f);
        cvar.setValue(speed);
    }
}
