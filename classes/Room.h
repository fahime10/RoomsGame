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
    Room() = default;

    Room(string, string, map<string, string>);

    ~Room() = default;

    string getId() const;

    string getDescription() const;

    const map<string, Enemy>& getEnemies() const;

    const map<string, Item>& getItems() const;

    const map<string, string>& getExits() const;

    string getPrevExit() const;

    void addItem(Item&);

    void removeItem(const string&);

    void addEnemy(Enemy&);

    void removeEnemy(const string&);

    void setPrevExit(string);

    string printItems() const;

    string printEnemies() const;

    void setPlayerLocation();

    string printExits() const;

private:
    string id_;
    string description_;
    string prev_exit;

    map<string, Item> items_;
    map<string, Enemy> enemies_;
    map<string, string> exits_;

    bool player_location;
};


#endif // ROOM_H