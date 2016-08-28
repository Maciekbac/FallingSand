#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Particle.h"
#include <cstdlib>
#include <ctime>
#include <string>

#undef main

using namespace std;

#define width 800
#define height 600

class Game
{
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	TTF_Font* font = NULL;
	SDL_Color textColor = { 0,0,0 };
	SDL_Event event;
	Particle particles;
	bool mousePressed = false;
	int brushSize = 5;
	char selectedParticle;
	bool moveDir = false;
	bool quit = false;
	int startick;
	int frames = 0;
	int currentFPS = 0;
	bool pause = false;

public:
	Game();
	void initGraphics();
	void play();
	void handleEvent();
	void addParticles();
	void updateParticles();
	void drawParticles();
	void fpsCounter();
	void drawGui();
};

