//#include <iostream>
#include "SDL.h"
#include "window.hpp"
#include "framebuffer.hpp"
#include "color_types.hpp"
#include "mesh.hpp"
#include "triangle.hpp"
#include <vector>
#include<cstdlib>
#include <kma/kma.hpp>

#define FPS 30
#define FRAME_TARGET_TIME (1000/FPS)

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

bool isRunning = false;

Window SDLWindow;
SDL_Texture* texture = nullptr;
FrameBuffer* frameBuffer = nullptr;
float width = NULL;
float height = NULL;
int previousFrameTime = 0;
const float FOV = 800;

kma::vec3 camPos{ 0.0f, 0.0f, 0.0f };

float AngleRotation = 0.005f;

kma::vec4 axisRotation{ 1.0f, 1.0f, 0.0f, 0.0f };
kma::vec4 cubeScale{ 200.0f, 200.0f, 200.0f, 0.0f };
kma::vec4 cubeTranslation{ 0.0f, 0.0f, 0.0f, 0.0f };
kma::mat4 projectionMatrix{};

Mesh* cube = nullptr;
int NumOfFaces = 0;



std::vector<Triangle> TrianglesToRender;

void HandleEvents();
void Update();
void Render();
void DeleteObjects();
kma::mat4 perspective(float fov, float aspectRatio, float znear, float zfar);
kma::vec4 project(kma::vec4 v, kma::mat4 proj);

kma::mat4 perspective(float fov, float aspectRatio, float znear, float zfar)
{
	
	kma::mat4 m{};

	std::cout << " Perspective Matrix Before" << std::endl;
	std::cout << m ;

	m.matrix[0][0] = aspectRatio * (1 / tan(fov / 2));
	m.matrix[1][1] = 1 / tan(fov / 2);
	m.matrix[2][2] = zfar / (zfar - znear);

	m.matrix[2][3] = 1.0;
	m.matrix[3][2] = (-zfar * znear) / (zfar - znear);

	m.matrix[3][3] = 0.0;

	std::cout << " Perspective Matrix After" << std::endl;
	std::cout << m;

	return m;
}

kma::vec4 project(kma::vec4 v, kma::mat4 proj)
{
	kma::vec4 res = v * proj;

	if (res.w != 0.0)
	{
		res.x = res.x / res.w;
		res.y = res.y / res.w;
		res.z = res.z / res.w;
	}

	return res;
}

int main(int argc, char* argv[])
{
	isRunning = true;
	SDLWindow.initWindow("Mini renderer", WINDOW_WIDTH, WINDOW_HEIGHT);
	width = SDLWindow.WIDTH;
	height = SDLWindow.HEIGHT;
	texture = SDLWindow.getScreenTexture();
	frameBuffer = new FrameBuffer(new uint32_t[width * height], width, height);

	float fov = kma::radians(90.0f);
	float aspectRatio = WINDOW_WIDTH / WINDOW_HEIGHT;
	float near = 0.1f;
	float far = 100.0f;

	projectionMatrix = perspective(fov, aspectRatio, near, far);

	cube = new Mesh("assets/cube.obj");

	NumOfFaces = cube->indices.size();

	TrianglesToRender.resize(cube->indices.size());


	std::cout << "vertices size: " << cube->vertices.size() << std::endl;
	std::cout << "indices size: " << cube->indices.size() << std::endl;

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

	AngleRotation -= 0.005f;

	kma::mat4 scaleMatrix = kma::scale(cubeScale);
	kma::mat4 rotationMatrix = kma::rotate(AngleRotation, axisRotation);
	kma::mat4 translationMatrix = kma::translate(cubeTranslation);

	for (int i = 0; i < NumOfFaces; i++)
	{
		face faceToRender = cube->indices[i];

		kma::vec3 FaceVertices[3];
		FaceVertices[0] = cube->vertices[faceToRender.a - 1];
		FaceVertices[1] = cube->vertices[faceToRender.b - 1];
		FaceVertices[2] = cube->vertices[faceToRender.c - 1];

		Triangle ProjectedTriangle;

		ProjectedTriangle.TriangleColor = faceToRender.FaceColor;

		kma::vec4 TransformedTriangle[3];

		for (int j = 0; j < 3; j++)
		{
			kma::vec4 TransformedVertex = kma::vec4(FaceVertices[j].x, FaceVertices[j].y, FaceVertices[j].z, 1);

			kma::mat4 worldMatrix{};

			kma::mat4 NewWorldMatrix = worldMatrix * translationMatrix * rotationMatrix * scaleMatrix;

			TransformedVertex = TransformedVertex * NewWorldMatrix;

			TransformedVertex.z += camPos.z;

			TransformedTriangle[j] = TransformedVertex;
		}

		for (int j = 0; j < 3; j++)
		{
			kma::vec4 ProjectedPoint = project(TransformedTriangle[j], projectionMatrix);

			ProjectedPoint.x += (width / 2);
			ProjectedPoint.y += (height / 2);

			ProjectedTriangle.Points[j].x = ProjectedPoint.x;
			ProjectedTriangle.Points[j].y = ProjectedPoint.y;

		}

		TrianglesToRender[i] = ProjectedTriangle;

	}

}

void Render()
{

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
				tr.TriangleColor
			);
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
	SDLWindow.destroyWindow();
	delete frameBuffer;
	delete cube;
}

