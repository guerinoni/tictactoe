#include "../src/Game.hpp"

#include <QtDebug>
#include <QtTest>

class MatchDecision3x3 : public QObject {
    Q_OBJECT

private slots:
    void firstMoveForAI();
    void only1moveToWin();
    void checkBestMoveAfterFirstMoveOfHuman();
    void preventHumanWin();
};

void MatchDecision3x3::firstMoveForAI()
{
    QList<QChar> board {
        ' ', ' ', ' ',
        ' ', ' ', ' ',
        ' ', ' ', ' '
    };
    QList<quint8> freeCells { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    Game g(board, freeCells);
    g.makeAImove();

    board[4] = 'O';
    auto output = g.dumpBoard();
    QCOMPARE(output, board);

    auto finished = g.isGameFinished();
    QVERIFY(!finished.first);
}

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

void MatchDecision3x3::preventHumanWin()
{
    struct testCase {
        QList<QChar> initialBoard;
        QList<quint8> initialFreecells;
        QList<QChar> expectedBoard;
        bool expectedGameFinished;
    };

    QList<testCase> tests {
        { { 'X', 'X', ' ', ' ', 'O', ' ', ' ', ' ', ' ' }, { 2, 3, 5, 6, 7, 8 }, {
                                                                                     'X',
                                                                                     'X',
                                                                                     'O',
                                                                                     ' ',
                                                                                     'O',
                                                                                     ' ',
                                                                                     ' ',
                                                                                     ' ',
                                                                                     ' ',
                                                                                 },
            false },
        { { ' ', ' ', 'X', ' ', 'O', 'X', ' ', ' ', ' ' }, { 0, 1, 3, 6, 7, 8 }, {
                                                                                     ' ',
                                                                                     ' ',
                                                                                     'X',
                                                                                     ' ',
                                                                                     'O',
                                                                                     'X',
                                                                                     ' ',
                                                                                     ' ',
                                                                                     'O',
                                                                                 },
            false },
        { { 'X', 'X', 'O', 'X', 'O', ' ', ' ', ' ', ' ' }, { 5, 6, 7, 8 }, {
                                                                               'X',
                                                                               'X',
                                                                               'O',
                                                                               'X',
                                                                               'O',
                                                                               ' ',
                                                                               'O',
                                                                               ' ',
                                                                               ' ',
                                                                           },
            true },
    };

    for (const auto& t : tests) {
        Game game(t.initialBoard, t.initialFreecells);
        game.makeAImove();
        QCOMPARE(game.dumpBoard(), t.expectedBoard);
        const auto finished = game.isGameFinished();
        QCOMPARE(t.expectedGameFinished, finished.first);
    }
}

QTEST_MAIN(MatchDecision3x3)
#include "matchDecision3x3.moc"
