#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void pp(int *grid[], const int width, const int height)
{
    int i, j;
    for(i = 0; i < width - 1; i++)
    {
        for(j = 0; j < height - 1; j++)
        {
            if(grid[i][j])
            {
                printf("#");
            }
            else {
                printf(" ");
            }
        }
	printf("\n");
    }
}
void gen(int *grid[], int *new[], const int width, const int height)
{
	int i, j;
	for(i = 1; i < width - 2; i++)
	{
		for(j = 1; j < height - 2; j++)
		{
			int n = 0;
			int x,y;
			for(x = -1; x <= 1; x++)
			{
				for(y = -1; y <= 1; y++)
				{
					n += grid[i+x][j+y];
				}
			}
			n -= grid[i][j];
			if(grid[i][j] && n < 2)
			{
				new[i][j] = 0;
			}
			else if(grid[i][j] && n > 3)
			{
				new[i][j] = 0;
			}
			else if(!grid[i][j] && n == 3)
			{
				new[i][j] = 1;
			}
			else
			{
				new[i][j] = grid[i][j];
			}
			
		}
	}
}
void iidup(int *grid[], int *new[], const int width, const int height)
{
	int i, j;
	for(i = 0; i < width - 1; i++)
	{
		for(j = 0; j < height - 1; j++)
		{
			new[i][j] = grid[i][j];
		}
	}
}
		
int main(int argv, char *argc[]) {
	int width = 50;
	int height = 100;
	int row, column;
	int **grid;

	int **new;
    srand(time(NULL));


    grid = malloc(width * sizeof(int *));

    new = malloc(width * sizeof(int *));

    for(row = 0; row < width - 1; row++)
    {
        grid[row] = malloc(height * sizeof(int));
        new[row] = malloc(height * sizeof(int));

        for(column = 0; column <height -1; column++)
        {
            grid[row][column] = (rand() % 10 == 1) ? 1 : 0;
            new[row][column] = 0;

        }
    }

	//iidup(grid, new, width, height);
		
	printf("%c[2J%c[;H",(char) 27, (char) 27);
	while(1)
	{
		printf("%c[2J%c[;H",(char) 27, (char) 27);
		pp(grid, width, height);
		gen(grid, new, width, height);
		iidup(new, grid, width, height);
		usleep(90000);
	}
	return 0;
}

