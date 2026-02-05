#include "LevelConfigLoader.h"

namespace configs {

    LevelConfig LevelConfigLoader::loadLevelData(int levelId) {
        LevelConfig config;
        std::string filePath =
            cocos2d::FileUtils::getInstance()->fullPathForFilename(
                StringUtils::format("res/levels/level_%d.json", levelId)
            );
        // 1. 获取文件内容
        std::string content = FileUtils::getInstance()->getStringFromFile(filePath);

        if (content.empty()) {
            CCLOG("LevelConfigLoader: File is empty or not found at %s", filePath.c_str());
            return config;
        }

        // 2. 解析 JSON 字符串
        rapidjson::Document doc;
        doc.Parse(content.c_str());

        if (doc.HasParseError()) {
            CCLOG("LevelConfigLoader: JSON parse error in %s. Error code: %d", filePath.c_str(), doc.GetParseError());
            return config;
        }

        // 3. 解析 Playfield (底牌/桌面牌区)
        if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
            const rapidjson::Value& playfieldArray = doc["Playfield"];
            for (rapidjson::SizeType i = 0; i < playfieldArray.Size(); ++i) {
                const rapidjson::Value& item = playfieldArray[i];

                CardUnitConfig unit;
                unit.cardFace = item["CardFace"].GetInt();
                unit.cardSuit = item["CardSuit"].GetInt();

                // 解析 Position 嵌套对象
                if (item.HasMember("Position")) {
                    unit.position.x = item["Position"]["x"].GetFloat();
                    unit.position.y = item["Position"]["y"].GetFloat();
                }

                config.playfield.push_back(unit);
            }
        }

        // 4. 解析 Stack (手牌区)
        if (doc.HasMember("Stack") && doc["Stack"].IsArray()) {
            const rapidjson::Value& stackArray = doc["Stack"];
            for (rapidjson::SizeType i = 0; i < stackArray.Size(); ++i) {
                const rapidjson::Value& item = stackArray[i];

                CardUnitConfig unit;
                unit.cardFace = item["CardFace"].GetInt();
                unit.cardSuit = item["CardSuit"].GetInt();

                if (item.HasMember("Position")) {
                    unit.position.x = item["Position"]["x"].GetFloat();
                    unit.position.y = item["Position"]["y"].GetFloat();
                }

                config.stack.push_back(unit);
            }
        }

        CCLOG("LevelConfigLoader: Successfully loaded %zu playfield cards and %zu stack cards.",
            config.playfield.size(), config.stack.size());

        return config;
    }
}