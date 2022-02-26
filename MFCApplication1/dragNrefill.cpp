#include "pch.h"
#include "dragNrefill.h"

dragNrefill::dragNrefill(CTypedPtrArray<CObArray, myShape*> &shapes, myShape* s, myShape* last)
	:shapes(shapes),s(s), last(last)
{
}


void dragNrefill::perform()
{
	for (int i = 0; i < shapes.GetSize(); ++i)
		if (shapes[i] == last)
		{
			shapes.RemoveAt(i);
			shapes.Add(s);
			return;
		}
}
