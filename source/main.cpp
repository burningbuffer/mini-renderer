#include <SDL2/SDL.h>
#include "window.hpp"
#include "framebuffer.hpp"
#include "color_types.hpp"
#include "mesh.hpp"
#include "triangle.hpp"
#include <vector>
#include <memory>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

bool isRunning = false;

std::unique_ptr<Window> SDLWindow;
std::unique_ptr<FrameBuffer> frameBuffer;
float width = NULL;
float height = NULL;
int previousFrameTime = 0;

glm::vec3 camPos{ 0.0f, 0.0f, 0.0f };

float AngleRotation = 0.005f;

glm::vec3 axisRotation{ 1.0f, 1.0f, 0.0f};
glm::vec3 cubeScale{ 1.0f, 1.0f, 1.0f,};
glm::vec3 cubeTranslation{ 0.0f, 0.0f, 10.0f};

Mesh* cube = nullptr;
int NumOfFaces = 0;

std::vector<Triangle> TrianglesToRender;

float fov = glm::radians(45.0f);
float aspectRatio = WINDOW_WIDTH / WINDOW_HEIGHT;
float near = 0.1f;
float far = 1000.0f;

void HandleEvents();
void Update();
void Render();
void DeleteObjects();

glm::vec4 project(glm::vec4 v, glm::mat4 proj)
{
	glm::vec4 res = proj * v;

	if (res.w != 0.0)
	{
		res.x /= res.w;
        res.y /= res.w;
        res.z /= res.w;
	}

	return res;
}

int main(int argc, char* argv[])
{
	isRunning = true;

	SDLWindow = std::make_unique<Window>();

	SDLWindow->ConfigWindow("Mini renderer", WINDOW_WIDTH, WINDOW_HEIGHT);

	width = SDLWindow->mWidth;
	height = SDLWindow->mHeight;

	frameBuffer = std::make_unique<FrameBuffer>(new uint32_t[width * height], width, height);

	cube = new Mesh("assets/head.obj");

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
		if (event.key.keysym.sym == SDLK_s) camPos.z += 0.001f;
		if (event.key.keysym.sym == SDLK_w) camPos.z -= 0.001f;
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

	glm::mat4 projectionMatrix{};

	projectionMatrix = glm::perspective(fov, aspectRatio, near, far);

	glm::mat4 model_matrix = glm::mat4(1.0f);

	AngleRotation -= 0.005f;

	// correct order -> translate -> rotate -> scale
	model_matrix = glm::translate(model_matrix, cubeTranslation+=camPos);
	model_matrix = glm::rotate(model_matrix, AngleRotation, axisRotation);
	model_matrix = glm::scale(model_matrix, cubeScale);

	for (int i = 0; i < NumOfFaces; i++)
	{
		face faceToRender = cube->indices[i];

		glm::vec3 FaceVertices[3];
		FaceVertices[0] = cube->vertices[faceToRender.a - 1];
		FaceVertices[1] = cube->vertices[faceToRender.b - 1];
		FaceVertices[2] = cube->vertices[faceToRender.c - 1];

		Triangle ProjectedTriangle;

		ProjectedTriangle.TriangleColor = faceToRender.FaceColor;

		glm::vec4 TransformedTriangle[3];

		for (int j = 0; j < 3; j++)
		{
			glm::vec4 TransformedVertex = glm::vec4(FaceVertices[j], 1);

            glm::mat4 worldMatrix = model_matrix;

			TransformedVertex = worldMatrix * TransformedVertex;

			TransformedVertex.y = TransformedVertex.y * -1 ;

			TransformedTriangle[j] = TransformedVertex;
		}

		for (int j = 0; j < 3; j++)
		{
			glm::vec4 ProjectedPoint = project(TransformedTriangle[j], projectionMatrix);

			ProjectedPoint.x = (ProjectedPoint.x + 1.0f) * (width / 2.0f);
			ProjectedPoint.y = (ProjectedPoint.y + 1.0f) * (height / 2.0f);

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
				WHITE
			);
		}

	}

	SDL_UpdateTexture(
		SDLWindow->GetTexture(),
		NULL,
		frameBuffer->pixels,
		(int)width * sizeof(uint32_t));

	SDL_RenderCopy(SDLWindow->GetRenderer(), SDLWindow->GetTexture(), NULL, NULL);

	frameBuffer->ClearFrameBuffer(BLACK);

	SDL_RenderPresent(SDLWindow->GetRenderer());
}

void DeleteObjects()
{
	std::cout << "Deleting objects...";
	SDLWindow->DestroyWindow();
	delete cube;
}