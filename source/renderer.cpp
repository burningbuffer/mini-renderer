#include "renderer.hpp"



Renderer::Renderer()
{
	isRunning = true;
	mWindow.initWindow("Mini renderer", 1200, 800);
	width = mWindow.WIDTH;
	height = mWindow.HEIGHT;
	texture = mWindow.getScreenTexture();
	frameBuffer = new FrameBuffer(new uint32_t[width * height], width, height);

	NumOfFaces = cube.CubeIndices.size();
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
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime);

	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
	{
		SDL_Delay(timeToWait);
	}

	cubeRotation.y += 0.015f;
	//cubeRotation.z += 0.011f;
	//cubeRotation.x += 0.001f;

	for (int i=0;i < NumOfFaces;i++)
	{

		indices MeshIndices = cube.CubeIndices[i];

		kma::vec3 FaceVertices[3];
		FaceVertices[0] = cube.CubeVertices[MeshIndices.a - 1];
		FaceVertices[1] = cube.CubeVertices[MeshIndices.b - 1];
		FaceVertices[2] = cube.CubeVertices[MeshIndices.c - 1];

		triangle ProjectedTriangle;

		for (int j = 0; j < 3; j++)
		{
			kma::vec3 TransformedVertex = FaceVertices[j];
			TransformedVertex = kma::RotateOnX(TransformedVertex, cubeRotation.x);
			TransformedVertex = kma::RotateOnY(TransformedVertex, cubeRotation.y);
			TransformedVertex = kma::RotateOnZ(TransformedVertex, cubeRotation.z);
		
			TransformedVertex.z -= camPos.z;

			kma::vec2 ProjectedPoint = Project(TransformedVertex);
		
			ProjectedPoint.x += (width / 2);
			ProjectedPoint.y += (height / 2);

			ProjectedTriangle.Points[j] = ProjectedPoint;
		}

		TrianglesToRender[i] = ProjectedTriangle;
	}

}

void Renderer::Render()
{

	/*frameBuffer->DrawPixel(100, 100, BLUE);
	//frameBuffer->DrawPixel(120, 120, BLUE);
	frameBuffer->DrawPixel(130, 130, BLUE);
	frameBuffer->DrawPixel(140, 140, BLUE);
	frameBuffer->DrawPixel(150, 150, BLUE);*/

	//frameBuffer->DrawLineDDA(100, 100, 500, 500, YELLOW);
	//frameBuffer->DrawLineBresenham(130, 100, 530, 500, BLUE);


	for (int i = 0; i < NumOfFaces; i++)
	{
		triangle tr = TrianglesToRender[i];
	
		frameBuffer->DrawTriangle(
			tr.Points[0].x,
			tr.Points[0].y,
			tr.Points[1].x,
			tr.Points[1].y,
			tr.Points[2].x,
			tr.Points[2].y,
			PINK
		);
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