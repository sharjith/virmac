#include "SimulReport.h"
#include "ui_SimulReport.h"

SimulReport::SimulReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulReport)
{
    ui->setupUi(this);
}

SimulReport::~SimulReport()
{
    delete ui;
}

void SimulReport::setFileName(const QString& fName)
{
    ui->textLabelFileName->setText(fName);
}

void SimulReport::setToolDia(const QString& tDia)
{
    ui->textLabelToolDia->setText(tDia);
}

void SimulReport::setPathLength(const QString& pLength)
{
    ui->textLabelPathLen->setText(pLength);
}

void SimulReport::setCuttingTime(const QString& cutTime)
{
    ui->textLabelCuttingTime->setText(cutTime);
}

void SimulReport::setRapidRate(const QString& rapidRate)
{
    ui->textLabelRapid->setText(rapidRate);
}
