#include <iostream>
#include <vector>
#include <map>
#include "json.hpp"
#include "GameFlow.h"
#include "classes/Item.h"
#include "classes/Room.h"
#include "classes/Player.h"
#include "classes/Enemy.h"
using namespace std;
using json = nlohmann::json;

void GameFlow::buildGame(json j) {
    try {
        for (auto room: j["rooms"]) {
            vector<map<string, string>> keyValues;

            for (auto exit: room["exits"].items()) {
                map<string, string> map;
                string key = exit.key();
                map[key] = exit.value();
                keyValues.push_back(map);
            }
            Room r(room["id"], room["desc"], keyValues);
            rooms.push_back(r);
        }

        for (auto enemy: j["enemies"]) {
            vector<string> killedBy;

            for (auto item: enemy["killedby"]) {
                killedBy.push_back(item);
            }
            Enemy e(enemy["id"], enemy["desc"], enemy["aggressiveness"], enemy["initialroom"], killedBy);
            enemies.push_back(e);
        }

        for (auto object: j["objects"]) {
            Item i(object["id"], object["desc"], object["initialroom"]);
            items.push_back(i);
        }

        p = Player(j["player"]["initialroom"]);

        for (Room room: rooms) {
            for (Enemy enemy: enemies) {
                if (enemy.getInitialRoom() == room.getId()) {
                    room.addEnemy(enemy);
                }
            }

            for (Item item: items) {
                if (item.getInitialRoom() == room.getId()) {
                    room.addItem(item);
                }
            }

            if (p.getInitialRoom() == room.getId()) {
                room.setPlayerLocation();
            } 
        }


    } catch (exception ex) {
        cerr << "Error reading file" << endl;
        return;
    }

    
}