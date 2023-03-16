#include <iostream>
#include "board.h"

#include "display.h"
#include "game.h"

int main ()
{
    std::cout << "Starting..." << std::endl;

    Chess::Game chessGame = Chess::Game();
    Chess::Display chessDisplay = Chess::Display(chessGame);

    chessDisplay.loop();

    return 0;
}