#include "brickbreaker.hpp"

// Game loop function
void play() {
    bool started = ball->startBall();  // Starting the ball
    while (true) {
        gotoxy(0, 0);
        std::cout << agent->lives << " lives left\n";
        std::cout << "Score: " << agent->score;

        dbg();  // Display debug info (default = false)

        system("clear");
        drawBricks();

        paddle->drawPaddle();
        ball->drawBall();

        // I hope you like if-else chains
        if (started) {
            agent->control(ball->getDir(), paddle);
            if (ball->getDir() == 1) {  // Top right
                ball->updateyPos(-1);
                ball->updatexPos(2);
                if (ball->getxPos() > MAX_X) {
                    ball->setDir(2);
                } else if (ball->getyPos() < MIN_Y) {
                    ball->switchDir(ball->getDir());
                }
            } else if (ball->getDir() == 2) {  // Top left
                ball->updateyPos(-1);
                ball->updatexPos(-2);
                if (ball->getyPos() < MIN_Y) {
                    ball->switchDir(ball->getDir());
                } else if (ball->getxPos() < MIN_X) {
                    ball->switchDir(ball->getDir());
                }
            } else if (ball->getDir() == 3) {  // Bottom left
                ball->updateyPos(1);
                ball->updatexPos(-2);
                if (ball->getyPos() > MAX_Y) {
                    agent->lives -= 1;
                    paddle->resetPaddle();
                    ball->resetBall();
                } else if (ball->getxPos() < MIN_X) {
                    ball->switchDir(ball->getDir());
                }
            } else if (ball->getDir() == 4) {  // Bottom right
                ball->updateyPos(1);
                ball->updatexPos(2);
                if (ball->getxPos() > MAX_X) {
                    ball->switchDir(ball->getDir());
                } else if (ball->getyPos() > MAX_Y) {
                    agent->lives -= 1;
                    ball->resetBall();
                    paddle->resetPaddle();
                }
            }
            ballHitSlider();
            ballHitBrick();
        }

        if (agent->lives < 0) {
            lose = true;
            break;
        }

        if (bricksLeft == 0) {
            win = true;
            break;
        }

        Sleep(10);
    }

    if (lose == true) {
        system("clear");

        gotoxy(10, 5);
        std::cout << " --------------------- ";
        gotoxy(10, 6);
        std::cout << " |     GAME OVER      | ";
        gotoxy(10, 7);
        std::cout << " --------------------- ";

        gotoxy(10, 9);
        std::cout << "Press any key to exit the game.\n";
        std::cout << "\tFinal score: " << agent->score;
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
        std::cout << "Press any key to exit the game.\n";
        gotoxy(11, 10);
        std::cout << "\tFinal score: " << agent->score;
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
        std::cout << "\n\tPRESS THE SPACE BAR TO CONTINUE";
        gotoxy(10, 7);
        char ch = getch();
        if (ch == 32) {
            break;
        }
    }

    play();

    std::cout << std::endl
              << std::endl;

    system("clear");
    exit(0);
}
