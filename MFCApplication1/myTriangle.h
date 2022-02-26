#pragma once
#include "myShape.h"


class myTriangle: public myShape
{
private:
	double area(const CPoint& start, const CPoint& end, const CPoint& midPoint) const;
public:
	DECLARE_SERIAL(myTriangle)

	myTriangle() {}
	myTriangle(const CPoint& start, const CPoint& end);
	virtual bool isInside(const CPoint& P)const;
	virtual void draw(CDC* dc)const;
	virtual void Serialize(CArchive& ar);
	virtual int getId() const { return 4; }
};

