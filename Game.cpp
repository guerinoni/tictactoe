#include "Game.hpp"

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
    m_freeCells.remove(cell);
    flipTurn();
    qDebug() << m_freeCells;
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
