#include "Item.h"
#include <vector>
using namespace std;

class Player {
public:
    Player() = default;

    ~Player() = default;

    string viewInventory() const;

    void addToInventory(Item);

private:
    vector<Item> inventory_;
};