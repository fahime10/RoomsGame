#include "Enemy.h"
#include <iostream>
#include <cstdlib> // for rand function (STL used)
#include <vector> // handling dynamic arrays (STL used)

using namespace std;

//Constructor implementation
Enemy::Enemy(const string id, const string desc, int aggressiveness, const string initialRoom, const vector<Item> killedBy) {
    id_ = id;
    description_ = desc;
    aggressiveness_ = aggressiveness;
    initial_room = initialRoom;
    killed_by = killedBy;
}


// // Destructor implementation
// Enemy::~Enemy() {
    
// }

// Operator == overloaded to help with iterator
bool Enemy::operator==(const Enemy& other) const {
    return (this->id_ == other.id_ && 
            this->description_ == other.description_ &&
            this->aggressiveness_ == other.aggressiveness_ &&
            this->initial_room == other.initial_room &&
            this->killed_by == other.killed_by);
}

// Getter function implementations
string Enemy::getId() const {
    return id_;
}

string Enemy::getDescription() const {
    return description_;
}

// Getter function to get the aggressiveness level of the enemy
int Enemy::getAggressiveness() const {
    return aggressiveness_;
}

// Getter function to get the initial room where the enemy is located
string Enemy::getInitialRoom() const {
    return initial_room;
}

// Getter function to get the items required to defeat enemy
const vector<Item>& Enemy::getKilledBy() const {
    return killed_by;
}

// Getter function to get the list of objects that can kill the enemy
string Enemy::printKilledBy() const {
    string items;
    
    for (const Item& item: killed_by) {
        items += "[ " + item.getId() + " ] \n";
    }
    
    return items;
}

// Member function implementation to determine if the enemy attacks the player
bool Enemy::attackPlayer() const {

    // Generate a random number between 0 and 100 to determine if the enemy attacks
    int randomChance = rand() % 101;
    return randomChance < aggressiveness_;  // enemy will attack unless this condition is true
}

// Member function implementation to print an attack message
void Enemy::printAttackMessage() const {
    cout << "The enemy " << id_ << " attacks you and you are defeated. Game over!" << endl;
  
}
