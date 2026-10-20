
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/wrappers/GameObject/BallWrapper.h"
#include <chrono>
#include <functional>

class SuperPinch : public BakkesMod::Plugin::BakkesModPlugin
{
private:
    std::chrono::steady_clock::time_point lastBoost{};

    void onLoad() override
    {
        cvarManager->log("SuperPinch loaded.");

        gameWrapper->HookEvent(
            "Function TAGame.Ball_TA.Touch",
            std::bind(&SuperPinch::onBallTouch, this,
                      std::placeholders::_1)
        );
    }

    void onUnload() override
    {
        cvarManager->log("SuperPinch unloaded.");
    }

    void onBallTouch(std::string eventName)
    {
        // Never modify the ball outside training modes.
        if (!gameWrapper->IsInFreeplay() &&
            !gameWrapper->IsInCustomTraining())
            return;

        auto now = std::chrono::steady_clock::now();

        // Prevent repeated boosts from stacking immediately.
        if (now - lastBoost < std::chrono::milliseconds(350))
            return;

        auto game = gameWrapper->GetCurrentGameState();
        if (!game) return;

        auto ball = game.GetBall();
        if (!ball) return;

        Vector velocity = ball.GetVelocity();

        // Prototype boost; tune after verifying the touch hook.
        constexpr float multiplier = 1.8f;
        ball.SetVelocity(velocity * multiplier);

        lastBoost = now;
    }
};

BAKKESMOD_PLUGIN(
    SuperPinch,
    "SuperPinch",
    "0.1.0",
    PLUGINTYPE_FREEPLAY
)
