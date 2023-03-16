#ifndef BOARD_H
#define BOARD_H

#include "square.h"
#include "pieces.h"
#include "move.h"

#include <vector>
#include <memory>
#include <list>

namespace Chess
{
    constexpr int BOARD_SIZE = 8;

    class Board
    {
        std::vector<std::vector<std::shared_ptr<Square>>> m_squares;

    public:
        Board();
        bool initDefault();
        std::vector<std::vector<std::shared_ptr<Square>>> getSquares();
        std::shared_ptr<Square> getSquare(Vector2 position);

        bool isPositionInBounds(Vector2 position);

        std::list<Move> getAvailableMovesFor(Color color);
    };
}

#endif