// File: objects.hpp
#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <iostream>

// This file contains the definitions of game objects - i.e. paddle, bricks, ball

// Parent class of all game objects
class GameObject {
   private:
    // Game object attributes - x position, y position, shape
    std::string shape;
    int xPos;
    int yPos;

   public:
    // CONSTRUCTOR
    explicit GameObject(std::string shape, int xPos, int yPos) {
        // All game objects have a shape and an (x, y) coordinate
        this->shape = shape;
        this->xPos = xPos;
        this->yPos = yPos;
    }

    // Getters and setters
    std::string getShape() { return this->shape; }
    int getxPos() { return this->xPos; }
    int getyPos() { return this->yPos; }
};

class Brick : public GameObject {
    // Brick is heavily based on GameObject parent class, except for the padding attribute
    // which determines which character pads the brick shape.
    // It should be the space character ' ', otherwise it will be visible in the game (and we don't want that)
   private:
    // Brick attributes
    std::string padding;
    bool isVisible;
    int integrity = 3;

   public:
    // Brick methods

    // CONSTRUCTOR
    using GameObject::GameObject;

    // Getters and setters
    // I resorted to giving extra attributes their own methods
    void setPadding(std::string padding) { this->padding = padding; }
    std::string getPadding() { return this->padding; }

    void setVisible(bool visible) { this->isVisible = visible; }
    bool getVisible() { return this->isVisible; }

    void setIntegrity(int integrity) { this->integrity = integrity; }
    int getIntegrity() { return this->integrity; }
};

// Ball and paddle classes are inherited entirely from GameObject

class Paddle : public GameObject {
   public:
    using GameObject::GameObject;
};

class Ball : public GameObject {
   public:
    using GameObject::GameObject;
};

#endif