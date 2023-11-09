#include "maze.h"

void Maze::GenerateMaze(size_t row, size_t col) {
  InitMaze(row, col);
  InitSets();
  for (size_t i = 0; i < rows_; ++i) {
    GenerateRow(i);
  }
  GenerateFinalRow();
}

void Maze::InitSets() {
  for (size_t j = 0; j < cols_; ++j) {
    free_sets_.insert(j + 1);
  }
}

void Maze::GenerateRow(const size_t &i) {
  CopyRow(i);
  AddVerticalWalls(i);
  if (i < rows_ - 1) AddHorizontalWalls(i);
}

void Maze::CopyRow(const size_t &i) {
  for (size_t j = 0; j < cols_; ++j) {
    if (i == 0 || horizontal_walls_[i - 1][j]) {
      FillSet(j);
    }
  }
}

void Maze::FillSet(const size_t &j) {
  if (free_sets_.empty()) return;
  auto free_set = free_sets_.begin();
  busy_sets_[*free_set].insert(j);
  if (*free_set) busy_sets_[temp_row_[j]].erase(j);
  temp_row_[j] = *free_set;
  free_sets_.erase(free_set);
}

void Maze::AddVerticalWalls(const size_t &i) {
  for (size_t j = 0; j < cols_ - 1; ++j) {
    bool random_wall = RandomWall();
    if (random_wall || temp_row_[j + 1] == temp_row_[j]) {
      vertical_walls_[i][j] = true;
    } else {
      MergeSet(j);
    }
  }
  vertical_walls_[i][cols_ - 1] = true;
}

void Maze::MergeSet(const size_t &index) {
  size_t changed_num = temp_row_[index + 1];
  size_t replacement_num = temp_row_[index];
  while (!busy_sets_[changed_num].empty()) {
    auto cell = busy_sets_[changed_num].begin();
    temp_row_[*cell] = replacement_num;
    busy_sets_[replacement_num].insert(*cell);
    busy_sets_[changed_num].erase(cell);
  }
  free_sets_.insert(changed_num);
}

void Maze::AddHorizontalWalls(const size_t &i) {
  std::unordered_map<size_t, size_t> count_horizontal_walls_for_sets;
  for (size_t j = 0; j < cols_; ++j) {
    size_t cell_set = temp_row_[j];
    size_t count_nums_in_set = busy_sets_[cell_set].size();
    if (count_nums_in_set > count_horizontal_walls_for_sets[cell_set] + 1 &&
        RandomWall()) {
      horizontal_walls_[i][j] = true;
      ++count_horizontal_walls_for_sets[cell_set];
    }
  }
}

void Maze::GenerateFinalRow() {
  SetHorizontalWallInFinalRow();
  DestroyVerticalWallsAndMerge();
}

void Maze::SetHorizontalWallInFinalRow() {
  for (size_t j = 0; j < cols_; ++j) {
    SetHorizontalWall(rows_ - 1, j, true);
  }
}

void Maze::DestroyVerticalWallsAndMerge() {
  for (size_t j = 0; j < cols_ - 1; ++j) {
    if (temp_row_[j + 1] != temp_row_[j]) {
      MergeSet(j);
      vertical_walls_[rows_ - 1][j] = false;
    }
  }
}

bool Maze::RandomWall() const {
  static std::random_device device;
  static std::mt19937 gen(device());
  std::bernoulli_distribution res(0.5);
  return res(gen);
}
