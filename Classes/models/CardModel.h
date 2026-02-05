#pragma once
#include "cocos2d.h" 
#include "CardCommonDefine.h"

namespace models {
    struct CardModel {
        int cardId = -1;
        CardSuitType suit = CST_NONE;
        CardFaceType face = CFT_NONE;
        cocos2d::Vec2 position; 
        CardModel() = default;
        CardModel(int id, CardSuitType s, CardFaceType f, cocos2d::Vec2 pos = cocos2d::Vec2::ZERO)
            : cardId(id), suit(s), face(f), position(pos) {}
    };
}