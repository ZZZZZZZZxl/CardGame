#include "GameView.h"
using namespace cocos2d;
namespace views {
    bool GameView::init() {
        if (!Scene::init()) return false;

        //// === 撤销按钮 ===
        auto undoBtn = ui::Button::create();
        undoBtn->setTitleText("UNDO");
        undoBtn->setTitleFontSize(40);
        undoBtn->setContentSize(Size(200, 100));
        undoBtn->setScale9Enabled(true);

        undoBtn->setPosition(Vec2(900, 290));

        undoBtn->addClickEventListener([this](Ref*) {
            if (_onUndoCallback) {
                _onUndoCallback();
            }
            });

        this->addChild(undoBtn, 1000); // UI 放最上层

        return true;
    }

    void GameView::setOnUndoCallback(std::function<void()> callback) {
        _onUndoCallback = callback;
    }
}