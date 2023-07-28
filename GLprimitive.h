#ifndef GLPRIMITIVE_H
#define GLPRIMITIVE_H

/*
typedef struct PointStruct : public CObject{
	DECLARE_SERIAL(PointStruct);
	PointStruct();
	virtual ~PointStruct();

	float x{ 0 };
	float y{ 0 };
	float z{ 0 };

	void Serialize(CArchive& archive);
} point;
*/

class Point : public CObject {
public:
	Point();
	virtual ~Point();

	float getPointX() const;
	float getPointY() const;
	float getPointZ() const;

	void setPoint(float, float, float);

	void pushPoint(Point&);

	void operator=(const Point&);

private:
	float x{ 0 };
	float y{ 0 };
	float z{ 0 };
};


class Line : public CObject
{
public:
	Line();
	~Line();
	void pushPoint(Point&);

	float getLineX(int) const;
	float getLineY(int) const;
	float getLineZ(int) const;

	void createList();

	void operator=(const Line& old);

	int getCapacity() const;
private:
	int capacity{ 0 };
	Point* point{ new Point[capacity] };
};

#endif