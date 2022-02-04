#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

// 1. Game();           (Public)
// 2. Initialize();     (Public) 
// 3. RunLoop();        (Public)
//    - ProcessInput(); (Private)
//    - UpdateGame();   (Private)
//    - GenerateOutput(); (Private)
// 4. ShutDown();       (Public)
struct Vector2
{
    float x;
    float y;
};

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void ShutDown();

private: 
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Vector2 mBallPos;
    Vector2 mPaddlePos;
    bool mIsRunning;
};
