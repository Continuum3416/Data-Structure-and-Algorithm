#pragma once
#include <iostream>
#include <string>

namespace dsac::array {

/// A representation of an entry on a scoreboard
class GameEntry {
  private:
    /// name of the person earning the score
    std::string name;

    /// the person's score value
    int score;

  public:
    /// Constructs a game entry with given arguments
    /// @param n  the user's name ("" by default)
    /// @param s  the user's score (0 by default)
    GameEntry(const std::string& n = "", int s = 0) : name{n}, score{s} {}

    /// Returns the user's name
    /// @return the user's name
    const std::string& get_name() const { return name; }

    /// Returns the user's score
    /// @return the user's score
    int get_score() const { return score; }
};

/// Inserts string representation of the entry to the output stream
std::ostream& operator<<(std::ostream& os, const GameEntry& ge);

}  // namespace dsac::array
