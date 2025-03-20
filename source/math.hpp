#pragma once
#include <glm/glm.hpp>
#include "common.hpp"

glm::vec4 Project(glm::vec4 v, glm::mat4 proj);
void Clamp(float number, int min, int max);
uint32 ApplyLightIntensity(uint32 original_color, float percentage_factor);