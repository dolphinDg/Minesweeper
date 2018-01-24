//
//  menu.cpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 04/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#include <algorithm>
#include <memory>
#include "Menu.hpp"

void init();

Menu::Menu(Application *parent) :
    Application({'Q', 'q', ESC_KEY}, parent),
    dim(0),
    scores(),
    start({'S', 's'}),
    configuration({'P', 'p'}),
    rate({'R', 'r'}),
    SPQR({'O', 'o', 'E', 'e'})
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
//    nodelay(stdscr, TRUE);
    
    start.connect(this, &Menu::init_game);
    configuration.connect(this, &Menu::config);
    rate.connect(this, &Menu::show_rate);
    SPQR.connect(this, &Menu::long_live_senate);
    
    add({start, configuration, rate, SPQR});
}


Menu::~Menu() {
    endwin();
}

void Menu::display() {
    print_line_CRLF("Welcome to Minesweeper!");
    print_line_CRLF("");
    print_line_CRLF("'S' to Start");
    print_line_CRLF("'P' to change Parameters");
    print_line_CRLF("'Q' or Esc to Quit");
    print_line_CRLF("'R' to see Rating table");
}

void Menu::init_game(int) {
    bool restart = false;
    do {
        auto game = std::make_shared<Game>(dim, this);
        restart = game->exec();
        scores.push_back(game->score);
    } while (restart == true);
}

void Menu::config(int) {
    auto opt = std::make_shared<Options>(this);
    opt->exec();
    dim = opt->dim;
}

void Menu::show_rate(int) {
    auto rating = std::make_shared<Rating>(scores, this);
    rating->exec();
}

void Menu::long_live_senate(int) {
    print_line_at_yx("Senatus Populusque Romanus!", 6, 0);
}
