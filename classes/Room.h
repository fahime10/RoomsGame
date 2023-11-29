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

    const vector<Enemy>& getEnemies() const;

    const vector<Item>& getItems() const;

    string getExits() const;

    string getPrevExit() const;

    void addItem(Item&);

    void removeItem(const Item&);

    void addEnemy(Enemy&);

    void removeEnemy(const Enemy&);

    void setPrevExit(string);

    string printItems() const;

    void printEnemies() const;

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