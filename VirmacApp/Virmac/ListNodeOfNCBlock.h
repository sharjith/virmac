//############################################################################

//  Author:	Sharjith Nair
//  Email:	sharjith_ssn@hotmail.com

// Program:	OpenGL, C++ QT Surface Modeler Demo Application

//							Important Notice:

//	This Idea and the Application is Copyright(c) Sharjith Nair 2002, 2003.
//	You can freely use it as long as you credit me for it.

//	No guarantee/warranty is given on this app and I will not be responsible 
//	for any damage to you, your property or any other person from using it.
//	USE IT ON YOUR OWN RISK.

//	Thankyou
//	Sharjith Nair.

//#############################################################################

// ListNodeOfNCBlock.h: interface for the CListNodeOfNCBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_LISTNODEOFNCBlock_H__0206868D_2E9C_40D2_AB3E_AD8990AA5941__INCLUDED_)
#define _LISTNODEOFNCBlock_H__0206868D_2E9C_40D2_AB3E_AD8990AA5941__INCLUDED_

#include "NCBlock.h"

class NCBlock;
class ListOfNCBlock;

class ListNodeOfNCBlock
{
	friend class ListOfNCBlock;
    friend class ListIteratorOfListOfNCBlock;
public:
    ListNodeOfNCBlock(const NCBlock&);
    NCBlock GetData() const;
    virtual ~ListNodeOfNCBlock();
    bool operator==(const ListNodeOfNCBlock& rhs);
    bool operator!=(const ListNodeOfNCBlock& rhs);
private:
    NCBlock data;
    ListNodeOfNCBlock* nextPtr;

};

#endif // !defined(_LISTNODEOFNCBlock_H__0206868D_2E9C_40D2_AB3E_AD8990AA5941__INCLUDED_)
