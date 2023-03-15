#include <iostream>
#include "board.h"

int main ()
{
    std::cout << "Starting..." << std::endl;

    Chess::Board board = Chess::Board();
    Chess::Piece piece = Chess::Piece();
    piece.print(&board);

    return 0;
}