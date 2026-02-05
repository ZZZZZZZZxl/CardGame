#include "StackFieldView.h"


namespace views {

    bool StackFieldView::init() {
        if (!Node::init()) return false;

        this->setContentSize(cocos2d::Size(1080, 580));

        auto bg = cocos2d::LayerColor::create(
            cocos2d::Color4B(148, 33, 146, 255),
            1080,
            580
        );
        this->addChild(bg, -1);

        return true;
    }

    void StackFieldView::initWithCards(
        const std::vector<models::CardModel*>& cards,
        managers::CardDataMapManager* cardMapManager
    ) {
        if (cards.empty()) return;

        int zOrder = static_cast<int>(cards.size());
        _topZOrder = zOrder + 1;

        bool isFirst = true;
        int handCardCount = 0;


        for (auto it = cards.rbegin(); it != cards.rend(); ++it) {
            auto cardData = *it;
            auto cardView = views::CardView::create(*cardData);

            float finalX = 0.0f;

            if (isFirst) {
                // 顶牌
                finalX = services::FieldLayoutService::getStackFieldViewCenterX() + services::FieldLayoutService::getStackFieldGapWidth();
                isFirst = false;
                _topCards.push(cardView);
            }
            else
            {
               
                // 底牌
                finalX = services::FieldLayoutService::getStackFieldViewCenterX() 
                    - services::FieldLayoutService::getStackFieldGapWidth() 
                    + ( handCardCount * services::FieldLayoutService::getStackFieldOffsetX() );
                handCardCount++;

                // ⭐ 给底牌添加点击事件
                auto listener = cocos2d::EventListenerTouchOneByOne::create();
                listener->setSwallowTouches(true);

                listener->onTouchBegan = [cardView](cocos2d::Touch* t, cocos2d::Event*) {
                    Vec2 localPoint = cardView->convertToNodeSpace(t->getLocation());
                    Size size = cardView->getContentSize();
                    Rect rect(-size.width / 2, -size.height / 2, size.width, size.height);
                    return rect.containsPoint(localPoint);
                };

                listener->onTouchEnded = [this, cardView](cocos2d::Touch*, cocos2d::Event*) {
                    if (_onBottomCardClickCallback)
                    {
                        _onBottomCardClickCallback(cardView);
                    }
                };

                _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, cardView);
                _bottomCardViews.push({zOrder, cardView});
            }

            cardView->setPosition(finalX, services::FieldLayoutService::getStackFieldViewBaseY());
            this->addCard(cardView, zOrder--);
            cardMapManager->addCardView(cardView, cardData->cardId);
            cardMapManager->addCardModel(cardData, cardData->cardId);
        }
    }

    void StackFieldView::addCard(cocos2d::Node* card, int zOrder) {
        this->addChild(card, zOrder);
    }

    CardView* StackFieldView::getTopCardView() const {
        if (_topCards.empty()) return nullptr;
        return _topCards.top();
    }

    CardView* StackFieldView::getTopBottomCardView() const
    {
        if (_bottomCardViews.empty()) return nullptr;
        
        return _bottomCardViews.top().second;
    }


    void StackFieldView::removeBottomTopCard()
    {
        if (_bottomCardViews.empty()) return;

        auto cardView = getTopBottomCardView();
        _bottomCardViews.pop();
        cardView->removeFromParent();
    }

    void StackFieldView::addTopCardView(CardView* cardView)
    {
        if (cardView == nullptr) return;

        _topCards.push(cardView);
        this->addCard(cardView, _topZOrder ++);
    }

    void StackFieldView::popTopCardView()
    {
        if (_topCards.empty()) return;

        CardView* top = getTopCardView();
        _topCards.pop();
    }


    void StackFieldView::addBottomCardView(CardView* cardView, int zOrder)
    {
        if (!cardView) return;
        _bottomCardViews.push({ zOrder, cardView });
        cardView->setLocalZOrder(zOrder);
    }
}
