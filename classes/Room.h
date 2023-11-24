#include "Item.h"
#include "Enemy.h"
#include <string>
#include <vector>
using namespace std;

class Room {

public:
    // This constructor should define all items, enemies and exits
    Room(string, string, vector<string>, bool);

    ~Room() = default;

    string getId() const;

    string getDescription() const;

    int getItemAmount() const;

    string getExits() const;

    string getPrevExit() const;

    // Player may take those items, and so they are no longer in the room
    void addItem(Item);

    // Player may defeat those enemies, so there is no longer a threat in the room
    void addEnemy(Enemy);

    void setPrevExit(string);

    void setPlayerLocation();

    void setExits(vector<string> exits);

    string printExits() const;

private:
    string id_;
    string description_;
    string prev_exit;

    vector<Item> items_;
    vector<Enemy> enemy_;
    vector<string> exits_;

    bool player_location;
};