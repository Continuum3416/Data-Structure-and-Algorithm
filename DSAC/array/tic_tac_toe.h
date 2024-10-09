#pragma once

#include <iostream>
#include <stdexcept>    // includes invalid_argument

namespace dsac::array {

/// Represents the state of a game of Tic-Tac-Toe
class TicTacToe {
  public:
    enum Mark { X = 1, Oh = -1, EMPTY = 0 };

  private:
    Mark board[3][3];           // 3 x 3 array of marks
    Mark current_player{X};     // the player whose move is next

  public:
    /// Creates a new game with empty board and player X's turn
    TicTacToe() { clear_board(); }

    /// Resets the board for a new game
    void clear_board() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = EMPTY;
        current_player = X;
    }

    /// Returns current content of position (i,j), which might be X, O, or EMPTY
    /// @throw invalid_argument if (i,j) out of range
    /// @returns X, O or EMPTY
    Mark get_mark(int i, int j) const {
        if (i < 0 || i > 2 || j < 0 || j > 2)
            throw std::invalid_argument("Invalid board position");
        return board[i][j];
    }

    /// Puts a mark at position (i,j) for current player
    /// @throw invalid_argument if (i,j) out of range or non-empty
    void put_mark(int i, int j) {
        if (get_mark(i,j) != EMPTY) throw std::invalid_argument("Board position occupied");
        board[i][j] = current_player;                       // place the mark for the current player
        current_player = (current_player == X ? Oh : X);     // switch players
    }

    /// Checks whether the board configuration is a win for the given player
    bool is_win(Mark mark) {
        int goal{mark*3};                                              // +3 for X and -3 for O
        return ((board[0][0] + board[0][1] + board[0][2] == goal)      // row 0
                || (board[1][0] + board[1][1] + board[1][2] == goal)   // row 1
                || (board[2][0] + board[2][1] + board[2][2] == goal)   // row 2
                || (board[0][0] + board[1][0] + board[2][0] == goal)   // column 0
                || (board[0][1] + board[1][1] + board[2][1] == goal)   // column 1
                || (board[0][2] + board[1][2] + board[2][2] == goal)   // column 2
                || (board[0][0] + board[1][1] + board[2][2] == goal)   // diagonal
                || (board[2][0] + board[1][1] + board[0][2] == goal)); // rev diag
    }

    /// Returns the winning player's mark, or EMPTY to indicate a tie or unfinished game
    Mark get_winner() {
        if (is_win(X)) return X;
        if (is_win(Oh)) return Oh;
        return EMPTY;
    }

    /// Display board on output stream
    friend std::ostream& operator<<(std::ostream& out, TicTacToe game) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                Mark m = game.get_mark(i, j);
                out << (m == X ? "X" : (m == Oh ? "O" : " "));
                if (j < 2) out << "|";                             // column boundary
            }
            if (i < 2) out << std::endl << "-+-+-" << std::endl;   // row boundary
        }
        return out;
    }
};

}  // namespace dsac::array
