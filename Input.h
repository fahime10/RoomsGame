#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "Enemy.h"
#include <vector>
#include <map>
#include <iostream>

#ifndef INPUT_H
#define INPUT_H

enum class Input {
    LOOK,
    LIST_ITEMS,
    TAKE_ITEM,
    CHECK_ITEM,
    LIST_EXITS,
    MOVE,
    ATTACK,
    QUIT,
    UNKNOWN
};

Input parseInput(const vector<string>&);

void handleInput(vector<string>, Input, Player&, map<string, Room>&, map<string, Item>&, map<string, Enemy>&);


#endif // INPUT_H
