#pragma once
#include <glm/glm.hpp>
#include "color_types.hpp"

struct Triangle
{
	glm::vec2 Points[3];

	unsigned int TriangleColor;

	bool isClockwise();

};