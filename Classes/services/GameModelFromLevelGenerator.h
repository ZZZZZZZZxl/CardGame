#pragma once

#include "configs/LevelConfig.h"
#include "models/GameModel.h"

namespace services
{
    class GameModelFromLevelGenerator {
    public:

        /*
        * 根据 LevelConfig 进行读取关卡信息并存储到 GameModel中, 为每个CardModel 提供全局的 cardId
        * 由GameController调用，传入gameModel
        * 
        * 1.根据 config 信息生成 PlayField 的 CardModel* 信息，并添加到 gameModel->_playFieldModel
        * 2.生成 StackField 的 CardModel* 信息，并添加到 gameModel->stackFieldModel
        */
        static void fillGameModel(const configs::LevelConfig& config, models::GameModel* gameModel) {
            if (!gameModel) return;

            // 清理旧数据（如果是重新开始关卡）
            gameModel->reset();

            int nextCardId = 1; // 从1开始生成全局唯一的卡牌ID

            // 1. 生成 Playfield (桌面/底牌区)
            for (const auto& unit : config.playfield) {
                auto card = new models::CardModel(
                    nextCardId,
                    static_cast<CardSuitType>(unit.cardSuit),
                    static_cast<CardFaceType>(unit.cardFace),
                    unit.position
                );
                gameModel->_playFieldModel->_cards.push_back(card);

                nextCardId++;
            }

            // 2. 生成 Stack (手牌区)
            for (const auto& unit : config.stack) {
                auto card = new models::CardModel(
                    nextCardId,
                    static_cast<CardSuitType>(unit.cardSuit),
                    static_cast<CardFaceType>(unit.cardFace),
                    unit.position
                );
                gameModel->_stackFieldModel->_cards.push_back(card);
                nextCardId++;
            }
        }
    };
}