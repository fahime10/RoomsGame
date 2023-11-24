// Object.cpp
#include "Object.h"
#include <iostream>

using namespace std;

// Constructor implementation
Object::Object(const string& id, const string& desc, const string& initialRoom) {
    id_ = id;
    description_ = desc;
    initialRoom_ = initialRoom;
}

// Destructor implementation
Object::~Object() {
 
}

// Getter function implementations
string Object::getId() const {
    return id_;
}

// Getter function to get the description of the object
string Object::getDescription() const {
    return description_;
}

// Getter function to get the initial room where the object is located
string Object::getInitialRoom() const {
    return initialRoom_;
}
