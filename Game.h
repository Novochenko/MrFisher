#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class ColliderComponent;


class Game {
private:
    
    bool IsRunning;
    int cnt;
public:
    int Record;
    SDL_Window* window;
    Game();
    ~Game();
    void Init();
    void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void HandleEnvents();
    void Update();
    void Render();
    void Clean();
    void GameReload();
    void Run() { IsRunning = true; }
    void Stop() { IsRunning = false; }
    static void AddTail(int sourceX, int sourceY, int xpos, int ypos);
    SDL_Renderer* GetRenderer() { return renderer; }
    SDL_Window* GetWindow() { return window; }
    static SDL_Renderer* renderer;
    static SDL_Event event;
    bool Running() {return IsRunning;}
    static std::vector<ColliderComponent*> colliders;
};


