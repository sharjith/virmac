/***************************************************************************
  qglview.h  -  description
  -------------------
begin                : |15- Feb|
copyright            : (C) |2003| by |Sharjith N.|
email                : |sharjith_ssn@hormail.com|
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGLVIEW_H
#define QGLVIEW_H

//Geometry
#include "Geometry.h"
#include "GeomException.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Line3D.h"
#include "Plane.h"

//Graphics
#include "VGLObject.h"
#include "VGLAxisSystem.h"
#include "VGLTrihedron.h"
#include "VGLGrid.h"
#include "VGLDisplayContext.h"
#include "VGLCamera.h"

#include <QWidget>
#include <QRect>
#include <QPoint>
#include <QGL>

/**
 *@author Sharjith
 */

class VirmacDocument;
class VirmacViewer;
class VGLDisplayContext;

enum GLProjectionType
{
    GLORTHOGRAPHIC,
    GLPERSPECTIVE
};

class VirmacGLView : public QObject
{
    Q_OBJECT

    public:
	VirmacGLView(QGLWidget* w, VGLDisplayContext* ctx);
	virtual ~VirmacGLView();
	void InitGL();
	void ReSize( int w, int h );
	void Draw();
	GLfloat GetRange() const { return nRange; }
    private:
	bool ldown;
	bool mdown;
	bool rdown;

	QPoint  lPoint;
	QPoint  mPoint;
	QPoint  rPoint;

	/* Light values and coordinates*/
	GLfloat  ambientLight[4];
	GLfloat  diffuseLight[4];
	GLfloat  specular[4];
	GLfloat  specref[4];
	/*Viewing Volume Range*/

	int     myXmin;
	int     myYmin;
	int     myXmax;
	int     myYmax;

	int	winW;
	int	winH;

	GLdouble nRange;

	GLdouble xTrans;
	GLdouble yTrans;
	GLdouble zTrans;
	GLdouble win_xmin;
	GLdouble win_ymin;
	GLdouble winz;
	GLdouble win_xmax;
	GLdouble win_ymax;
	GLfloat m_bkRed;
	GLfloat m_bkGreen;
	GLfloat m_bkBlue;
	GLfloat m_bkBotRed;
	GLfloat m_bkBotGreen;
	GLfloat m_bkBotBlue;
	GLDisplayMode displayMode;
	GLProjectionType projectionType;
	bool m_antialias;

	QPoint DownPoint;
	bool ZoomON;
	bool PanON;
	bool RotON;

	bool gridOn;

	bool backgroundGradient;

	bool multiViewActive;

	QGLWidget* theWidget;
	QString    viewLabel;
	VGLCamera* myCamera;
	VGLDisplayContext* theContext;
	VGLTrihedron* myTrihedron;
	VGLGrid* myGrid;
	GLViewType myViewType;
	// Operations
    public:
	void RenderScene(GLenum mode);

	void ZoomView(QPoint, QPoint);
	void ZoomViewBy(const int amount);
	void PanView(QPoint, QPoint);
	void RotateView(QPoint, QPoint);

	void StopZooming(){ ZoomON = false; }
	void StopPanning(){ PanON = false; }
	void StopRotation(){ RotON = false; }

	void TopView();
	void BottomView();
	void FrontView();
	void BackView();
	void LeftView();
	void RightView();
	void AxonView();
	void MultiView(bool);

	void SnapShot(const QString& fName);

	GLViewType GetViewType() const { return myViewType; }
	bool IsPlanarView() const;
	VGLGrid* GetGrid() { return myGrid; }

	void FitAll();
	void ZoomWindow(const int& xMin, const int& yMin, const int& xMax, const int& yMax);
	void ResetView();
	void Refresh() { theWidget->updateGL();}

	void PointToScreen(const Point3D& P, int& x, int& y);
	void ScreenToPoint(const int& x, const int& y, Point3D&  P, const bool& midPlane = true);
	void FitView();
	void Fit3d(QRect zcRect);

	void SetBackgroundColor(GLfloat, GLfloat, GLfloat);
	void SetDisplayMode(const GLDisplayMode& aMode);
	GLDisplayMode GetDisplayMode() const { return displayMode; }

	void SetProjectionType(const GLProjectionType& aProj);
	GLProjectionType GetProjectionType() const { return projectionType; }

	void SetAntiAliasing(const bool& mode);

	void SetGridOn(const bool& mode);
	void SetGridPara(const Plane& plane, const double& size, const double& step);
	void SetGridPlane(const Plane& plane) { myGrid->SetPlane(plane); }
	void SetGridStep(const float& step) { myGrid->SetStep(step); }
	void SetGridColor(const GLubyte& r, const GLubyte& g, const GLubyte& b);
	bool IsGridOn() const { return gridOn; }

	QColor GetBackgroundTopColor() const;
	void SetBackgroundTopColor(const QColor& color );

	QColor GetBackgroundBottomColor() const;
	void SetBackgroundBottomColor(const QColor& color );


	void Select(const int& x, const int& y);
	void MultiSelect(const int& x, const int& y);
	void SweepSelect(const QRect& swRect);

	GLuint  ProcessSelection(const int& x, const int& y, const int& sensitivity = 5);
	GLuint  ProcessSweepSelection(const QRect& rect, unsigned long int* id);

	bool GetBackgroundGradient() const;
	void SetBackgroundGradient(bool value);
};

#endif
