#include "Enemy.h"
#include <iostream>
#include <cstdlib> // for rand function (STL used)
#include <vector> // handling dynamic arrays (STL used)

using namespace std;

// Constructor implementation
Enemy::Enemy(string id, string desc, int aggressiveness, string initialRoom, map<string, Item> killedBy) {
    id_ = id;
    description_ = desc;
    aggressiveness_ = aggressiveness;
    initial_room = initialRoom;
    killed_by = killedBy;
}

// Operator == overloaded to help with iterator
bool Enemy::operator==(const Enemy& other) const {
    return (this->id_ == other.id_ && 
            this->description_ == other.description_ &&
            this->aggressiveness_ == other.aggressiveness_ &&
            this->initial_room == other.initial_room &&
            this->killed_by == other.killed_by);
}

// Get the enemy id
string Enemy::getId() const {
    return id_;
}

// Get the enemy description
string Enemy::getDescription() const {
    return description_;
}

// Get the enemy's aggressiveness
int Enemy::getAggressiveness() const {
    return aggressiveness_;
}

// Get the initial room where the enemy is located
string Enemy::getInitialRoom() const {
    return initial_room;
}

// Get the items required to defeat enemy
const map<string, Item>& Enemy::getKilledBy() const {
    return killed_by;
}

// Get the list of objects that can kill the enemy
string Enemy::printKilledBy() const {
    string items;
    
    for (const auto& item: killed_by) {
        items += "[ " + item.second.getId() + " ] \n";
    }
    
    return items;
}

// Member function implementation to determine if the enemy attacks the player
bool Enemy::attackPlayer() const {
    int randomChance = rand() % 101;
    return randomChance < aggressiveness_; 
}

// Member function implementation to print an attack message
void Enemy::printAttackMessage() const {
    cout << "The enemy " << id_ << " attacks you and you are defeated. Game over!" << endl;
}
