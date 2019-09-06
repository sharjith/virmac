#include "CircEntryPara.h"
#include "ui_CircEntryPara.h"

CircEntryPara::CircEntryPara(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CircEntryPara)
{
    ui->setupUi(this);
}

CircEntryPara::~CircEntryPara()
{
    delete ui;
}

double CircEntryPara::arcRadius() const
{
    return ui->doubleSpinBoxArcRadius->value();
}

bool CircEntryPara::isUpMilling() const
{
    return ui->radioButtonUpMill->isChecked();
}

void CircEntryPara::on_okButton_clicked()
{

}

void CircEntryPara::on_cancelButton_clicked()
{

}

void CircEntryPara::on_helpButton_clicked()
{

}
