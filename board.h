#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"

namespace Chess
{
    class Board {
    public:
        Piece **pieces;
        void print();
    };
}

#endif