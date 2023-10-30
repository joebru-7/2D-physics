#pragma once
#include "SDL_rect.h"
#include <array>

struct FPoint;
struct Point : SDL_Point 
{
	Point operator+(const Point& other)const;
	Point& operator+=(const Point& other);
	Point operator-(const Point& other)const;
	Point& operator-=(const Point& other);
	explicit operator FPoint() const;
};

struct FPoint : SDL_FPoint
{
	FPoint operator+(const FPoint& other) const;
	FPoint operator+(const float other) const;
	FPoint& operator+=(const FPoint& other);

	FPoint operator*(const float)const;
	FPoint& operator*=(const float);

	FPoint operator-(const FPoint& other)const;
	FPoint& operator-=(const FPoint& other);
	explicit operator Point() const;
};

FPoint FromAngle(float angle, float length = 1);


struct FMatrix
{
	std::array<float,9> data;
	FMatrix() :data{} {};
	FMatrix(float angle, FPoint pos);

	//TODO optimize to Reference?
	FPoint operator*(const FPoint point)const;

};
