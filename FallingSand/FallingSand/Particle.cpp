#include "Particle.h"

Particle::Particle()
{
	for (int i = 0; i < 800; i++)
		for (int j = 0; j < 600; j++)
			map[i][j] = none;
	srand(time(NULL));
}

void Particle::move(int x, int y)
{
	if (map[x][y] == sand)
	{
		if (canMove(x, y + 1, sand))
		{
			int distance = rand() % 5 + 1;
			for (int i = distance; i >= 1; i--)
			{
				if (canMove(x, y + i, sand))
				{
					swapParticles(x, y, x, y + i);
					break;
				}
			}
		}

		else
		{
			if (canMove(x + 1, y + 1, sand))
			{
				swapParticles(x, y, x + 1, y + 1);
			}
			else if (canMove(x - 1, y + 1, sand))
			{
				swapParticles(x, y, x - 1, y + 1);
			}
		}
	}

	else if (map[x][y] == water)
	{
		if (canMove(x, y + 1, water))
		{
			int distance = rand() % 5 + 1;
			for (int i = distance; i >= 1; i--)
			{
				if (canMove(x, y + i, water))
				{
					swapParticles(x, y, x, y + i);
					break;
				}
			}
		}

		else if (canMove(x + 1, y + 1, water) && canMove(x - 1, y + 1, water))
		{
			int r = rand() % 2;
			if (r == 0)
			{
				swapParticles(x, y, x + 1, y + 1);
			}
			else
			{
				swapParticles(x, y, x - 1, y + 1);
			}
		}
		else if (canMove(x + 1, y + 1, water))
		{
			swapParticles(x, y, x + 1, y + 1);

		}
		else if (canMove(x - 1, y + 1, water))
		{
			swapParticles(x, y, x - 1, y + 1);
		}

		else if (canMove(x - 1, y, water) && canMove(x + 1, y, water))
		{
			int r = rand() % 2;
			if (r == 0)
			{
				swapParticles(x, y, x - 1, y);
			}
			else
			{
				swapParticles(x, y, x + 1, y);
			}
		}

		else if (canMove(x - 1, y, water))
		{
			swapParticles(x, y, x - 1, y);
		}
		else if (canMove(x + 1, y, water))
		{
			swapParticles(x, y, x + 1, y);
		}
	}
}

bool Particle::canMove(int x, int y, char particleType)
{
	//vector <char> moveOk;

	//switch (particleType)
	//{
	//case sand: moveOk = { none, water};
	//		   break;
	//case water: moveOk = { none };
	//			break;
	//}

	bool move = false;
	//for (int i = 0; i < moveOk.size(); i++)
	//{
	//	if (map[x][y] == moveOk[i])
	//	{
	//		move = true;
	//		break;
	//	}
	//}

	if (x > 0 && x < 800 && y>0 && y < 600)
	{
		if (particleType == sand)
		{
			if (map[x][y] == none) move = true;
			else if (map[x][y] == water) move = true;
		}

		else if (particleType == water)
		{
			if (map[x][y] == none) move = true;
		}
	}

	return move;
}

void Particle::swapParticles(int x, int y, int xn, int yn)
{
	char tmp = map[x][y];
	map[x][y] = map[xn][yn];
	map[xn][yn] = tmp;
}