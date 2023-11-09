#include "filemanager.h"

#include <iostream>

FileManager::FileManager() {}

Maze FileManager::LoadMazeFromFile(const std::string path) {
  std::ifstream fin(path);
  if (!fin.is_open()) throw std::ios_base::failure("File is NOT opened!");
  size_t rows, cols;
  if (!(fin >> rows >> cols) || !rows || !cols)
    throw std::invalid_argument(
        "Incorrect number of rows and cols in Maze file!");
  Maze maze(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      int wall;
      if (!(fin >> wall) || !(wall == 0 || wall == 1))
        throw std::invalid_argument("Incorrect walls in Maze file!");
      maze.SetVerticalWall(i, j, static_cast<bool>(wall));
    }
  }
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      int wall;
      if (!(fin >> wall) || !(wall == 0 || wall == 1))
        throw std::invalid_argument("Incorrect walls in Maze file!");
      maze.SetHorizontalWall(i, j, static_cast<bool>(wall));
    }
  }
  return maze;
}

void FileManager::SaveMazeToFile(Maze &maze, const std::string path) {
  std::ofstream fout(path);
  size_t rows = maze.GetRows(), cols = maze.GetCols();
  fout << rows << " " << cols << std::endl;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      fout << maze.GetVerticalWall(i, j);
      if (j < cols - 1) fout << " ";
    }
    fout << std::endl;
  }
  fout << std::endl;

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      fout << maze.GetHorizontalWall(i, j);
      if (j < cols - 1) fout << " ";
    }
    if (i < rows - 1) fout << std::endl;
  }
}
