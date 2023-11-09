#ifndef CAVE_DATA_H
#define CAVE_DATA_H

#include <random>
#include <vector>

class Random {
 public:
  bool operator()(double chance) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    return (dis(gen) < chance);
  }
};

using Vector_walls_ = std::vector<bool>;
using Matrix_walls_ = std::vector<Vector_walls_>;

struct CaveData {
  double chance_;
  int rows_;
  int cols_;
  CaveData(double chance = 30.0, int rows = 10, int cols = 10)
      : chance_(chance), rows_(rows), cols_(cols){};
};

#endif  // CAVE_DATA_H
