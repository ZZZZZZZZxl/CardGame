#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
#include <vector>
#include <functional>
#include "views/CardView.h"
#include "models/FieldModel.h"
#include "managers/CardDataMapManager.h"

namespace views {

	class PlayFieldView : public cocos2d::Node {
	public:

		CREATE_FUNC(PlayFieldView);
		virtual bool init() override;

		void initWithCards(const std::vector<models::CardModel*>& cards, managers::CardDataMapManager* cardMapManager);

		void removeCardView(views::CardView* cardView);

		void setOnCardClickCallback(
			std::function<void(views::CardView* cardView)> callback
		);


	private:
		std::function<void(views::CardView* cardView)> _onCardClickCallback;
	};
}