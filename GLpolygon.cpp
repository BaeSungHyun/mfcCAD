#include "pch.h"
#include "GLpolygon.h"
#include "GLprimitive.h"

GLpolygon::GLpolygon() {

}

GLpolygon::~GLpolygon() {
	delete[] point;
	point = nullptr;
}

int GLpolygon::getCapacity() const {
	return capacity;
}

void GLpolygon::setCapacity(int step) {
	capacity += step;
}


void GLpolygon::pushPoint(Point& inputPoint) {
	Point* temp = new Point[capacity + 1];
	for (int i = 0; i < capacity; ++i) {
		temp[i].pushPoint(point[i]);
	}
	// capacity equal 1 in here so no worries
	temp[capacity].pushPoint(inputPoint);
	delete[] point;
	point = temp;

	++capacity;
}

float GLpolygon::getX(int index) const {
	return point[index].getPointX();
}

float GLpolygon::getY(int index) const {
	return point[index].getPointY();
}
float GLpolygon::getZ(int index) const {
	return point[index].getPointZ();
}

// **************************************** // 

GLRectangle::GLRectangle() {
	
}

GLRectangle::~GLRectangle() {
	GLpolygon::~GLpolygon();
}

void GLRectangle::setSize(float width, float height) {
	this->width = width;
	this->height = height;
}

void GLRectangle::setCenter(float x, float y, float z) {
	center[0] = x;
	center[1] = y;
	center[2] = z;
}

void GLRectangle::setNormal(int axis) { // x = 0; y = 1; z = 2
	// x + y + z == 0 -> check in Dialog Box (RectangleDialog)
	normalAxis = axis;
}

void GLRectangle::setFourCorner(float x, float y, float z, float width, float height, int axis) {
	// only when center, width, height, normal is decided -> check in dialogBox 
	setSize(width, height);
	setCenter(x, y, z);
	setNormal(axis);

	switch (normalAxis) {
	case 0: {
		for (int i = 0; i < 4; ++i) {
			Point newPoint;
			if (i == 0)
				newPoint.setPoint(x + width / 2, y + height / 2, z);
			else if (i == 1)
				newPoint.setPoint(x + width / 2, y - height / 2, z);
			else if (i == 2)
				newPoint.setPoint(x - width / 2, y - height / 2, z);
			else
				newPoint.setPoint(x - width / 2, y + height / 2, z);
		}

		break;
	}
	case 1: {
		for (int i = 0; i < 4; ++i) {
			Point newPoint;
			if (i == 0)
				newPoint.setPoint(x, y + height / 2, z + width / 2);
			else if (i == 1)
				newPoint.setPoint(x, y - height / 2, z + width / 2);
			else if (i == 2)
				newPoint.setPoint(x, y - height / 2, z - width / 2);
			else
				newPoint.setPoint(x, y + height / 2, z - width / 2);
		}

		break;
	}
	case 2: {
		for (int i = 0; i < 4; ++i) {
			Point newPoint;
			if (i == 0)
				newPoint.setPoint(x + width / 2, y, z + height / 2);
			else if (i == 1)
				newPoint.setPoint(x - width / 2, y, z + height / 2);
			else if (i == 2)
				newPoint.setPoint(x - width / 2, y, z - height / 2);
			else
				newPoint.setPoint(x + width / 2, y, z - height / 2);
		}

		break;
	}
	}

	setCapacity(4);
}