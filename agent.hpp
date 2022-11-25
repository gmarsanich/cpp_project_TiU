// File: agent.hpp
#ifndef AGENT_HPP
#define AGENT_HPP

// Local headers
#include "console.hpp"
#include "objects.hpp"

/**
 * @brief Player class
 */
class Player {
   public:
    int lives;
    int score = 0;

    /**
     * @brief Construct a new Player object
     *
     * @param lives: int, number of lives
     * @param score: int, player score
     */
    Player(int lives, int score) {
        this->lives = lives;
        this->score = score;
    }

    /**
     * @brief Starts the game
     * @return true
     */
    void startGame(Ball *ball) {
        ball->startBall();
    }

    // Moving the paddle
    void moveRight(Paddle *paddle) {
        if (paddle->getxPos() < MAX_X) {
            paddle->updatexPos(2);
        } else {
            while (paddle->getxPos() != paddleStartXpos) {
                stopMove(paddle);
                this->moveLeft(paddle);
            }
        }
    }

    void moveLeft(Paddle *paddle) {
        if (paddle->getxPos() > MIN_X) {
            paddle->updatexPos(-2);
        } else {
            while (paddle->getxPos() != paddleStartXpos) {
                stopMove(paddle);
                this->moveRight(paddle);
            }
        }
    }

    void stopMove(Paddle *paddle) {
        paddle->updatexPos(0);
    }

    /**
     * @brief Controls the movement of the paddle based on the ball direction
     * @param balldir ball direction
     */
    void control(int balldir, Paddle *paddle) {
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