// StlObject.cpp: implementation of the CStLObject class.
//
//////////////////////////////////////////////////////////////////////

#include "VirmacMainWin.h"
#include "VStLObject.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VStLObject::VStLObject(VStLReader* r)
{
    myReader = r->Copy();
    glObjType = GLSURFACE;
    glObjID = (int)glObjType + VGLObject::GetCount();

    itsMaterial.SetName(PLASTIC);

    itsShadeRed = 125;
    itsShadeGreen = 125;
    itsShadeBlue = 125;

    itsRed = 200;
    itsGreen = 225;
    itsBlue = 150;

    m_bShowNormals = false;

    displayMode = GLSHADED;

    pointList = new ListOfPoint3D;
    myFacetList = new ListOfTriFacet;
    myNormalList = new ListOfOneAxis;
    ComputePoints();
    ComputeBoundLimits();
    ComputeNormals();
    InitDisplayLists();
}

VStLObject::~VStLObject()
{
    pointList->Clear();
    delete pointList;
    myFacetList->Clear();
    delete myFacetList;
    myNormalList->Clear();
    delete myNormalList;
    delete myReader;
    glDeleteLists(facetList, 1);
    glDeleteLists(normalList, 1);
    glDeleteLists(bBoxList, 1);
}

VGLObject* VStLObject::Copy() const
{
    VStLObject* O = new VStLObject(myReader);
    O->SetColor(itsRed, itsGreen, itsBlue);
    O->SetMaterial(GetMaterial());
    O->glObjID = glObjID;
    return O;
}

void VStLObject::SetReader(VStLReader* r)
{
    if(myReader)
    {
        delete myReader;
        myReader = NULL;
    }
    myReader = r->Copy();
    glObjType = GLSURFACE;
    glObjID = (int)glObjType + VGLObject::GetCount();

    itsMaterial.SetName(PLASTIC);

    itsShadeRed = 125;
    itsShadeGreen = 125;
    itsShadeBlue = 125;

    itsRed = 200;
    itsGreen = 225;
    itsBlue = 150;

    ComputePoints();
    ComputeBoundLimits();
    ComputeNormals();
    InitDisplayLists();
}

void VStLObject::Nullify()
{
    pointList->Clear();
    myFacetList->Clear();
    myNormalList->Clear();
    glDeleteLists(facetList, 1);
    glDeleteLists(normalList, 1);
    glDeleteLists(bBoxList, 1);
}

void VStLObject::DefineDisplay()
{
    GLfloat bgcol[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE, bgcol);
    GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
    // Enable Depth Testing
    glEnable(GL_DEPTH_TEST);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,specref);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,128);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    if(displayMode == GLSHADED)
    {
        glPushAttrib(GL_LIGHTING_BIT);
        ApplyMaterial();
        DrawShaded();
        glPopAttrib();
    }

    else if(displayMode == GLWIREFRAME)
    {
        glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_DEPTH_TEST);
        DrawWired();
        glPopAttrib();
    }
    else if(displayMode == GLHLREMOVED)
    {
        glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_DEPTH_TEST);
        glColor3f(bgcol[0], bgcol[1], bgcol[2]);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(5, 5);
        DrawShaded();
        DrawWired();
        glDisable(GL_POLYGON_OFFSET_FILL);
        glPopAttrib();
    }

    glDisable(GL_BLEND);
}

void VStLObject::Display(const GLDisplayMode& dMode)
{
    displayMode = dMode;
    DefineDisplay();
}

void VStLObject::Hilight(const GLDisplayMode& /*dMode*/)
{
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    itsRed = 0; itsGreen = 255; itsBlue = 255;
    glColor3ub(itsRed, itsGreen, itsBlue);
    DrawWired();
    glPopAttrib();
}

void VStLObject::SetColor(const GLubyte& red, const GLubyte& green, const GLubyte& blue)
{
    if(displayMode == GLWIREFRAME)
    {
        itsRed = red;
        itsGreen = green;
        itsBlue = blue;
    }
    else
    {
        itsShadeRed = red;
        itsShadeGreen = green;
        itsShadeBlue = blue;
    }
    DefineDisplay();
}

void VStLObject::GetColor(GLubyte* colVect) const
{
    colVect = new GLubyte[3];
    if(displayMode == GLWIREFRAME)
    {
        colVect[0] = itsRed;
        colVect[1] = itsGreen;
        colVect[2] = itsBlue;
    }
    else
    {
        colVect[0] = itsShadeRed;
        colVect[1] = itsShadeGreen;
        colVect[2] = itsShadeBlue;
    }
}

void VStLObject::ComputeBoundLimits()
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

void VStLObject::DrawWired()
{
    ListIteratorOfListOfPoint3D myPList(pointList);

    glColor3ub(itsRed, itsGreen, itsBlue);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glCallList(facetList);

    if(m_bShowNormals)
        DrawNormals();
}

void VStLObject::DrawShaded()
{
    ListIteratorOfListOfPoint3D myPList(pointList);

    if(displayMode == GLSHADED)
        glColor3ub(itsShadeRed, itsShadeGreen, itsShadeBlue);
    //else HLR

    glDepthFunc(GL_LESS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glCallList(facetList);

    if(m_bShowNormals)
        DrawNormals();
}

void VStLObject::ComputePoints()
{
    Point3D curP;
    ListIteratorOfListOfPoint3D myPList(myReader->pointList);

    if(!myFacetList->IsEmpty())
        myFacetList->Clear();

    if(!pointList->IsEmpty())
        pointList->Clear();
    Point3D P1, P2, P3; Vector3D V;
    for(myPList.Init(); myPList.More();)
    {
        pointList->Append(myPList.Current());
        V.SetParam(myPList.Current().GetX(), myPList.Current().GetY(), myPList.Current().GetZ());
        myPList.Next();

        pointList->Append(myPList.Current());
        P1.SetParam(myPList.Current().GetX(), myPList.Current().GetY(), myPList.Current().GetZ());
        myPList.Next();

        pointList->Append(myPList.Current());
        P2.SetParam(myPList.Current().GetX(), myPList.Current().GetY(), myPList.Current().GetZ());
        myPList.Next();

        pointList->Append(myPList.Current());
        P3.SetParam(myPList.Current().GetX(), myPList.Current().GetY(), myPList.Current().GetZ());
        myPList.Next();

        TriFacet F;
        F.P1 = P1; F.P2 = P2; F.P3 = P3; F.N = V;
        myFacetList->Append(F);
    }
}

void VStLObject::DrawBoundBox()
{
    glCallList(bBoxList);
}

void VStLObject::DrawNormals()
{
    glCallList(normalList);
}

void VStLObject::ComputeNormals(const int& /*size*/)
{
    if(!myNormalList->IsEmpty())
        myNormalList->Clear();

    ListIteratorOfListOfTriFacet it(myFacetList);
    for(it.Init(); it.More(); it.Next())
    {
        TriFacet F = it.Current();//myFacetList.GetNext(pos);
        Point3D P, P1, P2, P3;
        P1 = F.P1; P2 = F.P2; P3 = F.P3;

        P.SetX((P1.GetX()+P2.GetX()+P3.GetX())/3);
        P.SetY((P1.GetY()+P2.GetY()+P3.GetY())/3);
        P.SetZ((P1.GetZ()+P2.GetZ()+P3.GetZ())/3);

        OneAxis Ax(P, F.N);
        myNormalList->Append(Ax);
    }
}

void VStLObject::InitDisplayLists()
{
    //facet list
    facetList = glGenLists(1);
    glNewList(facetList, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    ListIteratorOfListOfTriFacet it(myFacetList);
    for(it.Init(); it.More(); it.Next())
    {
        TriFacet F = it.Current();
        glNormal3d(F.N.GetX(), F.N.GetY(), F.N.GetZ());
        glVertex3d(F.P1.GetX(), F.P1.GetY(), F.P1.GetZ());
        glVertex3d(F.P2.GetX(), F.P2.GetY(), F.P2.GetZ());
        glVertex3d(F.P3.GetX(), F.P3.GetY(), F.P3.GetZ());

    }
    glEnd();
    glEndList();
    
    //normal list
    normalList = glGenLists(1);
    glNewList(normalList, GL_COMPILE);
    ListIteratorOfListOfOneAxis itr(myNormalList);
    for(itr.Init(); itr.More(); itr.Next())
    {
        OneAxis A = itr.Current();
        Vector3D P = A.GetPosition();
        Point3D D = P;
        D.Translate(A, 10);

        glDisable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        glColor3ub(255,0,0);
        glBegin(GL_LINES);
        glVertex3d(P.GetX(), P.GetY(), P.GetZ());
        glVertex3d(D.GetX(), D.GetY(), D.GetZ());
        glEnd();
    }
    glEndList();

    //bBox list
    bBoxList = glGenLists(1);
    glNewList(bBoxList, GL_COMPILE);
    double xmin, xmax, ymin, ymax, zmin, zmax;
    GetBoundingBox().GetLimits(xmin, xmax, ymin, ymax, zmin, zmax);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    //bottom
    glVertex3d(xmin, ymin, zmin);
    glVertex3d(xmax, ymin, zmin);
    glVertex3d(xmax, ymax, zmin);
    glVertex3d(xmin, ymax, zmin);
    //top
    glVertex3d(xmin, ymin, zmax);
    glVertex3d(xmax, ymin, zmax);
    glVertex3d(xmax, ymax, zmax);
    glVertex3d(xmin, ymax, zmax);
    //front
    glVertex3d(xmin, ymin, zmin);
    glVertex3d(xmax, ymin, zmin);
    glVertex3d(xmax, ymin, zmax);
    glVertex3d(xmin, ymin, zmax);
    //front
    glVertex3d(xmin, ymax, zmin);
    glVertex3d(xmax, ymax, zmin);
    glVertex3d(xmax, ymax, zmax);
    glVertex3d(xmin, ymax, zmax);
    glEnd();
    glEndList();
}

