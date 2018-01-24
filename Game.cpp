//
//  Game.cpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 04/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#include "Game.hpp"
#include <curses.h>
#include <string>

Game::Game(int n, Application *parent) :
    Application({'M','m','R','r', ESC_KEY}, parent),
    score(0),
    board(n == 0 ? 5 : n),
    score_x(0),
    score_y(0),
    key_enter({'O', 'o', ENTER_KEY}),
    F_clicked({'F', 'f'}),
    R_clicked({'R', 'r'}),
    arrow_clicked({KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_LEFT})
{
    init_colors();
    
    key_enter.connect(this, &Game::reveal);
    F_clicked.connect(this, &Game::set_unset_flag);
    R_clicked.connect(this, &Game::restart);
    arrow_clicked.connect(this, &Game::move_arrow);
    
    add({key_enter, F_clicked, R_clicked, arrow_clicked});
}

Game::~Game() {

}

void Game::display() {
    int y = 0, x = 0;
    for (int i = 0; i < board.dim; ++i) {
        for (int j = 0; j < board.dim; ++j) {
            addch(space);
            addch(' ');
        }
        getyx(stdscr, y, x);
        move(y + 1, 0);
    }
    move(y + 2, 0);
    addstr("Your Score: ");
    getyx(stdscr, y, x);
    score_x = x;
    score_y = y;
    show_score();
    
    print_line_CRLF("");
    print_line_CRLF("Use arrows to move");
    print_line_CRLF("'O' or Enter to open");
    print_line_CRLF("'F' to set or remove a flag");
    print_line_CRLF("'R' to restart");
    print_line_CRLF("Press 'M' or Esc to return to menu");
    move(0, 0);
    refresh();
}

//colors for each number/mine
void Game::init_colors() {
    init_pair(10, COLOR_BLACK, COLOR_RED);
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_RED, COLOR_BLACK);
    init_pair(8, COLOR_RED, COLOR_BLACK);
    init_pair(9, COLOR_RED, COLOR_BLACK);
}

const std::vector<char> Game::chars{'0','1','2','3','4','5','6','7','8','9','M'};
const char Game::space = '_';
const char Game::flag = 'F';

void Game::reveal(int) {
    int cy, cx;
    getyx(stdscr, cy, cx);
    
    //to prevent possibility to lose at first step
    if (score == 0) {
        int count = 0;
        do {
            board.generate();
            ++count;
        } while (board.playgr[cytoy(cy)][cxtox(cx)].n == 10 || count < 20);
        if (board.playgr[cytoy(cy)][cxtox(cx)].n == 10) {
            board.playgr[cytoy(cy)][cxtox(cx)].n = board.no_of_neighbours(cytoy(cy), cxtox(cx));
        }
    }
    
    int dim = board.dim;
    if (cytoy(cy) >= dim || cx % 2 != 0 || cxtox(cx) >= dim)
        return;
    
    reveal_help(cytoy(cy), cxtox(cx), true);
    
    if (board.no_of_closed == board.no_of_mines) {
        print_line_at_yx("You won!", score_y - 1, 0);
        finished();
    }
}

void Game::set_unset_flag(int) {
    int ch;
    ch = inch();
    
    if (ch == space)
        print_stay(flag);
    if (ch == flag)
        print_stay(space);
}

void Game::restart(int) {
    set_output(true);
}

void Game::move_arrow(int key) {
    int ry, rx, cy, cx;
    getyx(stdscr, ry, rx);
    
    switch (key) {
        case KEY_UP:
            move_in(-1, 0);
            break;
        case KEY_RIGHT:
            move_in(0, 2);
            break;
        case KEY_DOWN:
            move_in(1, 0);
            break;
        case KEY_LEFT:
            move_in(0, -2);
            break;
        default:
            break;
    }
    
    getyx(stdscr, cy, cx);
    
    if (cxtox(cx) >= board.dim || cytoy(cy) >= board.dim || cxtox(cx) < 0 || cytoy(cy) < 0) {
        move(ry, rx);
    }
}

void Game::reveal_help(int y, int x, bool is_first) {
    
    if (y >= board.dim || x >= board.dim || y < 0 || x < 0 || board.playgr[y][x].revealed)
        return;
    
    board.playgr[y][x].revealed = true;
    
    switch (board.playgr[y][x].n) {
        case 10:
            if (is_first) {
                print_yx(10, y, x);
                print_line_at_yx("You exploded!", score_y - 1, 0);
                finished();
            }
            break;
        case 0:
            print_yx(0, y, x);
            
            scoring();
            show_score();
            board.no_of_closed -= 1;
            
            for (int i = -1; i <= 1; ++i)
                for (int j = -1; j <= 1; ++j)
                    reveal_help(y + i, x + j, false);
            break;
        default:
            print_yx(board.playgr[y][x].n, y, x);
            
            scoring();
            show_score();
            board.no_of_closed -= 1;
            break;
    }
}

void Game::scoring() {
    score += 1;
}

void Game::show_score() {
    int y, x;
    getyx(stdscr, y, x);
    
    move(score_y, score_x);
    addstr(std::to_string(score).c_str());
    
    move(y, x);
}

void Game::finished() {
    remove_all();
    add({R_clicked});
    
    int dim = board.dim;
    for (int y = 0; y < dim; ++y)
        for (int x = 0; x < dim; ++x)
            if (board.playgr[y][x].n == 10)
                print_yx(board.playgr[y][x].n, y, x);
    
    print_line_at_yx(("Game Finished! Your Score is " + std::to_string(score)).c_str(), score_y, 0);
}

void Game::print_yx(int sq, int y, int x) {
    int cy = ytocy(y), cx = xtocx(x), ry, rx;
    getyx(stdscr, ry, rx);
    
    mvwaddch(stdscr, cy, cx, chars[sq] | COLOR_PAIR(sq));
    
    move(ry, rx);
    refresh();
}

int Game::cxtox(int cx){
    return cx / 2;
}

int Game::xtocx(int x) {
    return x * 2;
}

int Game::cytoy(int cy) {
    return cy;
}

int Game::ytocy(int y) {
    return y;
}
