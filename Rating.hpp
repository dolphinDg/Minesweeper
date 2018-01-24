//
//  Rating.hpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 07/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#ifndef Rating_hpp
#define Rating_hpp

#include "Application.hpp"
#include <vector>

class Rating : public Application {
public:
    Rating(std::vector<int>, Application*);
    ~Rating();
private:
    void display();
    
    std::vector<int> scores;
};

#endif /* Rating_hpp */
