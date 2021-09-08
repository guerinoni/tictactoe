#include "Game.hpp"

#include <QRandomGenerator>
#include <QTimer>
#include <QtDebug>

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

    QTimer::singleShot(100, this, &Game::flipTurn); // FIXME: clean this
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
