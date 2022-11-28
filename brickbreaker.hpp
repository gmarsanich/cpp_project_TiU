// File: brickbreaker.hpp
#ifndef BRICKBREAKER_HPP
#define BRICKBREAKER_HPP

//////// HEADERS

// Builtin headers
#include <array>
#include <iostream>
#include <vector>

// Local headers
#include "agent.hpp"
#include "console.hpp"
#include "objects.hpp"

//////// CONSTANTS, DATA STRUCTURES AND INTERNAL FUNCTIONS

namespace brbk {
// namespace to limit conflicting variable names

const int NO_BRICKS = 6;

/**
 * @brief Fills a vector of size n with obj::Brick objects
 *
 * @param size size of the vector
 * @return auto vector of bricks
 */
auto fillVector(int size) {
    std::vector<obj::Brick> bricks = {};
    int vec_size = 0;
    while (vec_size <= size) {
        for (int x = MIN_X + 2; x <= MAX_X; x += 2) {
            for (int y = MIN_Y + 2; y <= MAX_Y / 2; y += 2) {
                obj::Brick *b = new obj::Brick("\xDB", x, y);
                b->setPadding("   ");
                b->setVisible(1);
                bricks.push_back(*b);
                vec_size++;
            }
        }
    }

    return bricks;
}

// Vector that holds the bricks
std::vector<obj::Brick> bricks = fillVector(NO_BRICKS);

// Constructing the paddle, ball and player

player::Player *agent = new player::Player(3, 0);
obj::Paddle *paddle = new obj::Paddle("==========", obj::paddleStartXpos, obj::paddleStartYpos);
obj::Ball *ball = new obj::Ball("0", obj::ballStartXpos, obj::ballStartYpos);

int bricksLeft = NO_BRICKS;  // Number of bricks left on the map
bool win = false;            // Determines whether the game is won
bool lose = false;           // Determines whether the game is lost

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
            std::cout << "ball dir: " << ball->getDir() << "\n";
            std::cout << "ball pos: " << ball->getxPos() << ", " << ball->getyPos() << "\n";

            gotoxy(MIN_X, MIN_Y);
            std::cout << "top left: " << MIN_X << ", " << MIN_Y << "\n";

            gotoxy(MAX_X, MIN_Y);
            std::cout << "top right: " << MAX_X << ", " << MIN_Y << "\n";

            gotoxy(MAX_X, MAX_Y);
            std::cout << "\n";
            std::cout << "bottom right: " << MAX_X << ", " << MAX_Y << "\n";

            gotoxy(MIN_X, MAX_Y);
            std::cout << " \n";
            std::cout << "bottom left: " << MIN_X << ", " << MAX_Y << "\n";

            gotoxy(obj::paddleStartXpos, obj::paddleStartYpos);
            std::cout << "paddle spawn here\n";

            gotoxy(obj::ballStartXpos, obj::ballStartYpos);
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
    if (ball->getyPos() >= paddle->getyPos() && ball->getxPos() <= paddle->getxPos()) {
        if (ball->getyPos() == ball->getyPos() - 1) {
            if (ball->getDir() == 3)
                ball->switchDir(ball->getDir());
            else if (ball->getDir() == 4)
                ball->switchDir(ball->getDir());
        }
    }
}

/**
 * @brief Handles ball/brick collision
 * @return void
 */
void ballHitBrick() {
    for (auto &brick : bricks) {
        if (brick.getVisible()) {
            if (ball->getxPos() == brick.getxPos() && ball->getyPos() == brick.getyPos()) {
                if (brick.getIntegrity() < 1) {
                    brick.setVisible(0);
                    bricksLeft--;
                } else {
                    brick.updateIntegrity(1);
                    agent->score += 1;
                    ball->switchDir(ball->getDir());
                }
            }
        }
    }
}
}  // namespace brbk
#endif