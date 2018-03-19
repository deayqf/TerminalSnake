#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
using namespace std;

#define NRM "\x1B[0m"
#define RED "\x1B[31m"
#define GRN "\x1B[32m"

char wall = (char)178;
char head = (char)219;
char body = (char)254;

bool gameOver;
const int width = 22;
const int height = 22;
char map[width][height];
char prevMap[width][height];
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
const char* scoreText = GRN"Score: "NRM;

const unsigned short DARK_RED = FOREGROUND_RED;
const unsigned short DARK_GRN = FOREGROUND_GREEN;
const unsigned short DARK_BLU = FOREGROUND_BLUE;

void cls() { 
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = {0, 0};
    cout.flush();
    if(!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        return;
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
    DWORD written;
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);
    SetConsoleCursorPosition(hOut, topLeft);
}

void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void setConsoleColour(unsigned short colour)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    SetConsoleTextAttribute(hOut, colour);
}

void Setup() {
    system("@cls");
    printf("\x1B[?25l");
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = (rand() % 20) + 1;
    fruitY = (rand() % 20) + 1;
    score = 0;
}

void Load() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            if(i == 0 || i == 21 || j == 0 || j == 21)
                map[i][j] = wall;
            else if(i == fruitY && j == fruitX)
                map[i][j] = '@';
            else if(i == y && j == x)
                map[i][j] = head;
            else
                map[i][j] = ' ';
            for(int k = 0; k < nTail; k++) {
                if(tailX[k] == j && tailY[k] == i) {
                    map[i][j] = body;
                }
            }
        }
    }
}

void Draw() {
    memset((char*)prevMap, 0, width * height);
    for(int i = 0; i < width; i++) {
        int run = -1;
        for(int j = 0; j < height; j++) {
            if(map[i][j] == prevMap[i][j]) {
                if(run != -1) {
                    setCursorPosition(run, i);
                    cout.write(&map[i][run], j - run);
                    run = -1;
                }
            }
            else if(run == -1) {
                run = j;
            }
        }
        if(run != -1) {
            setCursorPosition(run, i);
            cout.write(&map[i][run], width - run);
        }
        cout << endl;
    }
    cout << scoreText << score << endl;
    cout.flush();
    memcpy((char*)prevMap, (char const*)map, width * height);
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
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir) {
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
    }
    if(x > width - 2 || x < 1 || y > height - 2 || y < 1)
        gameOver = true;
    for(int i = 0; i < nTail; i++) {
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
    if(x == fruitX && y == fruitY) {
        score++;
        fruitX = (rand() % 20) + 1;
        fruitY = (rand() % 20) + 1;
        nTail++;
    }
}

int main() {
    Setup();
    while(!gameOver) {
        Load();
        Draw();
        Input();
        Logic();
        Sleep(60);
    }
    printf("\x1B[?25h");
    return 0;
}
