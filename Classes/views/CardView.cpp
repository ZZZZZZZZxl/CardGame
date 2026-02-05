#include "CardView.h"

using namespace cocos2d;

namespace views {

    CardView* CardView::create(const models::CardModel& data) {
        CardView* ret = new (std::nothrow) CardView();
        if (ret && ret->init(data)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool CardView::init(const models::CardModel& data) {
        if (!Node::init()) return false;

        auto cardData = data;

        // 1. 获取点数以及对应颜色
        std::string colorStr = gameUtils::Utils::getColorBySuit(cardData.suit);
        std::string displayNum = gameUtils::Utils::getFaceString(cardData.face);

        // 2. 从config中提取路径
        _background = cocos2d::Sprite::create(CardResConfig::getCardBackGroundPath());
        auto bgSize = _background->getContentSize();
        this->setContentSize(bgSize);
        this->addChild(_background);

        // 3. 提取大数字对应的路径图片，加载到背景的中心
        auto bigNum = cocos2d::Sprite::create(CardResConfig::getBigNumberPath(colorStr, displayNum));
        if (bigNum) {
            bigNum->setPosition(bgSize / 2);
            _background->addChild(bigNum);
        }

        // 4. 提取小数字对应的路径图片，加载到背景左上角
        auto smallNum = cocos2d::Sprite::create(CardResConfig::getSmallNumberPath(colorStr, displayNum));
        if (smallNum) {
            smallNum->setAnchorPoint(cocos2d::Vec2(0, 1));
            smallNum->setPosition(cocos2d::Vec2(15, bgSize.height - 15));
            _background->addChild(smallNum);
        }

        // 5. 同样 花色图片到右上角
        
        auto suitSprite = cocos2d::Sprite::create(CardResConfig::getSuitPath(gameUtils::Utils::getSuitFileName(cardData.suit)));
        if (suitSprite) {
            suitSprite->setAnchorPoint(cocos2d::Vec2(1, 1));
            suitSprite->setPosition(cocos2d::Vec2(bgSize.width - 15, bgSize.height - 15));
            _background->addChild(suitSprite);
        }

        return true;
    }
    void CardView::moveToPosition(Vec2 targetPos, float duration) {
        auto move = MoveTo::create(duration, targetPos);
        this->runAction(move);
    }

}