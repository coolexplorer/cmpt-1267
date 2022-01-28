#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <math.h>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void drawCircle(SDL_Renderer* theRenderer, int cx, int cy, int radius, bool filled);

int main(int argc, char* args[])
{
	SDL_Window* myWindow = NULL;
	SDL_Texture* newTexture = NULL;
	SDL_Renderer* theRenderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);
	
	bool Done = false;
	SDL_Event e;
	while (!Done)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				Done = true;
			}
		}
		SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(theRenderer);
			
        drawCircle(theRenderer, 150, 150, 100, false);
		drawCircle(theRenderer, 500, 300, 100, true);

		SDL_RenderPresent(theRenderer);
	}

	SDL_DestroyTexture(newTexture);
	newTexture = NULL;

	SDL_DestroyRenderer(theRenderer);
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;
	theRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
	return 0;
}

void drawCircle(SDL_Renderer* theRenderer, int cx, int cy, int radius, bool filled) {
    double x = 0, y = 0, xOffset = 0, yOffset = 0;
    double start = 0;
    
    if (!filled) {
        start = radius;
    }

    SDL_SetRenderDrawColor(theRenderer, 0x00, 0x00, 0xFF, 0xFF);

    for (double r = start ; r <= radius ; r += 0.1) {
        for (double i = 0 ; i < M_PI / 2; i += 0.01) {
            xOffset = (r * cos(i));
            yOffset = (r * sin(i));  
            SDL_RenderDrawPoint(theRenderer, cx + xOffset, cy + yOffset);
            SDL_RenderDrawPoint(theRenderer, cx + xOffset, cy - yOffset);
            SDL_RenderDrawPoint(theRenderer, cx - xOffset, cy + yOffset);
            SDL_RenderDrawPoint(theRenderer, cx - xOffset, cy - yOffset);
        }
    }
}