#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	initGraphics();
	play();
}


void Game::initGraphics()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Falling Sand", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}


void Game::play()
{
	while (true)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		handleEvent();
		if (mousePressed) addParticles();
		updateParticles();
		drawParticles();

		SDL_RenderPresent(renderer);
	}
}

void Game::handleEvent()
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			mousePressed = true;
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				selectedParticle = sand;
			}

			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				selectedParticle = water;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			mousePressed = false;
		}
		if (event.type == SDL_MOUSEWHEEL)
		{
			brushSize += event.wheel.y;
			if (brushSize < 2) brushSize = 2;
		}
	}
}

void Game::addParticles()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	for (int i = -brushSize / 2; i < brushSize / 2; i++)
		for (int j = -brushSize / 2; j < brushSize / 2; j++)
		{
			particles.map[x + i][y + j] = selectedParticle;
		}
}

void Game::updateParticles()
{
	moveDir = !moveDir;

	if (moveDir)
	{
		for (int y = 598; y >= 0; y--)
			for (int x = 0; x < 798; x++)

			{
				particles.move(x, y);
			}
	}
	else
	{
		for (int y = 598; y > 0; y--)
			for (int x = 799; x >= 0; x--)
			{
				particles.move(x, y);
			}

	}
}

void Game::drawParticles()
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
		{

			if (particles.map[x][y] == sand)
			{
				SDL_SetRenderDrawColor(renderer, 255, 200, 100, 255);
				SDL_RenderDrawPoint(renderer, x, y);

			}
			else if (particles.map[x][y] == water)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				SDL_RenderDrawPoint(renderer, x, y);

			}
		}
}
