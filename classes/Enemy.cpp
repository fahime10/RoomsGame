#include "Enemy.h"
#include <iostream>
#include <cstdlib> // for rand function (STL used)
#include <vector> // handling dynamic arrays (STL used)

using namespace std;


//Constructor implementation
Enemy::Enemy(const string& id, const string& desc, int aggressiveness, const string& initialRoom, const vector<string>& killedBy) {
    id_ = id;
    description_ = desc;
    aggressiveness_ = aggressiveness;
    initialRoom_ = initialRoom;
    killedBy_ = killedBy;
}



// Destructor implementation
Enemy::~Enemy() {
    
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
    return initialRoom_;
}

// Getter function to get the list of objects that can kill the enemy
const vector<string>& Enemy::getKilledBy() const {
    return killedBy_;
}

// Member function implementation for moving the enemy to a different room

void Enemy::moveToRoom(const string& room) {
    initialRoom_ = room;
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