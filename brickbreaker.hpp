// File: brickbreaker.hpp
#ifndef BRICKBREAKER_HPP
#define BRICKBREAKER_HPP

// External headers
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// Builtin headers
#include <array>
#include <iostream>
#include <vector>

// Local headers
#include "objects.hpp"

//////// CONSTANTS, DATA STRUCTURES AND INTERNAL FUNCTIONS

// Screen size constants
#define SCREEN_WIDTH 640   // -> 640, default 52
#define SCREEN_HEIGHT 480  // -> 480, default 20

// Min and max (x, y) values for the items in the screen
#define MIN_X 2
#define MIN_Y 2
#define MAX_X 673  // => 673, default 49
#define MAX_Y 479  // => 479, default 19

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

const int NO_BRICKS = 24;

// No other way to make this work
// Fills a vector of Brick objects. Size specified by the size parameter

auto fillVector(int size) {
    std::vector<Brick> bricks = {};
    int vec_size = 0;
    while (vec_size <= size) {
        for (int x = 0; x <= 6; x++) {
            for (int y = 7; y <= 42; y += 5) {
                Brick *b = new Brick("###", x, y);
                b->setPadding("   ");
                bricks.push_back(*b);
            }
        }
        vec_size++;
    }

    return bricks;
}

std::vector<Brick> bricks = fillVector(NO_BRICKS);
std::array<int, NO_BRICKS> visibleBricks = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
std::array<int, 2> sliderPos = {18, 22};
std::array<int, 2> ballPos = {17, 26};
std::array<int, 4> dirs = {1, 2, 3, 4};
std::array<int, 4> starting_dirs = {1, 2};

Paddle *paddle = new Paddle("==========", sliderPos[0], sliderPos[1]);
Ball *ball = new Ball("0", ballPos[0], ballPos[1]);
int startBall = 0;
int bricksLeft = NO_BRICKS;
int dir = 1;  // 1-top right, 2-top left, 3-bottom left, 4-bottom right
bool win = 0;
bool lose = 0;

//////// FUNCTIONS FOR MAIN FILE

// Takes a random element from an std::array of any size
template <std::size_t SIZE>
int sample(std::array<int, SIZE> arr) {
    srand(time(NULL));
    int n = rand() % arr.size();
    return n + 1;
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
            gotoxy(bricks[i].getxPos(), bricks[i].getyPos());
            std::cout << bricks[i].getShape() << bricks[i].getPadding();
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
            if (ballPos[1] >= bricks[i].getyPos() && ballPos[1] <= bricks[i].getyPos() + 8) {
                if (ballPos[0] == bricks[i].getxPos()) {
                    visibleBricks[i] = 0;
                    bricksLeft--;
                }
            }
        }
    }
}

// Draws the ball at its initial position
void drawBall() {
    gotoxy(ball->getxPos(), ball->getyPos());
    std::cout << ball->getShape();
}

// Draws the paddle ball at its initial position
void drawPaddle() {
    gotoxy(paddle->getxPos(), paddle->getyPos());
    std::cout << paddle->getShape();
}
#endif