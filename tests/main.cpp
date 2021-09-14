#include "../src/Game.hpp"

#include <QtDebug>

int closeMatchForAI()
{
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
    if (output != board) {
        qDebug() << "dump output" << output;
        qDebug() << "expected" << board;
        return 1;
    }

    auto finished = g.isGameFinished();
    return (finished.first && finished.second == Game::GameFinished::AI) ? 0 : 1;
}

int bestMoveIsCentralCell()
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
    if (output != board) {
        qDebug() << "dump output" << output;
        qDebug() << "expected" << board;
        return 1;
    }

    auto finished = g.isGameFinished();
    return finished.first == false;
}

int main(int argc, char* argv[])
{
    int ret = 0 && closeMatchForAI() && bestMoveIsCentralCell();
    ret == 0 ? qDebug() << "all tests PASSED" : qDebug() << "test FAILED";
    return ret;
}
