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

// ListIteratorOfListOfNCBlock.h: interface for the CListIteratorOfListOfNCBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_LISTITERATOROFLISTOFNCBlock_H__7CFDA3D2_B226_49F6_9955_05E1A23506EA__INCLUDED_)
#define _LISTITERATOROFLISTOFNCBlock_H__7CFDA3D2_B226_49F6_9955_05E1A23506EA__INCLUDED_

#include "ListNodeOfNCBlock.h"
#include "ListOfNCBlock.h"

class ListIteratorOfListOfNCBlock
{
public:
	ListIteratorOfListOfNCBlock() {;}
	ListIteratorOfListOfNCBlock(ListOfNCBlock*);
	virtual ~ListIteratorOfListOfNCBlock();
	void SetList(ListOfNCBlock*);
	void Init();
	bool More() const;
	void Next();
	NCBlock Current() const;
	NCBlock ValueAt(const int index);
private:
	ListNodeOfNCBlock* curPtr;
	ListOfNCBlock* theList;
};

#endif // !defined(_LISTITERATOROFLISTOFNCBlock_H__7CFDA3D2_B226_49F6_9955_05E1A23506EA__INCLUDED_)
