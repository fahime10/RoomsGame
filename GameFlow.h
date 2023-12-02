#include <iostream>
#include <vector>
#include <map>
#include "json.hpp"
#include "classes/Room.h"
#include "classes/Enemy.h"
#include "classes/Item.h"
#include "classes/Player.h"
using namespace std;
using json = nlohmann::json;

class GameFlow {
    public:
        GameFlow() = default;

        ~GameFlow() = default;

        string getType() const;

        vector<string> getConditions() const; 

        void buildGame(json);

        void playGame();

        void printItems() const;

        void setType(string);

        void setConditions(vector<string>);

    private:
        map<string, Room> rooms_;
        map<string, Enemy> enemies_;
        map<string, Item> items_;

        string type_;
        vector<string> conditions_;

        Player p_;
};