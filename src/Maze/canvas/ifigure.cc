#include "figurefactory.h"

std::unique_ptr<IFigure> PointFactory::createFigure(
    FigureParams figure_params) const {
  return std::make_unique<Point>(figure_params.x1, figure_params.y1,
                                 figure_params.color, figure_params.size);
}

std::unique_ptr<IFigure> LineFactory::createFigure(
    FigureParams figure_params) const {
  return std::make_unique<Line>(figure_params.x1, figure_params.y1,
                                figure_params.x2, figure_params.y2,
                                figure_params.color, figure_params.size);
}

std::unique_ptr<IFigure> RectangleFactory::createFigure(
    FigureParams figure_params) const {
  return std::make_unique<Rectangle>(figure_params.x1, figure_params.y1,
                                     figure_params.x2, figure_params.y2,
                                     figure_params.color, figure_params.size);
}
