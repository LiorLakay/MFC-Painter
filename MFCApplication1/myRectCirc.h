#pragma once
#include "myRectangle.h"

class myRectCirc: public myRectangle
{
public:
	DECLARE_SERIAL(myRectCirc)

	myRectCirc() {}
	myRectCirc(const CPoint& start, const CPoint& end);
	virtual bool isInside(const CPoint& P)const;
	virtual void draw(CDC* dc)const;
	virtual void Serialize(CArchive& ar);
	virtual int getId() const { return 6; }
};

