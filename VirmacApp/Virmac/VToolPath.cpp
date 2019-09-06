// ToolPath.cpp: implementation of the CToolPath class.
//
//////////////////////////////////////////////////////////////////////

#include "VirmacMainWin.h"
#include "VToolPath.h"
#include "Point3D.h"
#include "CircularArc.h"
#include "AxisSystem.h"

#include "GCodeException.h"
using namespace CGCodeException;

#include <qmessagebox.h>
#include <qapplication.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VToolPath::VToolPath()
{
    glObjType = GLSIRUS;
    glObjID = (int)glObjType + VGLObject::GetCount();

    myGCodeList = new ListOfNCBlock;
    itsRed = 255;
    itsGreen = 165;
    itsBlue = 10;
    m_bShowArc = false;
    errString.sprintf("...");

    myArcPlane = G02_03_XOY;

    m_dTransX = 0;
    m_dTransY = 0;
    m_dTransZ = 0;

    m_dScaleX = 1;
    m_dScaleY = 1;
    m_dScaleZ = 1;

    m_dRotCX = 0;
    m_dRotCY = 0;
    m_dRotCZ = 0;

    m_dRotRX = 0;
    m_dRotRY = 0;
    m_dRotRZ = 0;
}

VToolPath::VToolPath(const QString& fName): fileName(fName)
{

    myGCodeList = new ListOfNCBlock;

    blocCount = 0;
    n=0;
    g=x=y=z=pn=pg=px=py=pz=brac=f=pf=0;
    ra=rb=rc=pa=pb=pc=ri=rj=rk=pi=pj=pk = 0;
    maxFeed = 10000;

    myArcPlane = G02_03_XOY;

    Done = true;
    errString.sprintf("...");


    if(!fName.isEmpty())
    {
        try
        {
            Read();
        }
        catch(CGCodeException::FileNotFound e)
        {
            QMessageBox mb(QString("Error!"), QString("File Not Found!!\n")+e.What(),
                           QMessageBox::Critical,
                           QMessageBox::Ok,


                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.exec();
            errString = e.What();
            Done = false;
        }
        catch(CGCodeException::SyntaxError e)
        {
            QMessageBox mb(QString("Error!"), QString("Syntax Error In File!!\n")+e.What(),
                           QMessageBox::Critical,
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.exec();
            errString = e.What();
            Done = false;
        }
        catch(CGCodeException::MissingDecimal e)
        {
            QMessageBox mb(QString("Error!"), QString("Missing Decimal!!\n")+e.What(),
                           QMessageBox::Critical,
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.exec();
            errString = e.What();
            Done = false;
        }
        catch(CGCodeException::MultipleDecimal e)
        {
            QMessageBox mb(QString("Error!"), QString("Multiple Decimal!!\n")+e.What(),
                           QMessageBox::Critical,
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.exec();
            errString = e.What();
            Done = false;
        }
        catch(CGCodeException::MultipleAddress e)
        {
            QMessageBox mb(QString("Error!"), QString("Multiple Address!!\n")+e.What(),
                           QMessageBox::Critical,
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.exec();
            errString = e.What();
            Done = false;
        }

    }

    glObjType = GLSIRUS;
    glObjID = (int)glObjType + VGLObject::GetCount();

    itsRed = 255;
    itsGreen = 165;
    itsBlue = 10;
    m_bShowArc = false;

    m_dTransX = 0;
    m_dTransY = 0;
    m_dTransZ = 0;

    m_dScaleX = 1;
    m_dScaleY = 1;
    m_dScaleZ = 1;

    m_dRotCX = 0;
    m_dRotCY = 0;
    m_dRotCZ = 0;

    m_dRotRX = 0;
    m_dRotRY = 0;
    m_dRotRZ = 0;

    ComputeBoundLimits();
    InitDisplayLists();
}

VToolPath::VToolPath(const VToolPath& P) : VGLObject()
{
    fileName = P.fileName;
    myGCodeList = new ListOfNCBlock;

    ListIteratorOfListOfNCBlock myListIter(myGCodeList);
    for(myListIter.Init(); myListIter.More(); myListIter.Next())
        myGCodeList->Append(myListIter.Current());

    myArcPlane = G02_03_XOY;

    glObjType = GLSIRUS;
    glObjID = P.glObjID;

    itsRed = P.itsRed;
    itsGreen = P.itsGreen;
    itsBlue = P.itsBlue;

    m_dTransX = P.m_dTransX;
    m_dTransY = P.m_dTransY;
    m_dTransZ = P.m_dTransZ;

    m_dScaleX = P.m_dScaleX;
    m_dScaleY = P.m_dScaleY;
    m_dScaleZ = P.m_dScaleZ;

    m_dRotCX = P.m_dRotCX;
    m_dRotCY = P.m_dRotCY;
    m_dRotCZ = P.m_dRotCZ;

    m_dRotRX = P.m_dRotRX;
    m_dRotRY = P.m_dRotRX;
    m_dRotRZ = P.m_dRotRX;

    blocCount = P.blocCount;
}

VToolPath::~VToolPath()
{
    if(myGCodeList)
    {
        myGCodeList->Clear();
        delete myGCodeList;
    }
    glDeleteLists(pathList, 1);
}

VGLObject* VToolPath::Copy() const
{
    VToolPath* aPath = new VToolPath(fileName);
    aPath->SetColor(itsRed, itsGreen, itsBlue);
    aPath->SetMaterial(GetMaterial());

    aPath->m_dTransX = m_dTransX;
    aPath->m_dTransY = m_dTransY;
    aPath->m_dTransZ = m_dTransZ;

    aPath->m_dScaleX = m_dScaleX;
    aPath->m_dScaleY = m_dScaleY;
    aPath->m_dScaleZ = m_dScaleZ;

    aPath->m_dRotCX = m_dRotCX;
    aPath->m_dRotCY = m_dRotCY;
    aPath->m_dRotCZ = m_dRotCZ;

    aPath->m_dRotRX = m_dRotRX;
    aPath->m_dRotRY = m_dRotRX;
    aPath->m_dRotRZ = m_dRotRX;

    aPath->blocCount = blocCount;

    return aPath;
}

VToolPath VToolPath::operator = (const VToolPath& P)
{
    if(this == &P)
        return *this;
    fileName = P.fileName;
    ListIteratorOfListOfNCBlock myListIter(myGCodeList);
    for(myListIter.Init(); myListIter.More(); myListIter.Next())
        myGCodeList->Append(myListIter.Current());

    glObjType = GLSIRUS;
    glObjID = P.glObjID;

    itsRed = P.itsRed;
    itsGreen = P.itsGreen;
    itsBlue = P.itsBlue;

    m_dTransX = P.m_dTransX;
    m_dTransY = P.m_dTransY;
    m_dTransZ = P.m_dTransZ;

    m_dScaleX = P.m_dScaleX;
    m_dScaleY = P.m_dScaleY;
    m_dScaleZ = P.m_dScaleZ;

    m_dRotCX = P.m_dRotCX;
    m_dRotCY = P.m_dRotCY;
    m_dRotCZ = P.m_dRotCZ;

    m_dRotRX = P.m_dRotRX;
    m_dRotRY = P.m_dRotRX;
    m_dRotRZ = P.m_dRotRX;

    blocCount = P.blocCount;

    return *this;
}

void VToolPath::SetFile(const QString& fName)
{
    myGCodeList->Clear();
    fileName = fName;
    blocCount = 0;
    n=0;
    g=x=y=z=pn=pg=px=py=pz=brac=f=pf=0;
    ra=rb=rc=pa=pb=pc=ri=rj=rk=pi=pj=pk = 0;

    maxFeed = 10000;

    Done = true;
    if(!fName.isEmpty())
    {
        try
        {
            Read();
        }
        catch(CGCodeException::FileNotFound e)
        {
            QMessageBox mb(QString("Error!"), QString("File Not Found!!\n")+e.What(),
                           QMessageBox::Critical,
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.exec();
            errString = e.What();
            Done = false;
        }
        catch(CGCodeException::SyntaxError e)
        {
            QMessageBox mb(QString("Error!"), QString("Syntax Error In File!!\n")+e.What(),
                           QMessageBox::Critical,
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.exec();
            errString = e.What();
            Done = false;
        }
        catch(CGCodeException::MissingDecimal e)
        {
            QMessageBox mb(QString("Error!"), QString("Missing Decimal!!\n")+e.What(),
                           QMessageBox::Critical,
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.exec();
            errString = e.What();
            Done = false;
        }
        catch(CGCodeException::MultipleDecimal e)
        {
            QMessageBox mb(QString("Error!"), QString("Multiple Decimal!!\n")+e.What(),
                           QMessageBox::Critical,
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);
            mb.exec();
            errString = e.What();
            Done = false;
        }
        catch(CGCodeException::MultipleAddress e)
        {
            QMessageBox mb(QString("Error!"), QString("Multiple Address!!\n")+e.What(),
                           QMessageBox::Critical,
                           QMessageBox::Ok,
                           QMessageBox::NoButton,
                           QMessageBox::NoButton);

            mb.exec();
            errString = e.What();
            Done = false;
        }
    }

    glObjType = GLSIRUS;
    glObjID = (int)glObjType + VGLObject::GetCount();

    itsRed = 255;
    itsGreen = 165;
    itsBlue = 10;

    m_dTransX = 0;
    m_dTransY = 0;
    m_dTransZ = 0;

    m_dScaleX = 1;
    m_dScaleY = 1;
    m_dScaleZ = 1;

    m_dRotCX = 0;
    m_dRotCY = 0;
    m_dRotCZ = 0;

    m_dRotRX = 0;
    m_dRotRY = 0;
    m_dRotRZ = 0;

    ComputeBoundLimits();
    InitDisplayLists();
}

bool VToolPath::AddBlock(NCBlock aBlock)
{
    bool b = true;
    myGCodeList->Append(aBlock);
    ++blocCount;
    return b;
}


void VToolPath::Nullify()
{
    myGCodeList->Clear();
    blocCount = 0;
    itsBox.SetLimits(-1,1,-1,1,-1,1);
    glDeleteLists(pathList, 1);
}

void VToolPath::DefineDisplay()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    
    glColor3ub(itsRed, itsGreen, itsBlue);

    glPushMatrix();
    glTranslated(m_dTransX,m_dTransY,m_dTransZ);
    glTranslated(m_dRotCX,m_dRotCY,m_dRotCZ);
    glRotated(m_dRotRX,1,0,0);
    glRotated(m_dRotRY,0,1,0);
    glRotated(m_dRotRZ,0,0,1);
    glScaled(m_dScaleX, m_dScaleY, m_dScaleZ);
    glPushMatrix();
    glTranslatef(-m_dRotCX,-m_dRotCY,-m_dRotCZ);

    glCallList(pathList);
    
    glPopMatrix();
    glPopMatrix();
    
    glDisable(GL_BLEND);

}

void VToolPath::Display(const GLDisplayMode& aMode)
{
    displayMode = aMode;
    DefineDisplay();
}

void VToolPath::Hilight(const GLDisplayMode& /*dMode*/)

{
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_DEPTH_TEST);
    itsRed = 0; itsGreen = 255; itsBlue = 255;
    DefineDisplay();
    glPopAttrib();
}

void VToolPath::InitDisplayLists()
{
    pathList = glGenLists(1);
    glNewList(pathList, GL_COMPILE);
    DrawPath();
    glEndList();
}

void VToolPath::DrawPath()
{
    if(!myGCodeList->IsEmpty())
    {
        glLineStipple(5,0x5555);

        NCBlock G1, G2;
        ListIteratorOfListOfNCBlock myListIter(myGCodeList);
        myListIter.Init();
        for(int i = 0; i < blocCount-1; i++)
        {
            G1 = myListIter.Current();
            if(myListIter.More())
            {
                myListIter.Next();
                G2 = myListIter.Current();
            }

            if(G1.G == 17)
                myArcPlane = G02_03_XOY;
            if(G1.G == 18)
                myArcPlane = G02_03_ZOX;
            if(G1.G == 19)
                myArcPlane = G02_03_YOZ;

            if(G2.G == 0)
                glEnable(GL_LINE_STIPPLE);  // dashed for rapid move
            else
                glDisable(GL_LINE_STIPPLE); // solid for feed move

            if(G2.G==0)
            {
                G2.myArcMode = ARC_STR;
            }
            if(G2.G==1)
            {
                G2.myArcMode = ARC_STR;
            }
            if(G2.G == 2)
            {
                G2.myArcMode = ARC_CW;
            }
            if(G2.G == 3)
            {
                G2.myArcMode = ARC_CCW;
            }

            Point3D P1(G1.X, G1.Y, G1.Z);
            Point3D P2(G2.X, G2.Y, G2.Z);

            glBegin(GL_LINE_STRIP);
            if(G2.myArcMode == ARC_CW && m_bShowArc)//draw clockwise arc
            {
                Point3D cp(G2.I,G2.J,G2.Z);
                Point3D sp(G1.X,G1.Y,G1.Z);
                Point3D ep(G2.X,G2.Y,G2.Z);

                glVertex3f(G1.X,G1.Y,G1.Z);

                AxisSystem cs;
                if(myArcPlane == G02_03_XOY)
                {
                    cs.SetDirection(0,0,1);
                }
                if(myArcPlane == G02_03_YOZ)
                {
                    cs.SetDirection(1,0,0);
                }
                if(myArcPlane == G02_03_ZOX)
                {
                    cs.SetDirection(0,1,0);
                }
                CircularArc anArc((int)myArcPlane, sp, ep, cp, PI/360, true);
                ListIteratorOfListOfPoint3D it(anArc.ArcPoints);
                for(it.Init();it.More();it.Next())
                {
                    Point3D P = it.Current();
                    glVertex3f(P.GetX(), P.GetY(), P.GetZ());
                }


                glVertex3f(G2.X, G2.Y, G2.Z);
            }
            else if(G2.myArcMode == ARC_CCW && m_bShowArc)//draw counter clockwise arc
            {
                Point3D cp(G2.I,G2.J,G2.Z);
                Point3D sp(G1.X,G1.Y,G1.Z);
                Point3D ep(G2.X,G2.Y,G2.Z);

                glVertex3f(G1.X,G1.Y,G1.Z);

                AxisSystem cs;
                if(myArcPlane == G02_03_XOY)
                {
                    cs.SetDirection(0,0,1);
                }
                if(myArcPlane == G02_03_YOZ)
                {
                    cs.SetDirection(1,0,0);
                }
                if(myArcPlane == G02_03_ZOX)
                {
                    cs.SetDirection(0,1,0);
                }
                CircularArc anArc((int)myArcPlane, sp, ep, cp, PI/360, false);
                ListIteratorOfListOfPoint3D it(anArc.ArcPoints);
                for(it.Init();it.More();it.Next())
                {
                    Point3D P = it.Current();
                    glVertex3f(P.GetX(), P.GetY(), P.GetZ());
                }



                glVertex3f(G2.X, G2.Y, G2.Z);
            }
            else//join by straight lines
            {
                glVertex3d(P1.GetX(), P1.GetY(), P1.GetZ());
                glVertex3d(P2.GetX(), P2.GetY(), P2.GetZ());
            }
            glEnd();
        }
        glDisable(GL_LINE_STIPPLE);
    }
}

void VToolPath::SetG00Color(const GLubyte& r, const GLubyte& g, const GLubyte& b)
{
    g00Red = r;
    g00Green = g;
    g00Blue = b;
}

void VToolPath::SetG01Color(const GLubyte& r, const GLubyte& g, const GLubyte& b)
{
    g01Red = r;
    g01Green = g;
    g01Blue = b;
}

void VToolPath::SetG02Color(const GLubyte& r, const GLubyte& g, const GLubyte& b)
{
    g02Red = r;
    g02Green = g;
    g02Blue = b;
}

void VToolPath::SetG03Color(const GLubyte& r, const GLubyte& g, const GLubyte& b)
{
    g03Red = r;
    g03Green = g;
    g03Blue = b;
}

void VToolPath::SetTranslation(double X, double Y, double Z)
{
    m_dTransX = X;
    m_dTransY = Y;
    m_dTransZ = Z;
    DefineDisplay();
}

void VToolPath::SetScale(double X, double Y, double Z)
{
    m_dScaleX = X;
    m_dScaleY = Y;
    m_dScaleZ = Z;
    DefineDisplay();
}

void VToolPath::SetRotation(double CX, double CY, double CZ, double RX, double RY, double RZ)

{
    m_dRotCX = CX;

    m_dRotCY = CY;
    m_dRotCZ = CZ;

    m_dRotRX = RX;
    m_dRotRY = RY;
    m_dRotRZ = RZ;

    DefineDisplay();
}

void VToolPath::GetTranslation(double& X, double& Y, double& Z)
{
    X = m_dTransX;
    Y = m_dTransY;
    Z = m_dTransZ;
}

void VToolPath::GetScale(double& X, double& Y, double& Z)
{
    X = m_dScaleX;
    Y = m_dScaleY;
    Z = m_dScaleZ;

}

void VToolPath::GetRotation(double& CX, double& CY, double& CZ, double& RX, double& RY, double& RZ)
{
    CX = m_dRotCX;
    CY = m_dRotCY;
    CZ = m_dRotCZ;


    RX = m_dRotRX;
    RY = m_dRotRY;
    RZ = m_dRotRZ;
}


//Helpers
bool VToolPath::Read()
{
    char a[100];
    NCBlock G;
    bool res = true;
    int bCnt = 0;
    int totBlk = 0;
    QString pCent;
    QStatusBar* pBar = ((VirmacMainWin*)VirmacMainWin::getMainWindow())->statusBar();
    QProgressBar* pProg = ((VirmacMainWin*)VirmacMainWin::getMainWindow())->progBar;

    //for progress bar step
    FILE* infile = fopen(fileName.toLatin1(), "r");
    while(!feof(infile))
    {
        fgets(a ,100, infile);
        totBlk++;
    }
    pProg->setMaximum(totBlk);
    fclose(infile);

    //now for reading g code
    fp = fopen(fileName.toLatin1(), "r");

    if(!fp)
    {
        throw FileNotFound(fileName);
        return false;
    }
    else
    {
        do{
            bCnt++;
            fgets(a,100, fp);
            if(strlen(a) == 0)
                continue;

            /*if(!CheckSyntax(a))
          {
          fclose(fp);
          throw SyntaxError(a);
          res = false;
          break;
          } */
            if(SearchVal(a,'(',brac))
            {
                continue;

            }
            if(SearchVal(a,'%',brac))
            {
                continue;
            }
            if(SearchMultiple(a,'N'))
            {
                fclose(fp);
                throw MultipleAddress(a);
                res = false;
                break;
            }
            if(SearchVal(a,'N',n))
            {
                pn = (unsigned long int)n;
                G.N = (unsigned long int)n;
            }
            else
            {
                ++pn;
                n = (unsigned long int)pn;
                G.N = (unsigned long int)n;
            }
            if(SearchVal(a,'G',g))
            {
                pg = (unsigned)g;
                G.G = (unsigned)g;
            }
            else
            {
                g = pg;
                G.G = 01;
            }
            if(SearchVal(a,'F',f))
            {
                pf = f;

                if(g == 0)
                    G.F = maxFeed;
                else
                    G.F = (unsigned)f;

            }
            else
            {
                f = pf;
                if(g == 0)
                    G.F = (unsigned)maxFeed;
                else
                    G.F = (unsigned)f;
            }
            if(SearchMultiple(a,'X'))
            {
                fclose(fp);
                throw MultipleAddress(a);
                res = false;
                break;
            }
            if(SearchVal(a,'X',x))
            {
                px = x;
                G.X = (x);
            }
            else
            {
                x = px;
                G.X = (x);
            }
            if(SearchMultiple(a,'Y'))

            {
                fclose(fp);


                throw MultipleAddress(a);
                res = false;

                break;
            }
            if(SearchVal(a,'Y',y))
            {
                py = y;
                G.Y = (y);
            }
            else
            {
                y = py;
                G.Y = (y);
            }
            if(SearchMultiple(a,'Z'))
            {
                fclose(fp);
                throw MultipleAddress(a);
                res = false;
                break;
            }
            if(SearchVal(a,'Z',z))
            {
                pz = z;
                G.Z = (z);
            }
            else
            {
                z = pz;
                G.Z = (z);
            }

            //A Axis
            if(SearchMultiple(a,'A'))
            {
                fclose(fp);
                throw MultipleAddress(a);
                res = false;
                break;
            }
            if(SearchVal(a,'A',ra))
            {
                pa = ra;
                G.A = (ra);
            }
            else
            {
                ra = pa;
                G.A = (ra);
            }


            //B Axis
            if(SearchMultiple(a,'B'))
            {
                fclose(fp);
                throw MultipleAddress(a);
                res = false;
                break;
            }
            if(SearchVal(a,'B',rb))
            {
                pb = rb;
                G.B = (rb);
            }
            else
            {
                rb = pb;

                G.B = (rb);
            }

            //C Axis
            if(SearchMultiple(a,'C'))
            {
                fclose(fp);
                throw MultipleAddress(a);
                res = false;
                break;
            }
            if(SearchVal(a,'C',rc))
            {
                pc = rc;
                G.C = (rc);
            }
            else
            {
                rc = pc;
                G.C = (rc);
            }

            //I Component
            if(SearchMultiple(a,'I'))
            {
                fclose(fp);
                throw MultipleAddress(a);
                res = false;
                break;
            }
            if(SearchVal(a,'I',ri))
            {
                pi = ri;
                G.I = (ri);

                G.myCircType = (IJK_TYPE);

            }
            else
            {
                ri = pi;
                G.I = (ri);
            }

            //J Component
            if(SearchMultiple(a,'J'))
            {
                fclose(fp);
                throw MultipleAddress(a);
                res = false;
                break;
            }
            if(SearchVal(a,'J',rj))
            {
                pj = rj;
                G.J = (rj);
                G.myCircType = (IJK_TYPE);
            }
            else
            {
                rj = pj;
                G.J = (rj);
            }

            //K Component
            if(SearchMultiple(a,'K'))
            {
                fclose(fp);
                throw MultipleAddress(a);
                res = false;
                break;
            }
            if(SearchVal(a,'K',rk))
            {
                pk = rk;
                G.K = (rk);
                G.myCircType = (IJK_TYPE);
            }
            else
            {

                rk = pk;
                G.K = (rk);
            }
            //R Component
            if(SearchMultiple(a,'R'))
            {
                fclose(fp);
                throw MultipleAddress(a);
                res = false;
                break;
            }
            if(SearchVal(a,'R',rk))
            {
                pk = rk;
                G.R = (rk);
                G.myCircType = (RAD_TYPE);
            }
            else
            {
                rk = pk;
                G.R = (rk);
            }
            //M Code
            if(SearchVal(a,'M',rk))
            {
                pm = m;
                G.M = (unsigned)m;
                if(m==3)
                    G.mySpindleCondition = (SPDL_CW);
                if(m==4)
                    G.mySpindleCondition = (SPDL_CCW);
                if(m==5)
                    G.mySpindleCondition = (SPDL_STOP);

            }
            else
            {
                m = pm;
                G.M = (unsigned)m;
            }
            myGCodeList->Append(G);
            if(bCnt%100 == 0)
                pProg->setValue(bCnt);
        }while(!feof(fp));
        pCent.sprintf("%d Blocks Processed", bCnt);
        pBar->showMessage(pCent);
        pProg->setValue(bCnt);
        pProg->reset();
    }
    ListIteratorOfListOfNCBlock myListIter(myGCodeList);
    for(myListIter.Init(); myListIter.More(); myListIter.Next())
    {
        ++blocCount;
    }
    fclose(fp);
    return res;
}

bool VToolPath::CheckSyntax(char str[])
{
    int i=0;
    if(strlen(str) == 0)
        return true;
    if(str[0]=='(' || str[0]=='%' || str[0]==' ' || str[0]=='/')
        return true;
    if(!isalpha((int)str[0]) && ( str[0]!='(' || str[0]!='%' || str[0]!=' ' || str[0]!='/' ))
        return false;
    if(isalpha((int)str[0]))
    {

        while(str[i]!='\0')
        {
            if(isalpha((int)str[i]) && isalpha((int)str[i+1]))
            {
                return false;
                break;
            }
            if(str[0]=='N' && str[i]=='(')
            {
                return true;
                break;
            }
            i++;
        }
    }
    return true;
}

bool VToolPath::SearchMultiple(char str[], char a)

{
    int i=0,cnt=0;
    char p;
    while(str[i]!='\0')
    {
        p = str[i];
        if(p==a)

        {
            cnt++;
            if(cnt>1)
            {
                return true;
                break;

            }
        }
        i++;
    }
    return false;
}

bool VToolPath::SearchVal(char str[], char a, double& val)
{
    int i=0,j=0,cnt=0;
    char p,temp[256];
    while(str[i]!='\0')
    {
        p = str[i];
        if(p==a)
        {
            i+=1;
            while(str[i]!='\0')
            {
                temp[j]=str[i];
                if(isalpha((int)temp[j]))
                    break;
                i++;
                j++;
            }
            temp[j]='\0';
            j=0;
            while(temp[j]!='\0')
            {
                if(temp[j]=='.')
                    cnt++;
                j++;
            }
            if(cnt==0 && (a=='X'||a=='Y'||a=='Z'||a=='I'||a=='J'||a=='K'))
            {
                fclose(fp);
                throw MissingDecimal(str);
                return false;
            }
            if(cnt>1 && (a=='X'||a=='Y'||a=='Z'||a=='I'||a=='J'||a=='K'))
            {
                fclose(fp);
                throw MultipleDecimal(str);
                return false;
            }
            sscanf(temp,"%lf",&val);
            return true;
            break;
        }
        cnt=0;
        i++;
    }
    return false;
}

bool VToolPath::SearchVal(char str[], char a, int& val)
{
    double v = (double)(val);
    return SearchVal(str, a, v);
}

void VToolPath::ComputeBoundLimits()
{
    if(!Done)
        return;

    double lx=0,ly=0,lz=0,sx=0,sy=0,sz=0;

    ListIteratorOfListOfNCBlock it(myGCodeList);

    QList<double> xList;
    QList<double> yList;
    QList<double> zList;

    for(it.Init(); it.More(); it.Next())
    {
        xList.append(it.Current().X);
        yList.append(it.Current().Y);
        zList.append(it.Current().Z);
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

