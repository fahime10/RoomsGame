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
        
};