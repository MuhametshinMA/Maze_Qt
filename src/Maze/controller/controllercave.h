#ifndef CONTROLLERCAVE_H
#define CONTROLLERCAVE_H

#include <QSize>
#include <memory>

#include "canvascave.h"
#include "cave.h"
#include "cave_data.h"
#include "figure.h"
#include "icontroller.h"

class ControllerCave : public IController {
 public:
  ControllerCave(const QSize& field);
  void Generate(CaveData) override;
  void LastEvolution(int, int) override;
  void NextStepEvolution(int, int, int) override;
  void FileOpen(std::string) override;
  void FileSave(std::string) override;
  std::shared_ptr<Cave>& GetCave();
  std::vector<std::shared_ptr<IFigure>> GetFigures() override;
  void ClearGraph() override;

 private:
  std::shared_ptr<Cave> cave_;
  std::shared_ptr<CanvasCave> canvas_cave_;
  QSize field_;
};

#endif  // CONTROLLERCAVE_H
