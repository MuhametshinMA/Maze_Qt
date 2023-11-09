#include "canvascave.h"

#include "figurefactory.h"

CanvasCave::CanvasCave(Cave& cave, const QSize& field)
    : cave_(cave), height_{field.height()}, width_{field.width()} {}

void CanvasCave::CreateCaveFigures() {
  ClearFigures();
  std::shared_ptr<IFigureFactory> factory_rect =
      std::make_shared<RectangleFactory>();

  int h_cell = height_ / cave_.GetRows();
  int w_cell = width_ / cave_.GetCols();

  for (int r = 0; r < cave_.GetRows(); r++) {
    for (int c = 0; c <= cave_.GetCols(); c++) {
      if (cave_.GetMatrix()[r][c]) {
        figures_.push_back(factory_rect->CreateFigure(
            {3 + c * w_cell, 3 + r * h_cell, w_cell, h_cell, Qt::gray, 1}));
      }
    }
  }
}

std::vector<std::shared_ptr<IFigure>>& CanvasCave::GetFigures() {
  return figures_;
}

void CanvasCave::ClearFigures() { figures_.clear(); }
