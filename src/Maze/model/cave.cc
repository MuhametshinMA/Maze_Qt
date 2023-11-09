#include "cave.h"

Cave::Cave() : Cave(CaveData()) {}

Cave::Cave(CaveData data) { ResizeCave(data); }

Cave::Cave(const Cave &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  AllocationMemory();
  CopyMatrix(other);
}

void Cave::ResizeCave(CaveData data) {
  chance_ = data.chance_;
  rows_ = data.rows_;
  cols_ = data.cols_;
  AllocationMemory();
  SendValueRandom(chance_);
}

void Cave::ResizeCavePath(std::string path) {
  try {
    LoadFile(path);
  } catch (const std::exception &e) {
    std::cout << e.what();
  }
}

void Cave::NextStepEvolution(int birth, int death) {
  Cave new_walls(CaveData(10.00, rows_, cols_));
  birth_ = birth;
  death_ = death;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      new_walls.matrix_walls_[i][j] = CalculateCellNewValue(i, j);
    }
  }
  CopyMatrix(new_walls);
}

int Cave::GetRows() const { return rows_; }

int Cave::GetCols() const { return cols_; }

Matrix_walls_ Cave::GetMatrix() const { return matrix_walls_; }

void Cave::SaveFile(const std::string &filename) {
  std::ofstream outfile(filename);
  if (!outfile) {
    throw std::invalid_argument("Error opening file for writing.");
  }
  outfile << rows_ << " " << cols_ << "\n";
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      outfile << matrix_walls_[i][j] << " ";
    }
    outfile << "\n";
  }
  outfile.close();
}

void Cave::LoadFile(const std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("can't open file");
  }
  std::string line;

  std::getline(file, line);
  std::stringstream ss(line);
  std::string token;
  std::string delimiter = " ";
  for (int i = 0; i < 2; i++) {
    std::getline(ss, token, ' ');
    if (i == 0)
      rows_ = std::stoi(token);
    else
      cols_ = std::stoi(token);
  }

  AllocationMemory();
  for (int i = 0; i < rows_; i++) {
    std::getline(file, line);

    std::istringstream iss(line);
    bool value;
    int j = 0;
    while (iss >> value) {
      matrix_walls_[i][j] = value;
      j++;
    }
  }
}

bool Cave::CalculateCellNewValue(int x, int y) {
  int count;
  count = CountLiveNeighbors(x, y);
  if (matrix_walls_[x][y] == true) {
    return (!(count < death_));
  } else {
    return (count > birth_);
  }
}

int Cave::CountLiveNeighbors(int x, int y) {
  int count = 0;
  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        count++;
        continue;
      } else if (i == x && j == y)
        continue;
      else {
        if (matrix_walls_[i][j]) count++;
      }
    }
  }
  return count;
}

void Cave::AllocationMemory() {
  if (!IsCorrectArgument()) {
    throw std::invalid_argument("Invalid argument");
  } else {
    matrix_walls_.resize(rows_);
    for (int i = 0; i < rows_; i++) {
      matrix_walls_[i].resize(cols_);
    }
  }
}

void Cave::CopyMatrix(const Cave &other) {
  for (int i = 0; i < std::min(rows_, other.rows_); i++) {
    for (int j = 0; j < std::min(cols_, other.cols_); j++) {
      matrix_walls_[i][j] = other.matrix_walls_[i][j];
    }
  }
}

void Cave::SendValueRandom(double chance) {
  Random rand;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_walls_[i][j] = rand(chance);
    }
  }
}

bool Cave::IsCorrectArgument() {
  return (!(rows_ <= 0 || cols_ <= 0 || chance_ <= 0));
}

bool Cave::MatrixEquals(const Matrix_walls_ &other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_walls_[i][j] != other[i][j]) {
        return false;
      }
    }
  }
  return true;
}
