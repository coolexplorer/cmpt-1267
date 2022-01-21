#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* args[])
{
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Surface* helloSDLSurface = nullptr;
    SDL_Surface* scaledSurface = nullptr;

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
		window = SDL_CreateWindow("CMPT 1267", 100, 100, WIDTH, HEIGHT, 0);

		// window == nullptr <= creation failed
		if (window == nullptr)
		{
			cout << "SDL_CreateWindow failed, Error: " << SDL_GetError() << endl;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			helloSDLSurface = SDL_LoadBMP("HelloSDL.bmp");
			if (helloSDLSurface == nullptr) 
			{
				cout << "I couldn't open the file" << endl;
			}
			else
			{
                scaledSurface = SDL_ConvertSurface(helloSDLSurface, screenSurface->format, 0);
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

					//SDL_BlitSurface(helloSDLSurface, NULL, screenSurface, NULL);
                    SDL_Rect stretchRect;
                    stretchRect.x = 100;
                    stretchRect.y = 100;
                    stretchRect.w = 300;
                    stretchRect.h = 400;
                    SDL_BlitSurface(scaledSurface, NULL, screenSurface, &stretchRect);
					SDL_UpdateWindowSurface(window);
				}
			}
		}
	}

    SDL_FreeSurface(scaledSurface);
    scaledSurface = nullptr;
	SDL_FreeSurface(helloSDLSurface);
	helloSDLSurface = nullptr;
	SDL_FreeSurface(screenSurface);
	screenSurface = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();

	return 0;
}
