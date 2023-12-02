#include "Player.h"

Player::Player(string initialRoom) {
    initial_room = initialRoom;
}

string Player::getInitialRoom() const {
    return initial_room;
}

string Player::getCurrentRoom() const {
    return current_room;
}

const map<string, Item> Player::getInventory() const {
    return inventory_;
}

// When user executes "list items"
string Player::viewInventory() const {
    string items;

    if (inventory_.empty()) {
        return "No items in the inventory";
    }

    items = "Your items are: \n";

    for (const auto item: inventory_) {
        items += "[ " + item.second.getId() + " ] \n";
    }

    return items;
}

// When user executes "grab" or "take" or "pick"
void Player::addToInventory(Item& item) {
    inventory_[item.getId()] = item;
}

// Set the current room id when player moves rooms
void Player::setCurrentRoom(string id) {
    current_room = id;
}