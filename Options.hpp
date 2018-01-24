//
//  Options.hpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 07/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#ifndef Options_hpp
#define Options_hpp

#include "Application.hpp"

class Options : public Application {
    
public:
    Options(Application *parent = nullptr);
    ~Options();
    
    void display();
    int dim;
    
private:
    
    //signals
    class signal number_clicked;
    class signal backspace_clicked;
    
    //slots
    void write_number(int);
    void delete_number(int);
};

#endif /* Options_hpp */
