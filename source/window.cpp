#include "window.hpp"
#include <stdexcept>

Window::Window(){}

void Window::ConfigWindow(const char* iname, int IWIDTH, int IHEIGHT)
{
	mWidth = IWIDTH;
	mHeight = IHEIGHT;
	mName = iname;

	SDL_Init(SDL_INIT_VIDEO);

	mWindow = SDL_CreateWindow(mName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, SDL_WINDOW_SHOWN);
	
	if (!mWindow)
	{
		throw std::runtime_error("Failed to create SDL Window");
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
	
	if (!mRenderer)
	{
		throw std::runtime_error("Failed to create SDL Renderer");
	}
	
	mTexture = SDL_CreateTexture(mRenderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING, mWidth, mHeight);

	if (!mTexture)
	{
		throw std::runtime_error("Failed to create SDL Texture");
	}

}

SDL_Renderer* Window::GetRenderer()
{
	return mRenderer;
}

SDL_Texture* Window::GetTexture()
{
	return mTexture;
}

void Window::DestroyWindow()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
