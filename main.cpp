#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include "GameFlow.h"
using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]) {

    string map;

    if (argc == 2) {
        map = *(argv+1);
    } else {
        cerr << "Please select a suitable map" << endl;
        return 1;
    }

	ifstream fin("json_maps/" + map);
	json j;
	fin >> j;

    GameFlow game;
    game.buildGame(j);
	game.playGame();

	// // This outputs how many things there are at the top level
	// // and the keys (5: rooms, objects, enemies, player, objective)
	// int numTypes = j.size();
	// cout << numTypes << endl;

	// for(auto e : j.items()) {
	// 	string s = e.key();
	// 	cout << s << endl;
	// }

	// // This outputs the number of rooms and something about the 2nd room
	// int numRooms = j["rooms"].size();
	// cout << numRooms << endl;
	// string room1desc =  j["rooms"][1]["desc"].get<string>();
	// cout << room1desc << endl;

	// // This retrieves the aggressiveness of the first enemy,
	// // and the list of objects that kills it as a vector
	// int agg = j["enemies"][0]["aggressiveness"].get<int>();
	// cout << agg << endl;
	// vector<string> v = j["enemies"][0]["killedby"].get<vector<string>>();
	// for(string s : v) cout << s << endl;


	// // if you want to handle fields that may or may not exist in the json
	// // file, here is one way to do it:
	// string s;
	// try {
	// 	s = j["enemies"][0]["intro_msg"].get<string>();
	// }
	// catch(const json::exception& e) {
	// 	s = "some default message";
	// }
	// cout << s << endl;
}
