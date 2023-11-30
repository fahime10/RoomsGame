#include <iostream>
#include <vector>
#include <map>
#include "json.hpp"
#include "GameFlow.h"
#include "classes/Item.h"
#include "classes/Room.h"
#include "classes/Player.h"
#include "classes/Enemy.h"
#include "Input.h"
using namespace std;
using json = nlohmann::json;

void presentCurrentRoom(Player, vector<Room>&, vector<Enemy>&);
void checkGameOver();

// Build all instances of Room, Item, Enemy and Player first, then populate
// all the Room instances with Item, Enemy and Player as defined in the 
// chosen JSON map
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

        for (auto object: j["objects"]) {
            Item i(object["id"], object["desc"], object["initialroom"]);
            items.push_back(i);
        }

        for (auto enemy: j["enemies"]) {
            vector<Item> killedBy;

            for (auto item: enemy["killedby"]) {
                for (const Item& i: items) {
                    if (i.getId() == item) {
                        Item object(i.getId(), i.getDescription(), i.getInitialRoom());
                        killedBy.push_back(object);
                    }
                }
            }

            Enemy e(enemy["id"], enemy["desc"], enemy["aggressiveness"], enemy["initialroom"], killedBy);
            enemies.push_back(e);
        }

        p = Player(j["player"]["initialroom"]);

        for (Room& room: rooms) {
            for (Enemy& enemy: enemies) {
                if (enemy.getInitialRoom() == room.getId()) {
                    room.addEnemy(enemy);
                }
            }

            for (Item& item: items) {
                if (item.getInitialRoom() == room.getId()) {
                    room.addItem(item);
                }
            }

            if (p.getInitialRoom() == room.getId()) {
                p.setCurrentRoom(room.getId());
            } 
        }

    } catch (exception ex) {
        cerr << "Error reading file" << endl;
        return;
    }
}

void GameFlow::printItems() const {
    string itemList;
    for (Item item: items) {
        itemList += "[" + item.getId() + "]";
    }

    cout << itemList << endl;
}

// Function to play the game and handle all sorts of user input
void GameFlow::playGame() {
    presentCurrentRoom(p, rooms, enemies);
    
    string currentRoom = p.getCurrentRoom();

    string command;

    getline(cin, command);

    // This is used to handle an array of strings
    istringstream is(command);
    vector<string> strArray;
    string singleStr;

    while (is >> singleStr) {
        strArray.push_back(singleStr);
    }

    Input enumInput;

    // This is where user input is handled
    while (command != "quit" && command != "q") {
        enumInput = parseInput(strArray);
        handleUserInput(strArray, enumInput, p, rooms, items, enemies);
        checkGameOver();

        if (p.getCurrentRoom() != currentRoom) {
            presentCurrentRoom(p, rooms, enemies);
            currentRoom = p.getCurrentRoom();
        }

        getline(cin, command);

        strArray.clear();

        istringstream is(command);

        while (is >> singleStr) {
            strArray.push_back(singleStr);
        }
    }
}

// This presents the current room the player is at
void presentCurrentRoom(Player p, vector<Room>& rooms, vector<Enemy>& enemies) {
    for (Room& room: rooms) {
        if (p.getCurrentRoom() == room.getId()) {
            cout << "\n" << room.getDescription() << endl;

            if (!room.getItems().empty()) {
                cout << "There are items in this room: " << endl;
                cout << room.printItems() << "\n" << endl;
            }

            if (!room.getEnemies().empty()) {
                cout << "There are enemies in this room: " << endl;
                
                for (Enemy& enemy: enemies) {
                    if (enemy.getInitialRoom() == room.getId()) {
                        cout << "[ " << enemy.getId() << " ]" << endl;
                        cout << enemy.getDescription() << endl;
                        cout << "It can be killed by: " << endl;

                        if (enemy.getKilledBy().empty()) {
                            cout << "[ Bare hands ]" << endl;
                        } else {
                            cout << enemy.printKilledBy() << "\n" <<  endl;
                        }
                    }
                }
            }
        }
    }
}

// This will constantly check if the player has been defeated by enemy or
// by soft-locking themselves
void checkGameOver() {

}