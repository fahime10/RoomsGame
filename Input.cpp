#include <iostream>
#include "Input.h"
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

    } else if ((input[0] == "exit" || input[0] == "exits") && input.size() == 1 || 
                ((input[0] == "list" && input[1] == "exits" && input.size() == 2))) {
        return Input::LIST_EXITS;

    } else if (((input[0] == "q" || input[0] == "quit") && input.size() == 1) ||
                (input[0] == "quit" && input[1] == "game" && input.size() == 2)) {
        return Input::QUIT;
    }
    
    return Input::UNKNOWN;
}

void handleUserInput(Input input, Player& p, vector<Room> rooms, vector<Item> items) {
    string currentRoomDesc;
    string exits;
    string itemList;
    bool anyItem;

    for (const auto& room : rooms) {
        if (p.getCurrentRoom() == room.getId()) {
            currentRoomDesc = room.getDescription();

            if (!(room.getItems().empty())) {
                anyItem = true;
                itemList = "There are items in this room \n" + room.printItems();
            } 
            
            exits = room.getExits();
        }
    }

    switch (input) {
        case Input::LOOK:
            cout << currentRoomDesc << endl;

            if (anyItem) {
                cout << itemList << "\n" << endl;
            }
            break;

        case Input::LIST_ITEMS:
            cout << p.viewInventory() << "\n" << endl;
            break;

        case Input::LIST_EXITS:
            cout << exits << endl;
            break;

        case Input::UNKNOWN:
            cout << "Instruction not understood" << "\n" << endl;
            break;
    }
}
