#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include <string.h>
using namespace std;

char* WALL = (char*)"\x1B[35m\xB2\x1B[0m";
char* HEAD = (char*)"\x1B[36m\xDB\x1B[0m";
char* BODY = (char*)"\x1B[36m\xFE\x1B[0m";
char* FRUIT = (char*)"\x1B[31m\x9D\x1B[0m";
char* BLANK = (char*)" ";
char* NL = (char*)"\n";

#define HEIGHT 22
#define WIDTH 22

const int width = 20;
const int height = 20;

bool gameOver;
int headX, headY, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

//string map[WIDTH][HEIGHT];
char map[HEIGHT][250];
char prevMap[HEIGHT][250];

void setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void Setup() {
    system("@cls");
    gameOver = false;
    dir = STOP;
    headX = width / 2;
    headY = height / 2;
    fruitX = (rand() % 20) + 1;
    fruitY = (rand() % 20) + 1;
    score = 0;
}

void load() {
    int i = 0;
    for(int x = 0; x < HEIGHT; x++) {
        i = 0;
        for(int y = 0; y < WIDTH; y++) {
            char* tile;
            if(x == 0 || y == 0 || x == HEIGHT-1 || y == WIDTH-1) {
                tile = WALL;
            } else if(x == headX && y == headY) {
                tile = HEAD;
            } else if(x == fruitX && y == fruitY) {
                tile = FRUIT;
            } else {
                tile = BLANK;
            }
            //map[x][y] = tile;
            for(int z = 0; z < strlen(tile); z++) {
                map[x][i] = tile[z];
                i++;
            }
        }
    }
}

void draw() {
    memset((char*)prevMap, 0, HEIGHT * 250);
    for(int x = 0; x < HEIGHT; x++) {
        int run = -1;
        for(int y = 0; y < WIDTH; y++) {
            if(map[x][y] == prevMap[x][y]) {
                if(run != -1) {
                    setCursorPosition(run, x);
                    cout.write(&map[x][run], strlen(&map[x][0]) - (run*10));
                    run = -1;
                }
            }
            else if(run == -1) {
                run = y;
            }
        }
        if(run != -1) {
            setCursorPosition(run, x);
            cout.write(&map[x][run], strlen(&map[x][0]) - (run*10));
        }
        cout << endl;
    }
    cout.flush();
    memcpy((char*)prevMap, (char const*)map, HEIGHT * 250);
}

void Input() {
    if(_kbhit()) {
        switch(_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Logic() {
    // int prevX = tailX[0];
    // int prevY = tailY[0];
    // int prev2X, prev2Y;
    // tailX[0] = x;
    // tailY[0] = y;
    // for(int i = 1; i < nTail; i++) {
    //     prev2X = tailX[i];
    //     prev2Y = tailY[i];
    //     tailX[i] = prevX;
    //     tailY[i] = prevY;
    //     prevX = prev2X;
    //     prevY = prev2Y;
    // }
    switch(dir) {
        case LEFT:
            headY--;
            break;
        case RIGHT:
            headY++;
            break;
        case UP:
            headX--;
            break;
        case DOWN:
            headX++;
            break;
    }
    if(headX > WIDTH - 2 || headX < 1 || headY > HEIGHT - 2 || headY < 1)
        gameOver = true;
    // for(int i = 0; i < nTail; i++) {
    //     if(tailX[i] == x && tailY[i] == y)
    //         gameOver = true;
    // }
    if(headX == fruitX && headY == fruitY) {
        score++;
        fruitX = (rand() % 20) + 1;
        fruitY = (rand() % 20) + 1;
        //nTail++;
    }
}

int main() {
    Setup();
    while(!gameOver) {
        load();
        draw();
        Input();
        Logic();
        Sleep(60);
    }

    // cout << endl;
    // int size = 0;
    // char line[22][250];
    // int x = 0;
    // for(int i = 0; i < 22; i++) {
    //     x = 0;
    //     for(int j = 0; j < 22; j++) {
    //         const char* tile = map[i][j].c_str();
    //         for(int k = 0; k < strlen(tile); k++) {
    //             line[i][x] = tile[k];
    //             x++;
    //         }
    //     }
    // }
    // cout << endl;
    // for(int i = 0; i < 22; i++) {
    //     cout.write(&line[i][0], strlen(&line[i][0]));
    //     cout << endl;
    // }
    // cout << endl;
    // cout << "Size: " << sizeof(map) << endl;
    return 0;
}
