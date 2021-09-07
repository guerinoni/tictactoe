#pragma once

#include <QHash>
#include <QObject>

class Game : public QObject {
    Q_OBJECT

public:
    [[nodiscard]] QString currentTurnSymbol() const noexcept;

    void setHumanMove(quint8 cell);

signals:
    void AIelaborationFinished(quint8 cell);
    void gameFinished();

private:
    enum class Turn {
        Human,
        AI
    };

    Turn m_turn { Turn::Human }; // TODO: make this random

    QHash<quint8, bool> m_freeCells { { 0, true }, { 1, true }, { 2, true }, { 3, true }, { 4, true }, { 5, true }, { 6, true }, { 7, true }, { 8, true } };

    void flipTurn();
    void makeAImove();
};
