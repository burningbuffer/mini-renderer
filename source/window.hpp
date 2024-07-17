#pragma once
#include <string>
#include "SDL.h"

class Window
{
public:

	Window();
	void ConfigWindow(const char* iname, int IWIDTH, int IHEIGHT);
	SDL_Texture* GetTexture();
	SDL_Renderer* GetRenderer();
	void DestroyWindow();

	int mWidth = NULL;
	int mHeight = NULL;

	const char* mName = "";

	SDL_Window* mWindow = NULL;
	SDL_Renderer* mRenderer = NULL;
	SDL_Texture* mTexture = NULL;
};