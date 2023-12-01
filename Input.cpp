#include <iostream>
#include "Input.h"
#include <algorithm>
using namespace std;

// This is required to work with switch statements
// Some strings/commands could be regarded as the same enum
Input parseInput(const vector<string>& input) {
    if (((input[0] == "look" || input[0] == "see" || input[0] == "check") && input.size() == 1) || 
        ((input[0] == "look" && input[1] == "around") && input.size() == 2) ||
        ((input[0] == "check" && input[1] == "room") && input.size() == 2)) {
        return Input::LOOK;

    } else if (((input[0] == "items" || input[0] == "inventory") && input.size() == 1) || 
                ((input[0] == "list" && input[1] == "items") && input.size() == 2) || 
                ((input[0] == "check" || input [0] == "view") && input[1] == "inventory" && input.size() == 2)) {
        return Input::LIST_ITEMS;

    } else if ((input[0] == "grab" || input[0] == "take" || input[0] == "pick")) {
        return Input::TAKE_ITEM;

    } else if (((input[0] == "check" || input[0] == "see") && input.size() == 2) ||
                 (input[0] == "look" && input[1] == "at") && input.size() == 3) {
        return Input::CHECK_ITEM;

    } else if ((input[0] == "exit" || input[0] == "exits") && input.size() == 1 || 
                ((input[0] == "list" && input[1] == "exits" && input.size() == 2))) {
        return Input::LIST_EXITS;

    } else if ((input[0] == "go" || input[0] == "move") && input.size() == 2) {
        return Input::MOVE;

    } else if ((input[0] == "attack" || input[0] == "kill")) {
        return Input::ATTACK;

    }
    
    return Input::UNKNOWN;
}

void handleUserInput(vector<string> input, Input enumInput, Player& p, 
                     vector<Room>& rooms, vector<Item>& items, vector<Enemy>& enemies) {
    string currentRoomDesc;
    string exits;
    string itemList;
    string enemyList;
    bool anyItem;
    bool anyEnemy;

    for (const auto& room : rooms) {
        if (p.getCurrentRoom() == room.getId()) {
            currentRoomDesc = room.getDescription();

            if (!(room.getItems().empty())) {
                anyItem = true;
                itemList = "There are items in this room: \n" + room.printItems();
            } 

            if (!(room.getEnemies().empty())) {
                anyEnemy = true;
                enemyList = "There are enemies in this room: \n" + room.printEnemies();
            } 
            
            exits = room.printExits();
        }
    }

    switch (enumInput) {
        case Input::LOOK: 
        {
            if (anyItem) {
                cout << currentRoomDesc << endl;
                cout << itemList << "\n" << endl;
            } else {
                cout << currentRoomDesc << "\n" << endl;
            }
            break;
        }

        case Input::LIST_ITEMS:
        {
            cout << p.viewInventory() << "\n" << endl;
            break;
        }

        case Input::TAKE_ITEM:
        {
            if (anyItem) {
                string requestedItem = "";

                for (int i = 1; i < input.size(); i++) {
                    if (i + 1 == input.size()) {
                        requestedItem += input[i];
                    } else {
                        requestedItem += input[i] + " ";   
                    }
                }
                
                string foundItem = "";

                for (Item& item: items) {
                    if (requestedItem == item.getId()) {
                        p.addToInventory(item);

                        for (Room& room: rooms) {
                            if (room.getId() == item.getInitialRoom()) {
                                room.removeItem(item);
                                foundItem = "You have taken: " + requestedItem + "\n";
                                break;
                            }
                        }

                        auto it = find(items.begin(), items.end(), item);
                        
                        if (it != items.end()) {
                            items.erase(it);
                        }
                        break;
                    }
                }

                if (foundItem.empty()) {
                    cout << "Item not found in the room\n" << endl;
                } else {
                    cout << foundItem << "\n" << endl;
                }

            } else {
                cout << "Item not found\n" << endl;
            }
            break;
        }

        case Input::CHECK_ITEM:
        {
            if (!p.getInventory().empty()) {
                string object = "";

                for(const Item& item: p.getInventory()) {
                    if (item.getId() == input[1] || item.getId() == input[2]) {
                        object += item.getDescription();
                        break;
                    }
                }

                if (object.empty()) {
                    cout << "Item not found\n" << endl;
                } else {
                    cout << object << "\n" << endl;
                }

            } else {
                cout << "Item not found\n" << endl;
            }
            break;
        }
        
        case Input::MOVE:
        {
            if (input.size() == 2) {
                string direction = input[1];
                bool movePossible = false;
                string newRoom = "";

                for (Room& room: rooms) {
                    if (p.getCurrentRoom() == room.getId()) {
                        for (auto& map: room.getExits()) {
                            for (auto& keyValue: map) {
                                if (keyValue.first == direction) {
                                    movePossible = true;
                                    newRoom = keyValue.second;
                                    break;
                                }
                            }
                        }
                    }
                }

                if (movePossible) {
                    for (Room& room: rooms) {
                        if (room.getId() == newRoom) {
                            p.setCurrentRoom(room.getId());
                            cout << "You moved in " << newRoom << endl;
                            break;
                        }
                    }
                } else {
                    cout << "Move not possible\n" << endl;
                }

            } else {
                cout << "Invalid move command. Usage: go <direction>.\n" << endl;
            }
            break;
        }

        case Input::ATTACK:
        {
            bool success;
            string requestedEnemy = "";
            string enemyFound = "";

            for (int i = 1; i < input.size(); i++) {
                if (i + 1 == input.size()) {
                    requestedEnemy += input[i];
                } else {
                    requestedEnemy += input[i] + " ";   
                }
            }

            for (Room& room: rooms) {
                for (const Enemy& enemy: room.getEnemies()) {
                    if (p.getCurrentRoom() == enemy.getInitialRoom() && enemy.getId() == requestedEnemy) {
                        enemyFound = enemy.getId();
                        success = 
                            all_of(enemy.getKilledBy().begin(), enemy.getKilledBy().end(), [&](const Item& item) {
                            return 
                            find(p.getInventory().begin(), p.getInventory().end(), item) != p.getInventory().end();
                        });

                        if (success) {
                            cout << "Enemy " << enemy.getId() << " has been defeated\n" << endl;
                            room.removeEnemy(enemy);

                            auto it = find(enemies.begin(), enemies.end(), enemy);
                        
                            if (it != enemies.end()) {
                                enemies.erase(it);
                            }
                            break;
                        }
                    }
                }
            }

            if (enemyFound.empty()) {
                cout << "Instruction not understood\n" << endl;
            } else if (!success) {
                cout << "You do not have enough items. \nYou have been defeated" << endl;
                exit(0);
            }
            break;
        }


        case Input::LIST_EXITS:
        {
            cout << exits << endl;
            break;
        }

        case Input::UNKNOWN:
        {
            cout << "Instruction not understood" << "\n" << endl;
            break;
        }
    }
}
