#pragma once

#include <QObject>

class Game : public QObject {
    Q_OBJECT

public:
    Game();
    explicit Game(QList<QChar> board, QList<quint8> freeCells);
    explicit Game(quint8 rows, quint8 column, quint8 consecutiveForWin);

    Q_INVOKABLE bool isMoveAllowed(quint8 cell);
    Q_INVOKABLE void setHumanMove(quint8 cell);
    Q_INVOKABLE void emptyBoard(void);

    enum class GameFinished {
        Human,
        AI,
        EndOfMoves,
    };
    Q_ENUMS(GameFinished)

    void makeAImove();
    QPair<bool, GameFinished> isGameFinished();

    static constexpr QChar kHumanSymbol { 'X' };
    static constexpr QChar kAiSymbol { 'O' };

signals:
    void aiElaborationFinished(quint8 cell);
    void gameFinished(GameFinished mode);

private:
    enum class Turn {
        Human,
        AI
    };

    quint8 m_rows { 3 };
    quint8 m_columns { 3 };
    quint8 m_consecutiveForWin { 3 };
    QList<QChar> m_board;
    QList<quint8> m_freeCells;
    Game::Turn m_turn = Game::Turn::Human;

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

    QList<QChar> dumpBoard() const;

    friend class MatchDecision3x3;
};
