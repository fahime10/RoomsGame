#include "Room.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

// Anytime a Room instance is created, we do not know items and enemies beforehand, as those
// are created after rooms, and then assigned to rooms
Room::Room(string id, string description, vector<map<string, string>> exits = {}) {
    id_ = id;
    description_ = description;
    exits_ = exits;
}

string Room::getId() const {
    return id_;
}

string Room::getDescription() const {
    return description_;
}

// This is used by gameflow for checking if exits requested by user do exits or not, 
// and which ones
string Room::getExits() const {
    if (!exits_.empty()) {
        string exits;

        exits = "Your exits are: \n";

        for (const auto& map: exits_) {
            for (const auto& pair: map) {
                exits += pair.first + ", which goes to " + pair.second + " \n";
            }
        }

        return exits;
    }

    return "No exits";
}

// This is used when user asks for possible exits
string Room::printExits() const {
    string exits;

    exits = "Your exits are: \n";

    if (!exits_.empty()) {
        for (const auto& map: exits_) {
            for (const auto& pair: map) {
                exits += pair.second + " \n";
            }
        }
    } else {
        exits += "There are no exits";
    }

    return exits;
}

// When user asks "go back", this will help find the previous room
string Room::getPrevExit() const {
    return prev_exit;
}

vector<Enemy> Room::getEnemies() const {
    return enemies_;
}

void Room::printEnemies() const {
    string enemies;
    
    for (auto enemy: enemies_) {
        enemies += enemy.getId() + " \n";
    }
    
    cout << enemies << endl;
}

vector<Item> Room::getItems() const {
    return items_;
}

string Room::printItems() const {
    string items;

    for (auto item: items_) {
        items += "[ " + item.getId() + " ] ";
    }

    return items;
}

// Function to be used in gameflow, add items one by one
void Room::addItem(Item& item) {
    items_.push_back(item);
}

// Function to be used in gameflow, add enemies one by one
void Room::addEnemy(Enemy& enemy) {
    enemies_.push_back(enemy);
}

// This relies on the JSON map, where each room has a way to go back to previous room
// from user's point of view
void Room::setPrevExit(string exit) {
    prev_exit = exit;
}

// Set or unset the player location on rooms
void Room::setPlayerLocation() {
    player_location = !player_location;
}