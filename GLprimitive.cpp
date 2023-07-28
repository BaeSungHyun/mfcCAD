#include "pch.h"
#include "GLprimitive.h"
#include <gl/GL.h>
#include <gl/GLu.h>

/*
IMPLEMENT_SERIAL(PointStruct, CObject, 1);

PointStruct::PointStruct() {

}

PointStruct::~PointStruct() {
}

void PointStruct::Serialize(CArchive& archive) {
	// call base class function first
	// base class is CObject in this case
	CObject::Serialize(archive);

	// now do the stuff for our specific class
	if (archive.IsStoring()) {
		archive << x << y << z;
	}
	else {
		archive >> x >> y >> z;
	}
}

*/

Point::Point() {

}

Point::~Point() {
	
}

float Point::getPointX() const {
	return x;
}

float Point::getPointY() const {
	return y;
}

float Point::getPointZ() const {
	return z;
}

void Point::setPoint(float newX, float newY, float newZ) {
	x = newX;
	y = newY;
	z = newZ;
}


void Point::pushPoint(Point& inputPoint) {
	x = inputPoint.x;
	y = inputPoint.y;
	z = inputPoint.z;
}

void Point::operator=(const Point& old) {
	x = old.x;
	y = old.y;
	z = old.z;
}
 

Line::Line() {
}

Line::~Line() {
	delete[] point;
	point = nullptr;
}

void Line::pushPoint(Point& inputPoint) {
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

float Line::getLineX(int index) const {
	return point[index].getPointX();
}

float Line::getLineY(int index) const {
	return point[index].getPointY();
}

float Line::getLineZ(int index) const {
	return point[index].getPointZ();
}

void Line::createList() {
	::glBegin(GL_LINE_STRIP);
	for (int j = 0; j < capacity; ++j) {
		::glVertex3f(this->getLineX(j), this->getLineY(j), this->getLineZ(j));
	}
	::glEnd();
}

int Line::getCapacity() const {
	return capacity;
}

// I thought old.Point[j] wouldn't work because it's private member. 
// But I guess it's alright because it's inside the class definition.
// overlaod assignment operator for 'pointer member data'
void Line::operator=(const Line& old) {
	capacity = old.capacity;
	Point* temp2 = new Point[capacity];
	for (int j = 0; j < capacity; ++j) {
		temp2[j] = old.point[j];
	}
	delete[] point;
	point = temp2;
}
