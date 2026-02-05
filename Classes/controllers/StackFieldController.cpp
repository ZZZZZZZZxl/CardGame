#include "StackFieldController.h"

namespace controllers {

    void StackFieldController::init(
        models::FieldModel* stackFieldModel,
        cocos2d::Node* parent,
        const cocos2d::Vec2& position,
        managers::UndoManager* undoManager
    ) {
        if (!parent) return;

        _stackView = views::StackFieldView::create();
        _stackView->setPosition(position);
        parent->addChild(_stackView,1);

        _undoManager = undoManager;
        _cardMap = new managers::CardDataMapManager();

        auto cards = stackFieldModel->_cards;
        _stackFieldModel = stackFieldModel;
        _stackView->initWithCards(cards, _cardMap);
        _stackView->setOnBottomCardClickCallback(
            [this](views::CardView* cardView) {
                this->bringBottomCardToTop(cardView);
            }
        );
    }

     models::CardModel* StackFieldController::getTopCardModel()  {
        if (!_stackView) return nullptr;

        auto topCardView = _stackView->getTopCardView();
        if (!topCardView) return nullptr;


        return _cardMap->getModel(topCardView);
    }

    void StackFieldController::pushCardToTop(
        views::CardView* cardView,
        const cocos2d::Vec2& worldPos,
        models::CardModel* cardModel
    ) {
        if (!_stackView || !cardView) return;

        //  添加 cardModel 到 StackFieldModel 中
        services::FieldModelService::addCardModelToFieldModel(cardModel, _stackFieldModel);
        _cardMap->addCardModel(const_cast<models::CardModel*>(cardModel), cardModel->cardId);
        _cardMap->addCardView(cardView, cardModel->cardId);

        // 临时挂载到主视图移动
        Vec2 worldStartPos = worldPos;
        auto mainView = _stackView->getParent();
        cardView->retain(); 
        cardView->removeFromParent();
        mainView->addChild(cardView, 1000); 
        cardView->setPosition(mainView->convertToNodeSpace(worldStartPos));
        Vec2 targetPos(services::FieldLayoutService::getStackFieldViewCenterX() + services::FieldLayoutService::getStackFieldGapWidth(), services::FieldLayoutService::getStackFieldViewBaseY());
        cardView->moveToPosition(targetPos);

        // 修改CardModel存储的坐标
        cardModel->position = targetPos;

        // 动画结束后的逻辑回调
        float duration = 0.3f;
        auto delay = cocos2d::DelayTime::create(duration);
        auto callback = cocos2d::CallFunc::create([this, cardView, targetPos]() {
            cardView->removeFromParent();
            _stackView->addTopCardView(cardView);
            cardView->setPosition(targetPos);
            cardView->release(); // 释放 retain 占用的计数
            });

        auto seq = cocos2d::Sequence::create(delay, callback, nullptr);
        cardView->runAction(seq);
    }


    void StackFieldController::bringBottomCardToTop(views::CardView* cardView)
    {
        if (!_stackView || !cardView) return;
        auto canMoveCard = _stackView->getTopBottomCardView();
        if (canMoveCard != cardView) return;

        // 记录撤销操作
        models::UndoStep step;
        step.type = models::UndoType::BottomToTop;
        step.oldPos = cardView->getPosition();
        step.zorder = cardView->getLocalZOrder();
        _undoManager->pushStep(step);

        // 修改CardModel数据
        Vec2 targetPos(services::FieldLayoutService::getStackFieldViewCenterX() + services::FieldLayoutService::getStackFieldGapWidth(), services::FieldLayoutService::getStackFieldViewBaseY());
        auto cardModel = _cardMap->getModel(cardView);
        cardModel->position = targetPos;

        // 执行移动
        cardView->retain();
        _stackView->removeBottomTopCard();
        _stackView->addTopCardView(cardView);
        cardView->moveToPosition(targetPos);
        cardView->release();
    }

    void StackFieldController::undoBottomToTop(models::UndoStep step)
    {
        auto cardView = getTopCardView();
        if (!cardView) return;

        // 修改对应的CardModel中存储的坐标
        auto cardModel = _cardMap->getModel(cardView);
        cardModel->position = step.oldPos;

        // 先播放动画
        _stackView->popTopCardView();
        cardView->moveToPosition(step.oldPos);

        // 动画播放完再添加CardView到底牌 防止立刻更改zOrder导致卡片被覆盖
        float duration = 0.3f;
        auto delay = cocos2d::DelayTime::create(duration);
        auto callback = cocos2d::CallFunc::create([this, cardView, step]() {
            _stackView->addBottomCardView(cardView, step.zorder);
        });
        auto seq = cocos2d::Sequence::create(delay, callback, nullptr);
        cardView->runAction(seq);
    }

    void StackFieldController::removeCardModel(const models::CardModel* card)
    {
        if (!card) return;

        services::FieldModelService::removeCardModelFromFieldModel(card, _stackFieldModel);
        _cardMap->removeCard(card->cardId);
    }

    views::CardView* StackFieldController::getTopCardView()
    {
        return _stackView->getTopCardView();
    }

    void StackFieldController::popTopCardView()
    {
        _stackView->popTopCardView();
    }

    void StackFieldController::removeCardView(views::CardView* cardView)
    {
        cardView->removeFromParent();
    }

    
}
