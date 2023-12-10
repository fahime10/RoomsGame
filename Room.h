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

    void addItem(Item&);
    void removeItem(const string&);
    void addEnemy(Enemy&);
    void removeEnemy(const string&);

    string printItemDesciption(Item&) const;
    string printItems() const;
    string printEnemies() const;
    string printExits() const;

private:
    string id_;
    string description_;

    map<string, Item> items_;
    map<string, Enemy> enemies_;
    map<string, string> exits_;
};


#endif // ROOM_H