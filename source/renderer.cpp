#include "renderer.hpp"


Renderer::Renderer()
{
	isRunning = true;
	mWindow.initWindow("Mini renderer", 1200, 800);
	width = mWindow.WIDTH;
	height = mWindow.HEIGHT;
	texture = mWindow.getScreenTexture();
	frameBuffer = new FrameBuffer(new uint32_t[width * height], width, height);

	cube = new Mesh("assets/head.obj");

	NumOfFaces = cube->indices.size();
	
	TrianglesToRender = new triangle[cube->indices.size()];

	std::cout << "vertices size: " << cube->vertices.size() << std::endl;
	std::cout << "indices size: " << cube->indices.size() << std::endl;
	
	//cube->PrintMeshContent();
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

	cubeRotation.y -= 0.005f;
	cubeRotation.z += 0.011f;
	cubeRotation.x += 0.011f;

	for (int i = 0; i < NumOfFaces; i++)
	{
		face faceToRender = cube->indices[i];

		kma::vec3 FaceVertices[3];
		FaceVertices[0] = cube->vertices[faceToRender.a - 1];
		FaceVertices[1] = cube->vertices[faceToRender.b - 1];
		FaceVertices[2] = cube->vertices[faceToRender.c - 1];

		triangle ProjectedTriangle;

		kma::vec3 TransformedTriangle[3];

		for (int j = 0; j < 3; j++)
		{
			kma::vec3 TransformedVertex = FaceVertices[j];
			TransformedVertex = kma::RotateOnX(TransformedVertex, cubeRotation.x);
			TransformedVertex = kma::RotateOnY(TransformedVertex, cubeRotation.y);
			TransformedVertex = kma::RotateOnZ(TransformedVertex, cubeRotation.z);

			TransformedVertex.z += 5;

			TransformedTriangle[j] = TransformedVertex;
		}


		for (int j = 0; j < 3; j++)
		{
			kma::vec2 ProjectedPoint = Project(TransformedTriangle[j]);

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

		if (!IsClockwise(tr))
		{
			frameBuffer->DrawTriangle(
				tr.Points[0].x,
				tr.Points[0].y,
				tr.Points[1].x,
				tr.Points[1].y,
				tr.Points[2].x,
				tr.Points[2].y,
				WHITE
			);
		}
		else {
			continue;
		}

		
	}

	SDL_UpdateTexture(
		texture,
		NULL,
		frameBuffer->pixels,
		(int)width * sizeof(uint32_t));

	SDL_RenderCopy(mWindow.Renderer, texture, NULL, NULL);

	frameBuffer->ClearFrameBuffer(BLACK);

	SDL_RenderPresent(mWindow.Renderer);
}

kma::vec2 Renderer::Project(kma::vec3 Point)
{
	kma::vec2 ProjectedPoint
	{
		FOV * (Point.x/ Point.z),
		FOV * (Point.y / Point.z)
	};
	return ProjectedPoint;
}

bool Renderer::IsClockwise(triangle t)
{
	auto ax = t.Points[0].x - t.Points[1].x;
	auto ay = t.Points[0].y - t.Points[1].y;
	auto bx = t.Points[0].x - t.Points[2].x;
	auto by = t.Points[0].y - t.Points[2].y;
	auto order = ax * by - ay * bx;
	return order < 0;
}
