//
//  signal_slot.cpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 04/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#include <algorithm>
#include "signal_slot.hpp"
#include "Application.hpp"

//void slot::call(int info) const {
//    return func(app, info);
//}

signal::signal(std::initializer_list<int> l) :
    ids(l)
{
    
}

signal::~signal() {}

bool signal::contains(int id) const {
    return ids.find(id) != ids.cend();
}


void emit(const class signal &si, int info) {
    for (auto &el : si.slots)
        el(info);
}


