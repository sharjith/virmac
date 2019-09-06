// ToolPath.h: interface for the CToolPath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLPATH_H__2FDF44A6_B9C2_42B9_A928_97FC3C160AFE__INCLUDED_)
#define AFX_TOOLPATH_H__2FDF44A6_B9C2_42B9_A928_97FC3C160AFE__INCLUDED_

#include "VGLObject.h"
#include "NCBlock.h"
#include "ListOfNCBlock.h"
#include "ListIteratorOfListOfNCBlock.h"
#include "GCodeException.h"

#include <fstream>
#include <cstdio>
#include <qstring.h>

using namespace std;

class VToolPath : public VGLObject

{
    public:
    VToolPath();
    VToolPath(const QString& fName);
    VToolPath(const VToolPath& P);
    virtual ~VToolPath();
	virtual VGLObject* Copy() const;
	virtual void DefineDisplay();
	virtual void Display(const GLDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GLDisplayMode&);
    VToolPath operator = (const VToolPath& P);
	bool IsFileValid() const { return fileIsValid; }
	bool IsDone() const { return Done; }
	bool IsEmpty() const { return myGCodeList->IsEmpty(); }
	bool IsArcShown() const { return m_bShowArc; }

	void SetFile(const QString& fName);
	virtual bool AddBlock(NCBlock aBlock);
	virtual void Nullify();
	virtual void SetShowArc(const bool& flag) { m_bShowArc = flag; RefreshPath(); }
	virtual void SetG00Color(const GLubyte&, const GLubyte&, const GLubyte&);
	virtual void SetG01Color(const GLubyte&, const GLubyte&, const GLubyte&);
	virtual void SetG02Color(const GLubyte&, const GLubyte&, const GLubyte&);
	virtual void SetG03Color(const GLubyte&, const GLubyte&, const GLubyte&);
	virtual void SetTranslation(double X, double Y, double Z);
	virtual void SetScale(double X, double Y, double Z);
	virtual void SetRotation(double CX, double CY, double CZ, double RX, double RY, double RZ);

	virtual void GetTranslation(double& X, double& Y, double& Z);
	virtual void GetScale(double& X, double& Y, double& Z);
	virtual void GetRotation(double& CX, double& CY, double& CZ, double& RX, double& RY, double& RZ);
	QString GetError() const { return errString; }
	void SetBlockCount(const int& cnt) { blocCount = cnt; }
	int GetBlockCount() const { return blocCount; }
	void RefreshPath() { InitDisplayLists(); DefineDisplay(); }
	ListOfNCBlock* myGCodeList;
    protected:
	bool Read();
    protected:
	QString fileName;
	bool fileIsValid;

    protected:
	bool CheckSyntax(char str[]);
	bool SearchMultiple(char str[], char a);
	bool SearchVal(char str[], char a, double& val);
	bool SearchVal(char str[], char a, int& val);
    protected:
	virtual void DrawPath();
	virtual void ComputeBoundLimits();
	virtual void InitDisplayLists();
    protected:
	int blocCount;
	double n, m, pm;
	int maxFeed;
	double g,x,y,z,pn,pg,px,py,pz,brac,f,pf;
	double ra,rb,rc,pa,pb,pc, ri,rj,rk,pi,pj,pk ;
	FILE* fp;
	bool Done;
	G02_G03_Plane myArcPlane;
	bool m_bShowArc;

	GLint	pathList;
	GLubyte g00Red;
	GLubyte g00Green;
	GLubyte g00Blue;

	GLubyte g01Red;
	GLubyte g01Green;
	GLubyte g01Blue;

	GLubyte g02Red;
	GLubyte g02Green;
	GLubyte g02Blue;

	GLubyte g03Red;

	GLubyte g03Green;
	GLubyte g03Blue;

	QString errString;

	double m_dTransX;
	double m_dTransY;
	double m_dTransZ;

	double m_dScaleX;
	double m_dScaleY;
	double m_dScaleZ;

	double m_dRotCX;
	double m_dRotCY;
	double m_dRotCZ;

	double m_dRotRX;
	double m_dRotRY;
	double m_dRotRZ;
};

#endif // !defined(AFX_TOOLPATH_H__2FDF44A6_B9C2_42B9_A928_97FC3C160AFE__INCLUDED_)
