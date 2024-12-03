#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "common.hpp"

struct FrameBuffer
{
	uint32* pixels;
	float numOfPixels;
	float width;
	float height;

	FrameBuffer(uint32* pixels, float width, float height);
	void DrawPixel(int x, int y, uint32 Color);
	void DrawLine(int x0, int y0, int x1, int y1, uint32 Color);
	void DrawLineDDA(int x0, int y0, int x1, int y1, uint32 Color);
	void DrawLineBresenham(int x0, int y0, int x1, int y1, uint32 Color);
	void DrawRect(int x, int y, int width, int height, uint32 color);
	void DrawTriangle(int x0, int y0,int x1,int y1, int x2, int y2, uint32 Color);
	void DrawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32 Color);
	void DrawFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32 Color);
	void DrawFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32 Color);
	void ClearFrameBuffer(uint32 Color);
};