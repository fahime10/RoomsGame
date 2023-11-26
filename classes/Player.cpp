#include "Player.h"

Player::Player(string initialRoom) {
    initial_room = initialRoom;
}

string Player::getInitialRoom() const {
    return initial_room;
}

// When user executes "list items"
string Player::viewInventory() const {
    string items;

    items = "Your items are: \n";

    for (const Item& item: inventory_) {
        items += item.getId() + " \n";
    }

    return items;
}

// When user executes "grab" or "take" or "pick"
void Player::addToInventory(Item item) {
    inventory_.push_back(item);
}