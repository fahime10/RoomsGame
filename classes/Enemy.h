#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Enemy {
public:
    // Constructor
    Enemy(const string id, const string desc, int aggressiveness,
          const string initialRoom, const vector<Item> killedBy);

    // Destructor
    ~Enemy() = default;

    bool operator==(const Enemy& other) const;

    // Getter functions
    string getId() const;
    string getDescription() const;
    int getAggressiveness() const;
    string getInitialRoom() const;
    string printKilledBy() const;

    const vector<Item>& getKilledBy() const;

    // Member functions
    bool attackPlayer() const;
    void printAttackMessage() const;

private:
    // Member variables
    string id_;
    string description_;
    int aggressiveness_;
    string initial_room;
    vector<Item> killed_by;
};

#endif // ENEMY_H