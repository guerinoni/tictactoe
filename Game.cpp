#include "Game.hpp"

#include <QRandomGenerator>

QString Game::currentTurnSymbol() const noexcept
{
    if (m_turn == Turn::Human)
        return "X";
    if (m_turn == Turn::AI)
        return "O";

    assert(false);
    return "";
}

void Game::setHumanMove(quint8 cell)
{
    if (m_turn != Turn::Human)
        return;

    m_freeCells.remove(cell);
    m_board[cell] = currentTurnSymbol().at(0);

    auto end
        = isGameFinished();
    if (end.first) {
        emit gameFinished(end.second);
        return;
    }

    flipTurn();
    makeAImove();
}

void Game::flipTurn()
{
    if (m_turn == Turn::Human)
        m_turn = Turn::AI;
    else if (m_turn == Turn::AI)
        m_turn = Turn::Human;
    else
        assert(false);
}

void Game::makeAImove()
{
    if (m_turn != Turn::AI)
        return;

    auto cell = m_freeCells.begin().key();
    m_freeCells.remove(cell);
    m_board[cell] = currentTurnSymbol().at(0);
    emit AIelaborationFinished(cell);

    auto end = isGameFinished();
    if (end.first) {
        emit gameFinished(end.second);
        return;
    }

    flipTurn();
}

QPair<bool, Game::GameFinished> Game::isGameFinished()
{
    if ((m_board[0] != ' ' && m_board[0] == m_board[1] && m_board[1] == m_board[2])
        || (m_board[0] != ' ' && m_board[0] == m_board[3] && m_board[3] == m_board[6])
        || (m_board[0] != ' ' && m_board[0] == m_board[4] && m_board[4] == m_board[8])
        || (m_board[1] != ' ' && m_board[1] == m_board[4] && m_board[4] == m_board[7])
        || (m_board[2] != ' ' && m_board[2] == m_board[5] && m_board[5] == m_board[8])
        || (m_board[2] != ' ' && m_board[2] == m_board[4] && m_board[4] == m_board[6])
        || (m_board[3] != ' ' && m_board[3] == m_board[4] && m_board[4] == m_board[5])
        || (m_board[6] != ' ' && m_board[6] == m_board[7] && m_board[7] == m_board[8])) {
        return qMakePair<bool, Game::GameFinished>(true, static_cast<Game::GameFinished>(m_turn));
    }

    if (m_freeCells.empty()) {
        return qMakePair<bool, Game::GameFinished>(true, Game::GameFinished::EndOfMoves);
    }

    return qMakePair<bool, Game::GameFinished>(false, Game::GameFinished::EndOfMoves);
}

qint32 Game::evaluateMove()
{
    return possibleWinFor(Game::Turn::AI) - possibleWinFor(Game::Turn::Human);
}

quint32 Game::evaluateWin(GameFinished whoWin)
{
    if (whoWin == GameFinished::Human)
        return -1000;
    if (whoWin == GameFinished::AI)
        return 1000;
    return 0;
}

quint8 Game::possibleWinFor(Game::Turn player)
{
    QChar symbolOpponent = player == Game::Turn::Human ? 'O' : 'X';
    quint8 counterPossibleWin = 0;

    // horizontal possible wins
    if (m_board[0] != symbolOpponent && m_board[1] != symbolOpponent && m_board[2] != symbolOpponent)
        counterPossibleWin++;
    if (m_board[3] != symbolOpponent && m_board[4] != symbolOpponent && m_board[5] != symbolOpponent)
        counterPossibleWin++;
    if (m_board[6] != symbolOpponent && m_board[7] != symbolOpponent && m_board[8] != symbolOpponent)
        counterPossibleWin++;

    // verticalpossible wins
    if (m_board[0] != symbolOpponent && m_board[3] != symbolOpponent && m_board[6] != symbolOpponent)
        counterPossibleWin++;
    if (m_board[1] != symbolOpponent && m_board[4] != symbolOpponent && m_board[7] != symbolOpponent)
        counterPossibleWin++;
    if (m_board[2] != symbolOpponent && m_board[5] != symbolOpponent && m_board[8] != symbolOpponent)
        counterPossibleWin++;

    // diagol wins
    if (m_board[0] != symbolOpponent && m_board[4] != symbolOpponent && m_board[8] != symbolOpponent)
        counterPossibleWin++;
    if (m_board[2] != symbolOpponent && m_board[4] != symbolOpponent && m_board[6] != symbolOpponent)
        counterPossibleWin++;

    return counterPossibleWin;
}

// depth is how many move in advance we are trying to calculate.
// If the game is finished the returned value is multiplied with the current depth where is found in order
// have a different wight based on what depth found winner moves. (+1 because last depth is 0 and any number *0...)
qint32 Game::minVal(quint8 depth)
{
    auto finished = isGameFinished();
    if (finished.first)
        return (depth + 1) * evaluateWin(finished.second);

    if (depth == 0) // limit of max depth that can be calculated, return estimation of wins
        return evaluateMove();

    auto min = std::numeric_limits<qint32>::max();
    for (auto it = m_freeCells.begin(); it != m_freeCells.end(); ++it) {
        auto cell = it.key();
        m_freeCells.remove(cell);
        m_board[cell] = 'O';
        min = std::min(min, maxVal(depth - 1));
        m_board[cell] = ' ';
        m_freeCells[cell] = true;
    }

    return min;
}

qint32 Game::maxVal(quint8 depth)
{
    auto finished = isGameFinished();
    if (finished.first)
        return (depth + 1) * evaluateWin(finished.second);

    if (depth == 0)
        return evaluateMove();

    auto max = std::numeric_limits<qint32>::max();
    for (auto it = m_freeCells.begin(); it != m_freeCells.end(); ++it) {
        auto cell = it.key();
        m_freeCells.remove(cell);
        m_board[cell] = 'O';
        max = std::max(max, minVal(depth - 1));
        m_board[cell] = ' ';
        m_freeCells[cell] = true;
    }

    return max;
}
