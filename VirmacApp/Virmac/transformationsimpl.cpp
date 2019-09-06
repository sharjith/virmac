#include "transformationsimpl.h"
//
TransformationsImpl::TransformationsImpl( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}
//

#include <QMessageBox>
void TransformationsImpl::on_pushButton57_clicked()
{
	QMessageBox::information(this, "Information", 
	"Fill the required transformation values and press Ok");
}

