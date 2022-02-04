#include "Game.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int THICKNESS = 15;
const int PADDLE_H = 100;

Game::Game() {
    mWindow = nullptr;
    mRenderer = nullptr;
    mIsRunning = true;
}

bool Game::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "SDL_Init failed. \n";
        return false;
    }

    mWindow = SDL_CreateWindow("Game Class", 100, 100, WIDTH, HEIGHT, 0);
    if (mWindow == nullptr) {
        cout << "SDL_CreateWindow failed,\n";
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == nullptr) {
        cout << "SDL_CreateRenderer failed.\n";
        return false;
    }

    mBallPos.x = WIDTH / 2.0f;
    mBallPos.y = HEIGHT / 2.0f;
    mPaddlePos.x = 10.0f;
    mPaddlePos.y = HEIGHT / 2.0f;

    return true;
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    } else if (state[SDL_SCANCODE_W]) {
        if (mPaddlePos.y > (PADDLE_H / 2 + THICKNESS)) {
            mPaddlePos.y -= 1;
        }
    } else if (state[SDL_SCANCODE_S]) {
        if (mPaddlePos.y <= HEIGHT - (PADDLE_H / 2 + THICKNESS)) {
            mPaddlePos.y += 1;
        }
    }
}

void Game::UpdateGame() {
    
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    // Top wall
    SDL_Rect wall = { 0, 0, WIDTH, THICKNESS };
    SDL_RenderFillRect(mRenderer, &wall);
    
    // Right wall
    wall.x = WIDTH - THICKNESS;
    wall.w = THICKNESS;
    wall.h = HEIGHT;
    SDL_RenderFillRect(mRenderer, &wall);

    // Bottom wall
    wall.x = 0;
    wall.y = HEIGHT - THICKNESS;
    wall.w = WIDTH;
    wall.h = THICKNESS;
    SDL_RenderFillRect(mRenderer, &wall);

    // Ball
    SDL_Rect ball = { static_cast<int>(mBallPos.x - THICKNESS / 2), static_cast<int>(mBallPos.y - THICKNESS / 2), THICKNESS, THICKNESS };
    SDL_RenderFillRect(mRenderer, &ball);

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
    // Paddle
    SDL_Rect paddle = { static_cast<int>(mPaddlePos.x), static_cast<int>(mPaddlePos.y - PADDLE_H/2), THICKNESS, PADDLE_H};
    SDL_RenderFillRect(mRenderer, &paddle);

    SDL_RenderPresent(mRenderer);
}

void Game::ShutDown() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
    SDL_Quit();
}
