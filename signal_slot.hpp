//
//  signal_slot.hpp
//  Minesweeper
//
//  Created by Lonteron Bassergoy on 04/01/2018.
//  Copyright © 2018 Lonteron Bassergoy. All rights reserved.
//

#ifndef signal_slot_hpp
#define signal_slot_hpp

#include <vector>
#include <initializer_list>
#include <set>
#include <functional>

typedef std::function<void(int)> slot;

class signal {
    friend void emit(const class signal&, int);
    
public:
    signal(std::initializer_list<int>);
    ~signal();

    bool contains(int id) const;
    template <typename T> void connect(T *app, void (T::*f)(int)) {
        slots.push_back([=] (int i) { (app->*f)(i); });
    }
    
private:
    std::set<int> ids;
    std::vector<slot> slots;
};

void emit(const class signal&, int);

#endif /* signal_slot_hpp */

