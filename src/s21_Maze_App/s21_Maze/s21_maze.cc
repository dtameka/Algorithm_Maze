#include "s21_maze.h"

s21::Maze::Maze()
{
   InitMazeScheme();
   path_amount_ = 0;
}

s21::Maze::~Maze(){
    DeleteMaze();
    delete maze;
}

s21::Maze::Maze(const Maze &src) {
    InitMazeScheme();
    CopyMaze(src);
}

s21::Maze::Maze(Maze &&src) {
    InitMazeScheme();
    CopyMaze(src);
    src.DeleteMaze();
}

s21::Maze s21::Maze::operator=(Maze &&src) {
    CopyMaze(src);
    src.DeleteMaze();
    return *this;
}

s21::Maze &s21::Maze::operator=(const Maze &src) {
    CopyMaze(src);
    return *this;
}

void s21::Maze::CopyMaze(const Maze &src) {
    InitMaze(src.maze->rows_number, src.maze->columns_number);
    for (int i = 0 ; i < src.maze->rows_number; ++i) {
        for (int j = 0; j < src.maze->rows_number; ++j) {
            this->maze->rows_right_boder[i][j] = src.maze->rows_right_boder[i][j];
            this->maze->columns_bottom_boder[i][j] = src.maze->columns_bottom_boder[i][j];
            this->maze->groups[i][j] = src.maze->groups[i][j];
        }
    }
    for (int j = 0; j < answers_amount; ++j) {
        this->maze->answer[j][0] = src.maze->answer[j][0];
        this->maze->answer[j][1] = src.maze->answer[j][1];
    }
    this->maze->start_answer[0] = src.maze->start_answer[0];
    this->maze->start_answer[1] = src.maze->start_answer[1];
    this->maze->end_answer[0] = src.maze->end_answer[0];
    this->maze->end_answer[1] = src.maze->end_answer[1];
    this->maze->answer_lenth = src.maze->answer_lenth;
}

void s21::Maze::InitMazeScheme() {
    maze = new Maze_scheme_t;
    maze->rows_number = 0;
    maze->columns_number = 0;
    maze->rows_right_boder = nullptr;
    maze->columns_bottom_boder = nullptr;
    maze->groups = nullptr;
    maze->answer = nullptr;
    maze->answer_lenth = 0;
    maze->start_answer = nullptr;
    maze->end_answer = nullptr;
}

void s21::Maze::InitMaze(int rows_number, int columns_number) {
    if (maze == nullptr) {
         maze = new Maze_scheme_t;
    } else {
        DeleteMaze();
    }
    if (rows_number <=  0 || columns_number <= 0) {
        maze->rows_number = 0;
        maze->columns_number = 0;
    } else {
        maze->rows_number = rows_number;
        maze->columns_number = columns_number;
        maze->rows_right_boder = new int*[rows_number];
        maze->columns_bottom_boder = new int*[rows_number];
        maze->groups = new int*[rows_number];
        for (int i = 0 ; i < rows_number; ++i) {
            maze->rows_right_boder[i] = new int[columns_number];
                for (int j = 0; j < columns_number; ++j) {
                    if (j < columns_number - 1) {
                        maze->rows_right_boder[i][j] = 0;
                    } else {
                        maze->rows_right_boder[i][j] = 1;
                    }
                }
        }
        for (int i = 0 ; i < rows_number; ++i) {
            maze->columns_bottom_boder[i] = new int[columns_number];
            for (int j = 0; j < columns_number; ++j) {
                if (i < rows_number - 1) {
                    maze->columns_bottom_boder[i][j] = 0;
                } else {
                    maze->columns_bottom_boder[i][j] = 1;
                }
            }
        }
        for (int i = 0 ; i < rows_number; ++i) {
            maze->groups[i] = new int[columns_number];
            for (int j = 0; j < columns_number; ++j) {
                maze->groups[i][j] = j;
            }
        }
        maze->answer = new int*[answers_amount];
        for (int j = 0; j < answers_amount; ++j) {
            maze->answer[j] = new int[2];
            maze->answer[j][0] = 0;
            maze->answer[j][1] = 0;
        }
        maze->start_answer = new int[2];
        maze->start_answer[0] = 0;
        maze->start_answer[1] = 0;
        maze->end_answer = new int[2];
        maze->end_answer[0] = 0;
        maze->end_answer[1] = 0;
        maze->answer_lenth = 0;
    }
}

void s21::Maze::DeleteMaze() {
    if (maze->rows_number > 0 && maze->columns_number > 0) {
        for (int i = 0 ; i < maze->rows_number; ++i) {
            delete[] maze->rows_right_boder[i];
        }
        for (int i = 0 ; i < maze->rows_number; ++i) {
            delete[] maze->columns_bottom_boder[i];
        }
        for (int i = 0 ; i < maze->rows_number; ++i) {
            delete[] maze->groups[i];
        }
        delete[] maze->rows_right_boder;
        delete[] maze->columns_bottom_boder;
        delete[] maze->groups;
        maze->rows_number = 0;
        maze->columns_number = 0;
        for (int j = 0; j < answers_amount; ++j) {
            delete[] maze->answer[j];
        }
        delete[] maze->answer;
        delete[] maze->start_answer;
        delete[] maze->end_answer;
        maze->rows_right_boder = nullptr;
        maze->columns_bottom_boder = nullptr;
        maze->groups = nullptr;
        maze->answer = nullptr;
        maze->answer_lenth = 0;
        maze->start_answer = nullptr;
        maze->end_answer = nullptr;
    }
}

int s21::Maze::SetRowsNumber(int rows_number) {
    int error = 0;
    if (rows_number > 0) {
        int temp_columns_number = maze->columns_number;
        DeleteMaze();
        InitMaze(rows_number, temp_columns_number);
    } else {
        error = 1;
    }
    return error;
}

int s21::Maze::SetColumnsNumber(int columns_number) {
    int error = 0;
    if (columns_number > 0) {
        int temp_rows_number = maze->rows_number;
        DeleteMaze();
        InitMaze(temp_rows_number, columns_number);
    } else {
        error = 1;
    }
    return error;
}

int s21::Maze::LoadMaze(char *maze_file_path) {
     FILE *maze_file;
     int error = 0;
     if ((maze_file = fopen(maze_file_path, "r")) == NULL) {
         error = 1;
     } else {
         char **temp_maze_str = nullptr;
          temp_maze_str = new char*[maze_file_str_number];
          for (int i = 0; i < maze_file_str_number; ++i) {
              temp_maze_str[i] = new char[maze_file_str_lenth];
              for (int j = 0; j < maze_file_str_lenth; ++j) {
                  temp_maze_str[i][j] = '\0';
              }
          }
         ReadStrFromFile(maze_file, temp_maze_str);
         error = ReadMazeFromStr(temp_maze_str);
         fclose(maze_file);
         for (int i = 0; i < maze_file_str_number; ++i) delete[] temp_maze_str[i];
         delete[] temp_maze_str;
     }
     return error;
}

int s21::Maze::SaveMaze(char *maze_file_path) {
    FILE *maze_file;
    int error = 0;
    if ((maze_file = fopen(maze_file_path, "w")) == NULL) {
        error = 1;
    } else {
        fprintf(maze_file, "%d %d\n", this->maze->rows_number, this->maze->columns_number);
        for (int i = 0; i < this->maze->rows_number; ++i) {
            for (int j = 0; j < this->maze->columns_number; ++j) {
               fprintf(maze_file, "%d ", this->maze->rows_right_boder[i][j]);
            }
            fprintf(maze_file, "\n");
        }
        fprintf(maze_file, "\n");
        for (int i = 0; i < this->maze->rows_number; ++i) {
            for (int j = 0; j < this->maze->columns_number; ++j) {
                fprintf(maze_file, "%d ", this->maze->columns_bottom_boder[i][j]);
            }
           fprintf(maze_file, "\n");
        }
        fclose(maze_file);
    }
    return error;
}

void s21::Maze::ReadStrFromFile(FILE *maze_file, char **temp_maze_str) {
    char letter;
    int counter = 0, str_counter = 0, temp_str_counter = 0;
    while (!feof(maze_file)) {
      letter = fgetc(maze_file);
      if (letter == 10 || letter == EOF) {
        if (letter == EOF) {
          temp_maze_str[str_counter][counter] = '\0';
          break;
        } else {
          temp_maze_str[str_counter][counter] = '\0';
          printf("\n");
        }
        counter = 0;
        str_counter++;
      } else {
        temp_maze_str[str_counter][counter] = letter;
        counter++;
      }
    }
}


int s21::Maze::ReadMazeFromStr(char **temp_maze_str) {
   int error = 0;
   int rows_number = 0;
   int columns_number = 0;
   sscanf((const char *) temp_maze_str[0], "%d%d", &rows_number, &columns_number);
   if (rows_number > 0 && columns_number > 0) {
       this->InitMaze(rows_number, columns_number);
       error = ReadMazeRightBoderFromStr(temp_maze_str);
       if (error == 0) error = ReadMazeColumnsBottomFromStr(temp_maze_str);

   } else {
       error = 1;
   }
   return error;
}

int s21::Maze::ReadMazeRightBoderFromStr(char **temp_maze_str) {
    int error = 0;
    int rows_number = 0;
    int columns_number = 0;
    int rows_counter = 0;
    int columns_counter = 0;
    int columns_counter_for_maze = 0;
    sscanf((const char *) temp_maze_str[0], "%d%d", &rows_number, &columns_number);
    for (int i = 1; i < rows_number + 1; ++i) {
        while (temp_maze_str[i][columns_counter] != '\0') {
            if (temp_maze_str[i][columns_counter] == ' ') {
                columns_counter++;
                continue;
            } else if (temp_maze_str[i][columns_counter] == '0' || temp_maze_str[i][columns_counter] == '1') {
                this->maze->rows_right_boder[rows_counter][columns_counter_for_maze] = temp_maze_str[i][columns_counter] - 48;
                columns_counter++;
                columns_counter_for_maze++;
            } else {
                error = 1;
                break;
            }
        }
        rows_counter++;
        columns_counter = 0;
        columns_counter_for_maze = 0;
    }
    return error;
}

int s21::Maze::ReadMazeColumnsBottomFromStr(char **temp_maze_str) {
    int error = 0;
    int rows_number = 0;
    int columns_number = 0;
    int rows_counter = 0;
    int columns_counter = 0;
    int columns_counter_for_maze = 0;
    sscanf((const char *) temp_maze_str[0], "%d%d", &rows_number, &columns_number);
    for (int i = rows_number + 2; i < 2 * rows_number + 3; ++i) {
        while (temp_maze_str[i][columns_counter] != '\0') {
            if (temp_maze_str[i][columns_counter] == ' ') {
                columns_counter++;
                continue;
            } else if (temp_maze_str[i][columns_counter] == '0' || temp_maze_str[i][columns_counter] == '1') {
                this->maze->columns_bottom_boder[rows_counter][columns_counter_for_maze] = temp_maze_str[i][columns_counter] - 48;
                columns_counter++;
                columns_counter_for_maze++;
            } else {
                error = 1;
            }
        }
        rows_counter++;
        columns_counter = 0;
        columns_counter_for_maze = 0;
    }
    return error;
}

void s21::Maze::PrintMaze() {
    std::cout << "Hello, you are in s21::Maze::PrintMaze()" << std::endl;
    printf("%d %d\n", this->maze->rows_number, this->maze->columns_number);
    for (int i = 0; i < this->maze->rows_number; ++i) {
        for (int j = 0; j < this->maze->columns_number; ++j) {
            printf("%d ", this->maze->rows_right_boder[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < this->maze->rows_number; ++i) {
        for (int j = 0; j < this->maze->columns_number; ++j) {
            printf("%d ", this->maze->columns_bottom_boder[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < this->maze->rows_number; ++i) {
        for (int j = 0; j < this->maze->columns_number; ++j) {
            printf("%d ", this->maze->groups[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < maze->answer_lenth; ++i) {
        std::cout << " i = " << i << "  path->path[" << i << "][0] = " << maze->answer[i][0] << "   path->path[" << i << "][1] = "  << maze->answer[i][1] << std::endl;
    }
        printf("\n");
}

void s21::Maze::CreateMaze(void) {
    for (int i = 0; i < this->maze->rows_number; ++i) {
        if (i < this->maze->rows_number - 1) CreateRandomRightBorder(i);
        if (i > 0) {
            MoveGroupsDownFromStart(i);
        } else {
            CollectToGroupsInRow(i);
        }
        if ( i < this->maze->rows_number - 1) {
            CreateRandomBottomBorder(i);
            CheckBottomBoder(i);
        }
    }
    MoveGroupsDown(this->maze->rows_number - 2);
    CheckLastRow(this->maze->rows_number - 1);
}

void s21::Maze::MoveGroupsDownFromStart(int row_number) {
    int current_group = 0;
    for (int i = 0; i < this->maze->columns_number; ++i) {
        this->maze->groups[row_number][i] = -1;
    }
    for (int i = 0; i < this->maze->columns_number; ++i) {
        if (this->maze->columns_bottom_boder[row_number - 1][i] == 0) {
            this->maze->groups[row_number][i] = this->maze->groups[row_number - 1][i];
            if (this->maze->groups[row_number][i] > current_group) current_group = this->maze->groups[row_number][i];
        }
    }
    for (int i = 0; i < this->maze->columns_number - 1; ++i) {
        if (this->maze->groups[row_number][i] != - 1 && this->maze->rows_right_boder[row_number][i] == 0 && this->maze->groups[row_number][i + 1] == - 1) {
            this->maze->groups[row_number][i + 1] = this->maze->groups[row_number][i];
        }
    }
    current_group++;
    for (int i = this->maze->columns_number - 1; i > 0; --i) {
        if (this->maze->groups[row_number][i] != - 1 && this->maze->rows_right_boder[row_number][i - 1] == 0) {
            this->maze->groups[row_number][i - 1] = this->maze->groups[row_number][i];
        }
    }
    for (int i = 0; i < this->maze->columns_number; ++i) {
        if (this->maze->groups[row_number][i] == - 1 && this->maze->rows_right_boder[row_number][i] == 0) {
            this->maze->groups[row_number][i] = current_group;
        }
        if (this->maze->groups[row_number][i] == - 1 && this->maze->rows_right_boder[row_number][i] == 0) {
            this->maze->groups[row_number][i] = current_group;
        }
        if (this->maze->groups[row_number][i] == - 1 && this->maze->rows_right_boder[row_number][i] == 1) {
            this->maze->groups[row_number][i] = current_group;
            current_group++;
        }
    }
}

void s21::Maze::CreateRandomRightBorder(int row_number) {
    for (int i = 0; i < this->maze->columns_number - 1; ++i) {
        int random = generator.bounded(0, 1000) / 500;
        this->maze->rows_right_boder[row_number][i] = random;
    }
}

void s21::Maze::CollectToGroupsInRow(int row_number) {
    for (int i = 0; i < this->maze->columns_number - 1; ++i) {
        if (this->maze->rows_right_boder[row_number][i] == 0) {
            this->maze->groups[row_number][i + 1] = this->maze->groups[row_number][i];
        }
    }
}

void s21::Maze::CreateRandomBottomBorder(int row_number) {
    for (int i = 0; i < this->maze->columns_number; ++i) {
        int random = generator.bounded(0, 1000) / 500;
        this->maze->columns_bottom_boder[row_number][i] = random;
    }
}


void  s21::Maze::CheckBottomBoder(int row_number) {
    int current_group = this->maze->groups[row_number][0];
    int pos = 0;
    while (pos < this->maze->columns_number) {
        CheckBottomBoderCurrentGroup(row_number, &current_group, &pos);
    }
}

void s21::Maze::CheckBottomBoderCurrentGroup(int row_number, int *current_group, int *pos) {
    int flag_for_bottom_boder = 0;
    if (this->maze->rows_right_boder[row_number][*pos] == 1) {
        this->maze->columns_bottom_boder[row_number][*pos] = 0;
        *pos = *pos + 1;
    } else {
        while (this->maze->groups[row_number][*pos] == *current_group) {
            if (this->maze->columns_bottom_boder[row_number][*pos] == 0) flag_for_bottom_boder++;
            if (this->maze->columns_bottom_boder[row_number][*pos] == 0 && flag_for_bottom_boder > 1) this->maze->columns_bottom_boder[row_number][*pos] = 1;
            *pos = *pos + 1;
            if (*pos > this->maze->columns_number - 1) break;
        }
        if (flag_for_bottom_boder == 0) {
            this->maze->columns_bottom_boder[row_number][*pos - 1] = 0;
        }
    }
    if (*pos < this->maze->columns_number) {
        *current_group = this->maze->groups[row_number][*pos];
    }
}


void s21::Maze::MoveGroupsDown(int row_number) {
    for (int i = 0; i < this->maze->columns_number; ++i) {
        this->maze->groups[row_number + 1][i] = this->maze->groups[row_number][i];

    }
}

void s21::Maze::CheckLastRow(int row_number) {
    for (int i = 0; i < this->maze->columns_number - 1; ++i) {
        if (this->maze->groups[row_number][i] == this->maze->groups[row_number - 1][i + 1] &&
                this->maze->groups[row_number][i] == this->maze->groups[row_number][i + 1]) {
            int random = generator.bounded(0, 1000) / 500;
            if (random == 1) {
                this->maze->columns_bottom_boder[row_number - 1][i + 1] = 0;
                this->maze->columns_bottom_boder[row_number - 1][i] = 0;
                this->maze->rows_right_boder[row_number][i] = 1;
            } else {
                this->maze->columns_bottom_boder[row_number - 1][i + 1] = 0;
                this->maze->columns_bottom_boder[row_number - 1][i] = 1;
                this->maze->rows_right_boder[row_number][i] = 0;
                this->maze->rows_right_boder[row_number - 1][i] = 0;
            }
        }
    }
}


void s21::Maze::SolveMaze(void) {
    if (CheckForCorrectTask()) {
        Path_t *temp_path = new Path();
        InitPath(temp_path);
        temp_path->path[0][0] = this->maze->start_answer[0];
        temp_path->path[0][1] = this->maze->start_answer[1];
        maze->answer_lenth = this->maze->rows_number * this->maze->columns_number + 1;
        SearchNextCell(temp_path, this->maze->start_answer[0], this->maze->start_answer[1]);
        DeletePath(temp_path);
        delete temp_path;
    }
}


void s21::Maze::SearchNextCell(Path_t *path, int x, int y) {
    if (x == this->maze->end_answer[0] && y == this->maze->end_answer[1] && path->path_lenth < maze->answer_lenth) {
        path->path_lenth = path->path_lenth + 1;
        CopyPathToMaze(path);
    } else {
        SearchUP(path, x, y);
        SearchDown(path, x, y);
        SearchLeft(path, x, y);
        SearchRight(path, x, y);
    }
}

void s21::Maze::SearchUP(Path_t *path, int x, int y) {
    if (y > 0 && this->maze->columns_bottom_boder[y - 1][x] == 0 && !(CheckForVisitedCell(path, x, y - 1))) {
        Path_t *temp_path = new Path(); InitPath(temp_path); CopySearchPath(temp_path, path);
        temp_path->path_lenth = temp_path->path_lenth + 1;
        temp_path->path[temp_path->path_lenth][0] = x;
        temp_path->path[temp_path->path_lenth][1] = y - 1;
        SearchNextCell(temp_path, x, y - 1);
        DeletePath(temp_path);
        delete temp_path;
    } else {
    }
}

void s21::Maze::SearchDown(Path_t *path, int x, int y) {
    if (y < this->maze->rows_number - 1 && this->maze->columns_bottom_boder[y][x] == 0 && !(CheckForVisitedCell(path, x, y + 1))) {
        Path_t *temp_path = new Path(); InitPath(temp_path); CopySearchPath(temp_path, path);
        temp_path->path_lenth = temp_path->path_lenth + 1;
        temp_path->path[temp_path->path_lenth][0] = x;
        temp_path->path[temp_path->path_lenth][1] = y + 1;
        SearchNextCell(temp_path, x, y + 1);
        DeletePath(temp_path);
        delete temp_path;
    } else {
    }
}

void s21::Maze::SearchLeft(Path_t *path, int x, int y) {
    if (x > 0 && this->maze->rows_right_boder[y][x - 1] == 0 && !(CheckForVisitedCell(path,x - 1, y))) {
        Path_t *temp_path = new Path(); InitPath(temp_path); CopySearchPath(temp_path, path);
        temp_path->path_lenth = temp_path->path_lenth + 1;
        temp_path->path[temp_path->path_lenth][0] = x - 1;
        temp_path->path[temp_path->path_lenth][1] = y;
        SearchNextCell(temp_path, x - 1, y);
        DeletePath(temp_path);
        delete temp_path;
    }
}

void s21::Maze::SearchRight(Path_t *path, int x, int y) {
    if (x < this->maze->columns_number - 1 && this->maze->rows_right_boder[y][x] == 0 && !(CheckForVisitedCell(path, x + 1, y))) {
        Path_t *temp_path = new Path(); InitPath(temp_path); CopySearchPath(temp_path, path);
        temp_path->path_lenth = temp_path->path_lenth + 1;
        temp_path->path[temp_path->path_lenth][0] = x + 1;
        temp_path->path[temp_path->path_lenth][1] = y;
        SearchNextCell(temp_path, x + 1, y);
        DeletePath(temp_path);
        delete temp_path;
    }
}

int s21::Maze::CheckForVisitedCell(Path_t *path, int x, int y) {
    int error = 0;
    for (int i = 0; i < path->path_lenth + 1; ++i) {
        if (path->path[i][0] == x && path->path[i][1] == y) {
            error = 1;
            break;
        }
    }
    return error;
}

void s21::Maze::CopySearchPath(Path_t *dist, Path_t *src) {
    for (int i = 0; i < this->maze->rows_number * this->maze->columns_number; ++i) {
        dist->path[i][0] = src->path[i][0];
        dist->path[i][1] = src->path[i][1];
    }
    dist->path_lenth = src->path_lenth;
}

void s21::Maze::CopyPathToMaze(Path_t *path) {
    for (int i = 0; i < this->maze->rows_number * this->maze->columns_number; ++i) {
        this->maze->answer[i][0] = path->path[i][0];
        this->maze->answer[i][1] = path->path[i][1];
    }
    this->maze->answer_lenth = path->path_lenth;
}



void s21::Maze::InitPath(Path_t *path) {
    path->path = new int*[this->maze->rows_number * this->maze->columns_number];
    for (int i = 0; i < this->maze->rows_number * this->maze->columns_number; ++i) {
        path->path[i] = new int[2];
        path->path[i][0] = 0;
        path->path[i][1] = 0;
    }
    path->path_lenth = 0;
}

void s21::Maze::DeletePath(Path_t *path) {
    for (int i = 0; i < this->maze->rows_number * this->maze->columns_number; ++i) {
        delete[] path->path[i];
    }
    delete[] path->path;
}

bool s21::Maze::CheckForCorrectTask(void) {
    bool error =false;
    if (this->maze->start_answer[0] == this->maze->end_answer[0]) error = true;
    if (!error && this->maze->start_answer[1] == this->maze->end_answer[1]) error = true;
    if (!error && this->maze->start_answer[0] < this->maze->columns_number) error = true;
    if (!error && this->maze->end_answer[0] < this->maze->columns_number) error = true;
    if (!error && this->maze->start_answer[1] < this->maze->rows_number) error = true;
    if (!error && this->maze->end_answer[1] < this->maze->rows_number) error = true;
    return error;
}































