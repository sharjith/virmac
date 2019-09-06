#include <QMessageBox>

#include "ToolLibrary.h"
#include "ui_ToolLibrary.h"

#include "VToolViewer.h"
#include "VirmacViewer.h"
#include "VirmacDocument.h"

#include <stdio.h>

ToolLibrary::ToolLibrary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolLibrary)
{
    ui->setupUi(this);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    init();
}

ToolLibrary::~ToolLibrary()
{
    delete ui;
}

void ToolLibrary::on_buttonCancel_clicked()
{
    QDialog::reject();
}

void ToolLibrary::on_buttonHelp_clicked()
{

}

#include "ToolDefinition.h"
void ToolLibrary::on_buttonAddNew_clicked()
{
    ++toolCount;
    ToolDefinition tbl(this);
    tbl.setToolNumber(toolCount);
    int res = tbl.exec();
    if(res == QDialog::Accepted)
    {
        int index = tbl.getToolPage();
        myViewer->itsType = static_cast<CutterType>(index+1);
        myViewer->itsHolderDia = tbl.getHolderDia();
        myViewer->itsHolderLen = tbl.getHolderLen();
        myViewer->itsShankDia = tbl.getShankDia();
        myViewer->itsShankLen = tbl.getShankLength();
        myViewer->itsTaperDiaA =  tbl.getTaperDiaA();
        myViewer->itsTaperDiaB =  tbl.getTaperDiaB();
        myViewer->itsTaperLen = tbl.getTaperLength();
        myViewer->itsBodyDia = tbl.getBodyDia();
        myViewer->itsBodyLen = tbl.getBodyLength();
        myViewer->itsBallRad = tbl.getBallRad();

        int toolIndex = tbl.getToolNumber() - 1;

        ui->tableWidget->insertRow(toolIndex);

        switch (index)
        {
        case 0:
            ui->tableWidget->setItem(toolIndex, 0,  new QTableWidgetItem("BALLNOSE"));
            break;
        case 1:
            ui->tableWidget->setItem(toolIndex, 0,  new QTableWidgetItem("SPHERICAL"));
            break;
        case 2:
            ui->tableWidget->setItem(toolIndex, 0,  new QTableWidgetItem("TORICAL"));
            break;
        case 3:
            ui->tableWidget->setItem(toolIndex, 0,  new QTableWidgetItem("CYLINDRICAL"));
            break;
        default:
            ui->tableWidget->setItem(toolIndex, 0,  new QTableWidgetItem("UNKNOWN"));
            break;
        }

        ui->tableWidget->setItem(toolIndex, 1, new QTableWidgetItem(QString("%1").arg(tbl.getBodyDia())));
        ui->tableWidget->setItem(toolIndex, 2, new QTableWidgetItem(QString("%1").arg(tbl.getBallRad())));
        ui->tableWidget->setItem(toolIndex, 3, new QTableWidgetItem(QString("%1").arg(tbl.getBodyLength())));
        ui->tableWidget->setItem(toolIndex, 4, new QTableWidgetItem(QString("%1").arg(tbl.getHolderDia())));
        ui->tableWidget->setItem(toolIndex, 5, new QTableWidgetItem(QString("%1").arg(tbl.getHolderLen())));
        ui->tableWidget->setItem(toolIndex, 6, new QTableWidgetItem(QString("%1").arg(tbl.getShankDia())));
        ui->tableWidget->setItem(toolIndex, 7, new QTableWidgetItem(QString("%1").arg(tbl.getShankLength())));
        ui->tableWidget->setItem(toolIndex, 8, new QTableWidgetItem(QString("%1").arg(tbl.getTaperDiaA())));
        ui->tableWidget->setItem(toolIndex, 9, new QTableWidgetItem(QString("%1").arg(tbl.getTaperDiaB())));
        ui->tableWidget->setItem(toolIndex, 10, new QTableWidgetItem(QString("%1").arg(tbl.getTaperLength())));


        ui->tableWidget->selectRow(toolIndex);
    }
    else
        --toolCount;

    //return;


    QString pth = QCoreApplication::applicationDirPath();
    pth = pth + "/data/cutter.dat";

    FILE* fp = fopen(pth.toLatin1(), "w");
    if(fp)
    {
        int i;
        fprintf(fp, "%d", toolCount);
        for(i = 0; i < toolCount; i++)
        {
            QString str = ui->tableWidget->item(i, 0)->text();
            if(!str.isEmpty())
            {
                fprintf(fp, "\n%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
                        static_cast<const char*>(ui->tableWidget->item(i, 0)->text().toLatin1()),
                        ui->tableWidget->item(i, 1)->text().toDouble(),
                        ui->tableWidget->item(i, 2)->text().toDouble(),
                        ui->tableWidget->item(i, 3)->text().toDouble(),
                        ui->tableWidget->item(i, 4)->text().toDouble(),
                        ui->tableWidget->item(i, 5)->text().toDouble(),
                        ui->tableWidget->item(i, 6)->text().toDouble(),
                        ui->tableWidget->item(i, 7)->text().toDouble(),
                        ui->tableWidget->item(i, 8)->text().toDouble(),
                        ui->tableWidget->item(i, 9)->text().toDouble(),
                        ui->tableWidget->item(i, 10)->text().toDouble());
            }
        }
        fclose(fp);
    }
    else
    {
        QMessageBox::critical(0, tr("LoadTool"), tr("File cutter.dat not found\nPlease set the environment variable VRMTLIB to correct location"), QMessageBox::Ok, 0, 0);
    }
}

void ToolLibrary::init()
{
    myViewer = new VToolViewer(ui->frame, static_cast<QGLWidget*>(parent()));
    if(!myViewer)
    {
        qWarning("Cannot Create Viewer!");
        return;
    }
    // Put the GL widget inside the frame
    QHBoxLayout* flayout = new QHBoxLayout(ui->frame);
    flayout->addWidget( myViewer, 1 );

    //load tools
    double HolderDia, HolderLen, ShankDia, ShankLen, TaperDiaA,TaperDiaB, TaperLen, BodyDia, BodyLen, BallRad;
    char typ[20];

    QString pth = QCoreApplication::applicationDirPath();
    //pth += "/cutter.dat";
    pth = pth +  "/data/cutter.dat";

    FILE* fp = fopen(pth.toLatin1(), "r");
    if(fp)
    {
        int ret = fscanf(fp, "%d", &toolCount);

        if(ret == 0)
        {
            toolCount = 0;
            QMessageBox::critical(0, tr("Init"), tr("File cutter.dat not read"), QMessageBox::Ok, 0, 0);
            fclose(fp);
            return;
        }

        ui->tableWidget->setSortingEnabled(false);
        for(int i = 0; i < toolCount; i++)
        {
            ret = fscanf(fp, "%s %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",  typ, &BodyDia,  &BallRad,  &BodyLen, &HolderDia, &HolderLen, &ShankDia, &ShankLen, &TaperDiaA, &TaperDiaB, &TaperLen);

            if(ret == 0)
                break;
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(typ)));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(BodyDia)));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(BallRad)));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString("%1").arg(BodyLen)));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString("%1").arg(HolderDia)));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString("%1").arg(HolderLen)));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString("%1").arg(ShankDia)));
            ui->tableWidget->setItem(i, 7, new QTableWidgetItem(QString("%1").arg(ShankLen)));
            ui->tableWidget->setItem(i, 8, new QTableWidgetItem(QString("%1").arg(TaperDiaA)));
            ui->tableWidget->setItem(i, 9, new QTableWidgetItem(QString("%1").arg(TaperDiaB)));
            ui->tableWidget->setItem(i, 10, new QTableWidgetItem(QString("%1").arg(TaperLen)));
        }
        ui->tableWidget->selectRow(0);
        fclose(fp);
    }
    else
    {
        toolCount = 0;
        QMessageBox::critical(0, tr("Init"), tr("File cutter.dat not found"), QMessageBox::Ok, 0, 0);
    }
}

void ToolLibrary::loadTool()
{
    int row = ui->tableWidget->currentRow();

    VirmacViewer* view = static_cast<VirmacViewer*>(parent());
    if( view )
    {
        view->setFocus();
        VirmacDocument* doc = (VirmacDocument*)view->getDocument();

        MillingCutter* cutter = doc->myCutter;
        if(cutter)
        {
            QString typ = ui->tableWidget->item(row, 0)->text();
            if(typ == "BALLNOSE")
                cutter->SetCutterType(MILL_BALL_NOSE);
            if(typ == "SPHERICAL")
                cutter->SetCutterType(MILL_SPHERICAL);
            if(typ == "TORICAL")
                cutter->SetCutterType(MILL_TOROIDAL);
            if(typ == "CYLINDRICAL")
                cutter->SetCutterType(MILL_CYLINDRICAL);

            cutter->SetBodyDia(ui->tableWidget->item(row, 1)->text().toDouble());
            cutter->SetBallRad(ui->tableWidget->item(row, 2)->text().toDouble());
            cutter->SetBodyLen(ui->tableWidget->item(row, 3)->text().toDouble());
            cutter->SetHolderDia (ui->tableWidget->item(row, 4)->text().toDouble());
            cutter->SetHolderLen(ui->tableWidget->item(row, 5)->text().toDouble());
            cutter->SetShankDia(ui->tableWidget->item(row, 6)->text().toDouble());
            cutter->SetShankLen(ui->tableWidget->item(row, 7)->text().toDouble());
            cutter->SetTaperDiaA(ui->tableWidget->item(row, 8)->text().toDouble());
            cutter->SetTaperDiaB(ui->tableWidget->item(row, 9)->text().toDouble());
            cutter->SetTaperLen(ui->tableWidget->item(row, 10)->text().toDouble());
            cutter->RebuildDisplayLists();
            view->GetView()->Refresh();
        }

        //QMessageBox::information(0, tr("LoadTool"), tr("Ball Rad %1").arg(cutter->GetBallRad()), QMessageBox::Ok, 0, 0);

    }
}



void ToolLibrary::on_tableWidget_itemSelectionChanged()
{
    int row = ui->tableWidget->currentRow();

    if(row < 0)
        return;

    // QMessageBox::information(0, tr("LoadTool"), tr("Row Number %1").arg(row), QMessageBox::Ok, 0, 0);
    QString typ = ui->tableWidget->item(row, 0)->text();
    if(typ == "BALLNOSE")
        myViewer->itsType = BALLNOSE;
    if(typ == "SPHERICAL")
        myViewer->itsType = SPHERICAL;
    if(typ == "TORICAL")
        myViewer->itsType = TORICAL;
    if(typ == "CYLINDRICAL")
        myViewer->itsType = CYLINDRICAL;
    myViewer->itsBodyDia = ui->tableWidget->item(row, 1)->text().toDouble();
    myViewer->itsBallRad = ui->tableWidget->item(row, 2)->text().toDouble();
    myViewer->itsBodyLen = ui->tableWidget->item(row, 3)->text().toDouble();
    myViewer->itsHolderDia = ui->tableWidget->item(row, 4)->text().toDouble();
    myViewer->itsHolderLen = ui->tableWidget->item(row, 5)->text().toDouble();
    myViewer->itsShankDia = ui->tableWidget->item(row, 6)->text().toDouble();
    myViewer->itsShankLen = ui->tableWidget->item(row, 7)->text().toDouble();
    myViewer->itsTaperDiaA = ui->tableWidget->item(row, 8)->text().toDouble();
    myViewer->itsTaperDiaB = ui->tableWidget->item(row, 9)->text().toDouble();
    myViewer->itsTaperLen = ui->tableWidget->item(row, 10)->text().toDouble();
    loadTool();
    myViewer->updateView();

    //QMessageBox::information(0, tr("LoadTool"), tr("Tool Type %1").arg(table1->text(row, 0)), QMessageBox::Ok, 0, 0);
}

void ToolLibrary::on_tableWidget_cellChanged(int /*row*/, int /*column*/)
{
    on_tableWidget_itemSelectionChanged();
}
