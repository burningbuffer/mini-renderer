#include "triangle.hpp"

bool Triangle::isClockwise()
{
	auto ax = Points[0].x - Points[1].x;
	auto ay = Points[0].y - Points[1].y;
	auto bx = Points[0].x - Points[2].x;
	auto by = Points[0].y - Points[2].y;
	auto order = ax * by - ay * bx;
	return order < 0;
}
