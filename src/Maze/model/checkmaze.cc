#include "checkmaze.h"

CheckMaze::CheckMaze(std::shared_ptr<Maze> maze) : maze_(maze) {
  ClearData();
  DFS();
}

void CheckMaze::ClearData() {
  s_positions_ = std::stack<Position>();
  visited_.clear();
}

void CheckMaze::DFS() {
  Position pos(0, 0);
  s_positions_.push(pos);
  while (!s_positions_.empty()) {
    pos = s_positions_.top();
    s_positions_.pop();

    if (ContainsInVisited(pos))
      throw std::invalid_argument("Maze is not ideal! It's has a loop(s)");

    SetVisited(pos);
    if (CheckLeft(pos.Left())) AddToStack(pos.Left());
    if (CheckUp(pos.Up())) AddToStack(pos.Up());
    if (CheckRight(pos, pos.Right())) AddToStack(pos.Right());
    if (CheckDown(pos, pos.Down())) AddToStack(pos.Down());
  }
  CheckDeadLock();
}

void CheckMaze::CheckDeadLock() {
  if (visited_.size() != maze_->GetRows() * maze_->GetCols())
    throw std::invalid_argument("Maze is not ideal! It's has a deadlock(s)");
}

void CheckMaze::AddToStack(const Position& new_pos) {
  if (!ContainsInVisited(new_pos)) {
    s_positions_.push(new_pos);
  }
}

bool CheckMaze::CheckLeft(const Position& new_pos) const {
  return IsPositionInMaze(new_pos) && !HasVerticalWall(new_pos);
}

bool CheckMaze::CheckUp(const Position& new_pos) const {
  return IsPositionInMaze(new_pos) && !HasHorisontalWall(new_pos);
}

bool CheckMaze::CheckRight(const Position& old_pos,
                           const Position& new_pos) const {
  return IsPositionInMaze(new_pos) && !HasVerticalWall(old_pos);
}

bool CheckMaze::CheckDown(const Position& old_pos,
                          const Position& new_pos) const {
  return IsPositionInMaze(new_pos) && !HasHorisontalWall(old_pos);
}

bool CheckMaze::IsPositionInMaze(const Position& new_pos) const {
  int i = new_pos.i();
  int j = new_pos.j();
  if (i >= 0 && i < static_cast<int>(maze_->GetRows()) && j >= 0 &&
      j < static_cast<int>(maze_->GetCols()))
    return true;
  return false;
}

bool CheckMaze::HasHorisontalWall(const Position& pos) const {
  return maze_->GetHorizontalWall(pos);
}

bool CheckMaze::HasVerticalWall(const Position& pos) const {
  return maze_->GetVerticalWall(pos);
}

bool CheckMaze::ContainsInVisited(const Position& pos) const {
  return visited_.find(pos) != visited_.end();
}

void CheckMaze::SetVisited(const Position& pos) { visited_.insert(pos); }
