#ifndef TOOLDEFINITION_H
#define TOOLDEFINITION_H

#include <QDialog>

namespace Ui {
class ToolDefinition;
}

class ToolDefinition : public QDialog
{
    Q_OBJECT

public:
    explicit ToolDefinition(QWidget *parent = 0);
    ~ToolDefinition();

    void setToolNumber(const int& val);
    void setBodyDia(const double& val);
    void setBallRad(const double& val);
    void setBodyLength(const double& val);
    void setHolderDia(const double& val);
    void setHolderLen(const double& val);
    void setShankDia(const double& val);
    void setShankLength(const double& val);
    void setTaperDiaA(const double& val);
    void setTaperDiaB(const double& val);
    void setTaperLength(const double& val);

    int getToolPage() const;
    int getToolNumber() const;
    double getBodyDia() const;
    double getBallRad() const;
    double getBodyLength() const;
    double getHolderDia() const;
    double getHolderLen() const;
    double getShankDia() const;
    double getShankLength() const;
    double getTaperDiaA() const;
    double getTaperDiaB() const;
    double getTaperLength() const;

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_helpButton_clicked();

private:
    Ui::ToolDefinition *ui;
};

#endif // TOOLDEFINITION_H
