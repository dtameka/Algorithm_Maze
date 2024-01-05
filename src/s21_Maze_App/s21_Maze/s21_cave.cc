#include "s21_cave.h"

s21::Cave::Cave()
{
    InitCaveScheme();
}

s21::Cave::~Cave()
{
    DeleteCave();
    delete cave;
}

s21::Cave::Cave(const Cave &src) {
    InitCaveScheme();
    CopyCave(src);
}

s21::Cave::Cave(Cave &&src) {
    InitCaveScheme();
    CopyCave(src);
    src.DeleteCave();
}

s21::Cave s21::Cave::operator=(Cave &&src) {
    CopyCave(src);
    src.DeleteCave();
    return *this;
}

s21::Cave &s21::Cave::operator=(const Cave &src) {
    CopyCave(src);
    return *this;
}

void s21::Cave::CopyCave(const Cave &src) {
    InitCave(src.cave->rows_number, src.cave->columns_number);
    for (int i = 0 ; i < src.cave->rows_number; ++i) {
        for (int j = 0; j < src.cave->columns_number; ++j) {
            this->cave->start_state[i][j] = src.cave->start_state[i][j];
            this->cave->current_state[i][j] = src.cave->current_state[i][j];
            this->cave->temp_state[i][j] = src.cave->temp_state[i][j];

        }
    }
    this->cave->current_step = src.cave->current_step;
    this->cave->life_limit = src.cave->life_limit;
    this->cave->death_limit = src.cave->death_limit;
    this->cave->time_step = src.cave->time_step;
}


void s21::Cave::InitCaveScheme()
{
    cave = new Cave_scheme_t;
    cave->rows_number = 0;
    cave->columns_number = 0;
    cave->start_state = nullptr;
    cave->current_state = nullptr;
    cave->temp_state = nullptr;
    cave->current_step = 0;
    cave->life_limit = 0;
    cave->death_limit = 0;
    cave->time_step = 25;
}

void s21::Cave::InitCave(int rows_number, int columns_number)
{
    if (cave == nullptr) {
         cave = new Cave_scheme_t;
    } else {
        DeleteCave();
    }
    if (rows_number <=  0 || columns_number <= 0) {
        cave->rows_number = 0;
        cave->columns_number = 0;
    } else {
        cave->rows_number = rows_number;
        cave->columns_number = columns_number;
        cave->start_state = new int*[rows_number];
        for (int i = 0 ; i < rows_number; ++i) {
            cave->start_state[i] = new int[columns_number];
                for (int j = 0; j < columns_number; ++j) {
                    cave->start_state[i][j] = 0;
                }
        }
        cave->current_state = new int*[rows_number];
        for (int i = 0 ; i < rows_number; ++i) {
            cave->current_state[i] = new int[columns_number];
                for (int j = 0; j < columns_number; ++j) {
                    cave->current_state[i][j] = 0;
                }
        }
        cave->temp_state = new int*[rows_number];
        for (int i = 0 ; i < rows_number; ++i) {
            cave->temp_state[i] = new int[columns_number];
                for (int j = 0; j < columns_number; ++j) {
                    cave->temp_state[i][j] = 0;
                }
        }
        cave->current_step = 0;
        cave->life_limit = 0;
        cave->death_limit = 0;
        cave->time_step = 25;
    }
}

void s21::Cave::DeleteCave()
{
    if (cave->rows_number > 0 && cave->columns_number > 0) {
        for (int i = 0 ; i < cave->rows_number; ++i) {
            delete[] cave->start_state[i];
        }
        for (int i = 0 ; i < cave->rows_number; ++i) {
            delete[] cave->current_state[i];
        }
        for (int i = 0 ; i < cave->rows_number; ++i) {
            delete[] cave->temp_state[i];
        }
        delete[] cave->start_state;
        delete[] cave->current_state;
        delete[] cave->temp_state;
        cave->rows_number = 0;
        cave->columns_number = 0;

        cave->start_state = nullptr;
        cave->current_state = nullptr;
        cave->temp_state = nullptr;
        cave->current_step = 0;
        cave->life_limit = 0;
        cave->death_limit = 0;
        cave->time_step = 25;
    }
}

int s21::Cave::SetRowsNumber(int rows_number)
{
    int error = 0;
    if (rows_number > 0) {
        int temp_columns_number = cave->columns_number;
        DeleteCave();
        InitCave(rows_number, temp_columns_number);
    } else {
        error = 1;
    }
    return error;
}

int s21::Cave::SetColumnsNumber(int columns_number)
{
    int error = 0;
    if (columns_number > 0) {
        int temp_rows_number = cave->rows_number;
        DeleteCave();
        InitCave(temp_rows_number, columns_number);
    } else {
        error = 1;
    }
    return error;
}

int s21::Cave::LoadCave(char *cave_file_path)
{
     FILE *cave_file;
     int error = 0;
     if ((cave_file = fopen(cave_file_path, "r")) == NULL) {
         error = 1;
     } else {
         char **temp_cave_str = nullptr;
          temp_cave_str = new char*[cave_file_str_number];
          for (int i = 0; i < cave_file_str_number; ++i) {
              temp_cave_str[i] = new char[cave_file_str_lenth];
              for (int j = 0; j < cave_file_str_lenth; ++j) {
                  temp_cave_str[i][j] = '\0';
              }
          }
         ReadStrFromFile(cave_file, temp_cave_str);
         error = ReadCaveFromStr(temp_cave_str);
         fclose(cave_file);
         for (int i = 0; i < cave_file_str_number; ++i) delete[] temp_cave_str[i];
         delete[] temp_cave_str;
     }
     if (!error) CopyStartStateToCurrentState();
     return error;
}

void s21::Cave::CopyStartStateToCurrentState(void) {
    for (int i = 0; i < this->cave->rows_number; ++i) {
        for (int j = 0; j < this->cave->columns_number; ++j) {
           this->cave->current_state[i][j] = this->cave->start_state[i][j];
        }
    }
}

int s21::Cave::SaveCave(char *cave_file_path)
{
    FILE *cave_file;
    int error = 0;
    if ((cave_file = fopen(cave_file_path, "w")) == NULL) {
        error = 1;
    } else {
        fprintf(cave_file, "%d %d\n", this->cave->rows_number, this->cave->columns_number);
        for (int i = 0; i < this->cave->rows_number; ++i) {
            for (int j = 0; j < this->cave->columns_number; ++j) {
               fprintf(cave_file, "%d ", this->cave->start_state[i][j]);
            }
            fprintf(cave_file, "\n");
        }
        fprintf(cave_file, "\n");
        fclose(cave_file);
    }
    return error;
}

void s21::Cave::ReadStrFromFile(FILE *cave_file, char **temp_cave_str)
{
        char letter;
        int counter = 0, str_counter = 0, temp_str_counter = 0;
        while (!feof(cave_file)) {
          letter = fgetc(cave_file);
          if (letter == 10 || letter == EOF) {
            if (letter == EOF) {
              temp_cave_str[str_counter][counter] = '\0';
              break;
            } else {
              temp_cave_str[str_counter][counter] = '\0';
              printf("\n");
            }
            counter = 0;
            str_counter++;
          } else {
            temp_cave_str[str_counter][counter] = letter;
            counter++;
          }
        }
}

int s21::Cave::ReadCaveFromStr(char **temp_cave_str)
{
       int error = 0;
       int rows_number = 0;
       int columns_number = 0;
       sscanf((const char *) temp_cave_str[0], "%d%d", &rows_number, &columns_number);
       if (rows_number > 0 && columns_number > 0) {
           this->InitCave(rows_number, columns_number);
           error = ReadCaveStartStateFromStr(temp_cave_str);
       } else {
           error = 1;
       }
       return error;
}

int s21::Cave::ReadCaveStartStateFromStr(char **temp_cave_str)
{
    int error = 0;
    int rows_number = 0;
    int columns_number = 0;
    int rows_counter = 0;
    int columns_counter = 0;
    int columns_counter_for_cave = 0;
    sscanf((const char *) temp_cave_str[0], "%d%d", &rows_number, &columns_number);
    for (int i = 1; i < rows_number + 1; ++i) {
        while (temp_cave_str[i][columns_counter] != '\0') {
            if (temp_cave_str[i][columns_counter] == ' ') {
                columns_counter++;
                continue;
            } else if (temp_cave_str[i][columns_counter] == '0' || temp_cave_str[i][columns_counter] == '1') {
                this->cave->start_state[rows_counter][columns_counter_for_cave] = temp_cave_str[i][columns_counter] - 48;
                columns_counter++;
                columns_counter_for_cave++;
            } else {
                error = 1;
                break;
            }
        }
        rows_counter++;
        columns_counter = 0;
        columns_counter_for_cave = 0;
    }
    return error;
}

void s21::Cave::CreateCave()
{
    for (int i = 0; i < this->cave->rows_number; ++i) {
        for (int j = 0; j < this->cave->columns_number; ++j) {
            int random = generator.bounded(0, 1000) / 500;
            this->cave->start_state[i][j] = random;
            this->cave->current_state[i][j] = random;
        }
    }
}

void s21::Cave::CreateNextStepCave()
{
    for (int i = 0; i < this->cave->rows_number; ++i) {
        for (int j = 0; j < this->cave->columns_number; ++j) {
            if (this->cave->current_state[i][j] == 1) {
                this->cave->temp_state[i][j] = CheckForDeath(i, j);
            } else {
                this->cave->temp_state[i][j] = CheckForLife(i, j);
            }
        }
    }
    for (int i = 0; i < this->cave->rows_number; ++i) {
        for (int j = 0; j < this->cave->columns_number; ++j) {
            this->cave->current_state[i][j] = this->cave->temp_state[i][j];
        }
    }
    this->cave->current_step = this->cave->current_step + 1;
}

int s21::Cave::CheckForLife(int row_number, int column_number) {
    int answer = 0;
    int life_factor = 0;
    for (int i = row_number - 1; i < row_number + 2; ++i) {
        for (int j = column_number - 1; j < column_number + 2; ++j) {
            if ( i < 0 || i == this->cave->rows_number || j < 0 || j == this->cave->columns_number) {
                life_factor++;
            } else {
                if (this->cave->current_state[i][j] == 1) life_factor++;
            }
        }
    }
    if (life_factor > this->cave->life_limit) answer = 1;
    return answer;
}

int s21::Cave::CheckForDeath(int row_number, int column_number) {
    int answer = 1;
    int death_factor = 0;
    for (int i = row_number - 1; i < row_number + 2; ++i) {
        for (int j = column_number - 1; j < column_number + 2; ++j) {
            if ( i < 0 || i == this->cave->rows_number || j < 0 || j == this->cave->columns_number) {
            } else {
                if (this->cave->current_state[i][j] == 0) death_factor++;
            }
        }
    }
    if (death_factor > this->cave->death_limit) answer = 0;
    return answer;
}


void s21::Cave::PrintCave()
{
    std::cout << "Hello, you are in s21::Cave::PrintCave()" << std::endl;
    printf("%d %d\n", this->cave->rows_number, this->cave->columns_number);
    for (int i = 0; i < this->cave->rows_number; ++i) {
        for (int j = 0; j < this->cave->columns_number; ++j) {
            printf("%d ", this->cave->start_state[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < this->cave->rows_number; ++i) {
        for (int j = 0; j < this->cave->columns_number; ++j) {
            printf("%d ", this->cave->current_state[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("this->cave->current_step = %d  ", this->cave->current_step);
    printf("this->cave->time_step = %d  ", this->cave->time_step);
    printf("this->cave->life_limit = %d  ", this->cave->life_limit);
    printf("this->cave->death_limit = %d  ", this->cave->death_limit);
    printf("\n");
}

