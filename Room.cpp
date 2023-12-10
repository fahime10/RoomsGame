#include "Room.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

// Room constructor
Room::Room(string id, string description, map<string, string> exits) {
    id_ = id;
    description_ = description;
    exits_ = exits;
}

// Get room id
string Room::getId() const {
    return id_;
}

// Get room description
string Room::getDescription() const {
    return description_;
}

// Get all exits of a room
const map<string, string>& Room::getExits() const {
    return exits_;
}

// Print available exits of a room
string Room::printExits() const {
    string exits;

    exits = "Your exits are: \n";

    if (!exits_.empty()) {
        for (const auto& map: exits_) {
            exits += map.first + " leads to " + map.second + " \n";
        }
    } else {
        exits += "There are no exits";
    }

    return exits;
}

// Get enemies in a room
const map<string, Enemy>& Room::getEnemies() const {
    return enemies_;
}

// Print all enemies in the room
string Room::printEnemies() const {
    string enemies;
    
    for (auto enemy: enemies_) {
        enemies += enemy.second.getId() + "\n";
    }
    
    return enemies;
}

// Get all items in a room
const map<string, Item>& Room::getItems() const {
    return items_;
}

// Print all items in the room
string Room::printItems() const {
    string items;

    for (const auto& item: items_) {
        items += item.second.getId() + "\n";
    }

    return items;
}

string Room::printItemDesciption(Item& item) const {
    return item.getDescription();
}

// Add item to the room
void Room::addItem(Item& item) {
    items_[item.getId()] = item;
}

// Remove item from the room
void Room::removeItem(const string& item) {
    auto it = items_.find(item);

    if (it != items_.end()) {
        items_.erase(it);
    }
}

// Add enemy to the room
void Room::addEnemy(Enemy& enemy) {
    enemies_[enemy.getId()] = enemy;
}

// Remove enemy from the room
void Room::removeEnemy(const string& enemy) {
    auto it = enemies_.find(enemy);

    if (it != enemies_.end()) {
        enemies_.erase(it);
    }
}