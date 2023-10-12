#include "Point.h"
#include <cmath>

using std::sin, std::cos;

Point Point::operator+( const Point&b)const
{
	return {x+b.x,y+b.y};
}

Point& Point::operator+=(const Point& that)
{
	return *this = *this + that;
}

Point Point::operator-(const Point&b)const
{
	return { x - b.x,y - b.y };
}

Point& Point::operator-=(const Point& that)
{
	return *this = *this - that;
}

Point::operator FPoint() const
{
	return FPoint{ (float)x,(float)y };
}

FPoint FPoint::operator+(const FPoint& b)const
{
	return { x + b.x,y + b.y };
}

FPoint FPoint::operator+(const float other) const
{
	return {x+other,y+other};
}

FPoint& FPoint::operator+=(const FPoint& that)
{
	return *this = *this + that;
}

FPoint FPoint::operator*(const float f) const
{
	return {x*f,y*f};
}

FPoint FPoint::operator-(const FPoint& b)const
{
	return { x - b.x,y - b.y };
}

FPoint& FPoint::operator-=(const FPoint& that)
{
	return *this = *this - that;
}

FPoint::operator Point() const
{
	return Point{ (int)x,(int)y };
}


FMatrix::FMatrix(float angle, FPoint pos)
{
	float s = sin(angle);
	float c = cos(angle);
	float x = pos.x;
	float y = pos.y;
	data = {
		c, -s, x,
		s,  c, y,
		0,  0, 1
	};
}

FPoint FMatrix::operator*(const FPoint point)const
{
	return {
		data[0] * point.x + data[1] * point.y + data[2] * 1,
		data[3] * point.x + data[4] * point.y + data[5] * 1
	};
};

FPoint FromAngle(float angle, float length)
{
	return { length * sin(angle),length * -cos(angle) };
}
