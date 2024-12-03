#pragma once

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)

class Renderer 
{
public:
    Renderer(int width, int height);
    ~Renderer();

    void Run();
    void HandleEvents();
    void Update();
    void Render();

    void DeleteObjects();
};
