#ifndef CAVE_H
#define CAVE_H

#include <fstream>
#include <iostream>
#include <sstream>

#include "cave_data.h"

class Cave {
 public:
  Cave();
  Cave(CaveData);
  Cave(const Cave&);
  ~Cave(){};

  void ResizeCave(CaveData);
  void ResizeCavePath(std::string);
  void NextStepEvolution(int, int);
  int GetRows() const;
  int GetCols() const;
  Matrix_walls_ GetMatrix() const;

  void SaveFile(const std::string&);
  void LoadFile(const std::string);
  bool MatrixEquals(const Matrix_walls_&);

 private:
  bool CalculateCellNewValue(int, int);
  int CountLiveNeighbors(int, int);
  void AllocationMemory();
  void CopyMatrix(const Cave&);
  void SendValueRandom(double);
  bool IsCorrectArgument();

  double chance_;
  int rows_;
  int cols_;
  int death_;
  int birth_;
  Matrix_walls_ matrix_walls_;
};

#endif  // CAVE_H
