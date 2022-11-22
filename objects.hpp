// File: objects.hpp
#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <iostream>

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

class Paddle : public GameObject {
   public:
    using GameObject::GameObject;
};

class Ball : public GameObject {
   public:
    using GameObject::GameObject;
};

#endif