#pragma once
#include "Point.h"
#include "Drawable.h"
struct Hit
{
	FPoint location;
	const Drawable* object1;
	const FPoint* segment1;
	const Drawable* object2;
	const FPoint* segment2;

};

