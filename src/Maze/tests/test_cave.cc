#include <gtest/gtest.h>

#include <memory>

#include "../model/cave.h"
#include "../model/cave_data.h"

std::string currentFilePathCave = __FILE__;
std::string directoryPathCave =
    currentFilePathCave.substr(0, currentFilePathCave.find_last_of("/")) +
    "/cave_data_tests/";

TEST(CreateCave, Cave_1) { ASSERT_NO_THROW(Cave m); }

TEST(CreateCave, Cave_2) { ASSERT_NO_THROW(Cave m(CaveData(30.0, 10, 10))); }

TEST(CreateCave, Cave_3) {
  ASSERT_THROW(Cave m(CaveData(30.0, 0, 10)), std::invalid_argument);
}

TEST(CreateCave, Cave_4) {
  ASSERT_THROW(Cave m(CaveData(0.0, 10, 10)), std::invalid_argument);
}

TEST(OpenFile, Cave_5) {
  std::string mazeFilePath = directoryPathCave + "test_10x10.txt";
  Cave m;
  m.ResizeCavePath(mazeFilePath);
  Cave m2(m);
  ASSERT_EQ(m.MatrixEquals(m2.GetMatrix()), 1);
}

TEST(GenerateCave, Cave_6) {
  std::string mazeFilePath = directoryPathCave + "test_10x10.txt";
  Cave m;
  m.ResizeCavePath(mazeFilePath);
  for (int i = 0; i < 8; ++i) {
    m.NextStepEvolution(4, 3);
  }
  Cave m2;
  mazeFilePath = directoryPathCave + "test_10x10_result.txt";
  m2.ResizeCavePath(mazeFilePath);
  ASSERT_EQ(m.MatrixEquals(m2.GetMatrix()), 1);
}
