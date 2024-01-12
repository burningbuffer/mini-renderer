//#include <iostream>
#include "SDL.h"
#include "window.hpp"
#include "framebuffer.hpp"
#include "color_types.hpp"
#include <kma/kma.hpp>

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

	void ClearFrameBuffer(uint32_t Color);

	kma::vec3 vector3{1.0f,3.0f,2.0f};

private:
	window mWindow;
	SDL_Texture* texture = nullptr;
	FrameBuffer* frameBuffer = nullptr;

	float width;
	float height;
	
};