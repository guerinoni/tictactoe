#pragma once

#include <QObject>

class Game : public QObject {
    Q_OBJECT

public:
    [[nodiscard]] QString currentTurnSymbol() const noexcept;

    void setHumanMove(quint8 cell);

private:
    enum class Turn {
        Human,
        AI
    };

    Turn m_turn { Turn::Human }; // TODO: make this random

    QList<quint8> m_freeCells { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    void flipTurn();
};
