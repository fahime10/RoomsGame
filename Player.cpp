#include "Player.h"

// Player constructor
Player::Player(string initialRoom) {
    initial_room = initialRoom;
    current_room = initial_room;
}

// Get player's initial room
string Player::getInitialRoom() const {
    return initial_room;
}

// Get player's current room
string Player::getCurrentRoom() const {
    return current_room;
}

// Get player's current inventory
const map<string, Item> Player::getInventory() const {
    return inventory_;
}

// List player's inventory
string Player::viewInventory() const {
    string items;

    if (inventory_.empty()) {
        return "No items in the inventory";
    }

    items = "Your items are: \n";

    for (const auto item: inventory_) {
        items += item.second.getId() + "\n";
    }

    return items;
}

// Add to player's inventory
void Player::addToInventory(Item& item) {
    inventory_[item.getId()] = item;
}

// Set the current room id for player
void Player::setCurrentRoom(string id) {
    current_room = id;
}