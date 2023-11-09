#include "controllercave.h"

ControllerCave::ControllerCave(const QSize& field) : field_{field} {
  try {
    cave_ = std::make_shared<Cave>();
    canvas_cave_ = std::make_shared<CanvasCave>(*cave_, field_);
    canvas_cave_->CreateCaveFigures();
  } catch (const std::exception& e) {
    std::cout << e.what();
  }
}

void ControllerCave::Generate(CaveData data) {
  try {
    cave_ = std::make_shared<Cave>(data);
    canvas_cave_ = std::make_shared<CanvasCave>(*cave_, field_);
    canvas_cave_->CreateCaveFigures();
  } catch (const std::exception& e) {
    std::cout << e.what();
  }
}

void ControllerCave::LastEvolution(int birth, int death) {
  cave_->NextStepEvolution(birth, death);
  canvas_cave_->CreateCaveFigures();
}

void ControllerCave::NextStepEvolution(int step, int birth, int death) {
  for (int i = 0; i < step; i++) {
    cave_->NextStepEvolution(birth, death);
    canvas_cave_->CreateCaveFigures();
  }
}

void ControllerCave::FileOpen(std::string path) {
  try {
    cave_->ResizeCavePath(path);
    canvas_cave_->CreateCaveFigures();
  } catch (const std::exception& e) {
    std::cout << e.what();
  }
}

void ControllerCave::FileSave(std::string path) {
  try {
    cave_->SaveFile(path);
  } catch (const std::exception& e) {
    std::cout << e.what();
  }
}

std::vector<std::shared_ptr<IFigure>> ControllerCave::GetFigures() {
  return canvas_cave_->GetFigures();
}

void ControllerCave::ClearGraph() { canvas_cave_->ClearFigures(); }
