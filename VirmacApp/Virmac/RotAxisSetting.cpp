#include "RotAxisSetting.h"
#include "ui_RotAxisSetting.h"

RotAxisSetting::RotAxisSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RotAxisSetting)
{
    ui->setupUi(this);
}

RotAxisSetting::~RotAxisSetting()
{
    delete ui;
}

double RotAxisSetting::angleA() const
{
    return ui->lineEditA->text().toDouble();
}

double RotAxisSetting::angleB() const
{
    return ui->lineEditB->text().toDouble();
}

double RotAxisSetting::angleC() const
{
    return ui->lineEditC->text().toDouble();
}

bool RotAxisSetting::isAnglesFromFile() const
{
    return ui->radioButton2->isChecked();
}


void RotAxisSetting::on_okButton_clicked()
{
    close();

}

void RotAxisSetting::on_cancelButton_clicked()
{
    close();
}

void RotAxisSetting::on_helpButton_clicked()
{

}
