#include<iostream>
#include<Windows.h>
#include <time.h>

// n = distance from start.
// -3 = unreachable.
// -2 = obstacle.
// -1 = default staring values.

const int WIDTH = 5;
const int HEIGHT = 5;

struct Coords
{
	int x = 0;
	int y = 0;
	int value = 0;
};

Coords grid[WIDTH][HEIGHT] = { {0} };

void displayGrid()
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			std::cout << "[ " << "(" << grid[x][y].x << ", " << grid[x][y].y << ")"  << " = " << grid[x][y].value <<  " ] ";

			//Sleep(250);
		}

		std::cout << '\n';
		//Sleep(250);
	}
}

void initGrid()
{
	int randNumOfObstacles = rand() % (WIDTH * 2);	// generate a random number of obstacles based on size of grid.
	int obstaclesPlaced = 0;

	// Populate cells with default value -1.
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			grid[x][y].value = -1; // default initial values.

			// Set the coords.
			grid[x][y].x = x;
			grid[x][y].y = y;
		}	
	}

	// Populate random cells with obstacle value -2.
	while (obstaclesPlaced < randNumOfObstacles)
	{
		// generate random coords.
		int randX = rand() % WIDTH;		// rtn a number between 0 and WIDTH - 1
		int randY = rand() % HEIGHT;	// rtn a number between 0 and HEIGHT - 1

		while (randX == (WIDTH - 1) && randY == (HEIGHT - 1))
		{
			// Re-generate random coords. This prevents us having an obstacle in the end cell.
			randX = rand() % WIDTH;		// rtn a number between 0 and WIDTH - 1
			randY = rand() % HEIGHT;	// rtn a number between 0 and HEIGHT - 1
		}		

		grid[randX][randY].value = -2; // places obstacle at random location, doesn't matter if location is (0,0) as this will be manually set again at the start of the lee algo.
		++obstaclesPlaced;
	}
}

// SECOND ATTEMPT!
void leeAlgoFlood()
{
	// Set starting point on grid to value 0 to represent 0 distance from the starting point.
	grid[0][0].value = 0;
	Coords start = grid[0][0];
	Coords end = grid[WIDTH - 1][HEIGHT - 1];
	int currDistance = 0;
	bool counted = false;
	bool noPath = false;

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (grid[x][y].value < 0)
			{
				continue;
			}

			currDistance = grid[x][y].value;

			// Check adjacent cells are not blocked OR on an edge.
			if (grid[x + 1][y].value == -2 || (x + 1) == WIDTH)
			{
				// Blocked. Or edge. Do nothing.
			}
			else
			{
				grid[x + 1][y].value = grid[x][y].value + 1;
			}

			if (grid[x][y + 1].value == -2 || (y + 1) == HEIGHT)
			{
				// Blocked. Or edge. Do nothing.
			}
			else
			{
				grid[x][y + 1].value = grid[x][y].value + 1;
			}
		}
	}

	// Check if the last cell has a value > -1 stored in it, if so it means there is a path to it, otherwise there is not.
	if (grid[WIDTH - 1][HEIGHT - 1].value < 0)
	{
		noPath = true;
	}

	if (noPath)
	{
		std::cout << "There was no path!\n";
	}
	else
	{
		std::cout << "There was a path!\n";
	}
}

// FIRST ATTEMPT!
void leeAlgorithmFlood()
{
	// Set starting point on grid to value 0 to represent 0 distance from the starting point.
	grid[0][0].value = 0;
	Coords start = grid[0][0];
	Coords end = grid[WIDTH - 1][HEIGHT - 1];
	bool noPath = false;

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			// If we land on an obstacle, move onto next cell.
			if (grid[x][y].value == -2)
			{
				continue;
			}
			else
			{
				if (grid[x][y].value > -1)
				{
					// EDGE CASE 1:
					if (x == (WIDTH - 1))
					{
						// We've reached the edge, do not check adjacent positive x direction cells (this is off the end!) Check y direction only.
						if (grid[x][y + 1].value == -2)
						{
							// We hit an obstacle. Do nothing.
						}
						else
						{
							// Otherwise update the cell with the appropriate distance value. Namely, whatever the previous cells value was + 1
							grid[x][y + 1].value = grid[x][y].value + 1;
						}
					}
					else if (y == (HEIGHT - 1))		// EDGE CASE 2:
					{
						// We've reached the edge, do not check adjacent positive y direction cells (this is off the end!) Check x direction only.
						if (grid[x + 1][y].value == -2)
						{
							// We hit an obstacle. Do nothing.
						}
						else
						{
							// Otherwise update the cell with the appropriate distance value. Namely, whatever the previous cells value was + 1
							grid[x + 1][y].value = grid[x][y].value + 1;
						}
					}
					else
					{
						// Check both x and y directions.
						// Check first adjacent position in the positve x direction, if a -2 is stored there, we have hit an obstacle.
						if (grid[x + 1][y].value == -2)
						{
							// We hit an obstacle. Do nothing.
						}
						else
						{
							// Otherwise update the cell with the appropriate distance value. Namely, whatever the previous cells value was + 1
							grid[x + 1][y].value = grid[x][y].value + 1;
						}

						// Check second adjacent position, in the positive y direction, if a -2 is stored there, we have hit an obstacle.
						if (grid[x][y + 1].value == -2)
						{
							// We hit an obstacle. Do nothing.
						}
						else
						{
							// Otherwise update the cell with the appropriate distance value. Namely, whatever the previous cells value was + 1
							grid[x][y + 1].value = grid[x][y].value + 1;
						}
					}
				}
				else
				{
					// If we arrive here, it is because a cell has not managed to be assigned a value yet, due to obstacles being in the way.
					// Check the cell to its positive x direction is not also an obstacle.
					if (grid[x + 1][y].value == -2)
					{
						// We hit an obstacle, so check the y direction.

						// Check the cell to its positive y direction is not also an obstacle.
						if (grid[x][y + 1].value == -2)
						{
							// We hit another obstacle. If this cell is surrounded by obstacles it is unreachable!
							grid[x][y].value = -3;
							noPath = true;
							break;
						}
						else
						{
							// Otherwise update the cell with the appropriate distance value. Namely, whatever the previous cells value was + 1
							grid[x][y].value = grid[x][y + 1].value + 1;
						}
					}
					else
					{
						// This cell is still the default -1, probably due to being blocked by obstacles, so set it to whatever is adjacent to it in the positive x direction + 1.
						grid[x][y].value = grid[x + 1][y].value + 1;
					}					
				}
			}
		}
	}
}

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	initGrid();
	displayGrid();
	leeAlgoFlood();

	std::cout << '\n';
	
	displayGrid();

	return 0;
}