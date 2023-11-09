#include "maze.h"

#include <fstream>

Maze::Maze() : Maze(1, 1) {}

Maze::Maze(size_t size) : Maze(size, size) {}

Maze::Maze(size_t rows, size_t cols) : rows_{rows}, cols_{cols} {
  InitMaze(rows, cols);
}
Maze::Maze(int rows, int cols) {
  if (rows < 1 || cols < 1)
    throw std::invalid_argument(
        "Number of rows and cols must be greater than 0!");
  InitMaze(static_cast<size_t>(rows), static_cast<size_t>(cols));
}

void Maze::InitMaze(size_t rows, size_t cols) {
  if (rows < 1 || cols < 1)
    throw std::invalid_argument(
        "Number of rows and cols must be greater than 0!");
  rows_ = rows;
  cols_ = cols;
  busy_sets_.clear();
  free_sets_.clear();
  vertical_walls_ = matrix_bool(rows_, row_matrix_bool(cols_));
  horizontal_walls_ = matrix_bool(rows_, row_matrix_bool(cols_));
  temp_row_ = std::vector<size_t>(cols_);
}

void Maze::SetHorizontalWall(const size_t &i, const size_t &j,
                             const bool wall) {
  horizontal_walls_[i][j] = wall;
}

void Maze::SetVerticalWall(const size_t &i, const size_t &j, const bool wall) {
  vertical_walls_[i][j] = wall;
}

size_t Maze::GetRows() const { return rows_; }

size_t Maze::GetCols() const { return cols_; }

bool Maze::GetVerticalWall(const size_t &i, const size_t &j) const {
  return vertical_walls_[i][j];
}

bool Maze::GetHorizontalWall(const size_t &i, const size_t &j) const {
  return horizontal_walls_[i][j];
}

bool Maze::GetVerticalWall(const Position &pos) const {
  return vertical_walls_[pos.i()][pos.j()];
}

bool Maze::GetHorizontalWall(const Position &pos) const {
  return horizontal_walls_[pos.i()][pos.j()];
}

void Maze::SaveFile(const std::string &filename) {
  std::ofstream outfile(filename);
  if (!outfile) {
    throw std::invalid_argument("Error opening file for writing.");
  }
  outfile << rows_ << " " << cols_ << "\n";
  for (size_t r = 0; r < rows_; r++) {
    for (size_t c = 0; c < cols_; c++) {
      outfile << GetVerticalWall(r, c) << " ";
    }
    outfile << "\n";
  }
  outfile << "\n";

  for (size_t r = 0; r < rows_; r++) {
    for (size_t c = 0; c < cols_; c++) {
      outfile << GetHorizontalWall(r, c) << " ";
    }
    outfile << "\n";
  }
}
