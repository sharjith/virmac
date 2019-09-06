/***************************************************************************
  virmacdoc.cpp  -  description
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
#include <QDir>
#include <QFileInfo>
#include <QtWidgets>
#include <QMessageBox>
#include <QFileDialog>


// application specific includes
#include "VirmacDocument.h"
#include "VirmacMainWin.h"
#include "VirmacViewer.h"


VirmacDocument::VirmacDocument()
{
    pViewList = new QList<VirmacViewer*>;
    //pViewList->setAutoDelete(false);
    dContext = new VGLDisplayContext(this);
    m_bGCodeLoaded = false;
    m_bModelLoaded = false;

    myCutter = NULL;
    myPath = NULL;
    myTrail = NULL;

    myCurrentBlock = 0;
    myTotalBlocks = 0;

    m_bCheckIntersection = false;
    myStLObj = NULL;
    myPointsPerFrame = 10;
    myBlocPointList = new ListOfNCBlock;
    mySelePointList = new ListOfNCBlock;
    myBPListIter.SetList(myBlocPointList);
    mySPListIter.SetList(mySelePointList);

    DX = 0;
    DY = 0;
    DZ = 0;
    CX = 0;
    CY = 0;
    CZ = 0;
    RX = 0;
    RY = 0;
    RZ = 0;
    XP = 1;
    YP = 1;
    ZP = 1;
}

VirmacDocument::~VirmacDocument()
{
    delete pViewList;
    delete dContext;
}

void VirmacDocument::addView(VirmacViewer *view)
{
    view->makeCurrent();
    pViewList->append(view);
    changedViewList();
}

void VirmacDocument::removeView(VirmacViewer *view)
{
    pViewList->removeOne(view);
    if(!pViewList->isEmpty())
        changedViewList();
    else
        deleteContents();
}

void VirmacDocument::changedViewList(){

    VirmacViewer *w;
    if((int)pViewList->count() == 1){
        w = pViewList->first();
        w->setWindowTitle(m_title);
    }
    else{
        int i;
        for( i=0; i<pViewList->size(); i++)
            pViewList->at(i)->setWindowTitle(QString(m_title+":%1").arg(i));
    }
}

VirmacViewer* VirmacDocument::firstView()
{
    VirmacViewer* view = NULL;

    if(!pViewList->isEmpty())
        view = pViewList->first();

    return view;
}

bool VirmacDocument::isLastView() {
    return ((int) pViewList->count() == 1);
}


void VirmacDocument::updateAllViews(VirmacViewer *sender)
{
    for(int i = 0; i < pViewList->size(); i++)
    {
        static_cast<VirmacViewer*>(pViewList->at(i))->update(sender);
    }

}

int VirmacDocument::GetCurrentBlock() const
{
    return myCurrentBlock;
}

void VirmacDocument::SetCurrentBlock(int value)
{
    myCurrentBlock = value;
}

void VirmacDocument::setPathName(const QString &name)
{
    m_filename=name;
    m_title=QFileInfo(name).fileName();
}

const QString& VirmacDocument::pathName() const
{
    return m_filename;
}

void VirmacDocument::setTitle(const QString &title)
{
    m_title=title;
}

const QString &VirmacDocument::title() const
{
    return m_title;
}


void VirmacDocument::closeDocument()
{
    VirmacViewer *w;
    if(!isLastView())
    {
        for(int i = 0; i < pViewList->size(); i ++)
        {
            if(!pViewList->at(i)->close())
                break;
        }
    }
    if(isLastView())
    {
        w = pViewList->first();
        w->close();
    }
}

bool VirmacDocument::newDocument()
{
    /////////////////////////////////////////////////
    // TODO: Add your document initialization code here
    /////////////////////////////////////////////////
    modified=false;
    return true;
}

bool VirmacDocument::openDocument(const QString &filename, const char* /* format =0 */)
{

    QFile f( filename );
    if ( !f.open( QIODevice::ReadOnly ) )
        return false;
    /////////////////////////////////////////////////
    // TODO: Add your document opening code here
    /////////////////////////////////////////////////
    readGCode(filename);

    f.close();

    modified=false;
    m_filename=filename;
    m_title=filename;//QFileInfo(f).fileName();
    return true;
}

bool VirmacDocument::saveDocument(const QString &filename, const char * /*format =0*/)
{
    QFile f( filename );
    if ( !f.open( QIODevice::WriteOnly ) )
        return false;

    /////////////////////////////////////////////////
    // TODO: Add your document saving code here
    /////////////////////////////////////////////////

    f.close();

    modified=false;
    m_filename=filename;
    m_title=QFileInfo(f).fileName();
    return true;
}

void VirmacDocument::deleteContents()
{
    /////////////////////////////////////////////////
    // TODO: Add implementation to delete the document contents
    /////////////////////////////////////////////////

}

bool VirmacDocument::canCloseFrame(VirmacViewer* pFrame)
{
    if(!isLastView())
        return true;

    bool ret=false;
    if(isModified())
    {
        QString saveName;
        switch(QMessageBox::information(pFrame, title(), tr("The current file has been modified.\n"
                                                            "Do you want to save it?"),QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel ))
        {
        case QMessageBox::Yes:
            if(title().contains(tr("Untitled")))
            {
                saveName=QFileDialog::getSaveFileName(pFrame, "Save");
                if(saveName.isEmpty())
                    return false;
            }
            else
                saveName=pathName();

            if(!saveDocument(saveName))
            {
                switch(QMessageBox::critical(pFrame, tr("I/O Error !"), tr("Could not save the current document !\n"
                                                                           "Close anyway ?"),QMessageBox::Yes ,QMessageBox::No))

                {
                case QMessageBox::Yes:
                    ret=true;
                    break;
                case QMessageBox::No:
                    ret=false;
                    break;
                }
            }
            else
                ret=true;
            break;
        case QMessageBox::No:
            ret=true;
            break;
        case QMessageBox::Cancel:
        default:
            ret=false;
            break;
        }
    }
    else
        ret=true;

    return ret;
}

bool VirmacDocument::readGCode(const QString& fName)
{
    for(int i = 0; i < pViewList->count(); i++)
    {
        pViewList->at(i)->makeCurrent();
    }
    QApplication::setOverrideCursor( Qt::WaitCursor );
    if (!fName.isEmpty())
    {
        if(myPath == NULL)
        {
            myPath = new VToolPath(fName);
            if(myPath->IsDone())
            {
                if(!myCutter)
                {
                    myCutter = new MillingCutter;
                    dContext->Display(myCutter);
                }

                dContext->Display(myPath);
                myPathIter.SetList(myPath->myGCodeList);
                myPathIter.Init();
                m_bGCodeLoaded = true;
                myTotalBlocks = myPath->myGCodeList->GetCount();
                myTrail = new VToolTrail();
                dContext->Display(myTrail);
                HidePath(false);
                modified=false;
                m_filename=fName;
                m_title=fName;
                if(!myCutter)
                {
                    myCutter = new MillingCutter;
                    dContext->Display(myCutter);
                }

                for(int i = 0; i < pViewList->count(); i++)
                {
                    pViewList->at(i)->updateGL();
                }
            }
            else
            {
                (VirmacMainWin::getMainWindow())->slotEditGCode();
                myPath = NULL;
            }
        }
        else
        {
            myPath->SetFile(fName);
            myTrail->Nullify();
            if(myPath->IsDone())
            {
                myPathIter.SetList(myPath->myGCodeList);
                myPathIter.Init();
                m_bGCodeLoaded = true;
                dContext->RefreshVolume();
            }
            modified=false;
            m_filename=fName;
            m_title=fName;
            HidePath(false);
        }
    }
    QApplication::restoreOverrideCursor();
    return m_bGCodeLoaded;
}

#include "VStLObject.h"
#include "VStLReader.h"
bool VirmacDocument::readStLFile(const QString& fName)
{
    for(int i = 0; i < pViewList->count(); i++)
    {
        pViewList->at(i)->makeCurrent();
    }
    QApplication::setOverrideCursor( Qt::WaitCursor );
    if (!fName.isEmpty())
    {
        VStLReader* m_Reader = new VStLReader(fName.toLatin1());
        if(m_Reader->IsFileValid())
        {
            if(!myStLObj)
            {
                myStLObj = new VStLObject(m_Reader);
                dContext->Display(myStLObj);
                //myStLObj->SetMaterial(GOLD);
                m_bModelLoaded = true;
            }
            else
            {
                myStLObj->SetReader(m_Reader);
                //myStLObj->SetMaterial(GOLD);
                m_bModelLoaded = true;
                dContext->RefreshVolume();
            }
            for(int i = 0; i < pViewList->count(); i++)
            {
                pViewList->at(i)->updateGL();
            }
        }
        delete m_Reader;
    }
    QApplication::restoreOverrideCursor();
    return true;
}

#include <Triangle.h>
#include <Point3D.h>
//#include <Intersection.h>
extern int tri_tri_intersection_test_3d(double p1[3], double q1[3], double r1[3], 
double p2[3], double q2[3], double r2[3],
int * coplanar,
double source[3],double target[3]);
int VirmacDocument::AnimFunction()
{
    NCBlock aBloc;
    for(int pnt = 0; pnt < myPointsPerFrame; pnt++)
    {
        if(myPathIter.More())
        {
            myCurrentBlock++;
            aBloc = myPathIter.Current();
            myPathIter.Next();
            Point3D P(aBloc.X, aBloc.Y, aBloc.Z);
            myCutter->MoveTo(P);
            myCutter->Rotate(aBloc.A, aBloc.B, aBloc.C);
            myTrail->AddBlock(aBloc);
            blocString.sprintf("N%ld  G%.2d  X%0.3lf  Y%0.3lf  Z%0.3lf  A%0.3lf  B%0.3lf  C%0.3lf",
                               aBloc.N,aBloc.G,aBloc.X,aBloc.Y,aBloc.Z,aBloc.A,aBloc.B, aBloc.C);
            if(m_bCheckIntersection)//check intersection
            {
                // FIXME
                // 1) Make AABB of cutter at current block
                // 2) Sort model triangles lying in AABB
                // and store in model triangle list
                /*
                unsigned long i, j;
                for(i=0; i< 50; i++) // FIXME numTriangles of model
                {
                    for(j=0; j< 2336; j++) // FIXME numTriangles of cutter
                    {
                        double V1[] = {-100, 0, -10}, V2[] = {100, 0, -10}, V3[] = {0, 100, 10};
                        double P1[] = {-100, 0, 10}, P2[] = {100, 0, 10}, P3[] = {0, 100, -10};
                        double S[] = {0,0,0}, E[] = {0,0,0};
                        int ins = 0, coplanar = 0;
                        ins = tri_tri_intersection_test_3d(V1, V2, V3, P1, P2, P3, &coplanar, S, E);
                        // double d = sqrt(pow(E[0]-S[0], 2)+pow(E[1]-S[1], 2)+pow(E[2]-S[2], 2));
                        // fprintf(stderr, "ins = %d\tcoplanar = %d\tdist = %lf\n", ins, coplanar, d);
                    }
                }
                */
            }
            //end intersection
        }
    }

    VirmacMainWin* win = VirmacMainWin::getMainWindow();
    QProgressBar* pBar = win->getProgBar();
    pBar->setMaximum(myTotalBlocks);
    pBar->setValue(myCurrentBlock);

    qApp->processEvents();

    if(myPathIter.More())
        return 1;
    else
    {
        pBar->setValue(0);
        myCurrentBlock = 0;
        return -1;
    }
}

//helpers
void VirmacDocument::ShowPoints(const bool& flag)
{
    if(flag)
    {
        if(!myBlocPointList->IsEmpty())
            myBlocPointList->Clear();
        if(!mySelePointList->IsEmpty())
            mySelePointList->Clear();
        //POSITION pos = myPath->myGCodeList.GetHeadPosition();
        for(myPathIter.Init(); myPathIter.More(); myPathIter.Next())
        {
            NCBlock aBloc = myPathIter.Current();
            myBlocPointList->Append(aBloc);
        }

    }
    else
        myBlocPointList->Clear();
}

void VirmacDocument::ShowSelectedBloc(NCBlock& bloc)
{
    if(!mySelePointList->IsEmpty())
        mySelePointList->Clear();
    mySelePointList->Append(bloc);
}

void VirmacDocument::EraseSelectedBloc()
{
    if(!mySelePointList->IsEmpty())
        mySelePointList->Clear();
}
