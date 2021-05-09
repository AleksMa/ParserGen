#include <string>

using namespace std;

class Position {
private:
    int index;
    int line;
    int pos;

    string source;
public:

    Position(string source);

    Position &operator++();
    Position operator++(int);

    char cp();

    bool is_whitespace();
    bool is_letter();
    bool is_digit();
    bool is_newline();

    string to_str();
    int get_index();

    bool is_high_letter();
};