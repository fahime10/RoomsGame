#include "classes/Player.h"
#include "classes/Room.h"
#include "classes/Item.h"
#include <vector>

#ifndef INPUT_H
#define INPUT_H

enum class Input {
    LOOK,
    QUIT,
    LIST_ITEMS,
    UNKNOWN
};

Input parseInput(const string& input);

void handleUserInput(Input input, Player p, vector<Room> rooms, vector<Item> items);

#endif // INPUT_H
