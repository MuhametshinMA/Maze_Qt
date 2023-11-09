#include "controllermaze.h"

#include "filemanager.h"

void ControllerMaze::SetPoint(size_t x, size_t y) {
  canvas_maze_->CreatePoint(x, y);
}

ControllerMaze::ControllerMaze(const QSize& field) : field_{field} {
  maze_ = std::make_shared<Maze>();
  maze_->GenerateMaze(1, 1);
  canvas_maze_ = std::make_shared<CanvasMaze>(*maze_, field_);
  canvas_maze_->CreateMazeFigures();
}

void ControllerMaze::Generate(const size_t& rows, const size_t& cols) {
  maze_ = std::make_shared<Maze>();
  maze_->GenerateMaze(rows, cols);
  canvas_maze_ = std::make_shared<CanvasMaze>(*maze_, field_);
  CreateMazeFigures();
}

void ControllerMaze::CreateMazeFigures() { canvas_maze_->CreateMazeFigures(); }

std::vector<std::shared_ptr<IFigure>> ControllerMaze::GetFigures() {
  return canvas_maze_->GetFigures();
}

void ControllerMaze::ClearPath() {
  canvas_maze_->ClearPoints();
  canvas_maze_->ClearPath();
}

void ControllerMaze::FileSave(std::string path) {
  std::unique_ptr<FileManager> fm = std::make_unique<FileManager>();
  try {
    fm->SaveMazeToFile(*maze_, path);
  } catch (const std::exception& e) {
  }
}

void ControllerMaze::FileOpen(std::string path) {
  std::unique_ptr<FileManager> fm = std::make_unique<FileManager>();
  try {
    maze_ = std::make_shared<Maze>(fm->LoadMazeFromFile(path));
    canvas_maze_ = std::make_shared<CanvasMaze>(*maze_, field_);
    CreateMazeFigures();
  } catch (const std::exception& e) {
  }
}
