#ifndef CURSOR_H
#define CURSOR_H

#include <Windows.h>

void cls() 
{ 
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = {0, 0};
    std::cout.flush();
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

void showCursor(bool flag)
{
    static const HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(out, &cursor_info);
    cursor_info.bVisible = flag;
    SetConsoleCursorInfo(out, &cursor_info);
}

#endif