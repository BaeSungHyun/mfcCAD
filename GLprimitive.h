#ifndef GLPRIMITIVE_H
#define GLPRIMITIVE_H


typedef struct PointStruct{
	float x;
	float y;
	float z;
} point;


class Line
{
public:
	Line(int = 0);
	~Line();
	void pushPoint(point);

	float getLineX(int) const;
	float getLineY(int) const;
	float getLineZ(int) const;

	void operator=(const Line& old);

	size_t getCapacity() const;
private:
	size_t capacity{ 0 };
	point* Point;
};

#endif