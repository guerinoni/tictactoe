#include "../src/Game.hpp"

#include <QtDebug>

enum TestResult {
    PASSED,
    FAILED
};

TestResult case1()
{
    QList<QChar> board {
        'X', 'X', 'O',
        'X', 'X', 'O',
        'O', ' ', ' '
    };
    QList<quint8> freeCells { 7, 8 };
    Game g(board, freeCells);
    g.makeAImove();

    board[8] = 'O';
    auto output = g.dumpBoard();
    if (output != board) {
        qDebug() << "dump output" << output;
        qDebug() << "expected" << board;
        return FAILED;
    }

    auto finished = g.isGameFinished();
    return finished.first && finished.second == Game::GameFinished::AI ? PASSED : FAILED;
}

int main(int argc, char* argv[])
{
    TestResult ret = PASSED;
    ret = case1() == PASSED ? PASSED : FAILED;
    ret == PASSED ? qDebug() << "all tests PASSED" : qDebug() << "test FAILED";
    return ret;
}
