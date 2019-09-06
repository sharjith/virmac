#ifndef RETRACTPARA_H
#define RETRACTPARA_H

#include <QDialog>

namespace Ui {
class RetractPara;
}

class RetractPara : public QDialog
{
    Q_OBJECT

public:
    explicit RetractPara(QWidget *parent = 0);
    ~RetractPara();

    double retraction() const;
    double clearance() const;

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_helpButton_clicked();

private:
    Ui::RetractPara *ui;
};

#endif // RETRACTPARA_H
