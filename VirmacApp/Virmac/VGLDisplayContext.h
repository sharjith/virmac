//############################################################################

//  Author:	Sharjith Naramparambath
//  Email:	sharjith_ssn@hotmail.com

// Program:	OpenGL, C++ NC Tool Simulation Application

//							Important Notice:

//	This Idea and the Application is Copyright(c) Sharjith Naramparambath 2002, 2003.
//	You can freely use it as long as you credit me for it.

//	No guarantee/warranty is given on this app and I will not be responsible 
//	for any damage to you, your property or any other person from using it.
//	USE IT ON YOUR OWN RISK.

//	Thankyou
//	Sharjith Naramparambath.

//#############################################################################

// GLDisplayContext.h: interface for the CGLDisplayContext class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLDISPLAYCONTEXT_H__D04FD53F_4852_4D6C_957A_44E8AE0C54DB__INCLUDED_)
#define AFX_GLDISPLAYCONTEXT_H__D04FD53F_4852_4D6C_957A_44E8AE0C54DB__INCLUDED_

#include "ListOfVGLObject.h"
#include "ListIteratorOfListOfVGLObject.h"
#include "VGLObject.h"
#include "BoundingBox.h"
#include "VirmacGLView.h"
#include "VirmacDocument.h"

class VirmacGLView;
class VirmacDocument;

class VGLDisplayContext
{
public:
    VGLDisplayContext();
    VGLDisplayContext(VirmacDocument* pDoc);
    virtual ~VGLDisplayContext();
	void Display(VGLObject*);
	void Erase(VGLObject*);
	void DisplayAll();
	void DisplaySelected();
	void EraseAll();
	void EraseSelected();
	void DeleteAll();
	void DeleteSelected();
	void DeletePoints();
	void Render(const GLDisplayMode& = GLWIREFRAME);
	bool Select(VirmacGLView* aView, const int& x, const int& y);
	bool MultiSelect(VirmacGLView* aView, const int& x, const int& y);
	bool SweepSelect(VirmacGLView* aView, const QRect& swRect);
	bool IsEmpty() const;
	bool IsDisplayed(const VGLObject*) const;
	bool IsErased(const VGLObject*) const;
	bool IsSelected(const VGLObject*) const;
	bool IsAllDisplayed() const;
	bool IsAllErased() const;
	bool HasSelected() const;
	void InitSelected() const;
	bool MoreSelected() const;
	void NextSelected() const;
	VGLObject* CurrentSelected() const;
	BoundingBox GetBoundingBox() const { return viewBox; }
	void SetSensitivity(const int& s) { mouseSensitivity = s; }
	void RefreshVolume();
private:
	void AddToSelection(const VGLObject* O);
	void RemoveSelection(const VGLObject* O);
	void EmptySelection();
private:
	ListOfVGLObject* display;
	ListOfVGLObject* erase;
	ListOfVGLObject* select;
	mutable ListIteratorOfListOfVGLObject selListIter;
	VirmacDocument* ptrDoc;
	BoundingBox viewBox;
	int mouseSensitivity; //for selection;
};

#endif // !defined(AFX_GLDISPLAYCONTEXT_H__D04FD53F_4852_4D6C_957A_44E8AE0C54DB__INCLUDED_)
