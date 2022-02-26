#pragma once
#include "myShape.h"

class mySegment : public myShape
{
public:
	DECLARE_SERIAL(mySegment)

	mySegment(){}
	mySegment(const CPoint& start, const CPoint& end);
	virtual bool isInside(const CPoint& P)const;
	virtual void draw( CDC* dc)const;
	virtual void Serialize(CArchive& ar);
	virtual int getId() const { return 1; }
};

