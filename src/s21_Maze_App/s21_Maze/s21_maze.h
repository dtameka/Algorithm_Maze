#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <QObject>
#include <QRandomGenerator>
#include <stdio.h>
#include <string.h>

static const int answers_amount = 3000;
static const int maze_file_str_number = 150;
static const int maze_file_str_lenth = 100;

namespace s21 {

typedef struct Maze_scheme {
    int rows_number;
    int columns_number;
    int **rows_right_boder;
    int **columns_bottom_boder;
    int **groups;
    int **answer;
    int answer_lenth;
    int *start_answer;
    int *end_answer;
} Maze_scheme_t;

typedef struct Path {
public: Path() {path = nullptr;}
    int **path;
    int path_lenth;
} Path_t;

class Maze
{
public:
    Maze();
    ~Maze();
    Maze(const Maze &src);
    Maze(Maze &&src);
    Maze operator=(Maze &&src);
    Maze &operator=(const Maze &src);
    void InitMazeScheme();
    void InitMaze(int rows_number, int columns_number);
    void DeleteMaze();
    int SetRowsNumber(int rows_number);
    int SetColumnsNumber(int columns_number);

    int LoadMaze(char *maze_file_path);
    int SaveMaze(char *maze_file_path);
    void ReadStrFromFile(FILE *maze_file, char **temp_maze_str);
    int ReadMazeFromStr(char **temp_maze_str);
    int ReadMazeRightBoderFromStr(char **temp_maze_str);
    int ReadMazeColumnsBottomFromStr(char **temp_maze_str);
    void CreateMaze(void);
    void SolveMaze(void);
    void PrintMaze();
    Maze_scheme_t *maze;

private:
    void CopyMaze(const Maze &src);
    void MoveGroupsDownFromStart(int row_number);
    void CreateRandomRightBorder(int row_number);
    void CollectToGroupsInRow(int row_number);
    void CreateRandomBottomBorder(int row_number);
    void CheckBottomBoder(int row_number);
    void CheckBottomBoderCurrentGroup(int row_number, int *current_group, int *pos);
    void MoveGroupsDown(int row_number);
    void CheckLastRow(int row_number);
    QRandomGenerator generator;

    bool CheckForCorrectTask(void);
    void InitPath(Path_t *path);
    void DeletePath(Path_t *path);
    void SearchNextCell(Path_t *path, int x, int y);
    void SearchUP(Path_t *path, int x, int y);
    void SearchDown(Path_t *path, int x, int y);
    void SearchLeft(Path_t *path, int x, int y);
    void SearchRight(Path_t *path, int x, int y);
    int CheckForVisitedCell(Path_t *path, int x, int y);
    void CopySearchPath(Path_t *dist, Path_t *src);
    void CopyPathToMaze(Path_t *path);

    int path_amount_;
};

} // namespace s21

#endif // MAZE_H
