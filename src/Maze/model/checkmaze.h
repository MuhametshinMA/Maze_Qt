#ifndef CHECKMAZE_H
#define CHECKMAZE_H

#include <memory>
#include <stack>
#include <unordered_set>

#include "maze.h"
#include "position.h"

class CheckMaze {
 public:
  CheckMaze(std::shared_ptr<Maze> maze);

 private:
  void ClearData();
  void DFS();
  bool HasHorisontalWall(const Position& pos) const;
  bool HasVerticalWall(const Position& pos) const;
  void AddToStack(const Position& new_pos);
  bool CheckLeft(const Position& new_pos) const;
  bool CheckUp(const Position& new_pos) const;
  bool CheckRight(const Position& old_pos, const Position& new_pos) const;
  bool CheckDown(const Position& old_pos, const Position& new_pos) const;
  bool IsPositionInMaze(const Position& new_pos) const;
  void SetVisited(const Position& pos);
  bool ContainsInVisited(const Position& pos) const;
  void CheckDeadLock();

  std::shared_ptr<Maze> maze_;
  std::stack<Position> s_positions_;
  std::unordered_set<Position, Position::HashFunction> visited_;
};

#endif  // CHECKMAZE_H
