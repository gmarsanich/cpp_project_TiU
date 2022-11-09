// File: objects.hpp
#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <iostream>

// This file contains the definitions of game objects - i.e. the paddle and bricks

class Brick {
   private:
    // Brick attributes
    int xPos;
    int yPos;
    std::string padding;
    std::string shape;

   public:
    // Brick methods

    // CONSTRUCTOR
    Brick(std::string shape, std::string padding, int xPos, int yPos) {
        this->shape = shape;
        this->padding = padding;
        this->xPos = xPos;
        this->yPos = yPos;
    }

    // Getters and setters
    std::string getShape() { return this->shape; }
    std::string getPadding() { return this->padding; }
    int getxPos() { return this->xPos; }
    int getyPos() { return this->yPos; }
};

class Paddle {
   private:
    // Paddle attributes
    int xPos;
    int yPos;
    std::string shape;

   public:
    // Paddle methods

    // CONSTRUCTOR
    Paddle(std::string shape, int xPos, int yPos) {
        this->shape = shape;
        this->xPos = xPos;
        this->yPos = yPos;
    }

    // Getters and setters
    std::string getShape() { return this->shape; }
    int getxPos() { return this->xPos; }
    int getyPos() { return this->yPos; }
};

#endif