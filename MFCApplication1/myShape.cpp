#include "pch.h"
#include <iostream>
using namespace std;
#include "myShape.h"


int myShape::thickness = 2;
int myShape::fColor = 0;
int myShape::bColor = RGB(255, 255, 255);

myShape::myShape(const CPoint& start, const CPoint& end)
{
	setStart(start);
	setEnd(end);
	objThickness = thickness;
	objFrameColor = fColor;
	objBackColor = bColor;
}

void myShape::setStart(const CPoint& start)
{
	 this->start = start; 
}

void myShape::setEnd(const CPoint& end)
{
	this->end = end;
}


void myShape::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << start;
		ar << end;
		ar << objThickness << objFrameColor << objBackColor;
	}
	else 
	{
		ar >> start;
		ar >> end;
		ar >> objThickness >> objFrameColor >> objBackColor;
	}
}