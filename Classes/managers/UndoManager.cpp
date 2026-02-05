#include "UndoManager.h"

namespace managers {
    void UndoManager::pushStep(const models::UndoStep& step) {
        _undoStack.push(step);
    }

    bool UndoManager::canUndo() const { return !_undoStack.empty(); }

    models::UndoStep UndoManager::popStep() {
        auto step = _undoStack.top();
        _undoStack.pop();
        return step;
    }

}