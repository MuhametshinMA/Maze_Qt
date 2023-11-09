#ifndef CONTROLLERMAZE_H
#define CONTROLLERMAZE_H

#include <QSize>
#include <memory>

#include "canvasmaze.h"
#include "icontroller.h"
#include "maze.h"
#include "path.h"
#include "position.h"

class ControllerMaze : public IController {
 public:
  ControllerMaze(const QSize& field);
  void Generate(const size_t& rows, const size_t& cols) override;
  void SetPoint(size_t, size_t) override;
  void ClearPath() override;
  void CreateMazeFigures() override;
  std::vector<std::shared_ptr<IFigure>> GetFigures() override;
  void FileSave(std::string path) override;
  void FileOpen(std::string path) override;

 private:
  std::shared_ptr<Maze> maze_;
  std::shared_ptr<Path> path_;
  std::shared_ptr<CanvasMaze> canvas_maze_;
  QSize field_;

  void PrintShortPath(const std::vector<Position>& path);
  int RandomIndex(int max) const;
};

#endif  // CONTROLLERMAZE_H
