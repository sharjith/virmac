#include "Transformations.h"
#include "ui_Transformations.h"

Transformations::Transformations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transformations)
{
    ui->setupUi(this);
}

Transformations::~Transformations()
{
    delete ui;
}

double Transformations::CX() const
{
    return ui->doubleSpinBoxCX->value();
}

double Transformations::CY() const
{
    return ui->doubleSpinBoxCY->value();
}

double Transformations::CZ() const
{
    return ui->doubleSpinBoxCZ->value();
}

double Transformations::DX() const
{
    return ui->doubleSpinBoxDX->value();
}

double Transformations::DY() const
{
    return ui->doubleSpinBoxDY->value();
}

double Transformations::DZ() const
{
    return ui->doubleSpinBoxDZ->value();
}

double Transformations::RX() const
{
    return ui->doubleSpinBoxRX->value();
}

double Transformations::RY() const
{
    return ui->doubleSpinBoxRY->value();
}

double Transformations::RZ() const
{
    return ui->doubleSpinBoxRZ->value();
}

double Transformations::XP() const
{
    return ui->doubleSpinBoxXP->value();
}

double Transformations::YP() const
{
    return ui->doubleSpinBoxYP->value();
}

double Transformations::ZP() const
{
    return ui->doubleSpinBoxZP->value();
}



void Transformations::on_okButton_clicked()
{
    close();
}

void Transformations::on_cancelButton_clicked()
{
    close();
}

void Transformations::on_helpButton_clicked()
{

}
