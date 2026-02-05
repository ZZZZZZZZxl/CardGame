#pragma once
#include <string>

// 提供卡牌 UI 资源的路径
class CardResConfig {
public:
    // 背景固定路径
    static std::string getCardBackGroundPath() {
        return "res/card_general.png";
    }

    // 获取大数字图片路径
    static std::string getBigNumberPath(const std::string& color, const std::string& face) {
        return "res/number/big_" + color + "_" + face + ".png";
    }

    // 获取左上角小数字图片路径
    static std::string getSmallNumberPath(const std::string& color, const std::string& face) {
        return "res/number/small_" + color + "_" + face + ".png";
    }

    // 获取花色图片路径
    static std::string getSuitPath(std::string& suitFile) {
        return "res/suits/" + suitFile + ".png";
    }

};