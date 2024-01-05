#include "s21_maze.h"
#include "s21_cave.h"
#include <cmath>
#include <gtest/gtest.h>
#include <iostream>

TEST(maze_0, test_1) {
  using namespace s21;
  Maze *test = new Maze();
  test->InitMaze(5, 5);
  EXPECT_EQ(test->maze->columns_number, 5);
  delete test;
}

TEST(maze_1, test_1) {
  using namespace s21;
  Maze *test = new Maze();
  test->InitMaze(5, 5);
  test->CreateMaze();
  EXPECT_EQ(test->maze->columns_number, 5);
  delete test;
}

 TEST(maze_2, test_1) {
   using namespace s21;
   Maze *test = new Maze();
   test->InitMaze(4, 4);
   test->SetRowsNumber(5);
   test->SetColumnsNumber(5);
   test->CreateMaze();
   test->SaveMaze((char *)"test-1.mze");
   EXPECT_EQ(test->maze->columns_number, 5);
   delete test;
 }

 TEST(maze_3, test_1) {
   using namespace s21;
   Maze *test = new Maze();
   test->LoadMaze((char *)"test-1.mze");
   EXPECT_EQ(test->maze->columns_number, 5);
   delete test;
 }

 TEST(maze_4, test_1) {
   using namespace s21;
   Maze *test = new Maze();
   test->InitMaze(5, 5);
   test->CreateMaze();
   test->maze->start_answer[0] = 0;
   test->maze->start_answer[1] = 0;
   test->maze->end_answer[0] = 4;
   test->maze->end_answer[1] = 4;
   test->SolveMaze();
   test->PrintMaze();
   EXPECT_EQ(test->maze->answer_lenth, 11);
   delete test;
 }

 TEST(maze_5, test_1) {
   using namespace s21;
   Maze test;
   test.InitMaze(4, 4);
   test.CreateMaze();
   Maze test2((const s21::Maze)test);
   EXPECT_EQ(test2.maze->columns_number, 4);
 }

 TEST(maze_6, test_1) {
   using namespace s21;
   Maze test;
   test.InitMaze(4, 4);
   test.CreateMaze();
   Maze test2 = std::move(s21::Maze(test));
   EXPECT_EQ(test2.maze->columns_number, 4);
 }

 TEST(maze_7, test_1) {
   using namespace s21;
   Maze test;
   test.InitMaze(4, 4);
   test.CreateMaze();
   Maze test2;
   test2 = std::move(s21::Maze(test));
   EXPECT_EQ(test2.maze->columns_number, 4);
 }

 TEST(maze_8, test_1) {
   using namespace s21;
   Maze test;
   test.InitMaze(4, 4);
   test.CreateMaze();
   Maze test2;
   test2 = test;
   EXPECT_EQ(test2.maze->columns_number, 4);
 }

 TEST(cave_0, test_2) {
   using namespace s21;
   Cave *test = new Cave();
   test->InitCave(5, 5);
   test->PrintCave();
   EXPECT_EQ(test->cave->columns_number, 5);
   delete test;
 }

 TEST(cave_1, test_2) {
   using namespace s21;
   Cave *test = new Cave();
   test->InitCave(5, 5);
   test->CreateCave();
   test->SaveCave((char *)"test1.cve");
   EXPECT_EQ(test->cave->columns_number, 5);
   delete test;
 }

 TEST(cave_2, test_2) {
   using namespace s21;
   Cave *test = new Cave();
   test->InitCave(4, 4);
   test->SetRowsNumber(5);
   test->SetColumnsNumber(5);
   test->CreateCave();
   EXPECT_EQ(test->cave->columns_number, 5);
   delete test;
 }

 TEST(cave_3, test_2) {
   using namespace s21;
   Cave *test = new Cave();
   test->InitCave(4, 4);
   test->CreateCave();
   test->CreateNextStepCave();
   EXPECT_EQ(test->cave->columns_number, 4);
   delete test;
 }

 TEST(cave_4, test_2) {
   using namespace s21;
   Cave *test = new Cave();
   test->LoadCave((char *)"test1.cve");
   EXPECT_EQ(test->cave->columns_number, 5);
   delete test;
 }

 TEST(cave_5, test_1) {
   using namespace s21;
   Cave test;
   test.InitCave(4, 4);
   test.CreateCave();
   Cave test2((const s21::Cave)test);
   EXPECT_EQ(test2.cave->columns_number, 4);
 }

 TEST(cave_6, test_1) {
   using namespace s21;
   Cave test;
   test.InitCave(4, 4);
   test.CreateCave();
   Cave test2 = std::move(s21::Cave(test));
   EXPECT_EQ(test2.cave->columns_number, 4);
 }

 TEST(cave_7, test_1) {
   using namespace s21;
   Cave test;
   test.InitCave(4, 4);
   test.CreateCave();
   Cave test2;
   test2 = std::move(s21::Cave(test));
   EXPECT_EQ(test2.cave->columns_number, 4);
 }

 TEST(cave_8, test_1) {
   using namespace s21;
   Cave test;
   test.InitCave(4, 4);
   test.CreateCave();
   Cave test2;
   test2 = test;
   EXPECT_EQ(test2.cave->columns_number, 4);
 }

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
