#include <string>

using namespace std;

class Object {
public:
    // Constructor
    Object(const string& id, const string& desc, const string& initialRoom);

    // Destructor
    ~Object();

    // Getter functions
    string getId() const;
    string getDescription() const;
    string getInitialRoom() const;

private:
    // Member variables
    string id_;
    string description_;
    string initialRoom_;
};