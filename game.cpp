#include "game.h"

namespace Chess
{
    std::list<Move> Game::getAvailableMoves()
    {
        return m_board->getAvailableMovesFor(m_toMove);
    }

    Game::Game()
    {
        newGame();
    }

    bool Game::newGame()
    {
        m_board = std::make_shared<Board>();
        m_board->initDefault();
        m_toMove = Color::White;
        m_history = std::list<std::shared_ptr<Move>>();
        return true;
    }

    std::shared_ptr<Board> Game::getBoard()
    {
        return m_board;
    }

    bool Game::tryToMakeMove(std::shared_ptr<Move> move)
    {
        std::list<Move> allMoves = getAvailableMoves();

        for (const Move &currentMove: allMoves)
        {
            if (currentMove == *move)
            {
                m_history.push_back(move);

                move->m_captured = move->m_to->getPiece();
                move->m_to->setPiece(move->m_from->getPiece());
                move->m_from->setPiece(nullptr);

                if (move->m_promotion != nullptr)
                {
                    move->m_to->setPiece(move->m_promotion);
                }

                return true;
            }
        }

        return false;
    }

    Color Game::whoIsOnTurn()
    {
        return m_toMove;
    }
}