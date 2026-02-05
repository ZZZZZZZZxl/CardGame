#pragma once
#include "cocos2d.h"
#include <vector>

namespace configs {
    struct CardUnitConfig {
        int cardFace;
        int cardSuit;
        cocos2d::Vec2 position;
    };

    struct LevelConfig {
        std::vector<CardUnitConfig> playfield;
        std::vector<CardUnitConfig> stack;
    };
}