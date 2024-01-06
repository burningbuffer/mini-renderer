#include "renderer.hpp"

Renderer::Renderer()
{
	isRunning = true;
	mWindow.initWindow("Mini renderer", 800, 600);

	
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

void Renderer::Update()
{
}

void Renderer::Render()
{
	SDL_SetRenderDrawColor(mWindow.Renderer, 255, 0, 0, 255);
	SDL_RenderClear(mWindow.Renderer);

	SDL_RenderPresent(mWindow.Renderer);
}
