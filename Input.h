#include "classes/Player.h"
#include "classes/Room.h"
#include "classes/Item.h"
#include "classes/Enemy.h"
#include <vector>

#ifndef INPUT_H
#define INPUT_H

enum class Input {
    LOOK,
    LIST_ITEMS,
    TAKE_ITEM,
    CHECK_ITEM,
    LIST_EXITS,
    GO_LEFT,
    GO_UP,
    MOVE,
    GO_RIGHT,
    GO_DOWN,
    GO_BACK,
    QUIT,
    UNKNOWN
};

Input parseInput(const vector<string>& input);

void handleUserInput(vector<string> input, Input enumInput, Player& p, vector<Room>& rooms, vector<Item>& items);


#endif // INPUT_H
