// Homework 2 by Mohammed Ajoor
// Game Rock paper scissor

#include <iostream>
using std::endl;
using std::cout;

// function decleation
int RandomNumber();
void game_result(int x);
void printGame(int player, int computer);

int input() {

    int selected;

    while (true) {
        std::cin >> selected;
        if (std::cin.good() && (selected == 10 || selected == 20 || selected == 30)) { // user is only allowed to select 10,20 or 30
            return selected; // return the selected number
        }
        else {
            cout << "Please enter a VALID selection: ";
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }
    }
    return -1;
}

int main()
{

    int player_choice; // which cell the player selected
    int computer_choice; 
    char ans;

    cout << "-----------------------------------\n"
        << "     This is Rock-Paper-c game \n"
        << "-----------------------------------\n\n\n";

    // Game Introduction
    cout << "Select one of the following choices by entering the digit associated with it:" << "\n\n";
    cout << "   Rock: 10" << endl;
    cout << "   Paper: 20" << endl;
    cout << "   Scissor: 30" << endl;
    cout << endl;

    // player & computer selction
    do { 
        cout << "Player selection: ";
        player_choice = input(); // get player choice
        computer_choice = RandomNumber(); // get computer choice
        cout << endl;

        printGame(player_choice, computer_choice);
        game_result(player_choice + computer_choice);

        // Asks the user to play another round
        cout << "Do you want to play again?  Enter (N or n) to stop playing!: ";
        std::cin >> ans;
        cout << endl;
    } while (ans != 'N' && ans != 'n'); // keep playing until the user enters N or n

}

int RandomNumber() { //Generates a random number
    
    // choices are between 1 to 3
    int min = 1;
    int max = 3;
    int x = (rand() % max)+min;
    return x;

}
void printGame(int player, int computer) { // print the player choice based on the selected case
    
    
    switch (player)
    {
    case 10:
        cout << "   You have selected Rock.";
        break;
    case 20:
        cout << "   You have selected Paper.";
        break;
    case 30:
        cout << "   You have selected scissor.";
        break;
    }
    cout << endl;
    switch (computer)
    {
    case 1:
        cout << "   The computer have selected Rock.";
        break;
    case 2:
        cout << "   The computer have selected Paper.";
        break;
    case 3:
        cout << "   The computer have selected Scissor.";
        break;
    }
    cout << endl << endl;
}

void game_result(int x) { // determines who has won the game

    if (x % 11 == 0) {
        cout << "This game has ended in a DRAW!" << endl;
    }
    else {
        switch (x) {

        case 13:
            cout << "You have WON the game!" << endl;
            break;
        case 21:
            cout << "You have WON the game!" << endl;
            break;
        case 32:
            cout << "You have WON the game!" << endl;
            break;
        default:
            cout << "The computer has WON the game!" << endl;
        }
    }
}

