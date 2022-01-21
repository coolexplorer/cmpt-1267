#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

const int X_POSITION = 100;
const int Y_POSITION = 100;
const int WIDTH = 640;
const int HEIGHT = 480;

int main(int argc, char* args[])
{
	SDL_Window* window = nullptr;
	SDL_Texture* newTexture = nullptr;
	SDL_Renderer* theRenderer = nullptr;

	// SDL_Init() < 0 => Initialization failed
	// SDL_Init() >= 0 => Initialization Succeed
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL_Init failed, Error: " << SDL_GetError() << endl;
	}
	else
	{
		// SDL_CreateWindow(<Title>, <X Position of window>, <Y Position of window>, <Window width size>, <Window Heigt size>, <options>)
		// options : minize, maximize, and so on
		window = SDL_CreateWindow("CMPT 1267", X_POSITION, Y_POSITION, WIDTH, HEIGHT, 0);

		// window == nullptr <= creation failed
		if (window == nullptr)
		{
			cout << "SDL_CreateWindow failed, Error: " << SDL_GetError() << endl;
		}
		else
		{
			theRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			SDL_SetRenderDrawColor(theRenderer, 0xff, 0xff, 0xff, 0xff);
			IMG_Init(IMG_INIT_PNG);

			SDL_Surface* loadedSurface = IMG_Load("ping_pong.png");
			if (loadedSurface == nullptr) 
			{
				cout << "Unable to load image." << endl;
			}
			else
			{
                newTexture = SDL_CreateTextureFromSurface(theRenderer, loadedSurface);
				SDL_FreeSurface(loadedSurface);
				loadedSurface = nullptr;

				bool done = false;
				SDL_Event event;

				while (!done) 
				{
					while(SDL_PollEvent(&event) != 0) 
					{
						if (event.type == SDL_QUIT)
						{
							done = true;
						}
						else if (event.type == SDL_KEYDOWN)
						{
							if (event.key.keysym.sym == SDLK_q)
							{
								done = true;
							}
						}
					}
					SDL_RenderClear(theRenderer);
					SDL_RenderCopy(theRenderer, newTexture, NULL, NULL);
					SDL_RenderPresent(theRenderer);
				}
			}
		}
	}

	SDL_DestroyTexture(newTexture);
	newTexture = nullptr;
	SDL_DestroyRenderer(theRenderer);
	theRenderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	IMG_Quit();
	SDL_Quit();

	return 0;
}
