#include <array>
#include <iostream>
//#include "brickbreaker.hpp"
int main() {
    const int NO_BRICKS = 24;
    std::array<std::array<int, 2>, NO_BRICKS> bricks = {{{2, 7},
                                                         {2, 12},
                                                         {2, 17},
                                                         {2, 22},
                                                         {2, 27},
                                                         {2, 32},
                                                         {2, 37},
                                                         {2, 42},
                                                         {4, 7},
                                                         {4, 12},
                                                         {4, 17},
                                                         {4, 22},
                                                         {4, 27},
                                                         {4, 32},
                                                         {4, 37},
                                                         {4, 42},
                                                         {6, 7},
                                                         {6, 12},
                                                         {6, 17},
                                                         {6, 22},
                                                         {6, 27},
                                                         {6, 32},
                                                         {6, 37},
                                                         {6, 42}}};

    std::cout << bricks.at(23).at(0);
    std::cout << bricks.at(23).at(1);
}