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

    } else if ((input[0] == "grab" || input[0] == "take" || input[0] == "pick") && input.size() == 2) {
        return Input::TAKE_ITEM;

    } else if (((input[0] == "check" || input[0] == "see") && input.size() == 2) ||
                 (input[0] == "look" && input[1] == "at") && input.size() == 3) {
        return Input::CHECK_ITEM;

    } else if ((input[0] == "exit" || input[0] == "exits") && input.size() == 1 || 
                ((input[0] == "list" && input[1] == "exits" && input.size() == 2))) {
        return Input::LIST_EXITS;

    } else if (((input[0] == "q" || input[0] == "quit") && input.size() == 1) ||
                (input[0] == "quit" && input[1] == "game" && input.size() == 2)) {
        return Input::QUIT;
    } else if ((input[0] == "go" || input[0] == "move") && input.size() == 2) {
        return Input::MOVE;
    }
    
    return Input::UNKNOWN;
}

void movePlayer(Player& p, const string& direction, vector<Room>& rooms) {
    string currentRoomId = p.getCurrentRoom();

    for (const auto& room : rooms) {
        if (currentRoomId == room.getId()) {
            // Find the position of the specified direction in the exits description of the room
            auto pos = room.getExits().find(direction);

            // Check if the specified direction is found in the exits description
            if (pos != string::npos) {
                // Find the position of "goes to" in the exits description, starting from the position of the direction
                auto arrowPos = room.getExits().find("goes to", pos);

                // Find the position of the newline character after "goes to"
                auto newlinePos = room.getExits().find("\n", arrowPos);

                // Check if both "goes to" and the newline character are found
                if (arrowPos != string::npos && newlinePos != string::npos) {
                    // Extract the exit room ID from the exits description
                    string exitRoom = room.getExits().substr(arrowPos + 8, newlinePos - arrowPos - 8);

                    // Set the player's current room to the exit room
                    p.setCurrentRoom(exitRoom);

                    // Print a message indicating that the player has moved in the specified direction
                    cout << "You have moved " << direction << ".\n" << endl;

                    // Exit the function
                    return;
                }
            }

            // If the specified direction is not found in the exits description, print an error message
            cout << "There is no exit in the " << direction << " direction.\n" << endl;

            // Exit the function
            return;
        }
    }

    // If the current room ID is not found, print an error message
    cout << "Error: Current room not found.\n" << endl;
}

void handleUserInput(vector<string> input, Input enumInput, Player& p, vector<Room>& rooms, vector<Item>& items) {
    string currentRoomDesc;
    string exits;
    string itemList;
    bool anyItem;

    for (const auto& room : rooms) {
        if (p.getCurrentRoom() == room.getId()) {
            currentRoomDesc = room.getDescription();

            if (!(room.getItems().empty())) {
                anyItem = true;
                itemList = "There are items in this room: \n" + room.printItems();
            } 
            
            exits = room.getExits();
        }
    }

    switch (enumInput) {
        case Input::LOOK:
            if (anyItem) {
                cout << currentRoomDesc << endl;
                cout << itemList << "\n" << endl;
            } else {
                cout << currentRoomDesc << "\n" << endl;
            }
            break;

        case Input::LIST_ITEMS:
            cout << p.viewInventory() << "\n" << endl;
            break;

        case Input::TAKE_ITEM:
            if (anyItem) {
                string requestedItem = input[1];
                string foundItem = "";

                for (Item& item: items) {
                    if (requestedItem == item.getId()) {
                        p.addToInventory(item);

                        auto it = find(items.begin(), items.end(), item);
                        
                        if (it != items.end()) {
                            items.erase(it);
                        }

                        for (Room& room: rooms) {
                            if (room.getId() == item.getInitialRoom()) {
                                room.removeItem(item);
                                foundItem = "You have taken: " + requestedItem + "\n";
                                break;
                            }
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

        case Input::CHECK_ITEM:
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
        
        case Input::MOVE:
            if (input.size() == 2) {
                string direction = input[1];
                movePlayer(p, direction, rooms);
            } else {
                cout << "Invalid move command. Usage: go <direction>.\n" << endl;
            }
            break;

        case Input::LIST_EXITS:
            cout << exits << endl;
            break;

        case Input::UNKNOWN:
            cout << "Instruction not understood" << "\n" << endl;
            break;
    }
}
