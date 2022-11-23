// File: console.hpp
#ifndef CONSOLE_HPP
#define CONSOLE_HPP

// External headers
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Generates a handle for the console and initializes a variable for the cursor position
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

// Screen size constants
#define SCREEN_WIDTH 52
#define SCREEN_HEIGHT 20

// Min and max (x, y) values for the items in the screen

// Bottom right corner
#define MAX_X 49
#define MAX_Y 19

// Top left corner
#define MIN_X 2
#define MIN_Y 2

////////////// CONSOLE FUNCTIONS

/**
 * @brief Moves the cursor to an (x, y) position
 *
 * @param x x coordinate
 * @param y y coordinate
 * @return ** void
 */
void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

/**
 * @brief Makes the cursor of size 20 and changes its visibility
 *
 * @param visible bool, determines visibility of cursor
 * @param size DWORD (using DWORD instead of unsigned int because Windows doesn't like it otherwise)
 */
void setcursor(bool visible, DWORD size) {
    if (size == 0) {
        size = 20;
    }
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = visible;
    cursor.dwSize = size;
    SetConsoleCursorInfo(console, &cursor);
}

#endif