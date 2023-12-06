#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item {
public:
    Item() = default;

    Item(const string id, const string desc, const string initialRoom);

    ~Item() = default;

    Item& operator=(const Item& other);

    bool operator==(const Item& other) const;

    string getId() const;
    string getDescription() const;
    string getInitialRoom() const;

private:
    string id_;
    string description_;
    string initial_room;
};

#endif // ITEM_H