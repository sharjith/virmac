#include "blockentryimpl.h"
//
BlockEntryImpl::BlockEntryImpl( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//

#include <QMessageBox>
void BlockEntryImpl::on_pushButton3_clicked()
{
	QMessageBox::information(this, "Information", "Enter the block number to find and press Ok");
}
