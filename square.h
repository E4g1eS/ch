#ifndef SQUARE_H
#define SQUARE_H

#include "pieces.h"

#include <memory>

namespace Chess
{
    class Square
    {
        std::shared_ptr<Piece> m_piece;

    public:
        bool setPiece(std::shared_ptr<Piece> piece);
        std::shared_ptr<Piece> getPiece();
        char getAsciiRepresentation();
    };
}

#endif