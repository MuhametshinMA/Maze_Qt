#include "canvasmaze.h"

CanvasMaze::CanvasMaze(Maze& maze, const QSize& field)
    : maze_{maze}, height_{field.height() - 2}, width_{field.width() - 2} {
  InitSizes();
}

void CanvasMaze::InitSizes() {
  rows_ = maze_.GetRows();
  cols_ = maze_.GetCols();
  shift_r_ = height_ / rows_;
  shift_c_ = width_ / cols_;
  center_r_ = shift_r_ / 2;
  center_c_ = shift_c_ / 2;
  start_r_ = 1 + (height_ - shift_r_ * rows_) / 2;
  start_c_ = 1 + (width_ - shift_c_ * cols_) / 2;
  end_r_ = start_r_ + rows_ * shift_r_;
  end_c_ = start_c_ + cols_ * shift_c_;
  line_ = std::make_unique<LineFactory>();
  point_ = std::make_unique<PointFactory>();
}

void CanvasMaze::CreateMazeFigures() {
  ClearPoints();
  CreateLine(start_c_, start_r_, start_c_, end_r_, Qt::gray, 2);
  CreateLine(start_c_, start_r_, end_c_, start_r_, Qt::gray, 2);
  CreateVerticalWalls();
  CreateHorizontalWalls();
}

void CanvasMaze::CreateVerticalWalls() {
  for (int r = 0; r < rows_; ++r) {
    for (int c = 0; c < cols_; ++c) {
      if (maze_.GetVerticalWall(r, c)) {
        int x = start_c_ + (c + 1) * shift_c_;
        int y1 = start_r_ + r * shift_r_;
        int y2 = y1 + shift_r_;
        CreateLine(x, y1, x, y2, Qt::gray, 2);
      }
    }
  }
}

void CanvasMaze::CreateHorizontalWalls() {
  for (int r = 0; r < rows_; ++r) {
    for (int c = 0; c < cols_; ++c) {
      if (maze_.GetHorizontalWall(r, c)) {
        int x1 = start_c_ + c * shift_c_;
        int x2 = x1 + shift_c_;
        int y = start_r_ + (r + 1) * shift_r_;
        CreateLine(x1, y, x2, y, Qt::gray, 2);
      }
    }
  }
}

void CanvasMaze::CreatePoint(size_t x, size_t y) {
  size_t row = x / shift_r_;
  if (row >= rows_) row = rows_ - 1;
  size_t col = y / shift_c_;
  if (col >= cols_) col = cols_ - 1;

  if (path_positions_.size() == 2) {
    point_layer_.pop_back();
    path_positions_.pop_back();
  }

  if (path_positions_.empty() || path_positions_.back() != Position(row, col)) {
    path_positions_.push_back(Position(row, col));
    Position pos = GetRealPosition(col, row);
    point_layer_.push_back(
        point_->CreateFigure({pos.j(), pos.i(), 0, 0, Qt::black, 6}));
  }
  DrawPath();
}

std::vector<std::shared_ptr<IFigure>>& CanvasMaze::GetFigures() {
  figures_.clear();
  figures_.insert(figures_.end(), walls_layer_.begin(), walls_layer_.end());
  figures_.insert(figures_.end(), point_layer_.begin(), point_layer_.end());
  figures_.insert(figures_.end(), path_layer_.begin(), path_layer_.end());
  return figures_;
}

void CanvasMaze::ClearPoints() {
  path_positions_.clear();
  point_layer_.clear();
}

void CanvasMaze::ClearPath() { path_layer_.clear(); }

void CanvasMaze::DrawPath() {
  ClearPath();
  if (path_positions_.size() != 2) return;
  path_ = std::make_shared<Path>(maze_);
  std::vector<Position> path =
      path_->FindPath(path_positions_[0], path_positions_[1]);
  if (path.empty()) {
    ClearPoints();
    return;
  }
  for (auto it = path.begin(); it != --path.end(); ++it) {
    Position pos1 = GetRealPosition(it[0].j(), it[0].i());
    Position pos2 = GetRealPosition(it[1].j(), it[1].i());
    path_layer_.push_back(line_->CreateFigure(
        {pos1.j(), pos1.i(), pos2.j(), pos2.i(), Qt::red, 2}));
  }
}

Position CanvasMaze::GetRealPosition(size_t x, size_t y) {
  return Position(y * shift_r_ + center_r_ + start_r_,
                  x * shift_c_ + center_c_ + start_c_);
}

void CanvasMaze::CreateLine(const int& x1, const int& y1, const int& x2,
                            const int& y2, QColor color, const int& size) {
  walls_layer_.push_back(line_->CreateFigure({x1, y1, x2, y2, color, size}));
}
