#include "ToolDefinition.h"
#include "ui_ToolDefinition.h"

ToolDefinition::ToolDefinition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolDefinition)
{
    ui->setupUi(this);
}

ToolDefinition::~ToolDefinition()
{
    delete ui;
}

void ToolDefinition::setToolNumber(const int &val)
{
    ui->toolNumber->setValue(val);
}

void ToolDefinition::setBodyDia(const double &val)
{
    ui->bodyDia->setValue(val);
}

void ToolDefinition::setBallRad(const double &val)
{
    ui->ballRad->setValue(val);
}

void ToolDefinition::setBodyLength(const double &val)
{
    ui->bodyLen->setValue(val);
}

void ToolDefinition::setHolderDia(const double &val)
{
    ui->holderDia->setValue(val);
}

void ToolDefinition::setHolderLen(const double &val)
{
    ui->holderLen->setValue(val);
}

void ToolDefinition::setShankDia(const double &val)
{
    ui->shankDia->setValue(val);
}

void ToolDefinition::setShankLength(const double &val)
{
    ui->shankLen->setValue(val);
}

void ToolDefinition::setTaperDiaA(const double &val)
{
    ui->taperDiaA->setValue(val);
}

void ToolDefinition::setTaperDiaB(const double &val)
{
    ui->taperDiaB->setValue(val);
}

void ToolDefinition::setTaperLength(const double &val)
{
    ui->taperLen->setValue(val);
}



int ToolDefinition::getToolPage() const
{
    return ui->tabWidget2->currentIndex();
}

int ToolDefinition::getToolNumber() const
{
    return ui->toolNumber->value();
}

double ToolDefinition::getBodyDia() const
{
    return ui->bodyDia->value();
}

double ToolDefinition::getBallRad() const
{
    return ui->ballRad->value();
}

double ToolDefinition::getBodyLength() const
{
    return ui->bodyLen->value();
}

double ToolDefinition::getHolderDia() const
{
    return ui->holderDia->value();
}

double ToolDefinition::getHolderLen() const
{
    return ui->holderLen->value();
}

double ToolDefinition::getShankDia() const
{
    return ui->shankDia->value();
}

double ToolDefinition::getShankLength() const
{
    return ui->shankLen->value();
}

double ToolDefinition::getTaperDiaA() const
{
    return ui->taperDiaA->value();
}

double ToolDefinition::getTaperDiaB() const
{
    return ui->taperDiaB->value();
}

double ToolDefinition::getTaperLength() const
{
    return ui->taperLen->value();
}


void ToolDefinition::on_okButton_clicked()
{
    QDialog::accept();
}

void ToolDefinition::on_cancelButton_clicked()
{
    QDialog::reject();
}

void ToolDefinition::on_helpButton_clicked()
{

}
