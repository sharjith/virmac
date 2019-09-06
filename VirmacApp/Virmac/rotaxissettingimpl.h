#ifndef ROTAXISSETTINGIMPL_H
#define ROTAXISSETTINGIMPL_H
//
#include "ui_RotAxisSetting.h"
//
class RotAxisSettingImpl : public QDialog, public Ui::RotAxisSetting
{
Q_OBJECT
public:
	RotAxisSettingImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
	void on_pushButton45_clicked();
};
#endif





