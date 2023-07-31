#include "pch.h"
#include "GLpolygon.h"


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

void GLpolygon::setFaceMode(int face, int mode) {
	switch (face) {
	case 0:
		this->face = GL_FRONT;
		break;
	case 1:
		this->face = GL_BACK;
		break;
	case 2:
		this->face = GL_FRONT_AND_BACK;
		break;
	}

	switch (mode) {
	case 0:
		this->mode = GL_POINT;
		break;
	case 1:
		this->mode = GL_LINE;
		break;
	case 2:
		this->mode = GL_FILL;
		break;
	}
}

void GLpolygon::setColor(float color[3]) {
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
}
// **************************************** // 

GLRectangle::GLRectangle() {
	
}

GLRectangle::~GLRectangle() {
	GLpolygon::~GLpolygon();
}

void GLRectangle::createList() {
	::glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,color);
	::glPolygonMode(face, mode);
	::glBegin(GL_QUADS);
	for (int j = 0; j < capacity; ++j) {
		::glVertex3f(this->getX(j), this->getY(j), this->getZ(j));
	}
	::glEnd();
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
			if (i == 0) {
				newPoint.setPoint(x + width / 2, y + height / 2, z);
				pushPoint(newPoint);
			}
			else if (i == 1) {
				newPoint.setPoint(x + width / 2, y - height / 2, z);
				pushPoint(newPoint);
			}
			else if (i == 2) {
				newPoint.setPoint(x - width / 2, y - height / 2, z);
				pushPoint(newPoint);
			}
			else {
				newPoint.setPoint(x - width / 2, y + height / 2, z);
				pushPoint(newPoint);
			}
		}
		break;
	}
	case 1: {
		for (int i = 0; i < 4; ++i) {
			Point newPoint;
			if (i == 0) {
				newPoint.setPoint(x, y + height / 2, z + width / 2);
				pushPoint(newPoint);
			}
			else if (i == 1) {
				newPoint.setPoint(x, y - height / 2, z + width / 2);
				pushPoint(newPoint);
			}
			else if (i == 2) {
				newPoint.setPoint(x, y - height / 2, z - width / 2);
				pushPoint(newPoint);
			}
			else {
				newPoint.setPoint(x, y + height / 2, z - width / 2);
				pushPoint(newPoint);
			}
		}

		break;
	}
	case 2: {
		for (int i = 0; i < 4; ++i) {
			Point newPoint;
			if (i == 0) {
				newPoint.setPoint(x + width / 2, y, z + height / 2);
				pushPoint(newPoint);
			}
			else if (i == 1) {
				newPoint.setPoint(x - width / 2, y, z + height / 2);
				pushPoint(newPoint);
			}
			else if (i == 2) {
				newPoint.setPoint(x - width / 2, y, z - height / 2);
				pushPoint(newPoint);
			}
			else {
				newPoint.setPoint(x + width / 2, y, z - height / 2);
				pushPoint(newPoint);
			}
		}

		break;
	}
	}

	setCapacity(4);
}

void GLRectangle::operator=(const GLRectangle& old) {
	setCapacity(old.getCapacity());

	Point* temp2 = new Point[getCapacity()];	

	for (int j = 0; j < getCapacity(); ++j) {
		temp2[j] = old.point[j];
	}
	delete[] this->point;
	this->point = temp2;
}