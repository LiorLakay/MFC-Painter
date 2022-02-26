#pragma once
#include "myShape.h"
class dragNrefill
{
public:
	dragNrefill(CTypedPtrArray<CObArray, myShape*> &shapes, myShape* s, myShape* last);
	virtual void perform(); 

private:
	CTypedPtrArray<CObArray, myShape*> &shapes;
	myShape* s;
	myShape* last;
};

