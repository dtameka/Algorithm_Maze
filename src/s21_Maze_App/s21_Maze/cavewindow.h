#ifndef CAVEWINDOW_H
#define CAVEWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "caveview.h"

namespace Ui {
class CaveWindow;
}

class CaveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CaveWindow(QWidget *parent = nullptr);
    ~CaveWindow();

public slots:
    void ConnectCaveViewToCaveWindow(CaveView *src);
    void GetCaveCurrentStepNumber(int);


private slots:
    void on_actionLoad_Cave_triggered();

    void on_actionSave_Cave_triggered();

    void on_PBCreate_clicked();

    void on_PBNexStep_clicked();

    void on_PBAutoCaveFormationStart_clicked();

    void on_PBAutoCaveFormationStop_clicked();

private:
    void LoadFileName(void);
    void SaveFileName(void);
    void Draw(void);
    Ui::CaveWindow *ui_;
    CaveView *my_cave_view_;

signals:
      void SendCaveFileName(char *, char *);
      void SendCaveSaveFileName(char *, char *);
      void SendCaveNumberOfRowsForCreating(int);
      void SendCaveNumberOfColumnsForCreating(int);
      void SendCaveCreateSignal(void);
      void SendCaveNextStepSignal(void);
      void SendCaveAutoFormationStartSignal(void);
      void SendCaveAutoFormationStopSignal(void);
      void SendCaveTimeStep(int);
      void SendCaveLifeLimit(int);
      void SendCaveDeathLimit(int);

};

#endif // CAVEWINDOW_H
