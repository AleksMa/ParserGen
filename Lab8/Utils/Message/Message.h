#ifndef LAB71_MESSAGE_H
#define LAB71_MESSAGE_H

#include <string>
#include <utility>

using namespace std;


class Message {
private:
    bool is_error;
    string text;

public:
    Message(bool is_error, string text);
    bool get_error();
    string get_text();
};


#endif //LAB71_MESSAGE_H
