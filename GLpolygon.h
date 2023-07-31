#ifndef GLPOLYGON_H
#define GLPOLYGON_H

#include <afx.h>
#include "GLprimitive.h"
#include <gl/GL.h>
#include <gl/GLU.h>


class GLpolygon : public CObject
{
public:
	friend class GLRectangle;

	GLpolygon();
	virtual ~GLpolygon();

	virtual void createList() = 0;
	virtual void pushPoint(Point&);
	virtual float getX(int) const;
	virtual float getY(int) const;
	virtual float getZ(int) const;

	virtual int getCapacity() const;
	virtual void setCapacity(int);
	virtual void setFaceMode(int, int);
	virtual void setColor(float[3]);
private:
	int capacity{0};
	Point* point{ new Point[capacity] };
	float color[3]{ 0.7f, 0.7f, 0.7f };
	GLenum face{ GL_FRONT_AND_BACK};
	GLenum mode{ GL_FILL};
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

	void operator=(const GLRectangle& old);
	

private:
	float center[3]{ 0,0,0 };
	float width{ 0 };
	float height{ 0 };
	int normalAxis{ 0 };
};

#endif