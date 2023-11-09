#include "position.h"

Position::Position(const int &i, const int &j) : i_{i}, j_{j} {}

bool Position::operator==(const Position &pos) const {
  return i_ == pos.i() && j_ == pos.j();
}

bool Position::operator!=(const Position &pos) const {
  return i_ != pos.i() || j_ != pos.j();
}

int Position::i() const { return i_; }

int Position::j() const { return j_; }

Position Position::Left() const { return Position(i_, j_ - 1); }

Position Position::Up() const { return Position(i_ - 1, j_); }

Position Position::Right() const { return Position(i_, j_ + 1); }

Position Position::Down() const { return Position(i_ + 1, j_); }
