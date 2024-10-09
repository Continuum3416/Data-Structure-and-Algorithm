#include <cstdlib>  // provides EXIT_SUCCESS
#include <iostream>

#include "array/tic_tac_toe.h"

using namespace std;
using namespace dsac::array;


int main() {
    TicTacToe game;
    string outcome[] = {"O wins", "Tie", "X wins"};  // rely on enum ordering

    /* X moves: */               /* O moves: */
    game.put_mark(1,1);          game.put_mark(0,2);
    game.put_mark(2,2);          game.put_mark(0,0);
    game.put_mark(0,1);          game.put_mark(2,1);
    game.put_mark(1,2);          game.put_mark(1,0);
    game.put_mark(2,0);
    cout << game << endl;
    cout << outcome[1 + game.get_winner()] << endl;

    game.clear_board();
    cout << endl << game << endl;
    
    /* X moves: */               /* O moves: */
    game.put_mark(0,2);          game.put_mark(2,2);
    game.put_mark(0,0);          game.put_mark(0,1);
    game.put_mark(2,0);          game.put_mark(1,1);
    game.put_mark(1,0);
    cout << endl << game << endl;
    cout << outcome[1 + game.get_winner()] << endl;

    return EXIT_SUCCESS;
}

