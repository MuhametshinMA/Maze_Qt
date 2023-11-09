#ifndef IFIGURE_H
#define IFIGURE_H

#include <QColor>
#include <memory>

#include "figure.h"

struct FigureParams {
  int x1;
  int y1;
  int x2;
  int y2;
  QColor color;
  int size;
};

class IFigureFactory {
 public:
  virtual std::unique_ptr<IFigure> createFigure(
      FigureParams figure_params) const = 0;
  virtual ~IFigureFactory() = default;
};

class PointFactory : public IFigureFactory {
 public:
  std::unique_ptr<IFigure> createFigure(
      FigureParams figure_params) const override;
};

class LineFactory : public IFigureFactory {
 public:
  std::unique_ptr<IFigure> createFigure(
      FigureParams figure_params) const override;
};

class RectangleFactory : public IFigureFactory {
 public:
  std::unique_ptr<IFigure> createFigure(
      FigureParams figure_params) const override;
};

#endif  // IFIGURE_H
