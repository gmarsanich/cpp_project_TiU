// File: brickbreaker.hpp
#ifndef BRICKBREAKER_HPP
#define BRICKBREAKER_HPP

//////// HEADERS

// Builtin headers
#include <array>
#include <iostream>
#include <vector>

// Local headers
#include "console.hpp"
#include "objects.hpp"

//////// CONSTANTS, DATA STRUCTURES AND INTERNAL FUNCTIONS

const int NO_BRICKS = 6;

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
        for (int x = MIN_X + 2; x <= MAX_X; x += 2) {
            for (int y = MIN_Y + 2; y <= MAX_Y / 2; y += 2) {
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

// Constructing the paddle and the ball

Paddle *paddle = new Paddle("==========", paddleStartXpos, paddleStartYpos);
Ball *ball = new Ball("0", ballStartXpos, ballStartXpos);

int bricksLeft = NO_BRICKS;  // Number of bricks left on the map
bool win = false;            // Determines whether the game is won
bool lose = false;           // Determines whether the game is lost
int lives = 3;               // Number of lives
int score = 0;               // Game score

//////// FUNCTIONS FOR MAIN FILE

/**
 * @brief enables or disables debug information
 * @param enable bool
 * @details Shows ball direction and ball position, left and right corners of the playable area, and the paddle/ball spawn points
 */
void dbg(bool enable = false) {
    switch (enable) {
        case true:
            gotoxy(SCREEN_WIDTH, SCREEN_HEIGHT + 1);
            std::cout << "DEBUG:\n";
            std::cout << "ball dir: " << ball->getDir() << "\n";
            std::cout << "ball pos: " << ball->getxPos() << ", " << ball->getyPos() << "\n";

            gotoxy(MIN_X, MIN_Y);
            std::cout << "min here\n";

            gotoxy(paddleStartXpos, paddleStartYpos);
            std::cout << "paddle spawn here\n";

            gotoxy(ballStartXpos, ballStartYpos);
            std::cout << "ball spawn here\n";

        default:
            std::cout << "";
    }
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
            if (ball->getDir() == 3)
                ball->setDir(2);
            else if (ball->getDir() == 4)
                ball->setDir(1);
        }
    }
}

/**
 * @brief Removes integrity from a brick if it's hit by the ball
 * @return void
 */
void ballHitBrick() {
    for (auto &brick : bricks) {
        if (brick.getVisible()) {
            if (ball->getyPos() >= brick.getyPos() && ball->getyPos() <= brick.getyPos() + 8) {
                if (ball->getxPos() == brick.getxPos()) {
                    if (brick.getIntegrity() < 1) {
                        brick.setVisible(0);
                        bricksLeft--;
                    } else {
                        brick.updateIntegrity(1);
                        // debugging only
                        gotoxy(0, 0);
                        std::cout << "integrity: " << brick.getIntegrity() << "\n";
                        score += 1;
                        ball->switchDir(ball->getDir());
                    }
                }
            }
        }
    }
}

#endif