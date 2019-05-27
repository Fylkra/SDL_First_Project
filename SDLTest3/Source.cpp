// This application will be used to learn how to use external libraries and to create a simple particle explosion graphic.

#include <iostream>
#include <SDL.h> // This is the external library header file. 

using namespace std;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)/* This does a test to confirm that SDL is correctly installed and linked to the cpp file */
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!";
	}

	cin.get(); /* Holds the window open "Press any key to continue... type of thing"*/

	const int SCREEN_WIDTH = 600;
	const int SCREEN_HEIGHT = 800;

	SDL_Window* window = SDL_CreateWindow("Particle Fire Explosion ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_SHOWN); 

	if (window == NULL) /* If window doesn't open this closes all resources. */
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL)
	{
		cout << "Could not create Renderer! " << endl;

		cin.get();

		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();

		return 2;
	}

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (texture == NULL)
	{
		cout << "Could not create Texture! " << endl;

		cin.get();

		SDL_DestroyTexture(texture);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 3;

	}

	Uint32* buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	memset(buffer, 0x00, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));

	for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
	{
		buffer[i] = 0xFFFF0000;
	}

	SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));

	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, texture, NULL, NULL);

	SDL_RenderPresent(renderer);

	bool quit = false; /* set quit = true; to finish*/

	SDL_Event event;

	while (quit != true)
	{

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}

		}
	}


	delete[] buffer;

	SDL_DestroyTexture(texture);

	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}