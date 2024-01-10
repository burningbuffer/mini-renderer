#include <iostream>
#include "SDL.h"
#include "window.hpp"
#include "framebuffer.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Run();

	bool isRunning = false;

	void HandleEvents();
	void Update();
	void Render();

	void DrawPixel(int x, int y, uint32_t Color);
	void ClearFrameBuffer(uint32_t Color);

private:
	window mWindow;
	SDL_Texture* texture = nullptr;
	FrameBuffer* frameBuffer = nullptr;

	float width;
	float height;
	
};