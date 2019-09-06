/****************************************************************************
** Form interface generated from reading ui file 'GCodeEditor.ui'
**
** Created: Sat Sep 15 11:20:51 2012
**      by: The User Interface Compiler ($Id: main.cpp 2051 2007-02-21 10:04:20Z chehrlic $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef GCODEEDITOR_H
#define GCODEEDITOR_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>
#include "VirmacDoc.h"
#include "Virmac.h"
#include "VirmacView.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTextEdit;

class GCodeEditor : public QWidget
{
    Q_OBJECT

public:
    GCodeEditor( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~GCodeEditor();

    QPushButton* pushButton1;
    QPushButton* pushButton2;
    QPushButton* pushButton5;
    QPushButton* pushButton6;
    QPushButton* pushButton9;
    QPushButton* pushButton10;
    QPushButton* pushButton11;
    QPushButton* pushButton12;
    QPushButton* pushButton7;
    QPushButton* pushButton8;
    QTextEdit* textEdit1;

    virtual void loadGCode();
    virtual void init();

public slots:
    virtual void slotOpen();
    virtual void slotSave();
    virtual void slotReload();
    virtual void slotHelp();
    virtual void slotSaveAs();
    virtual void slotClose();

protected:
    QGridLayout* GCodeEditorLayout;
    QVBoxLayout* layout4;
    QHBoxLayout* layout3;
    QSpacerItem* spacer3;

protected slots:
    virtual void languageChange();

private:
    QString pathName;

    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;
    QPixmap image6;
    QPixmap image7;
    QPixmap image8;
    QPixmap image9;
    QPixmap image10;

};

#endif // GCODEEDITOR_H
