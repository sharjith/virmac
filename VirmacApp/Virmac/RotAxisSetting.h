#ifndef ROTAXISSETTING_H
#define ROTAXISSETTING_H

#include <QDialog>

namespace Ui {
class RotAxisSetting;
}

class RotAxisSetting : public QDialog
{
    Q_OBJECT

public:
    explicit RotAxisSetting(QWidget *parent = 0);
    ~RotAxisSetting();

    double angleA() const;
    double angleB() const;
    double angleC() const;

    bool isAnglesFromFile() const;

private slots:


    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_helpButton_clicked();

private:
    Ui::RotAxisSetting *ui;
};

#endif // ROTAXISSETTING_H
