#include "pch.h"
#include "myCircle.h"

IMPLEMENT_SERIAL(myCircle, myShape, 1)

myCircle::myCircle(const CPoint& start, const CPoint& end) :myShape(start, end)
{
}

void myCircle::draw(CDC* dc) const
{
	CPen pen(PS_SOLID, objThickness, objFrameColor);
	CPen* oldPen = dc->SelectObject(&pen);
	CBrush brush(objBackColor);
	CBrush* oldBrush = dc->SelectObject(&brush);
	dc->Ellipse(start.x, start.y, end.x, end.y);
	dc->SelectObject(oldBrush);
	dc->SelectObject(oldPen);
}

void myCircle::Serialize(CArchive& ar)
{
	myShape::Serialize(ar);
}

bool myCircle::isInside(const CPoint& P) const
{
	return (start.x <= P.x && P.x <= end.x || start.x >= P.x && P.x >= end.x) &&
		(start.y <= P.y && P.y <= end.y || start.y >= P.y && P.y >= end.y);
}