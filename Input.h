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
    LIST_EXITS,
    TAKE_ITEM,
    GO_LEFT,
    GO_UP,
    GO_RIGHT,
    GO_DOWN,
    GO_BACK,
    QUIT,
    UNKNOWN
};

Input parseInput(const string& input);

void handleUserInput(Input input, Player& p, vector<Room> rooms, vector<Item> items);

#endif // INPUT_H
