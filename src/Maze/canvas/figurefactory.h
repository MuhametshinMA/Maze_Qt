#ifndef FIGUREFACTORY_H
#define FIGUREFACTORY_H

#include <memory>

#include "figure.h"
#include "figureparams.h"

class IFigureFactory {
 public:
  virtual std::unique_ptr<IFigure> CreateFigure(
      FigureParams figure_params) const = 0;
  virtual ~IFigureFactory() = default;
};

class PointFactory : public IFigureFactory {
 public:
  std::unique_ptr<IFigure> CreateFigure(
      FigureParams figure_params) const override {
    return std::make_unique<Point>(figure_params.x1, figure_params.y1,
                                   figure_params.color, figure_params.size);
  }
};

class LineFactory : public IFigureFactory {
 public:
  std::unique_ptr<IFigure> CreateFigure(
      FigureParams figure_params) const override {
    return std::make_unique<Line>(figure_params.x1, figure_params.y1,
                                  figure_params.x2, figure_params.y2,
                                  figure_params.color, figure_params.size);
  }
};

class RectangleFactory : public IFigureFactory {
 public:
  std::unique_ptr<IFigure> CreateFigure(
      FigureParams figure_params) const override {
    return std::make_unique<Rectangle>(figure_params.x1, figure_params.y1,
                                       figure_params.x2, figure_params.y2,
                                       figure_params.color, figure_params.size);
  }
};

#endif  // FIGUREFACTORY_H
