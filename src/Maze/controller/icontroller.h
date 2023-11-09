#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <QSize>

#include "cave_data.h"
#include "figure.h"

class IController {
 public:
  virtual ~IController() = default;
  virtual void Generate(CaveData) {}
  virtual void Generate(const size_t& rows, const size_t& cols) {}
  virtual void ClearPath() {}
  virtual void ClearGraph() {}
  virtual std::vector<std::shared_ptr<IFigure>> GetFigures() = 0;
  virtual void SetPoint(size_t, size_t) {}
  virtual void CreateMazeFigures() {}
  virtual void LastEvolution(int, int) {}
  virtual void NextStepEvolution(int, int, int) {}
  virtual void FileOpen(std::string) {}
  virtual void FileSave(std::string) {}
};

#endif  // ICONTROLLER_H
