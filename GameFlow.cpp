#include "json.hpp"
#include "GameFlow.h"
#include "Input.h"
using namespace std;
using json = nlohmann::json;

void presentCurrentRoom(Player, map<string, Room>);
void checkGameOver(string, vector<string>, Player, map<string, Room>&);

// Build game with Room objects and assign into those the Item, Enemy and 
// Player objects according to JSON maps
void GameFlow::buildGame(json j) {
    try {
        for (auto room: j["rooms"]) {
            map<string, string> exits;

            for (auto exit: room["exits"].items()) {
                exits[exit.key()] = exit.value();
            }
            Room r(room["id"], room["desc"], exits);
            rooms_[room["id"]] = r;
        }

        for (auto object: j["objects"]) {
            Item i(object["id"], object["desc"], object["initialroom"]);
            items_[i.getId()] = i;
        }

        for (auto enemy: j["enemies"]) {
            map<string, Item> killedBy;

            for (auto item: enemy["killedby"]) {
                for (const auto& i: items_) {
                    if (i.second.getId() == item) {
                        Item object(i.second.getId(), i.second.getDescription(), i.second.getInitialRoom());
                        killedBy[object.getId()] = object;
                    }
                }
            }

            Enemy e(enemy["id"], enemy["desc"], enemy["aggressiveness"], enemy["initialroom"], killedBy);
            enemies_[e.getId()] = e;
        }

        p_ = Player(j["player"]["initialroom"]);

        for (auto& room: rooms_) {
            for (auto enemy: enemies_) {
                if (enemy.second.getInitialRoom() == room.first) {
                    room.second.addEnemy(enemy.second);
                }
            }

            for (auto item: items_) {
                if (item.second.getInitialRoom() == room.first) {
                    room.second.addItem(item.second);
                }
            }
        }

        type_ = j["objective"]["type"];
        
        for (auto condition: j["objective"]["what"]) {
            conditions_.push_back(condition);
        }

    } catch (exception ex) {
        cerr << "Error reading file" << endl;
        return;
    }
}

// Function to play the game and handle all sorts of user input
void GameFlow::playGame() {
    string command;

    presentCurrentRoom(p_, rooms_);

    do {
        string currentRoom = p_.getCurrentRoom();

        cout << "> ";

        getline(cin, command);

        istringstream strStream(command);
        vector<string> strArray;
        string singleStr;

        while (strStream >> singleStr) {
            strArray.push_back(singleStr);
        }

        Input enumInput = parseInput(strArray);
        handleInput(strArray, enumInput, p_, rooms_, items_, enemies_);
        checkGameOver(type_, conditions_, p_, rooms_);

        if (p_.getCurrentRoom() != currentRoom) {
            presentCurrentRoom(p_, rooms_);
            currentRoom = p_.getCurrentRoom();
        }

    } while (command != "quit" && command != "q");
}

// Function to present the current room the player is at
void presentCurrentRoom(Player p, map<string, Room> rooms) {
    int itemsSize = 0;
    int enemiesSize = 0;

    bool anyItem = !rooms[p.getCurrentRoom()].getItems().empty();
    itemsSize = rooms[p.getCurrentRoom()].getItems().size();

    bool anyEnemy = !rooms[p.getCurrentRoom()].getEnemies().empty();
    enemiesSize = rooms[p.getCurrentRoom()].getEnemies().size();

    cout << "\n" << rooms[p.getCurrentRoom()].getDescription() << "\n" << endl;

    if (anyItem && itemsSize > 1) {
        cout << "There are items in this room: " << endl;
        cout << rooms[p.getCurrentRoom()].printItems() << "\n" << endl;
    } else if (anyItem) {
        cout << "There is an item in this room: " << endl;
        cout << rooms[p.getCurrentRoom()].printItems() << "\n" << endl;
    }

    if (anyEnemy && enemiesSize > 1) {
        cout << "There are enemies in this room: " << endl;
        cout << rooms[p.getCurrentRoom()].printEnemies() << "\n" << endl;
    } else if (anyEnemy) {
        cout << "There is an enemy in this room: " << endl;
        cout << rooms[p.getCurrentRoom()].printEnemies() << "\n" << endl;
    }
}

// This will constantly check if the player has been defeated by enemy or 
// completed the map
void checkGameOver(string type, vector<string> conditions, Player p, map<string, Room>& rooms) {
    bool win = true;

    if (type == "kill") {
        for (string objective: conditions) {
            for (auto room: rooms) {
                for (const auto enemy: room.second.getEnemies()) {
                    if (enemy.second.getId() == objective) {
                        win = false;
                        break;
                    }
                }
            }
        }
    } else if (type == "collect") {
        for (string objective: conditions) {
            for (auto room: rooms) {
                for (const auto item: room.second.getItems()) {
                    if (item.second.getId() == objective) {
                        win = false;
                        break;
                    }
                }
            }
        }


    } else if (type == "room") {
        for (string objective: conditions) {
            if (p.getCurrentRoom() != objective) {
                win = false;
            }
        }
    }

    if (win) {
        cout << "Congratulations! \nYou have completed the map.\n" << endl;
        exit(0);
    }
}

// Get the type of win condition
string GameFlow::getType() const {
    return type_;
}

// Get the conditions required to win the map
vector<string> GameFlow::getConditions() const {
    return conditions_;
}