#ifndef TRANSFORMATIONSIMPL_H
#define TRANSFORMATIONSIMPL_H
//
#include "ui_Transformations.h"
//
class TransformationsImpl : public QDialog, public Ui::Transformations
{
Q_OBJECT
public:
	TransformationsImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
	void on_pushButton57_clicked();
};
#endif





