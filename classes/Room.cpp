#include "Room.h"
#include <string>
using namespace std;

// Room::Room(string, string, int, int, int, Item*, Enemy*, string*, bool) {

// }

// Room::~Room() {
//     delete[] items;
//     delete[] enemies;
//     delete[] exits_;
// }

string Room::getId() const {
    return id_;
}

string Room::getDescription() const {
    return description_;
}

int Room::getItemAmount() const {
    return item_amount;
}

int Room::getEnemyAmount() const {
    return enemy_amount;
}

// This is used by gameflow for checking if exits requested by user do exits or not
string Room::getExits() const {
    if (exits_) {
        string exits;

        exits = "Your exits are: \n";

        for (int i = 0; i < exit_amount; i++) {
            exits += *(exits_+i); 
        }

        return exits;
    }
}

// This is used when user asks for possible exits
string Room::printExits() const {
    string exits;

    exits = "Your exits are: \n";

    if (exits_) {
        for (int i = 0; i < exit_amount; i++) {
            exits += *(exits_+i); 
        }
    } else {
        exits += "There are no exits";
    }

    return exits;
}


string Room::getPrevExit() const {
    return prev_exit;
}

void Room::setPrevExit(string exit) {
    prev_exit = exit;
}

void Room::setPlayerLocation() {
    player_location = !player_location;
}