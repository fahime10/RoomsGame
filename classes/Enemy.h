#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>
#include <map>
#include "Item.h"

using namespace std;

class Enemy {
public:
    Enemy() = default;

    // Constructor
    Enemy(string id, string desc, int aggressiveness, string initialRoom, map<string, Item> killedBy);

    // Destructor
    ~Enemy() = default;

    bool operator==(const Enemy& other) const;

    // Getter functions
    string getId() const;
    string getDescription() const;
    int getAggressiveness() const;
    string getInitialRoom() const;
    string printKilledBy() const;

    const map<string, Item>& getKilledBy() const;

    // Member functions
    bool attackPlayer() const;
    void printAttackMessage() const;

private:
    // Member variables
    string id_;
    string description_;
    int aggressiveness_;
    string initial_room;
    map<string, Item> killed_by;
};

#endif // ENEMY_H