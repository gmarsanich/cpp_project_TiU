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
#define SCREEN_WIDTH 640   // default 640
#define SCREEN_HEIGHT 480  // default 480

// Min and max (x, y) values for the items in the screen
#define MIN_X 2
#define MIN_Y 2
#define MAX_X 640  // => default 637
#define MAX_Y 480  // => default 479

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

const int NO_BRICKS = 24;

// No other way to make this work
// Fills a vector of Brick objects. Size specified by the size parameter

auto fillVector(int size) {
    std::vector<Brick> bricks = {};
    int vec_size = 0;
    while (vec_size <= size) {
        for (int x = 300; x <= MAX_X; x++) {         // max 640
            for (int y = 150; y <= MAX_Y; y += 5) {  // max 480
                Brick *b = new Brick("\xDB", x, y);
                b->setPadding("   ");
                b->setVisible(1);
                bricks.push_back(*b);
            }
        }
        vec_size++;
    }

    return bricks;
}

std::vector<Brick> bricks = fillVector(NO_BRICKS);
std::array<int, 2> sliderPos = {1, 2};  // {x, y}
std::array<int, 2> ballPos = {3, 3};
std::array<int, 4> dirs = {1, 2, 3, 4};  // 1-top right, 2-top left, 3-bottom left, 4-bottom right
std::array<int, 4> starting_dirs = {1, 2};

Paddle *paddle = new Paddle("==========", sliderPos[0], sliderPos[1]);
Ball *ball = new Ball("0", ballPos[0], ballPos[1]);
int startBall = 0;
int bricksLeft = NO_BRICKS;
int dir = 1;
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

// Draws the bricks
void drawBricks() {
    for (auto &brick : bricks) {
        if (brick.getVisible()) {
            gotoxy(brick.getxPos(), brick.getyPos());
            std::cout << brick.getShape() << brick.getPadding();
        }
    }
}

// Checks if the ball hits the slider and changes the ball's direction if it does
void ballHitSlider() {
    if (ballPos[1] >= sliderPos[1] && ballPos[1] <= sliderPos[1] + 8) {
        // if ball y position is greater than or equal to slider y position AND ball y position is smaller than slider y position + 8 (why 8?):
        // if ball x position is same as slider x position -1:
        // if direction is bottom left: direction becomes top left
        // else if direction is bottom right: direction becomes top right
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
    // range based for loop to avoid messing around with indices
    for (auto &brick : bricks) {                                                       // for each brick
        if (brick.getVisible()) {                                                      // if brick is visible (they all start as visible)
            if (ballPos[1] >= brick.getyPos() && ballPos[1] <= brick.getyPos() + 8) {  // if ball y position is greater than or equal to brick y position
                                                                                       // and if ball y position is smaller than or equal to brick y position + 8 (8 again?)
                if (ballPos[0] == brick.getxPos()) {                                   // if ball x position is equal to brick x position
                    brick.setVisible(0);                                               // brick is made invisible

                    bricksLeft--;  // number of bricks is reduced by 1
                }
            }
        }
    }
}

// Draws the ball at its initial position
// void drawBall() {
//     gotoxy(ball->getxPos(), ball->getyPos());
//     std::cout << ball->getShape();
// }

// // Draws the paddle ball at its initial position
// void drawPaddle() {
//     gotoxy(paddle->getxPos(), paddle->getyPos());
//     std::cout << paddle->getShape();
// }

void drawBall() {
    gotoxy(ballPos[1], ballPos[0]);
    std::cout << "0";
}

// Draws the paddle ball at its initial position
void drawPaddle() {
    gotoxy(sliderPos[1], sliderPos[0]);
    std::cout << "=========";
}
#endif