#pragma once

#include <QObject>

class Game : public QObject {
    Q_OBJECT

public:
    Game() = default;
    explicit Game(QList<QChar> board, QList<quint8> freeCells);

    [[nodiscard]] QString currentTurnSymbol() const noexcept;

    void setHumanMove(quint8 cell);

    enum class GameFinished {
        Human,
        AI,
        EndOfMoves,
    };

    void makeAImove();
    QPair<bool, GameFinished> isGameFinished();

    QList<QChar> dumpBoard() const;

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
    QList<quint8> m_freeCells { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    void flipTurn();

    qint32 evaluateMove();
    qint32 evaluateWin(GameFinished whoWin);
    quint8 possibleWinFor(Game::Turn player);

    struct CalculatedMove {
        // value of the move calculated based on points that we assign for a specific move.
        qint32 value;

        // index of board for that move calculated by the algorigthm.
        quint8 index;
    };

    CalculatedMove minVal(quint8 depth);
    CalculatedMove maxVal(quint8 depth);
};
