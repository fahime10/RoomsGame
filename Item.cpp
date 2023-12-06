// Item.cpp
#include "Item.h"
#include <iostream>

using namespace std;

// Constructor implementation
Item::Item(const string id, const string desc, const string initialRoom) {
    id_ = id;
    description_ = desc;
    initial_room = initialRoom;
}

// Operator = overloaded to help with iterator
Item& Item::operator=(const Item& other) {
    if (this != &other) {
        this->id_ = other.id_;
        this->description_ = other.description_;
        this->initial_room = other.initial_room;
    }

    return *this;
}

// Operator == overloaded to help with iterator
bool Item::operator==(const Item& other) const {
    return (this->id_ == other.id_ && this->description_ == other.description_ && 
            this->initial_room == other.initial_room);
}

// Get id of item
string Item::getId() const {
    return id_;
}

// Get the description of the item
string Item::getDescription() const {
    return description_;
}

// Get the initial room where the object is located
string Item::getInitialRoom() const {
    return initial_room;
}
