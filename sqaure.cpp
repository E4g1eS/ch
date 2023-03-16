#include "square.h"

namespace Chess
{

    bool Square::setPiece(std::shared_ptr<Piece> piece)
    {
        m_piece = piece;
        return true;
    }

    std::shared_ptr<Piece> Square::getPiece()
    {
        return m_piece;
    }

    char Square::getAsciiRepresentation()
    {
        if (m_piece == nullptr)
        {
            return '.';
        }

        return m_piece->getAsciiRepresentation();
    }

}