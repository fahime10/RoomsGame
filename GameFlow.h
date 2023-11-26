#include <iostream>
#include <vector>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class GameFlow {
    public:
        GameFlow() = default;

        ~GameFlow() = default;

        void buildGame(json);

    private:
        vector<Room> rooms;
        vector<Enemy> enemies;
        vector<Item> items;

        Player p;
};