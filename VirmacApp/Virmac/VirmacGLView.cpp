/***************************************************************************
  QGLView.cpp  -  description
  -------------------
begin                : |15 - Feb|
copyright            : (C) |2003| by |Sharjith N.|
email                : |sharjith_ssn@hotmail.com|
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "VirmacGLView.h"
#include "MMath.h"

#include "VirmacViewer.h"
#include "VirmacDocument.h"

VirmacGLView::VirmacGLView(QGLWidget* w, VGLDisplayContext* ctx) : theWidget(w), theContext(ctx)
{
    ldown = mdown = rdown = false;

    myCamera = new VGLCamera;
    myCamera->setView(VGLCamera::SE_ISOMETRIC_VIEW);
    winW = winH = 0;
    viewLabel.sprintf("Axonometric");
    /* Rotation amounts*/

    xTrans = yTrans = zTrans = 0.0f;

    myViewType = GLAXONVIEW;

    nRange = 500;

    m_bkRed = 0.3f;
    m_bkGreen = 0.3f;
    m_bkBlue = 0.3f;

    m_bkBotRed = 0.925f;
    m_bkBotGreen = 0.913f;
    m_bkBotBlue = 0.847f;

    backgroundGradient = true;

    displayMode = GLSHADED;
    projectionType = GLORTHOGRAPHIC;

    m_antialias = false;

    ZoomON = false;
    PanON = false;
    RotON = false;

    gridOn = false;

    multiViewActive = false;

    myXmin=0;
    myYmin=0;
    myXmax=0;
    myYmax=0;

    myTrihedron = new VGLTrihedron(theWidget);
    myGrid = new VGLGrid;


    /* Light values and coordinates*/
    ambientLight[0] = 0.3f;
    ambientLight[1] = 0.3f;
    ambientLight[2] = 0.3f;
    ambientLight[3] = 1.0f;
    diffuseLight[0] = 0.7f;
    diffuseLight[1] = 0.7f;
    diffuseLight[2] = 0.7f;
    diffuseLight[3] = 1.0f;
    specular[0] = 1.0f;
    specular[1] = 1.0f;
    specular[2] = 1.0f;
    specular[3] = 1.0f;
    specref[0] =  1.0f;
    specref[1] =  1.0f;
    specref[2] =  1.0f;
    specref[3] =  1.0f;
}

VirmacGLView::~VirmacGLView()
{
    delete myTrihedron;
    delete myGrid;
    delete myCamera;
}

void VirmacGLView::InitGL()
{
    // Set up the rendering context, define display lists etc.:
    /* Insert your OpenGL initialization code here */
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    // Enable Depth Testing
    glEnable(GL_DEPTH_TEST);

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // All materials hereafter have full specular reflectivity
    // with a high shine
    glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
    glMateriali(GL_FRONT,GL_SHININESS,128);


    // Set drawing color to
    glColor3ub(156, 128, 255);

    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

void VirmacGLView::ReSize( int w, int h )
{
    // setup viewport, projection etc.:
    //

    GLdouble modelMatrix[16];
    GLdouble projMatrix[16];
    GLint viewport[4];

    /* Prevent a divide by zero*/
    winW = w;
    winH = h;
    int width = w; int height = h;
    if(h == 0)
	h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(projectionType == GLORTHOGRAPHIC)//orthographic projection
    {
	if(w <= h)
	    glOrtho(-nRange-xTrans, nRange-xTrans, -(nRange*h/w)-yTrans,
		    (nRange*h/w)-yTrans, -(nRange*50000.0f)-zTrans, (nRange*50000.0f)-zTrans);
	else
	    glOrtho(-(nRange*w/h)-xTrans, (nRange*w/h)-xTrans, -nRange-yTrans,
		    nRange-yTrans, -nRange*50000.0f, nRange*50000.0f);

    }

    if(projectionType == GLPERSPECTIVE)//perspective projection
    {
	if(w <= h)
	    gluPerspective(30, static_cast<GLdouble>(h)/static_cast<GLdouble>(w), 1, nRange*50000.0f);
	else
	    gluPerspective(30, static_cast<GLdouble>(w)/static_cast<GLdouble>(h), 1, nRange*50000.0f);
	glTranslated(0.0, 0.0, -nRange*4);
    }

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    /* store limits for gradient background */
    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
    glGetIntegerv(GL_VIEWPORT, viewport);
    gluUnProject(0, 0, 1, modelMatrix, projMatrix, viewport,
	    &win_xmin, &win_ymin, &winz);
    gluUnProject(width, height, 1, modelMatrix, projMatrix, viewport,
	    &win_xmax, &win_ymax, &winz);
}

void VirmacGLView::Draw()
{
    // call RenderScene():
    RenderScene(GL_RENDER);
}

bool VirmacGLView::GetBackgroundGradient() const
{
    return backgroundGradient;
}

void VirmacGLView::SetBackgroundGradient(bool value)
{
    backgroundGradient = value;
}


void VirmacGLView::RenderScene(GLenum /*mode*/)
{
    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // gradient background
    GLint mode;

    glGetIntegerv(GL_RENDER_MODE, &mode);
    if(mode == GL_RENDER)
    {
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(m_bkRed, m_bkGreen, m_bkBlue);
	glVertex3d (win_xmin, win_ymax, nRange*5000);
	glVertex3d (win_xmax, win_ymax, nRange*5000);
	if(backgroundGradient)
	{
	    glColor3f(m_bkBotRed, m_bkBotGreen, m_bkBotBlue);
	}
	glVertex3d (win_xmax, win_ymin, nRange*5000);
	glVertex3d (win_xmin, win_ymin, nRange*5000);
	glEnd();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glPopMatrix();
    }
    // end gradient background

    if(m_antialias)
    {
	glEnable (GL_POINT_SMOOTH);
	glEnable (GL_LINE_SMOOTH);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(1.5125f);
	glDepthFunc(GL_ALWAYS);
	glEnable(GL_DEPTH_TEST);
    }
    else
    {
	glDisable (GL_LINE_SMOOTH);
	glLineWidth (1);
	glDepthFunc(GL_LESS);
	glDisable (GL_BLEND);
    }

    glPushMatrix();

    myCamera->render();

    myTrihedron->SetSize(static_cast<GLfloat>(nRange/2.0));
    myTrihedron->Display();

    // grid displayed for projections only
    if(gridOn && ((myViewType == GLTOPVIEW) || (myViewType == GLBOTTOMVIEW) ||
		(myViewType == GLFRONTVIEW) || (myViewType == GLBACKVIEW) ||
		(myViewType == GLLEFTVIEW) || (myViewType == GLRIGHTVIEW)))
	myGrid->Display();

    //Do The Rendering
    if(mode == GL_RENDER)
    {
	theContext->Render(displayMode);
    }

    //Rendering Of Block Points
    if(!(static_cast<VirmacViewer*>(theWidget))->getDocument()->myBlocPointList->IsEmpty())
    {
	glInitNames();
	glPushName(0);
	ListIteratorOfListOfNCBlock anIter = (static_cast<VirmacViewer*>(theWidget))->getDocument()->myBPListIter;
	for(anIter.Init(); anIter.More(); anIter.Next())
	{
	    NCBlock aBloc = anIter.Current();
	    glPushAttrib(GL_COLOR_BUFFER_BIT);
	    glColor3ub(255, 255, 255);
	    glDisable(GL_LIGHTING);
	    glEnable (GL_POINT_SMOOTH);
	    glEnable (GL_BLEND);
	    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);

	    glPointSize(3);
	    glLoadName(static_cast<GLuint>(aBloc.N));
	    //QString str; str.sprintf("N %ld", aBloc.N);
	    //QMessageBox::information(this, "Info", str, QMessageBox::Ok, 0, 0);
	    glBegin(GL_POINTS);
	    glVertex3d(aBloc.X, aBloc.Y, aBloc.Z);
	    glEnd();
	    glPointSize(1);
	    glDisable (GL_POINT_SMOOTH);
	    glDisable (GL_BLEND);
	    glPopAttrib();
	}
    }
    //Rendering Of Selected Bloc;
    if(!(static_cast<VirmacViewer*>(theWidget))->getDocument()->mySelePointList->IsEmpty())
    {
	ListIteratorOfListOfNCBlock anIter = (static_cast<VirmacViewer*>(theWidget))->getDocument()->mySPListIter;
	for(anIter.Init(); anIter.More(); anIter.Next())
	{
	    NCBlock aBloc = anIter.Current();
	    glPushAttrib(GL_COLOR_BUFFER_BIT);
	    glColor3ub(255, 255, 0);
	    glDisable(GL_LIGHTING);
	    glEnable (GL_POINT_SMOOTH);
	    glEnable (GL_BLEND);
	    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);

	    glPointSize(5);
	    glBegin(GL_POINTS);
	    glVertex3d(aBloc.X, aBloc.Y, aBloc.Z);
	    glEnd();
	    glPointSize(1);
	    glDisable (GL_POINT_SMOOTH);
	    glDisable (GL_BLEND);
	    glPopAttrib();
	}
    }



    glPopMatrix();

    glFlush();
}

void VirmacGLView::ZoomView(QPoint dPoint, QPoint mPoint)
{
    if(!ZoomON)
	DownPoint = dPoint;
    ZoomON = true;

    if(DownPoint.x() > mPoint.x() || DownPoint.y() < mPoint.y())
	nRange *= 1.05;
    else
	nRange /= 1.05;

    DownPoint = mPoint;

    ReSize(winW, winH);
    theWidget->updateGL();
}

void VirmacGLView::ZoomViewBy(const int amount)
{
    if(amount < 0)
	nRange *= abs(amount)/114.2857142857;
    else
	nRange /= abs(amount)/114.2857142857;


    ReSize(winW, winH);
    theWidget->updateGL();
}

void VirmacGLView::PanView(QPoint dPoint, QPoint mPoint)
{
    if(!PanON)
	DownPoint = dPoint;
    PanON = true;

    Point3D O, P;
    ScreenToPoint(mPoint.x(), mPoint.y(), O);
    ScreenToPoint(DownPoint.x(), DownPoint.y(), P);
    Vector3D OP(O, P);
    myCamera->move(OP.GetX(), OP.GetY(), OP.GetZ());

    DownPoint = mPoint;

    ReSize(winW, winH);
    theWidget->updateGL();
}

void VirmacGLView::RotateView(QPoint dPoint, QPoint mPoint)
{
    if(!RotON)
	DownPoint = dPoint;
    RotON = true;
    QPoint rotate = DownPoint - mPoint;
    myCamera->rotateX(rotate.y()/2);
    myCamera->rotateY(rotate.x()/2);
    DownPoint = mPoint;
    myViewType = GLUNDEFINEDVIEW;
    theWidget->updateGL();
}


void VirmacGLView::TopView()
{	
    myCamera->resetAll();
    myCamera->setView(VGLCamera::TOP_VIEW);
    myViewType = GLTOPVIEW;
    viewLabel.sprintf("Top View");
    theWidget->updateGL();
}

void VirmacGLView::BottomView()
{	
    myCamera->resetAll();
    myCamera->setView(VGLCamera::BOTTOM_VIEW);

    myViewType = GLBOTTOMVIEW;
    viewLabel.sprintf("Bottom View");
    theWidget->updateGL();
}

void VirmacGLView::FrontView()
{	
    myCamera->resetAll();
    myCamera->setView(VGLCamera::FRONT_VIEW);
    myViewType = GLFRONTVIEW;
    viewLabel.sprintf("Front View");
    theWidget->updateGL();
}

void VirmacGLView::BackView()
{	
    myCamera->resetAll();
    myCamera->setView(VGLCamera::REAR_VIEW);
    myViewType = GLBACKVIEW;
    viewLabel.sprintf("Back View");
    theWidget->updateGL();
}

void VirmacGLView::LeftView()
{
    myCamera->resetAll();
    myCamera->setView(VGLCamera::LEFT_VIEW);
    myViewType = GLLEFTVIEW;
    viewLabel.sprintf("Left View");
    theWidget->updateGL();
}

void VirmacGLView::RightView()
{
    myCamera->resetAll();
    myCamera->setView(VGLCamera::RIGHT_VIEW);
    myViewType = GLRIGHTVIEW;
    viewLabel.sprintf("Right View");
    theWidget->updateGL();
}

void VirmacGLView::AxonView()
{
    myCamera->resetAll();
    myCamera->setView(VGLCamera::SE_ISOMETRIC_VIEW);
    myViewType = GLAXONVIEW;
    viewLabel.sprintf("Axonometric");
    theWidget->updateGL();
}

void VirmacGLView::MultiView(bool status)
{
    multiViewActive = status;
}

#include <qimage.h>
void VirmacGLView::SnapShot(const QString& fName)
{
    QImage px = theWidget->grabFrameBuffer();
    px.save(fName, "PNG");
}

bool VirmacGLView::IsPlanarView() const
{
    bool b = (myViewType==GLTOPVIEW || myViewType==GLBOTTOMVIEW ||
	    myViewType==GLFRONTVIEW || myViewType==GLBACKVIEW ||
	    myViewType==GLLEFTVIEW || myViewType==GLRIGHTVIEW);
    return b;
}

void VirmacGLView::FitAll()
{	
    if(theContext->IsEmpty())
	return;
    FitView();

    QRect Rect = theWidget->geometry();
    int w = Rect.width();
    int h = Rect.height();

    ReSize( w, h);
    theWidget->updateGL();
}

void VirmacGLView::ZoomWindow(const int& xMin, const int& yMin, const int& xMax, const int& yMax)
{		

    theWidget->makeCurrent();
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    QRect clientRect = theWidget->geometry();//(viewport[0], viewport[1], viewport[2], viewport[3]);

    int xmin = xMin, xmax = xMax, ymin = yMin, ymax = yMax;

    if(xmin > xmax) std::swap(xmin, xmax);
    if(ymin > ymax) std::swap(ymin, ymax);

    QRect zoomRect(xmin, ymin, abs(xmax-xmin), abs(ymax-ymin));

    //int clientArea = clientRect.width() * clientRect.height();
    //int zoomArea   = zoomRect.width() * zoomRect.height();

    double widthRatio = (double)clientRect.width()/zoomRect.width();
    double heightRatio = (double)clientRect.height()/zoomRect.height();
    double zoomRatio = (heightRatio < widthRatio) ? heightRatio : widthRatio;

    QPoint clientCen = clientRect.center();
    QPoint zoomCen = zoomRect.center();

    Point3D clientCen3d;
    ScreenToPoint(clientCen.x(), clientCen.y(), clientCen3d, true);


    Point3D zoomCen3d;
    ScreenToPoint(zoomCen.x(), zoomCen.y(), zoomCen3d, true);


    Vector3D OP(clientCen3d, zoomCen3d);
    myCamera->move(OP.GetX(), OP.GetY(), OP.GetZ());

    double oldZoom = myCamera->getZoom();

    myCamera->setZoom(myCamera->getZoom() + zoomRatio);

    double newZoom = myCamera->getZoom();

    //mZoomVal = newZoom;
    // Maintain constant size of trihedron while zoom
    double tsize = myTrihedron->GetSize();
    myTrihedron->SetSize(tsize*(oldZoom/newZoom));

    theWidget->updateGL();


    /*
       QRect rcRect = theWidget->geometry();

       int rcWidth, rcHeight, zcWidth, zcHeight;
       QPoint rcCentre, zcCentre;
       int dx, dy, dw, dh;
       GLdouble wRatio, hRatio;
       GLdouble dRange;

       GLint viewport[4];
       GLdouble mvmatrix[16],projmatrix[16];
       GLint realy;

       GLdouble cx, cy, cz;
       GLdouble mx, my, mz;

       rcWidth = rcRect.width();
       rcHeight = rcRect.height();

       zcWidth = zcRect.width();
       zcHeight = zcRect.height();

       rcCentre = rcRect.center();
       zcCentre = zcRect.center();

       theWidget->makeCurrent();
       glPushMatrix();
       glGetIntegerv(GL_VIEWPORT,viewport);
       glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
       glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);

       realy=viewport[3] - static_cast<GLint>(zcCentre.y()-1);
       gluUnProject(static_cast<GLdouble>(zcCentre.x()), static_cast<GLdouble>(realy), 0.5, mvmatrix, projmatrix, viewport,
       &mx, &my, &mz);

       realy=viewport[3]-static_cast<GLint>(rcCentre.y()-1);
       gluUnProject(static_cast<GLdouble>(rcCentre.x()), static_cast<GLdouble>(realy), 0.5, mvmatrix, projmatrix, viewport,
       &cx, &cy, &cz);

       glPopMatrix();

       dx = static_cast<int>(cx - mx);
       dy = static_cast<int>(cy - my);

       dw = rcWidth - zcWidth;
       dh = rcHeight - zcHeight;

       wRatio = static_cast<GLdouble>(zcWidth/rcWidth);
       hRatio = static_cast<GLdouble>(zcHeight/rcHeight);

       dRange = (wRatio < hRatio) ? hRatio : wRatio;

       nRange *= dRange/0.8;

       myCamera->moveAcross(-dx);
    // myCamera->move(SF3DVector(0.0, -dy, 0.0));

    ReSize(rcWidth, rcHeight);
    theWidget->updateGL();
    // theWidget->erase();

*/
}

void VirmacGLView::ResetView()
{
    xTrans = 0;
    yTrans = 0;
    zTrans = 0;
    nRange = 500;
    myCamera->resetAll();
    myCamera->setView(VGLCamera::SE_ISOMETRIC_VIEW);

    myViewType = GLAXONVIEW;
    viewLabel.sprintf("Axonometric");

    QRect rect = theWidget->geometry();

    int w = rect.width();
    int h = rect.height();

    ReSize(w, h);
    theWidget->updateGL();
}

void VirmacGLView::SetBackgroundColor(GLfloat r, GLfloat g, GLfloat b)
{
    m_bkRed = r;
    m_bkGreen = g;
    m_bkBlue = b;
    m_bkBotRed = r/0.4101f;
    m_bkBotGreen = g/0.4101f;
    m_bkBotBlue = b/0.4101f;
    theWidget->makeCurrent();
    glClearColor(m_bkRed, m_bkGreen, m_bkBlue, 1.0f);
    theWidget->updateGL();
}

void VirmacGLView::SetDisplayMode(const GLDisplayMode& aMode)
{
    displayMode = aMode;
    theWidget->updateGL();
}

void VirmacGLView::SetProjectionType(const GLProjectionType& aProj)
{
    projectionType = aProj;
    QRect rect = theWidget->geometry();

    int w = rect.width();
    int h = rect.height();

    ReSize(w, h);
    theWidget->updateGL();
}

void VirmacGLView::SetAntiAliasing(const bool& mode)
{
    m_antialias = mode;
    theWidget->updateGL();
}

void VirmacGLView::SetGridOn(const bool& mode)
{
    gridOn = mode;
    theWidget->updateGL();
}

void VirmacGLView::SetGridPara(const Plane& plane, const double& size, const double& step)
{
    myGrid->SetPlane(plane);
    myGrid->SetSize(size);
    myGrid->SetStep(step);
    theWidget->updateGL();
}

void VirmacGLView::SetGridColor(const GLubyte& r, const GLubyte& g, const GLubyte& b)
{
    myGrid->SetColor(r, g, b);
}

QColor VirmacGLView::GetBackgroundTopColor() const
{
    return QColor(static_cast<int>(m_bkRed*256),
	    static_cast<int>(m_bkGreen*256),
	    static_cast<int>(m_bkBlue*256));
}

void VirmacGLView::SetBackgroundTopColor(const QColor& color )
{
    m_bkRed = static_cast<GLfloat>(color.red())/256.0f;
    m_bkGreen = static_cast<GLfloat>(color.green())/256.0f;
    m_bkBlue = static_cast<GLfloat>(color.blue())/256.0f;
}

QColor VirmacGLView::GetBackgroundBottomColor() const
{
    return QColor(static_cast<int>(m_bkBotRed*256),
	    static_cast<int>(m_bkBotGreen*256),
	    static_cast<int>(m_bkBotBlue*256));
}

void VirmacGLView::SetBackgroundBottomColor(const QColor& color )
{
    m_bkBotRed = static_cast<GLfloat>(color.red())/256.0f;
    m_bkBotGreen = static_cast<GLfloat>(color.green())/256.0f;
    m_bkBotBlue = static_cast<GLfloat>(color.blue())/256.0f;
}

void VirmacGLView::PointToScreen(const Point3D& P, int& x, int& y)
{
    Point3D p = P;
    GLint viewport[4];
    GLdouble mvmatrix[16],projmatrix[16];
    GLdouble wx, wy, wz;
    theWidget->makeCurrent();
    glPushMatrix();
    myCamera->render();
    glGetIntegerv(GL_VIEWPORT,viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
    gluProject(p.GetX(), p.GetY(), p.GetZ(), mvmatrix, projmatrix, viewport,
	    &wx, &wy, &wz);
    wx = sround(wx);
    wy = sround(wy);
    x = static_cast<int>(wx); y = static_cast<int>(wy);
    glPopMatrix();
}

void VirmacGLView::ScreenToPoint(const int& x, const int& y, Point3D&  P, const bool& midPlane)
{
    QPoint point(x,y);
    GLint viewport[4];
    GLdouble mvmatrix[16],projmatrix[16];
    GLint realy;
    GLdouble wx, wy, wz;
    theWidget->makeCurrent();
    glPushMatrix();
    myCamera->render();
    glGetIntegerv(GL_VIEWPORT,viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
    realy=viewport[3] - static_cast<GLint>(point.y()-1);

    float winZ = 0.0f;
    if(!midPlane)
    {
	glReadPixels(point.x(), realy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	if(winZ == 1.0f)
	    winZ = 0.0f;
    }
    else
	winZ = 0.5;

    gluUnProject(static_cast<GLdouble>(point.x()), static_cast<GLdouble>(realy), winZ, mvmatrix, projmatrix, viewport,
	    &wx, &wy, &wz);
    P.SetParam(wx, wy, wz);
    glPopMatrix();
}


void VirmacGLView::FitView()
{

    /*
       BoundingBox B = theContext->GetBoundingBox();

       QList<Point3D> corners = B.GetCorners();

       if(corners.isEmpty())
       return;

       QList<int> xList, yList;

       for(int i = 0; i < corners.count(); i++)
       {
       int x, y;
       PointToScreen(corners.at(i), x, y);
       xList.append(x);
       yList.append(y);
       }

       std::sort(xList.begin(), xList.end());
       std::sort(yList.begin(), yList.end());

       int xMin = xList.first();
       int xMax = xList.last();
       int yMin = yList.first();
       int yMax = yList.last();


       ZoomWindow(xMin, yMin, xMax, yMax);

       theWidget->updateGL();
       */

    myCamera->setZoom(1.0);
    double rad;
    //theContext->RefreshVolume();
    BoundingBox B = theContext->GetBoundingBox();
    Point3D cen = B.Center();
    rad = B.BoundingRadius();
    nRange = (rad < 0.0001) ? nRange : rad;

    qWarning("Bounding radius = %f", rad);

    myCamera->setPosition(cen.GetX(), cen.GetY(), cen.GetZ());

    QRect rect = theWidget->geometry();

    int w = rect.width();
    int h = rect.height();

    ReSize(w, h);
    theWidget->updateGL();
}

void VirmacGLView::Fit3d(QRect rect)
{	
    QRect zcRect = rect;
    QRect rcRect = theWidget->geometry();

    int rcWidth, rcHeight, zcWidth, zcHeight;
    QPoint rcCentre, zcCentre;
    int dx, dy;
    GLdouble wRatio, hRatio;
    GLdouble dRange;

    GLint viewport[4];
    GLdouble mvmatrix[16],projmatrix[16];
    GLint realy;

    GLdouble cx, cy, cz;
    GLdouble mx, my, mz;

    rcWidth = rcRect.width();
    rcHeight = rcRect.height();

    zcWidth = zcRect.width();
    zcHeight = zcRect.height();

    rcCentre = rcRect.center();
    zcCentre = zcRect.center();

    theWidget->makeCurrent();

    glPushMatrix();

    glGetIntegerv(GL_VIEWPORT,viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);

    realy=viewport[3]- static_cast<GLint>(zcCentre.y()-1);
    gluUnProject(static_cast<GLdouble>(zcCentre.x()), static_cast<GLdouble>(realy), 0.5, mvmatrix, projmatrix, viewport,
	    &mx, &my, &mz);

    realy=viewport[3]- static_cast<GLint>(rcCentre.y()-1);
    gluUnProject(static_cast<GLdouble>(rcCentre.x()), static_cast<GLdouble>(realy), 0.5, mvmatrix, projmatrix, viewport,
	    &cx, &cy, &cz);

    glPopMatrix();

    dx = static_cast<int>(cx - mx);
    dy = static_cast<int>(cy - my);

    wRatio = static_cast<GLdouble>(zcWidth/rcWidth);
    hRatio = static_cast<GLdouble>(zcHeight/rcHeight);

    dRange = (wRatio < hRatio) ? hRatio : wRatio;

    nRange *= dRange/0.8;

    myCamera->setPosition(0,0,0);
    xTrans += dx;
    yTrans -= dy;

    theWidget->updateGL();
}

void VirmacGLView::Select(const int &x, const int &y)
{
    theContext->Select(this, x, y);
    theWidget->updateGL();
}

void VirmacGLView::MultiSelect(const int &x, const int &y)
{
    theContext->MultiSelect(this, x, y);
    theWidget->updateGL();
}

void VirmacGLView::SweepSelect(const QRect& swRect)
{
    theContext->SweepSelect(this, swRect);
    theWidget->updateGL();
}

GLuint VirmacGLView::ProcessSelection(const int& xPos, const int& yPos , const int& sensitivity)
{
    GLuint id = 0;

    theWidget->makeCurrent();

    // Space for selection buffer
    GLuint selectBuff[512];

    // Hit counter and viewport storeage
    GLint hits, viewport[4];

    // Setup selection buffer
    glSelectBuffer(512, selectBuff);

    // Get the viewport
    glGetIntegerv(GL_VIEWPORT, viewport);

    // Switch to projection and save the matrix
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    // Change render mode
    glRenderMode(GL_SELECT);

    // Establish new clipping volume to be unit cube around
    // mouse cursor point (xPos, yPos) and extending n pixels
    // in the vertical and horzontal direction
    int n = sensitivity;
    glLoadIdentity();
    gluPickMatrix(xPos, viewport[3] - yPos, n, n, viewport);

    QRect rect = theWidget->geometry();

    int w = rect.width();
    int h = rect.height();

    if(projectionType == GLORTHOGRAPHIC)//orthographic projection
    {
	if(w <= h)
	    glOrtho(-nRange-xTrans, nRange-xTrans, -(nRange*h/w)-yTrans,
		    (nRange*h/w)-yTrans, -(nRange*50000.0f)-zTrans, (nRange*50000.0f)-zTrans);
	else
	    glOrtho(-(nRange*w/h)-xTrans, (nRange*w/h)-xTrans, -nRange-yTrans,
		    nRange-yTrans, -nRange*50000.0f, nRange*50000.0f);
    }

    if(projectionType == GLPERSPECTIVE)//perspective projection
    {
	if(w <= h)
	    gluPerspective(30, static_cast<GLdouble>(h)/static_cast<GLdouble>(w), 1, nRange*50000.0f);
	else
	    gluPerspective(30, static_cast<GLdouble>(w)/static_cast<GLdouble>(h), 1, nRange*50000.0f);
	glTranslated(0.0, 0.0, -nRange*4);
    }

    // Draw the scene
    RenderScene(GL_SELECT);

    // Collect the hits
    hits = glRenderMode(GL_RENDER);

    // Restore the projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    // Go back to modelview for normal rendering
    glMatrixMode(GL_MODELVIEW);

    // If a single hit occured, display the info.
    if(hits)
    {
	id =  selectBuff[3];
    }

    return id;

}

GLuint VirmacGLView::ProcessSweepSelection(const QRect& swRect, unsigned long int* id)
{
    GLuint i;
    GLuint j;
    theWidget->makeCurrent();

    // Space for selection buffer
    GLuint selectBuff[512];

    // Hit counter and viewport storeage
    GLuint hits = 0;
    GLint viewport[4];

    // Setup selection buffer
    glSelectBuffer(512, selectBuff);

    // Get the viewport
    glGetIntegerv(GL_VIEWPORT, viewport);

    // Switch to projection and save the matrix
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    // Change render mode
    glRenderMode(GL_SELECT);

    // Establish new clipping volume to be cube around
    // center point of sweeping rectangle and extending pixels
    // falling within the height and width of the sweep rectangle
    // in the vertical and horzontal direction
    glLoadIdentity();
    gluPickMatrix(swRect.center().x(), viewport[3] - swRect.center().y(), swRect.width(), swRect.height(), viewport);

    QRect trect = theWidget->geometry();

    int w = trect.width();
    int h = trect.height();

    if(projectionType == GLORTHOGRAPHIC)//orthographic projection
    {
	if(w <= h)
	    glOrtho(-nRange-xTrans, nRange-xTrans, -(nRange*h/w)-yTrans,
		    (nRange*h/w)-yTrans, -(nRange*50000.0f)-zTrans, (nRange*50000.0f)-zTrans);
	else
	    glOrtho(-(nRange*w/h)-xTrans, (nRange*w/h)-xTrans, -nRange-yTrans,
		    nRange-yTrans, -nRange*50000.0f, nRange*50000.0f);
    }

    if(projectionType == GLPERSPECTIVE)//perspective projection
    {
	if(w <= h)
	    gluPerspective(30, static_cast<GLdouble>(h)/static_cast<GLdouble>(w), 1, nRange*50000.0f);
	else
	    gluPerspective(30, static_cast<GLdouble>(w)/static_cast<GLdouble>(h), 1, nRange*50000.0f);
	glTranslated(0.0, 0.0, -nRange*4);
    }

    // Draw the scene
    RenderScene(GL_SELECT);

    // Collect the hits
    hits = static_cast<GLuint>(glRenderMode(GL_RENDER));

    // Restore the projection matrix
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    // Go back to modelview for normal rendering
    glMatrixMode(GL_MODELVIEW);

    // If hits occured, display the info.
    if(hits)
    {
	GLuint *ptr, names;
	ptr = static_cast<GLuint*>(selectBuff);
	for(i = 0; i < hits; i++)
	{
	    names = *ptr;
	    ptr++; ptr++; ptr++;
	    for(j = 0; j < names; j++)
	    {
		id[i] = *ptr;
		ptr++;
	    }
	}
    }

    return hits;
}

