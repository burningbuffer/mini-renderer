#include "renderer.hpp"



Renderer::Renderer()
{
	isRunning = true;
	mWindow.initWindow("Mini renderer", 800, 600);
	width = mWindow.WIDTH;
	height = mWindow.HEIGHT;
	texture = mWindow.getScreenTexture();
	frameBuffer = new FrameBuffer(new uint32_t[width * height], width, height);


	int pointCount = 0;
	for (float x = -1; x <= 1; x += 0.25)
	{
		for (float y = -1; y <= 1; y += 0.25)
		{
			for (float z = -1; z <= 1; z += 0.25)
			{
				kma::vec3 newPoint{x,y,z};
				cubePoints[pointCount++] = newPoint;
			}
		}
	}

}


Renderer::~Renderer(){}

void Renderer::Run()
{
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
	cubeRotation.y += 0.001f;
	cubeRotation.z += 0.011f;
	cubeRotation.x += 0.000f;

	for (int i=0;i<(N_POINTS);i++)
	{
		kma::vec3 Point = cubePoints[i];

		kma::vec3 TransformedPoint = kma::RotateOnY(Point, cubeRotation.y);
		TransformedPoint = kma::RotateOnZ(TransformedPoint, cubeRotation.z);
		TransformedPoint = kma::RotateOnZ(TransformedPoint, cubeRotation.x);

		TransformedPoint.z -= camPos.z;

		kma::vec2 ProjectedPoint = Project(TransformedPoint);

		ProjectedPoints[i] = ProjectedPoint;
	}
}

void Renderer::Render()
{


	/*frameBuffer->DrawPixel(100, 100, BLUE);
	frameBuffer->DrawPixel(120, 120, BLUE);
	frameBuffer->DrawPixel(130, 130, BLUE);
	frameBuffer->DrawPixel(140, 140, BLUE);
	frameBuffer->DrawPixel(150, 150, BLUE);*/

	//frameBuffer->DrawLineDDA(100, 100, 500, 500, YELLOW);
	//frameBuffer->DrawLineBresenham(130, 100, 530, 500, BLUE);


	for (int i = 0; i < N_POINTS; i++)
	{
		kma::vec2 ProjectedReady = ProjectedPoints[i];
		frameBuffer->DrawRect(
			ProjectedReady.x + (mWindow.WIDTH / 2), 
			ProjectedReady.y + (mWindow.HEIGHT / 2),
			4, 
			4, 
			YELLOW);
	}

	SDL_UpdateTexture(
		texture,
		NULL,
		frameBuffer->pixels,
		(int)width * sizeof(uint32_t));

	SDL_RenderCopy(mWindow.Renderer, texture, NULL, NULL);


	//SDL_SetRenderDrawColor(mWindow.Renderer, 255, 0, 0, 255);
	//SDL_RenderClear(mWindow.Renderer);

	frameBuffer->ClearFrameBuffer(BLACK);

	SDL_RenderPresent(mWindow.Renderer);
}

kma::vec2 Renderer::Project(kma::vec3 Point)
{
	kma::vec2 ProjectedPoint
	{
		FOVfactor * (Point.x/ Point.z),
		FOVfactor * (Point.y / Point.z)
	};
	return ProjectedPoint;
}

//kma::mat4 rotate(float iAngle, kma::vec4& Axis)
//{
//	const float a = kma::radians(iAngle);
//	const float c = cos(a);
//	const float s = sin(a);
//	kma::vec4 axis = Axis.normalize();
//	kma::mat4 Rotate;
//	Rotate.matrixData[0] = c + (axis.x * axis.x) * (float(1) - c);
//	Rotate.matrixData[1] = (axis.x * axis.y) * (float(1) - c) - axis.z * s;
//	Rotate.matrixData[2] = (axis.x * axis.z) * (float(1) - c) + axis.y * s;
//	Rotate.matrixData[4] = (axis.y * axis.x) * (float(1) - c) + axis.z * s;
//	Rotate.matrixData[5] = c + (axis.y * axis.y) * (float(1) - c);
//	Rotate.matrixData[6] = (axis.y * axis.z) * (float(1) - c) - axis.x * s;
//	Rotate.matrixData[8] = (axis.z * axis.x) * (float(1) - c) - axis.y * s;
//	Rotate.matrixData[9] = (axis.z * axis.y) * (float(1) - c) + axis.x * s;
//	Rotate.matrixData[10] = c + (axis.z * axis.z) * (float(1) - c);
//	Rotate.matrixData[15] = 1;
//	return Rotate;
//}
//
//kma::vec3 RotateAxisAngle(kma::vec4 iPos, kma::vec4 iAxis, float iAngle)
//{
//	kma::mat4 Rotation = rotate(30, iAxis);
//	iPos = iPos * Rotation;
//}