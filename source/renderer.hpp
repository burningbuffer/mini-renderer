#include <iostream>
#include "SDL.h"
#include "window.hpp"

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

private:
	window mWindow;
	
};