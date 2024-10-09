#include "array/game_entry.h"

#include <iostream>
using namespace std;

namespace dsac::array {

/// Inserts string representation of the entry to the output stream
ostream& operator<<(ostream& os, const GameEntry& ge) {
    return os << "(" << ge.get_name() << "," << ge.get_score() << ")";
}

}  // namespace dsac::array
