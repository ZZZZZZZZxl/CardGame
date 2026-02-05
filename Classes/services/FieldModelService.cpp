#include "FieldModelService.h"

namespace services
{
	void FieldModelService::removeCardModelFromFieldModel(const models::CardModel* card, models::FieldModel* model)
	{
		// 从filedmodel中 删除 cardmodel 的数据
		auto& cards = model->_cards;
		auto it = std::find(cards.begin(), cards.end(), card);

		if (it != cards.end()) cards.erase(it);
	}

	void FieldModelService::addCardModelToFieldModel(const models::CardModel* card, models::FieldModel* model)
	{
		auto& cards = model->_cards;
		cards.push_back(const_cast<models::CardModel*>(card));
	}
	
}