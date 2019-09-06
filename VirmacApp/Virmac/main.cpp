
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>

#include "VirmacMainWin.h"
#include <iostream>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    
    //QApplication::setStyle(QStyleFactory::create("Fusion"));
    
    QPixmap pixmap(":/images/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();   

    app.processEvents();

    VirmacMainWin* mw = new VirmacMainWin();
    mw->showMaximized();

    mw->openDocumentFile("");
    
    splash.finish(mw);
    
    return app.exec();
}
