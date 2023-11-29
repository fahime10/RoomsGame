#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include <vector>
using namespace std;

class Player {
public:
    Player() = default;
    Player(string);

    ~Player() = default;

    string getInitialRoom() const;

    string getCurrentRoom() const;

    string viewInventory() const;

    const vector<Item>& getInventory() const;

    void addToInventory(Item&);

    void setCurrentRoom(string);

private:
    string initial_room;
    string current_room;
    vector<Item> inventory_;
};

#endif // PLAYER_H