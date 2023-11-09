#ifndef CONTROLLERFACTORY_H
#define CONTROLLERFACTORY_H

#include <memory>

#include "controllercave.h"
#include "controllermaze.h"

class IControllerFactory {
 public:
  virtual std::shared_ptr<IController> MakeController(const QSize& field) = 0;
  virtual ~IControllerFactory() = default;
};

class MazeControllerFactory : public IControllerFactory {
 public:
  std::shared_ptr<IController> MakeController(const QSize& field) override {
    return std::make_shared<ControllerMaze>(field);
  }
};

class CaveControllerFactory : public IControllerFactory {
 public:
  std::shared_ptr<IController> MakeController(const QSize& field) override {
    return std::make_shared<ControllerCave>(field);
  }
};

#endif  // CONTROLLERFACTORY_H
