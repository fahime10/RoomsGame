#include "classes/Player.h"
#include "classes/Room.h"
#include "classes/Item.h"
#include "classes/Enemy.h"
#include <vector>
#include <map>

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

Input parseInput(const vector<string>& input);

void handleUserInput(vector<string> input, Input enumInput, Player& p, 
                     map<string, Room>& rooms, map<string, Item>& items, map<string, Enemy>& enemies);


#endif // INPUT_H
