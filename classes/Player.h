// #include "Item.h"
#include <string>
using namespace std;

class Player {
public:
    Player();

    ~Player();

    string viewInventory() const;

private:
    // Decision to be made whether this is a dynamic array or linked list
    // Item* inventory_;

};