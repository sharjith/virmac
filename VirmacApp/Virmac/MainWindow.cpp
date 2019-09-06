#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSimulationbar_triggered(bool checked)
{
    checked ? ui->dockSimulationBar->show() : ui->dockSimulationBar->hide();
}

void MainWindow::on_dockSimulationBar_visibilityChanged(bool visible)
{
    ui->actionSimulationbar->setChecked(visible);
}

void MainWindow::on_actionNew_triggered()
{

}
