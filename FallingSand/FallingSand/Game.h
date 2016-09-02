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
#define iconSize 30 //particle selection icon size
#define iconBorder 4
#define iconX width - iconSize - 10 
#define sandIconY 5
#define waterIconY 10 + iconSize
#define wallIconY 15 + 2 * iconSize

class Game
{
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	TTF_Font* font = NULL;
	SDL_Color textColor = { 0,0,0 };
	SDL_Event event;
	Particle particles;
	int mouseX, mouseY;
	bool mousePressedL = false;
	bool mousePressedR = false;
	int brushSize = 10;
	char selectedParticle = sand;
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
	void addParticles(char type);
	void updateParticles();
	void drawParticles();
	void fpsCounter();
	void drawGui();
	bool insideIcon(char type);
};

