#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Item {
public:
    Item() = default;

    Item(string, string, string);

    ~Item() = default;

    Item& operator=(const Item&);

    bool operator==(const Item&) const;

    string getId() const;
    string getDescription() const;
    string getInitialRoom() const;

private:
    string id_;
    string description_;
    string initial_room;
};

#endif // ITEM_H