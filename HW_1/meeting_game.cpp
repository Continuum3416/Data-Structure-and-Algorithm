#include <iostream>
#include <vector>

class Game {
private:
    int n;              // Number of players
    std::vector<std::vector<bool>> meetings; // Meeting tracker for each player
    int winner;        // To track the winner

public:
    Game(int numPlayers) : n{numPlayers}, winner{-1} {
        meetings.resize(n + 1, std::vector<bool>(n + 1, false)); // Create a 2D array for meetings
    }

    void meet(int i, int j) {
        if (i == j) return;

        meetings[i][j] = true;
        meetings[j][i] = true;

        if (checkAllMet(i) && winner == -1) {
            winner = i; 
            std::cout << "Player " << winner << " is the winner!" << std::endl;
        }

        if (checkAllMet(j) && winner == -1) {
            winner = j;
            std::cout << "Player " << winner << " is the winner!" << std::endl;
        }
    }

    // Function to check if a player has met all others
    bool checkAllMet(int player) {
        for (int k = 1; k <= n; ++k) {
            if (k != player && !meetings[player][k]) {
                return false; // Found a player that has not been met
            }
        }
        return true; // All players have been met
    }

    // Function to get the current winner
    int getWinner() const {
        return winner;
    }
};


int main(){
    int n = 100; // Number of players
    Game game(n);

    // Example meetings
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++)
            game.meet(i, j);
    }

    // You can also check for a winner at any point
    if (game.getWinner() != -1) {
        std::cout << "Current winner: Player " << game.getWinner() << std::endl;
    } else {
        std::cout << "No winner yet!" << std::endl;
    }

    return 0;

    // Run: g++ meeting_game.cpp -o meeting_game.exe; ./meeting_game.exe   
    return 0;
}