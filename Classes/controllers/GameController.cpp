#include "GameController.h"

namespace controllers {

    GameController::GameController() {
        _gameModel = new models::GameModel();
        _playFieldController = new PlayFieldController();
        _stackController = new StackFieldController();
        _gameView = nullptr; 
        _undoManager = new managers::UndoManager();
    }

    void GameController::startGame(int levelId) {
        // 根据配置 初始化游戏 model 数据
        auto config = configs::LevelConfigLoader::loadLevelData(levelId);
        services::GameModelFromLevelGenerator::fillGameModel(config, _gameModel);

        // 创建主 GamveView
        _gameView = views::GameView::create();
        _gameView->retain();

        // 添加撤销回调函数
        _gameView->setOnUndoCallback([this]() {
            this->onUndoPressed();
            });

        // 初始化两个Field的视图
        _stackController->init(
            _gameModel->_stackFieldModel,
            _gameView,
            cocos2d::Vec2(0, 0),
            _undoManager
        );

        _playFieldController->init(
            _gameModel->_playFieldModel,
            _gameView,
            cocos2d::Vec2(0, 580),
            _undoManager
        );

        _playFieldController->setStackController(_stackController);
    }
    
    void GameController::onUndoPressed() {
        if (!_undoManager->canUndo()) return;

        auto step = _undoManager->popStep();
        if (step.type == models::UndoType::PlayToStack) {
            _playFieldController->undoMoveFromStack(step);
        }
        else if (step.type == models::UndoType::BottomToTop) {
            _stackController->undoBottomToTop(step);
        }
    }

    GameController::~GameController() {
        delete _gameModel;
        delete _playFieldController;
        delete _stackController;
        if (_gameView) _gameView->release();
    }
}