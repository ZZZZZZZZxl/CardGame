#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include "views/PlayFieldView.h"
#include "StackFieldController.h"
#include "models/FieldModel.h"
#include "managers/UndoManager.h"
#include "services/FieldModelService.h"
#include "services/CardRuleService.h"
#include "managers/CardDataMapManager.h"
#include <vector>

namespace controllers {

	class PlayFieldController {
	public:
		PlayFieldController() = default;
		~PlayFieldController() = default;

		/*
		* 初始化 PlayFieldController
		* 1. _playFieldModel 初始化
		* 2. 设置自己为 parent（由 GameController 传入 GamveView）的Child
		* 3. 初始化 _cardMap 并让 _playFiedView 为 _cardMap 添加 cardId, CardView, CardModel之间的映射关系
		* 4. 传入_playFieldModel->cards 初始化 _playFiedView 并为其设置卡牌回调函数为 handleCardClick
		*/
		void init(
			models::FieldModel* playFieldModel,
			cocos2d::Node* parent,
			const cocos2d::Vec2& position,
			managers::UndoManager* undoManager
		);

		
		void setStackController(controllers::StackFieldController* stack);
		void undoMoveFromStack(models::UndoStep step);

	private:
		bool canMoveToStack(views::CardView* cardView, models::CardModel* cardModel);
		void replaceTrayWithPlayFieldCard(views::CardView* cardView, models::CardModel* cardModel);
		void handleCardClick(views::CardView* cardView);

	private:
		views::PlayFieldView* _playFieldView = nullptr;
		controllers::StackFieldController* _stackController = nullptr;

		models::FieldModel* _playFieldModel = nullptr;
		managers::UndoManager* _undoManager = nullptr;
		managers::CardDataMapManager* _cardMap = nullptr;
	};

}
