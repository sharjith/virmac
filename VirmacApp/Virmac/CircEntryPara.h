#ifndef CIRCENTRYPARA_H
#define CIRCENTRYPARA_H

#include <QDialog>

namespace Ui {
class CircEntryPara;
}

class CircEntryPara : public QDialog
{
    Q_OBJECT

public:
    explicit CircEntryPara(QWidget *parent = 0);
    ~CircEntryPara();

    double arcRadius() const;
    bool isUpMilling() const;

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_helpButton_clicked();

private:
    Ui::CircEntryPara *ui;
};

#endif // CIRCENTRYPARA_H
