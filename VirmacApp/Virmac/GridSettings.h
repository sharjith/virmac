#ifndef GRIDSETTINGS_H
#define GRIDSETTINGS_H

#include <QDialog>

namespace Ui {
class GridSettings;
}

class GridSettings : public QDialog
{
    Q_OBJECT

public:
    explicit GridSettings(QWidget *parent = 0);
    ~GridSettings();

    int gridSize() const;
    int gridStep() const;

private slots:


    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_helpButton_clicked();

private:
    Ui::GridSettings *ui;
};

#endif // GRIDSETTINGS_H
