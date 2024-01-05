#include "s21_controller.h"

Controller::Controller()
{
    my_maze_ = new s21::Maze();
    my_maze_->InitMaze(5, 5);
    my_cave_ = new s21::Cave();
    my_cave_->InitCave(5, 5);
    my_cave_view_ = new CaveView();
    my_cave_window_ = new CaveWindow();
    connect(this, &Controller::SendCaveForDrawing, my_cave_view_, &CaveView::DrawCave);
    connect(this, &Controller::SendCaveViewPointerToCaveWindow, my_cave_window_, &CaveWindow::ConnectCaveViewToCaveWindow);
    connect(my_cave_window_, &CaveWindow::SendCaveFileName, this, &Controller::GetCaveFileName);
    connect(my_cave_window_, &CaveWindow::SendCaveSaveFileName, this, &Controller::GetCaveSaveFileName);
    connect(my_cave_window_, &CaveWindow::SendCaveNumberOfRowsForCreating, this, &Controller::GetCaveNumberOfRowsForCreating);
    connect(my_cave_window_, &CaveWindow::SendCaveNumberOfColumnsForCreating, this, &Controller::GetCaveNumberOfColumnsForCreating);
    connect(my_cave_window_, &CaveWindow::SendCaveCreateSignal, this, &Controller::GetCaveCreateSignal);
    connect(my_cave_window_, &CaveWindow::SendCaveNextStepSignal, this, &Controller::GetCaveNextStepSignal);
    connect(my_cave_window_, &CaveWindow::SendCaveAutoFormationStartSignal, this, &Controller::GetCaveAutoFormationStartSignal);
    connect(my_cave_window_, &CaveWindow::SendCaveAutoFormationStopSignal, this, &Controller::GetCaveAutoFormationStopSignal);
    connect(my_cave_window_, &CaveWindow::SendCaveTimeStep, this, &Controller::GetCaveTimeStep);
    connect(my_cave_window_, &CaveWindow::SendCaveLifeLimit, this, &Controller::GetCaveLifeLimit);
    connect(my_cave_window_, &CaveWindow::SendCaveDeathLimit, this, &Controller::GetCaveDeathLimit);
    connect (this, &Controller::SendCaveCurrentStepNumber, my_cave_window_, &CaveWindow::GetCaveCurrentStepNumber);
    emit SendCaveViewPointerToCaveWindow(my_cave_view_);
    timer_ = new QTimer(this);
}

Controller::~Controller() {
  my_maze_->DeleteMaze();
}

void Controller::GetFileNameAndPath(char *path, char * name) {
    my_maze_->LoadMaze(path);
    emit SendMazeForDrawing(my_maze_);
}

void Controller::GetSaveFileNameAndPath(char *path, char * name) {
    my_maze_->SaveMaze(path);
}

void Controller::ConnectMazeViewToController(MazeView *maze_view) {
    my_maze_view_ = maze_view;
}

void Controller::GetNumberOfRowsForCreatingMaze(int rows_number) {
    my_maze_->SetRowsNumber(rows_number);
}

void Controller::GetNumberOfColumnsForCreatingMaze(int columns_number) {
    my_maze_->SetColumnsNumber(columns_number);
}

void Controller::GetStartRowNumber(int start_row_number) {
    my_maze_->maze->start_answer[1] = start_row_number - 1;
}

void Controller::GetStartColumnNumber(int start_columns_number) {
    my_maze_->maze->start_answer[0] = start_columns_number - 1;
}

void Controller::GetEndRowNumber(int end_row_number) {
    my_maze_->maze->end_answer[1] = end_row_number - 1;
}

void Controller::GetEndColumnNumber(int end_column_number) {
     my_maze_->maze->end_answer[0] = end_column_number - 1;
}

void Controller::GetCreateMazeSignal(void) {
    my_maze_->CreateMaze();
    emit SendMazeForDrawing(my_maze_);
}

void Controller::GetSolveMazeSignal(void) {
    my_maze_->SolveMaze();
    emit SendMazeForDrawing(my_maze_);
}

void Controller::GetCreateCaveWindowSignal()
{
    my_cave_window_->show();
    emit SendCaveForDrawing(my_cave_);
}

void Controller::GetCaveFileName(char * path, char *name)
{
    my_cave_->LoadCave(path);
    emit SendCaveForDrawing(my_cave_);
}

void Controller::GetCaveSaveFileName(char *path, char *name)
{
    my_cave_->SaveCave(path);
}

void Controller::GetCaveNumberOfRowsForCreating(int rows_number)
{
        my_cave_->SetRowsNumber(rows_number);
}

void Controller::GetCaveNumberOfColumnsForCreating(int columns_number)
{
        my_cave_->SetColumnsNumber(columns_number);
}

void Controller::GetCaveCreateSignal()
{
    my_cave_->CreateCave();
    emit SendCaveCurrentStepNumber(my_cave_->cave->current_step);
    emit SendCaveForDrawing(my_cave_);
}

void Controller::GetCaveNextStepSignal()
{
    my_cave_->CreateNextStepCave();
    emit SendCaveCurrentStepNumber(my_cave_->cave->current_step);
    emit SendCaveForDrawing(my_cave_);
}

void Controller::GetCaveAutoFormationStartSignal()
{
    timer_->setInterval(this->my_cave_->cave->time_step);
    connect(timer_, &QTimer::timeout, this, &Controller::GetCaveNextStepSignal);
    timer_->start(this->my_cave_->cave->time_step);
}

void Controller::GetCaveAutoFormationStopSignal()
{
    disconnect(timer_, &QTimer::timeout, this, &Controller::GetCaveNextStepSignal);
}

void Controller::GetCaveTimeStep(int time_step)
{
    my_cave_->cave->time_step = time_step;
}

void Controller::GetCaveLifeLimit(int life_limit)
{
    my_cave_->cave->life_limit = life_limit;
}

void Controller::GetCaveDeathLimit(int death_limit)
{
    my_cave_->cave->death_limit = death_limit;
}








