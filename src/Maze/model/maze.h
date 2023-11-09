#ifndef MAZE_H
#define MAZE_H

#include <algorithm>
#include <map>
#include <random>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "position.h"

class Maze {
 public:
  using row_matrix_bool = std::vector<bool>;
  using matrix_bool = std::vector<row_matrix_bool>;

  Maze();
  Maze(size_t size);
  explicit Maze(int rows, int cols);
  explicit Maze(size_t rows, size_t cols);
  void InitMaze(size_t rows, size_t cols);
  void SetHorizontalWall(const size_t &i, const size_t &j, const bool wall);
  void SetVerticalWall(const size_t &i, const size_t &j, const bool wall);
  size_t GetRows() const;
  size_t GetCols() const;
  bool GetVerticalWall(const size_t &i, const size_t &j) const;
  bool GetHorizontalWall(const size_t &i, const size_t &j) const;
  bool GetVerticalWall(const Position &pos) const;
  bool GetHorizontalWall(const Position &pos) const;
  void GenerateMaze(size_t rows, size_t cols);
  void SaveFile(const std::string &filename);

 private:
  void GenerateRow(const size_t &i);
  void CopyRow(const size_t &i);
  void AddVerticalWalls(const size_t &i);
  void MergeSet(const size_t &index);
  void AddHorizontalWalls(const size_t &i);
  void GenerateFinalRow();
  void SetHorizontalWallInFinalRow();
  void DestroyVerticalWallsAndMerge();
  bool RandomWall() const;
  void InitSets();
  void FillSet(const size_t &j);

  size_t rows_;
  size_t cols_;
  matrix_bool vertical_walls_;
  matrix_bool horizontal_walls_;

  std::vector<size_t> temp_row_;
  std::unordered_map<size_t, std::unordered_set<size_t>> busy_sets_;
  std::unordered_set<size_t> free_sets_;
};

#endif  // MAZE_H
