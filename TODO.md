# Code

## Objectives

- Make initial ball direction random\*
  - It only goes left or right, can't go between the extremes
  - Implement angular directions (i.e. not left or right - see project pdf for info)
- Fix the replay bug
- Make ball bounce back when it hits brick
- When ball hits brick, make integrity go down by one
  - When integrity < 1, brick disappears
- Implement AI player
- Implement lives (no instant fail when ball drops)
- Refactor using OOP (for some reason)
  - So far created GameObject class and subclasses
  - Began implementing them in the brickbreaker.hpp file

## Fixes

- Make ball and paddle respawn in appropriate position (i.e. at initial position) after life lost
- Make bricks spawn correctly (i.e. close to the center of the screen, not out of bounds)
- Refactor the movement code section to use paddle.setxPos() and paddle.setyPos()
- Refactor drawBall() and drawPaddle() to use paddle and ball class methods rather than array operation

# Report

- Start writing report
