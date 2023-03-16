#ifndef PIECES_H
#define PIECES_H

#include "primitives.h"

#include <list>

namespace Chess
{
    class Board;
    class Move;

    class Piece
    {
    protected:
        Color m_color;
        char m_asciiRepresentation;

        std::list<Move> checkJumpMove(Vector2 position, Board &board, Vector2 offset, bool canTake = true, bool mustTake = false);
        std::list<Move> checkSlideMove(Vector2 position, Board &board, Vector2 offset);

    public:
        Piece(Color color);
        char getAsciiRepresentation();
        Color getColor();

        bool operator==(const Piece &other) const;

        virtual std::list<Move> getAvailableMoves(Vector2 position, Board &board) = 0;
    };

    class King : public Piece
    {
    public:
        King(Color color);
        std::list<Move> getAvailableMoves(Vector2 position, Board &board) override;
    };

    class Queen : public Piece
    {
    public:
        Queen(Color color);
        std::list<Move> getAvailableMoves(Vector2 position, Board &board) override;
    };

    class Rook : public Piece
    {
    public:
        Rook(Color color);
        std::list<Move> getAvailableMoves(Vector2 position, Board &board) override;
    };

    class Bishop : public Piece
    {
    public:
        Bishop(Color color);
        std::list<Move> getAvailableMoves(Vector2 position, Board &board) override;
    };

    class Knight : public Piece
    {
    public:
        Knight(Color color);
        std::list<Move> getAvailableMoves(Vector2 position, Board &board) override;
    };

    class Pawn : public Piece
    {

    public:
        Pawn(Color color);
        std::list<Move> getAvailableMoves(Vector2 position, Board &board) override;
    };

}

#endif