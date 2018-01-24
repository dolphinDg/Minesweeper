//
//  Application.hpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 04/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <vector>
#include <initializer_list>
#include <set>
#include <curses.h>
#include "signal_slot.hpp"

class Application {
public:
    Application(std::initializer_list<int>, Application* parent = nullptr);
    virtual ~Application();

    int exec();
    void set_output(int);
    virtual void display();
//signal managing
    void add(const std::initializer_list<class signal>&);
    void remove_all();
    
private:
    Application *parent;
    std::vector<class signal> signals;
//set of exit codes
    const std::set<int> q;
//return of exec function
    int result;
    
protected:
//general gui commands and keys
    static void move_in(int dy, int dx);
    static void print_line_CRLF(const char*);
    static void print_stay(const chtype);
    static void print_line_at_yx(const char*, int, int);
    
    static const int ESC_KEY = 27;
    static const int ENTER_KEY = 10;
    static const int BACKSPACE_KEY = 127;
//slots
    
//signals
    
};

#endif /* Application_hpp */
