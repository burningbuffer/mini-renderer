#include <iostream>
#include "SDL.h"

struct FrameBuffer
{
	uint32_t* pixels;
	float numOfPixels;
	float width;
	float height;

	FrameBuffer(uint32_t* pixels, float width, float height);

};