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

// Operator == overloaded to help with iterator
bool Item::operator==(const Item& other) const {
    return (this->id_ == other.id_ && this->description_ == other.description_ && 
            this->initial_room == other.initial_room);
}

// Getter function implementations
string Item::getId() const {
    return id_;
}

// Getter function to get the description of the object
string Item::getDescription() const {
    return description_;
}

// Getter function to get the initial room where the object is located
string Item::getInitialRoom() const {
    return initial_room;
}
