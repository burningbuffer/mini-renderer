#include "renderer.hpp"
#include <SDL2/SDL.h>
#include "window.hpp"
#include "framebuffer.hpp"
#include "common.hpp"
#include "mesh.hpp"
#include "triangle.hpp"
#include <vector>
#include <memory>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "math.hpp"
#include <iostream>

static constexpr int WINDOW_WIDTH = 800;
static constexpr int WINDOW_HEIGHT = 600;

bool isRunning;
std::unique_ptr<Window> SDLWindow;
std::unique_ptr<FrameBuffer> frameBuffer;
int previousFrameTime;

glm::vec3 camPos;
float AngleRotation;
glm::vec3 axisRotation;
glm::vec3 meshObjectScale;
glm::vec3 meshObjectTranslation;

Mesh* meshObject;
uint32 NumOfFaces;

glm::vec3 lightDir;

std::vector<Triangle> TrianglesToRender;

float fov;
float aspectRatio;
float near;
float far;

Renderer::Renderer(int width, int height)
{
    camPos = glm::vec3(0.0f, 0.0f, 0.0f);
    AngleRotation = 0.005f;
    axisRotation = glm::vec3(1.0f, 1.0f, 0.0f);
    meshObjectScale = glm::vec3(1.0f, 1.0f, 1.0f);
    meshObjectTranslation = glm::vec3(0.0f, 0.0f, 10.0f);
    meshObject = nullptr;
    NumOfFaces = 0;
    fov = glm::radians(45.0f);
    aspectRatio = static_cast<float>(WINDOW_WIDTH) / WINDOW_HEIGHT;
    near = 0.1f;
    far = 1000.0f;

    isRunning = true;

    SDLWindow = std::make_unique<Window>();
    SDLWindow->ConfigWindow("Mini renderer", WINDOW_WIDTH, WINDOW_HEIGHT);

    frameBuffer = std::make_unique<FrameBuffer>(new uint32[WINDOW_WIDTH * WINDOW_HEIGHT],WINDOW_WIDTH, WINDOW_HEIGHT);

    previousFrameTime = 0.0f;

    meshObject = new Mesh("assets/cube.obj");
    NumOfFaces = meshObject->mIndices.size();
    TrianglesToRender.resize(meshObject->mIndices.size());

    lightDir = glm::vec3{ 0, 0, 1 };

    std::cout << "vertices size: " << meshObject->mVertices.size() << std::endl;
    std::cout << "indices size: " << meshObject->mIndices.size() << std::endl;
}

Renderer::~Renderer() 
{
    DeleteObjects();
}

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

    switch (event.type) {
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

void Renderer::Update() 
{
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime);

    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) 
    {
        SDL_Delay(timeToWait);
    }

    glm::mat4 projectionMatrix = glm::perspective(fov, aspectRatio, near, far);
    glm::mat4 model_matrix = glm::mat4(1.0f);

    AngleRotation -= 0.005f;

    model_matrix = glm::translate(model_matrix, meshObjectTranslation += camPos);
    model_matrix = glm::rotate(model_matrix, AngleRotation, axisRotation);
    model_matrix = glm::scale(model_matrix, meshObjectScale);

    for (uint32 i = 0; i < NumOfFaces; i++) 
    {
        face faceToRender = meshObject->mIndices[i];

        glm::vec3 FaceVertices[3];
        FaceVertices[0] = meshObject->mVertices[faceToRender.a - 1];
        FaceVertices[1] = meshObject->mVertices[faceToRender.b - 1];
        FaceVertices[2] = meshObject->mVertices[faceToRender.c - 1];

        Triangle ProjectedTriangle;
        ProjectedTriangle.TriangleColor = faceToRender.FaceColor;

        glm::vec4 TransformedTriangle[3];

        for (int j = 0; j < 3; j++) 
        {
            glm::vec4 TransformedVertex = glm::vec4(FaceVertices[j], 1);
            glm::mat4 worldMatrix = model_matrix;
            TransformedVertex = worldMatrix * TransformedVertex;
            TransformedTriangle[j] = TransformedVertex;
        }

        glm::vec3 a = glm::vec3(TransformedTriangle[0]);
        glm::vec3 b = glm::vec3(TransformedTriangle[1]);
        glm::vec3 c = glm::vec3(TransformedTriangle[2]);

        glm::vec3 vector_ab = glm::normalize(a - b);
        glm::vec3 vector_ac = glm::normalize(a - c);

        glm::vec3 normal = glm::normalize(glm::cross(vector_ab, vector_ac));

        float lightIntensityFactor = glm::dot(normal, lightDir);

        for (int j = 0; j < 3; j++) 
        {
            glm::vec4 ProjectedPoint = Project(TransformedTriangle[j], projectionMatrix);

            ProjectedPoint.x = (ProjectedPoint.x + 1.0f) * (WINDOW_WIDTH / 2.0f);
            ProjectedPoint.y = (ProjectedPoint.y + 1.0f) * (WINDOW_HEIGHT / 2.0f);

            ProjectedTriangle.Points[j].x = ProjectedPoint.x;
            ProjectedTriangle.Points[j].y = ProjectedPoint.y;
        }

        TrianglesToRender[i] = ProjectedTriangle;
        TrianglesToRender[i].TriangleColor = ApplyLightIntensity(WHITE, lightIntensityFactor);
    }
}

void Renderer::Render() 
{
    for (uint32 i = 0; i < NumOfFaces; i++) 
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
        SDLWindow->GetTexture(),
        NULL,
        frameBuffer->pixels,
        (int)WINDOW_WIDTH * sizeof(uint32)
    );

    SDL_RenderCopy(SDLWindow->GetRenderer(), SDLWindow->GetTexture(), NULL, NULL);

    frameBuffer->ClearFrameBuffer(BLACK);

    SDL_RenderPresent(SDLWindow->GetRenderer());
}

void Renderer::DeleteObjects() 
{
    std::cout << "Deleting objects...";
    SDLWindow->DestroyWindow();
    delete meshObject;
}

int main(int argc, char* argv[]) 
{
    Renderer renderer(800, 600);
    renderer.Run();

    return 0;
}