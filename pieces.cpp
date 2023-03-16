#include "pieces.h"

#include "board.h"
#include "move.h"

namespace Chess
{

    std::list<Move> Piece::checkJumpMove(Vector2 position, Board &board, Vector2 offset, bool canTake, bool mustTake)
    {
        std::list<Move> move = std::list<Move>();

        Vector2 positionAfterJump = position + offset;

        if (!board.isPositionInBounds(positionAfterJump))
            return move;

        std::shared_ptr<Piece> piece = board.getSquare(positionAfterJump)->getPiece();

        if ((piece == nullptr && !mustTake) || (piece->getColor() != m_color && canTake))
        {
            move.emplace_back(board.getSquare(position), board.getSquare(positionAfterJump));
            return move;
        }

        return move;
    }

    std::list<Move> Piece::checkSlideMove(Vector2 position, Board &board, Vector2 offset)
    {
        std::list<Move> availableMoves = std::list<Move>();

        Vector2 currentPosition = position;

        while (true)
        {
            currentPosition += offset;

            if (!board.isPositionInBounds(currentPosition))
                break;

            std::shared_ptr<Piece> piece = board.getSquare(currentPosition)->getPiece();

            if (piece == nullptr) // empty square
            {
                availableMoves.emplace_back(board.getSquare(position), board.getSquare(currentPosition));
                continue;
            }

            if (piece->getColor() == m_color) // same color
            {
                break;
            }

            // else different color
            availableMoves.emplace_back(board.getSquare(position), board.getSquare(currentPosition));
            break;
        }

        return availableMoves;
    }

    Piece::Piece(Color color)
        : m_color(color)
    {
    }

    char Piece::getAsciiRepresentation()
    {
        return m_asciiRepresentation;
    }

    Color Piece::getColor()
    {
        return m_color;
    }

    bool Piece::operator==(const Piece &other) const
    {
        if (m_asciiRepresentation == other.m_asciiRepresentation && m_color == other.m_color) return true;
        return false;
    }

    King::King(Color color)
        : Piece(color)
    {
        m_asciiRepresentation = 'K';
    }

    std::list<Move> King::getAvailableMoves(Vector2 position, Board &board)
    {
        std::list<Move> availableMoves = std::list<Move>();

        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(-1, -1)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(-1, 0)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(-1, 1)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(0, -1)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(0, 1)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(1, -1)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(1, 0)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(1, 1)));

        return availableMoves;
    }

    Queen::Queen(Color color)
        : Piece(color)
    {
        m_asciiRepresentation = 'Q';
    }
    std::list<Move> Queen::getAvailableMoves(Vector2 position, Board &board)
    {
        std::list<Move> availableMoves = std::list<Move>();

        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(-1, -1)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(-1, 0)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(-1, 1)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(0, -1)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(0, 1)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(1, -1)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(1, 0)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(1, 1)));

        return availableMoves;
    }
    Rook::Rook(Color color)
        : Piece(color)
    {
        m_asciiRepresentation = 'R';
    }

    std::list<Move> Rook::getAvailableMoves(Vector2 position, Board &board)
    {
        std::list<Move> availableMoves = std::list<Move>();

        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(-1, 0)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(0, -1)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(0, 1)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(1, 0)));

        return availableMoves;
    }

    Bishop::Bishop(Color color)
        : Piece(color)
    {
        m_asciiRepresentation = 'B';
    }

    std::list<Move> Bishop::getAvailableMoves(Vector2 position, Board &board)
    {
        std::list<Move> availableMoves = std::list<Move>();

        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(-1, -1)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(-1, 1)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(1, -1)));
        availableMoves.splice(availableMoves.end(), checkSlideMove(position, board, Vector2(1, 1)));

        return availableMoves;
    }

    Knight::Knight(Color color)
        : Piece(color)
    {
        m_asciiRepresentation = 'N';
    }

    std::list<Move> Knight::getAvailableMoves(Vector2 position, Board &board)
    {
        std::list<Move> availableMoves = std::list<Move>();

        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(-2, -1)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(-2, 1)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(-1, -2)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(-1, 2)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(1, -2)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(1, 2)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(2, -1)));
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(2, 1)));

        return availableMoves;
    }

    Pawn::Pawn(Color color)
        : Piece(color)
    {
        m_asciiRepresentation = 'P';
    }

    std::list<Move> Pawn::getAvailableMoves(Vector2 position, Board &board)
    {
        std::list<Move> availableMoves = std::list<Move>();

        int invert = 1;
        if (m_color == Color::Black) invert = -1;

        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(-1, 1 * invert), true, true)); // capture left
        availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(1, 1 * invert), true, true));  // capture right

        std::list<Move> singlePush = checkJumpMove(position, board, Vector2(0, 1 * invert), false); // push check

        if (singlePush.size() != 0) // if can push once, check if can doublepush
        {
            if (position.m_y == (7 + (invert * -5)) / 2)
            {
                availableMoves.splice(availableMoves.end(), checkJumpMove(position, board, Vector2(0, 2 * invert), false)); // doublepush
            }

            else if (position.m_y == (7 + (invert * 5)) / 2)
            {
                int lastRow = (7 + (invert * 7)) / 2;
                availableMoves.emplace_back(board.getSquare(position), board.getSquare(Vector2(position.m_x, lastRow)), std::make_shared<Queen>(m_color)); 
                availableMoves.emplace_back(board.getSquare(position), board.getSquare(Vector2(position.m_x, lastRow)), std::make_shared<Rook>(m_color)); 
                availableMoves.emplace_back(board.getSquare(position), board.getSquare(Vector2(position.m_x, lastRow)), std::make_shared<Bishop>(m_color)); 
                availableMoves.emplace_back(board.getSquare(position), board.getSquare(Vector2(position.m_x, lastRow)), std::make_shared<Knight>(m_color)); 
                return availableMoves;
            }
        }

        availableMoves.splice(availableMoves.end(), singlePush); // push add

        return availableMoves;
    }
}