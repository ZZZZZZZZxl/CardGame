
#pragma once
#include "models/CardCommonDefine.h"
#include "utils/Utils.h"
#include <string>

namespace services
{
    class CardRuleService {
    public:

        static bool canLink(CardFaceType face1, CardFaceType face2)
        {
            return gameUtils::Utils::getFaceDistance(face1, face2) == 1;
        }

    };
}