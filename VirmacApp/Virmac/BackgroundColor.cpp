#include "BackgroundColor.h"
#include "ui_BackgroundColor.h"

#include "VirmacViewer.h"

#include <QColorDialog>
#include <QMessageBox>

BackgroundColor::BackgroundColor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BackgroundColor)
{
    ui->setupUi(this);

    VirmacViewer* viewer = dynamic_cast<VirmacViewer*>(parent);
    if(viewer)
    {
        VirmacGLView* view = viewer->GetView();
        topColor = view->GetBackgroundTopColor();
        QPalette pal = ui->pushButtonTop->palette();
        pal.setColor(QPalette::Button, topColor);
        ui->pushButtonTop->setAutoFillBackground(true);
        ui->pushButtonTop->setPalette(pal);
        ui->pushButtonTop->update();

        pal = ui->pushButtonBottom->palette();
        bottomColor = view->GetBackgroundBottomColor();
        pal.setColor(QPalette::Button, bottomColor);
        ui->pushButtonBottom->setAutoFillBackground(true);
        ui->pushButtonBottom->setPalette(pal);
        ui->pushButtonBottom->update();
    }
}

BackgroundColor::~BackgroundColor()
{
    delete ui;
}



bool BackgroundColor::hasGradient() const
{
    return ui->checkBoxGrad->isChecked();
}

void BackgroundColor::on_okButton_clicked()
{
    QDialog::accept();
}

void BackgroundColor::on_cancelButton_clicked()
{
    QDialog::reject();
}

void BackgroundColor::on_pushButtonTop_clicked()
{
    QColor initColor;

    topColor = QColorDialog::getColor(initColor, this);

    VirmacViewer* viewer = dynamic_cast<VirmacViewer*>(parent());
    if(viewer)
    {
        VirmacGLView* view = viewer->GetView();
        initColor = view->GetBackgroundTopColor();

        QPalette pal = ui->pushButtonTop->palette();
        pal.setColor(QPalette::Button, topColor);
        ui->pushButtonTop->setAutoFillBackground(true);
        ui->pushButtonTop->setPalette(pal);
        ui->pushButtonTop->update();
    }
}

void BackgroundColor::on_pushButtonBottom_clicked()
{
    QColor initColor;

    bottomColor = QColorDialog::getColor(initColor, this);

    VirmacViewer* viewer = dynamic_cast<VirmacViewer*>(parent());
    if(viewer)
    {
        VirmacGLView* view = viewer->GetView();
        initColor = view->GetBackgroundBottomColor();

        QPalette pal = ui->pushButtonBottom->palette();
        pal.setColor(QPalette::Button, bottomColor);
        ui->pushButtonBottom->setAutoFillBackground(true);
        ui->pushButtonBottom->setPalette(pal);
        ui->pushButtonBottom->update();
    }
}
