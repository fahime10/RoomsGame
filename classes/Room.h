#ifndef ROOM_H
#define ROOM_H



#include "Item.h"
#include "Enemy.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class Room {

public:
    Room(string, string, vector<map<string, string>>);

    ~Room() = default;

    string getId() const;

    string getDescription() const;

    string getEnemies() const;

    string getItems() const;

    string getExits() const;

    string getPrevExit() const;

    // Player may take those items, and so they are no longer in the room
    void addItem(Item);

    // Player may defeat those enemies, so there is no longer a threat in the room
    void addEnemy(Enemy);

    void setPrevExit(string);

    void setPlayerLocation();

    string printExits() const;

private:
    string id_;
    string description_;
    string prev_exit;

    vector<Item> items_;
    vector<Enemy> enemies_;
    vector<map<string, string>> exits_;

    bool player_location;
};


#endif // ROOM_H