#pragma once
#include <string>
#include "SDL.h"

class Window
{
public:

	Window();
	void initWindow(const char* iname, int IWIDTH, int IHEIGHT);
	SDL_Texture* getScreenTexture();
	void destroyWindow();

	int WIDTH = NULL;
	int HEIGHT = NULL;

	const char* name = "";

	SDL_Window* SDLWindow = NULL;
	SDL_Renderer* Renderer = NULL;
	SDL_Texture* texture = NULL;
};