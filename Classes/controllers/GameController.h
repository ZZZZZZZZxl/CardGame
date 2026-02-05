#pragma once
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/GameView.h"
#include "PlayFieldController.h" 
#include "StackFieldController.h"  
#include "managers/UndoManager.h"
#include "models/UndoModel.h"
#include "configs/LevelConfigLoader.h"
#include "services/GameModelFromLevelGenerator.h"
#include "views/PlayFieldView.h"
#include "views/StackFieldView.h"

namespace controllers {
    class GameController {
    public:
        GameController();
        ~GameController();

        void startGame(int levelId); // ºËÐÄÈë¿Ú
        views::GameView* getGameView() { return _gameView; }

    private:
        void onUndoPressed();

    private:
        models::GameModel* _gameModel;
        views::GameView* _gameView;

        PlayFieldController* _playFieldController;
        StackFieldController* _stackController;
        managers::UndoManager* _undoManager;
    };
}