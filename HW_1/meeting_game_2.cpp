#include <vector>
#include <iostream>

using namespace std;

class Game {
private:
    int n;
    vector<vector<bool>> meetings;
    vector<int> meet_count;
    int winner;   

public:
    Game(int numPlayers) : n{numPlayers}, winner{-1} {
        meetings.resize(n + 1, vector<bool>(n + 1, false)); // (n+1) * (n+1) vector
        meet_count.resize(n + 1, 0);
    }

    // Function to handle meetings between players
    void meet(int i, int j) {
        if (i == j) return;

        if (!meetings[i][j]) { // if i and j met, then do
            meetings[i][j] = true;  // player i has met player j
            meetings[j][i] = true;  // player j has met player i

            meet_count[i]++;
            meet_count[j]++;

            // n players in total, n - 1 other players except the first player
            if (meet_count[i] == n - 1 && winner == -1) {
                winner = i;
            }
            if (meet_count[j] == n - 1 && winner == -1) {
                winner = j;
            }
        }
    }
    void simulate() {
        for (int i = 1; i <= n - 1; i++) {
            for (int j = i + 1; j <= n; j++) {
                meet(i, j);
            }
        }
    }

    int getWinner() const {
        return winner;
    }
};

int main() {
    Game game(1000);
    game.simulate();

    int winner = game.getWinner();
    if (winner != -1) {
        cout << "Player " << winner << " is the winner!" << endl;
    } else {
        cout << "No winner yet!" << endl;
    }
    // g++ meeting_game_2.cpp -o meeting_game_2.exe; ./meeting_game_2.exe
    return 0;
}
