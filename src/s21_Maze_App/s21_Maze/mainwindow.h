#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "mazeview.h"
#include "caveview.h"
#include "s21_controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:


private slots:
    void on_actionLoad_triggered();

    void on_PBCreate_clicked();

    void on_PBSolve_clicked();

    void on_actionSave_triggered();

    void on_PBCreateCave_clicked();

private:
    void LoadFileName(void);
    void SaveFileName(void);
    void Draw(void);
    Ui::MainWindow *ui_;
    MazeView  *my_maze_view_;
    Controller *my_controller_;

signals:
      void SendFileName(char *, char *);
      void SendSaveFileName(char *, char *);
      void SendNumberOfRowsForCreatingMaze(int);
      void SendNumberOfColumnsForCreatingMaze(int);
      void SendStartRowNumber(int);
      void SendStartColumnNumber(int);
      void SendEndRowNumber(int);
      void SendEndColumnNumber(int);
      void SendCreateMazeSignal(void);
      void SendSolveMazeSignal(void);
      void SendCreateCaveSignal(void);
};

#endif // MAINWINDOW_H
