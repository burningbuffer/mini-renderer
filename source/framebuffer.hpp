#include <iostream>
#include "SDL.h"

struct FrameBuffer
{
	uint32_t* pixels;
	float numOfPixels;
	float width;
	float height;

	FrameBuffer(uint32_t* pixels, float width, float height);
	void DrawPixel(int x, int y, uint32_t Color);
	void DrawLine(int x0, int y0, int x1, int y1, uint32_t Color);
	void DrawLineDDA(int x0, int y0, int x1, int y1, uint32_t Color);
	void DrawLineBresenham(int x0, int y0, int x1, int y1, uint32_t Color);
	void DrawRect(int x, int y, int width, int height, uint32_t color);
	void ClearFrameBuffer(uint32_t Color);



};