#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include "models/UndoModel.h"
#include "models/FieldModel.h"
#include "views/StackFieldView.h"
#include "views/CardView.h"
#include "services/FieldModelService.h"
#include "services/FieldLayoutService.h"
#include "managers/UndoManager.h"
#include "managers/CardDataMapManager.h"
#include <vector>
using namespace cocos2d;

namespace controllers {

    class StackFieldController {
    public:
        StackFieldController() = default;
        ~StackFieldController() = default;

        void init(
            models::FieldModel* stackFieldModel,
            cocos2d::Node* parent,
            const cocos2d::Vec2& position,
            managers::UndoManager* undoManager
        );
        
        void StackFieldController::pushCardToTop(views::CardView* cardView, const cocos2d::Vec2& worldPos, models::CardModel* cardModel);
        void undoBottomToTop(models::UndoStep step);
        void removeCardModel(const models::CardModel* card);
        void popTopCardView();
        void removeCardView(views::CardView* cardView);

        views::CardView* getTopCardView();
        models::CardModel* StackFieldController::getTopCardModel() ;

    private:
        views::StackFieldView* _stackView = nullptr;
        void bringBottomCardToTop(views::CardView* cardView);
        models::FieldModel* _stackFieldModel;
        managers::UndoManager* _undoManager = nullptr;
        managers::CardDataMapManager* _cardMap = nullptr;
    };

}
