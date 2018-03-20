#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include "cursor.h"
using namespace std;
#include "direction.h"
#include "tile.h"
#include "snake.h"
#include "level.h"

int get_rand(int max, int min)
{
    return (rand() % max) + min;
}

struct Game
{
    int width = 22;
    int height = 22;
    int score = 0;
    bool quit = false;
    Snake* snake = NULL;
    Level* level = NULL;
    Game();
    ~Game();
    void input();
    void logic();
    void load();
    void show_score();
    void loop();
};

Game::Game()
{
    cls();
    showCursor(quit);
    snake = new Snake(width / 2, height / 2, (char)219, (char)254, STOP);
    level = new Level(width, height, (char)178, get_rand(20, 1), get_rand(20, 1), '@');
}

Game::~Game()
{
    level->~Level();
    snake->~Snake();
    showCursor(quit);
}

void Game::input()
{
    if (_kbhit()) 
    {
        char key = _getch();
        if (key != 'q')
        {
            snake->set_dir(key);
        }
        else
        {
            quit = true;
        }
    }
}

void Game::logic()
{
    snake->update();
    if (snake->did_die(width, height))
    {
        quit = true;
    }
    else if (snake->did_get_fruit(level->fruit_x, level->fruit_y))
    {
        score++;
        level->fruit_x = get_rand(20, 1);
        level->fruit_y = get_rand(20, 1);
    }
}

void Game::load()
{
    for (int y = 0; y < level->height; y++)
    {
        for (int x = 0; x < level->width; x++)
        {
            if (y == 0 || y == level->height - 1 || x == 0 || x == level->width - 1)
            {
                level->set_tile(x, y, WALL);
            }
            else if (y == level->fruit_y && x == level->fruit_x)
            {
                level->set_tile(x, y, FRUIT);
            }
            else if (y == snake->y_pos && x == snake->x_pos)
            {
                level->set_tile(x, y, HEAD, snake->head);
            }
            else
            {
                level->set_tile(x, y, FLOOR);
            }
            for (int z = 0; z < snake->tail_len; z++)
            {
                if (snake->tail_x[z] == x && snake->tail_y[z] == y)
                {
                    level->set_tile(x, y, TAIL, snake->body);
                }
            }
        }
    }
}

void Game::show_score()
{
    setCursorPosition(0, height + 1);
    cout << "Score: " << score;
}

void Game::loop()
{
    while (!quit)
    {
        load();
        input();
        logic();
        level->draw();
        show_score();
        Sleep(60);
    }
}
