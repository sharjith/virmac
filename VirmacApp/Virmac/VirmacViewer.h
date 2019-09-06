/***************************************************************************
  virmacview.h  -  description
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

#ifndef VIRMACVIEW_H
#define VIRMACVIEW_H

#include "VirmacMainWin.h"

// include files for Qt
#include <QtWidgets>
#include <QGL>
#include <QLabel>
#include <QHBoxLayout>
#include <QString>
#include <QDateTime>
#include <QPoint>
#include <QSplitter>

#include "VirmacGLView.h"

class VirmacDocument;
class VirmacGLView;

class VirmacViewer : public QGLWidget
{
    Q_OBJECT

	friend class VirmacDocument;

    public:
    VirmacViewer(VirmacDocument* pDoc, QWidget* parent, Qt::WindowFlags wflags);
    ~VirmacViewer();

    VirmacDocument *getDocument() const;

    void update(VirmacViewer* pSender);
    void print(QPrinter *pPrinter);

    protected:
    virtual void closeEvent(QCloseEvent*);

    VirmacDocument *doc;
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    private:
    void Popup();
    void DrawRectangle (const int  MinX  ,
	    const int  MinY  ,
	    const int  MaxX  ,
	    const int  MaxY  ,
	    const bool  Draw
	    );
    public:
    bool winZoom;
    bool dShaded;
    bool antialiased;
    bool gridOn;
    bool showArc;
    bool showPath;
    bool showTool;
    bool showTrail;
    bool showModel;
    bool showNormal;
    bool pickMode;
    bool pickNplay;
    bool pickNplayActive;
    bool trimAfter;
    bool trimBefore;
    bool multiViewActive;
    bool animActive;
    bool editorActive;

    QString viewLabel;
    QLabel *coordViewer;
    private:
    bool ldown;
    bool mdown;
    bool rdown;

    QPoint  lPoint;
    QPoint  mPoint;
    QPoint  rPoint;

    int     myXmin;
    int     myYmin;
    int     myXmax;
    int     myYmax;

    protected:
    void mousePressEvent( QMouseEvent *);
    void mouseReleaseEvent( QMouseEvent *);
    void mouseMoveEvent( QMouseEvent *);
    void wheelEvent( QWheelEvent *);
    void resizeEvent( QResizeEvent *);
    void timerEvent(QTimerEvent*);
    public:
    void TopView();
    void BottomView();
    void FrontView();
    void BackView();
    void RightView();
    void LeftView();
    void AxonView();
    void MultiView(bool doIt);
    void SetDisplayMode(const GLDisplayMode& aMode);
    GLDisplayMode GetDisplayMode() const { return myView->GetDisplayMode(); }
    VirmacGLView* GetView() const { return myView; }
    void ShowPickedBlockInfo(QPoint point);
    void PickBlock();
    void AddCircularEntry();
    void AddCircularExit();
    private:
    VirmacGLView* myView;

    private:
    int mouseX;
    int mouseY;

    QRubberBand* mRectBand;
};

#endif
