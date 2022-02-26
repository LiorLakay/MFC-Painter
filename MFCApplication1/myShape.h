#pragma once

class myShape :public CObject
{
public:
	static int thickness;
	static int fColor;
	static int bColor;
	CPoint start, end;
protected:
	int objThickness, objFrameColor, objBackColor;
public:
	myShape(){}
	myShape(const CPoint& start,const CPoint& end); 
	virtual ~myShape(){}
	virtual void draw( CDC* dc) const = 0;
	void setStart(const CPoint& start);
	void setEnd(const CPoint& end);
	CPoint getStart() const { return start; }
	CPoint getEnd()const { return end; }
	virtual void Serialize(CArchive& ar);
	virtual bool isInside(const CPoint& P) const=0;
	virtual int getId() const = 0;
	virtual COLORREF getFColor() const { return objFrameColor; }
	virtual COLORREF getBColor()const { return objBackColor; }
	virtual int getThickness()const { return objThickness; }
	virtual void setFColor(int fcolor) { objFrameColor = fcolor; }
	virtual void setBColor(int bcolor) { objBackColor = bcolor; }
	virtual void setThickness(int thickness) { objThickness = thickness; }
};