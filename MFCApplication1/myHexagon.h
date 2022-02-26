#pragma once
#include "myShape.h"
#define PI 3.14159265
class myHexagon:public myShape
{
public:
	DECLARE_SERIAL(myHexagon)

	myHexagon() {}
	myHexagon(const CPoint& start, const CPoint& end);
	virtual void draw(CDC* dc) const;
	virtual void Serialize(CArchive& ar);
	virtual int getId() const { return 5; }
	virtual bool isInside(const CPoint& point) const;

private:
	CPoint* createPtsArr(const CPoint& start, const CPoint& end)const;
};

