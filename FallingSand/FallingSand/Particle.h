#pragma once

#include <iostream>
#include <SDL.h>
#include <cstdlib>
#include <ctime>
//#include <vector>;


//particles names
#define none 0
#define sand 1
#define water 2
#define wall 3

using namespace std;

class Particle
{
public:
	char map[800][600];
	Particle();
	void move(int x, int y);
	bool canMove(int x, int y, char particleType);
	void swapParticles(int x,int y,int xn,int yn);
};

