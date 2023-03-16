#ifndef MOVE_H
#define MOVE_H

#include "square.h"
#include "pieces.h"

#include <memory>

namespace Chess
{
  class Move
  {
  public:
    Move();
    Move(std::shared_ptr<Square> from, std::shared_ptr<Square> to, std::shared_ptr<Piece> promotion = nullptr); 
    std::shared_ptr<Square> m_from;
    std::shared_ptr<Square> m_to;
    std::shared_ptr<Piece> m_promotion;
    std::shared_ptr<Piece> m_captured;

    bool operator==(const Move& other) const;
  };
}

#endif