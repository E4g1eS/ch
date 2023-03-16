#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"

#include <memory>

namespace Chess
{

    class Display
    {
        Game &m_game;

        std::shared_ptr<Move> getInput();
        void print();

    public:
        Display(Game &game);
        bool loop();
    };

}

#endif