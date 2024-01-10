#include "renderer.hpp"



Renderer::Renderer()
{
	isRunning = true;
	mWindow.initWindow("Mini renderer", 800, 600);
	width = mWindow.WIDTH;
	height = mWindow.HEIGHT;
	texture = mWindow.getScreenTexture();
	frameBuffer = new FrameBuffer(new uint32_t[width * height], width, height);

	Uint32* pixels = (Uint32*)frameBuffer->pixels;
}


Renderer::~Renderer(){}

void Renderer::Run()
{
	// struct buffer ?>??
	while (isRunning)
	{

		HandleEvents();
		Update();
		Render();
	}

	
}

void Renderer::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
		
		break;
	}
}

void Renderer::DrawPixel(int x, int y, uint32_t Color)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		int index = (width * y) + x;
		frameBuffer->pixels[index] = Color;
	}
}

void Renderer::ClearFrameBuffer(uint32_t Color)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = (width * y) + x;
			frameBuffer->pixels[index] = Color;
		}
	}

}

void Renderer::Update()
{
}

void Renderer::Render()
{


	DrawPixel(100, 100, 0xFF00FF00);
	DrawPixel(120, 120, 0xFF00FF00);
	DrawPixel(130, 130, 0xFF00FF00);
	DrawPixel(140, 140, 0xFF00FF00);
	DrawPixel(150, 150, 0xFF00FF00);


	SDL_UpdateTexture(
		texture,
		NULL,
		frameBuffer->pixels,
		(int)width * sizeof(uint32_t));

	SDL_RenderCopy(mWindow.Renderer, texture, NULL, NULL);




	//SDL_SetRenderDrawColor(mWindow.Renderer, 255, 0, 0, 255);
	//SDL_RenderClear(mWindow.Renderer);

	ClearFrameBuffer(0xFFFF0000);

	SDL_RenderPresent(mWindow.Renderer);
}