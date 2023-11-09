#ifndef CANVASMAZE_H
#define CANVASMAZE_H

#include <memory>
#include <vector>

#include "figure.h"
#include "figurefactory.h"
#include "maze.h"
#include "path.h"

class CanvasMaze {
 public:
  CanvasMaze(Maze& maze, const QSize& field);

  void CreateMazeFigures();
  void CreatePoint(size_t x, size_t y);
  void ClearPoints();
  void ClearPath();
  std::vector<std::shared_ptr<IFigure>>& GetFigures();

 private:
  void InitSizes();
  void DrawPath();
  Position GetRealPosition(size_t x, size_t y);
  void CreateLine(const int& x1, const int& y1, const int& x2, const int& y2,
                  QColor color, const int& size);
  void CreateVerticalWalls();
  void CreateHorizontalWalls();

  Maze& maze_;
  std::vector<std::shared_ptr<IFigure>> figures_;
  std::vector<std::shared_ptr<IFigure>> walls_layer_;
  std::vector<std::shared_ptr<IFigure>> point_layer_;
  std::vector<std::shared_ptr<IFigure>> path_layer_;
  std::vector<Position> path_positions_;
  std::shared_ptr<Path> path_;
  std::unique_ptr<IFigureFactory> line_;
  std::unique_ptr<IFigureFactory> point_;
  int rows_;
  int cols_;
  int height_;
  int width_;
  int shift_r_;
  int shift_c_;
  int center_r_;
  int center_c_;
  int start_r_;
  int start_c_;
  int end_r_;
  int end_c_;
};

#endif  // CANVASMAZE_H
