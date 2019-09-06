#ifndef SIMULREPORT_H
#define SIMULREPORT_H

#include <QDialog>

namespace Ui {
class SimulReport;
}

class SimulReport : public QDialog
{
    Q_OBJECT

public:
    explicit SimulReport(QWidget *parent = 0);
    ~SimulReport();

    void setFileName(const QString& fName);
    void setToolDia(const QString& tDia);
    void setPathLength(const QString& pLength);
    void setCuttingTime(const QString& cutTime);
    void setRapidRate(const QString& rapidRate);

private:
    Ui::SimulReport *ui;
};

#endif // SIMULREPORT_H
