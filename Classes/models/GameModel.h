#pragma once
#include <vector>
#include "views/CardView.h"
#include "FieldModel.h"
#include "FieldModel.h"

namespace models {
    class GameModel {
    public:
        FieldModel* _playFieldModel = nullptr;
        FieldModel* _stackFieldModel = nullptr;

        GameModel() {
            _playFieldModel = new FieldModel();
            _stackFieldModel = new FieldModel();
        }

        void reset() {
            if (_playFieldModel) _playFieldModel->reset();
            if (_stackFieldModel) _stackFieldModel->reset();
        }

        ~GameModel() {
            if (_playFieldModel) { _playFieldModel->reset(); delete _playFieldModel; }
            if (_stackFieldModel) { _stackFieldModel->reset(); delete _stackFieldModel; }
        }
    };
}
