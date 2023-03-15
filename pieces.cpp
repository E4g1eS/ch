#include "pieces.h"

#include "board.h"

bool Chess::Piece::print(Chess::Board *b)
{
    b->print();
    return false;
}