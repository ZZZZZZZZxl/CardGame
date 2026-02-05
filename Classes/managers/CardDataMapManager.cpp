#include "CardDataMapManager.h"

namespace managers
{
    CardDataMapManager::CardDataMapManager() {}

    CardDataMapManager::~CardDataMapManager() {
        clear();
    }

    void CardDataMapManager::addCardModel(models::CardModel* model, int cardId) {
        if (!model) return;

        _idToModel[cardId] = model;
    }

    void CardDataMapManager::addCardView(views::CardView* view, int cardId) {
        if (!view) return;

        _idToView.insert(cardId, view);
        _viewToId[view] = cardId;
    }

    models::CardModel* CardDataMapManager::getModel(int cardId) {
        return _idToModel.at(cardId);
    }

    models::CardModel* CardDataMapManager::getModel(views::CardView* view) {
        int id = getCardId(view);
        return getModel(id);
    }

    views::CardView* CardDataMapManager::getView(int cardId) {
        return _idToView.at(cardId);
    }

    int CardDataMapManager::getCardId(views::CardView* view) {
        auto it = _viewToId.find(view);
        if (it != _viewToId.end()) {
            return it->second;
        }
        return -1; // 没找到返回-1
    }

    void CardDataMapManager::removeCard(int cardId) {
        auto view = getView(cardId);
        if (view) {
            _viewToId.erase(view);
            _idToView.erase(cardId);
        }
        _idToModel.erase(cardId);
    }


    void CardDataMapManager::clear() {
        _idToView.clear();
        _idToModel.clear();
        _viewToId.clear();
    }
}