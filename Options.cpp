//
//  Options.cpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 07/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#include "Options.hpp"

Options::Options(Application *parent) :
    Application({'M', 'm', ENTER_KEY}, parent),
    dim(0),
    number_clicked({'0','1','2','3','4','5','6','7','8','9'}),
    backspace_clicked({BACKSPACE_KEY, 'D', 'd'})
{
    number_clicked.connect(this, &Options::write_number);
    backspace_clicked.connect(this, &Options::delete_number);
    add({number_clicked, backspace_clicked});
}

Options::~Options() {}

void Options::display() {
    print_line_CRLF("Options:");
    addstr("Dimensions of a board: 5");
    
    int y, x;
    getyx(stdscr, y, x);
    
    print_line_CRLF("");
    print_line_CRLF("'D' or Backspace to delete");
    print_line_CRLF("'M' or Enter to save your choice and return to Menu");
    
    move(y, x - 1);
}

void Options::write_number(int number) {
    if (!(dim == 0 && number == 0)) {
        addch(number);
        dim = dim * 10 + number - '0';
        refresh();
    }
}

void Options::delete_number(int) {
    int y, x;
    getyx(stdscr, y, x);
    
    if (x != 0 && dim != 0) {
        move_in(0, -1);
        print_stay(' ');
        dim /= 10;
    }
    
    if (dim == 0) {
        print_stay('0');
    }
    refresh();
}
