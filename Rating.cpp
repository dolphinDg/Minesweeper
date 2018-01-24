//
//  Rating.cpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 07/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#include "Rating.hpp"
#include <algorithm>
#include <string>

Rating::Rating(std::vector<int> lst, Application *parent) :
    Application({'M', 'm', ESC_KEY}, parent),
    scores(lst)
{
    std::sort(scores.begin(), scores.end(), [] (int x, int y) -> bool {return x > y;});
}

Rating::~Rating() {}

void Rating::display() {
    print_line_CRLF("Rating Table:");
    
    for (int i = 0; i < scores.size() && i < 10; ++i) {
        addstr(std::to_string(i + 1).c_str());
        addstr(": ");
        print_line_CRLF(std::to_string(scores[i]).c_str());
    }
    
    print_line_CRLF("'M' or Esc to return to Menu");
}
