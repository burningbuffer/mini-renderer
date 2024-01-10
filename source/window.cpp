#include "window.hpp"
#include <stdexcept>

window::window(){}

void window::initWindow(const char* iname, int IWIDTH, int IHEIGHT)
{
	WIDTH = IWIDTH;
	HEIGHT = IHEIGHT;
	name = iname;

	SDL_Init(SDL_INIT_VIDEO);

	Window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	
	if (!Window)
	{
		throw std::runtime_error("Failed to create SDL Window");
	}
	
	Renderer = SDL_CreateRenderer(Window, -1, 0);
	
	if (!Renderer)
	{
		throw std::runtime_error("Failed to create SDL Renderer");
	}
	
	texture = SDL_CreateTexture(Renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,WIDTH,HEIGHT);

	if (!texture)
	{
		throw std::runtime_error("Failed to create SDL Texture");
	}

}

SDL_Texture* window::getScreenTexture()
{
	return texture;
}


void window::destroyWindow()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}
