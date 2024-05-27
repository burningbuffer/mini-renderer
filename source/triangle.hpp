#pragma once
#include <kma/kma.hpp>
#include "color_types.hpp"

struct Triangle
{
	kma::vec2 Points[3];

	unsigned int TriangleColor;

	bool isClockwise();

};