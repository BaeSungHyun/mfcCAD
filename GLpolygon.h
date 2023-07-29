#pragma once
#include <afx.h>

class Point;
class Line;

class GLpolygon : public CObject
{
public:
	GLpolygon();
	virtual ~GLpolygon();

	virtual void createList() = 0;
	virtual void pushPoint(Point&);

	virtual float getX(int) const;
	virtual float getY(int) const;
	virtual float getZ(int) const;

	virtual int getCapacity() const;
	virtual void setCapacity(int);

private:
	int capacity{0};
	Point* point{ new Point[capacity] };
};



class GLRectangle : public GLpolygon {
public:
	GLRectangle();
	~GLRectangle(); // override

	// void pushPoint(Point&); // override
	// int getCapacity; // override

	void createList(); // pure override

	// float getRectX(int) const; // override
	// float getRectY(int) const; // override
	// float getRectZ(int) const; // override

	void setSize(float, float);
	void setCenter(float, float, float);
	void setNormal(int axis); // x = 0; y = 1; z = 2;

	void setFourCorner(float x, float y, float z, float width, float height, int axis);
	

private:
	float center[3]{ 0,0,0 };
	float width{ 0 };
	float height{ 0 };
	int normalAxis;
};