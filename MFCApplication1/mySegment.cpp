#include "pch.h"
#include "mySegment.h"

IMPLEMENT_SERIAL(mySegment, myShape, 1)

mySegment::mySegment(const CPoint& start, const CPoint& end) :myShape(start, end)
{
}

void mySegment::draw(CDC* dc) const
{
	CPen pen(PS_SOLID, objThickness, objFrameColor);
	CPen* oldPen = dc->SelectObject(&pen);
	dc->MoveTo(start.x, start.y);
	dc->LineTo(end.x, end.y);
	dc->SelectObject(oldPen);
}

void mySegment::Serialize(CArchive& ar)
{
	myShape::Serialize(ar);
}

 bool mySegment::isInside(const CPoint& P)const
{
	 double mone = (end.y - start.y);
	 double mechane = (end.x - start.x);
	 double m = mone / mechane;
	 double n = start.y - (m * start.x);

	 if (P.y == m * P.x + n)
		 return true;
	 return false;
}