//
//  Game.hpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 04/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Application.hpp"
#include "Board.hpp"

class Game : public Application {
public:
    Game(int n, Application *parent = nullptr);
    ~Game();
    
    int score;
private:
    void display();
    void init_colors();
    
    Board board;
    
//score coordinates
    int score_x;
    int score_y;
    
//gui chars
    static const std::vector<char> chars;
    static const char space;
    static const char flag;
    
//slots
    void reveal(int);
    void set_unset_flag(int);
    void restart(int);
    void move_arrow(int);

//signals
    class signal key_enter;
    class signal F_clicked;
    class signal R_clicked;
    class signal arrow_clicked;
    
//game managing functions
    void reveal_help(int, int, bool);
    void scoring();
    void show_score();
    void finished();
    
//helper functions
    static void print_yx(int, int, int);
//convert window coordinates to board coordinates and vice versa
    static inline int cxtox(int);
    static inline int xtocx(int);
    static inline int cytoy(int);
    static inline int ytocy(int);
};

#endif /* Game_hpp */
