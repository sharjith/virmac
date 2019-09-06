#ifndef TOOLLIBRARY_H
#define TOOLLIBRARY_H

#include <QDialog>

namespace Ui {
class ToolLibrary;
}

class VToolViewer;

class ToolLibrary : public QDialog
{
    Q_OBJECT

public:
    explicit ToolLibrary(QWidget *parent = 0);
    ~ToolLibrary();

private slots:
    void on_buttonCancel_clicked();

    void on_buttonHelp_clicked();

    void on_buttonAddNew_clicked();

    void on_tableWidget_itemSelectionChanged();

    void on_tableWidget_cellChanged(int row, int column);

private:
    void init();
    void loadTool();

private:
    Ui::ToolLibrary *ui;

    VToolViewer* myViewer;
    int toolCount;
};

#endif // TOOLLIBRARY_H
