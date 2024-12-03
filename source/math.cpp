#include "math.hpp"

glm::vec4 Project(glm::vec4 v, glm::mat4 proj) {
    glm::vec4 res = proj * v;

    if (res.w != 0.0) {
        res.x /= res.w;
        res.y /= res.w;
        res.z /= res.w;
    }

    return res;
}

void clamp(float& number, int min, int max)
{
    if (number < min) number = min;
    if (number > max) number = max;
}


uint32 ApplyLightIntensity(uint32 original_color, float percentage_factor) {

    clamp(percentage_factor, 0.0f, 1.0f);

    uint32 a = (original_color & 0xFF000000);
    uint32 r = static_cast<uint32>((original_color & 0x00FF0000) * percentage_factor);
    uint32 g = static_cast<uint32>((original_color & 0x0000FF00) * percentage_factor);
    uint32 b = static_cast<uint32>((original_color & 0x000000FF) * percentage_factor);

    uint32 new_color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);

    return new_color;
}
