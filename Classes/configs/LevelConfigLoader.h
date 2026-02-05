#pragma once

#include <string>
#include "LevelConfig.h"
#include "cocos2d.h"
#include "json/document.h"

using namespace cocos2d;

namespace configs {

    // LevelConfigLoader - 配置加载逻辑类 负责读取 JSON 文件，并将其解析为静态的 LevelConfig 结构体
    class LevelConfigLoader {
    public:
        // 加载关卡数据 返回LevelConfig结构体数据
        static LevelConfig loadLevelData(int levelId);

    private:
        
        LevelConfigLoader() = delete;
    };

} 