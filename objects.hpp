// File: objects.hpp
#ifndef OBJECTS_HPP
#define OBJECTS_HPP

// External headers
#include <time.h>

// Builtin headers
#include <iostream>
#include <random>

// Local headers
#include "console.hpp"

// This file contains the definitions of game objects - i.e. paddle, bricks, ball

/**
 * @brief Parent class of all game objects
 */
class GameObject {
   private:
    // Game object attributes - x position, y position, shape
    std::string shape;
    int xPos;
    int yPos;

   public:
    // CONSTRUCTOR
    /**
     * @brief Constructs a new Game Object object
     *
     * @param shape the shape of the object
     * @param xPos the x position of the object
     * @param yPos the y position of the object
     */
    explicit GameObject(std::string shape, int xPos, int yPos) {
        // All game objects have a shape and an (x, y) coordinate
        this->shape = shape;
        this->xPos = xPos;
        this->yPos = yPos;
    }

    // Getters and setters
    std::string getShape() { return this->shape; }
    void setShape(std::string shape) { this->shape = shape; }

    int getxPos() { return this->xPos; }
    void setxPos(int xPos) { this->xPos = xPos; }
    void updatexPos(int add_xPos) { this->xPos += add_xPos; }

    int getyPos() { return this->yPos; }
    void setyPos(int yPos) { this->yPos = yPos; }
    void updateyPos(int add_yPos) { this->yPos += add_yPos; }
};

////////////////////////////////////////////////////////////

class Brick : public GameObject {
    /*!
    Brick is heavily based on GameObject parent class, except for the padding attribute which determines which character pads the brick shape.
    It should be the space character ' ', otherwise it will be visible in the game (and we don't want that)
    */

   private:
    // Brick attributes
    std::string padding;  // the padding character
    bool isVisible;       // whether the brick is visible or not
    int integrity = 3;    // how many hits the brick can take before it breaks

   public:
    // Brick methods

    // CONSTRUCTOR INHERITED FROM GameObject
    using GameObject::GameObject;

    // Getters and setters
    void setPadding(std::string padding) { this->padding = padding; }
    std::string getPadding() { return this->padding; }

    void setVisible(bool visible) { this->isVisible = visible; }
    bool getVisible() { return this->isVisible; }

    void setIntegrity(int integrity) { this->integrity = integrity; }
    int getIntegrity() { return this->integrity; }

    void updateIntegrity(int dmg) { this->integrity -= dmg; }
};

////////////////////////////////////////////////////////////
const int paddleStartYpos = MAX_Y;
const int paddleStartXpos = MAX_X / 2;

class Paddle : public GameObject {
   public:
    using GameObject::GameObject;
    /**
     * @brief Resets the paddle to its initial positions
     * @return void
     */
    void resetPaddle() {
        this->setxPos(paddleStartXpos);
        this->setyPos(paddleStartXpos);
    }
    /**
     * @brief Draws the paddle at a specified (x, y) position
     * @return void
     */
    void drawPaddle() {
        gotoxy(this->getxPos(), this->getyPos());
        std::cout << this->getShape();
    }
};

////////////////////////////////////////////////////////////

const int ballStartXpos = paddleStartXpos + 4;
const int ballStartYpos = paddleStartYpos;

class Ball : public GameObject {
   private:
    bool start = false;
    int dir = 0;
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

   public:
    using GameObject::GameObject;

    bool startBall() {
        this->start = true;
        this->setDir(getRandomInt(1, 2));  // Can either go top left or top right
        return true;
    }
    void setDir(int dir) { this->dir = dir; }
    int getDir() { return this->dir; }

    /**
     * @brief Draws the ball at a specified (x, y) position
     * @return void
     */
    void drawBall() {
        gotoxy(this->getxPos(), this->getyPos());
        std::cout << this->getShape();
    }

    /**
     * @brief Resets the ball to its initial positions
     * @return void
     */
    void resetBall() {
        this->setyPos(ballStartXpos);
        this->setyPos(ballStartYpos);
    }

    /**
     * @brief Ugly way of inverting ball direction after hit
     * @param int dir - ball direction
     */
    void switchDir(int dir) {
        switch (dir) {
            case 1:
                this->setDir(4);
            case 2:
                this->setDir(3);
            case 3:
                this->setDir(2);
            case 4:
                this->setDir(1);
        }
    }
};

#endif