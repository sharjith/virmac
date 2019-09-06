#ifndef SIMULSETTINGS_H
#define SIMULSETTINGS_H

#include <QDialog>

namespace Ui {
class SimulSettings;
}

class SimulSettings : public QDialog
{
    Q_OBJECT

public:
    explicit SimulSettings(QWidget *parent = 0);
    ~SimulSettings();

    int resolution() const;
    int pointsPerFrame() const;
    int rapidRate() const;

    bool isSyntaxEnabled() const;
    bool isStopAtIntersection() const;

private slots:
    void on_OKButton_clicked();

    void on_CancelButton_clicked();

    void on_helpButton_clicked();

private:
    Ui::SimulSettings *ui;
};

#endif // SIMULSETTINGS_H
