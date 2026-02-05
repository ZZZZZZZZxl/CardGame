#include "PlayFieldView.h"
#include "views/CardView.h"

using namespace cocos2d;

namespace views {

	bool PlayFieldView::init() {
		if (!Node::init()) return false;

		this->setContentSize(cocos2d::Size(1080, 1500));

		auto bg = cocos2d::LayerColor::create(
			cocos2d::Color4B(170, 121, 66, 255),
			1080,
			1500
		);
		this->addChild(bg, -1);

		return true;
	}

	void PlayFieldView::initWithCards(
		const std::vector<models::CardModel*>& cards,
		managers::CardDataMapManager* cardMapManager
	) {
		int zOrder = 0;
		for (auto cardData : cards) {

			// 创建CardView视图
			auto cardView = views::CardView::create(*cardData);
			cardView->setPosition(cardData->position);
			this->addChild(cardView, zOrder ++);

			// 在cardMapManager添加 cardId , cardView ,  cardModel的互相映射
			cardMapManager->addCardView(cardView, cardData->cardId);
			cardMapManager->addCardModel(cardData, cardData->cardId);

			// 添加点击监听
			auto listener = cocos2d::EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);

			listener->onTouchBegan = [cardView](cocos2d::Touch* t, cocos2d::Event*) {
				Vec2 localPoint = cardView->convertToNodeSpace(t->getLocation());
				Size size = cardView->getContentSize();
				Rect rect(-size.width / 2, -size.height / 2, size.width, size.height);
				return rect.containsPoint(localPoint);
			};
			
			listener->onTouchEnded = [this, cardView](cocos2d::Touch*, cocos2d::Event*) {
				if (_onCardClickCallback) {
					_onCardClickCallback(cardView);
				}
			};

			_eventDispatcher->addEventListenerWithSceneGraphPriority(
				listener, cardView
			);
		}
	}

	void PlayFieldView::removeCardView(views::CardView* cardView) {
		cardView->removeFromParent();
	}

	void PlayFieldView::setOnCardClickCallback(
		std::function<void(CardView* cardView)> callback
	) {
		_onCardClickCallback = callback;
	}


}
