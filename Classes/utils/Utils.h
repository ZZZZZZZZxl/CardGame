#pragma once
#include "models/CardCommonDefine.h"
#include <algorithm> 
#include <cmath> 

namespace gameUtils
{
    class Utils {
    public: 
        static int getFaceDistance(CardFaceType face1, CardFaceType face2)
        {
            if (face1 == CFT_NONE || face2 == CFT_NONE) return 999;

            int f1 = static_cast<int>(face1);
            int f2 = static_cast<int>(face2);

            int linearDiff = std::abs(f1 - f2);
            // 计算环形差值
            int circularDiff = std::min(linearDiff, 13 - linearDiff);

            return circularDiff;
        }

        // 获取对应的花色
        static std::string getFaceString(CardFaceType face) {
            switch (face) {
            case CFT_ACE:   return "A";
            case CFT_TWO:   return "2";
            case CFT_THREE: return "3";
            case CFT_FOUR:  return "4";
            case CFT_FIVE:  return "5";
            case CFT_SIX:   return "6";
            case CFT_SEVEN: return "7";
            case CFT_EIGHT: return "8";
            case CFT_NINE:  return "9";
            case CFT_TEN:   return "10";
            case CFT_JACK:  return "J";
            case CFT_QUEEN: return "Q";
            case CFT_KING:  return "K";
            default: return "?";
            }
        }

        // 判断花色对应的颜色
        static std::string getColorBySuit(CardSuitType suit) {
            return (suit == CST_DIAMONDS || suit == CST_HEARTS) ? "red" : "black";
        }

        // 判断花色对应的文件名
        static std::string getSuitFileName(CardSuitType suit)
        {
            switch (suit)
            {
            case CST_CLUBS: return "club";
            case CST_DIAMONDS: return "diamond";
            case CST_HEARTS: return "heart";
            case CST_SPADES: return "spade";
            }
        }
    };
}