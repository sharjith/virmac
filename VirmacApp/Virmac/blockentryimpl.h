#ifndef BLOCKENTRYIMPL_H
#define BLOCKENTRYIMPL_H
//
#include "ui_BlockEntry.h"
//
class BlockEntryImpl : public QDialog, public Ui::BlockEntry
{
Q_OBJECT
public:
	BlockEntryImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
	void on_pushButton3_clicked();
};
#endif






