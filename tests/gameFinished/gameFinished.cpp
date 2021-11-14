#include "../../src/Game.hpp"

#include <QtDebug>
#include <QtTest>

class GameFinished : public QObject {
    Q_OBJECT

private slots:
    void boardIsFull();
};

void GameFinished::boardIsFull()
{
    QList<QChar> board {
        'O', 'X', 'O',
        'X', 'X', 'O',
        'X', 'O', 'X'
    };
    QList<quint8> freeCells {};
    Game g(board, freeCells);

    auto result = g.isGameFinished();
    QVERIFY(result.first);
}

QTEST_APPLESS_MAIN(GameFinished)
#include "gameFinished.moc"
