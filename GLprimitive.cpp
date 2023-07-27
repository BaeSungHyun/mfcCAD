#include "pch.h"
#include "GLprimitive.h"

Line::Line(int cap) {
		Point = new point[cap];
		capacity = cap;
}

Line::~Line() {
	delete[] Point;
	Point = nullptr;
}

void Line::pushPoint(point inputPoint) {
	point* temp = new point[capacity + 1];
	for (size_t i = 0; i < capacity; ++i) {
		temp[i] = Point[i];
	}
	temp[capacity] = inputPoint;
	delete[] Point;
	Point = temp;

	++capacity;
}

float Line::getLineX(int index) const {
	return Point[index].x;
}

float Line::getLineY(int index) const {
	return Point[index].y;
}

float Line::getLineZ(int index) const {
	return Point[index].z;
}

size_t Line::getCapacity() const {
	return capacity;
}

// I thought old.Point[j] wouldn't work because it's private member. 
// But I guess it's alright because it's inside the class definition.
void Line::operator=(const Line& old) {
	capacity = old.capacity;
	point* temp2 = new point[capacity];
	for (size_t j = 0; j < capacity; ++j) {
		temp2[j] = old.Point[j];
	}
	delete[] Point;
	Point = temp2;
}