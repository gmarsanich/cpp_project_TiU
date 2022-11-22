#include "brickbreaker.hpp"

#include "agent.hpp"

// Game loop function
void play() {
    dir = getRandomInt(1, 2);  // Takes random direction
    Player agent = agent;      // Initializing player

    while (1) {
        dbg(true);
        system("clear");
        drawBricks();

        drawPaddle();
        drawBall();

        if (agent.startGame()) {
            agent.control(dir);

            if (dir == 1) {  // TOP RIGHT
                ball->updatexPos(-1);
                ball->updateyPos(2);
                if (ball->getxPos() > MAX_X) {
                    dir = 2;
                } else if (ball->getyPos() < MIN_Y) {
                    dir = 4;
                }
            } else if (dir == 2) {  // TOP LEFT
                ball->updatexPos(-1);
                ball->updateyPos(-2);
                if (ball->getyPos() < MIN_Y) {
                    dir = 3;
                } else if (ball->getxPos() < MIN_X) {
                    dir = 1;
                }
            } else if (dir == 3) {  // BOTTOM LEFT
                ball->updatexPos(1);
                ball->updateyPos(2);

                if (ball->getyPos() > MAX_Y) {
                    lives -= 1;
                    resetPaddle();
                    resetBall();
                } else if (ball->getxPos() < MIN_X) {
                    dir = 4;
                }
            } else if (dir == 4) {  // BOTTOM RIGHT
                ball->updatexPos(1);
                ball->updateyPos(2);
                if (ball->getxPos() > MAX_X) {
                    dir = 3;
                } else if (ball->getyPos() < paddle->getyPos()) {
                    lives -= 1;
                    resetBall();
                    resetPaddle();
                }
            }
            ballHitSlider();
        }

        ballHitBrick();

        if (lives < 0) {
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
        std::cout << "\tFinal score: " << score;
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
        std::cout << "\tFinal score: " << score;
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

    system("clear");
    exit(0);
}
