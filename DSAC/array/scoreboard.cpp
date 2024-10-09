#include "array/scoreboard.h"

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

namespace dsac::array {

// Attempts to add a new score to the collection (if it is high enough)
void Scoreboard::add(int score, const string& name) {
    // is the new score really a high score?
    if (num_entries < capacity || score > board[num_entries - 1].get_score()) {
        if (num_entries < capacity)            // no score drops from the board
            num_entries++;                     // so overall number increases
        // shift any lower scores rightward to make room for the new entry
        int j = num_entries - 1;               // index where last entry should be
        while (j > 0 && board[j - 1].get_score() < score) {
            board[j] = board[j - 1];           // shift entry from j-1 to j
            j--;                               // and decrement j
        }
        board[j] = GameEntry(name, score);     // when done, add new entry
    }
}

// Removes and returns the high score at index i
GameEntry Scoreboard::remove(int i) {
    if (i < 0 || i >= num_entries) throw out_of_range("Invalid index");
    GameEntry temp{board[i]};                  // save the entry to be removed
    // shift entries to the right of the removed one to the left
    for (int j = i; j < num_entries - 1; j++)  // count up from i
        board[j] = board[j + 1];
    num_entries--;
    return temp;
}

// Inserts string representation of the entries to the output stream
ostream& operator<<(ostream& os, const Scoreboard& sb) {
    int n = sb.get_num_entries();
    for (int j = 0; j < n; j++) {
        os << sb.get_entry(j);
        if (j < n - 1)
            os << ", ";
        else
            os << endl;
    }
    return os;
}

// (re)assigns this state to match other
void Scoreboard::clone(const Scoreboard& other) {
    capacity = other.capacity;
    num_entries = other.num_entries;
    board = new GameEntry[capacity];
    for (int j = 0; j < num_entries; j++)
        board[j] = other.board[j];
}
    
// transfers other's state to this, and resets other to empty
void Scoreboard::transfer(Scoreboard& other) {
    capacity = other.capacity;
    num_entries = other.num_entries;
    board = other.board;
    other.board = nullptr;
    other.capacity = other.num_entries = 0;            // reset other to valid empty state
}
    
}  // namespace dsac::array
