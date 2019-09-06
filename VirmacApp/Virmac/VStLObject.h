//############################################################################

//  Author:	Sharjith Nair
//  Email:	sharjith_ssn@hotmail.com

// Program:	StereoLithography Data File Object

//							Important Notice:

//	This Idea and the Application is Copyright(c) Sharjith Nair 2002, 2003.
//	You can freely use it as long as you credit me for it.

//	No guarantee/warranty is given on this app and I will not be responsible 
//	for any damage to you, your property or any other person from using it.
//	USE IT ON YOUR OWN RISK.

//	Thankyou
//	Sharjith Nair.

//#############################################################################

// StlObject.h: interface for the CStLObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __STLOBJECT_H__
#define __STLOBJECT_H__

#include "VGLObject.h"
#include "VStLReader.h"
#include "ListOfPoint3D.h"
#include "ListIteratorOfListOfPoint3D.h"
#include "ListOfCTriFacet.h"
#include "ListOfOneAxis.h"
#include "ListIteratorOfListOfCTriFacet.h"
#include "ListIteratorOfListOfOneAxis.h"
#include "VGLOneAxis.h"
#include "TriFacet.h"

class VStLObject : public VGLObject
{
    public:
    VStLObject(){}
    VStLObject(VStLReader*);
    virtual ~VStLObject();
	virtual VGLObject* Copy() const;
	virtual void DefineDisplay();
	virtual void Display(const GLDisplayMode& = GLWIREFRAME);
	virtual void Hilight(const GLDisplayMode&);
	virtual void SetColor(const GLubyte&, const GLubyte&, const GLubyte&);
	virtual void GetColor(GLubyte*) const;
	void ShowNormals(const bool& flag) { m_bShowNormals = flag; }
    void SetReader(VStLReader*);
	void Nullify();
	bool IsNormalShown() const { return m_bShowNormals; }
    private:
	void DrawWired();
	void DrawShaded();
	void DrawBoundBox();
	void DrawNormals();
	void ComputePoints();
	void ComputeBoundLimits();
	void ComputeNormals(const int& size = 5);
	void InitDisplayLists();
    private:
    VStLReader *myReader;
	ListOfPoint3D* pointList;
	ListOfTriFacet* myFacetList;
	ListOfOneAxis* myNormalList;
	bool m_bShowNormals;
	int  facetList;
	int  normalList;
	int  bBoxList;
};

#endif
