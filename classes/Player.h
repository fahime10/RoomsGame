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

    string viewInventory() const;

    void addToInventory(Item);

private:
    string initial_room;
    vector<Item> inventory_;
};

#endif // PLAYER_H