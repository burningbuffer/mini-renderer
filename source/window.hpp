#pragma once
#include <string>
#include "SDL.h"

class window
{
public:

	window();
	void initWindow(const char* iname, int IWIDTH, int IHEIGHT);
	SDL_Surface* getScreenSurface();

	void destroyWindow();

	int WIDTH = NULL;
	int HEIGHT = NULL;

	const char* name = "";

	SDL_Window* Window = NULL;
	SDL_Renderer* Renderer = NULL;
	SDL_Surface* screenSurface = NULL;
};