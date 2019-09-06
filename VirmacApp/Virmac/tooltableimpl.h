#ifndef TOOLTABLEIMPL_H
#define TOOLTABLEIMPL_H
//
#include "ui_ToolTable.h"
//
class ToolTableImpl : public QDialog, public Ui::ToolTable
{
Q_OBJECT
public:
	ToolTableImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
	void on_pushButton54_clicked();
};
#endif





