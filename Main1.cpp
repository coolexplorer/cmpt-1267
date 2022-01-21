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
		cout << "SDL Init failed! SDL_Error: " << SDL_GetError() << endl;
	else
	{
		window = SDL_CreateWindow("CMPT 1267", 100, 100, WIDTH, HEIGHT, 0);
		if (window == nullptr)
			cout << "Create Window failed! SDL_Error: " << SDL_GetError() << endl;
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 127, 127, 255));
			SDL_UpdateWindowSurface(window);
			SDL_Delay(5000); // Delay in milliseconds
		}
	}
	SDL_FreeSurface(screenSurface);
	screenSurface = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
	return 0;
}