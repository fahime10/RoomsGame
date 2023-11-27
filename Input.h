#include "classes/Player.h"
#include "classes/Room.h"
#include <vector>

#ifndef INPUT_H
#define INPUT_H

enum class Input {
    LOOK,
    GO,
    QUIT,
    UNKNOWN
};

Input parseInput(const string& input);

void handleUserInput(Input input, Player p, vector<Room> room);

#endif // INPUT_H