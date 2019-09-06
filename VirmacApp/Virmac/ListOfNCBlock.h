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

// ListOfNCBlock.h: interface for the CListOfNCBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_LISTOFNCBlock_H__64FE1368_B1AF_44CF_8FFF_9382221176C2__INCLUDED_)
#define _LISTOFNCBlock_H__64FE1368_B1AF_44CF_8FFF_9382221176C2__INCLUDED_

#include "ListNodeOfNCBlock.h"

class NCBlock;
class ListIteratorOfListOfNCBlock;

class ListOfNCBlock
{
	friend class ListIteratorOfListOfNCBlock;
public:
	ListOfNCBlock();
	virtual ~ListOfNCBlock();
	void Append(const NCBlock& data);
	void Prepend(const NCBlock& data);
	NCBlock First() const;
    NCBlock& First();
	NCBlock Last() const;
    NCBlock& Last();
	bool IsEmpty() const;
	void Clear();
    int GetCount() const;

private:
    ListNodeOfNCBlock* firstPtr;
	ListNodeOfNCBlock* lastPtr;

    int count;
private:
	ListNodeOfNCBlock* NewNode(const NCBlock&);
};

#endif // !defined(_LISTOFNCBlock_H__64FE1368_B1AF_44CF_8FFF_9382221176C2__INCLUDED_)
