#include "board.h"

#include <iostream>

namespace Chess
{
    Board::Board()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            m_squares.push_back(std::vector<std::shared_ptr<Square>>());

            for (int j = 0; j < BOARD_SIZE; j++)
            {
                m_squares[i].push_back(std::make_shared<Square>());
            }
        }
    }

    bool Board::initDefault()
    {
        // WHITE
        m_squares[0][1]->setPiece(std::make_shared<Pawn>(Color::White));
        m_squares[1][1]->setPiece(std::make_shared<Pawn>(Color::White));
        m_squares[2][1]->setPiece(std::make_shared<Pawn>(Color::White));
        m_squares[3][1]->setPiece(std::make_shared<Pawn>(Color::White));
        m_squares[4][1]->setPiece(std::make_shared<Pawn>(Color::White));
        m_squares[5][1]->setPiece(std::make_shared<Pawn>(Color::White));
        m_squares[6][1]->setPiece(std::make_shared<Pawn>(Color::White));
        m_squares[7][1]->setPiece(std::make_shared<Pawn>(Color::White));

        m_squares[0][0]->setPiece(std::make_shared<Rook>(Color::White));
        m_squares[1][0]->setPiece(std::make_shared<Knight>(Color::White));
        m_squares[2][0]->setPiece(std::make_shared<Bishop>(Color::White));
        m_squares[3][0]->setPiece(std::make_shared<Queen>(Color::White));
        m_squares[4][0]->setPiece(std::make_shared<King>(Color::White));
        m_squares[5][0]->setPiece(std::make_shared<Bishop>(Color::White));
        m_squares[6][0]->setPiece(std::make_shared<Knight>(Color::White));
        m_squares[7][0]->setPiece(std::make_shared<Rook>(Color::White));

        // BLACK
        m_squares[0][6]->setPiece(std::make_shared<Pawn>(Color::Black));
        m_squares[1][6]->setPiece(std::make_shared<Pawn>(Color::Black));
        m_squares[2][6]->setPiece(std::make_shared<Pawn>(Color::Black));
        m_squares[3][6]->setPiece(std::make_shared<Pawn>(Color::Black));
        m_squares[4][6]->setPiece(std::make_shared<Pawn>(Color::Black));
        m_squares[5][6]->setPiece(std::make_shared<Pawn>(Color::Black));
        m_squares[6][6]->setPiece(std::make_shared<Pawn>(Color::Black));
        m_squares[7][6]->setPiece(std::make_shared<Pawn>(Color::Black));

        m_squares[0][7]->setPiece(std::make_shared<Rook>(Color::Black));
        m_squares[1][7]->setPiece(std::make_shared<Knight>(Color::Black));
        m_squares[2][7]->setPiece(std::make_shared<Bishop>(Color::Black));
        m_squares[3][7]->setPiece(std::make_shared<Queen>(Color::Black));
        m_squares[4][7]->setPiece(std::make_shared<King>(Color::Black));
        m_squares[5][7]->setPiece(std::make_shared<Bishop>(Color::Black));
        m_squares[6][7]->setPiece(std::make_shared<Knight>(Color::Black));
        m_squares[7][7]->setPiece(std::make_shared<Rook>(Color::Black));
        return true;
    }

    std::vector<std::vector<std::shared_ptr<Square>>> Board::getSquares()
    {
        return m_squares;
    }

    std::shared_ptr<Square> Board::getSquare(Vector2 position)
    {
        return m_squares[position.m_x][position.m_y];
    }

    bool Board::isPositionInBounds(Vector2 position)
    {
        if (position.m_x < 0 || (size_t)position.m_x >= m_squares.size() || position.m_y < 0 || (size_t)position.m_y >= m_squares.size())
        {
            return false;
        }

        return true;
    }

    std::list<Move> Board::getAvailableMovesFor(Color color)
    {
        std::list<Move> allMoves = std::list<Move>();

        for (size_t x = 0; x < m_squares.size(); x++)
        {
            for (size_t y = 0; y < m_squares[0].size(); y++)
            {
                auto piece = m_squares[x][y]->getPiece();

                if (piece == nullptr || piece->getColor() != color)
                {
                    continue;
                }

                std::list<Move> movesForPiece = piece->getAvailableMoves(Vector2(x, y), (*this));

                allMoves.splice(allMoves.end(), movesForPiece);
            }
        }

        return allMoves;
    }
}