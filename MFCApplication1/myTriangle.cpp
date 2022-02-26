#include "pch.h"
#include "myTriangle.h"

IMPLEMENT_SERIAL(myTriangle, myShape, 1)

myTriangle::myTriangle(const CPoint& start, const CPoint& end) :
	myShape(start, end)
{
}

void myTriangle::draw(CDC* dc)const
{
	CPen pen(PS_SOLID, objThickness, objFrameColor);
	CPen* oldPen = dc->SelectObject(&pen);
	CBrush brush(objBackColor);
	CBrush* oldBrush = dc->SelectObject(&brush);
	CPoint midPoint(start.x - (end.x - start.x), end.y);
	CPoint pointsArr[3] = { start,midPoint,end };
	dc->Polygon(pointsArr, 3);
	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);

}

bool myTriangle::isInside(const CPoint& point) const
{
	CPoint midPoint(start.x - (end.x - start.x), end.y);

	double A = area(start, midPoint, end);

	double A1 = area(point, midPoint, end);

	double A2 = area(start, point, end);
	
	double A3 = area(start, midPoint, point);

	return (A == A1 + A2 + A3);
}
double myTriangle::area(const CPoint& start, const CPoint& midPoint, const CPoint& end) const
{
	return abs((start.x * (midPoint.y - end.y) + midPoint.x * (end.y - start.y)
		+ end.x * (start.y - midPoint.y)) / 2.0);
}

void myTriangle::Serialize(CArchive& ar)
{
	myShape::Serialize(ar);
}