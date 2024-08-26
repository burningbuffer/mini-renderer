#pragma once
#include <iostream>
#include <SDL2/SDL.h>

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
	void DrawTriangle(int x0, int y0,int x1,int y1, int x2, int y2, uint32_t Color);
	void DrawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t Color);
	void DrawFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t Color);
	void DrawFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t Color);
	void ClearFrameBuffer(uint32_t Color);
};