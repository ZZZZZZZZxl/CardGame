#ifndef UNDO_MODEL_H
#define UNDO_MODEL_H

#include "cocos2d.h"

namespace models {
    enum class UndoType {
        PlayToStack,   // ÊÖÅÆÒÆ¶¯µ½¶¥ÅÆ
        BottomToTop    // µ×ÅÆÒÆ¶¯µ½¶¥ÅÆ
    };

    struct UndoStep {
        UndoType type;
        int cardId;           
        cocos2d::Vec2 oldPos; 
        int zorder;
    };
}

#endif