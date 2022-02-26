#include "pch.h"
#include "myRectLine.h"


IMPLEMENT_SERIAL(myRectLine, myRectangle, 1)


myRectLine::myRectLine(const CPoint& start, const CPoint& end) :myRectangle(start, end)
{
}

void myRectLine::draw(CDC* dc) const
{
	myRectangle::draw(dc);
	CPen pen(PS_SOLID, objThickness, objFrameColor);
	CPen* oldPen = dc->SelectObject(&pen);
	CBrush brush(objBackColor);
	CBrush* oldBrush = dc->SelectObject(&brush);
	dc->MoveTo(start.x, start.y);
	dc->LineTo(end.x, end.y);
	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);
}

bool myRectLine::isInside(const CPoint& P)const
{
	if (myRectangle::isInside(P))
		return true;
	return false;
}

void myRectLine::Serialize(CArchive& ar)
{
	myRectangle::Serialize(ar);
}





