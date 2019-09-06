// StLReader.cpp: implementation of the CStLReader class.
//
//////////////////////////////////////////////////////////////////////

#include "VirmacMainWin.h"
#include "VStLReader.h"

#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VStLReader::VStLReader(const char* fName)
{
    fileIsValid = false;
    fileName = new char[strlen(fName)+1];
    strcpy(fileName, fName);
    pointList = new ListOfPoint3D;
    if(Read())
        fileIsValid = true;
}

VStLReader::~VStLReader()
{
    pointList->Clear();
    delete pointList;
    delete [] fileName;
}

VStLReader* VStLReader::Copy()
{
    VStLReader* R = new VStLReader();
    R->fileName = new char[strlen(fileName)+1];
    strcpy(R->fileName, fileName);
    R->fileIsValid = fileIsValid;
    ListIteratorOfListOfPoint3D it(pointList);
    for(it.Init(); it.More(); it.Next())
        R->pointList->Append(it.Current());
    return R;
}

bool VStLReader::Read()
{
    FILE* stlfp;
    int i=0,j=0,cnt=0 ,pCnt=4;
    char a[100];
    char str[40];
    double x=0,y=0,z=0;
    Point3D tPoint;
    int bCnt = 0;
    int totBlk = 0;
    QString pCent;
    QStatusBar* pStatusBar = ((VirmacMainWin*)VirmacMainWin::getMainWindow())->statusBar();
    QProgressBar* pProgBar = ((VirmacMainWin*)VirmacMainWin::getMainWindow())->progBar;

    //for progress bar step
    FILE* infile = fopen(fileName, "r");
    while(!feof(infile))
    {
        fgets(a ,100, infile);
        totBlk++;
    }
    pProgBar->setRange(0, totBlk);
    fclose(infile);


    stlfp = fopen(fileName,"r");
    if(!stlfp)
        return false;
    else
    {
        fscanf(stlfp,"%s",a);
        if (strcmp(a,"solid") != 0)
        {
            if(QMessageBox::critical(0, "Expected \"solid\" keyword", "StL Format Error", QMessageBox::Ok, 0, 0) == QMessageBox::Ok)
                return false;
        }
        do
        {
            bCnt++;
            i=0;
            cnt=0;
            fgets(a,100,stlfp);
            while(a[i]!='\0')
            {
                if(!islower((int)a[i]) && !isupper((int)a[i]) && a[i]!=' ')
                    break;
                cnt++;
                i++;
            }
            while(a[cnt]!='\0')
            {
                str[j]=a[cnt];
                cnt++;
                j++;
            }
            str[j]='\0';
            j=0;
            if(sscanf(str,"%lf%lf%lf",&x,&y,&z)==3)
            {
                tPoint.SetParam(x,y,z);
                pointList->Append(tPoint);
                pCnt++;
            }
            if(bCnt%100 == 0)
                pProgBar->setValue(bCnt);
        }while(!feof(stlfp));
        fclose(stlfp);
        pCent.sprintf("%d Triangles Processed", (pCnt/4));
        pStatusBar->showMessage(pCent);
        pProgBar->setValue(bCnt);
        pProgBar->reset();
        return true;
    }
}

