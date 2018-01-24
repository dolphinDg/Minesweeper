//
//  Board.hpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 04/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//
#ifndef Board_hpp
#define Board_hpp

#include <vector>

struct square {
    int n = 0;
    bool revealed = false;
};

class Board {
public:
    Board(int dimension = 10, double ch = 0.2);
    ~Board();
    
    std::vector<std::vector<square>> playgr;
    const int dim;
    const double chance;
    int no_of_mines;
    int no_of_closed;
    
    void generate();
    int no_of_neighbours(int x, int y);
};

#endif /* Board_hpp */
