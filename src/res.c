#include "res.h"

// Loads file bricks.txt
// First line contains two space separated decimal numbers
// representing a number of rows and collums.
// Second line contains two space separated decimal numbers
// representing width and height of each brick.
// Then there is a new line for each row
// containing collums sequences of X and Y coordinates 
// (decimal space seperated numbers).  
void load_bricks(void)
{
    char* path = "../resources/bricks.txt";
    FILE *fp = fopen(path, "r");
    if (!fp)
    {
        fprintf(stderr, "An error occurred while trying to open file: %s\n", path);
        exit(1);
    }

    fscanf(fp, "%d %d\n", &rows, &cols);
    fscanf(fp, "%d %d\n", &width, &height);
    coords = (Coords *)malloc(rows * cols * sizeof(Coords));
    if(!coords)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(fp, "%d %d", &coords[i * cols + j].x, &coords[i * cols + j].y);
        }
    }

    if (fclose(fp))
    {
        fprintf(stderr, "An error occurred while trying to close file: %s\n", path);
        exit(1);
    }
}

// Loads file highscores.txt
void load_highscores(void)
{
    char* path = "../resources/highscores.txt";
    FILE *fp = fopen(path, "r");
    if (!fp)
    {
        fprintf(stderr, "An error occurred while trying to open file: %s\n", path);
        exit(1);
    }

    for (int i = 0; i < HIGHSCORE_NUM; i++)
    {
        fscanf(fp, "%d\n", &highscores[i]);
    }

    if (fclose(fp))
    {
        fprintf(stderr, "An error occurred while trying to close file: %s\n", path);
        exit(1);
    }
}

// Saves changes to file highscores.txt
void save_highscores(void)
{
    char* path = "../resources/highscores.txt";
    FILE *fp = fopen(path, "w");
    if (!fp)
    {
        fprintf(stderr, "An error occurred while trying to open file: %s\n", path);
        exit(1);
    }

    for (int i = 0; i < HIGHSCORE_NUM; i++)
    {
        fprintf(fp, "%d\n", highscores[i]);
    }

    if (fclose(fp))
    {
        fprintf(stderr, "An error occurred while trying to close file: %s\n", path);
        exit(1);
    }
}

// Resets file highscores.txt
// This function is never used.
void reset_highscores(void)
{
    char* path = "../resources/highscores.txt";
    FILE *fp = fopen(path, "w");
    if (!fp)
    {
        fprintf(stderr, "An error occurred while trying to open file: %s\n", path);
        exit(1);
    }

    for (int i = 0; i < HIGHSCORE_NUM; i++)
    {
        fprintf(fp, "%d\n", 100-i*10);
    }

    if (fclose(fp))
    {
        fprintf(stderr, "An error occurred while trying to close file: %s\n", path);
        exit(1);
    }
}

// Creates file bricks.txt
// This function is never used.
void level_generation(void)
{
    const int ROWS = 5;
    const int COLS = 15;
    char* path = "../resources/bricks.txt";
    FILE *fp = fopen(path, "w");
    if (!fp)
    {
        fprintf(stderr, "An error occurred while trying to open file: %s\n", path);
        exit(1);
    }

    brick.x = BORDER;
    brick.y = 2 * HUD;
    brick.w = (WINDOW_WIDTH - 2 * BORDER) / COLS;
    brick.h = (WINDOW_HEIGHT / 4) / ROWS;
    fprintf(fp, "%d %d\n", ROWS, COLS);
    fprintf(fp, "%d %d\n", brick.w, brick.h);
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            fprintf(fp, "%d %d ", brick.x, brick.y);
            brick.x += brick.w;
        }
        fprintf(fp, "\n");
        brick.x = BORDER;
        brick.y += brick.h;
    }

    if (fclose(fp))
    {
        fprintf(stderr, "An error occurred while trying to close file: %s\n", path);
        exit(1);
    }
}