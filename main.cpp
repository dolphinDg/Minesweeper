//
//  main.cpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 02/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#include "Menu.hpp"
#include <memory>

int main() {
    auto menu = std::make_shared<Menu>();
    return menu->exec();
}
