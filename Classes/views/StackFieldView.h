#pragma once
//#include "cocos2d.h"
#include "models/CardModel.h"
#include "models/FieldModel.h"
#include "views/CardView.h"
#include "managers/CardDataMapManager.h"
#include "services/FieldLayoutService.h"
#include <vector>
#include <queue>

using namespace cocos2d;

namespace views {

    class StackFieldView : public cocos2d::Node {
    public:
        

        CREATE_FUNC(StackFieldView);
        virtual bool init() override;

        void initWithCards(const std::vector<models::CardModel*>& cards, managers::CardDataMapManager* cardMapManager);
        void addCard(cocos2d::Node* card, int zOrder);
        void setOnBottomCardClickCallback(std::function<void(CardView*)> callback) {
            _onBottomCardClickCallback = callback;
        }
        void addTopCardView(CardView* cardView);
        void removeBottomTopCard();
        void popTopCardView();
        void addBottomCardView(CardView* cardView, int zOrder);

        CardView* getTopBottomCardView() const;
        CardView* getTopCardView() const;

    private:
        std::function<void(CardView*)> _onBottomCardClickCallback;
        std::priority_queue<std::pair<int, CardView*>> _bottomCardViews;
        std::stack<CardView*> _topCards;
        int _topZOrder;
    };
}
