#include "cavewindow.h"
#include "ui_cavewindow.h"

CaveWindow::CaveWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::CaveWindow)
{
    ui_->setupUi(this);

}

CaveWindow::~CaveWindow()
{
    delete ui_;
}

void CaveWindow::ConnectCaveViewToCaveWindow(CaveView *src)
{
    my_cave_view_ = src;
    ui_->GLCave->addWidget(my_cave_view_);
}

void CaveWindow::on_actionLoad_Cave_triggered()
{
    LoadFileName();
}

void CaveWindow::on_actionSave_Cave_triggered()
{
    SaveFileName();
}

void CaveWindow::LoadFileName(void) {
    QString str = QFileDialog::getOpenFileName(
        this, tr("Choose cve file"), QDir::currentPath(),
        tr("CVE Image (*.cve);; All Files (*.*)"));
    QFileInfo fileinfo(str);
    QString str_1 = fileinfo.fileName();
    QString str_2 = fileinfo.filePath();
    if (str_2 != "") {
        ui_->LCaveName->setText(str_1);
        ui_->LFilePath->setText(str_2);
        Draw();
    }
}

void CaveWindow::SaveFileName(void) {
    QString str = QFileDialog::getSaveFileName(this, tr("Enter .cve file name"), QDir::currentPath(),tr("CVE Image (*.cve);; All Files (*.*)"));
    QFileInfo fileinfo(str);
    QString str_1 = fileinfo.fileName();
    QString str_2 = fileinfo.filePath();
    if (str_2 != "") {
        char path[255] = "", name[50];
        ui_->LCaveName->setText(str_1);
        ui_->LFilePath->setText(str_2);
        QByteArray temp_path = ui_->LFilePath->text().toLocal8Bit();
        strcpy(path, temp_path.data());
        QByteArray temp_name = ui_->LCaveName->text().toLocal8Bit();
        strcpy(name, temp_name.data());
        emit SendCaveSaveFileName(path, name);
    }
}

void CaveWindow::Draw(void) {
    char path[255] = "", name[50];
    if (ui_->LFilePath->text() != "home_directory" || ui_->LFilePath->text() != "") {
      QByteArray temp_path = ui_->LFilePath->text().toLocal8Bit();
      strcpy(path, temp_path.data());
      QByteArray temp_name = ui_->LCaveName->text().toLocal8Bit();
      strcpy(name, temp_name.data());
      emit SendCaveFileName(path, name);
    }
}

void CaveWindow::on_PBCreate_clicked()
{
    emit SendCaveNumberOfRowsForCreating(ui_->SBRowsNumber->value());
    emit SendCaveNumberOfColumnsForCreating(ui_->SBColumnsNumber->value());
    emit SendCaveCreateSignal();
}

void CaveWindow::on_PBNexStep_clicked()
{
    emit SendCaveTimeStep(ui_->SBTimeStep->value());
    emit SendCaveLifeLimit(ui_->SBLifeLimit->value());
    emit SendCaveDeathLimit(ui_->SBDeathLimit->value());
    emit SendCaveNextStepSignal();
}

void CaveWindow::on_PBAutoCaveFormationStart_clicked()
{
    emit SendCaveTimeStep(ui_->SBTimeStep->value());
    emit SendCaveLifeLimit(ui_->SBLifeLimit->value());
    emit SendCaveDeathLimit(ui_->SBDeathLimit->value());
    emit SendCaveAutoFormationStartSignal();
}

void CaveWindow::on_PBAutoCaveFormationStop_clicked()
{
    emit SendCaveAutoFormationStopSignal();
}

void CaveWindow::GetCaveCurrentStepNumber(int temp_number)
{
    QString temp_current_step = QString::number(temp_number, 'f', 0);
    ui_->LCurrentStepNumber->setText(temp_current_step);
}

