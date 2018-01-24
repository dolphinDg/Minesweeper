//
//  menu.hpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 04/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#ifndef menu_hpp
#define menu_hpp

#include "Application.hpp"
#include "Options.hpp"
#include "Game.hpp"
#include "Rating.hpp"

class Menu : public Application {
public:
    Menu(Application *parent = nullptr);
    ~Menu();

private:
    void display();
    
    int dim;
    std::vector<int> scores;
    
//signals
    class signal start;
    class signal configuration;
    class signal rate;
    class signal SPQR;
//slots
    void init_game(int);
    void config(int);
    void show_rate(int);
    void long_live_senate(int);
};

#endif /* menu_hpp */
