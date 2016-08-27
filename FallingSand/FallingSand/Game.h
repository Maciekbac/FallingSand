#pragma once
#include <SDL.h>
#include "Particle.h"
#include <cstdlib>
#include <ctime>
#undef main

#define width 800
#define height 600

class Game
{
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event event;
	Particle particles;
	bool mousePressed = false;
	int brushSize = 5;
	char selectedParticle;
	bool moveDir = false;

public:
	Game();
	void initGraphics();
	void play();
	void handleEvent();
	void addParticles();
	void updateParticles();
	void drawParticles();
};

