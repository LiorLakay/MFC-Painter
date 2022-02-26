#include "pch.h"
#include "myRectangle.h"

IMPLEMENT_SERIAL(myRectangle, myShape, 1)


myRectangle::myRectangle(const CPoint& start, const CPoint& end) :myShape(start, end)
{
}

void myRectangle::draw(CDC* dc) const
{
	CPen pen(PS_SOLID, objThickness, objFrameColor);
	CPen* oldPen = dc->SelectObject(&pen);
	CBrush brush(objBackColor);
	CBrush* oldBrush = dc->SelectObject(&brush);
	dc->Rectangle(start.x, start.y, end.x, end.y);
	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);
}


void myRectangle::Serialize(CArchive& ar)
{
	myShape::Serialize(ar);
}

bool myRectangle::isInside(const CPoint& P) const
{
	return (start.x <= P.x && P.x <= end.x || start.x >= P.x && P.x >= end.x) &&
		(start.y <= P.y && P.y <= end.y || start.y >= P.y && P.y >= end.y);
}