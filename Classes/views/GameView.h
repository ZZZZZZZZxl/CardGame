#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <functional>
namespace views {
    class GameView : public cocos2d::Scene {
    public:
        CREATE_FUNC(GameView);
        virtual bool init() override;

        void setOnUndoCallback(std::function<void()> callback);

    private:
        std::function<void()> _onUndoCallback;
    };
}