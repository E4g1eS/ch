#include "display.h"

#include <iostream>
#include <string>

namespace Chess
{
    std::shared_ptr<Move> Display::getInput()
    {
        std::string input;
        std::shared_ptr<Move> move = std::shared_ptr<Move>();

        while (true)
        {
            std::cout << "What move do you want to play?" << std::endl;
            input = "";
            std::cin >> input;
            if (input.length() < 4 && input.length() > 5)
            {
                std::cout << "Invalid input! Write move in format [a1-h8][a1-h8](+ Q/R/B/N when promoting). For example: 'e2e4'." << std::endl;
                continue;
            }

            Vector2 from = Vector2(input.substr(0, 2));
            Vector2 to = Vector2(input.substr(2, 2));

            if (!m_game.getBoard()->isPositionInBounds(from) || !m_game.getBoard()->isPositionInBounds(to))
            {
                std::cout << "Position is out of bounds! FROM = " << from.toString() << ", TO = " << to.toString() << "." << std::endl;
                continue;
            }

            if (input.length() == 5) // Promotion
            {
                switch (input[4])
                {
                case 'Q':
                    move->m_promotion = std::make_shared<Queen>(m_game.whoIsOnTurn());
                    break;

                case 'R':
                    move->m_promotion = std::make_shared<Rook>(m_game.whoIsOnTurn());
                    break;

                case 'B':
                    move->m_promotion = std::make_shared<Bishop>(m_game.whoIsOnTurn());
                    break;

                case 'N':
                    move->m_promotion = std::make_shared<Knight>(m_game.whoIsOnTurn());
                    break;
                
                default:
                    std::cout << "Promotion invalid!" << std::endl;
                    continue;
                }
            }

            move->m_from = m_game.getBoard()->getSquare(from);
            move->m_to = m_game.getBoard()->getSquare(to);

            return move;
        }
    }

    void Display::print()
    {
        if (m_game.whoIsOnTurn() == Color::White) std::cout << "WHITE";
        else std::cout << "BLACK";

        std::cout << " to move." << std::endl;

        std::vector<std::vector<std::shared_ptr<Square>>> squares = m_game.getBoard()->getSquares();

        std::cout << " ";

        for (size_t x = 0; x < squares.size(); x++)
        {
            std::cout << "-";
        }

        std::cout << std::endl;

        for (size_t y = squares.size(); y > 0; y--)
        {
            std::cout << "|";

            for (size_t x = 0; x < squares.size(); x++)
            {
                std::shared_ptr<Square> square = squares[x][y - 1];
                std::shared_ptr<Piece> piece = square->getPiece();

                if (piece != nullptr && piece->getColor() == Color::White)
                {
                    std::cout << "\u001b[30m\u001b[47m";
                }

                std::cout << squares[x][y - 1]->getAsciiRepresentation() << "\u001b[0m";
            }

            std::cout << "|" << y << std::endl;
        }

        std::cout << " ";

        for (size_t x = 0; x < squares.size(); x++)
        {
            std::cout << "-";
        }

        std::cout << std::endl << " ";

        for (size_t x = 0; x < squares.size(); x++)
        {
            std::cout << (char)(x + 97);
        }

        std::cout << std::endl;
    }

    Display::Display(Game &game)
    : m_game(game)
    {
    }

    bool Display::loop()
    {
        while (true)
        {
            print();
            std::shared_ptr<Move> move = getInput();
            if (!m_game.tryToMakeMove(move))
            {
                std::cout << "That move is not valid!" << std::endl;
            }
        }
        return true;
    }
}
