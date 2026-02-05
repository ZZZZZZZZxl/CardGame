#pragma once
#include "models/CardModel.h"
#include "views/CardView.h"
#include "cocos2d.h"
#include <unordered_map> 

namespace managers
{
    class CardDataMapManager : public cocos2d::Ref {
    public:
        CardDataMapManager();
        ~CardDataMapManager();

        // 添加数据
        void addCardModel(models::CardModel* model, int cardId);
        void addCardView(views::CardView* view, int cardId);

        // 查询数据
        models::CardModel* getModel(int cardId);
        models::CardModel* getModel(views::CardView* view);
        views::CardView* getView(int cardId);
        int getCardId(views::CardView* view);

        // 删除数据
        void removeCard(int cardId);
        void clear();

    private:
        // cardId->view cardId->model view->cardId
        cocos2d::Map<int, views::CardView*> _idToView;
        std::unordered_map<int, models::CardModel*> _idToModel;
        std::unordered_map<views::CardView*, int> _viewToId;

    };
}