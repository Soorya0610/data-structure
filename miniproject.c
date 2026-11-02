
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

int gameOver;
int x, y, foodX, foodY, score;

int tailX[100], tailY[100];
int tailLength;

enum Direction {
    STOP = 0, LEFT, RIGHT, UP, DOWN
};

enum Direction dir;

void Setup()
{
    gameOver = 0;
    dir = STOP;

    x = WIDTH / 2;
    y = HEIGHT / 2;

    srand(time(0));

    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;

    score = 0;
    tailLength = 0;
}

void Draw()
{
    system("cls");

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");

    printf("\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                printf("#");

            if (i == y && j == x)
                printf("O");

            else if (i == foodY && j == foodX)
                printf("*");

            else
            {
                int print = 0;

                for (int k = 0; k < tailLength; k++)
                {
                    if (tailX[k] == j &&
                        tailY[k] == i)
                    {
                        printf("o");
                        print = 1;
                    }
                }

                if (!print)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#");
        }

        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");

    printf("\nScore: %d\n", score);
    printf("Controls: W = Up, S = Down, A = Left, D = Right");
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'a':
            case 'A':
                if (dir != RIGHT)
                    dir = LEFT;
                break;

            case 'd':
            case 'D':
                if (dir != LEFT)
                    dir = RIGHT;
                break;

            case 'w':
            case 'W':
                if (dir != DOWN)
                    dir = UP;
                break;

            case 's':
            case 'S':
                if (dir != UP)
                    dir = DOWN;
                break;

            case 'x':
            case 'X':
                gameOver = 1;
                break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
        case LEFT:
            x--;
            break;

        case RIGHT:
            x++;
            break;

        case UP:
            y--;
            break;

        case DOWN:
            y++;
            break;

        default:
            break;
    }

    // Wall collision
    if (x < 0 || x >= WIDTH ||
        y < 0 || y >= HEIGHT)
    {
        gameOver = 1;
    }

    // Snake body collision
    for (int i = 0; i < tailLength; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }

    // Food collection
    if (x == foodX && y == foodY)
    {
        score += 10;
        tailLength++;

        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    }
}

int main()
{
    Setup();

    while (!gameOver)
    {
        Draw();
        Input();
        Logic();

        Sleep(100);
    }

    printf("\n\nGAME OVER!");
    printf("\nFinal Score: %d\n", score);

    return 0;
}
