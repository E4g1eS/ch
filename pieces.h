#ifndef PIECES_H
#define PIECES_H

namespace Chess
{
    class Board;

    class Piece
    {
        public:
        bool print(Chess::Board *b);
    };

    class King : public Piece
    {
    };
    class Queen : public Piece
    {
    };
    class Rook : public Piece
    {
    };
    class Bishop : public Piece
    {
    };
    class Knight : public Piece
    {
    };
    class Pawn : public Piece
    {
    };

}

#endif