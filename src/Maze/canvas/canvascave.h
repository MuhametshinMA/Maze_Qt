#ifndef CANVASCAVE_H
#define CANVASCAVE_H

#include <memory>
#include <vector>

#include "cave.h"
#include "figure.h"

class CanvasCave {
 public:
  CanvasCave(Cave& cave, const QSize& field);
  void CreateCaveFigures();
  void ClearFigures();
  std::vector<std::shared_ptr<IFigure>>& GetFigures();

 private:
  Cave& cave_;
  std::vector<std::shared_ptr<IFigure>> figures_;
  int height_;
  int width_;
};

#endif  // CANVASCAVE_H
