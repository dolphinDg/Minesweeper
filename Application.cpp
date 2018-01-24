//
//  Application.cpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 04/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#include "Application.hpp"
#include <curses.h>
#include <algorithm>
#include <iterator>

Application::Application(std::initializer_list<int> lst, Application *parent) :
    parent(parent),
    signals(),
    q(lst),
    result(0)
{
    
}

Application::~Application() {
    
}

int Application::exec() {
    
    clear();
    display();
    refresh();
    
    int id;
    
    //searching for singals containing requested id amd emitting it
    do {
        id = getch();
        std::vector<class signal> sis;
        
        std::copy_if(signals.cbegin(), signals.cend(), std::back_inserter(sis), [id] (class signal si) -> bool { return si.contains(id); });
        std::for_each(sis.cbegin(), sis.cend(), [id] (class signal si) -> void { emit(si, id); });
        
    } while(q.find(id) == q.cend());
    
    clear();
    if (parent)
        parent->display();
    refresh();
    
    return result;
}

void Application::set_output(int res) {
    result = res;
}

void Application::display() {
    
}

void Application::add(const std::initializer_list<class signal> &lst) {
    for (auto &si : lst) {
        signals.push_back(si);
    }
}

void Application::remove_all() {
    signals = {};
}
void Application::move_in(int dy, int dx) {
    int y, x;
    getyx(stdscr, y, x);
    move(y + dy, x + dx);
}

void Application::print_line_CRLF(const char *a) {
    int y, x;
    getyx(stdscr, y, x);
    addstr(a);
    move(y + 1, 0);
    refresh();
}

void Application::print_stay(const chtype ch) {
    int y, x;
    getyx(stdscr, y, x);
    addch(ch);
    move(y, x);
    refresh();
}

void Application::print_line_at_yx(const char *ch, int cy, int cx) {
    int ry, rx;
    getyx(stdscr, ry, rx);
    
    move(cy, cx);
    addstr(ch);
    
    move(ry, rx);
}
