#ifndef BLOCKENTRY_H
#define BLOCKENTRY_H

#include <QDialog>

namespace Ui {
class BlockEntry;
}

class BlockEntry : public QDialog
{
    Q_OBJECT

public:
    explicit BlockEntry(QWidget *parent = 0);
    ~BlockEntry();

    int blockNumber() const;

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_helpButton_clicked();

private:
    Ui::BlockEntry *ui;
};

#endif // BLOCKENTRY_H
