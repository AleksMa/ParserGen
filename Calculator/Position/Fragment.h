#include "Position.h"

struct Fragment {
    Position start;
    Position end;

    Fragment(Position start, Position end): start(start), end(end) {};

    string to_str() { return start.to_str() + " - " + end.to_str(); }
};