#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    my_maze_view_ = new MazeView();
    ui_->GLMaze->addWidget(my_maze_view_);
    my_controller_ = new Controller();
    connect(this, &MainWindow::SendFileName, my_controller_, &Controller::GetFileNameAndPath);
    connect(this, &MainWindow::SendSaveFileName, my_controller_, &Controller::GetSaveFileNameAndPath);
    connect(my_controller_, &Controller::SendMazeForDrawing, my_maze_view_, &MazeView::DrawMaze);
    connect(this, &MainWindow::SendNumberOfRowsForCreatingMaze, my_controller_, &Controller::GetNumberOfRowsForCreatingMaze);
    connect(this, &MainWindow::SendNumberOfColumnsForCreatingMaze, my_controller_, &Controller::GetNumberOfColumnsForCreatingMaze);
    connect(this, &MainWindow::SendStartRowNumber, my_controller_, &Controller::GetStartRowNumber);
    connect(this, &MainWindow::SendStartColumnNumber, my_controller_, &Controller::GetStartColumnNumber);
    connect(this, &MainWindow::SendEndRowNumber, my_controller_, &Controller::GetEndRowNumber);
    connect(this, &MainWindow::SendEndColumnNumber, my_controller_, &Controller::GetEndColumnNumber);
    connect(this, &MainWindow::SendCreateMazeSignal, my_controller_, &Controller::GetCreateMazeSignal);
    connect(this, &MainWindow::SendSolveMazeSignal, my_controller_, &Controller::GetSolveMazeSignal);
    connect(this, &MainWindow::SendCreateCaveSignal, my_controller_, &Controller::GetCreateCaveWindowSignal);
    my_controller_->ConnectMazeViewToController(my_maze_view_);
    ui_->SBRowsNumber->setValue(10); ui_->SBRowsNumber->repaint();
    ui_->SBColumnsNumber->setValue(10);ui_->SBColumnsNumber->repaint();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::on_actionLoad_triggered()
{
    LoadFileName();
}

void MainWindow::on_actionSave_triggered()
{
    SaveFileName();
}

void MainWindow::LoadFileName(void) {
    QString str = QFileDialog::getOpenFileName(
        this, tr("Choose mze file"), QDir::currentPath(),
        tr("MZE Image (*.mze);; All Files (*.*)"));
    QFileInfo fileinfo(str);
    QString str_1 = fileinfo.fileName();
    QString str_2 = fileinfo.filePath();
    if (str_2 != "") {
        ui_->LMazeName->setText(str_1);
        ui_->LFilePath->setText(str_2);
        Draw();
    }
}

void MainWindow::SaveFileName(void) {
    QString str = QFileDialog::getSaveFileName(this, tr("Enter .mze file name"), QDir::currentPath(),tr("MZE Image (*.mze);; All Files (*.*)"));
    QFileInfo fileinfo(str);
    QString str_1 = fileinfo.fileName();
    QString str_2 = fileinfo.filePath();
    if (str_2 != "") {
        char path[255] = "", name[50];
        ui_->LMazeName->setText(str_1);
        ui_->LFilePath->setText(str_2);
        QByteArray temp_path = ui_->LFilePath->text().toLocal8Bit();
        strcpy(path, temp_path.data());
        QByteArray temp_name = ui_->LMazeName->text().toLocal8Bit();
        strcpy(name, temp_name.data());
        emit SendSaveFileName(path, name);
    }
}

void MainWindow::Draw(void) {
    char path[255] = "", name[50];
    if (ui_->LFilePath->text() != "home_directory" || ui_->LFilePath->text() != "") {
      QByteArray temp_path = ui_->LFilePath->text().toLocal8Bit();
      strcpy(path, temp_path.data());
      QByteArray temp_name = ui_->LMazeName->text().toLocal8Bit();
      strcpy(name, temp_name.data());
      emit SendFileName(path, name);
    }
}


void MainWindow::on_PBCreate_clicked()
{
    emit SendNumberOfRowsForCreatingMaze(ui_->SBRowsNumber->value());
    emit SendNumberOfColumnsForCreatingMaze(ui_->SBColumnsNumber->value());
    emit SendCreateMazeSignal();
}



void MainWindow::on_PBSolve_clicked()
{
    emit SendStartRowNumber(ui_->SBStartRow->value());
    emit SendStartColumnNumber(ui_->SBStartColumn->value());
    emit SendEndRowNumber(ui_->SBEndRow->value());
    emit SendEndColumnNumber(ui_->SBEndColumn->value());
    emit SendSolveMazeSignal();
}



void MainWindow::on_PBCreateCave_clicked()
{
    emit SendCreateCaveSignal();
}
