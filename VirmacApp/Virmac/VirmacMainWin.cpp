/***************************************************************************
  virmac.cpp  -  description
  -------------------
begin                : Thu Dec  4 09:55:15 IST 2003
copyright            : (C) 2003 by Sharjith Nair
email                : sharjith_ssn@hotmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// Qt includes
#include <QApplication>
#include <QVBoxLayout>
#include <QShortcut>
#include <QLayout>
#include <QDesktopWidget>
#include <QRect>
#include <QPoint>
#include <QMessageBox>
#include <QToolButton>
#include <QColorDialog>

// application specific includes
#include "VirmacViewer.h"
#include "VirmacDocument.h"
#include "VirmacMainWin.h"


VirmacMainWin* VirmacMainWin::getMainWindow()
{
    QWidgetList widgets = qApp->topLevelWidgets();
    for (QWidgetList::iterator i = widgets.begin(); i != widgets.end(); ++i)
        if ((*i)->objectName() == "MainWindow")
            return static_cast<VirmacMainWin*>(*i);
    return NULL;
}

QProgressBar *VirmacMainWin::getProgBar() const
{
    return progBar;
}

VirmacMainWin::VirmacMainWin()
{
    setObjectName("MainWindow");
    setWindowTitle(tr("Virmac 1.0") );
    setWindowIcon(QIcon(":/images/appIcon.png"));

    printer = new QPrinter;
    untitledCount=0;
    pDocList = new QList<VirmacDocument*>();

    mesgCnt = 0;
    promCnt = 0;

    ///////////////////////////////////////////////////////////////////
    // call inits to invoke all other construction parts

    initView();
    initActions();
    initMenuBar();
    initToolBar();
    initStatusBar();

    QDesktopWidget *d = QApplication::desktop();
    int w = d->width();     // returns desktop width
    int h = d->height();    // returns desktop height
    resize( w, h );

    bSplit = false;
    progBar = new QProgressBar(statusBar());
    cViewer = new QLabel(statusBar());
    cViewer->setMaximumWidth(250);
    cViewer->setMinimumWidth(250);
    cViewer->setScaledContents(true);
    cViewer->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    statusBar()->addPermanentWidget(progBar);
    statusBar()->addPermanentWidget(cViewer);

//    viewToolBar->setOn(true);
//    viewStatusBar->setOn(true);

    setUnifiedTitleAndToolBarOnMac(true);
}

VirmacMainWin::~VirmacMainWin()
{
    delete printer;
}

VirmacViewer* VirmacMainWin::getActiveView() const
{
    VirmacViewer* view = NULL;
    QMdiSubWindow* subWin = pWorkspace->activeSubWindow();
    if(subWin)
    {
        view = static_cast<VirmacViewer*>(subWin->widget());
    }

    return view;
}


void VirmacMainWin::initActions()
{
    QPixmap openIcon, gcodeIcon, gcodeWriteIcon, stlIcon, newIcon;
    newIcon = QPixmap(":/images/filenew.png");
    openIcon = QPixmap(":/images/fileopen.png");
    gcodeIcon = QPixmap(":/images/filegcode.png");
    gcodeWriteIcon = QPixmap(":/images/filewritegcode.png");
    stlIcon = QPixmap(":/images/filestl.png");

    //viewer toolbar
    QPixmap topIcon, bottomIcon, frontIcon, backIcon, leftIcon, rightIcon, axoIcon, multiIcon, orthoIcon, resetIcon, fitallIcon, zoomwinIcon, antialIcon, snapshotIcon;
    topIcon = QPixmap(":/images/top.png");
    bottomIcon = QPixmap(":/images/bottom.png");
    frontIcon = QPixmap(":/images/front.png");
    backIcon = QPixmap(":/images/back.png");
    leftIcon = QPixmap(":/images/left.png");
    rightIcon = QPixmap(":/images/right.png");
    axoIcon = QPixmap(":/images/axo.png");
    multiIcon = QPixmap(":/images/multi.png");
    orthoIcon = QPixmap(":/images/ortho.png");
    resetIcon = QPixmap(":/images/resetview.png");
    fitallIcon = QPixmap(":/images/fitall.png");
    zoomwinIcon = QPixmap(":/images/zoomwin.png");
    antialIcon = QPixmap(":/images/antial.png");
    snapshotIcon = QPixmap(":/images/snapshot.png");

    //anim toolbar
    QPixmap playIcon, playstepIcon, pickplayIcon, rewindIcon, pauseIcon, stopIcon;
    playIcon = QPixmap(":/images/play.png");
    playstepIcon = QPixmap(":/images/playstep.png");
    pickplayIcon = QPixmap(":/images/pickplay.png");
    rewindIcon = QPixmap(":/images/rewindxpm.png");
    pauseIcon = QPixmap(":/images/pause.png");
    stopIcon = QPixmap(":/images/stop.png");

    //util
    QPixmap trimBefIcon, trimAftIcon, pickBlocIcon, searchBlocIcon, measDistIcon, measAngIcon, editIcon;
    trimBefIcon = QPixmap(":/images/trimbefore.png");
    trimAftIcon = QPixmap(":/images/trimafter.png");
    pickBlocIcon = QPixmap(":/images/pickbloc.png");
    searchBlocIcon = QPixmap(":/images/searchbloc.png");
    measDistIcon = QPixmap(":/images/measdist.png");
    measAngIcon = QPixmap(":/images/measang.png");
    editIcon = QPixmap(":/images/edit.png");

    fileNew = new QAction(newIcon, tr("&New"), this);
    fileNew->setShortcut(QKeySequence(tr("Ctrl+N")));
    fileNew->setStatusTip(tr("Creates a new document"));
    fileNew->setWhatsThis(tr("New File\n\nCreates a new document"));
    connect(fileNew, SIGNAL(triggered()), this, SLOT(slotFileNew()));

    /*fileOpen = new QAction(tr("Open File"), openIcon, tr("&Open..."), 0, this);
      fileOpen->setStatusTip(tr("Opens an existing document"));
      fileOpen->setWhatsThis(tr("Open File\n\nOpens an existing document"));
      connect(fileOpen, SIGNAL(triggered()), this, SLOT(slotFileOpen()));*/

    fileReadGCode = new QAction(gcodeIcon, tr("&Read G Code"), this);
    fileReadGCode->setShortcut(QKeySequence(tr("Ctrl+Shift+R")));
    fileReadGCode->setStatusTip(tr("Read G Code File"));
    fileReadGCode->setWhatsThis(tr("Read G Code File.\n\nReads The G Code File To Simulate"));
    connect(fileReadGCode, SIGNAL(triggered()), this, SLOT(slotFileReadGCode()));

    fileWriteGCode = new QAction(gcodeWriteIcon, tr("&Write G Code"), this);
    fileWriteGCode->setShortcut(QKeySequence(tr("Ctrl+Shift+W")));
    fileWriteGCode->setStatusTip(tr("Write G Code File"));
    fileWriteGCode->setWhatsThis(tr("Write G Code File.\n\nWrite The G Code File To Disk"));
    connect(fileWriteGCode, SIGNAL(triggered()), this, SLOT(slotFileWriteGCode()));

    fileReadStl = new QAction(stlIcon, tr("Read &StL..."), this);
    fileReadStl->setShortcut(QKeySequence(tr("Ctrl+Shift+S")));
    fileReadStl->setStatusTip(tr("Read Stl File"));
    fileReadStl->setWhatsThis(tr("Read Stl File\n\nRead Stl File"));
    connect(fileReadStl, SIGNAL(triggered()), this, SLOT(slotFileReadStL()));

    fileClose = new QAction(tr("&Close"), this);
    fileClose->setShortcut(QKeySequence(tr("Ctrl+W")));
    fileClose->setStatusTip(tr("Closes the actual document"));
    fileClose->setWhatsThis(tr("Close File\n\nCloses the actual document"));
    connect(fileClose, SIGNAL(triggered()), this, SLOT(slotFileClose()));

    fileQuit = new QAction(tr("E&xit"), this);
    fileQuit->setShortcut(QKeySequence(tr("Ctrl+Q")));
    fileQuit->setStatusTip(tr("Quits the application"));
    fileQuit->setWhatsThis(tr("Exit\n\nQuits the application"));
    connect(fileQuit, SIGNAL(triggered()), this, SLOT(slotFileQuit()));

    editTrimBefore = new QAction(trimBefIcon, tr("Trim &Before"), this);
    editTrimBefore->setShortcut(QKeySequence(tr("Shift+B")));
    editTrimBefore->setStatusTip(tr("Trims The G Code Before The Selected Bloc"));
    editTrimBefore->setWhatsThis(tr("Trim Before\n\nTrim The G Code Before The Selected Bloc"));
    connect(editTrimBefore, SIGNAL(triggered()), this, SLOT(slotEditTrimBefore()));

    editTrimAfter = new QAction(trimAftIcon, tr("Trim &After"), this);
    editTrimAfter->setShortcut(QKeySequence(tr("Shift+A")));
    editTrimAfter->setStatusTip(tr("Trims The G Code Before The After Bloc"));
    editTrimAfter->setWhatsThis(tr("Trim Before\n\nTrim The G Code After The Selected Bloc"));
    connect(editTrimAfter, SIGNAL(triggered()), this, SLOT(slotEditTrimAfter()));

    editGCode = new QAction(editIcon, tr("Edit &GCode"), this);
    editGCode->setShortcut(QKeySequence(tr("Ctrl+E")));
    editGCode->setStatusTip(tr("Edit G Code File"));
    editGCode->setWhatsThis(tr("Edit G Code\n\nOpens G Code File For Editing"));
    connect(editGCode, SIGNAL(triggered()), this, SLOT(slotEditGCode()));

    viewToolBar = new QAction(tr("Tool&bar"), this);
    viewToolBar->setStatusTip(tr("Enables/disables the toolbar"));
    viewToolBar->setWhatsThis(tr("Toolbar\n\nEnables/disables the toolbar"));
    viewToolBar->setCheckable(true);
    viewToolBar->setChecked(true);
    connect(viewToolBar, SIGNAL(toggled(bool)), this, SLOT(slotViewToolBar(bool)));

    viewStatusBar = new QAction(tr("&Statusbar"), this);
    viewStatusBar->setStatusTip(tr("Enables/disables the statusbar"));
    viewStatusBar->setWhatsThis(tr("Statusbar\n\nEnables/disables the statusbar"));
    viewStatusBar->setCheckable(true);
    viewStatusBar->setChecked(true);
    connect(viewStatusBar, SIGNAL(toggled(bool)), this, SLOT(slotViewStatusBar(bool)));

    analysisPPInter = new QAction(tr("&Intersection"), this);
    analysisPPInter->setStatusTip(tr("Point To Point Tool Intersection Analysis"));
    analysisPPInter->setWhatsThis(tr("Intersection\n\nPoint To Point Tool Intersection Analysis"));
    connect(analysisPPInter, SIGNAL(toggled(bool)), this, SLOT(slotPPIntersection(bool)));

    analysisRoughStock = new QAction(tr("&Rough Stock"), this);
    analysisRoughStock->setStatusTip(tr("Rough Stock For WYSIWYC Analysis"));
    analysisRoughStock->setWhatsThis(tr("Rough Stock\n\nRough Stock For WYSIWYC Analysis"));
    connect(analysisRoughStock, SIGNAL(triggered()), this, SLOT(slotRoughStock()));

    analysisWYSIWYC = new QAction(tr("&WYSIWYC"), this);
    analysisWYSIWYC->setStatusTip(tr("What-You-See-Is-What-You-Cut Analysis"));
    analysisWYSIWYC->setWhatsThis(tr("WYSIWYC\n\nWhat-You-See-Is-What-You-Cut Analysis"));
    connect(analysisWYSIWYC, SIGNAL(triggered()), this, SLOT(slotWYSIWYC()));

    windowNewWindow = new QAction(tr("&New Window"), this);
    windowNewWindow->setStatusTip(tr("Opens a new view for the current document"));
    windowNewWindow->setWhatsThis(tr("New Window\n\nOpens a new view for the current document"));
    connect(windowNewWindow, SIGNAL(triggered()), this, SLOT(slotWindowNewWindow()));

    windowCascade = new QAction(tr("&Cascade"), this);
    windowCascade->setStatusTip(tr("Cascades all windows"));
    windowCascade->setWhatsThis(tr("Cascade\n\nCascades all windows"));
    connect(windowCascade, SIGNAL(triggered()), pWorkspace, SLOT(cascadeSubWindows()));

    windowTile = new QAction(tr("&Tile"), this);
    windowTile->setStatusTip(tr("Tiles all windows"));
    windowTile->setWhatsThis(tr("Tile\n\nTiles all windows"));
    connect(windowTile, SIGNAL(triggered()), pWorkspace, SLOT(tileSubWindows()));


    windowAction = new QActionGroup(this);
    windowAction->addAction(windowNewWindow);
    windowAction->addAction(windowCascade);
    windowAction->addAction(windowTile);

    helpAboutApp = new QAction(tr("&About..."), this);
    helpAboutApp->setStatusTip(tr("About the application"));
    helpAboutApp->setWhatsThis(tr("About\n\nAbout the application"));
    connect(helpAboutApp, SIGNAL(triggered()), this, SLOT(slotHelpAbout()));

    //viewer actions
    viewTop = new QAction(topIcon, tr("Top"), this);
    viewTop->setShortcut(QKeySequence(tr("Ctrl+T")));
    viewTop->setCheckable(true);
    viewTop->setStatusTip(tr("Displays The Top View"));
    viewTop->setWhatsThis(tr("Top View\n\nDisplays The Top View"));
    connect(viewTop, SIGNAL(triggered()), this, SLOT(slotTopView()));

    viewBottom = new QAction(bottomIcon, tr("Bottom"), this);
    viewBottom->setShortcut(QKeySequence(tr("Ctrl+B")));
    viewBottom->setCheckable(true);
    viewBottom->setStatusTip(tr("Displays The Bottom View"));
    viewBottom->setWhatsThis(tr("Bottom View\n\nDisplays The Bottom View"));
    connect(viewBottom, SIGNAL(triggered()), this, SLOT(slotBottomView()));

    viewFront = new QAction(frontIcon, tr("Front"), this);
    viewFront->setShortcut(QKeySequence(tr("Ctrl+F")));
    viewFront->setCheckable(true);
    viewFront->setStatusTip(tr("Displays The Front View"));
    viewFront->setWhatsThis(tr("Front View\n\nDisplays The Front View"));
    connect(viewFront, SIGNAL(triggered()), this, SLOT(slotFrontView()));

    viewBack = new QAction(backIcon, tr("Back"), this);
    viewBack->setShortcut(QKeySequence(tr("Ctrl+Shift+B")));
    viewBack->setCheckable(true);
    viewBack->setStatusTip(tr("Displays The Back View"));
    viewBack->setWhatsThis(tr("Back View\n\nDisplays The Back View"));
    connect(viewBack, SIGNAL(triggered()), this, SLOT(slotBackView()));

    viewLeft = new QAction(leftIcon, tr("Left"), this);
    viewLeft->setShortcut(QKeySequence(tr("Ctrl+L")));
    viewLeft->setCheckable(true);
    viewLeft->setStatusTip(tr("Displays The Left View"));
    viewLeft->setWhatsThis(tr("Left View\n\nDisplays The Left View"));
    connect(viewLeft, SIGNAL(triggered()), this, SLOT(slotLeftView()));

    viewRight = new QAction(rightIcon, tr("Right"), this);
    viewRight->setShortcut(QKeySequence(tr("Ctrl+R")));
    viewRight->setCheckable(true);
    viewRight->setStatusTip(tr("Displays The Right View"));
    viewRight->setWhatsThis(tr("Right View\n\nDisplays The Right View"));
    connect(viewRight, SIGNAL(triggered()), this, SLOT(slotRightView()));

    viewAxo = new QAction(axoIcon, tr("Axo"), this);
    viewAxo->setShortcut(QKeySequence(tr("Ctrl+A")));
    viewAxo->setCheckable(true);
    viewAxo->setChecked(true);
    viewAxo->setStatusTip(tr("Displays The Axonometric View"));
    viewAxo->setWhatsThis(tr("Axo View\n\nDisplays The Axonometric View"));
    connect(viewAxo, SIGNAL(triggered()), this, SLOT(slotAxoView()));

    viewMultiFour = new QAction(multiIcon, tr("MultiFour"), this);
    viewMultiFour->setShortcut(QKeySequence(tr("Ctrl+4")));
    viewMultiFour->setCheckable(true);
    viewMultiFour->setStatusTip(tr("Displays The Multiple Four Views"));
    viewMultiFour->setWhatsThis(tr("Multi Four View\n\nDisplays The Multiple Four Views"));
    connect(viewMultiFour, SIGNAL(triggered()), this, SLOT(slotMultiFour()));

    QActionGroup* viewGroup = new QActionGroup(this);

    viewGroup->addAction(viewTop);
    viewGroup->addAction(viewBottom);
    viewGroup->addAction(viewFront);
    viewGroup->addAction(viewBack);
    viewGroup->addAction(viewLeft);
    viewGroup->addAction(viewRight);
    viewGroup->addAction(viewAxo);
    viewGroup->addAction(viewMultiFour);

    viewProjection = new QAction(orthoIcon, tr("Perspective"), this);
    viewProjection->setStatusTip(tr("Toggles View Projection"));
    viewProjection->setWhatsThis(tr("Projection\n\nToggles View Projection Between Orthographic And Perspective"));
    connect(viewProjection, SIGNAL(triggered()), this, SLOT(slotProjection()));

    viewFitall = new QAction(fitallIcon, tr("Fit All"), this);
    viewFitall->setShortcut(QKeySequence(tr("F2")));
    viewFitall->setStatusTip(tr("Fits The View To Screen"));
    viewFitall->setWhatsThis(tr("Fit All\n\nFits The View To Screen"));
    connect(viewFitall, SIGNAL(triggered()), this, SLOT(slotFitall()));

    viewZoomwin = new QAction(zoomwinIcon, tr("Zoom Win"), this);
    viewZoomwin->setShortcut(QKeySequence(tr("Z")));
    viewZoomwin->setStatusTip(tr("Zooms The View Defined By A Window"));
    viewZoomwin->setWhatsThis(tr("Zoom Win\n\nZooms The View Defined By A Window"));
    connect(viewZoomwin, SIGNAL(triggered()), this, SLOT(slotZoomwin()));

    viewReset = new QAction(resetIcon, tr("Axo"), this);
    viewReset->setStatusTip(tr("Resets The View"));
    viewReset->setWhatsThis(tr("Reset View\n\nResets The View"));
    connect(viewReset, SIGNAL(triggered()), this, SLOT(slotReset()));

    viewAntial = new QAction(antialIcon, tr("Antialias"), this);
    viewAntial->setStatusTip(tr("Toggle Antialias"));
    viewAntial->setWhatsThis(tr("Toggle Antialias\n\nToggles Antialiasing On And Off"));
    connect(viewAntial, SIGNAL(triggered()), this, SLOT(slotAntial()));

    viewSnapshot = new QAction(snapshotIcon, tr("Snapshot"), this);
    viewSnapshot->setStatusTip(tr("Take A Snapshot"));
    viewSnapshot->setWhatsThis(tr("Take A Snapshot\n\nTakes A Snapshot Of Current Screen"));
    connect(viewSnapshot, SIGNAL(triggered()), this, SLOT(slotSnapshot()));

    bgColor = new QAction(tr("Background Color"), this);
    bgColor->setStatusTip(tr("Sets The Background Color"));
    bgColor->setWhatsThis(tr("Background Color\n\nChange The Background Color"));
    connect(bgColor, SIGNAL(triggered()), this, SLOT(slotBgColor()));

    //animation
    animPlay = new QAction(playIcon, tr("Play"), this);
    animPlay->setShortcut(QKeySequence(tr("Ctrl+P")));
    animPlay->setStatusTip(tr("Play Simulation"));
    animPlay->setWhatsThis(tr("Play Simulation\n\nStart Playing The Animation"));
    connect(animPlay, SIGNAL(triggered()), this, SLOT(slotPlay()));

    animPlayStep = new QAction(playstepIcon, tr("Play Step"), this);
    animPlayStep->setShortcut(QKeySequence(tr("F5")));
    animPlayStep->setStatusTip(tr("Play Step"));
    animPlayStep->setWhatsThis(tr("Play Simulation Step\n\nStart Playing The Animation Step By Step"));
    connect(animPlayStep, SIGNAL(triggered()), this, SLOT(slotPlayStep()));

    animPickPlay = new QAction(pickplayIcon, tr("Pick And Play"), this);
    animPickPlay->setShortcut(QKeySequence(tr("Shift+Ctrl+P")));
    animPickPlay->setStatusTip(tr("Pick Play Simulation"));
    animPickPlay->setWhatsThis(tr("Pick Play Simulation\n\nStart Playing The Animation From Picked Block"));
    connect(animPickPlay, SIGNAL(triggered()), this, SLOT(slotPickPlay()));

    animRewind = new QAction(rewindIcon, tr("Rewind"), this);
    animRewind->setShortcut(QKeySequence(tr("Alt+W")));
    animRewind->setStatusTip(tr("Rewind Simulation"));
    animRewind->setWhatsThis(tr("Rewind Simulation\n\nRewind The Animation"));
    connect(animRewind, SIGNAL(triggered()), this, SLOT(slotRewind()));

    animPause = new QAction(pauseIcon, tr("Pause"), this);
    animPause->setShortcut(QKeySequence(tr("Alt+P")));
    animPause->setStatusTip(tr("Pause Simulation"));
    animPause->setWhatsThis(tr("Pause Simulation\n\nPause The Animation"));
    connect(animPause, SIGNAL(triggered()), this, SLOT(slotPause()));

    animStop = new QAction(stopIcon, tr("Stop"), this);
    animStop->setShortcut(QKeySequence(tr("Alt+S")));
    animStop->setStatusTip(tr("Stop Simulation"));
    animStop->setWhatsThis(tr("Stop Simulation\n\nStop Playing The Animation"));
    connect(animStop, SIGNAL(triggered()), this, SLOT(slotStop()));

    deleteSirus = new QAction(tr("Delete Sirus"), this);
    deleteSirus->setShortcut(QKeySequence(tr("Ctrl+D")));
    deleteSirus->setStatusTip(tr("Delete Sirus"));
    deleteSirus->setWhatsThis(tr("Delete Sirus\n\nDelete The G Code Sirus"));
    connect(deleteSirus, SIGNAL(triggered()), this, SLOT(slotDeleteSirus()));

    deleteModel = new QAction(tr("Delete Model"), this);
    deleteModel->setShortcut(QKeySequence(tr("Ctrl+M")));
    deleteModel->setStatusTip(tr("Delete Model"));
    deleteModel->setWhatsThis(tr("Delete Model\n\nDelete The StL Model"));
    connect(deleteModel, SIGNAL(triggered()), this, SLOT(slotDeleteModel()));

    simulSettings = new QAction(tr("Parameters"), this);
    simulSettings->setStatusTip(tr("Simulation Settings"));
    simulSettings->setWhatsThis(tr("Simulation Settings\n\nSet The Simulation Parameters"));
    connect(simulSettings, SIGNAL(triggered()), this, SLOT(slotSimulSettings()));

    toolLibrary = new QAction( tr("Tool Library"), this);
    toolLibrary->setShortcut(QKeySequence(tr("Shift+T")));
    toolLibrary->setStatusTip(tr("Tool Library Settings"));
    toolLibrary->setWhatsThis(tr("toolLibrary Settings\n\nCall The Tool Library"));
    connect(toolLibrary, SIGNAL(triggered()), this, SLOT(slotToolLibrary()));

    rotaryAxis = new QAction(tr("Rotary Axis"), this );
    rotaryAxis->setStatusTip(tr("Rotary Axis Settings"));
    rotaryAxis->setWhatsThis(tr("Rotary Axis\n\nRotary Axis Settings For 5 Axis"));
    connect(rotaryAxis, SIGNAL(triggered()), this, SLOT(slotRotaryAxis()));

    startBlock = new QAction(tr("Start Block"), this );
    startBlock->setStatusTip(tr("Start Block Settings"));
    startBlock->setWhatsThis(tr("Start Block\n\nSet The Start Block For The Simulation"));
    connect(startBlock, SIGNAL(triggered()), this, SLOT(slotStartBlock()));

    pToolDisplayMode = new QAction(tr("Transparent"), this);
    pToolDisplayMode->setStatusTip(tr("Tool Transparent/Solid"));
    pToolDisplayMode->setWhatsThis(tr("Transparent/Solid\n\nDisplay Tool In Transparent Or Solid Mode"));
    connect(pToolDisplayMode, SIGNAL(triggered()), this, SLOT(slotToolDisplayMode()));

    pToolHide = new QAction(tr("Hide"), this );
    pToolHide->setStatusTip(tr("Tool Hide"));
    pToolHide->setWhatsThis(tr("Hide\n\nToggle Hiding/Displaying The Tool"));
    connect(pToolHide, SIGNAL(triggered()), this, SLOT(slotToolHide()));

    pToolColor = new QAction(tr("Color"), this );
    pToolColor->setStatusTip(tr("Tool Color"));
    pToolColor->setWhatsThis(tr("Color\n\nChange Color Of The Tool"));
    connect(pToolColor, SIGNAL(triggered()), this, SLOT(slotToolColor()));

    pToggleTrail = new QAction(tr("Off"), this);
    pToggleTrail->setShortcut(QKeySequence(tr("T")));
    pToggleTrail->setStatusTip(tr("Toggle Tool Trail"));
    pToggleTrail->setWhatsThis(tr("Toggle Tool Trail\n\nEnable/Disable Display Of The Tool Trail"));
    connect(pToggleTrail, SIGNAL(triggered()), this, SLOT(slotToggleTrail()));

    pModelDisplayMode = new QAction(tr("Wireframe"), this );
    pModelDisplayMode->setStatusTip(tr("Model Wireframe/Shaded"));
    pModelDisplayMode->setWhatsThis(tr("Wireframe/Shaded\n\nDisplay Model In Wireframe Or Shaded Mode"));
    connect(pModelDisplayMode, SIGNAL(triggered()), this, SLOT(slotModelDisplayMode()));

    pModelHide = new QAction(tr("Hide"), this );
    pModelHide->setStatusTip(tr("Model Hide"));
    pModelHide->setWhatsThis(tr("Hide\n\nToggle Hiding/Displaying The Model"));
    connect(pModelHide, SIGNAL(triggered()), this, SLOT(slotModelHide()));

    pModelColor = new QAction(tr("Color"), this );
    pModelColor->setStatusTip(tr("Model Color"));
    pModelColor->setWhatsThis(tr("Color\n\nChange Color Of The Model"));
    connect(pModelColor, SIGNAL(triggered()), this, SLOT(slotModelColor()));

    pModelMaterial = new QAction(tr("Material"), this );
    pModelMaterial->setStatusTip(tr("Model Material"));
    pModelMaterial->setWhatsThis(tr("Color\n\nChange Material Of The Model"));
    connect(pModelMaterial, SIGNAL(triggered()), this, SLOT(slotModelMaterial()));


    pModelNormals = new QAction(tr("Normals"), this );
    pModelNormals->setStatusTip(tr("Model Normals"));
    pModelNormals->setWhatsThis(tr("Normals\n\nToggle Display Of Normals Of The Model"));
    connect(pModelNormals, SIGNAL(triggered()), this, SLOT(slotModelNormals()));

    pToggleSirus = new QAction(tr("Hide Sirus"),  this);
    pToggleSirus->setShortcut(QKeySequence(tr("S")));
    pToggleSirus->setStatusTip(tr("Toggle Sirus"));
    pToggleSirus->setWhatsThis(tr("Toggle Sirus\n\nEnable/Disable Display Of The Sirus"));
    connect(pToggleSirus, SIGNAL(triggered()), this, SLOT(slotToggleSirus()));

    pColToolPath = new QAction(tr("Tool Path"), this );
    pColToolPath->setStatusTip(tr("ToolPath Color"));
    pColToolPath->setWhatsThis(tr("Color\n\nChange Color Of The ToolPath"));
    connect(pColToolPath, SIGNAL(triggered()), this, SLOT(slotColToolPath()));

    pColFeedTrail = new QAction(tr("Feed Trail"), this );
    pColFeedTrail->setStatusTip(tr("FeedTrail Color"));
    pColFeedTrail->setWhatsThis(tr("Color\n\nChange Color Of The FeedTrail"));
    connect(pColFeedTrail, SIGNAL(triggered()), this, SLOT(slotColFeedTrail()));

    pColRapidTrail = new QAction(tr("Rapid Trail"), this );
    pColRapidTrail->setStatusTip(tr("RapidTrail Color"));
    pColRapidTrail->setWhatsThis(tr("Color\n\nChange Color Of The RapidTrail"));
    connect(pColRapidTrail, SIGNAL(triggered()), this, SLOT(slotColRapidTrail()));

    pColG02Trail = new QAction(tr("G02 Trail"), this );
    pColG02Trail->setStatusTip(tr("G02 Color"));
    pColG02Trail->setWhatsThis(tr("Color\n\nChange Color Of The G02 Interpolation"));
    connect(pColG02Trail, SIGNAL(triggered()), this, SLOT(slotColG02Trail()));

    pColG03Trail = new QAction(tr("G03 Trail"), this );
    pColG03Trail->setStatusTip(tr("G03 Color"));
    pColG03Trail->setWhatsThis(tr("Color\n\nChange Color Of The G03 Interpolation"));
    connect(pColG03Trail, SIGNAL(triggered()), this, SLOT(slotColG03Trail()));

    pGridSettings = new QAction(tr("Settings"), this );
    pGridSettings->setStatusTip(tr("Grid Settings"));
    pGridSettings->setWhatsThis(tr("Settings\n\nChange Dimensions Of The Grid"));
    connect(pGridSettings, SIGNAL(triggered()), this, SLOT(slotGridSettings()));

    pColGrid = new QAction(tr("Color"), this );
    pColGrid->setStatusTip(tr("Grid Color"));
    pColGrid->setWhatsThis(tr("Color\n\nChange Color Of The Grid"));
    connect(pColGrid, SIGNAL(triggered()), this, SLOT(slotColGrid()));

    pToggleGrid = new QAction(tr("On"), this);
    pToggleGrid->setShortcut(QKeySequence(tr("G")));
    pToggleGrid->setStatusTip(tr("Toggle Grid"));
    pToggleGrid->setWhatsThis(tr("Toggle Grid\n\nToggle On/Off Display Of The Grid"));
    connect(pToggleGrid, SIGNAL(triggered()), this, SLOT(slotToggleGrid()));

    pToggleCircInt = new QAction(tr("Show Circular Interp"), this);
    pToggleCircInt->setShortcut(QKeySequence(tr("C")));
    pToggleCircInt->setStatusTip(tr("Toggle Circular Interpolation"));
    pToggleCircInt->setWhatsThis(tr("Toggle CircInt\n\nToggle On/Off Display Of The Circular Interpolation"));
    connect(pToggleCircInt, SIGNAL(triggered()), this, SLOT(slotToggleCircInt()));

    pTransform = new QAction(tr("Transformations"), this );
    pTransform->setStatusTip(tr("Set Transformations"));
    pTransform->setWhatsThis(tr("Transformations\n\nSet Transformations For The Sirus"));
    connect(pTransform, SIGNAL(triggered()), this, SLOT(slotTransform()));

    //util actions
    pSearchBlock = new QAction(searchBlocIcon, tr("Search Block"), this );
    pSearchBlock->setStatusTip(tr("Search An NC Block"));
    pSearchBlock->setWhatsThis(tr("Search Block\n\nSearch A Specified NC Block In The Sirus"));
    connect(pSearchBlock, SIGNAL(triggered()), this, SLOT(slotSearchBlock()));

    pPickBlock = new QAction(pickBlocIcon, tr("Pick Block"), this );
    pPickBlock->setStatusTip(tr("Pick Block"));
    pPickBlock->setWhatsThis(tr("Pick Block\n\nPick Block In The Sirus From The Screen"));
    connect(pPickBlock, SIGNAL(triggered()), this, SLOT(slotPickBlock()));

    pMeasDist = new QAction(measDistIcon, tr("Measure Distance"), this );
    pMeasDist->setStatusTip(tr("Measure Distance"));
    pMeasDist->setWhatsThis(tr("Measure Distance\n\nMeasure Distance Between Two Blocks In The Sirus From The Screen"));
    connect(pMeasDist, SIGNAL(triggered()), this, SLOT(slotMeasDist()));

    pMeasAng = new QAction(measDistIcon, tr("Measure Angle"), this );
    pMeasAng->setStatusTip(tr("Measure Angle"));
    pMeasAng->setWhatsThis(tr("Measure Angle\n\nMeasure Vector Angle Between Three Blocks In The Sirus From The Screen"));
    connect(pMeasAng, SIGNAL(triggered()), this, SLOT(slotMeasAng()));
    
    pSimulRep = new QAction(tr("Simulation Report"), this );
    pSimulRep->setStatusTip(tr("Show Simulation Report"));
    pSimulRep->setWhatsThis(tr("Simul Report\n\nShow The Simulation Report"));
    connect(pSimulRep, SIGNAL(triggered()), this, SLOT(slotSimulRep()));

}

void VirmacMainWin::initMenuBar()
{
    ///////////////////////////////////////////////////////////////////
    // MENUBAR
    //menuBar()->setNativeMenuBar(false);

    ///////////////////////////////////////////////////////////////////
    // menuBar entry pFileMenu
    pFileMenu = menuBar()->addMenu(tr("&File"));
    pFileMenu->setTearOffEnabled(true);
    pFileMenu->addAction(fileNew);
    //fileOpen->addTo(pFileMenu);
    pFileMenu->addAction(fileReadGCode);
    pFileMenu->addAction(fileWriteGCode);
    pFileMenu->addAction(fileReadStl);
    pFileMenu->addAction(fileClose);
    pFileMenu->addSeparator();
    pFileMenu->addAction(fileQuit);

    ///////////////////////////////////////////////////////////////////
    // menuBar entry editMenu
    pEditMenu = menuBar()->addMenu(tr("&Edit"));
    pEditMenu->setTearOffEnabled(true);
    pEditMenu->addAction(editGCode);
    pEditMenu->addSeparator();
    pEditMenu->addAction(editTrimBefore);
    pEditMenu->addAction(editTrimAfter);

    ///////////////////////////////////////////////////////////////////
    // menuBar entry viewMenu
    pViewMenu = menuBar()->addMenu(tr("&View"));

    pViewMenu->setTearOffEnabled(true);

    pViewMenu->addAction(viewTop);
    pViewMenu->addAction(viewBottom);
    pViewMenu->addAction(viewFront);
    pViewMenu->addAction(viewBack);
    pViewMenu->addAction(viewLeft);
    pViewMenu->addAction(viewRight);
    pViewMenu->addAction(viewAxo);
    pViewMenu->addAction(viewMultiFour);
    pViewMenu->addSeparator();
    pViewMenu->addAction(viewProjection);
    pViewMenu->addSeparator();
    pViewMenu->addAction(viewFitall);
    pViewMenu->addAction(viewZoomwin);
    pViewMenu->addAction(viewReset);
    pViewMenu->addAction(viewAntial);
    pViewMenu->addSeparator();
    pViewMenu->addAction(viewSnapshot);
    pViewMenu->addSeparator();
    pViewMenu->addAction(viewToolBar);
    pViewMenu->addAction(viewStatusBar);
    pViewMenu->addSeparator();

    ///////////////////////////////////////////////////////////////////
    //simulation
    pSimulMenu = menuBar()->addMenu(tr("&Simulation"));

    pSimulMenu->setTearOffEnabled(true);

    pSimulMenu->addAction(animPlay);
    pSimulMenu->addAction(animPlayStep);
    pSimulMenu->addAction(animPickPlay);
    pSimulMenu->addAction(animRewind);
    pSimulMenu->addAction(animPause);
    pSimulMenu->addAction(animStop);

    pSimulMenu->addSeparator();
    pSimulMenu->addAction(deleteSirus);
    pSimulMenu->addAction(deleteModel);
    pSimulMenu->addSeparator();
    pSimulMenu->addAction(simulSettings);
    pSimulMenu->addAction(toolLibrary);
    pSimulMenu->addAction(rotaryAxis);
    pSimulMenu->addAction(startBlock);

    //preferences
    pPrefMenu = menuBar()->addMenu("&Preferences");
    //pPrefMenu->setCheckable(true);
    pPrefMenu->setTearOffEnabled(true);

    pToolMenu = new QMenu(tr("&Tool"));
    pPrefMenu->addMenu(pToolMenu);
    pToolMenu->setTearOffEnabled(true);
    pToolMenu->addAction(pToolDisplayMode);
    pToolMenu->addAction(pToolHide);
    pToolMenu->addAction(pToolColor);
    connect(pToolMenu, SIGNAL(aboutToShow()), this, SLOT(toolMenuATS()));

    pTrailMenu = new QMenu(tr("T&rail"));
    pToolMenu->addMenu(pTrailMenu);
    pTrailMenu->addAction(pToggleTrail);
    connect(pTrailMenu, SIGNAL(aboutToShow()), this, SLOT(trailMenuATS()));

    pModelMenu = new QMenu(tr("&Model"));
    pPrefMenu->addMenu(pModelMenu);
    pModelMenu->setTearOffEnabled(true);
    pModelMenu->addAction(pModelDisplayMode);
    pModelMenu->addAction(pModelHide);
    pModelMenu->addAction(pModelColor);
    pModelMenu->addAction(pModelMaterial);
    pModelMenu->addAction(pModelNormals);
    connect(pModelMenu, SIGNAL(aboutToShow()), this, SLOT(modelMenuATS()));

    pPrefMenu->addAction(pToggleSirus);

    pColorMenu = new QMenu(tr("&Color"));
    pPrefMenu->addMenu(pColorMenu);
    pColorMenu->setTearOffEnabled(true);
    pColorMenu->addAction(pColToolPath);
    pColorMenu->addAction(pColFeedTrail);
    pColorMenu->addAction(pColRapidTrail);
    pColorMenu->addAction(pColG02Trail);
    pColorMenu->addAction(pColG03Trail);

    pGridMenu = new QMenu(tr("&Grid"));
    pPrefMenu->addMenu(pGridMenu);
    pGridMenu->setTearOffEnabled(true);
    pGridMenu->addAction(pGridSettings);
    pGridMenu->addAction(pColGrid);
    pGridMenu->addAction(pToggleGrid);
    connect(pGridMenu, SIGNAL(aboutToShow()), this, SLOT(gridMenuATS()));

    pPrefMenu->addSeparator();
    pPrefMenu->addAction(pToggleCircInt);
    pPrefMenu->addAction(pTransform);

    //analysis
    pAnalysisMenu = menuBar()->addMenu(tr("&Analysis"));
    pAnalysisMenu->setTearOffEnabled(true);
    pAnalysisMenu->addAction(analysisPPInter);
    pAnalysisMenu->addSeparator();
    pAnalysisMenu->addAction(analysisRoughStock);
    pAnalysisMenu->addAction(analysisWYSIWYC);

    //utilities
    pUtilMenu = menuBar()->addMenu(tr("&Utilities"));
    //pUtilMenu->setCheckable(true);
    pUtilMenu->setTearOffEnabled(true);
    pUtilMenu->addAction(pSearchBlock);
    pUtilMenu->addAction(pPickBlock);
    pUtilMenu->addSeparator();
    pUtilMenu->addAction(pMeasDist);
    pUtilMenu->addAction(pMeasAng);
    pUtilMenu->addSeparator();
    pUtilMenu->addAction(pSimulRep);

    ///////////////////////////////////////////////////////////////////
    // menuBar entry windowMenu
    pWindowMenu = menuBar()->addMenu(tr("&Window"));
    pWindowMenu->setTearOffEnabled(true);
    //pWindowMenu->setCheckable(true);
    connect(pWindowMenu, SIGNAL(aboutToShow()), this, SLOT(windowMenuAboutToShow()));

    ///////////////////////////////////////////////////////////////////
    // menuBar entry helpMenu
    pHelpMenu = menuBar()->addMenu(tr("&Help"));
    pHelpMenu->setTearOffEnabled(true);
    pHelpMenu->addAction(helpAboutApp);
    pHelpMenu->addSeparator();
    //pHelpMenu->insertItem(tr("What's &This"), this, SLOT(whatsThis()), SHIFT+Key_F1);
}

void VirmacMainWin::initToolBar()
{
    ///////////////////////////////////////////////////////////////////
    // TOOLBAR
    fileToolbar = addToolBar("File operations");
    fileNew->setWhatsThis("Creates a new document");
    fileToolbar->addAction(fileNew);

    //fileOpen->addTo(fileToolbar);
    fileReadGCode->setWhatsThis("Read the G Code File");
    fileToolbar->addAction(fileReadGCode);

    fileReadStl->setWhatsThis("Read StL  File");
    fileToolbar->addAction(fileReadStl);
    fileToolbar->addSeparator();


    viewBar = addToolBar(" View Tool Bar");
    addToolBar(Qt::LeftToolBarArea, viewBar);
    viewBar->addAction(viewTop);
    viewBar->addAction(viewBottom);
    viewBar->addAction(viewFront);
    viewBar->addAction(viewBack);
    viewBar->addAction(viewLeft);
    viewBar->addAction(viewRight);
    viewBar->addAction(viewAxo);
    viewBar->addAction(viewMultiFour);
    viewBar->addSeparator();
    viewBar->addAction(viewProjection);
    viewBar->addSeparator();
    viewBar->addAction(viewFitall);
    viewBar->addAction(viewZoomwin);
    viewBar->addAction(viewReset);
    viewBar->addAction(viewAntial);
    viewBar->addAction(viewSnapshot);

    animBar = addToolBar(" Anim Tool Bar");
    addToolBar(Qt::BottomToolBarArea, animBar);

    //animation buttons
    pPlayButton = new QToolButton(this);
    pPlayButton->setIcon(QIcon(":/images/play.png"));
    pPlayButton->setText("Play");
    pPlayButton->setStatusTip("Play The Simulation");
    pPlayButton->setIconSize(QSize(64, 64));
    connect(pPlayButton, SIGNAL(clicked()), this, SLOT(slotPlay()));
    animBar->insertWidget(Q_NULLPTR, pPlayButton);

    pPlayStepButton = new QToolButton(animBar);
    pPlayStepButton->setIcon(QIcon(":/images/playstep.png"));
    pPlayStepButton->setText("Step");
    pPlayStepButton->setStatusTip("Play The Simulation Step By Step");
    pPlayStepButton->setIconSize(QSize(64, 64));
    connect(pPlayStepButton, SIGNAL(clicked()), this, SLOT(slotPlayStep()));
    animBar->insertWidget(Q_NULLPTR, pPlayStepButton);

    pPickPlayButton = new QToolButton(animBar);
    pPickPlayButton->setIcon(QIcon(":/images/pickplay.png"));
    pPickPlayButton->setText("Pick And Play");
    pPickPlayButton->setStatusTip("Play The Simulation From Picked Block");
    pPickPlayButton->setIconSize(QSize(64, 64));
    connect(pPickPlayButton, SIGNAL(clicked()), this, SLOT(slotPickPlay()));
    animBar->insertWidget(Q_NULLPTR, pPickPlayButton);

    pRewindButton = new QToolButton(animBar);
    pRewindButton->setIcon(QIcon(":/images/rewind.png"));
    pRewindButton->setText("Rewind");
    pRewindButton->setStatusTip("Rewind The Simulation");
    pRewindButton->setIconSize(QSize(64, 64));
    connect(pRewindButton, SIGNAL(clicked()), this, SLOT(slotRewind()));
    animBar->insertWidget(Q_NULLPTR, pRewindButton);

    pPauseButton = new QToolButton(animBar);
    pPauseButton->setIcon(QIcon(":/images/pause.png"));
    pPauseButton->setText("Pause");
    pPauseButton->setStatusTip("Pause The Simulation");
    pPauseButton->setIconSize(QSize(64, 64));
    connect(pPauseButton, SIGNAL(clicked()), this, SLOT(slotPause()));
    animBar->insertWidget(Q_NULLPTR, pPauseButton);

    pStopButton = new QToolButton(animBar);
    pStopButton->setIcon(QIcon(":/images/stop.png"));
    pStopButton->setText("Stop");
    pStopButton->setStatusTip("Stop The Simulation");
    pStopButton->setIconSize(QSize(64, 64));
    connect(pStopButton, SIGNAL(clicked()), this, SLOT(slotStop()));
    animBar->insertWidget(Q_NULLPTR, pStopButton);

    //Slider
    animBar->addSeparator();
    pSlider = new QSlider(Qt::Horizontal, animBar);
    pSlider->setRange(1, 100);
    pSlider->setTickInterval(10);
    pSlider->setValue(10);
    pSlider->setMaximumWidth(100);
    pSlider->setTickPosition(QSlider::TicksAbove);
    connect(pSlider, SIGNAL(valueChanged(int)), this, SLOT(slotPointsPerFrame(int)));
    animBar->insertWidget(Q_NULLPTR, pSlider);

    //Points Per Frame
    animBar->addSeparator();
    pPointsPerFrame = new QLCDNumber(3, animBar);
    pPointsPerFrame->setSegmentStyle(QLCDNumber::Filled);
    pPointsPerFrame->setFrameShape(QFrame::WinPanel);
    pPointsPerFrame->setFrameShadow(QFrame::Raised);
    pPointsPerFrame->display(10);
    connect(pSlider, SIGNAL(valueChanged(int)), pPointsPerFrame, SLOT(display(int)));
    animBar->insertWidget(Q_NULLPTR, pPointsPerFrame);

    ppfLabel = new QLabel(" Points Per Frame", animBar);
    animBar->insertWidget(Q_NULLPTR, ppfLabel);

    //G Code Blocks
    animBar->addSeparator();
    blockStr.sprintf("N%d G%.2d X%0.3f Y%0.3f Z%0.3f A%0.3f B%0.3f C%0.3f", 1, 2, 100., 100., 100., 10., 10. ,90.);
    blockLabel = new QLabel(blockStr);
    blockLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    blockLabel->setFrameShape(QFrame::NoFrame);
    blockLabel->setFrameShadow(QFrame::Plain);
    //animBar->setStretchableWidget(blockLabel);
    animBar->insertWidget(Q_NULLPTR, blockLabel);

    utilBar = new QToolBar(" Anim Tool Bar", this);
    //  utilBar->setPaletteBackgroundColor(QColor(190,190,190));

    utilBar->addAction(fileWriteGCode);
    utilBar->addAction(pPickBlock);
    utilBar->addAction(pSearchBlock);
    utilBar->addAction(editTrimBefore);
    utilBar->addAction(editTrimAfter);
    utilBar->addAction(pMeasDist);
    utilBar->addAction(pMeasAng);

    addToolBar(Qt::RightToolBarArea, utilBar);


    //prompt bar
    promWinFrame = new QDockWidget("Prompt Bar", this);
    promWinFrame->setAllowedAreas(Qt::BottomDockWidgetArea);
    promBox = new QListWidget(promWinFrame);
    promWinFrame->setWidget(promBox);

    mesgWinFrame = new QDockWidget("Message Bar", this);
    mesgWinFrame->setAllowedAreas(Qt::BottomDockWidgetArea);
    mesgBox = new QListWidget(mesgWinFrame);
    mesgWinFrame->setWidget(mesgBox);

    int dockHeight = 250;
    promBox->resize(promBox->width(), dockHeight);
    mesgBox->resize(mesgBox->width(), dockHeight);

    addDockWidget(Qt::BottomDockWidgetArea, promWinFrame);
    addDockWidget(Qt::BottomDockWidgetArea, mesgWinFrame);
    pViewMenu->addAction(promWinFrame->toggleViewAction());
    pViewMenu->addAction(mesgWinFrame->toggleViewAction());

}

void VirmacMainWin::initStatusBar()
{
    ///////////////////////////////////////////////////////////////////
    //STATUSBAR
    statusBar()->showMessage(tr("Ready."));
}


void VirmacMainWin::initView()
{
    ////////////////////////////////////////////////////////////////////
    // set the main widget here
    pWorkspace = new QMdiArea(this);

    //pWorkspace->setViewMode(QMdiArea::TabbedView);
    pWorkspace->setBackground(QBrush(QPixmap(":/images/granite.png")));
    setCentralWidget(pWorkspace);
}


void VirmacMainWin::createClient(VirmacDocument* doc)
{
    QPixmap appIcon = QPixmap(":/images/appicontr.png");
    VirmacViewer* w = new VirmacViewer(doc, this, Qt::SubWindow);
    w->setWindowIcon(appIcon);
    w->installEventFilter(this);
    doc->addView(w);
    pWorkspace->addSubWindow(w);
    if ( pWorkspace->subWindowList().count() == 1 ) // show the very first window in maximized mode
    {
        w->showMaximized();
    }
    else
    {
        w->showMaximized();
        pWorkspace->tileSubWindows();
    }

}

void VirmacMainWin::openDocumentFile(const QString& file)
{
    statusBar()->showMessage(tr("Opening file..."));
    VirmacDocument* doc;
    // check, if document already open. If yes, set the focus to the first view
    for(int i = 0; i< pDocList->size(); i++)
    {
        doc = pDocList->at(i);
        if(doc->pathName() == file)
        {
            VirmacViewer* view = doc->firstView();
            view->setFocus();
            return;
        }
    }
    doc = new VirmacDocument();
    pDocList->append(doc);
    doc->newDocument();
    // Creates an untitled window if file is 0
    if(file.isEmpty())
    {
        untitledCount+=1;
        QString fileName=QString(tr("Untitled%1")).arg(untitledCount);
        doc->setPathName(fileName);
        doc->setTitle(fileName);
    }
    // Open the file
    else
    {
        if(!doc->openDocument(file))
        {
            QMessageBox::critical(this, tr("Error !"),tr("Could not open document !"));
            delete doc;
            return;
        }
    }
    // create the window
    createClient(doc);

    statusBar()->showMessage(tr("Ready."));
}

bool VirmacMainWin::queryExit()
{
    int exit=QMessageBox::question(this, tr("Quit..."),
                                   tr("Do your really want to quit?"),
                                   QMessageBox::Yes, QMessageBox::No);

    return (exit==QMessageBox::Yes);
}

bool VirmacMainWin::eventFilter(QObject* object, QEvent* event)
{
    if((event->type() == QEvent::Close) && (static_cast<VirmacMainWin*>(object) != this))
    {
        QCloseEvent* e= static_cast<QCloseEvent*>(event);
        VirmacViewer* pView= static_cast<VirmacViewer*>(object);
        VirmacDocument* pDoc=pView->getDocument();
        if(pDoc->canCloseFrame(pView))
        {
            pDoc->removeView(pView);
            if(!pDoc->firstView())
                pDocList->removeOne(pDoc);

            e->accept();
        }
        else
            e->ignore();
    }
    return QWidget::eventFilter( object, event );    // standard event processing
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////


void VirmacMainWin::slotFileNew()
{
    statusBar()->showMessage(tr("Creating new file..."));

    openDocumentFile("");

    statusBar()->showMessage(tr("Ready."));
}

void VirmacMainWin::slotFileOpen()
{
    statusBar()->showMessage(tr("Opening file..."));

    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        openDocumentFile(fileName);
    }
    statusBar()->showMessage(tr("Ready."));
}


void VirmacMainWin::slotFileReadGCode()
{
    VirmacViewer* view = getActiveView();
    if(!view)
        return;
    view->killTimer(timerID);
    VirmacDocument* doc = static_cast<VirmacDocument*>(view->getDocument());
    if(!doc)
        return;
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            "Read G Code File",
                                            QApplication::applicationDirPath(),
                                            "All Files (*.*);;G Code files (*.cnc *.iso *.nc)");
    if(doc->readGCode(fileName))
    {
        setMessage(tr("Loaded G Code File ") + fileName + tr(" For Simulation"));
        setPrompt(tr("Press Play To Start Simulation"));
        view->setWindowTitle(fileName);
        slotToolLibrary();
    }
}

void VirmacMainWin::slotFileWriteGCode()
{

}

void VirmacMainWin::slotFileReadStL()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            QString fileName;
            fileName = QFileDialog::getOpenFileName(this,
                                                    "Read StL File",
                                                    QApplication::applicationDirPath(),
                                                    "All Files (*.*);;StL files (*.stl *.STL)");
            doc->readStLFile(fileName);
        }
    }

}

void VirmacMainWin::slotFileClose()
{
    statusBar()->showMessage(tr("Closing file..."));

    VirmacViewer* m = getActiveView();
    if( m )
    {
        VirmacDocument* doc=m->getDocument();
        doc->closeDocument();
    }

    statusBar()->showMessage(tr("Ready."));
}

void VirmacMainWin::slotFileQuit()
{ 
    statusBar()->showMessage(tr("Exiting application..."));
    ///////////////////////////////////////////////////////////////////
    // exits the Application
    if(queryExit())
    {
        qApp->quit();
    }

    statusBar()->showMessage(tr("Ready."));
}

void VirmacMainWin::closeEvent( QCloseEvent* ce )
{
    int exit=QMessageBox::question(this, tr("Quit..."),
                                   tr("Do your really want to quit?"),
                                   QMessageBox::Yes, QMessageBox::No);
    if (exit==QMessageBox::Yes)
    {
        ce->accept();
        //qApp->quit();
    }
    else
    {
        ce->ignore();
    };
}

//#include "GCodeEditor.h"
void VirmacMainWin::slotEditGCode()
{
    VirmacViewer* view = getActiveView();
    if(view && !view->editorActive)
    {
        //GCodeEditor* e = new GCodeEditor(view, "Editor", Qt::WDestructiveClose);
        //e->loadGCode();
        //e->show();
        //view->editorActive = true;
    }
}

void VirmacMainWin::slotEditTrimBefore()
{
    VirmacViewer* view = getActiveView();
    if(view)
    {
        VirmacDocument* doc = view->getDocument();
        if(!doc->m_bGCodeLoaded)
            return;
        view->trimBefore = true;
        view->PickBlock();
    }
}

void VirmacMainWin::slotEditTrimAfter()
{
    VirmacViewer* view = getActiveView();
    if(view)
    {
        VirmacDocument* doc = view->getDocument();
        if(!doc->m_bGCodeLoaded)
            return;
        view->trimAfter = true;
        view->PickBlock();
    }
}

void VirmacMainWin::slotViewToolBar(bool toggle)
{
    statusBar()->showMessage(tr("Toggle toolbar..."));
    ///////////////////////////////////////////////////////////////////
    // turn Toolbar on or off
    if (toggle== false)
    {
        fileToolbar->hide();
    }
    else
    {
        fileToolbar->show();
    };

    statusBar()->showMessage(tr("Ready."));
}

void VirmacMainWin::slotViewStatusBar(bool toggle)
{
    statusBar()->showMessage(tr("Toggle statusbar..."));
    ///////////////////////////////////////////////////////////////////
    //turn Statusbar on or off

    if (toggle == false)
    {
        statusBar()->hide();
    }
    else
    {
        statusBar()->show();
    }

    statusBar()->showMessage(tr("Ready."));
}


void VirmacMainWin::slotWindowNewWindow()
{
    statusBar()->showMessage(tr("Opening new document view..."));

    VirmacViewer* m = getActiveView();
    if ( m ){
        VirmacDocument* doc = m->getDocument();
        createClient(doc);
    }

    statusBar()->showMessage(tr("Ready."));
}

#include <qdatetime.h>
#include "AboutDialog.h"

void VirmacMainWin::slotHelpAbout()
{
    QDateTime dt = QDateTime::currentDateTime();
    QDate d = dt.date();
    QString cYear = d.toString("yyyy");
    /*
    QMessageBox::about(this,tr("About..."),
        tr("Virmac\n Version " VERSION
        "\nCopyright  2000- " + cYear + " N. Sharjith"));
        */
    AboutDialog ab;
    ab.exec();
}

void VirmacMainWin::slotStatusHelpMsg(const QString &text)
{
    ///////////////////////////////////////////////////////////////////
    // change status message of whole statusbar temporary (text, msec)
    statusBar()->showMessage(text, 2000);
}

void VirmacMainWin::windowMenuAboutToShow()
{
    pWindowMenu->clear();
    pWindowMenu->setTearOffEnabled(true);
    pWindowMenu->addAction(windowNewWindow);
    pWindowMenu->addAction(windowCascade);
    pWindowMenu->addAction(windowTile);

    if ( pWorkspace->subWindowList().isEmpty() )
    {
        windowAction->setEnabled(false);
    }
    else
    {
        windowAction->setEnabled(true);
    }

    pWindowMenu->addSeparator();


    QSignalMapper* windowActionSignalMapper = new QSignalMapper (this);
    QList<QMdiSubWindow*> windows = pWorkspace->subWindowList();
    for ( int i = 0; i < int(windows.count()); ++i )
    {
        QAction* windowAction = pWindowMenu->addAction(QString("&%1 ").arg(i+1)+windows.at(i)->windowTitle());

        connect(windowAction, SIGNAL(triggered()), windowActionSignalMapper, SLOT(map()));

        windowActionSignalMapper->setMapping (windowAction, i) ;

        connect (windowActionSignalMapper, SIGNAL(mapped(int)), this,
                           SLOT(windowMenuActivated(int))) ;

        windowAction->setChecked(pWorkspace->activeSubWindow() == windows.at(i) );
    }
}

void VirmacMainWin::windowMenuActivated( int id )
{
    QWidget* w = pWorkspace->subWindowList().at( id );
    if ( w )
        w->setFocus();
}

//viewer slots

void VirmacMainWin::slotTopView()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        view->TopView();
        view->setCursor(QCursor(QPixmap(":/images/crosscursor.png")));
    }
}

void VirmacMainWin::slotBottomView()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        view->BottomView();
        view->setCursor(QCursor(QPixmap(":/images/crosscursor.png")));
    }
}

void VirmacMainWin::slotFrontView()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        view->FrontView();
        view->setCursor(QCursor(QPixmap(":/images/crosscursor.png")));
    }
}

void VirmacMainWin::slotBackView()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        view->BackView();
        view->setCursor(QCursor(QPixmap(":/images/crosscursor.png")));
    }
}

void VirmacMainWin::slotLeftView()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        view->LeftView();
        view->setCursor(QCursor(QPixmap(":/images/crosscursor.png")));
    }
}

void VirmacMainWin::slotRightView()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        view->RightView();
        view->setCursor(QCursor(QPixmap(":/images/crosscursor.png")));
    }
}

void VirmacMainWin::slotAxoView()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        view->AxonView();
        view->setCursor(Qt::ArrowCursor);
    }
}

void VirmacMainWin::slotMultiFour()
{	
    bSplit = !bSplit;
    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        if(bSplit)
            view->MultiView(true);
        else
            view->MultiView(false);
    }
}

void VirmacMainWin::slotProjection()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        GLProjectionType pt = view->GetView()->GetProjectionType();
        if(pt  == GLPERSPECTIVE)
        {
            view->GetView()->SetProjectionType(GLORTHOGRAPHIC);
            viewProjection->setText("Perspective");
            QPixmap perspIcon(":/images/persp.png");
            viewProjection->setIcon(perspIcon);
        }
        else
        {
            view->GetView()->SetProjectionType(GLPERSPECTIVE);
            viewProjection->setText("Orthographic");
            QPixmap orthoIcon(":/images/ortho.png");
            viewProjection->setIcon(orthoIcon);
        }
    }
}

void VirmacMainWin::slotFitall()
{

    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        view->GetView()->FitAll();
    }
}

void VirmacMainWin::slotZoomwin()
{   
    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        view->winZoom = true;
        view->setCursor(QCursor(QPixmap(":/images/zoomwincursor.png")));
        setPrompt(tr("Press And Drag MB_1 To Create Zoom Window"));
    }
}

void VirmacMainWin::slotReset()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        view->GetView()->ResetView();
        view->viewLabel.sprintf("Axonometric");
    }
}

void VirmacMainWin::slotAntial()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        view->setFocus();
        view->antialiased = !view->antialiased;
        if(!view->antialiased)
            view->GetView()->SetAntiAliasing(false);
        else
            view->GetView()->SetAntiAliasing(true);
    }
}

void VirmacMainWin::slotSnapshot()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        QString fn = QFileDialog::getSaveFileName();
        if ( !fn.isEmpty() )
        {
            view->GetView()->SnapShot(fn);
        }
    }
}

#include "BackgroundColor.h"
void VirmacMainWin::slotBgColor()
{
    VirmacViewer* viewer = getActiveView();
    if( viewer )
    {

        BackgroundColor dlg(viewer);
        if(dlg.exec() == QDialog::Accepted)
        {
            VirmacGLView* view = viewer->GetView();
            view->SetBackgroundTopColor(dlg.getTopColor());
            view->SetBackgroundBottomColor(dlg.getBottomColor());
            view->SetBackgroundGradient(dlg.hasGradient());
            viewer->updateGL();
        }
    }
}

//animation
void VirmacMainWin::slotPlay()
{
    VirmacViewer* view = getActiveView();
    if(view)
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->m_bGCodeLoaded)
            {
                QMessageBox::critical(this, "Virmac Error", "No G Code File Loaded For Simulation",
                                      QMessageBox::Ok, 0, 0);
                return;
            }
            if(!view->animActive)
            {
                timerID = view->startTimer(1);
                doc->HidePath(true);
                view->animActive = true;
            }
        }
    }
}

void VirmacMainWin::slotPickPlay()
{
    VirmacViewer* view = getActiveView();
    if(view)
    {
        VirmacDocument* doc = view->getDocument();
        if(!doc->m_bGCodeLoaded)
        {
            QMessageBox::critical(this, "Virmac Error", "No G Code File Loaded For Simulation",
                                  QMessageBox::Ok, 0, 0);
            return;
        }
        if(view->animActive)
        {
            view->killTimer(timerID);
            view->animActive = false;
            doc->HidePath(false);
        }
        view->pickMode = true;
        view->pickNplay = true;
        view->pickNplayActive = true;
        view->PickBlock();
    }
}
void VirmacMainWin::slotPlayStep()
{
    VirmacViewer* view = getActiveView();
    if(view)
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->m_bGCodeLoaded)
            {
                QMessageBox::critical(this, "Virmac Error", "No G Code File Loaded For Simulation",
                                      QMessageBox::Ok, 0, 0);
                return;
            }
            view->killTimer(timerID);
            view->animActive = false;
            doc->HidePath(true);
            NCBlock aBloc;
            if(doc->myPathIter.More())
            {
                aBloc = doc->myPathIter.Current();
                doc->myPathIter.Next();
                Point3D P(aBloc.X, aBloc.Y, aBloc.Z);
                doc->myCutter->MoveTo(P);
                doc->myCutter->Rotate(aBloc.A, aBloc.B, aBloc.C);
                doc->myTrail->AddBlock(aBloc);
                doc->blocString.sprintf("N%uld  G%.2d  X%0.3f  Y%0.3f  Z%0.3f  A%0.3f  B%0.3f  C%0.3f",
                                        (unsigned)aBloc.N,(int)aBloc.G,aBloc.X,aBloc.Y,aBloc.Z,aBloc.A,aBloc.B, aBloc.C);
                view->GetView()->Refresh();
            }
        }
    }
}
void VirmacMainWin::slotRewind()
{	
    VirmacViewer* view = getActiveView();
    if(view)
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->m_bGCodeLoaded)
            {
                QMessageBox::critical(this, "Virmac Error", "Nothing To Rewind!",
                                      QMessageBox::Ok | QMessageBox::Default, 0, 0);
                return;
            }

            int res = QMessageBox::question( this, "Virmac Confirmation",
                                             "Do You Really Want To Rewind The Simulation?",
                                             QMessageBox::Yes | QMessageBox::Default,
                                             QMessageBox::No  | QMessageBox::Escape, 0);
            if(res == QMessageBox::No)
            {
                return;
            }

            view->killTimer(timerID);
            view->animActive = false;
            doc->myCutter->MoveTo(Point3D(0,0,0));
            doc->myCutter->Rotate(0, 0, 0);
            doc->myTrail->Nullify();
            doc->HidePath(false);
            doc->myPathIter.Init();
            progBar->setValue(0);
            doc->SetCurrentBlock(0);
            if(view->pickNplayActive)
                view->pickNplayActive = false;
            view->GetView()->Refresh();
        }
    }
}

void VirmacMainWin::slotPause()
{
    VirmacViewer* view = getActiveView();
    if(view)
    {
        view->killTimer(timerID);
        view->animActive = false;
    }
}
void VirmacMainWin::slotStop()
{
    slotPause();
    slotRewind();
    setMessage(tr("Simulation Stopped By User!"));
}

void VirmacMainWin::slotDeleteSirus()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->m_bGCodeLoaded)
                return;
            doc->myPath->Nullify();
            doc->myTrail->Nullify();
            doc->m_bGCodeLoaded = false;
            doc->GetDisplayContext()->RefreshVolume();
        }
    }
}

void VirmacMainWin::slotDeleteModel()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->m_bModelLoaded)
                return;
            doc->myStLObj->Nullify();
            doc->m_bModelLoaded = false;
            doc->GetDisplayContext()->RefreshVolume();
        }
    }
}

#include "SimulSettings.h"
void VirmacMainWin::slotSimulSettings()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        SimulSettings *dlg = new SimulSettings(view);
        int res = dlg->exec();
        if(res == QDialog::Accepted)
        {
            VirmacDocument* pDoc = view->getDocument();
            if(pDoc)
            {
                //pDoc->myPath->EnableSyntaxChecking(dlg->checkBox1->isChecked());
                //pDoc->StopAtIntersections(dlg->checkBox2->isChecked())
                switch(dlg->resolution())
                {
                case 0:
                    pDoc->myCutter->SetResolution(MODEL_LOW);
                    break;
                case 1:
                    pDoc->myCutter->SetResolution(MODEL_MEDIUM);
                    break;
                case 2:
                    pDoc->myCutter->SetResolution(MODEL_HIGH);
                    break;
                case 3:
                    pDoc->myCutter->SetResolution(MODEL_VERYHIGH);
                    break;
                default:
                    break;
                }
                pDoc->myPointsPerFrame = dlg->pointsPerFrame();
                pSlider->setValue(pDoc->myPointsPerFrame);
            }
        }
        delete dlg;
    }
}

#include "ToolLibrary.h"
void VirmacMainWin::slotToolLibrary()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        ToolLibrary *lib = new ToolLibrary(view);
        lib->exec();
    }
}

#include "RotAxisSetting.h"
void VirmacMainWin::slotRotaryAxis()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc=view->getDocument();
        if(doc)
        {
            RotAxisSetting *dlg = new RotAxisSetting(this);
            int res = dlg->exec();
            if(res == QDialog::Accepted)
            {
                if(!dlg->isAnglesFromFile())
                {
                    doc->myCutter->Rotate(dlg->angleA(), dlg->angleB(), dlg->angleC());
                }
            }
        }
    }
}

#include "BlockEntry.h"
void VirmacMainWin::slotStartBlock()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc=view->getDocument();
        if(doc)
        {
            if(!doc->m_bGCodeLoaded)
            {
                QMessageBox::critical(this, "Error", "No G Code File Loaded", QMessageBox::Ok, 0, 0);
                return;
            }
            BlockEntry *dlg = new BlockEntry(this);
            int res = dlg->exec();
            if(res == QDialog::Accepted)
            {
                for(doc->myPathIter.Init(); doc->myPathIter.More(); doc->myPathIter.Next())
                {
                    if(doc->myPathIter.Current().N == (unsigned) dlg->blockNumber())
                        break;
                }
                QString str; str.sprintf("Start Block Number Is %d", dlg->blockNumber());
                setMessage(str);
            }
        }
    }
}

void VirmacMainWin::slotPointsPerFrame(int value)
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc=view->getDocument();
        if(doc)
        {
            doc->myPointsPerFrame = value;
            QString str;
            str.sprintf("Set Points Per Frame %d", value);
            setMessage(str);
        }
    }
}


//preferences
void VirmacMainWin::toolMenuATS()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc=view->getDocument();
        if(!doc->myCutter)
            return;
        if(doc->myCutter->GetDisplayMode() == GLWIREFRAME)
        {
            pToolDisplayMode->setText("Solid");
        }
        else
        {
            pToolDisplayMode->setText("Transparent");
        }
        if(doc->myCutter->IsHidden())
        {
            pToolHide->setText("Show");
        }
        else
        {
            pToolHide->setText("Hide");
        }
    }
}
void VirmacMainWin::slotToolDisplayMode()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc=view->getDocument();
        if(!doc->myCutter)
            return;
        if(doc->myCutter->GetDisplayMode() == GLWIREFRAME)
        {
            doc->myCutter->SetDisplayMode(GLSHADED);
            pToolDisplayMode->setText("Transparent");
        }
        else
        {
            doc->myCutter->SetDisplayMode(GLWIREFRAME);
            pToolDisplayMode->setText("Solid");
        }
    }
}

void VirmacMainWin::slotToolHide()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc=view->getDocument();
        if(!doc->myCutter)
            return;
        if(doc->myCutter->IsHidden())
        {
            doc->HideTool(false);
            pToolHide->setText(tr("Hide"));
        }
        else
        {
            doc->HideTool(true);
            pToolHide->setText(tr("Show"));
        }
    }
}

void VirmacMainWin::slotToolColor()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myCutter)
                return;
            QColor col(0,0,0);
            col = QColorDialog::getColor ( col, this, 0 );
            if(!col.isValid())
                return;
            doc->myCutter->SetColor(col.red(), col.green(), col.blue());
        }
    }
}

void VirmacMainWin::trailMenuATS()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myTrail)
                return;
            if(doc->myTrail->IsHidden())
            {
                pToggleTrail->setText("Show");
            }
            else
            {
                pToggleTrail->setText("Hide");
            }
        }
    }
}

void VirmacMainWin::slotToggleTrail()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myTrail)
                return;
            if(doc->myTrail->IsHidden())
            {
                doc->myTrail->MakeHidden(false);
                pToggleTrail->setText("Off");
            }
            else
            {
                doc->myTrail->MakeHidden(true);
                pToggleTrail->setText("On");
            }
            view->GetView()->Refresh();
        }
    }
}

void VirmacMainWin::modelMenuATS()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myStLObj)
                return;
            if(doc->myStLObj->GetDisplayMode() == GLWIREFRAME)
            {
                pModelHide->setText("Shaded");
            }
            else
            {
                pModelHide->setText("Wireframe");
            }
            if(doc->myStLObj->IsHidden())
            {
                pModelHide->setText("Show");
            }
            else
            {
                pModelHide->setText("Hide");
            }
        }
    }
}

void VirmacMainWin::slotModelDisplayMode()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc=view->getDocument();
        if(!doc->myStLObj)
            return;
        if(doc && doc->myStLObj->GetDisplayMode() == GLWIREFRAME)
        {
            doc->myStLObj->SetDisplayMode(GLSHADED);
            pModelDisplayMode->setText("Wireframe");
        }
        else
        {
            doc->myStLObj->SetDisplayMode(GLWIREFRAME);
            pModelDisplayMode->setText("Shaded");
        }
    }
}

void VirmacMainWin::slotModelHide()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc=view->getDocument();
        if(!doc->myStLObj)
            return;
        if(doc && doc->myStLObj->IsHidden())
        {
            doc->HideModel(false);
            pModelHide->setText(tr("Hide"));
        }
        else
        {
            doc->HideModel(true);
            pModelHide->setText(tr("Show"));
        }
    }
}

void VirmacMainWin::slotModelColor()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myStLObj)
                return;
            QColor col(0,0,0);
            col = QColorDialog::getColor ( col, this, 0 );
            if(!col.isValid())
                return;
            doc->myStLObj->SetColor(col.red(), col.green(), col.blue());
        }
    }
}

#include "MatlEditor.h"
void VirmacMainWin::slotModelMaterial()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myStLObj)
                return;
            MatlEditor e;
            if(e.exec() == QDialog::Rejected)
                return;
            doc->myStLObj->SetMaterial(e.material());
        }
    }
}


void VirmacMainWin::slotModelNormals()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myStLObj)
                return;
            doc->myStLObj->ShowNormals(!doc->myStLObj->IsNormalShown());
        }
    }
}

void VirmacMainWin::slotToggleSirus()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myPath)
                return;
            if(doc->myPath->IsHidden())
            {
                doc->myPath->MakeHidden(false);
                pToggleSirus->setText("Hide Sirus");
            }
            else
            {
                doc->myPath->MakeHidden(true);
                pToggleSirus->setText("Show Sirus");
            }
            view->GetView()->Refresh();
        }
    }
}

void VirmacMainWin::slotColToolPath()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myPath)
                return;
            QColor col(0,0,0);
            col = QColorDialog::getColor ( col, this, 0 );
            if(!col.isValid())
                return;
            doc->myPath->SetColor(static_cast<GLubyte>(col.red()),
                                  static_cast<GLubyte>(col.green()),
                                  static_cast<GLubyte>(col.blue()));
        }
    }

}

void VirmacMainWin::slotColFeedTrail()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myTrail)
                return;
            QColor col(0,0,0);
            col = QColorDialog::getColor ( col, this, 0 );
            if(!col.isValid())
                return;
            doc->myTrail->SetG01Color(static_cast<GLubyte>(col.red()),
                                      static_cast<GLubyte>(col.green()),
                                      static_cast<GLubyte>(col.blue()));
        }
    }
}

void VirmacMainWin::slotColRapidTrail()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myTrail)
                return;
            QColor col(0,0,0);
            col = QColorDialog::getColor ( col, this, 0 );
            if(!col.isValid())
                return;
            doc->myTrail->SetG00Color(static_cast<GLubyte>(col.red()),
                                      static_cast<GLubyte>(col.green()),
                                      static_cast<GLubyte>(col.blue()));
        }
    }
}

void VirmacMainWin::slotColG02Trail()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myTrail)
                return;
            QColor col(0,0,0);
            col = QColorDialog::getColor ( col, this, 0 );
            if(!col.isValid())
                return;
            doc->myTrail->SetG02Color(static_cast<GLubyte>(col.red()),
                                      static_cast<GLubyte>(col.green()),
                                      static_cast<GLubyte>(col.blue()));
        }
    }
}

void VirmacMainWin::slotColG03Trail()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(!doc->myTrail)
                return;
            QColor col(0,0,0);
            col = QColorDialog::getColor ( col, this, 0 );
            if(!col.isValid())
                return;
            doc->myTrail->SetG03Color(static_cast<GLubyte>(col.red()),
                                      static_cast<GLubyte>(col.green()),
                                      static_cast<GLubyte>(col.blue()));
        }
    }
}

void VirmacMainWin::gridMenuATS()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {

        if(view->GetView()->IsGridOn())
        {
            pToggleGrid->setText("Off");
        }
        else
        {
            pToggleGrid->setText("On");
        }
    }
}

#include "GridSettings.h"
void VirmacMainWin::slotGridSettings()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        GridSettings dlg(this);
        if(dlg.exec() ==  QDialog::Accepted)
        {
            VGLGrid* pGrid = view->GetView()->GetGrid();
            view->GetView()->SetGridPara(pGrid->GetPlane(), dlg.gridSize(), dlg.gridStep());
        }
    }
}

void VirmacMainWin::slotColGrid()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        QColor col(0,0,0);
        col = QColorDialog::getColor ( col, this, 0 );
        if(!col.isValid())
            return;
        view->GetView()->SetGridColor(static_cast<GLubyte>(col.red()),
                                      static_cast<GLubyte>(col.green()),
                                      static_cast<GLubyte>(col.blue()));
    }
}

void VirmacMainWin::slotToggleGrid()
{
    VirmacViewer* view = getActiveView();
    if(view)
    {
        if(view->GetView()->IsGridOn())
        {
            view->GetView()->SetGridOn(false);
            pToggleGrid->setText(tr("On"));
        }
        else
        {
            view->GetView()->SetGridOn(true);
            pToggleGrid->setText(tr("Off"));
        }
    }
}

void VirmacMainWin::slotToggleCircInt()
{
    VirmacViewer* view = getActiveView();
    if(view)
    {
        VirmacDocument* doc = view->getDocument();
        if(doc)
        {
            if(doc->myPath)
            {
                bool b = doc->myPath->IsArcShown();
                if(b)
                {
                    doc->myPath->SetShowArc(false);
                    doc->myTrail->SetShowArc(false);
                    pToggleCircInt->setText(tr("Show Circular Inter"));
                }
                else
                {
                    doc->myPath->SetShowArc(true);
                    doc->myTrail->SetShowArc(true);
                    pToggleCircInt->setText(tr("Hide Circular Inter"));
                }
            }
        }
    }
}

#include "Transformations.h"
void VirmacMainWin::slotTransform()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        Transformations *dlg = new Transformations(this);
        int res = dlg->exec();
        VirmacDocument* doc=view->getDocument();
        if(doc)
        {
            if(!doc->myPath)
                return;
            if(res == QDialog::Accepted)
            {
                doc->DX = dlg->DX();
                doc->DY = dlg->DY();
                doc->DZ = dlg->DZ();
                doc->CX = dlg->CX();
                doc->CY = dlg->CY();
                doc->CZ = dlg->CZ();
                doc->RX = dlg->RX();
                doc->RY = dlg->RY();
                doc->RZ = dlg->RZ();
                doc->XP = dlg->XP();
                doc->YP = dlg->YP();
                doc->ZP = dlg->ZP();

                //toolpath translations
                doc->myPath->SetTranslation(doc->DX, doc->DY, doc->DZ);
                doc->myPath->SetRotation(doc->CX, doc->CY, doc->CZ, doc->RX, doc->RY, doc->RZ);
                doc->myPath->SetScale(doc->XP, doc->YP, doc->ZP);

                //tooltrail translations
                doc->myTrail->SetTranslation(doc->DX, doc->DY, doc->DZ);
                doc->myTrail->SetRotation(doc->CX, doc->CY, doc->CZ, doc->RX, doc->RY, doc->RZ);
                doc->myTrail->SetScale(doc->XP, doc->YP, doc->ZP);

                //tool translations
                //donot scale tool with number... only sign
                double scalex, scaley, scalez;
                scalex = (doc->XP >= 0) ? 1 : -1;
                scaley = (doc->YP >= 0) ? 1 : -1;
                scalez = (doc->ZP >= 0) ? 1 : -1;

                doc->myCutter->SetTranslation(doc->DX, doc->DY, doc->DZ);
                doc->myCutter->SetRotation(doc->CX, doc->CY, doc->CZ, doc->RX, doc->RY, doc->RZ);
                doc->myCutter->SetScale(scalex, scaley, scalez);
            }
        }
    }
}

//analysis
void VirmacMainWin::slotPPIntersection(bool flag)
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc=view->getDocument();
        if(doc)
        {
            doc->m_bCheckIntersection = flag;
        }
    }
}

void VirmacMainWin::slotRoughStock()
{
    QMessageBox::information(this, "Sorry", "Not Yet Implemented!", QMessageBox::Ok, 0, 0);
}

void VirmacMainWin::slotWYSIWYC()
{
    QMessageBox::information(this, "Sorry", "Not Yet Implemented!", QMessageBox::Ok, 0, 0);
}

//utilities
#include "BlockEntry.h"
void VirmacMainWin::slotSearchBlock()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc=view->getDocument();
        if(doc)
        {
            if(!doc->myPath)
                return;
            BlockEntry *dlg = new BlockEntry(this);
            NCBlock aBloc;
            QString str;
            int totCnt = doc->myPath->GetBlockCount();
            //fprintf(stderr, "Count %d\n", totCnt);
            if(dlg->exec() == QDialog::Accepted)
            {
                unsigned bNum = static_cast<unsigned>(dlg->blockNumber());
                int cnt = 1;
                for(doc->myPathIter.Init(); doc->myPathIter.More(); doc->myPathIter.Next())
                {
                    aBloc = doc->myPathIter.Current();
                    if(aBloc.N == bNum)
                    {
                        str.sprintf("N%uld  G%d  X%0.3f  Y%0.3f  Z%0.3f  A%0.3f  B%0.3f  C%0.3f\nSearch Next Occurance?",
                                    static_cast<unsigned>(aBloc.N), aBloc.G,
                                    aBloc.X,aBloc.Y,aBloc.Z,aBloc.A,aBloc.B,aBloc.C);
                        setMessage(str);
                        doc->ShowSelectedBloc(aBloc);
                        view->GetView()->Refresh();
                        if(QMessageBox::information(this, "NC Block Information", str, QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
                        {
                            break;
                        }
                    }
                    else if(totCnt == cnt)
                    {
                        str.sprintf("Bloc Not Found");
                        setMessage(str);
                        QMessageBox::information(this, "NC Block Information", str, QMessageBox::Ok);
                    }
                    ++cnt;
                }
                view->GetView()->Refresh();
                doc->myPathIter.Init();
            }
        }
    }
}

void VirmacMainWin::slotPickBlock()
{
    VirmacViewer* view = getActiveView();
    if( view )
    {
        VirmacDocument* doc = view->getDocument();
        if(!doc->myPath)
            return;
        view->PickBlock();
    }
}

void VirmacMainWin::slotMeasDist()
{
}

void VirmacMainWin::slotMeasAng()
{
}

#include "SimulReport.h"
#include "ListException.h"
void VirmacMainWin::slotSimulRep()
{
    VirmacViewer* view = getActiveView();
    VirmacDocument* pDoc = view->getDocument();
    if(!pDoc->m_bGCodeLoaded)
        return;
    QString fName, tData, pLength, cutTime,rapidRate;
    SimulReport dlg;
    NCBlock G1, G2;
    Point3D P1, P2;
    double plen = 0;
    double ctTime = 0;
    double len=0;
    //try
    //{
    for(pDoc->myPathIter.Init();  pDoc->myPathIter.More(); pDoc->myPathIter.Next())
    {
        G1 = pDoc->myPathIter.Current();
        pDoc->myPathIter.Next();
        G2 = pDoc->myPathIter.Current();
        P1.SetParam(G1.X,G1.Y,G1.Z);
        P2.SetParam(G2.X,G2.Y,G2.Z);
        plen+=P1.Distance(P2);
        len = P1.Distance(P2);
        if(len == 0.0||G2.F == 0.0)
            ctTime+=0;
        else
            ctTime+=(len/G2.F);
    }
    //}
    //catch(CListException ex)
    //{
    //qWarning("Exception Caught\n %s", ex.ErrorMessage());
    //return;
    //}
    if(ctTime != 0.0)
        ctTime /= static_cast<double>(60);

    fName = pDoc->title();

    tData.sprintf("Diameter:  \t%0.4g\nCorner Radius:  \t%0.4g\nLength:  \t%0.4g\n",pDoc->myCutter->GetBodyDia(),
                  pDoc->myCutter->GetBallRad(),pDoc->myCutter->GetShankLen());

    pLength.sprintf("%0.4g units",plen);

    cutTime.sprintf("%0.4g hours",ctTime);

    rapidRate.sprintf("%0.0g units/min", 10000.0/*pDoc->rapidRate*/);

    dlg.setFileName(fName);
    dlg.setToolDia(tData);
    dlg.setPathLength(pLength);
    dlg.setCuttingTime(cutTime);
    dlg.setRapidRate(rapidRate);
    dlg.exec();
}



void VirmacMainWin::setMessage(const QString& str)
{
    QString msg;
    int cnt = mesgBox->count();
    ++mesgCnt;
    msg.sprintf("MSG #%d ", mesgCnt);
    msg += str;
    mesgBox->addItem(new QListWidgetItem(msg));
    mesgBox->setCurrentRow(cnt);
    if(cnt > 100)
        mesgBox->takeItem(0);
}

void VirmacMainWin::setPrompt(const QString& str)
{
    QString prm;
    int cnt = promBox->count();
    ++promCnt;
    prm.sprintf("PRM #%d ", promCnt);
    prm += str;
    promBox->addItem(new QListWidgetItem(prm));
    promBox->setCurrentRow(cnt);
    if(cnt > 100)
        promBox->takeItem(0);
}

void VirmacMainWin::timerEvent(QTimerEvent* /*e*/)
{
    VirmacViewer* view = getActiveView();
    if(!view)
        return;
    VirmacDocument* doc = view->getDocument();
    if(!doc)
        return;
    doc->AnimFunction();
    blockLabel->setText(doc->blocString);
    view->GetView()->Refresh();
}

