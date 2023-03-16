#include "move.h"

namespace Chess
{
  Move::Move()
  {
  }

  Move::Move(std::shared_ptr<Square> from, std::shared_ptr<Square> to, std::shared_ptr<Piece> promotion)
    : m_from(from), m_to(to), m_promotion(promotion)
  {
  }

  bool Move::operator==(const Move &other) const
  {
    if (m_from == other.m_from && m_to == other.m_to && (m_promotion == other.m_promotion || *m_promotion == *(other.m_promotion))) return true;

    return false;
  }
}
