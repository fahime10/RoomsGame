#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include <map>
using namespace std;

class Player {
public:
    Player() = default;
    
    Player(string);

    ~Player() = default;

    string getInitialRoom() const;

    string getCurrentRoom() const;

    string viewInventory() const;

    const map<string, Item> getInventory() const;

    void addToInventory(Item&);

    void setCurrentRoom(string);

private:
    string initial_room;
    string current_room;
    map<string, Item> inventory_;
};

#endif // PLAYER_H