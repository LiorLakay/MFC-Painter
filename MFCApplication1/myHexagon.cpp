#include "pch.h"
#include "myHexagon.h"

IMPLEMENT_SERIAL(myHexagon, myShape, 1)

myHexagon::myHexagon(const CPoint& start, const CPoint& end) :
	myShape(start, end)
{
}

CPoint* myHexagon::createPtsArr(const CPoint& start, const CPoint& end) const
{
	double side, h, r;

	side = start.x - end.x;
	h = side * sin(60 * PI / 180);
	r = side * cos(60 * PI / 180);

	double x = start.x;
	double y = start.y;

	CPoint pointsArr[6];

	pointsArr[0].x = x;
	pointsArr[0].y = y;

	pointsArr[1].x = x + side;
	pointsArr[1].y = y;

	pointsArr[2].x = x + side + r;
	pointsArr[2].y = y - h;

	pointsArr[3].x = x + side;
	pointsArr[3].y = y - (2 * h);

	pointsArr[4].x = x;
	pointsArr[4].y = y - (2 * h);

	pointsArr[5].x = x - r;
	pointsArr[5].y = y - h;

	return pointsArr;
}
void myHexagon::draw(CDC* dc) const
{

	CPen pen(PS_SOLID, objThickness, objFrameColor);
	CPen* oldPen = dc->SelectObject(&pen);
	CBrush brush(objBackColor);
	CBrush* oldBrush = dc->SelectObject(&brush);
	CPoint* pointsArr = createPtsArr(start, end);

	dc->Polygon(pointsArr, 6);
	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);

}

bool myHexagon::isInside(const CPoint& P) const
{
	CPoint* pointsArr = createPtsArr(start, end);

	BOOL c = FALSE;
	for (int i = 0, j = 5; i < 6; j = i++)
	{
		if (((pointsArr[i].y > P.y) != (pointsArr[j].y > P.y))
			&& (P.x < (pointsArr[j].x - pointsArr[i].x) * (P.y - pointsArr[i].y) / (pointsArr[j].y - pointsArr[i].y) + pointsArr[i].x))
			c = !c;
	}
	return c;
}



void myHexagon::Serialize(CArchive& ar)
{
	myShape::Serialize(ar);
}

