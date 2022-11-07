#include "brickbreaker.hpp"
void play() {
    while (1) {
        system("cls");
        drawBricks();
        drawBorder();

        gotoxy(sliderPos[1], sliderPos[0]);
        std::cout << "=========";

        gotoxy(ballPos[1], ballPos[0]);
        std::cout << "0";

        // Checks for keyboard inputs
        if (kbhit()) {
            char ch = getch();
            if (ch == 'd' || ch == 'D' || ch == 77) {
                if (sliderPos[1] < 44)
                    sliderPos[1] = sliderPos[1] + 2;
            }
            if (ch == 'a' || ch == 'A' || ch == 75) {
                if (sliderPos[1] > 2)
                    sliderPos[1] = sliderPos[1] - 2;
            }
            if (ch == 32) {
                startBall = 1;
            }
            if (ch == 27) {
                break;
            }
        }

        if (startBall == 1) {
            if (dir == 1) {  // TOP RIGHT
                ballPos[0] = ballPos[0] - 1;
                ballPos[1] = ballPos[1] + 2;
                if (ballPos[1] > MAX_X) {
                    dir = 2;
                } else if (ballPos[0] < MIN_Y) {
                    dir = 4;
                }
            } else if (dir == 2) {  // TOP LEFT
                ballPos[0] = ballPos[0] - 1;
                ballPos[1] = ballPos[1] - 2;
                if (ballPos[0] < MIN_Y) {
                    dir = 3;
                } else if (ballPos[1] < MIN_X) {
                    dir = 1;
                }
            } else if (dir == 3) {  // BOTTOM LEFT
                ballPos[0] = ballPos[0] + 1;
                ballPos[1] = ballPos[1] - 2;

                if (ballPos[0] > MAX_Y) {
                    lose = 1;
                    break;
                } else if (ballPos[1] < MIN_X) {
                    dir = 4;
                }
            } else if (dir == 4) {  // BOTTOM RIGHT
                ballPos[0] = ballPos[0] + 1;
                ballPos[1] = ballPos[1] + 2;
                if (ballPos[1] > MAX_X) {
                    dir = 3;
                } else if (ballPos[0] > MAX_Y) {
                    lose = 1;
                    break;
                }
            }

            ballHitSlider();
        }

        ballHitBrick();

        if (bricksLeft == 0) {
            win = 1;
            break;
        }

        Sleep(30);
    }

    if (lose == 1) {
        system("cls");

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

    if (win == 1) {
        system("cls");
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

// Prints out the instructions
void instructions() {
    system("cls");
    std::cout << "Instructions";
    std::cout << "\n----------------";
    std::cout << "\nPress the spacebar to start playing";
    std::cout << "\n\nPress any key to go back to the main menu";
    getch();
}

int main() {
    setcursor(0, 0);
    system("cls");
    gotoxy(10, 5);
    gotoxy(10, 6);
    std::cout << "EPILEPSY WARNING:\nTHIS GAME MAY CONTAIN FLASHING LIGHTS\n\tPLAY AT YOUR OWN RISK";
    std::cout << "\nYOU CAN PRESS CTRL+C TO CLOSE THE GAME AT ANY POINT";
    gotoxy(10, 7);

    Sleep(3500);

    do {
        system("cls");
        gotoxy(10, 5);
        std::cout << " -------------------------- ";
        gotoxy(10, 6);
        std::cout << " |     BRICK BREAKER      | ";
        gotoxy(10, 7);
        std::cout << " --------------------------";
        gotoxy(10, 9);
        std::cout << "1. Start Game";
        gotoxy(10, 10);
        std::cout << "2. Instructions";
        gotoxy(10, 11);
        std::cout << "3. Quit";
        gotoxy(10, 13);
        std::cout << "Select option: ";
        char op = getche();

        switch (op) {
            case '1':
                play();
            case '2':
                instructions();
            case '3':
                std::cout << "\nThanks for playing!";
                Sleep(500);
                exit(0);
        }

    } while (1);

    play();

    std::cout << std::endl
              << std::endl;
    return 0;
}
