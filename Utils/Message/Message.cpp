#include "Message.h"

Message::Message(bool is_error, string text): is_error(is_error), text(std::move(text)) {}

bool Message::get_error() {
    return is_error;
}

string Message::get_text() {
    return text;
}

