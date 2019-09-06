// ToolTrail.h: interface for the CToolTrail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLTRAIL_H__7AE8B03E_0FCE_41DC_AC01_04E9C29E6B41__INCLUDED_)
#define AFX_TOOLTRAIL_H__7AE8B03E_0FCE_41DC_AC01_04E9C29E6B41__INCLUDED_

#include "VToolPath.h"
#include "ListIteratorOfListOfNCBlock.h"

class VToolTrail : public VToolPath
{
public:
    VToolTrail();
    virtual ~VToolTrail();
	virtual void DefineDisplay();
    virtual void Display(const GLDisplayMode& = GLWIREFRAME);
	virtual void DrawPath();
	VGLObject* Copy() const;
};

#endif // !defined(AFX_TOOLTRAIL_H__7AE8B03E_0FCE_41DC_AC01_04E9C29E6B41__INCLUDED_)
