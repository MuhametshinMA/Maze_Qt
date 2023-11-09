#include "path.h"

Path::Path(const Maze& maze) : maze_{maze} {}

std::vector<Position> Path::FindPath(const Position& begin_pos,
                                     const Position& end_pos) {
  if (!IsPositionInMaze(begin_pos) || !IsPositionInMaze(end_pos))
    throw std::invalid_argument(
        "Begin or end position of search path is not at maze! Check "
        "borders!");
  ClearData();
  begin_pos_ = begin_pos;
  end_pos_ = end_pos;
  q_positions_.push(begin_pos_);
  SetVisited(begin_pos_);
  RunWave();
  return result_path_;
}

void Path::ClearData() {
  q_positions_ = std::queue<Position>();
  result_path_.clear();
  visited_.clear();
  steps_.clear();
  path_is_finded_ = false;
}

void Path::RunWave() {
  while (!q_positions_.empty()) {
    Position pos = q_positions_.front();
    q_positions_.pop();
    if (CheckLeft(pos.Left())) AddPosToQueue(pos, pos.Left());
    if (CheckUp(pos.Up())) AddPosToQueue(pos, pos.Up());
    if (CheckRight(pos, pos.Right())) AddPosToQueue(pos, pos.Right());
    if (CheckDown(pos, pos.Down())) AddPosToQueue(pos, pos.Down());
  }
}

void Path::AddPosToQueue(const Position& old_pos, const Position& new_pos) {
  if (!ContainsInVisited(new_pos)) {
    SetVisited(new_pos);
    q_positions_.push(new_pos);
    steps_.insert({new_pos, old_pos});
    if (new_pos == end_pos_) {
      SavePathToVector();
      q_positions_ = std::queue<Position>();
      path_is_finded_ = true;
    }
  }
}

void Path::SavePathToVector() {
  Position pos = q_positions_.back();
  result_path_.push_back(pos);
  while (pos != begin_pos_) {
    pos = steps_[pos];
    result_path_.push_back(pos);
  }
  std::reverse(result_path_.begin(), result_path_.end());
}

bool Path::ContainsInVisited(const Position& pos) const {
  return visited_.find(pos) != visited_.end();
}

bool Path::CheckLeft(const Position& new_pos) const {
  return CheckFinishAndCorrectBorder(new_pos) && !HasVerticalWall(new_pos);
}

bool Path::CheckUp(const Position& new_pos) const {
  return CheckFinishAndCorrectBorder(new_pos) && !HasHorisontalWall(new_pos);
}

bool Path::CheckRight(const Position& old_pos, const Position& new_pos) const {
  return CheckFinishAndCorrectBorder(new_pos) && !HasVerticalWall(old_pos);
}

bool Path::CheckDown(const Position& old_pos, const Position& new_pos) const {
  return CheckFinishAndCorrectBorder(new_pos) && !HasHorisontalWall(old_pos);
}

bool Path::CheckFinishAndCorrectBorder(const Position& new_pos) const {
  return !path_is_finded_ && IsPositionInMaze(new_pos);
}

bool Path::IsPositionInMaze(const Position& new_pos) const {
  int i = new_pos.i();
  int j = new_pos.j();
  if (i >= 0 && i < static_cast<int>(maze_.GetRows()) && j >= 0 &&
      j < static_cast<int>(maze_.GetCols()))
    return true;
  return false;
}

bool Path::HasHorisontalWall(const Position& pos) const {
  return maze_.GetHorizontalWall(pos);
}

bool Path::HasVerticalWall(const Position& pos) const {
  return maze_.GetVerticalWall(pos);
}

void Path::SetVisited(const Position& pos) { visited_.insert(pos); }
