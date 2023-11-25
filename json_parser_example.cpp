// The following are some examples of how the https://github.com/nlohmann/json
// JSON parser can be used.
//
// In this example we read from the sample map1.json file.
// Put the json.hpp file in the same folder as everything else.

#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

int main() {

	ifstream fin("map1.json");
	json j; // object that represents the json data
	fin >> j; // read from file into j

	// JSON is essentially a set of key:value pairs, although
	// the "value" themselves can be a single value, or an array of
	// other values, or some other set of key:value pairs.
	// This gives a rich nested structure.

	// This outputs how many things there are at the top level
	// and the keys (5: rooms, objects, enemies, player, objective)
	int numTypes = j.size();
	cout << numTypes << endl;

	for(auto e : j.items()) {
		string s = e.key();
		cout << s << endl;
	}

	// This outputs the number of rooms and something about the 2nd room
	int numRooms = j["rooms"].size();
	cout << numRooms << endl;
	string room1desc =  j["rooms"][1]["desc"].get<string>();
	cout << room1desc << endl;

	// This retrieves the aggressiveness of the first enemy,
	// and the list of objects that kills it as a vector
	int agg = j["enemies"][0]["aggressiveness"].get<int>();
	cout << agg << endl;
	vector<string> v = j["enemies"][0]["killedby"].get<vector<string>>();
	for(string s : v) cout << s << endl;


	// if you want to handle fields that may or may not exist in the json
	// file, here is one way to do it:
	string s;
	try {
		s = j["enemies"][0]["intro_msg"].get<string>();
	}
	catch(const json::exception& e) {
		s = "some default message";
	}
	cout << s << endl;
}
