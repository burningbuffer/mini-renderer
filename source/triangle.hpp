#pragma once
#include <glm/glm.hpp>
#include "common.hpp"

struct Triangle
{
	glm::vec2 Points[3];
	uint32 TriangleColor;

	bool isClockwise();
};