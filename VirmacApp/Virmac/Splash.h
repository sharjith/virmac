/****************************************************************************
** Form interface generated from reading ui file 'Splash.ui'
**
** Created: Sat Sep 15 11:20:46 2012
**      by: The User Interface Compiler ($Id: main.cpp 2051 2007-02-21 10:04:20Z chehrlic $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SPLASH_H
#define SPLASH_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>
#include <qtimer.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;

class Splash : public QWidget
{
    Q_OBJECT

public:
    Splash( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Splash();

    QLabel* pixmapLabel1;

    virtual void init();

public slots:
    virtual void timerDone();
    virtual void mousePressEvent( QMouseEvent * e );
    virtual void keyPressEvent( QKeyEvent * e );

protected:
    QGridLayout* SplashLayout;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;

};

#endif // SPLASH_H
