#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#if defined(_WIN32)
#define PLATFORM_NAME "windows" // windows
#include <windows.h>

#elif defined(_WIN64)
#define PLATFORM_NAME "windows" // windows
#include <windows.h>

#elif defined(__linux__)
#define PLATFORM_NAME "linux" // linux
#include <unistd.h>
#include <sys/ioctl.h>


#else
#define PLATFORM_NAME NULL
#endif

//Pretty Printer for now alive --> #
void pp(int *grid[], const int width, const int height) {
    int i, j;

    for (i = 0; i < width - 1; i++) {
        for (j = 0; j < height - 1; j++) {
            if (grid[i][j]) printf("#");

            else printf(" ");
        }

        printf("\n");
    }
}

// Next Generation function
void gen(int *grid[], int *new[], const int width, const int height) {
    int n, i, j, x, y;

    for (i = 1; i < width - 2; i++) {
        for (j = 1; j < height - 2; j++) {
            n = 0;
            for (x = -1; x <= 1; x++) {
                for (y = -1; y <= 1; y++) {
                    n += grid[i + x][j + y];
                }
            }

            n -= grid[i][j]; // remove itself

            if (grid[i][j] && n < 2) new[i][j] = 0; // dies of loneliness

            else if (grid[i][j] && n > 3) new[i][j] = 0; // dies of overpopulation

            else if (!grid[i][j] && n == 3) new[i][j] = 1; // revives from 3 near

            else new[i][j] = grid[i][j]; // stay the same
        }
    }
}

// **int duplication function to copy the grid
void iidup(int *grid[], int *new[], const int width, const int height) {
    int i, j;

    for (i = 0; i < width - 1; i++) {
        for (j = 0; j < height - 1; j++) new[i][j] = grid[i][j];
    }
}


int main(int argv, char *argc[]) {
	int coolPattern = 1; 
    int width, height;

#if defined(__linux__)
    struct winsize sz;
    ioctl(0, TIOCGWINSZ, &sz);
    width = sz.ws_row;
    height = sz.ws_col;
#else
    width = 300;
    height = 200;
#endif


    int row, column;
    int **grid, **new;

    srand(time(NULL));

    grid = malloc(width * sizeof(int *));
    new = malloc(width * sizeof(int *));

    for (row = 0; row < width - 1; row++) {
        grid[row] = malloc(height * sizeof(int));
        new[row] = malloc(height * sizeof(int));

        for (column = 0; column < height - 1; column++) {
            if(coolPattern) grid[row][column] =  0; // just the prob of alive cell on spawn
            else grid[row][column] = (rand() % 10 == 1) ? 1 : 0; // just the prob of alive cell on spawn

        }
    }

	if(coolPattern){
		grid[(int)width/2][(int)height/2]= 1;
		grid[(int)width/2 - 1][(int)height/2]= 1;
		grid[width/2 - 2][height/2 + 1] = 1;
		grid[width/2][height/2 + 1] = 1;
		grid[width/2][height/2 + 2] = 1;
		grid[width/2][height/2 - 1] = 1;
		grid[width/2 - 1][height/2 - 1] = 1;
		grid[width/2 - 2][height/2 - 2] = 1;
		grid[width/2][height/2 - 2] = 1;
		grid[width/2][height/2 - 3] = 1;


	}
	    printf("%c[2J%c[;H", (char) 27, (char) 27); // clear screen

    while (1) //infinite loop for now keyboard int to exit
    {
        printf("%c[2J%c[;H", (char) 27, (char) 27);

        pp(grid, width, height);
        gen(grid, new, width, height);
        iidup(new, grid, width, height);

        usleep(18000); // sleep for 180 milsecs
    }
	free(grid);
	free(new);

    return 0;
}

