//
//  Board.cpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 04/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#include "Board.hpp"
#include <cstdlib>
#include <iostream>
#include <ctime>

Board::Board(int n, double ch) : playgr(n, std::vector<square>(n)), dim(n), chance(ch), no_of_mines(0), no_of_closed(n * n) {
    
}

Board::~Board() {}

void Board::generate() {
    srand(static_cast<unsigned int>(time(NULL)));
    
    no_of_mines = 0;
    
    for (auto &line : playgr)
        for (auto &sq : line)
            if (double(rand())/RAND_MAX < chance) {
                sq.n = 10;
                no_of_mines += 1;
            }
    
    for (int i = 0; i < dim; ++i)
        for (int j = 0; j < dim; ++j)
            if (playgr[i][j].n != 10)
                playgr[i][j].n = no_of_neighbours(i, j);
}

int Board::no_of_neighbours(int y, int x) {
    int count = 0;
    int dim = this->dim;                                                    //complaint "'dim' in capture list does not name a variable"
    auto notValid = [dim] (int x) -> bool {return !(x >= 0 && x < dim);};
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if(notValid(y + i) || notValid(x + j) ||
                        (i == 0 && j == 0) || playgr[y + i][x + j].n != 10)
                continue;
            else
                ++count;
    return count;
}


