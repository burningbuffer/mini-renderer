//#include <iostream>
#include "SDL.h"
#include "window.hpp"
#include "framebuffer.hpp"
#include "color_types.hpp"
#include "mesh.hpp"
#include <vector>
#include <kma/kma.hpp>

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)

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

	window mWindow;
	SDL_Texture* texture = nullptr;
	FrameBuffer* frameBuffer = nullptr;

	float width = NULL;
	float height = NULL;

	int previousFrameTime = 0;

	kma::vec3 camPos{0.0f, 0.0f, -5.0f};
	kma::vec3 cubeRotation{0.0f, 0.0f, 0.0f};

	const float FOVfactor = 800;

	Mesh* cube; 
	int NumOfFaces = 0;
	triangle* TrianglesToRender;
};