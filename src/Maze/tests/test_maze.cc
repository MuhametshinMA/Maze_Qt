#include <gtest/gtest.h>

#include <memory>

#include "../model/checkmaze.h"
#include "../model/filemanager.h"
#include "../model/maze.h"
#include "../model/path.h"
#include "../model/position.h"

std::string currentFilePath = __FILE__;
std::string directoryPath =
    currentFilePath.substr(0, currentFilePath.find_last_of("/")) +
    "/maze_data_tests/";

TEST(CreateMaze, Maze_1) { ASSERT_NO_THROW(Maze m(7, 8)); }

TEST(CreateMaze, Maze_2) { ASSERT_THROW(Maze m(0, 8), std::invalid_argument); }

TEST(CreateMaze, Maze_3) { ASSERT_THROW(Maze m(0, 0), std::invalid_argument); }

TEST(CreateMaze, Maze_4) { ASSERT_THROW(Maze m(-1, 2), std::invalid_argument); }

TEST(IdealMaze, Maze_1) {
  std::shared_ptr<Maze> m = std::make_shared<Maze>();
  m->GenerateMaze(7, 8);
  ASSERT_NO_THROW(CheckMaze check(m));
}

TEST(IdealMaze, Maze_2) {
  std::shared_ptr<Maze> m = std::make_shared<Maze>();
  std::random_device device;
  std::mt19937 gen(device());
  std::uniform_int_distribution<size_t> rows(1, 50), cols(1, 50);

  for (int i = 0; i < 200; ++i) {
    m->GenerateMaze(rows(gen), cols(gen));
    ASSERT_NO_THROW(CheckMaze check(m));
  }
}

TEST(LoadMaze, Maze_1) {
  FileManager mgr;
  std::shared_ptr<Maze> m = std::make_shared<Maze>();
  std::string mazeFilePath = directoryPath + "ideal_5x5";
  m = std::make_shared<Maze>(mgr.LoadMazeFromFile(mazeFilePath));
  ASSERT_NO_THROW(CheckMaze check(m));
}

TEST(LoadMaze, Maze_2) {
  FileManager mgr;
  std::shared_ptr<Maze> m = std::make_shared<Maze>();
  std::string mazeFilePath = directoryPath + "ideal_4x7";
  m = std::make_shared<Maze>(mgr.LoadMazeFromFile(mazeFilePath));
  ASSERT_NO_THROW(CheckMaze check(m));
}

TEST(LoadMaze, Maze_Ugly_1) {
  FileManager mgr;
  std::shared_ptr<Maze> m = std::make_shared<Maze>();
  std::string mazeFilePath = directoryPath + "ugly_4x3";
  m = std::make_shared<Maze>(mgr.LoadMazeFromFile(mazeFilePath));
  ASSERT_THROW(CheckMaze check(m), std::invalid_argument);
}

TEST(LoadMaze, Maze_Ugly_2) {
  FileManager mgr;
  std::shared_ptr<Maze> m = std::make_shared<Maze>();
  std::string mazeFilePath = directoryPath + "ugly_4x3";
  m = std::make_shared<Maze>(mgr.LoadMazeFromFile(mazeFilePath));
  ASSERT_THROW(CheckMaze check(m), std::invalid_argument);
}

TEST(LoadMaze, Maze_Ugly_3) {
  FileManager mgr;
  std::shared_ptr<Maze> m = std::make_shared<Maze>();
  std::string mazeFilePath = directoryPath + "ugly_4x4";

  m = std::make_shared<Maze>(mgr.LoadMazeFromFile(mazeFilePath));
  ASSERT_THROW(CheckMaze check(m), std::invalid_argument);
}

TEST(FindPath, Maze_1) {
  FileManager mgr;
  std::shared_ptr<Maze> m = std::make_shared<Maze>();
  std::string mazeFilePath = directoryPath + "ideal_5x5";
  m = std::make_shared<Maze>(mgr.LoadMazeFromFile(mazeFilePath));
  Path p(*m);
  std::vector<Position> path_pos = p.FindPath(Position(0, 3), Position(4, 2));
  std::vector<std::pair<int, int>> expect_path{{0, 3}, {1, 3}, {1, 2}, {0, 2},
                                               {0, 1}, {0, 0}, {1, 0}, {2, 0},
                                               {3, 0}, {4, 0}, {4, 1}, {4, 2}};
  for (size_t i = 0; i < expect_path.size(); ++i) {
    EXPECT_EQ(path_pos[i].i(), expect_path[i].first);
    EXPECT_EQ(path_pos[i].j(), expect_path[i].second);
  }
}

TEST(FindPath, Maze_2) {
  FileManager mgr;
  std::shared_ptr<Maze> m = std::make_shared<Maze>();
  std::string mazeFilePath = directoryPath + "ideal_5x5";
  m = std::make_shared<Maze>(mgr.LoadMazeFromFile(mazeFilePath));
  Path p(*m);
  std::vector<Position> path_pos = p.FindPath(Position(0, 3), Position(0, 3));
  EXPECT_TRUE(path_pos.empty());
}

TEST(FindPath, Maze_3) {
  FileManager mgr;
  std::shared_ptr<Maze> m = std::make_shared<Maze>();
  std::string mazeFilePath = directoryPath + "ideal_5x5";
  m = std::make_shared<Maze>(mgr.LoadMazeFromFile(mazeFilePath));

  Path p(*m);
  ASSERT_THROW(p.FindPath(Position(0, 5), Position(0, 3)),
               std::invalid_argument);
}

TEST(FindPath, Maze_4) {
  FileManager mgr;
  std::shared_ptr<Maze> m = std::make_shared<Maze>();
  std::string mazeFilePath = directoryPath + "not_ideal_5x5_1";
  m = std::make_shared<Maze>(mgr.LoadMazeFromFile(mazeFilePath));

  Path p(*m);
  std::vector<Position> path_pos = p.FindPath(Position(0, 3), Position(4, 2));
  EXPECT_TRUE(path_pos.empty());
}

TEST(FindPath, Maze_5) {
  FileManager mgr;
  std::shared_ptr<Maze> m = std::make_shared<Maze>();
  std::string mazeFilePath = directoryPath + "not_ideal_5x5_2";
  m = std::make_shared<Maze>(mgr.LoadMazeFromFile(mazeFilePath));

  Path p(*m);
  std::vector<Position> path_pos = p.FindPath(Position(0, 3), Position(4, 2));
  std::vector<std::pair<int, int>> expect_path{{0, 3}, {1, 3}, {2, 3},
                                               {3, 3}, {4, 3}, {4, 2}};
  for (size_t i = 0; i < expect_path.size(); ++i) {
    EXPECT_EQ(path_pos[i].i(), expect_path[i].first);
    EXPECT_EQ(path_pos[i].j(), expect_path[i].second);
  }
}
