#include "pch.h"
#include "myRectCirc.h"

IMPLEMENT_SERIAL(myRectCirc, myRectangle, 1)


myRectCirc::myRectCirc(const CPoint& start, const CPoint& end) :myRectangle(start, end)
{
}

void myRectCirc::draw(CDC* dc) const
{
	myRectangle::draw(dc);
	CPen pen(PS_SOLID, objThickness, objFrameColor);
	CPen* oldPen = dc->SelectObject(&pen);
	CBrush brush(objBackColor);
	CBrush* oldBrush = dc->SelectObject(&brush);
	dc->Ellipse(start.x, start.y, end.x, end.y);
	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);
}


void myRectCirc::Serialize(CArchive& ar)
{
	myRectangle::Serialize(ar);
}

bool myRectCirc::isInside(const CPoint& P) const
{
	if (myRectangle::isInside(P) || (start.x <= P.x && P.x <= end.x || start.x >= P.x && P.x >= end.x) &&
		(start.y <= P.y && P.y <= end.y || start.y >= P.y && P.y >= end.y))
		return true;
	return false;

}