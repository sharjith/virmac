#include "BlockEntry.h"
#include "ui_BlockEntry.h"

BlockEntry::BlockEntry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlockEntry)
{
    ui->setupUi(this);
}

BlockEntry::~BlockEntry()
{
    delete ui;
}

int BlockEntry::blockNumber() const
{
    return ui->SpinBoxBlock->text().toInt();
}

void BlockEntry::on_okButton_clicked()
{
    close();
}

void BlockEntry::on_cancelButton_clicked()
{
    close();
}

void BlockEntry::on_helpButton_clicked()
{

}
