//#include <iostream>
#include "SDL.h"
#include "window.hpp"
#include "framebuffer.hpp"
#include "color_types.hpp"
#include <vector>
#include <kma/kma.hpp>

#define N_POINTS (9 * 9 * 9)

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

	kma::vec2 Project(kma::vec3 Point);

private:
	window mWindow;
	SDL_Texture* texture = nullptr;
	FrameBuffer* frameBuffer = nullptr;

	float width;
	float height;

	kma::vec3 camPos{0.0f, 0.0f, -5.0f};
	kma::vec3 cubeRotation{0.0f, 0.0f, 0.0f};

	float FOVfactor = 500;

	kma::vec3 cubePoints[N_POINTS];
	kma::vec2 ProjectedPoints[N_POINTS];

};