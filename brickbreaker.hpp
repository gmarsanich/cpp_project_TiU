// File: brickbreaker.hpp
#ifndef BRICKBREAKER_HPP
#define BRICKBREAKER_HPP

//////// HEADERS

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
#include <random>
#include <vector>

// Local headers
#include "objects.hpp"

//////// CONSTANTS, DATA STRUCTURES AND INTERNAL FUNCTIONS

// Screen size constants
#define SCREEN_WIDTH 52
#define SCREEN_HEIGHT 20

// Min and max (x, y) values for the items in the screen
#define MIN_X 2
#define MIN_Y 2
#define MAX_X 49
#define MAX_Y 19

// Generates a handle for the console and initializes a variable for the cursor position
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

const int NO_BRICKS = 12;

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
 * @brief Fills a vector of size n with Brick objects
 *
 * @param size size of the vector
 * @return auto vector of bricks
 */
auto fillVector(int size) {
    std::vector<Brick> bricks = {};
    int vec_size = 0;
    while (vec_size <= size) {
        for (int x = SCREEN_WIDTH - 20; x <= MAX_X; x += 2) {
            for (int y = SCREEN_HEIGHT - 10; y <= MAX_Y; y += 2) {
                Brick *b = new Brick("\xDB", x, y);
                b->setPadding("   ");
                b->setVisible(1);
                bricks.push_back(*b);
            }
        }
        vec_size++;
        gotoxy(0, 0);
        std::cout << vec_size;
    }

    return bricks;
}

// Vector that holds the bricks
std::vector<Brick> bricks = fillVector(NO_BRICKS);

// Array that holds the possible ball directions: 1-top right, 2-top left, 3-bottom left, 4-bottom right
std::array<int, 4> dirs = {1, 2, 3, 4};

// Constructing the paddle and the ball

const int paddleStartXpos = 32;
const int paddleStartYpos = 20;

const int ballStartXpos = paddleStartXpos + 4;
const int ballStartYpos = paddleStartYpos;

Paddle *paddle = new Paddle("==========", paddleStartXpos, paddleStartYpos);
Ball *ball = new Ball("0", ballStartXpos, ballStartXpos);

bool startBall = false;      // Determines whether the ball has started moving or not
int bricksLeft = NO_BRICKS;  // Number of bricks left on the map
int dir = 1;                 // Default direction
bool win = false;            // Determines whether the game is won
bool lose = false;           // Determines whether the game is lost
int lives = 3;               // Number of lives
int score = 0;               // Game score

//////// FUNCTIONS FOR MAIN FILE

/**
 * @brief enables or disables debug information
 * @param enable bool
 */
void dbg(bool enable = false) {
    switch (enable) {
        case true:
            gotoxy(0, 0);
            std::cout << lives << " Lives left\n";
            std::cout << "starting ball direction: " << dir << "\n";
            std::cout << "Score: " << score;
            std::cout << "ball pos: " << ball->getxPos() << ", " << ball->getyPos() << "\n";
        case false:
            std::cout << "\n";
    }
}

/**
 * @brief Returns either of 2 random integers (inclusive)
 *
 * @param a integer a
 * @param b integer b
 * @return int
 */
int getRandomInt(int const a, int const b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 2);
    return (dis(gen) == 1) ? a : b;
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

/**
 * @brief Draws the bricks
 * @return void
 */
void drawBricks() {
    for (auto &brick : bricks) {
        if (brick.getVisible()) {
            gotoxy(brick.getxPos(), brick.getyPos());
            std::cout << brick.getShape() << brick.getPadding();
        }
    }
}

/**
 * @brief Checks if the ball hits the slider and changes the ball's direction if it does
 * @return void
 */
void ballHitSlider() {
    if (ball->getyPos() >= paddle->getyPos() && ball->getyPos() <= paddle->getyPos() + 8) {
        // if ball y position is greater than or equal to slider y position AND ball y position is smaller than slider y position + 8 (why 8?):
        // if ball x position is same as slider x position -1:
        // if direction is bottom left: direction becomes top left
        // else if direction is bottom right: direction becomes top right
        if (ball->getxPos() == ball->getxPos() - 1) {
            if (dir == 3)
                dir = 2;
            else if (dir == 4)
                dir = 1;
        }
    }
}

/**
 * @brief Removes one brick if it's hit by the ball
 * @return void
 */
void ballHitBrick() {
    for (auto &brick : bricks) {                                                                 // for each brick
        if (brick.getVisible()) {                                                                // if brick is visible (they all start as visible)
            if (ball->getyPos() >= brick.getyPos() && ball->getyPos() <= brick.getyPos() + 8) {  // if ball y position is greater than or equal to brick y position
                                                                                                 // and if ball y position is smaller than or equal to brick y position + 8 (8 again?)
                if (ball->getxPos() == brick.getxPos()) {                                        // if ball x position is equal to brick x position
                    if (brick.getIntegrity() < 1) {
                        brick.setVisible(0);  // brick is made invisible
                        bricksLeft--;         // number of bricks is reduced by 1
                    } else {
                        brick.updateIntegrity(1);  // remove 1 from integrity
                        // debugging only
                        gotoxy(0, 0);
                        std::cout << "integrity: " << brick.getIntegrity() << "\n";
                        score += 1;
                    }
                }
            }
        }
    }
}

/**
 * @brief Draws the ball at a specified (x, y) position
 * @return void
 */
void drawBall() {
    gotoxy(ball->getxPos(), ball->getyPos());
    std::cout << ball->getShape();
}

/**
 * @brief Draws the paddle at a specified (x, y) position
 * @return void
 */
void drawPaddle() {
    gotoxy(paddle->getxPos(), paddle->getyPos());
    std::cout << paddle->getShape();
}

/**
 * @brief Resets the ball to its initial positions
 * @return void
 */
void resetBall() {
    ball->setyPos(ballStartXpos);
    ball->setyPos(ballStartYpos);
}

/**
 * @brief Resets the paddle to its initial positions
 * @return void
 */
void resetPaddle() {
    paddle->setxPos(paddleStartXpos);
    paddle->setyPos(paddleStartXpos);
}

#endif