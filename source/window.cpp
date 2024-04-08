#include "window.hpp"
#include <stdexcept>

Window::Window(){}

void Window::initWindow(const char* iname, int IWIDTH, int IHEIGHT)
{
	WIDTH = IWIDTH;
	HEIGHT = IHEIGHT;
	name = iname;

	SDL_Init(SDL_INIT_VIDEO);

	SDLWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	
	if (!SDLWindow)
	{
		throw std::runtime_error("Failed to create SDL Window");
	}
	
	Renderer = SDL_CreateRenderer(SDLWindow, -1, 0);
	
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

SDL_Texture* Window::getScreenTexture()
{
	return texture;
}


void Window::destroyWindow()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(SDLWindow);
	SDL_Quit();
}
