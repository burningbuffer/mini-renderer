#include "framebuffer.hpp"

FrameBuffer::FrameBuffer(uint32_t* pixels, float width, float height) : pixels(pixels), width(width), height(height)
{
	numOfPixels = width * height;



}



