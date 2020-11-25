#include<iostream>
#include<Windows.h>
#include <time.h>
#include <list>

// n = distance from start.
// -3 = unreachable.
// -2 = obstacle.
// -1 = default staring values.

const int WIDTH = 15;
const int HEIGHT = 15;

struct Coords
{
	int x = 0;
	int y = 0;
	int value = 0;
};

Coords grid[WIDTH][HEIGHT] = { {0} };

// "(" << grid[x][y].x << ", " << grid[x][y].y << ")"  << "\t= "

void displayGrid()
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			std::cout << grid[x][y].value << '\t';

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

void leeAlgoFlood3()
{
	// Set random start and end positions.
	bool xCoordsNogood = true;
	bool yCoordsNogood = true;
	int randStX;
	int randEndX;
	int randStY;
	int randEndY;
	
	// Keep re-generating randX positions until we have startX < endX
	while (xCoordsNogood)
	{
		randStX = rand() % (WIDTH - 1);
		randEndX = rand() % (WIDTH - 1);

		if (randStX < randEndX)
		{
			xCoordsNogood = false;
		}
	}
	
	// Keep re-generating randY positions until we have startY < endY
	while (yCoordsNogood)
	{
		randStY = rand() % (HEIGHT - 1);
		randEndY = rand() % (HEIGHT - 1);

		if (randStY < randEndY)
		{
			yCoordsNogood = false;
		}
	}

	std::cout << "\nStarting Pos: (" << randStX << ", " << randStY << ")\n";
	std::cout << "EndingPos: (" << randEndX << ", " << randEndY << ")\n";

	// Set starting point on grid to value 0 to represent 0 distance from the starting point.
	Coords startPos = grid[randStX][randStY];
	Coords endPos = grid[randEndX][randEndY];
	grid[randStX][randStY].value = 0;
	grid[randEndX][randEndY].value = 0;
	int currDistance = 0;
	bool isPath = false;

	for (int y = randStY; y < HEIGHT; ++y)
	{
		for (int x = randStX; x < WIDTH; ++x)
		{
			// Check if we've hit a blockage or a value that is still deafult.
			// If we have move to next cell in row and check again.
			if (grid[x][y].value < 0)
			{
				continue;
			}

			// Set the current distance from the start to the value of the cell we're currently on.
			currDistance = grid[x][y].value;

			// Check adjacent 'x' cell to the right is not blocked OR on an edge.
			if (grid[x + 1][y].value == -2 || (x + 1) == WIDTH)
			{
				// Blocked. Or edge. Do nothing.
			}
			else
			{
				grid[x + 1][y].value = grid[x][y].value + 1;
			}

			// Check adjacent 'y' cell below us is not blocked or an edge.
			if (grid[x][y + 1].value == -2 || (y + 1) == HEIGHT)
			{
				// Blocked. Or edge. Do nothing.
			}
			else
			{
				grid[x][y + 1].value = grid[x][y].value + 1;
			}

			// If our current grid position is the same as the end goal position, the there is a path.
			if (grid[x][y].x == endPos.x && grid[x][y].y == endPos.y)
			{
				// We have found the end position.
				// exit out of everything.
				grid[x][y].value = (char)35;
				isPath = true;
				break;
			}
		}

		if (isPath)
		{
			break;
		}
	}

	if (isPath)
	{
		std::cout << "\nThere was a path!\n";
	}
	else
	{
		std::cout << "\nThere was no path!\n";
	}
}

// SECOND ATTEMPT!
bool leeAlgoFlood()
{
	// Set starting point on grid to value 0 to represent 0 distance from the starting point.
	Coords startPos = grid[0][0];
	Coords endPos = grid[WIDTH - 1][HEIGHT - 1];
	grid[0][0].value = 0;
	int currDistance = 0;
	bool noPath = false;

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			if (grid[x][y].x == endPos.x && grid[x][y].y == endPos.y)
			{
				// We have found the end position.
				// exit out of everything.
			}

			// Check if we've hit a blockage or a value that is still deafult.
			// If we have move to next cell in row and check again.
			if (grid[x][y].value < 0)
			{
				continue;
			}

			// Set the current distance from the start to the value of the cell we're currently on.
			currDistance = grid[x][y].value;

			// Check adjacent 'x' cell to the right is not blocked OR on an edge.
			if (grid[x + 1][y].value == -2 || (x + 1) == WIDTH)
			{
				// Blocked. Or edge. Do nothing.
			}
			else
			{
				grid[x + 1][y].value = grid[x][y].value + 1;
			}

			// Check adjacent 'y' cell below us is not blocked or an edge.
			if (grid[x][y + 1].value == -2 || (y + 1) == HEIGHT)
			{
				// Blocked. Or edge. Do nothing.
			}
			else
			{
				grid[x][y + 1].value = grid[x][y].value + 1;
			}

			// Make sure we're not on the upper 'y' edge.
			if (y > 0)
			{
				// Check adjacent 'y' cell above us has been assigned a value.
				if (grid[x][y - 1].value == -1)
				{
					grid[x][y - 1].value = grid[x][y].value + 1;
				}
			}

			// Make sure we're not on the left 'x' edge.
			if (x > 0)
			{
				int currXPos = x;

				// Loop over all adjacent 'x' cells to the "left" of our current position and assign them relevant distance.
				while (grid[currXPos - 1][y].value == -1)
				{
					grid[currXPos - 1][y].value = grid[currXPos][y].value + 1;
					--currXPos;

					// Make sure we're not on the upper 'y' edge.
					if (y > 0)
					{
						// Check adjacent 'y' cell above us has been assigned a value.
						if (grid[currXPos][y - 1].value == -1)
						{
							grid[currXPos][y - 1].value = grid[currXPos][y].value + 1;
						}
					}
					
					if (currXPos == 0)
					{
						break;
					}
				}
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
		std::cout << "\nThere was no path!\n";
	}
	else
	{
		std::cout << "\nThere was a path!\n";
	}

	return noPath;
}

//std::list<Coords> leeAlgoTrace()
//{
//	std::list<Coords> route;
//
//	// Start at end coords
//	// Loop over checking adjacent cells for a value 1 less than currValue
//	// When we find one store the coords of that location in the list and move to that position
//	// Repeat until we are at the start coords.
//
//	Coords end = grid[WIDTH - 1][HEIGHT - 1];
//	Coords start = grid[0][0];
//
//	for (int y = (HEIGHT - 1); y > 0; --y)
//	{
//		for (int x = (WIDTH - 1); x > 0; --x)
//		{
//			if (grid[x - 1][y].value == (grid[x][y].value - 1))
//			{
//				// Store coords and move here.
//			}
//			else
//			{
//				// Check the adjacent y cell.
//			}
//		}
//	}
//}

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
	bool isPath = false;

	initGrid();
	displayGrid();
	leeAlgoFlood3();

	std::cout << '\n';
	
	displayGrid();

	/*if (isPath)
	{
		leeAlgoTrace();
	}*/

	return 0;
}