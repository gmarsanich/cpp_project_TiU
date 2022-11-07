// File: brickbreaker.hpp
#ifndef BRICKBREAKER_HPP
#define BRICKBREAKER_HPP

#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include <array>
#include <iostream>

//////// CONSTANTS AND DATA STRUCTURES

// Screen size constants
#define SCREEN_WIDTH 52
#define SCREEN_HEIGHT 20

// Min and max (x, y) values for the items in the screen
#define MIN_X 2
#define MIN_Y 2
#define MAX_X 49
#define MAX_Y 19

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

const int NO_BRICKS = 24;
std::array<std::array<int, 2>, NO_BRICKS> bricks = {{{2, 7},
                                                     {2, 12},
                                                     {2, 17},
                                                     {2, 22},
                                                     {2, 27},
                                                     {2, 32},
                                                     {2, 37},
                                                     {2, 42},
                                                     {4, 7},
                                                     {4, 12},
                                                     {4, 17},
                                                     {4, 22},
                                                     {4, 27},
                                                     {4, 32},
                                                     {4, 37},
                                                     {4, 42},
                                                     {6, 7},
                                                     {6, 12},
                                                     {6, 17},
                                                     {6, 22},
                                                     {6, 27},
                                                     {6, 32},
                                                     {6, 37},
                                                     {6, 42}}};

std::array<int, NO_BRICKS> visibleBricks = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
std::array<int, 2> sliderPos = {18, 22};
std::array<int, 2> ballPos = {17, 26};
std::array<int, 4> dirs = {1, 2, 3, 4};
std::array<int, 4> starting_dirs = {1, 2};

int startBall = 0;
int dir;  // 1-top right, 2-top left, 3-bottom left, 4-bottom right
int bricksLeft = NO_BRICKS;
bool win = 0;
bool lose = 0;

//////// FUNCTIONS FOR MAIN FILE

// Takes a random element from an std::array of any size
template <std::size_t SIZE>
int sample(std::array<int, SIZE> arr) {
    srand(time(NULL));
    int n = rand() % arr.size();
    return n;
}

// Moves the cursor to an (x, y) position
void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

// Makes the cursor of size 20 and changes its visibility
// using DWORD instead of unsigned int because Windows doesn't like it otherwise
void setcursor(bool visible, DWORD size) {
    if (size == 0) {
        size = 20;
    }
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = visible;
    cursor.dwSize = size;
    SetConsoleCursorInfo(console, &cursor);
}

// Draws the border around the playable area
void drawBorder() {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        gotoxy(i, 0);
        std::cout << "--";
        gotoxy(i, SCREEN_WIDTH);
        std::cout << "--";
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(0, i);
        std::cout << "|";
        gotoxy(SCREEN_WIDTH + 2, i);
        std::cout << "|";
    }
}

// Draws the bricks
void drawBricks() {
    for (int i = 0; i < NO_BRICKS; i++) {
        if (visibleBricks[i] == 1) {
            gotoxy(bricks[i][1], bricks[i][0]);
            std::cout << "####";
        }
    }
}

// Checks if the ball hits the slider and changes the ball's direction if it does
void ballHitSlider() {
    if (ballPos[1] >= sliderPos[1] && ballPos[1] <= sliderPos[1] + 8) {
        if (ballPos[0] == sliderPos[0] - 1) {
            if (dir == 3)
                dir = 2;
            else if (dir == 4)
                dir = 1;
        }
    }
}

// Removes one brick if it's hit by the ball
void ballHitBrick() {
    for (int i = 0; i < NO_BRICKS; i++) {
        if (visibleBricks[i] == 1) {
            if (ballPos[1] >= bricks[i][1] && ballPos[1] <= bricks[i][1] + 8) {
                if (ballPos[0] == bricks[i][0]) {
                    visibleBricks[i] = 0;
                    bricksLeft--;
                }
            }
        }
    }
}

#endif