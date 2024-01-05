#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include "s21_maze.h"
#include "s21_cave.h"
#include "mazeview.h"
#include "caveview.h"
#include "cavewindow.h"

class Controller: public QObject
{
    Q_OBJECT
public:
    Controller();
    ~Controller();
    void ConnectMazeViewToController(MazeView *maze_view);


public slots:
  void GetFileNameAndPath(char *, char *);
  void GetSaveFileNameAndPath(char *, char *);
  void GetNumberOfRowsForCreatingMaze(int);
  void GetNumberOfColumnsForCreatingMaze(int);
  void GetStartRowNumber(int);
  void GetStartColumnNumber(int);
  void GetEndRowNumber(int);
  void GetEndColumnNumber(int);
  void GetCreateMazeSignal(void);
  void GetSolveMazeSignal(void);
  void GetCreateCaveWindowSignal(void);

  void GetCaveFileName(char *, char *);
  void GetCaveSaveFileName(char *, char *);
  void GetCaveNumberOfRowsForCreating(int);
  void GetCaveNumberOfColumnsForCreating(int);
  void GetCaveCreateSignal(void);
  void GetCaveNextStepSignal(void);
  void GetCaveAutoFormationStartSignal(void);
  void GetCaveAutoFormationStopSignal(void);
  void GetCaveTimeStep(int);
  void GetCaveLifeLimit(int);
  void GetCaveDeathLimit(int);

signals:
  void SendMazeForDrawing(s21::Maze *maze);
  void SendCaveForDrawing(s21::Cave *cave);
  void SendCaveViewPointerToCaveWindow(CaveView *cave_view);
  void SendCaveCurrentStepNumber(int);

private:
  s21::Maze *my_maze_;
  s21::Cave *my_cave_;
  MazeView *my_maze_view_;
  CaveView *my_cave_view_;
  CaveWindow *my_cave_window_;
  QTimer *timer_;
};

#endif // CONTROLLER_H
