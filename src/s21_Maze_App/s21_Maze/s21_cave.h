#ifndef CAVE_H
#define CAVE_H
#include <iostream>
#include <QObject>
#include <QRandomGenerator>
#include <stdio.h>
#include <string.h>

static const int cave_file_str_number = 150;
static const int cave_file_str_lenth = 100;

namespace s21 {

typedef struct Cave_scheme {
    int rows_number;
    int columns_number;
    int **start_state;
    int **current_state;
    int **temp_state;
    int current_step;
    int life_limit;
    int death_limit;
    int time_step;
} Cave_scheme_t;

class Cave
{
public:
    Cave();
    ~Cave();
    Cave(const Cave &src);
    Cave(Cave &&src);
    Cave operator=(Cave &&src);
    Cave &operator=(const Cave &src);
    void InitCaveScheme();
    void InitCave(int rows_number, int columns_number);
    void DeleteCave();
    int SetRowsNumber(int rows_number);
    int SetColumnsNumber(int columns_number);

    int LoadCave(char *cave_file_path);
    int SaveCave(char *cave_file_path);
//    void InitTempStr(char **cave_temp_str);

    void CreateCave(void);
    void CreateNextStepCave(void);
    void PrintCave();
    Cave_scheme_t *cave;
private:
    void CopyCave(const Cave &src);
    QRandomGenerator generator;
    int CheckForLife(int, int);
    int CheckForDeath(int, int);
    void ReadStrFromFile(FILE *cave_file, char **temp_cave_str);
    int ReadCaveFromStr(char **temp_cave_str);
    int ReadCaveStartStateFromStr(char **temp_cave_str);
    void CopyStartStateToCurrentState(void);
};


}  // namespace s21

#endif // CAVE_H
