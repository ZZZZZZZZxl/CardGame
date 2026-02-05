#pragma once

#include "cocos2d.h"
#include "models/CardModel.h"
#include "utils/Utils.h"
#include "configs/CardResConfig.h"

namespace views {

    class CardView : public cocos2d::Node {
    public:
        static CardView* create(const models::CardModel& data);

        bool init(const models::CardModel& data);

        void moveToPosition(cocos2d::Vec2 targetPos, float duration = 0.3f);

    private:
        cocos2d::Sprite* _background;
    };

}