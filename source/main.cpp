#include <iostream>
#include "SDL.h"


int main(int argsc, char *argv[])
{
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("SDL Window", 500, 200, 800, 600, SDL_WINDOW_SHOWN);
	screenSurface = SDL_GetWindowSurface(window);
	SDL_Delay(5000);
	SDL_FreeSurface(screenSurface);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}