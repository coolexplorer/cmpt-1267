#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

const int X_POSITION = 100;
const int Y_POSITION = 100;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	SDL_Window* myWindow = NULL;
	SDL_Texture* currentTexture = NULL;
	SDL_Texture* newTexture[2] = { NULL };
	SDL_Renderer* theRenderer = NULL;

	int nowTextureWidth, nowTextureHeight;
	int textureWidth[2], textureHeight[2];

	SDL_Init(SDL_INIT_VIDEO);
	myWindow = SDL_CreateWindow("CMPT 1267", X_POSITION, X_POSITION, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);

	string imageFile[2] = { "arrow1.png", "arrow2.png"};

	for (int i = 0 ; i < 2 ; i++) {
		SDL_Surface* theSurface = IMG_Load(imageFile[i].c_str());

		newTexture[i] = SDL_CreateTextureFromSurface(theRenderer, IMG_Load(imageFile[i].c_str()));
		textureWidth[i] = theSurface->w;
		textureHeight[i] = theSurface->h;

		SDL_FreeSurface(theSurface);
	}

	bool Done = false;
	SDL_Event e;
	double degrees = 0;
	SDL_RendererFlip flipType = SDL_FLIP_NONE;

	nowTextureWidth = textureWidth[0];
	nowTextureHeight = textureHeight[0];
	currentTexture = newTexture[0];
	
	while (!Done)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				Done = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_n:
						nowTextureWidth = textureWidth[0];
						nowTextureHeight = textureWidth[0];
						currentTexture = newTexture[0];
						break;

					case SDLK_m:
						nowTextureWidth = textureWidth[1];
						nowTextureHeight = textureWidth[1];
						currentTexture = newTexture[1];
						break;

					case SDLK_a:
						degrees -= 60;
						break;

					case SDLK_s:
						degrees += 60;
						break;

					case SDLK_q:
						flipType = SDL_FLIP_HORIZONTAL;
						break;

					case SDLK_w:
						flipType = SDL_FLIP_NONE;
						break;

					case SDLK_e:
						flipType = SDL_FLIP_VERTICAL;
						break;
				}
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(theRenderer);

		// Render arrow
		int x = (SCREEN_WIDTH - nowTextureWidth) / 2;
		int y = (SCREEN_HEIGHT - nowTextureHeight) / 2;

		SDL_Rect* clip = NULL;
		SDL_Rect renderQuad = { x, y, nowTextureWidth, nowTextureHeight };
		//Set clip rendering dimensions
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		// Render to screen
		SDL_RenderCopyEx(theRenderer, currentTexture, clip, &renderQuad, degrees, NULL, flipType);

		// Update Screen
		SDL_RenderPresent(theRenderer);
	}

	SDL_DestroyTexture(currentTexture);
	currentTexture = NULL;

	SDL_DestroyTexture(newTexture[0]);
	newTexture[0] = NULL;

	SDL_DestroyTexture(newTexture[1]);
	newTexture[1] = NULL;

	SDL_DestroyRenderer(theRenderer);
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;
	theRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
	return 0;
}