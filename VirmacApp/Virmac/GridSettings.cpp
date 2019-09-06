#include "GridSettings.h"
#include "ui_GridSettings.h"

GridSettings::GridSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GridSettings)
{
    ui->setupUi(this);
}

GridSettings::~GridSettings()
{
    delete ui;
}


int GridSettings::gridSize() const
{
    return ui->spinBoxSize->value();
}

int GridSettings::gridStep() const
{
    return ui->spinBoxStep->value();
}

void GridSettings::on_okButton_clicked()
{
    close();
}

void GridSettings::on_cancelButton_clicked()
{
    close();
}

void GridSettings::on_helpButton_clicked()
{

}
