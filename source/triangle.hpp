#pragma once
#include <kma/kma.hpp>

struct Triangle
{
	kma::vec2 Points[3];

	bool isClockwise();

};