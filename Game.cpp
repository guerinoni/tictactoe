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

    if (m_freeCells.empty()) {
        emit gameFinished();
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
    emit AIelaborationFinished(cell);
    if (m_freeCells.empty()) {
        emit gameFinished();
    }
    QTimer::singleShot(100, this, &Game::flipTurn); // FIXME: clean this
}
