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

void FrameBuffer::DrawLine(int x0, int y0, int x1, int y1, uint32_t Color)
{
	for (float t = 0.; t < 1.; t += .01) {
		int x = (x1 - x0) * t + x0;
		int y = (y1 - y0) * t + y0;
		DrawPixel(x, y, Color);
	}
}

void FrameBuffer::DrawLineDDA(int x0, int y0, int x1, int y1, uint32_t Color)
{
	int DeltaX = (x1 - x0);
	int DeltaY = (y1 - y0);

	int SideLength = abs(DeltaX) >= abs(DeltaY) ? abs(DeltaX) : abs(DeltaY);

	float xinc = DeltaX / (float)SideLength;
	float yinc = DeltaY / (float)SideLength;

	float currX = x0;
	float currY = y0;

	for (int i = 0; i <= SideLength; i++)
	{
		DrawPixel(round(currX), round(currY), Color);
		currX += xinc;
		currY += yinc;
	}
}

void FrameBuffer::DrawLineBresenham(int x0, int y0, int x1, int y1, uint32_t Color)
{
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    float derror = std::abs(dy / float(dx));
    float error = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            DrawPixel(y, x, Color);
        }
        else {
            DrawPixel(x, y, Color);
        }
        error += derror;

        if (error > .5) {
            y += (y1 > y0 ? 1 : -1);
            error -= 1.;
        }
    }
}






