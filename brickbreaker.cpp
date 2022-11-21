#include "brickbreaker.hpp"

// Game loop function
void play() {
    dir = getRandomInt(1, 2);  // Takes random direction

    while (1) {
        system("clear");
        drawBricks();

        gotoxy(0, 0);

        std::cout << lives << " Lives left\n";
        std::cout << "starting ball direction: " << dir << "\n";
        std::cout << "Score: " << score;

        drawPaddle();
        drawBall();

        // Checks for keyboard inputs - will be deprecated when the AI agent is implemented
        if (kbhit()) {
            char ch = getch();
            if (ch == 'd' || ch == 'D' || ch == 77) {
                if (paddle->getxPos() < 44)
                    paddle->updatexPos(2);
            }
            if (ch == 'a' || ch == 'A' || ch == 75) {
                if (paddle->getxPos() > 2)
                    paddle->updatexPos(-2);
            }
            if (ch == 32) {
                startBall = true;
            }
            if (ch == 27) {
                break;
            }
        }

        if (startBall == true) {
            if (ball->getyPos() < paddle->getyPos()) {
                lives -= 1;
            }

            if (dir == 1) {  // TOP RIGHT
                ball->updateyPos(2);
                ball->updatexPos(1);
                if (ball->getxPos() > MAX_X) {
                    dir = 2;
                } else if (ball->getyPos() < MIN_Y) {
                    dir = 4;
                }
            } else if (dir == 2) {  // TOP LEFT
                ball->updateyPos(-2);
                ball->updatexPos(-1);
                if (ball->getyPos() < MIN_Y) {
                    dir = 3;
                } else if (ball->getxPos() < MIN_X) {
                    dir = 1;
                }
            } else if (dir == 3) {  // BOTTOM LEFT
                ball->updateyPos(2);
                ball->updatexPos(1);

                if (ball->getyPos() > MAX_Y) {
                    lives -= 1;
                    drawPaddle();
                    drawBall();
                } else if (ball->getxPos() < MIN_X) {
                    dir = 4;
                }
            } else if (dir == 4) {  // BOTTOM RIGHT
                ball->updateyPos(2);
                ball->updatexPos(1);
                if (ball->getxPos() > MAX_X) {
                    dir = 3;
                } else if (ball->getyPos() < MAX_Y) {
                    drawPaddle();
                    drawBall();
                    lives -= 1;
                    resetBall();
                    resetPaddle();
                }
            }
        }

        ballHitSlider();
        ballHitBrick();

        if (lives < 0) {
            lose = true;
            break;
        }

        if (bricksLeft == 0) {
            win = true;
            break;
        }

        Sleep(30);
    }

    if (lose == true) {
        system("clear");

        gotoxy(10, 5);
        std::cout << " --------------------- ";
        gotoxy(10, 6);
        std::cout << " |     YOU LOSE      | ";
        gotoxy(10, 7);
        std::cout << " --------------------- ";

        gotoxy(10, 9);
        std::cout << "Press any key to go back to the main menu.";
        getch();
    }

    if (win == true) {
        system("clear");
        gotoxy(10, 5);
        std::cout << " --------------------- ";
        gotoxy(10, 6);
        std::cout << " |     YOU WIN       | ";
        gotoxy(10, 7);
        std::cout << " --------------------- ";

        gotoxy(10, 9);
        std::cout << "Press any key to go back to the main menu.";
        getch();
    }
}

int main() {
    setcursor(0, 0);
    system("clear");
    gotoxy(10, 5);
    gotoxy(10, 6);

    while (true) {
        std::cout << "EPILEPSY WARNING:\nTHIS GAME MAY CONTAIN FLASHING LIGHTS\n\tPLAY AT YOUR OWN RISK";
        std::cout << "\nYOU CAN PRESS CTRL+C TO CLOSE THE GAME AT ANY POINT";
        std::cout << "\n\tPRESS ANY KEY TO CONTINUE";
        gotoxy(10, 7);
        char ch = getch();
        if (ch) {
            break;
        }
    }

    play();

    std::cout << std::endl
              << std::endl;
}
