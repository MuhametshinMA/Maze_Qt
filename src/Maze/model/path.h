#ifndef PATH_H
#define PATH_H

#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "maze.h"
#include "position.h"

class Path {
 public:
  Path(const Maze& maze);
  std::vector<Position> FindPath(const Position& begin_pos,
                                 const Position& end_pos);

 private:
  void ClearData();
  void RunWave();
  bool IsPositionInMaze(const Position& new_pos) const;
  bool HasHorisontalWall(const Position& pos) const;
  bool HasVerticalWall(const Position& pos) const;
  bool CheckLeft(const Position& new_pos) const;
  bool CheckUp(const Position& new_pos) const;
  bool CheckRight(const Position& old_pos, const Position& new_pos) const;
  bool CheckDown(const Position& old_pos, const Position& new_pos) const;
  bool CheckFinishAndCorrectBorder(const Position& new_pos) const;
  void AddPosToQueue(const Position& old_pos, const Position& new_pos);
  void SetVisited(const Position& pos);
  void SavePathToVector();
  bool ContainsInVisited(const Position& pos) const;

  Maze maze_;
  Position begin_pos_;
  Position end_pos_;
  std::queue<Position> q_positions_;
  std::vector<Position> result_path_;
  std::unordered_set<Position, Position::HashFunction> visited_;
  std::unordered_map<Position, Position, Position::HashFunction> steps_;
  bool path_is_finded_;
};

#endif  // PATH_H
