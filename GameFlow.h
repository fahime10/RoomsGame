#include <iostream>
#include <vector>
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

        void buildGame(json);

        void playGame();

        void printItems() const;

    private:
        vector<Room> rooms;
        vector<Enemy> enemies;
        vector<Item> items;

        Player p;
};