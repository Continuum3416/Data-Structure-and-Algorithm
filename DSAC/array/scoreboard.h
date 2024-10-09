#pragma once
#include <stdexcept>     // includes out_of_range exception
#include <string>

#include "array/game_entry.h"

namespace dsac::array {

/// Class for storing high scores ordered within an array
class Scoreboard {
  private:
    /// capacity of the array
    int capacity;

    /// number of actual entries
    int num_entries{0};

    /// pointer to an array of game entries (names & scores)
    GameEntry* board;

  public:
    /// Constructs an empty scoreboard with the given capacity for storing entries
    /// The default capacity is 10.
    /// @param cap the desired capacity for the scoreboard
    Scoreboard(int cap = 10) : capacity{cap}, board{new GameEntry[cap]} {}

    /// Attempts to add a new score to the scoreboard (if it is high enough)
    /// @param int score
    /// @param string name
    void add(int score, const std::string& name);

    /// Removes and returns the scoreboard entry at index i
    /// @param i  index within scoreboard
    /// @throws out_of_range if not 0 <= i < get_num_entries()
    /// @returns GameEntry instance
    GameEntry remove(int i);

    /// Returns the capacity of the scoreboard
    /// @returns the capacity of the scoreboard
    int get_capacity() const { return capacity; }

    /// Returns the number of current entries stored
    /// @returns the number of current entries stored
    int get_num_entries() const { return num_entries; }

    /// Returns a reference to the entry at index i
    /// @param i  index such that 0 <= i < getNumEntries()
    /// @returns the entry at index i
    const GameEntry& get_entry(int i) const { return board[i]; }

    //------------------------------------------------
    // rule-of-five behaviors
    //------------------------------------------------

    /// Copy constructor
    Scoreboard(const Scoreboard& other) { clone(other); }

    /// Copy assignment
    Scoreboard& operator=(const Scoreboard& other) {
        if (this != &other) {                        // nothing to be done for self-assignment
            delete[] board;
            clone(other);
        }
        return *this;
    }

    /// Move constructor
    Scoreboard(Scoreboard&& other) { transfer(other); }

    /// Move assignment
    Scoreboard& operator=(Scoreboard&& other) {
        if (this != &other) {                        // nothing to be done for self-assignment
            delete[] board;
            transfer(other);         
        }
        return *this;
    }

    /// destructor
    ~Scoreboard() { delete[] board; }
    
  private:
    void clone(const Scoreboard& other);
    void transfer(Scoreboard& other);
};  // end of Scorebard class

/// Inserts string representation of the entry to the output stream
std::ostream& operator<<(std::ostream& os, const Scoreboard& sb);

}  // namespace dsac::array
