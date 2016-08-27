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
		if (map[x][y + 1] == none)
		{
			int distance = rand() % 5 + 1;
			for (int i = distance; i >= 1; i--)
			{
				if (map[x][y + i] == none)
				{
					map[x][y + i] = sand;
					map[x][y] = none;
					break;
				}
			}
		}

		else
		{
			if (map[x + 1][y + 1] == none)
			{
				map[x + 1][y + 1] = sand;
				map[x][y] = none;
			}
			else if (map[x - 1][y + 1] == none)
			{
				map[x - 1][y + 1] = sand;
				map[x][y] = none;
			}
		}
	}

	else if (map[x][y] == water)
	{
		if (map[x][y + 1] == none)
		{
			int distance = rand() % 5 + 1;
			for (int i = distance; i >= 1; i--)
			{
				if (map[x][y + i] == none)
				{
					map[x][y + i] = water;
					map[x][y] = none;
					break;
				}
			}
		}

		else if ((map[x + 1][y + 1] == none) && (map[x - 1][y + 1] == none))
		{
			int r = rand() % 2;
			if (r == 0)
			{
				map[x + 1][y + 1] = water;
				map[x][y] = none;
			}
			else
			{
				map[x - 1][y + 1] = water;
				map[x][y] = none;
			}
		}
		else if (map[x + 1][y + 1] == none)
		{
			map[x + 1][y + 1] = water;
			map[x][y] = none;

		}
		else if (map[x - 1][y + 1] == none)
		{
			map[x - 1][y + 1] = water;
			map[x][y] = none;
		}

		else if ((map[x - 1][y] == none) && (map[x + 1][y] == none))
		{
			int r = rand() % 2;
			if (r == 0)
			{
				map[x - 1][y] = water;
				map[x][y] = none;
			}
			else
			{
				map[x + 1][y] = water;
				map[x][y] = none;
			}
		}

		else if (map[x - 1][y] == none)
		{
			map[x - 1][y] = water;
			map[x][y] = none;

		}
		else if (map[x + 1][y] == none)
		{
			map[x + 1][y] = water;
			map[x][y] = none;

		}
	}
}


