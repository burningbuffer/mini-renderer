#include "framebuffer.hpp"

FrameBuffer::FrameBuffer(uint32_t* pixels, float width, float height) : pixels(pixels), width(width), height(height)
{
	numOfPixels = width * height;



}

void FrameBuffer::DrawPixel(int x, int y, uint32_t Color)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		int index = (width * y) + x;
		pixels[index] = Color;
	}
}



