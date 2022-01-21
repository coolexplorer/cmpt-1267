#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* args[])
{
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL_Init failed, Error: " << SDL_GetError() << endl;
	}
	else
	{
		window = SDL_CreateWindow("Lab 1", 100, 100, WIDTH, HEIGHT, 0);

		if (window == nullptr)
		{
			cout << "SDL_CreateWindow failed, Error: " << SDL_GetError() << endl;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 255));
			
			if (screenSurface == nullptr) 
			{
				cout << "I couldn't open the file" << endl;
			}
			else
			{
				bool done = false;
				SDL_Event event;

				while (!done) 
				{
					while(SDL_PollEvent(&event) != 0) 
					{
						if (event.type == SDL_KEYDOWN)
						{
							if (event.key.keysym.sym == SDLK_r)
							{
								SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 0, 0));
							}
							else if (event.key.keysym.sym == SDLK_g)
							{
								SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 255, 0));
							}
							else if (event.key.keysym.sym == SDLK_b)
							{
								SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 255));
							}
							else if (event.key.keysym.sym == SDLK_y)
							{
								SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 255, 0));
							}
							else if (event.key.keysym.sym == SDLK_q)
							{
								done = true;
							}
						}
					}

					SDL_UpdateWindowSurface(window);
				}
			}
		}
	}

	SDL_FreeSurface(screenSurface);
	screenSurface = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();

	return 0;
}
