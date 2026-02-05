#pragma once
#include <vector>
#include "CardModel.h"
#include "views/CardView.h"

namespace models {
    class FieldModel {
    public:
        std::vector<CardModel*> _cards;
        void reset() {
            for (auto c : _cards) delete c;
            _cards.clear();
        }

        ~FieldModel() { reset(); }
    private:
    };
}