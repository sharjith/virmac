/***************************************************************************
  virmacview.cpp  -  description
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

// include files for Qt
#include <QPrinter>
#include <QPainter>

// application specific includes
#include "VirmacViewer.h"
#include "VirmacDocument.h"
#include "VirmacMainWin.h"

VirmacViewer::VirmacViewer(VirmacDocument* pDoc, QWidget *parent, Qt::WindowFlags wflags)
    : QGLWidget(parent, Q_NULLPTR, wflags)
{
    doc=pDoc;

    viewLabel.sprintf("Axonometric");//l = new QLabel("Axonometric", this, "VIEWS");

    myView = new VirmacGLView(this, doc->GetDisplayContext());

    ldown = mdown = rdown = false;
    winZoom = false;
    dShaded = false;
    antialiased = false;
    gridOn = false;
    showArc = false;
    showPath = true;
    showTool = true;
    showTrail = true;
    showModel = true;
    showNormal = false;
    pickMode = false;
    pickNplay = false;
    pickNplayActive = false;
    trimAfter = false;
    trimBefore = false;
    multiViewActive = false;
    animActive = false;
    editorActive = false;

    mRectBand = NULL;

    setMouseTracking(true);
}

VirmacViewer::~VirmacViewer()
{
    if(myView)
        delete myView;
}

VirmacDocument *VirmacViewer::getDocument() const
{
    return doc;
}

void VirmacViewer::update(VirmacViewer* pSender){
    if(pSender != this)
        repaint();
}

void VirmacViewer::print(QPrinter *pPrinter)
{
    if (pPrinter)
    {
        QPainter p;
        p.begin(pPrinter);

        ///////////////////////////////
        // TODO: add your printing code here
        ///////////////////////////////

        p.end();
    }
}

void VirmacViewer::closeEvent(QCloseEvent*)
{
    //QMessageBox::information(this, "Info", "Close");
}

void VirmacViewer::initializeGL()
{
    myView->InitGL();
}

void VirmacViewer::resizeGL(int w, int h)
{
    myView->ReSize(w, h);
}

void VirmacViewer::paintGL()
{
    myView->Draw();

    //View Label
    glDisable(GL_LIGHTING);
    glColor3ub(255, 255, 0);
    renderText(10, 20, viewLabel);
    //End Label

    //Dynamic Coord
    if(myView->IsPlanarView() && !pickMode && myView->GetProjectionType() == GLORTHOGRAPHIC)
    {
        VirmacMainWin *top = (VirmacMainWin*)topLevelWidget()->topLevelWidget();
        glColor3ub(255, 255, 0);
        renderText(mouseX, mouseY, top->cViewer->text());
    }
    //End Coord
}

void VirmacViewer::resizeEvent( QResizeEvent* /*e*/)
{
    QRect aRect = geometry();
    resizeGL(aRect.width(), aRect.height());
    update(NULL);
}

void VirmacViewer::mousePressEvent( QMouseEvent *e)
{
    if(e->button() & Qt::LeftButton)
    {
        // ask window to give us events even if outside the view
        if(!pickMode)
            grabMouse();

        getDocument()->EraseSelectedBloc();

        //  save the current mouse coordinate in min
        myXmin=e->x();  myYmin=e->y();
        myXmax=e->x();  myYmax=e->y();

        ldown = true;
        lPoint.setX(e->x());
        lPoint.setY(e->y());
        if(!(e->modifiers() & Qt::ShiftModifier) && !(e->modifiers() & Qt::ControlModifier) && !winZoom)
        {
            myView->Select(e->x(), e->y());

        }
        if ((e->modifiers() & Qt::ShiftModifier) && !(e->modifiers() & Qt::ControlModifier) && !winZoom)
        {
            myView->MultiSelect(e->x(), e->y());

        }
    }
    if(e->button() & Qt::MidButton)
    {
        mdown = true;
        mPoint.setX(e->x());
        mPoint.setY(e->y());

        /*if(!(e->modifiers() & Qt::ShiftModifier) && !(e->modifiers() & Qt::ControlModifier) && myView->GetViewType() != GLUNDEFINEDVIEW && myView->GetViewType() != GLAXONVIEW)
      {
      VirmacApp *top = (VirmacApp*)topLevelWidget()->topLevelWidget();
      QPainter paint( this );
      paint.setPen( Qt::yellow );
      paint.drawText( e->x()+10, e->y(), top->cViewer->text() );
      }*/

    }
    if(e->button() & Qt::RightButton)
    {
        rdown = true;
        rPoint.setX(e->x());
        rPoint.setY(e->y());
        if(!(e->modifiers() & Qt::ControlModifier) && !(e->modifiers() & Qt::ShiftModifier))
            Popup();
    }
}

void VirmacViewer::mouseReleaseEvent( QMouseEvent *e)
{
    if(e->button() & Qt::LeftButton)
    {
        ldown = false;
        myView->StopZooming();

        if(!(e->modifiers() & Qt::ShiftModifier) && !(e->modifiers() & Qt::ControlModifier) && !winZoom)
        {
            DrawRectangle(myXmin,myYmin,myXmax,myYmax,false);
            myXmax=e->x();
            myYmax=e->y();
            QPoint point(e->x(), e->y());
            QRect arect(lPoint, point);
            arect = arect.normalized();
            if(arect.width() && arect.height())
                myView->SweepSelect(arect);

        }

        if((e->modifiers() & Qt::ControlModifier))
        {
            setCursor(Qt::ArrowCursor);
        }

        if(winZoom)
        {
            DrawRectangle(myXmin,myYmin,myXmax,myYmax,false);
            myXmax=e->x();
            myYmax=e->y();
            QRect myZoomRect(myXmin, myYmax, abs(myXmax-myXmin), abs(myYmax-myYmin));
            if ((abs(myXmin-myXmax)>1) || (abs(myYmin-myYmax)>1))
                // Test if the zoom window size is not null
            {
                myView->ZoomWindow(myXmin, myYmin, myXmax, myYmax);
            }
            setCursor(Qt::ArrowCursor);
        }

        if(pickMode && !(e->modifiers() & Qt::ShiftModifier) && !(e->modifiers() & Qt::ControlModifier) && !winZoom)
        {
            QPoint point(e->x(), e->y());
            ShowPickedBlockInfo(point);
        }

        winZoom = false;
        releaseMouse();
    }
    if(e->button() & Qt::MidButton)
    {
        mdown = false;
        myView->StopPanning();
        QWidget::update();
        if((e->modifiers() & Qt::ControlModifier))
        {
            setCursor(Qt::ArrowCursor);
        }
    }

    if(e->button() & Qt::RightButton)
    {
        rdown = false;
        myView->StopRotation();
        if((e->modifiers() & Qt::ControlModifier))
        {
            setCursor(Qt::ArrowCursor);
        }
    }
}

void VirmacViewer::mouseMoveEvent( QMouseEvent *e)
{
    QPoint point(e->x(), e->y());
    mouseX = e->x();
    mouseY = e->y();

    VirmacMainWin *top = VirmacMainWin::getMainWindow();
    QString str;
    Point3D C;
    myView->ScreenToPoint(e->x(), e->y(), C);
    GLViewType vt = myView->GetViewType();
    bool b = (myView->GetProjectionType() == GLORTHOGRAPHIC);
    if(vt == GLTOPVIEW || vt == GLBOTTOMVIEW)
        str.sprintf(" X  %0.3lf  Y  %0.3lf",C.GetX(), C.GetY());
    else if(vt == GLFRONTVIEW || vt == GLBACKVIEW)
        str.sprintf(" X  %0.3lf  Z  %0.3lf",C.GetX(), C.GetZ());
    else if(vt == GLLEFTVIEW || vt == GLRIGHTVIEW)
        str.sprintf(" Y  %0.3lf  Z  %0.3lf", C.GetY(), C.GetZ());
    if(b)
        top->cViewer->setText(str);

    if(!(e->modifiers() & Qt::ControlModifier) && !(e->modifiers() & Qt::ShiftModifier))
    {
        if(myView->IsPlanarView() && !pickMode)
        {
            setCursor(Qt::CrossCursor);
        }
    }
    if(ldown && !(e->modifiers() & Qt::ControlModifier) && !(e->modifiers() & Qt::ShiftModifier))
    {
        myXmax = point.x(); myYmax = point.y();
        DrawRectangle(myXmin,myYmin,myXmax,myYmax,false);
        DrawRectangle(myXmin,myYmin,myXmax,myYmax,true);
    }


    // Window Zoom
    if(winZoom && (e->buttons() & Qt::LeftButton && e->modifiers() == Qt::NoModifier))
    {
        myXmax = e->pos().x();
        myYmax = e->pos().y();
        DrawRectangle(myXmin, myYmin, myXmax, myYmax, false);
        DrawRectangle(myXmin, myYmin, myXmax, myYmax, true);
    }


    if(e->modifiers() & Qt::ControlModifier)
    {
        if(ldown)
        {
            myView->ZoomView(lPoint, point);
            setCursor(QCursor(QPixmap(":/images/zoomcursor.png")));
        }
        else if(mdown)
        {
            myView->PanView(mPoint, point);
            setCursor(QCursor(QPixmap(":/images/pancursor.png")));
        }
        else if(rdown)
        {
            if(myView->GetViewType() == GLAXONVIEW || myView->GetViewType() == GLUNDEFINEDVIEW)
            {
                myView->RotateView(rPoint, point);
                setCursor(QCursor(QPixmap(":/images/rotatecursor.png")));
            }
            else
            {
                VirmacMainWin* pApp = VirmacMainWin::getMainWindow();
                pApp->setMessage(tr("Rotation allowed in axonometric view only!"));
            }
        }
    }
    if(myView->IsPlanarView())
        updateGL();
}

void VirmacViewer::wheelEvent(QWheelEvent *e)
{
    if(e->source() != Qt::MouseEventSynthesizedBySystem)
    {
        int zoomVal = e->angleDelta().manhattanLength();
        zoomVal = e->angleDelta().y() > 1 ? -1*zoomVal : zoomVal;
        myView->ZoomViewBy(zoomVal);
    }
}

void VirmacViewer::timerEvent(QTimerEvent* /*e*/)
{
    VirmacMainWin* app = VirmacMainWin::getMainWindow();
    VirmacDocument* doc = getDocument();
    if(!doc)
        return;
    doc->AnimFunction();
    app->getBlockLabel()->setText(doc->blocString);
    myView->Refresh();
}

void VirmacViewer::SetDisplayMode(const GLDisplayMode& aMode)
{
    myView->SetDisplayMode(aMode);
}

void VirmacViewer::TopView()
{
    myView->SetGridPlane(Plane::XOY());
    viewLabel.sprintf("Top View");
    myView->TopView();
}

void VirmacViewer::BottomView()
{
    myView->SetGridPlane(Plane::XOY());
    viewLabel.sprintf("Bottom View");
    myView->BottomView();
}

void VirmacViewer::FrontView()
{
    myView->SetGridPlane(Plane::ZOX());
    viewLabel.sprintf("Front View");
    myView->FrontView();
}

void VirmacViewer::BackView()
{
    myView->SetGridPlane(Plane::ZOX());
    viewLabel.sprintf("Back View");
    myView->BackView();
}

void VirmacViewer::RightView()
{
    myView->SetGridPlane(Plane::YOZ());
    viewLabel.sprintf("Right View");
    myView->RightView();
}

void VirmacViewer::LeftView()
{
    myView->SetGridPlane(Plane::YOZ());
    viewLabel.sprintf("Left View");
    myView->LeftView();
}

void VirmacViewer::AxonView()
{
    viewLabel.sprintf("Axonometric");
    myView->AxonView();
}


void VirmacViewer::DrawRectangle(const int minX, const int minY,
                                 const int maxX, const int maxY, const bool draw)
{
    static int StoredminX, StoredmaxX, StoredminY, StoredmaxY;
    static bool m_IsVisible = false;

    StoredminX = (minX < maxX) ? minX: maxX ;
    StoredminY = (minY < maxY) ? minY: maxY ;
    StoredmaxX = (minX > maxX) ? minX: maxX ;
    StoredmaxY = (minY > maxY) ? minY: maxY ;

    QRect aRect;
    aRect.setRect( StoredminX, StoredminY, abs(StoredmaxX-StoredminX), abs(StoredmaxY-StoredminY));

    if (!mRectBand )
    {

        mRectBand = new QRubberBand( QRubberBand::Rectangle, this);
        mRectBand->setStyle(QStyleFactory::create("Windows"));
        mRectBand->setGeometry( aRect );
        mRectBand->show();

        QPalette palette;
        palette.setColor(mRectBand->foregroundRole(), Qt::white);
        QColor color(Qt::blue);
        color.setAlpha(80);
        palette.setBrush(QPalette::Highlight, QBrush(color));

        mRectBand->setPalette(palette);
    }

    if ( m_IsVisible && !draw ) // move or up  : erase at the old position
    {
        mRectBand->hide();
        delete mRectBand;
        mRectBand = 0;
        m_IsVisible = false;
    }

    if (draw) // move : draw
    {
        //aRect.setRect( StoredminX, StoredminY, abs(StoredmaxX-StoredminX), abs(StoredmaxY-StoredminY));
        m_IsVisible = true;
        mRectBand->setGeometry( aRect );
        //mRectBand->show();
    }
}


void VirmacViewer::Popup()
{

    VirmacMainWin* pApp = VirmacMainWin::getMainWindow();
    QMenu *pPopup = new QMenu();
    pPopup->setTearOffEnabled(true);
    pPopup->addAction(pApp->bgColor);
    pPopup->addSeparator();
    pApp->pGridMenu->setTitle(tr("Grid"));
    pPopup->addMenu(pApp->pGridMenu);
    pPopup->popup(QCursor::pos());
    rdown = false;
}

#include "RetractPara.h"
#include "CircEntryPara.h"
void VirmacViewer::ShowPickedBlockInfo(QPoint point)
{
    VirmacDocument* doc = getDocument();
    if(doc)
    {
        pickMode = false;
        NCBlock aBloc;
        Point3D P;
        unsigned long int id = myView->ProcessSelection(point.x(), point.y(), 5);
        //POSITION pos = GetDocument()->GetPath()->myGCodeList.GetHeadPosition();
        for(doc->myPathIter.Init(); doc->myPathIter.More();doc->myPathIter.Next())
        {
            aBloc = doc->myPathIter.Current();
            if(aBloc.N == id)
                break;
        }
        QString str; str.sprintf("N%d  X%lf  Y%lf Z%lf", (int)aBloc.N, aBloc.X, aBloc.Y, aBloc.Z);
        ((VirmacMainWin*)VirmacMainWin::getMainWindow())->setMessage(str);
        QMessageBox::information(this, "NC Block Information", str, QMessageBox::Ok);
        doc->ShowSelectedBloc(aBloc);
        doc->HidePath(false);
        if(pickNplay)
        {
            pickNplay = false;
            VirmacMainWin* mw = (VirmacMainWin*)VirmacMainWin::getMainWindow();
            str.sprintf("Simulation Starting At Block N%d  X%lf  Y%lf Z%lf", (int)aBloc.N, aBloc.X, aBloc.Y, aBloc.Z);
            mw->setMessage(str);
            pickNplayActive = true;
            mw->slotPlay();
        }
        if(trimAfter)
        {
            ListOfNCBlock* myNewList = new ListOfNCBlock;
            ListIteratorOfListOfNCBlock myNewListIter(myNewList);
            for(doc->myPathIter.Init(); doc->myPathIter.More(); doc->myPathIter.Next())
            {
                myNewList->Append(doc->myPathIter.Current());
                if(doc->myPathIter.Current().N == aBloc.N)
                    break;
            }
            doc->myPath->myGCodeList->Clear();
            doc->myPath->SetBlockCount(0);
            int cnt = 0;
            for(myNewListIter.Init(); myNewListIter.More(); myNewListIter.Next())
            {
                doc->myPath->AddBlock(myNewListIter.Current());
                ++cnt;
            }
            doc->myPath->SetBlockCount(cnt);
            QString str;
            str.sprintf("Path Trimmed After Bloc N%ld", aBloc.N);
            (static_cast<VirmacMainWin*>(VirmacMainWin::getMainWindow()))->setMessage(str);
            //QMessageBox::information(this, "Path Trim Info", str, QMessageBox::Ok);
            (static_cast<VirmacMainWin*>(VirmacMainWin::getMainWindow()))->setMessage("Do You Want To Add A Circular Exit?");
            if(QMessageBox::information(this, "Tool Exit Option", "Do You Want To Add A Circular Exit?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
            {
                AddCircularExit();
                (static_cast<VirmacMainWin*>(VirmacMainWin::getMainWindow()))->setMessage("Circular Exit Added!");
            }

            RetractPara dlg;
            if(dlg.exec() == QDialog::Accepted)
            {
                NCBlock H = doc->myPath->myGCodeList->Last();
                NCBlock P;

                //Disengagement
                P.G = (1);
                P.X = H.X;
                P.Y = H.Y;
                P.Z = (H.Z+dlg.retraction());
                doc->myPath->myGCodeList->Append(P);
                doc->myPath->SetBlockCount(doc->myPath->GetBlockCount() + 1);
                //Clearance Retract
                P.G = 0;
                P.Z = (H.Z+dlg.clearance());
                doc->myPath->myGCodeList->Append(P);
                doc->myPath->myGCodeList->Append(P);
                doc->myPath->SetBlockCount(doc->myPath->GetBlockCount() + 2);
            }
            trimAfter = false;
            doc->myPathIter.Init();
            doc->myPath->RefreshPath();
        }
        else if(trimBefore)
        {
            ListOfNCBlock* myNewList = new ListOfNCBlock;
            ListIteratorOfListOfNCBlock myNewListIter(myNewList);
            for(doc->myPathIter.Init(); doc->myPathIter.More(); doc->myPathIter.Next())
            {
                if(doc->myPathIter.Current().N == aBloc.N)
                    break;
            }
            while(doc->myPathIter.More())
            {
                myNewList->Append(doc->myPathIter.Current());
                doc->myPathIter.Next();
            }
            doc->myPath->myGCodeList->Clear();
            doc->myPath->SetBlockCount(0);
            int cnt = 0;
            for(myNewListIter.Init(); myNewListIter.More(); myNewListIter.Next())
            {
                doc->myPath->AddBlock(myNewListIter.Current());
                ++cnt;
            }
            doc->myPath->SetBlockCount(cnt);
            QString str;
            str.sprintf("Path Trimmed Before Bloc N%ld", aBloc.N);
            ((VirmacMainWin*)VirmacMainWin::getMainWindow())->setMessage(str);
            ((VirmacMainWin*)VirmacMainWin::getMainWindow())->setMessage("Do You Want To Add A Circular Entry?");
            if(QMessageBox::information(this, "Tool Exit Option", "Do You Want To Add A Circular Entry?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
            {
                AddCircularEntry();
                ((VirmacMainWin*)VirmacMainWin::getMainWindow())->setMessage("Circular Entry Added!");
            }

            RetractPara dlg;
            if(dlg.exec() == QMessageBox::Accepted)
            {
                NCBlock H = doc->myPath->myGCodeList->First();
                NCBlock P;
                //Engagement
                P.G = 0;
                P.X = H.X;
                P.Y = H.Y;
                P.Z = (H.Z + dlg.retraction());
                doc->myPath->myGCodeList->Prepend(P);
                doc->myPath->SetBlockCount(doc->myPath->GetBlockCount() + 1);
                //Positioning
                P.G = 0;
                P.X = H.X;
                P.Y = H.Y;
                P.Z = (H.Z + dlg.clearance());
                doc->myPath->myGCodeList->Prepend(P);
                doc->myPath->SetBlockCount(doc->myPath->GetBlockCount() + 1);
                //Clearance Plane
                P.G = 0;
                P.Z = (H.Z + dlg.clearance());
                doc->myPath->myGCodeList->Prepend(P);
                doc->myPath->SetBlockCount(doc->myPath->GetBlockCount() + 1);
            }
            trimBefore = false;
            doc->myPathIter.Init();
            doc->myPath->RefreshPath();
        }

        doc->ShowPoints(false);
        doc->HideTool(false);
        setCursor(QCursor(Qt::ArrowCursor));
        if(!pickNplayActive)
            doc->myPathIter.Init();
        myView->Refresh();
    }
}

void VirmacViewer::PickBlock()
{
    pickMode = true;
    doc->HidePath(true);
    doc->ShowPoints(true);
    doc->HideTool(true);
    myView->Refresh();
    setCursor(QCursor(QPixmap(":/images/pickcursor.png")));
    ((VirmacMainWin*)VirmacMainWin::getMainWindow())->setPrompt("Pick A Point To Get The Block Number");
}

void VirmacViewer::AddCircularEntry()
{
    VirmacDocument* pDoc = getDocument();
    NCBlock stBlock = pDoc->myPath->myGCodeList->First();
    NCBlock nxBlock = pDoc->myPathIter.ValueAt(2);
    Vector3D OP(stBlock.X, stBlock.Y, 0);
    Vector3D XP(nxBlock.X, nxBlock.Y, 0);
    Vector3D V1(OP, XP);
    Vector3D Vz(OP, Vector3D(OP.GetX(),OP.GetY(),OP.GetZ()+10)), Vr;

    bool CW = true;
    double rad = 10;
    CircEntryPara dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        CW = dlg.isUpMilling();
        rad = dlg.arcRadius();
    }

    V1 = V1.Unit();
    Vz = Vz.Unit();
    if(CW)
        Vr = V1.Crossed(Vz);
    else
        Vr = Vz.Crossed(V1);
    Vr = Vr.Unit();
    Vr *= rad;
    Vector3D cen(stBlock.X+Vr.GetX(), stBlock.Y+Vr.GetY(), stBlock.Z);

    Vector3D aV1(OP, cen);
    Vector3D aVz(OP, Vector3D(OP.GetX(),OP.GetY(),OP.GetZ()+10)), aVr;
    aV1 = aV1.Unit();
    aVz = aVz.Unit();
    if(CW)
        aVr = aV1.Crossed(aVz);
    else
        aVr = aVz.Crossed(aV1);
    aVr = aVr.Unit();
    aVr *= rad;

    NCBlock &aBloc = pDoc->myPath->myGCodeList->First();

    if(CW)
        aBloc.G = 2;
    else
        aBloc.G = 3;
    aBloc.I = cen.GetX(); aBloc.J = cen.GetY();

    NCBlock G1;
    G1.G = 1;
    G1.X = (cen.GetX()+aVr.GetX());  G1.Y = (cen.GetY()+aVr.GetY());  G1.Z = (cen.GetZ());
    pDoc->myPath->myGCodeList->Prepend(G1);

}

void VirmacViewer::AddCircularExit()
{
    VirmacDocument* pDoc = getDocument();
    NCBlock endBlock = pDoc->myPath->myGCodeList->Last();
    NCBlock prevBlock = pDoc->myPathIter.ValueAt(pDoc->myPath->GetBlockCount() - 1);
    Vector3D OP(prevBlock.X, prevBlock.Y, 0);
    Vector3D XP(endBlock.X, endBlock.Y, 0);
    Vector3D V1(OP, XP);
    Vector3D Vz(OP, Vector3D(OP.GetX(),OP.GetY(),OP.GetZ()+10)), Vr;

    bool CW = true;
    double rad = 10;
    CircEntryPara dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        CW = dlg.isUpMilling();
        rad = dlg.arcRadius();
    }

    //QString str;
    V1 = V1.Unit();
    Vz = Vz.Unit();
    if(CW)
        Vr = V1.Crossed(Vz);
    else
        Vr = Vz.Crossed(V1);
    Vr = Vr.Unit();
    Vr *= rad;
    Vector3D cen(endBlock.X+Vr.GetX(), endBlock.Y+Vr.GetY(), endBlock.Z);

    Vector3D aV1(XP, cen);
    Vector3D aVz(XP, Vector3D(XP.GetX(),XP.GetY(),XP.GetZ()+10)), aVr;
    aV1 = aV1.Unit();
    aVz = aVz.Unit();
    if(CW)
        aVr = aV1.Crossed(aVz);
    else
        aVr = aVz.Crossed(aV1);
    aVr = aVr.Unit();
    aVr *= rad;

    NCBlock aBloc;

    if(CW)
        aBloc.G = 2;
    else
        aBloc.G = 3;
    aBloc.X = (cen.GetX()-aVr.GetX());  aBloc.Y = (cen.GetY()-aVr.GetY());  aBloc.Z = (cen.GetZ());
    aBloc.I = (cen.GetX()); aBloc.J = (cen.GetY());
    pDoc->myPath->myGCodeList->Append(aBloc);
}

void VirmacViewer::MultiView(bool doIt)
{
    if(doIt)
    {
        multiViewActive = true;
        myView->MultiView(true);
    }
    else
    {
        multiViewActive = false;
        myView->MultiView(false);
    }
}

