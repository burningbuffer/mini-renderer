//#include <iostream>
#include "SDL.h"
#include "window.hpp"
#include "framebuffer.hpp"
#include "color_types.hpp"
#include "mesh.hpp"
#include "triangle.hpp"
#include <vector>
#include <kma/kma.hpp>

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)

bool isRunning = false;

Window SDLWindow;
SDL_Texture* texture = nullptr;
FrameBuffer* frameBuffer = nullptr;
float width = NULL;
float height = NULL;
int previousFrameTime = 0;
const float FOV = 800;

kma::vec3 camPos{ 0.0f, 0.0f, 5.0f };

kma::vec4 cubeRotation{ 0.0f, 0.0f, 0.0f, 0.0f };
kma::vec4 axisRotation{ 1.0f, 1.0f, 1.0f, 0.0f };
kma::vec4 cubeScale{ 1.5f, 1.5f, 1.5f, 0.0f };
kma::vec4 cubeTranslation{ 0.0f, 0.0f, 0.0f, 0.0f };

Mesh* cube = nullptr;
int NumOfFaces = 0;
Triangle* TrianglesToRender = nullptr;

void HandleEvents();
void Update();
void Render();
void DeleteObjects();
kma::vec2 Project(kma::vec4 Point);

int main(int argc, char* argv[])
{
	isRunning = true;
	SDLWindow.initWindow("Mini renderer", 1200, 800);
	width = SDLWindow.WIDTH;
	height = SDLWindow.HEIGHT;
	texture = SDLWindow.getScreenTexture();
	frameBuffer = new FrameBuffer(new uint32_t[width * height], width, height);

	cube = new Mesh("assets/head.obj");

	NumOfFaces = cube->indices.size();

	TrianglesToRender = new Triangle[cube->indices.size()];

	std::cout << "vertices size: " << cube->vertices.size() << std::endl;
	std::cout << "indices size: " << cube->indices.size() << std::endl;

	//cube->PrintMeshContent();

	while (isRunning)
	{
		HandleEvents();
		Update();
		Render();
	}

	DeleteObjects();

	return 0;
}

void HandleEvents()
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
		if (event.key.keysym.sym == SDLK_s) camPos.z += 0.15f;
		break;
	}
}

void Update()
{
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime);

	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
	{
		SDL_Delay(timeToWait);
	}

	cubeRotation.y -= 0.005f;
	//cubeRotation.z += 0.011f;
	//cubeRotation.x += 0.011f;

	//cubeScale.x += 0.01f;
	//cubeScale.y += 0.01f;
	//cubeScale.z += 0.01f;
	//cubeTranslation.x += 0.01f;

	kma::mat4 scaleMatrix = kma::scale(cubeScale);
	kma::mat4 rotationMatrix = kma::rotate(cubeRotation.y, axisRotation);
	kma::mat4 translationMatrix = kma::translate(cubeTranslation);

	for (int i = 0; i < NumOfFaces; i++)
	{
		face faceToRender = cube->indices[i];

		kma::vec3 FaceVertices[3];
		FaceVertices[0] = cube->vertices[faceToRender.a - 1];
		FaceVertices[1] = cube->vertices[faceToRender.b - 1];
		FaceVertices[2] = cube->vertices[faceToRender.c - 1];

		Triangle ProjectedTriangle;

		kma::vec4 TransformedTriangle[3];

		for (int j = 0; j < 3; j++)
		{
			kma::vec4 TransformedVertex = kma::vec4(FaceVertices[j].x, FaceVertices[j].y, FaceVertices[j].z, 1);

			kma::mat4 worldMatrix{};

			kma::mat4 NewworldMatrix = worldMatrix * translationMatrix * rotationMatrix * scaleMatrix;

			TransformedVertex = TransformedVertex * NewworldMatrix;

			TransformedVertex.z += camPos.z;

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

void Render()
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
		Triangle tr = TrianglesToRender[i];

		if (!tr.isClockwise())
		{
			frameBuffer->DrawFilledTriangle(
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

	SDL_RenderCopy(SDLWindow.Renderer, texture, NULL, NULL);

	frameBuffer->ClearFrameBuffer(BLACK);

	SDL_RenderPresent(SDLWindow.Renderer);
}

void DeleteObjects()
{
	std::cout << "Deleting objects...";
	delete texture;
	delete frameBuffer;
	delete cube;
	delete TrianglesToRender;

}

kma::vec2 Project(kma::vec4 Point)
{
	kma::vec2 ProjectedPoint
	{
		FOV * (Point.x / Point.z),
		FOV * (Point.y / Point.z)
	};
	return ProjectedPoint;
}

