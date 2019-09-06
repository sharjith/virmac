// GLCurve.cpp: implementation of the CGLCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "VGLCurve.h"
#include "MMath.h"

#include <QList>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VGLCurve::VGLCurve(const Curve* crv , const GLLineStyle& lt) : lineStyle(lt)
{
    pCurve = crv->Copy();
    glObjType = GLCURVE;
    glObjID = (int)glObjType + VGLObject::GetCount();

    SMOOTH = 1000;

    itsRed = 255;
    itsGreen = 0;
    itsBlue = 255;

    pointList = new ListOfPoint3D;
    ComputePoints();
    ComputeBoundLimits();

    listNum = 1;
}

VGLCurve::~VGLCurve()
{
    if(pointList)
    {
        pointList->Clear();
        delete pointList;
    }
    delete pCurve;
}

VGLObject* VGLCurve::Copy() const
{
    VGLCurve* C = new VGLCurve(pCurve, lineStyle);
    C->SetColor(itsRed, itsGreen, itsBlue);
    C->SetSmooth(SMOOTH);
    C->glObjID = glObjID;
    return C;
}

Geometry* VGLCurve::GetGeometry() const
{
    Curve* crv = pCurve->Copy();
    return crv;
}

void VGLCurve::DefineDisplay()
{
    Point3D curP;
    ListIteratorOfListOfPoint3D myListIter(pointList);

    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);

    glColor3ub(itsRed, itsGreen, itsBlue);

    if(lineStyle == LINE_SOLID)
        glDisable(GL_LINE_STIPPLE);
    else
        glEnable(GL_LINE_STIPPLE);

    if(lineStyle == LINE_DOTTED)
        glLineStipple (1, 0x0101);  /*  dotted  */
    if(lineStyle == LINE_DASHED)
        glLineStipple (1, 0x00FF);  /*  dashed  */
    if(lineStyle == LINE_DASHDOTTED)
        glLineStipple (2, 0x1C47);  /*  dash/dot/dash  */

    glBegin(GL_LINE_STRIP);		//LINE_STRIP So that it will be common for Open and Closed Curves
    for(myListIter.Init(); myListIter.More(); myListIter.Next())
    {
        curP = myListIter.Current();
        glVertex3d(curP.GetX(), curP.GetY(), curP.GetZ());
    }
    glEnd();

    glDisable(GL_LINE_STIPPLE);
}

void VGLCurve::Display(const GLDisplayMode&)
{
    DefineDisplay();
}

void VGLCurve::Hilight(const GLDisplayMode&)
{
    itsRed = 0; itsGreen = 255; itsBlue = 255;
    DefineDisplay();
}

void VGLCurve::SetSmooth(const double& sm)
{
    SMOOTH = sm;
    ComputePoints();
    ComputeBoundLimits();
    DefineDisplay();
}

void VGLCurve::SetCurve(const Curve* crv)
{
    pCurve = crv->Copy();
    ComputePoints();
    ComputeBoundLimits();
}

void VGLCurve::ComputePoints()
{
    Point3D sP, eP, curP;
    double parts , step;
    double fPar, lPar;

    fPar = pCurve->FirstParameter();
    lPar = pCurve->LastParameter();

    parts = SMOOTH/10;

    step = fabs(lPar-fPar)/parts;

    sP = pCurve->PointAtPara(fPar);

    if(pCurve->IsClosed())
        eP = sP;
    else
        eP = pCurve->PointAtPara(lPar);

    if(!pointList->IsEmpty())
        pointList->Clear();

    if(pCurve->IsOfType(CurveType::LINE))
    {
        pointList->Append(sP);
        pointList->Append(eP);
    }
    else
    {
        for(double i = fPar; i < lPar; i += step)
        {
            curP = pCurve->PointAtPara(i);
            pointList->Append(curP);
        }
        pointList->Append(eP);//To Ensure Closure If Curve Is Closed
    }
}

void VGLCurve::ComputeBoundLimits()
{
    double lx=0,ly=0,lz=0,sx=0,sy=0,sz=0;

    ListIteratorOfListOfPoint3D it(pointList);


    QList<double> xList;
    QList<double> yList;
    QList<double> zList;

    for(it.Init(); it.More(); it.Next())
    {
        xList.append(it.Current().GetX());
        yList.append(it.Current().GetY());
        zList.append(it.Current().GetZ());
    }

    qSort(xList.begin(), xList.end());
    qSort(yList.begin(), yList.end());
    qSort(zList.begin(), zList.end());

    sx = xList.first();    lx = xList.last();
    sy = yList.first();    ly = yList.last();
    sz = zList.first();    lz = zList.last();

    itsBox.SetLimits(1,1,1,1,1,1);
    itsBox.SetLimits(sx,lx,sy,ly,sz,lz);
}
