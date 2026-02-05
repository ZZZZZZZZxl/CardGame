#include "PlayFieldController.h"

namespace controllers {

    void PlayFieldController::init(
        models::FieldModel* playFieldModel,
        cocos2d::Node* parent,
        const cocos2d::Vec2& position,
        managers::UndoManager* undoManager
    ) {
        if (!parent) return;
        _playFieldModel = playFieldModel;

        _playFieldView = views::PlayFieldView::create();
        _playFieldView->setPosition(position);
        _playFieldView->setOnCardClickCallback(
            [this](views::CardView* cardView) {
                this->handleCardClick(cardView);
            }
        );

        _cardMap = new managers::CardDataMapManager();

        _undoManager = undoManager;

        parent->addChild(_playFieldView,1);

        auto cards = playFieldModel->_cards;
        _playFieldView->initWithCards(cards, _cardMap);
    }

    void PlayFieldController::handleCardClick(views::CardView* cardView) {
        if (!cardView) return;
        auto cardModel = _cardMap->getModel(cardView);
        if (!cardModel) return;

        if (!canMoveToStack(cardView, cardModel)) return;
        replaceTrayWithPlayFieldCard(cardView, cardModel);
    }

    bool PlayFieldController::canMoveToStack(views::CardView* cardView, models::CardModel* cardModel) {
        if (!cardView) return false;
        if (!cardModel) return false;
        if (!_stackController) return false;

        const auto* stackTopCard = _stackController->getTopCardModel();
        if (!stackTopCard) return true;

        return services::CardRuleService::canLink(cardModel->face, stackTopCard->face);
    }

    
    void PlayFieldController::replaceTrayWithPlayFieldCard(views::CardView* cardView, models::CardModel* cardModel) {
        if (!cardView) return;
        if (!cardModel) return;
        if (!_stackController) return;

        CCLOG("Able To Move To TopCard");

        // 记录到 UndoManager
        models::UndoStep step;
        step.type = models::UndoType::PlayToStack;
        step.oldPos = cardView->getPosition();
        step.zorder = cardView->getLocalZOrder();
        _undoManager->pushStep(step);

        // 删除 playfield 中的 cardModel 数据
        services::FieldModelService::removeCardModelFromFieldModel(cardModel, _playFieldModel);
        _cardMap->removeCard(cardModel->cardId);
        
        // 向stack区域添加牌
        auto worldPos = cardView->getParent()->convertToWorldSpace(cardView->getPosition());
        cardView->retain();
        _playFieldView->removeCardView(cardView);
        _stackController->pushCardToTop(cardView, worldPos, cardModel); // 添加cardView->stackFieldView, 同时添加cardModel到stackFieldmodel
        cardView->release();
    }

    void PlayFieldController::undoMoveFromStack(models::UndoStep step)
    {
        if (!_stackController) return;

        auto cardView = _stackController->getTopCardView();
        auto cardModel = _stackController->getTopCardModel();
        if (!cardView) return;
        if (!cardModel) return;

        // 移动
        auto worldPos = cardView->getParent()->convertToWorldSpace(cardView->getPosition()); 
        auto startPos = _playFieldView->convertToNodeSpace(worldPos); 
        cardView->retain(); 
        _stackController->popTopCardView();               // StackField弹出当前的顶牌
        _stackController->removeCardView(cardView);       // StackField移除当前的顶牌
        _playFieldView->addChild(cardView, step.zorder);  // 将牌设置到 PlayField 中
        cardView->setPosition(startPos); cardView->moveToPosition(step.oldPos);  // 播放移动动画
        cardView->release();

        // 将 stackfield 的 CardModel 删除 并添加到 playfield 中
        cardModel->position = cardView->getPosition();
        _stackController->removeCardModel(cardModel);
        services::FieldModelService::addCardModelToFieldModel(cardModel, _playFieldModel);
        _cardMap->addCardModel(cardModel, cardModel->cardId);
        _cardMap->addCardView(cardView, cardModel->cardId);
    }


    void PlayFieldController::setStackController(StackFieldController* stackController) {
        _stackController = stackController;
    }

}
