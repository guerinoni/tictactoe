#include "Game.hpp"

#include <QRandomGenerator>
#include <QtDebug>

Game::Game(QList<QChar> board, QList<quint8> freeCells)
    : m_board { std::move(board) }
    , m_freeCells { std::move(freeCells) }
{
}

void Game::emptyBoard(void)
{
    m_board = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    m_freeCells = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
}

bool Game::isMoveAllowed(quint8 cell)
{
    return m_freeCells.contains(cell) && m_turn == Game::Turn::Human && !isGameFinished().first;
}

void Game::setHumanMove(quint8 cell)
{
    auto item = std::find(m_freeCells.begin(), m_freeCells.end(), cell);
    m_freeCells.removeOne(*item);
    m_board[cell] = kHumanSymbol;

    auto end = isGameFinished();
    if (end.first) {
        emit gameFinished(end.second);
        return;
    }

    m_turn = Game::Turn::AI;
    makeAImove();
}

void Game::makeAImove()
{
    auto bestMove = maxVal(5, 0, 255);
    m_freeCells.removeOne(bestMove.index);
    m_board[bestMove.index] = kAiSymbol;

    emit aiElaborationFinished(bestMove.index);
    m_turn = Game::Turn::Human;

    auto end = isGameFinished();
    if (end.first) {
        emit gameFinished(end.second);
    }
}

QPair<bool, Game::GameFinished> Game::isGameFinished()
{
    if ((m_board[0] == m_board[1] && m_board[1] == m_board[2])
        || (m_board[0] == m_board[3] && m_board[3] == m_board[6])
        || (m_board[0] == m_board[4] && m_board[4] == m_board[8])) {
        if (m_board[0] == kHumanSymbol)
            return qMakePair<bool, Game::GameFinished>(true, GameFinished::Human);
        if (m_board[0] == kAiSymbol)
            return qMakePair<bool, Game::GameFinished>(true, GameFinished::AI);
    }

    if (m_board[1] == m_board[4] && m_board[4] == m_board[7]) {
        if (m_board[1] == kHumanSymbol)
            return qMakePair<bool, Game::GameFinished>(true, GameFinished::Human);
        if (m_board[1] == kAiSymbol)
            return qMakePair<bool, Game::GameFinished>(true, GameFinished::AI);
    }

    if ((m_board[2] == m_board[5] && m_board[5] == m_board[8])
        || (m_board[2] == m_board[4] && m_board[4] == m_board[6])) {
        if (m_board[2] == kHumanSymbol)
            return qMakePair<bool, Game::GameFinished>(true, GameFinished::Human);
        if (m_board[2] == kAiSymbol)
            return qMakePair<bool, Game::GameFinished>(true, GameFinished::AI);
    }

    if (m_board[3] == m_board[4] && m_board[4] == m_board[5]) {
        if (m_board[3] == kHumanSymbol)
            return qMakePair<bool, Game::GameFinished>(true, GameFinished::Human);
        if (m_board[3] == kAiSymbol)
            return qMakePair<bool, Game::GameFinished>(true, GameFinished::AI);
    }

    if (m_board[6] == m_board[7] && m_board[7] == m_board[8]) {
        if (m_board[6] == kHumanSymbol)
            return qMakePair<bool, Game::GameFinished>(true, GameFinished::Human);
        if (m_board[6] == kAiSymbol)
            return qMakePair<bool, Game::GameFinished>(true, GameFinished::AI);
    }

    if (m_freeCells.empty()) {
        return qMakePair<bool, Game::GameFinished>(true, Game::GameFinished::EndOfMoves);
    }

    return qMakePair<bool, Game::GameFinished>(false, Game::GameFinished::EndOfMoves);
}

QList<QChar> Game::dumpBoard() const
{
    return m_board;
}

qint32 Game::evaluateMove()
{
    return possibleWinFor(Game::Turn::AI) - possibleWinFor(Game::Turn::Human);
}

qint32 Game::evaluateWin(GameFinished whoWin)
{
    if (whoWin == GameFinished::Human)
        return -10;
    if (whoWin == GameFinished::AI)
        return 10;
    return 0;
}

quint8 Game::possibleWinFor(Game::Turn player)
{
    QChar symbolOpponent = player == Game::Turn::Human ? kAiSymbol : kHumanSymbol;
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
// alpha is the maximum found fo last two max evaluation, with this concept of alpha beta pruning we can stop search
// for all depth of tree. (best option for max)
// beta is the minimum found for last two min evaluation. (best option for min)
Game::CalculatedMove Game::minVal(quint8 depth, quint8 alpha, quint8 beta)
{
    auto finished = isGameFinished();
    if (finished.first)
        // this allowa to prioritize an early win, without `(depth + 1) *` a win in 1 move and a win in 10 moves have same value for AI
        return CalculatedMove { (depth + 1) * evaluateWin(finished.second), 0 };

    if (depth == 0) // limit of max depth that can be calculated, return estimation of wins
        return { evaluateMove(), 0 };

    auto min = std::numeric_limits<qint32>::max();
    auto freeCellsCpy = m_freeCells;
    quint8 bestMoveIndex = 0;
    for (auto it = freeCellsCpy.begin(); it != freeCellsCpy.end(); ++it) {
        auto cell = *it;
        auto item = std::find(m_freeCells.begin(), m_freeCells.end(), cell);
        m_freeCells.removeOne(*item);
        m_board[cell] = kHumanSymbol;
        auto currentMove = maxVal(depth - 1, alpha, beta);
        if (currentMove.value < min) {
            min = currentMove.value;
            bestMoveIndex = cell;
        }

        if (min < beta) {
            beta = min;
        }

        m_board[cell] = ' ';
        m_freeCells.push_back(cell);

        // alpha pruning
        if (min <= alpha) {
            break;
        }
    }

    return { min, bestMoveIndex };
}

Game::CalculatedMove Game::maxVal(quint8 depth, quint8 alpha, quint8 beta)
{
    auto finished = isGameFinished();
    if (finished.first)
        return CalculatedMove { (depth + 1) * evaluateWin(finished.second), 0 };

    if (depth == 0) // limit of max depth that can be calculated, return estimation of wins
        return { evaluateMove(), 0 };

    auto max = std::numeric_limits<qint32>::min();
    auto freeCellsCpy = m_freeCells;
    quint8 bestMoveIndex = 0;
    for (auto it = freeCellsCpy.begin(); it != freeCellsCpy.end(); ++it) {
        auto cell = *it;
        auto item = std::find(m_freeCells.begin(), m_freeCells.end(), cell);
        m_freeCells.removeOne(*item);
        m_board[cell] = kAiSymbol;
        auto currentMove = minVal(depth - 1, alpha, beta);
        if (currentMove.value > max) {
            max = currentMove.value;
            bestMoveIndex = cell;
        }

        if (max > alpha) {
            alpha = max;
        }

        m_board[cell] = ' ';
        m_freeCells.push_back(cell);

        // beta pruning
        if (max >= beta) {
            break;
        }
    }

    return { max, bestMoveIndex };
}
