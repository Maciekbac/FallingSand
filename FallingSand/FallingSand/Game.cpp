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
	startick = SDL_GetTicks();
	TTF_Init();
	font = TTF_OpenFont("font/OpenSans-Regular.ttf", 12);
}


void Game::play()
{
	while (!quit)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		handleEvent();
		if (mousePressedL) addParticles(selectedParticle);
		else if (mousePressedR) addParticles(none);
		if (!pause) updateParticles();
		drawParticles();
		fpsCounter();
		drawGui();
		SDL_RenderPresent(renderer);
	}
}

void Game::handleEvent()
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (insideIcon(sand))
					selectedParticle = sand;
				else if (insideIcon(water))
					selectedParticle = water;
				else if (insideIcon(wall))
					selectedParticle = wall;
				else mousePressedL = true;
			}

			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				mousePressedR = true;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			mousePressedL = false;
			mousePressedR = false;
		}
		if (event.type == SDL_MOUSEWHEEL)
		{
			brushSize += event.wheel.y;
			if (brushSize < 2) brushSize = 2;
		}

		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_SPACE) pause = !pause;
		}

		if (event.type == SDL_QUIT)
		{
			quit = true;
		}
	}
}

void Game::addParticles(char type)
{
	for (int i = -brushSize / 2; i < brushSize / 2; i++)
		for (int j = -brushSize / 2; j < brushSize / 2; j++)
		{
			if (mouseX + i > 0 && mouseX + i < 800 && mouseY + j>0 && mouseY + j < 600)
			{
				particles.map[mouseX + i][mouseY + j] = type;
			}
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
	//for (int x = 0; x < width; x++)
	//	for (int y = 0; y < height; y++)
	//	{
	//		if (particles.map[x][y] == sand)
	//		{
	//			SDL_SetRenderDrawColor(renderer, 255, 200, 100, 255);
	//			SDL_RenderDrawPoint(renderer, x, y);
	//		}
	//		else if (particles.map[x][y] == water)
	//		{
	//			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	//			SDL_RenderDrawPoint(renderer, x, y);
	//		}
	//	}
	char lastParticle = none;
	char currentParticle;
	int lineLength = 1;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			currentParticle = particles.map[x][y];
			if (currentParticle == lastParticle) lineLength++;
			if (currentParticle != lastParticle || x == width - 1)
			{
				if (lastParticle != none)
				{
					if (x == width - 1) x++;
					if (lastParticle == sand)
						SDL_SetRenderDrawColor(renderer, 255, 200, 100, 255);
					else if (lastParticle == water)
						SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					else if (lastParticle == wall)
						SDL_SetRenderDrawColor(renderer, 40, 30, 30, 255);
					SDL_RenderDrawLine(renderer, x - lineLength, y, x - 1, y);
				}
				lastParticle = currentParticle;
				lineLength = 1;
			}
		}
		lastParticle = none;
		lineLength = 1;
	}

}

void Game::fpsCounter()
{
	frames++;
	if (SDL_GetTicks() - startick >= 1000)
	{
		currentFPS = frames;
		frames = 0;
		startick = SDL_GetTicks();
	}
}

void Game::drawGui()
{
	string fpsText = "FPS: " + to_string(currentFPS);
	SDL_Surface* fpsText_s = TTF_RenderText_Solid(font, fpsText.c_str(), textColor);
	SDL_Texture* fpsText_t = SDL_CreateTextureFromSurface(renderer, fpsText_s);
	SDL_Rect fpsText_r;
	fpsText_r.x = 0;
	fpsText_r.y = 0;
	fpsText_r.w = fpsText_s->w;
	fpsText_r.h = fpsText_s->h;
	SDL_RenderCopy(renderer, fpsText_t, NULL, &fpsText_r);

	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	SDL_Rect brush_r = { mouseX - brushSize / 2,mouseY - brushSize / 2,brushSize,brushSize };
	SDL_RenderDrawRect(renderer, &brush_r);

	SDL_Rect icon_r;
	if (selectedParticle == sand)
	{
		icon_r = { iconX - iconBorder / 2,sandIconY - iconBorder / 2,iconSize + iconBorder,iconSize + iconBorder };
		SDL_SetRenderDrawColor(renderer, 50, 0, 100, 255);
		SDL_RenderFillRect(renderer, &icon_r);
	}
	icon_r = { iconX,sandIconY,iconSize,iconSize };
	SDL_SetRenderDrawColor(renderer, 255, 200, 100, 255);
	SDL_RenderFillRect(renderer, &icon_r);

	if (selectedParticle == water)
	{
		icon_r = { iconX - iconBorder / 2, waterIconY - iconBorder / 2,iconSize + iconBorder,iconSize + iconBorder };
		SDL_SetRenderDrawColor(renderer, 50, 0, 100, 255);
		SDL_RenderFillRect(renderer, &icon_r);
	}

	icon_r = { iconX,waterIconY,iconSize,iconSize };
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &icon_r);

	if (selectedParticle == wall)
	{
		icon_r = { iconX - iconBorder / 2, wallIconY - iconBorder / 2,iconSize + iconBorder,iconSize + iconBorder };
		SDL_SetRenderDrawColor(renderer, 50, 0, 100, 255);
		SDL_RenderFillRect(renderer, &icon_r);
	}

	icon_r = { iconX,wallIconY,iconSize,iconSize };
	SDL_SetRenderDrawColor(renderer, 40, 30, 30, 255);
	SDL_RenderFillRect(renderer, &icon_r);

	if (insideIcon(sand))
	{
		SDL_Surface* iconText_s = TTF_RenderText_Solid(font, "Sand", textColor);
		SDL_Texture* iconText_t = SDL_CreateTextureFromSurface(renderer, iconText_s);
		SDL_Rect iconText_r;
		iconText_r.x = iconX - iconBorder - iconText_s->w - 5;
		iconText_r.y = sandIconY + iconSize / 4;
		iconText_r.w = iconText_s->w;
		iconText_r.h = iconText_s->h;
		SDL_RenderCopy(renderer, iconText_t, NULL, &iconText_r);
	}

	else if (insideIcon(water))
	{
		SDL_Surface* iconText_s = TTF_RenderText_Solid(font, "Water", textColor);
		SDL_Texture* iconText_t = SDL_CreateTextureFromSurface(renderer, iconText_s);
		SDL_Rect iconText_r;
		iconText_r.x = iconX - iconBorder - iconText_s->w - 5;
		iconText_r.y = waterIconY + iconSize / 4;
		iconText_r.w = iconText_s->w;
		iconText_r.h = iconText_s->h;
		SDL_RenderCopy(renderer, iconText_t, NULL, &iconText_r);
	}
}

bool Game::insideIcon(char type)
{
	bool inside = false;
	if (mouseX >= iconX && mouseX <= iconX + iconSize)
	{
		if (type == sand)
		{
			if (mouseY >= sandIconY && mouseY <= sandIconY + iconSize)
				inside = true;
		}

		else if (type == water)
		{
			if (mouseY >= waterIconY && mouseY <= waterIconY + iconSize)
				inside = true;
		}

		else if (type == wall)
		{
			if (mouseY >= wallIconY && mouseY <= wallIconY + iconSize)
				inside = true;
		}
	}

	return inside;
}