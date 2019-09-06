#include "SimulSettings.h"
#include "ui_SimulSettings.h"

SimulSettings::SimulSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulSettings)
{
    ui->setupUi(this);
}

SimulSettings::~SimulSettings()
{
    delete ui;
}


int SimulSettings::resolution() const
{
    return ui->slider1->value();
}

int SimulSettings::pointsPerFrame() const
{
    return ui->SpinBoxPPF->value();
}

int SimulSettings::rapidRate() const
{
    return ui->SpinBoxRapid->value();
}

bool SimulSettings::isSyntaxEnabled() const
{
    return ui->checkBox1->isChecked();
}

bool SimulSettings::isStopAtIntersection() const
{
    return ui->checkBox2->isChecked();
}


void SimulSettings::on_OKButton_clicked()
{
    close();
}

void SimulSettings::on_CancelButton_clicked()
{
    close();
}


void SimulSettings::on_helpButton_clicked()
{

}
