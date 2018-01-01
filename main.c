#include <stdio.h>
#include <stdlib.h>
#include "time.h"

#define MAZE_WIDTH 15
#define MAZE_HEIGHT 15
#define NUMBER_OF_WALLS_PER_CELL 2

enum { NORTH, WEST };

typedef struct Cell Cell;
struct Cell {
    unsigned int idPath;
    unsigned int walls[NUMBER_OF_WALLS_PER_CELL];
};

void displayMaze(Cell maze[][MAZE_HEIGHT]);

int main()
{
    srand(time(NULL));

    Cell maze[MAZE_WIDTH][MAZE_HEIGHT];
    int i, j, k, xVector, yVector;
    int idCell1, idCell2;
    int counterBrokenWalls = 0;

    for (i = 0 ; i < MAZE_WIDTH ; i++)
    {
        for (j = 0 ; j < MAZE_HEIGHT ; j++)
        {
            maze[i][j].idPath = i + j * MAZE_WIDTH;
            for (k = 0 ; k < NUMBER_OF_WALLS_PER_CELL ; k++)
                maze[i][j].walls[k] = 1;
        }
    }

    while (counterBrokenWalls < MAZE_WIDTH * MAZE_HEIGHT - 1)
    {
        i = rand() % MAZE_WIDTH;
        j = rand() % MAZE_HEIGHT;
        k = rand() % NUMBER_OF_WALLS_PER_CELL;

        if (maze[i][j].walls[k])
        {
            if (!((k == NORTH && j == 0) || (k == WEST && i == 0)))
            {
                switch (k)
                {
                    case NORTH:
                        xVector = 0;
                        yVector = -1;
                        break;
                    case WEST:
                    default:
                        xVector = -1;
                        yVector = 0;
                        break;
                }
                if (maze[i][j].idPath != maze[i + xVector][j + yVector].idPath)
                {
                    maze[i][j].walls[k] = 0;
                    counterBrokenWalls++;
                    idCell1 = maze[i][j].idPath;
                    idCell2 = maze[i + xVector][j + yVector].idPath;

                    for (i = 0 ; i < MAZE_WIDTH ; i++)
                        for (j = 0 ; j < MAZE_HEIGHT ; j++)
                            if (maze[i][j].idPath == idCell2)
                                maze[i][j].idPath = idCell1;
                }
            }
        }
    }

    displayMaze(maze);
    return 0;
}

void displayMaze(Cell maze[][MAZE_HEIGHT])
{
    int i, j;
    for (j = 0 ; j < MAZE_HEIGHT ; j++)
    {
        for (i = 0 ; i < MAZE_WIDTH ; i++)
        {
            if (maze[i][j].walls[NORTH])
                printf("+---");
            else
                printf("+   ");
        }
        printf("+");
        printf("\n");
        for (i = 0 ; i < MAZE_WIDTH ; i++)
        {
            if (maze[i][j].walls[WEST])
                printf("|   ");
            else
                printf("    ");
        }
        printf("|");
        printf("\n");
    }
    for (i = 0 ; i < MAZE_WIDTH ; i++)
    {
        printf("+---");
    }
    printf("+");
}
