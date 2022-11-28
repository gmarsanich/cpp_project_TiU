#include "brickbreaker.hpp"

// Game loop function
void play() {
    bool started = brbk::ball->startBall();  // Starting the ball
    while (started) {
        gotoxy(0, 0);
        std::cout << brbk::agent->lives << " lives left\n";
        std::cout << "Score: " << brbk::agent->score;

        brbk::dbg(true);  // Display debug info (default = false)

        system("clear");
        brbk::drawBricks();

        brbk::paddle->drawPaddle();
        brbk::ball->drawBall();

        brbk::agent->control(brbk::ball->getDir(), brbk::paddle);

        // I hope you like if-else chains
        if (brbk::ball->getDir() == 1) {  // Top right
            brbk::ball->updateyPos(-1);
            brbk::ball->updatexPos(2);
            if (brbk::ball->getxPos() > MAX_X) {
                brbk::ball->setDir(2);
            } else if (brbk::ball->getyPos() <= MIN_Y) {
                brbk::ball->switchDir(brbk::ball->getDir());
            }
        } else if (brbk::ball->getDir() == 2) {  // Top left
            brbk::ball->updateyPos(-1);
            brbk::ball->updatexPos(-2);
            if (brbk::ball->getyPos() < MIN_Y) {
                brbk::ball->switchDir(brbk::ball->getDir());
            } else if (brbk::ball->getxPos() < MIN_X) {
                brbk::ball->switchDir(brbk::ball->getDir());
            }
        } else if (brbk::ball->getDir() == 3) {  // Bottom left
            brbk::ball->updateyPos(1);
            brbk::ball->updatexPos(-2);
            if (brbk::ball->getyPos() >= brbk::paddle->getyPos()) {
                brbk::agent->lives -= 1;
                brbk::paddle->resetPaddle();
                brbk::ball->resetBall();
            } else if (brbk::ball->getxPos() < MIN_X) {
                brbk::ball->switchDir(brbk::ball->getDir());
            }
        } else if (brbk::ball->getDir() == 4) {  // Bottom right
            brbk::ball->updateyPos(1);
            brbk::ball->updatexPos(2);
            if (brbk::ball->getxPos() >= MAX_X) {
                brbk::ball->switchDir(brbk::ball->getDir());
            } else if (brbk::ball->getyPos() > MAX_Y) {
                brbk::agent->lives -= 1;
                brbk::ball->resetBall();
                brbk::paddle->resetPaddle();
            }
        }
        brbk::ballHitSlider();
        brbk::ballHitBrick();

        if (brbk::agent->lives < 0) {
            brbk::lose = true;
            break;
        }

        if (brbk::bricksLeft == 0) {
            brbk::win = true;
            break;
        }
    }

    if (brbk::lose == true) {
        system("clear");

        gotoxy(10, 5);
        std::cout << " --------------------- ";
        gotoxy(10, 6);
        std::cout << " |     GAME OVER      | ";
        gotoxy(10, 7);
        std::cout << " --------------------- ";

        gotoxy(10, 9);
        std::cout << "Press any key to exit the game.\n";
        std::cout << "\tFinal score: " << brbk::agent->score;
        getch();
    }

    if (brbk::win == true) {
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
        std::cout << "\tFinal score: " << brbk::agent->score;
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
