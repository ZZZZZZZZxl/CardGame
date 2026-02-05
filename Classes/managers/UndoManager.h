#pragma once

#include <stack>
#include "models/UndoModel.h"

namespace managers {

    class UndoManager {
    public:
        void pushStep(const models::UndoStep& step);
        bool canUndo() const;
        models::UndoStep popStep();

    private:
        std::stack<models::UndoStep> _undoStack;
    };
}
