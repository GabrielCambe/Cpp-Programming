#include <iostream>

using std::cin, std::cout, std::endl;
using std::string;

int main(){
// 2.Create a variable numberOfPlayers and ask the user to set the number of players. Use std::cin.
unsigned int numberOfPlayers;
cout << "How many players?" << endl;
// cin >> numberOfPlayers >> numberOfPlayers; // reading twice from stdin
cin >> numberOfPlayers >> endl;

// 3.Implement Macao. Read the instructions first:

// a.Every player has exactly one turn.
for( unsigned int turn = 1; turn <= numberOfPlayers; ++turn ){
    // At the beginning of the game and whenever another players turn starts
    // print a message stating whose turn it is (Player 1, Player 2, etc.).
    cout << "NEXT TURN: Player " << turn << endl;
    // d.The goal is to get as close as possible to 9 with the sum of all rolls.
    unsigned int playerRollSum = 0;
    // c.A player may roll the dice as often as he/she wants
    // (as long as he/she did not lose).
    bool rollAgain = 1;
    string yesORno;
    while( rollAgain && playerRollSum <= 9 ){
        // b.The player rolls a six-sided dice.
        // Simulate the dice using an appropriate random number generator from the standard library.
        /*STL RANDOM NUMBER DICE GENERATOR*/
        // Before every new roll, the player has to be asked if he/she wants to roll the dice again. Use std::cin for this.
        cout << "Roll the dice again?\n" << "Press 'y' to continue or any other key to quit." << endl;
        cin >> yesORno;
        (yesORno == string("y")) ? rollAgain = 1 : rollAgain = 0; 
        // if((yesORno == string("y")){ 
            // rollAgain = 1; }
        // else{ rollAgain = 0; }
    }
    // A player loses immediately if he/she has a sum greater 9.
    if( playerRollSum > 9 ){
        cout << "Player "<< rankPlayers[1] <<" has won with a score of " << rankPlayers[1].playerRollSum << "!" << endl;
    }
    // e.At the end of each turn print out the sum of a player.

}
// 4.Extend the game to show the winner in the end.
// If no player won, give an appropriate message.
// If there is a tie, print out all winners


// Example 2
// How many players?
// 2

// NEXT TURN: Player 1
// You rolled a 2! Score: 2
// Roll the dice again?
// Press 'y' to continue or any other key to quit.
// y
// You rolled a 5! Score: 7
// Roll the dice again?
// Press 'y' to continue or any other key to quit.
// n
// Your final score is: 7

// NEXT TURN: Player 2
// You rolled a 1! Score: 1
// Roll the dice again?
// Press 'y' to continue or any other key to quit.
// y
// You rolled a 1! Score: 2
// Roll the dice again?
// Press 'y' to continue or any other key to quit.
// y
// You rolled a 6! Score: 8
// Roll the dice again?
// Press 'y' to continue or any other key to quit.
// n
// Your final score is: 8
// Player 2 has won with a score of 8!

};