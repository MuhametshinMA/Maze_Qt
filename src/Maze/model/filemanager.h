#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <exception>
#include <fstream>
#include <string>

#include "maze.h"

class FileManager {
 public:
  FileManager();
  Maze LoadMazeFromFile(const std::string path);
  void SaveMazeToFile(Maze &maze, const std::string path);
};

#endif  // FILEMANAGER_H
