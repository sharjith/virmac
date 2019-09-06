#include "RetractPara.h"
#include "ui_RetractPara.h"

RetractPara::RetractPara(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RetractPara)
{
    ui->setupUi(this);
}

RetractPara::~RetractPara()
{
    delete ui;
}

double RetractPara::retraction() const
{
    return ui->doubleSpinBoxEngagement->value();
}

double RetractPara::clearance() const
{
    return ui->doubleSpinBoxClearanceHeight->value();
}

void RetractPara::on_okButton_clicked()
{

}

void RetractPara::on_cancelButton_clicked()
{

}

void RetractPara::on_helpButton_clicked()
{

}
