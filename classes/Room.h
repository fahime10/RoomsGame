// #include "Item.h"
// #include "Enemy.h"
#include <string>
using namespace std;

class Room {

public:
    // To delete
    Room();

    // This constructor should define all items, enemies and exits
    // Room(string, string, int, int, int, Item*, Enemy*, string*, string, bool);

    ~Room();

    string getId() const;

    string getDescription() const;

    int getItemAmount() const;

    int getEnemyAmount() const;

    string getExits() const;

    string getPrevExit() const;

    // Player may take those items, and so they are no longer in the room
    // Item setItem(string);

    // Player may defeat those enemies, so there is no longer a threat in the room
    // Enemy setEnemy(string);

    void setPrevExit(string);

    void setPlayerLocation();

    string printExits() const;

private:
    string id_;
    string description_;
    int item_amount;
    int enemy_amount;
    int exit_amount;

    // Dynamic array of Items
    // Item* items;

    // Dynamic array of Enemies
    // Enemy* enemies;

    // Dynamic array of exits
    string* exits_;

    string prev_exit;

    bool player_location;

};