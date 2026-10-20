#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/wrappers/GameObject/BallWrapper.h"

#include <cmath>
#include <chrono>

class SuperPinch : public BakkesMod::Plugin::BakkesModPlugin
{
private:
    std::chrono::steady_clock::time_point lastTouch{};
    bool hasBoosted = false;

    void onLoad() override
    {
        cvarManager->registerCvar(
            "superpinch_speed_kph",
            "150.0",
            "SuperPinch target ball speed in KPH",
            true,
            true, 0.0f,
            false, 0.0f,
            true
        );

        gameWrapper->HookEventWithCallerPost<BallWrapper>(
            "Function TAGame.Ball_TA.OnCarTouch",
            [this](BallWrapper ball, void* params,
                   std::string eventName)
            {
                if (!gameWrapper->IsInFreeplay() &&
                    !gameWrapper->IsInCustomTraining())
                    return;

                if (!ball)
                    return;

                const auto now = std::chrono::steady_clock::now();

                if (hasBoosted &&
                    now - lastTouch < std::chrono::milliseconds(300))
                    return;

                const float kph =
                    cvarManager->getCvar(
                        "superpinch_speed_kph"
                    ).getFloatValue();

                if (!std::isfinite(kph) || kph < 0.0f)
                    return;

                // Rocket League speed units:
                // 1 Unreal unit/second = 0.036 km/h.
                const float target = kph / 0.036f;

                Vector v = ball.GetVelocity();

                const float magnitude = std::sqrt(
                    v.X * v.X + v.Y * v.Y + v.Z * v.Z
                );

                if (magnitude < 1.0f)
                    return;

                const float scale = target / magnitude;

                ball.SetVelocity(Vector{
                    v.X * scale,
                    v.Y * scale,
                    v.Z * scale
                });

                lastTouch = now;
                hasBoosted = true;
            }
        );

        cvarManager->log("SuperPinch loaded. Target speed: KPH.");
    }

    void onUnload() override
    {
        cvarManager->log("SuperPinch unloaded.");
    }
};

BAKKESMOD_PLUGIN(
    SuperPinch,
    "SuperPinch",
    "1.0.0",
    PLUGINTYPE_FREEPLAY
)
