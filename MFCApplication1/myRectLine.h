#pragma once
#include "myRectangle.h"

class myRectLine:public myRectangle
{
public:
	DECLARE_SERIAL(myRectLine)

	myRectLine() {}
	myRectLine(const CPoint& start, const CPoint& end);
	virtual bool isInside(const CPoint& P)const;
	virtual void draw(CDC* dc)const;
	virtual void Serialize(CArchive& ar);
	virtual int getId() const { return 7; }
};

