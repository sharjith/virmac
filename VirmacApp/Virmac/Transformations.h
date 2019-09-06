#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <QDialog>

namespace Ui {
class Transformations;
}

class Transformations : public QDialog
{
    Q_OBJECT

public:
    explicit Transformations(QWidget *parent = 0);
    ~Transformations();

    double CX() const;
    double CY() const;
    double CZ() const;

    double DX() const;
    double DY() const;
    double DZ() const;

    double RX() const;
    double RY() const;
    double RZ() const;

    double XP() const;
    double YP() const;
    double ZP() const;

private slots:


    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_helpButton_clicked();

private:
    Ui::Transformations *ui;
};

#endif // TRANSFORMATIONS_H
