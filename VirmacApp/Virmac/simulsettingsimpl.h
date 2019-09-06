#ifndef SIMULSETTINGSIMPL_H
#define SIMULSETTINGSIMPL_H
//
#include "ui_SimulSettings.h"
//
class SimulSettingsImpl : public QDialog, public Ui::SimulSettings
{
Q_OBJECT
public:
	SimulSettingsImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
	void on_pushButton48_clicked();
};
#endif





