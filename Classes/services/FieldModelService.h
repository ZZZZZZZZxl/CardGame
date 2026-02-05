#pragma once
#include "models/CardModel.h"
#include "models/FieldModel.h"

namespace services {
    class FieldModelService {
    public:
        static void removeCardModelFromFieldModel(const models::CardModel* card, models::FieldModel* model);
        static void addCardModelToFieldModel(const models::CardModel* card, models::FieldModel* model);
    };
}