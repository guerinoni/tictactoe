#include "../src/Game.hpp"

#include <QtDebug>
#include <QtTest>

class MatchDecision3x3 : public QObject {
    Q_OBJECT

private slots:
    void only1moveToWin();
    void checkBestMoveAfterFirstMoveOfHuman();
};

void MatchDecision3x3::only1moveToWin()
{
    // TODO: add other case for 1 move remaining.
    QList<QChar> board {
        'O', 'X', 'O',
        'X', 'X', 'O',
        'X', ' ', ' '
    };
    QList<quint8> freeCells { 7, 8 };
    Game g(board, freeCells);
    g.makeAImove();

    board[8] = 'O';
    auto output = g.dumpBoard();
    QCOMPARE(output, board);

    auto finished = g.isGameFinished();
    QVERIFY(finished.first);
    QCOMPARE(finished.second, Game::GameFinished::AI);
}

void MatchDecision3x3::checkBestMoveAfterFirstMoveOfHuman()
{
    QList<QChar> board {
        ' ', 'X', ' ',
        ' ', ' ', ' ',
        ' ', ' ', ' '
    };
    QList<quint8> freeCells { 0, 2, 3, 4, 5, 6, 7, 8 };
    Game g(board, freeCells);
    g.makeAImove();

    board[4] = 'O';
    auto output = g.dumpBoard();
    QCOMPARE(output, board);

    auto finished = g.isGameFinished();
    QVERIFY(!finished.first);
}

QTEST_MAIN(MatchDecision3x3)
#include "matchDecision3x3.moc"
