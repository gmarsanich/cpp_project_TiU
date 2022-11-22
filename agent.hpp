// File: agent.hpp
#ifndef AGENT_HPP
#define AGENT_HPP

#include <array>

#include "brickbreaker.hpp"
#include "objects.hpp"

/**
 * @brief Player class
 */
class Player {
   public:
    Player() {}

    /**
     * @brief Starts the game
     * @return true
     */
    bool startGame() {
        startBall = true;
        return startBall;
    }

    // Moving the paddle
    void moveRight(Paddle *paddle) {
        if (paddle->getxPos() < 44)
            paddle->updatexPos(2);
    }

    void moveLeft(Paddle *paddle) {
        if (paddle->getxPos() > 2)
            paddle->updatexPos(-2);
    }

    /**
     * @brief Controls the movement of the paddle based on the ball position
     * @param balldir ball direction
     */
    void control(int balldir) {
        if (balldir == 1) {
            this->moveLeft(paddle);
        } else if (balldir == 2) {
            this->moveRight(paddle);
        } else if (balldir == 3) {
            this->moveLeft(paddle);
        } else if (balldir == 4) {
            this->moveRight(paddle);
        }
    }
};

#endif