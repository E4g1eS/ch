#ifndef GAME_H
#define GAME_H

#include "primitives.h"
#include "board.h"
#include "move.h"

#include <memory>
#include <list>

namespace Chess
{
    class Game
    {

        std::shared_ptr<Board> m_board;
        Color m_toMove;
        std::list<std::shared_ptr<Move>> m_history;

        std::list<Move> getAvailableMoves();

    public:
        Game();

        bool newGame();

        std::shared_ptr<Board> getBoard();

        bool tryToMakeMove(std::shared_ptr<Move> move);

        Color whoIsOnTurn();
    };
}

#endif