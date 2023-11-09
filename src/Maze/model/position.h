#ifndef POSITION_H
#define POSITION_H

#include <functional>

class Position {
 public:
  struct HashFunction {
    size_t operator()(const Position &pos) const {
      return std::hash<int>()(pos.i_) ^ (std::hash<int>()(pos.j_) << 1);
    }
  };

  Position() = default;
  Position(const int &i, const int &j);
  bool operator==(Position const &pos) const;
  bool operator!=(Position const &pos) const;
  int i() const;
  int j() const;
  Position Left() const;
  Position Up() const;
  Position Right() const;
  Position Down() const;

 private:
  int i_;
  int j_;
};

#endif  // POSITION_H
