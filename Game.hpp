#pragma once

#include <QMap>
#include <QObject>

class Game : public QObject {
    Q_OBJECT

public:
    [[nodiscard]] QString currentTurnSymbol() const noexcept;

    void setHumanMove(quint8 cell);

    enum class GameFinished {
        Human,
        AI,
        EndOfMoves,
    };

signals:
    void AIelaborationFinished(quint8 cell);
    void gameFinished(GameFinished mode);

private:
    enum class Turn {
        Human,
        AI
    };

    Turn m_turn { Turn::Human }; // TODO: make this random

    QList<QChar> m_board { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    QMap<quint8, bool> m_freeCells { { 0, true }, { 1, true }, { 2, true }, { 3, true }, { 4, true }, { 5, true }, { 6, true }, { 7, true }, { 8, true } };

    void flipTurn();
    void makeAImove();
    QPair<bool, GameFinished> isGameFinished();

    qint32 evaluateMove();
    quint32 evaluateWin(GameFinished whoWin);
    quint8 possibleWinFor(Game::Turn player);
    qint32 minVal(quint8 depth);
    qint32 maxVal(quint8 depth);
};
