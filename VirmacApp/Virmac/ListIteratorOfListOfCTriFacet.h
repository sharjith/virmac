//############################################################################

//  Author:	Sharjith Nair
//  Email:	sharjith_ssn@hotmail.com

// Program:	Geometric Class Library

//							Important Notice:

//	This Idea and the Application is Copyright(c) Sharjith Nair 2002, 2003.
//	You can freely use it as long as you credit me for it.

//	No guarantee/warranty is given on this app and I will not be responsible 
//	for any damage to you, your property or any other person from using it.
//	USE IT ON YOUR OWN RISK.

//	Thankyou
//	Sharjith Nair.

//#############################################################################

// ListIteratorOfListOfCTriFacet.h: interface for the CListIteratorOfListOfCTriFacet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_LISTITERATOROFLISTOFCTriFacet_H__7CFDA3D2_B226_49F6_9955_05E1A23506EA__INCLUDED_)
#define _LISTITERATOROFLISTOFCTriFacet_H__7CFDA3D2_B226_49F6_9955_05E1A23506EA__INCLUDED_

#include "ListNodeOfCTriFacet.h"
#include "ListOfCTriFacet.h"

class ListIteratorOfListOfTriFacet
{
public:
	ListIteratorOfListOfTriFacet() {;}
	ListIteratorOfListOfTriFacet(ListOfTriFacet*);
	virtual ~ListIteratorOfListOfTriFacet();
	void SetList(ListOfTriFacet*);
	void Init();
	bool More() const;
	void Next();
	TriFacet Current() const;
	TriFacet ValueAt(const int index);
private:
	ListNodeOfTriFacet* curPtr;
	ListOfTriFacet* theList;
};

#endif // !defined(_LISTITERATOROFLISTOFCTriFacet_H__7CFDA3D2_B226_49F6_9955_05E1A23506EA__INCLUDED_)
